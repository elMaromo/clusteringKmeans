
#include <iostream>
#include <math.h>
#include "DbStreamArd.h"
#include <stdlib.h>
#include <vector>
#include <unordered_set>

using namespace std;

DbStream::DbStream(int minVecAux, float minDistAux, int i_numDimensions)
{
    this->minVec = minVecAux;
    this->minD = minDistAux;
    this->numDimensions = i_numDimensions;

    if (numDimensions > maxDimensions)
    {
        numDimensions = maxDimensions;
    }
}

float DbStream::distEuclid(float point1[], float point2[])
{
    float dist = 0;
    for (int i = 0; i < maxDimensions; i++)
    {
        dist = dist + (point1[i] - point2[i]) * (point1[i] - point2[i]);
    }

    dist = sqrt(dist);
    return dist;
}

void DbStream::eraseRepeated(int arr[], int size)
{
    for (int i = 0; i < size; ++i)
    {
        // Check if the current element is not already marked as -1
        if (arr[i] != -1)
        {
            for (int j = i + 1; j < size; ++j)
            {
                // Check for repeated values
                if (arr[i] == arr[j])
                {
                    // Set repeated values to -1
                    arr[j] = -1;
                }
            }
        }
    }
}

int DbStream::getNeighboors(int neightboors[], int index)
{
    int numV = 0;

    for (int i = 0; i < currentDataInit; i++)
    {
        float dist = distEuclid(data[i], data[index]);
        if (dist < minD && i != index && numV < maxNeightboors)
        {
            neightboors[numV] = i;
            numV++;
        }
    }

    for (int i = numV; i < maxNeightboors; i++)
    {
        neightboors[i] = -1;
    }

    return numV;
}

void DbStream::muestraAgrupaciones()
{
    cout << "agrupaciones";
    cout << endl;
    for (int i = 0; i < maxDataStored; i++)
    {
        cout << labelData[i];
        cout << " ";
    }
    cout << endl;
    cout << endl;
}

int DbStream::functionDbStream(float point[])
{
    int pointClass = 0;
    int indexPoint = assignPointToData(point);
    labelData[indexPoint] = -1;

    for (int i = 0; i < currentDataInit; i++)
    {
        if (labelData[i] == -1)
        {
            int numNeightboors = getNeighboors(currentNeightboors, i);

            if (numNeightboors >= minVec)
            {
                labelData[i] = pointClass;

                while (numNeightboors != 0)
                {
                    if (labelData[currentNeightboors[0]] == -1)
                    {
                        labelData[currentNeightboors[0]] = pointClass;
                        getNeighboors(adyacentNeightboors, currentNeightboors[0]);
                        addToArray(currentNeightboors, adyacentNeightboors, maxNeightboors);
                        eraseRepeated(currentNeightboors, maxNeightboors);
                        eraseFromArray(currentNeightboors, 0, maxNeightboors);
                    }
                    else
                    {
                        eraseFromArray(currentNeightboors, 0, maxNeightboors);
                    }
                }

                pointClass++;
            }
        }
    }

    return pointClass;
}

int DbStream::assignPointToData(float newPoint[])
{
    int indexOfNewPoint = -1;
    if (currentDataInit < maxDataStored)
    {
        for (int currDim = 0; currDim < numDimensions; currDim++)
        {
            data[currentDataInit][currDim] = newPoint[currDim];
        }

        indexOfNewPoint = currentDataInit;
        currentDataInit++;
    }
    else
    {
        // print a random number from 0 to maxDataStored
        indexOfNewPoint = random(maxDataStored);

        for (int currDim = 0; currDim < numDimensions; currDim++)
        {
            data[indexOfNewPoint][currDim] = newPoint[currDim];
        }
    }

    return indexOfNewPoint;
}

void DbStream::clearLabels()
{
    for (int i = 0; i < maxDataStored; i++)
    {
        labelData[i] = -1;
    }
}

template <typename T>
void DbStream::eraseFromArray(T array[], int index, int size)
{
    for (int i = 0; i < size; i++)
    {
        if (i > index)
        {
            if (i == size - 1)
            {
                array[size - 1] = -1;
            }
            else
            {
                array[i] = array[i + 1];
            }
        }
    }
}

template <typename T>
void DbStream::addToArray(T array1[], T array2[], int size)
{
    for (int i = 0; i < size; i++)
    {
        if (array1[i] == -1)
        {
            for (int j = 0; j < size; j++)
            {
                if (array2[j] == -1 || i == size)
                {
                    return;
                }
                else
                {
                    array1[i] = array2[j];
                    i++;
                }
            }

            return;
        }
    }

    return;
}

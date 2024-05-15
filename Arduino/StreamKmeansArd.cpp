#include <Arduino.h>
#include <math.h>
#include <algorithm>
#include <iterator>
#include "SKM.h"


void SKM::setUp(int numKlusters, bool forget, float learningR, int numDimensions)
{
  this->numKlusters = numKlusters;
  if (this->numKlusters > 10)
  {
    this->numKlusters = 10;
  }

  this->numDimensions = numDimensions;
  if (this->numDimensions > 10)
  {
    this->numDimensions = 10;
  }

  centInicialiced = 0;
  forgetfull = forget;
  learnRate = learningR;

  for (int i = 0; i < numKlusters; ++i)
  {
    tamCent[0] = 0;
  }
}

int SKM::funcionStreamKmeans(float point[])
{
  int clas = -1;

  if (centInicialiced < numKlusters)
  {
    for (int i = 0; i < numDimensions; i++)
    {
      centroids[centInicialiced][i] = point[i];
    }
    clas = centInicialiced;
    centInicialiced++;
  }
  else
  {
    clas = centMasCerc(point);

    if (forgetfull)
    {
      for (int i = 0; i < numDimensions; i++)
      {
        centroids[clas][i] = centroids[clas][i] + learnRate * (point[i] - centroids[clas][i]);
      }
    }
    else
    {
      float incr = (float)1.00 / ((float)tamCent[clas] + (float)1.00);
      for (int i = 0; i < numDimensions; i++)
      {
        centroids[clas][i] = centroids[clas][i] + incr * (point[i] - centroids[clas][i]);
      }
    }
  }

  tamCent[clas]++;
  return clas;
}

int SKM::centMasCerc(float point[])
{
  int masCerc = -1;
  float disMasCerc = 0;

  for (int i = 0; i < numKlusters; i++)
  {
    float distAct = distEuclid(point, centroids[i]);

    if (i == 0 || distAct < disMasCerc)
    {
      masCerc = i;
      disMasCerc = distAct;
    }
  }

  return masCerc;
}

float SKM::distEuclid(float point1[], float point2[] )
{
  float dist = 0;
  for (int i = 0; i < numDimensions; i++)
  {
    dist = dist + (point1[i] - point2[i]) * (point1[i] - point2[i]);
  }
  
  dist = sqrt(dist);
  return dist;
}

void SKM::showCentroids()
{
  
  //cout << "centroides";
  //cout << endl;
  //for (int i = 0; i < centInicialiced; i++)
  //{
  //  for (int j = 0; j < numDimensions; j++)
  //  {
  //    cout << centroids[i][j] << " ";
  //  }
  //  cout << endl;
  //}
  //cout << endl;
}


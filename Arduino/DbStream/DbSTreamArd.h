#ifndef _DBSTREAM_H
#define _DBSTREAM_H
#include <vector>
using namespace std;

class DbStream
{

private:
    int maxDataStored = 100;
    int maxDimensions = 10;
    int numDimensions;
    int maxNeightboors = 10;

    int minVec;
    float minD;
    int currentDataInit = 0;
    int currentNeightboors[10];
    int adyacentNeightboors[10];

    void eraseRepeated(int arr[], int size);
    float distEuclid(float point1[], float point2[]);
    int getNeighboors(int neightboors[], int index);

    void clearLabels();
    int assignPointToData(float newPoint[]);
    template <typename T>
    void eraseFromArray(T array[], int index, int size);
    template <typename T>
    void addToArray(T array1[], T array2[], int size);

public:
    float data[100][10];
    int labelData[100];
    DbStream(int minVecAux, float minDistAux, int i_numDimensions);
    void muestraAgrupaciones();
    int functionDbStream(float point[]);
};

#endif
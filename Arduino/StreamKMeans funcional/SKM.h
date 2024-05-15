#ifndef _STREAMKMEANS_H
#define _STREAMKMEANS_H
#include <Arduino.h>

class SKM
{
private:
    float centroids[10][10];
    int tamCent[10];

    float learnRate;
    bool forgetfull;
    int centInicialiced;
    int numKlusters;

    float distEuclid(float point1[], float point2[] );
    int centMasCerc(float point[]);

public:
    int numDimensions;
    void setUp(int numKlusters, bool forget, float learningR, int numDimensions);
    int funcionStreamKmeans(float point[]);
    void showCentroids();
};

#endif

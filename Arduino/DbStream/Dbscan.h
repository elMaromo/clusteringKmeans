#ifndef _DBSCAN_H
#define _DBSCAN_H
#include <vector>
using namespace std;

class Dbscan
{
private:
    void quitaRepes(vector<int> &v);
    float distEuclid(vector<float> &x, vector<float> &y);
    vector<int> getVecinos(vector<vector<float>> &X, int index, float minD);

public:
    void muestraAgrupaciones(vector<int> &idx);
    vector<int> funcionDbscan(vector<vector<float>> &X, int minP, float distMin);
};

#endif

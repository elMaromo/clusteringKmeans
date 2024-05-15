#ifndef _DBSTREAM_H
#define _DBSTREAM_H
#include <vector>
using namespace std;

class DbStream
{

private:
    vector<int> idx;
    vector<vector<float>> datos;
    int minVec;
    float minD;

    void quitaRepes(vector<int> &v);
    float distEuclid(vector<float> &x, vector<float> &y);
    vector<int> getVecinos(int index);

public:
    DbStream(int minVecAux, float minDistAux);
    void muestraAgrupaciones();
    int funcionDbStream(vector<float> &x);
};

#endif
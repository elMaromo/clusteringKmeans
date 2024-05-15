
#ifndef _STREAMKMEANS_H
#define _STREAMKMEANS_H

#include <vector>
using namespace std;

class Streamkmeans
{
private:
    vector<vector<float>> centroides;
    vector<int> tamCent;

    float learnRate;
    bool forgetfull;
    int centInicializados;
    int k;

    float distEuclid(vector<float> &x, vector<float> &y);
    int centMasCerc(vector<float> &x);

public:
    Streamkmeans(int kAux, bool forget, float learningR);
    int funcionStreamKmeans(vector<float> &x);
    void muestraCentroides();
};

#endif

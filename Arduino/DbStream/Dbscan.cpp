
#include <iostream>
#include <math.h>
#include "Dbscan.h"
#include <stdlib.h>
#include <vector>
#include <unordered_set>

using namespace std;

float Dbscan::distEuclid(vector<float> &x, vector<float> &y)
{
    float dist = 0;
    for (int i = 0; i < x.size(); i++)
    {
        dist = dist + (x.at(i) - y.at(i)) * (x.at(i) - y.at(i));
    }

    dist = sqrt(dist);
    return dist;
}


void Dbscan::quitaRepes(vector<int>& v)
{

    std::vector<int>::iterator itr = v.begin();
    std::unordered_set<int> s;

    for (auto curr = v.begin(); curr != v.end(); ++curr)
    {
        if (s.insert(*curr).second)
        {
            *itr++ = *curr;
        }
    }

    v.erase(itr, v.end());
}

vector<int> Dbscan::getVecinos(vector<vector<float>> &X, int index, float minD)
{
    vector<int> vecinos;
    int numV = 0;

    for (int i = 0; i < X.size(); i++)
    {
        float dist = distEuclid(X[i], X[index]);

        if (dist < minD && i != index)
        {
            vecinos.push_back(i);
        }
    }

    return vecinos;
}

vector<int> Dbscan::funcionDbscan(vector<vector<float>> &X, int minP, float distMin)
{
    vector<int> idx;
    idx.assign(X.size(), -1);

    int clase = 0;

    for (int i = 0; i < X.size(); i++)
    {
        if (idx[i] == -1)
        {
            vector<int> vecinos = getVecinos(X, i, distMin);

            if (vecinos.size() >= minP)
            {
                idx[i] = clase;

                while (vecinos.size() != 0)
                {
                    if (idx[vecinos[0]] == -1)
                    {
                        idx[vecinos[0]] = clase;
                        vector<int> vecinos2 = getVecinos(X, vecinos[0], distMin);
                        vecinos.insert(vecinos.end(), vecinos2.begin(), vecinos2.end());
                        quitaRepes(vecinos);
                        vecinos.erase(vecinos.begin());
                    }
                    else
                    {
                        vecinos.erase(vecinos.begin());
                    }
                }

                clase++;
            }
        }
    }

    return idx;
}

void Dbscan::muestraAgrupaciones(vector<int> &idx)
{
    cout << "agrupaciones";
    cout << endl;
    for (int i = 0; i < idx.size(); i++)
    {
        cout << idx[i];
        cout << " ";
    }
    cout << endl;
    cout << endl;
}






#include <iostream>
#include <math.h>
#include "DbStream.h"
#include <stdlib.h>
#include <vector>
#include <unordered_set>

using namespace std;

DbStream::DbStream(int minVecAux, float minDistAux)
{
    this->minVec = minVecAux;
    this->minD = minDistAux;
}

float DbStream::distEuclid(vector<float> &x, vector<float> &y)
{
    float dist = 0;
    for (int i = 0; i < x.size(); i++)
    {
        dist = dist + (x.at(i) - y.at(i)) * (x.at(i) - y.at(i));
    }

    dist = sqrt(dist);
    return dist;
}

void DbStream::quitaRepes(vector<int> &v)
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

vector<int> DbStream::getVecinos(int index)
{
    vector<int> vecinos;
    int numV = 0;

    for (int i = 0; i < datos.size(); i++)
    {
        float dist = distEuclid(datos[i], datos[index]);

        if (dist < minD && i != index)
        {
            vecinos.push_back(i);
        }
    }

    return vecinos;
}

void DbStream::muestraAgrupaciones()
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

int DbStream::funcionDbStream(vector<float> &x)
{
    int clase = 0;

    datos.push_back(x);
    idx.clear();
    idx.assign(datos.size(), -1);

    for (int i = 0; i < datos.size(); i++)
    {
        if (idx[i] == -1)
        {
            vector<int> vecinos = getVecinos(i);

            if (vecinos.size() >= minVec)
            {
                idx[i] = clase;

                while (vecinos.size() != 0)
                {
                    if (idx[vecinos[0]] == -1)
                    {
                        idx[vecinos[0]] = clase;
                        vector<int> vecinos2 = getVecinos(vecinos[0]);
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

    return clase;
}

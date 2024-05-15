
#include <iostream>
#include <math.h>
#include "StreamKmeans.h"

#include <vector>
#include <stdlib.h>

using namespace std;

Streamkmeans::Streamkmeans(int kAux, bool forget, float learningR)
{
       k = kAux;

       for (int i = 0; i < k; ++i)
       {
              tamCent.push_back(0);
       }

       centInicializados = 0;
       forgetfull = forget;
       learnRate = learningR;
}

int Streamkmeans::funcionStreamKmeans(vector<float> &x)
{
       int clas = -1;

       if (centInicializados < k)
       {
              centroides.push_back(x);
              clas = centInicializados;
              centInicializados++;
       }
       else
       {
              clas = centMasCerc(x);

              if (forgetfull)
              {
                     for (int i = 0; i < centroides[0].size(); i++)
                     {
                            centroides[clas][i] = centroides[clas][i] + learnRate * (x[i] - centroides[clas][i]);
                     }
              }
              else
              {
                     float incr = (float)1.00 / ((float)tamCent[clas] + (float)1.00);
                     for (int i = 0; i < centroides[0].size(); i++)
                     {
                            centroides[clas][i] = centroides[clas][i] + incr * (x[i] - centroides[clas][i]);
                     }
              }
       }

       tamCent[clas]++;
       return clas;
}

int Streamkmeans::centMasCerc(vector<float> &x)
{
       int masCerc = -1;
       float disMasCerc = 0;

       for (int i = 0; i < k; i++)
       {
              float distAct = distEuclid(x, centroides[i]);

              if (i == 0 || distAct < disMasCerc)
              {
                     masCerc = i;
                     disMasCerc = distAct;
              }
       }

       return masCerc;
}

float Streamkmeans::distEuclid(vector<float> &x, vector<float> &y)
{
       float dist = 0;
       for (int i = 0; i < x.size(); i++)
       {
              dist = dist + (x.at(i) - y.at(i)) * (x.at(i) - y.at(i));
       }

       dist = sqrt(dist);
       return dist;
}

void Streamkmeans::muestraCentroides()
{
       cout << "centroides";
       cout << endl;
       for (int i = 0; i < centInicializados; i++)
       {
              for (int j = 0; j < centroides[0].size(); j++)
              {
                     cout << centroides[i][j] << " ";
              }
              cout << endl;
       }
       cout << endl;
}

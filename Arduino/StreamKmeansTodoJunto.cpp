// Online C++ compiler to run C++ program online
#include <iostream>
#include <math.h>

#include <stdlib.h>

using namespace std;

class Streamkmeans
{
private:
    float centroids[10][10];
    int tamCent[10];
    int numDimensions;

    float learnRate;
    bool forgetfull;
    int centInicialiced;
    int numKlusters;

    float distEuclid(float point1[], float point2[] );
    int centMasCerc(float point[]);

public:
    Streamkmeans(int numKlusters, bool forget, float learningR, int numDimensions);
    int funcionStreamKmeans(float point[]);
    void showCentroids();
};

Streamkmeans::Streamkmeans(int numKlusters, bool forget, float learningR, int numDimensions)
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

int Streamkmeans::funcionStreamKmeans(float point[])
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

int Streamkmeans::centMasCerc(float point[])
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

float Streamkmeans::distEuclid(float point1[], float point2[] )
{
    cout << "point1 " << point1[0] << " " << point1[1] << " " << point1[2];
    cout << "point1 " << point2[0] << " " << point2[1] << " " << point2[2];
       float dist = 0;
       for (int i = 0; i < numDimensions; i++)
       {
              dist = dist + (point1[i] - point2[i]) * (point1[i] - point2[i]);
       }
       dist = sqrt(dist);
       cout << " DISTANCIA" << dist << "\n";
       return dist;
}

void Streamkmeans::showCentroids()
{
       cout << "centroides";
       cout << endl;
       for (int i = 0; i < centInicialiced; i++)
       {
              for (int j = 0; j < numDimensions; j++)
              {
                     cout << centroids[i][j] << " ";
              }
              cout << endl;
       }
       cout << endl;
}


int main() {
    // Write C++ code here
    Streamkmeans skm(3, false, 0.2, 3);
    
    float point1[3] = {1.7, 1.7, 1.7};
    float point2[3] = {8.7, 8.7, 8.7};
    float point3[3] = {20.7, 20.7, 20.7};
    float point4[3] = {2.7, 1.7, 1.7};
    float point5[3] = {1.7, 2.7, 2.7};
    float point6[3] = {5.7, 8.7, 9.7};
    float point7[3] = {20.7, 21.7, 21.7};
    float point8[3] = {20.7, 25.7, 20.7};
    float point9[3] = {20.7, 20.7, 25.7};


    cout<<skm.funcionStreamKmeans(point1);
    cout<<skm.funcionStreamKmeans(point2);
    cout<<skm.funcionStreamKmeans(point3);
    skm.showCentroids();
    cout<<skm.funcionStreamKmeans(point4);
    skm.showCentroids();
    cout<<skm.funcionStreamKmeans(point5);
    skm.showCentroids();
    cout<<skm.funcionStreamKmeans(point6);
    skm.showCentroids();

    return 0;
}
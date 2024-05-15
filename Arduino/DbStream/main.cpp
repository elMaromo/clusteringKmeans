#include <iostream>
#include <vector>

//#include "kmeans.h"
//#include "streamkmeans.h"
//#include "Dbscan.h"
#include "DbStream.h"


using namespace std;

int main()
{
  //g++ *.cpp -o main.exe

  //Serial.begin(9600);
  //while (!Serial) {
  //  ;
  //}

  vector<vector<float>> X{
      {8, 1},
      {2, 5},
      {0, 9},
      {8, 1},
      {4, 3},
      {8, 0},
      {9, 1},
      {4, 5},
      {8, 3},
      {3, 5}};

  int k = 3;



  int minP = 2;
  float distMin = 3;

  DbStream dbStr( minP, distMin );
  
  //vector<int> idx = dbsc.funcionDbscan( X, minP, distMin);

  for (int i = 0; i < X.size(); i++)
  {
    dbStr.funcionDbStream( X[i] );
    dbStr.muestraAgrupaciones();
    cout<<endl;
  }
  

  /*

  streamkmeans kmen(3, false, 0.2);

  for (int i = 0; i < X.size(); i++)
  {
    cout << X.at(i).at(0) << " " << X.at(i).at(1) << endl;
    cout << "clase: " << kmen.funcionStreamKmeans(X.at(i)) << endl
         << endl;
    kmen.muestraCentroides();
  }

  */

  ///kmen.~streamkmeans();

  //Serial.println(distEuclid( centroides[0], centroides[1] ));
  //funcion_calcula_agrupacion( numPuntos, X, centroides, k, idx );
  //funcion_calcula_centroides( numPuntos, X, idx, k, centroides );

  return 0;
}

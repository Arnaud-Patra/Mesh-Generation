#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector> //for Mesh and Front
#include <math.h> //For sqrt(3)
#include <fstream> //readfile
using namespace std;

void Round(float * seg = nullptr, int n = 4 ){
   int rnd = pow(10,n);
   cout << rnd<<endl;

   seg[0] = roundf(seg[0] * rnd) / rnd;
   seg[1] = roundf(seg[1] * rnd) / rnd;
   seg[2] = roundf(seg[2] * rnd) / rnd;
   seg[3] = roundf(seg[3] * rnd) / rnd;
   cout << "seg       = "<< seg[0]<< " " << seg[1]<< " "<< seg[2]<< " "<< seg[3]<< endl;
   cout <<"coucou round fin"<<endl;
}

int main(){
   float * edge = new float[4];
   edge[0] = 2.33216875;
   edge[1] = 3.15489845;
   edge[2] = 0.66897556;
   edge[3] = 10.5498755;
   float * edge_copy = new float[4];
   edge_copy[0] = edge[0];edge_copy[1] = edge[1];edge_copy[2] = edge[2];edge_copy[3] = edge[3]; //We create identical vectors for tests.

   Round(edge_copy,2);

   cout << "coucoufinal"<<endl;
   cout << "edge       = "<< edge[0]<< " " << edge[1]<< " "<< edge[2]<< " "<< edge[3]<< endl;
   cout << "edge_copy = "<<edge_copy[0]<< " " << edge_copy[1]<< " "<< edge_copy[2]<< " "<< edge_copy[3]<< endl;
   return 0;
}

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector> //for Mesh and Front
#include <math.h> //For sqrt(3)
#include <fstream> //readfile
using namespace std;

void Round(float * seg = nullptr, int n =2){
   int rnd = pow(10,n);
   seg[0] = roundf(seg[0] * rnd) / rnd;
   seg[1] = roundf(seg[1] * rnd) / rnd;
   seg[2] = roundf(seg[2] * rnd) / rnd;
   seg[3] = roundf(seg[3] * rnd) / rnd;

}


int main()
{
    int n_round =3;
    float* edge_1 = new float[4];
    edge_1[0] = 4.44444;
    edge_1[1] = 10;
    edge_1[2] = 3.88889;
    edge_1[3] = 9.03775;
    float* Front_edge = new float[4];
    Front_edge[0] = 4.44444;
    Front_edge[1] = 10;
    Front_edge[2] =  3.88889;
    Front_edge[3] =  9.03775;

    float* edge_1_copy = new float[4];  //creation identical edges for the tests.
    float* edge_2_copy = new float[4];
    edge_1_copy[0]=edge_1[0] ;edge_1_copy[1]=edge_1[1] ;edge_1_copy[2]=edge_1[2] ;edge_1_copy[3]=edge_1[3];

    Round(edge_1_copy,n_round);//We use round to tet if segments are the same. Otherwise we have rounding errors.
    Round(Front_edge,n_round);
    cout << "avant if"<< endl;
   if( ((edge_1_copy[0]==Front_edge[0])and(edge_1_copy[1]==Front_edge[1])and(edge_1_copy[2]==Front_edge[2])and(edge_1_copy[3] == Front_edge[3]))
             or ((edge_1_copy[0]==Front_edge[2])and(edge_1_copy[1]==Front_edge[3])and(edge_1_copy[2]==Front_edge[0])and(edge_1_copy[3] == Front_edge[1])) ){//we test if edge_1 is in Front (and only in Front).

                 cout <<"coucou"<< endl;
             }
             cout << "après if"<< endl;
   return 0;
}

#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector> //for mesh and Front
#include <math.h> //For sqrt(3)
#include <fstream> //readfile

#include <boost/algorithm/string/split.hpp> //For read file
#include <boost/algorithm/string/classification.hpp>

#pragma once

using namespace std;

class AdvancingFront{

public :

   AdvancingFront();  // The constructor
   ~AdvancingFront();

   //creation of empty stack
   vector<float*> Front; //Front and Mesh need to be accessed from the other functions.

   //Creation of the Mesh
   vector<float *> Mesh;

   float rho = 0.5;

   int Discret(float rho);

   void NewPoint(const float * seg, float ** return_new_point);

   float CheckNeighbors(float * a, float rho);

   int Collision(float * a, float * b, float * c);

   int Intersect_segment(float * a,float * b,float * P);

   void Round(float * seg, int n );

   void WritePoints();

};

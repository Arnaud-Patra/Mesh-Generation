#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <stack> //for Front
#include <vector> //for Mesh
#include <math.h> //For sqrt(3)
#include <fstream> //readfile

using namespace std;

int Intersect_segment(float * a,float * b, float * P){
   float d_rho = 1/sqrt(M_PI*0.5); //DEBUG
   if (max(a[0], b[0]) < min(P[0], P[2])){ //Check if this interval exists
      // There is no mutual abscisses => no intersection possible.
      cout << "no mutual abscisses"<<endl;
      return 0; //This skips the iteration we are on and we get the next segment.
   }
   // We have the two lines formed by the segments :
   //f1(x) = A1*x + b1 = y
   //f2(x) = A2*x + b2 = y
   if ((P[0]-P[2])==0){
      P[0] = P[0]+(d_rho/100);
      cout << "(P[0]-P[2])==0"<<endl;
      //DEBUG temporary solution
   }else if ((a[0]-b[0])==0){
      a[0] = a[0]+(d_rho/100);
      cout << "a[0]=b[0]"<<endl;

   }
   float A1 = (a[1]-b[1])/(a[0]-b[0]);
   float A2 = (P[1]-P[3])/(P[0]-P[2]);
   float b1 = a[1]-A1*a[0];
   float b2 = P[1]-A2*P[0];
   if (A1==A2){
      //Segments are parallel, no intersection can be found, check next segment of the mesh.
      cout << "Segments are parallel"<<endl;
      return 0;
   }
   float Xi = (b2-b1)/(A1-A2); //Abscisse of the point of intersection of the two lines, we just need to check if it is in the semgents.
   //Test if Xi in in Ii. This is the only test we need because we already have an intersection.
   if ( (Xi < max(min(a[0], b[0]), min(P[0], P[2]))) or (Xi > min(max(a[0], b[0]), max(P[0], P[2]))) ){
      //intersection out of bound
      cout << "intersection out of bound"<<endl;
      return 0;
   }else{ //intersection found, we have a collision.
      cout << "intersection found"<<endl;
      return 1; //We found one collision, that is enouth, we can exit this function.
   }
   return 0;
}



int main(){

//test
   float * a = new float[2];
   float * b = new float[2];
   float * P_ = new float[4];

/*
   // intersection test
   a[0] = 1;
   a[1] = 1;
   b[0] = 0;
   b[1] = 0;
   P_[0] = 0;
   P_[1] = 1;
   P_[2] = 1;
   P_[3] = 0;
*/

/*
   //no intersection test
   a[0] = 1;
   a[1] = 1;
   b[0] = 0;
   b[1] = 0;
   P_[0] = 1;
   P_[1] = 2;
   P_[2] = 0;
   P_[3] = 1;
// Should return : "segments are parallel" and "intersection not found"
*/

/*
//no intersection test
   a[0] = 1;
   a[1] = 1;
   b[0] = 0;
   b[1] = 0.51;
   P_[0] = 1.123;
   P_[1] = 2;
   P_[2] = 1;
   P_[3] = 0;
   // Should return : "intersection out of bound"
*/

/*
   // intersection test with vertical segment
   a[0] = 1;
   a[1] = 0.5;
   b[0] = 0;
   b[1] = 0.5;
   P_[0] = 0.5;
   P_[1] = 0;
   P_[2] = 0.5;
   P_[3] = 1;
*/
   P_[0] = 1;
   P_[1] = 0.5;
   P_[2] = 0;
   P_[3] = 0.5;
   a[0] = 0.5;
   a[1] = 0;
   b[0] = 0.5;
   b[1] = 1;

   float rho = 0.5;
   static float d_rho = 1/sqrt(M_PI*0.5);

   Intersect_segment( a, b, P_);

   return 0;
}

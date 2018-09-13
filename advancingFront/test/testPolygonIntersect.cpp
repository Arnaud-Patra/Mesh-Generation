#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector> //for Mesh and Front
#include <math.h> //For sqrt(3)
#include <fstream> //readfile

using namespace std;



int Intersect_segment(float * a, float * P){
   float * b = new float[2];
   b[0] = 0; //DEBUG : might cause a problem is the figure goes x <0.
   b[1] = a[1];

   float * Ii = new float[2];
   Ii[0] = max(min(a[0], b[0]), min(P[0], P[2]));
   Ii[1] = min(max(a[0], b[0]), max(P[0], P[2]));

   if (max(a[0], b[0]) < min(P[0], P[2])){ //Check if this interval exists
        // There is no mutual abscisses => no intersection possible.
        return 0; //This skips the iteration we are on and we get the next segment.
    }
    // We have the two lines formed by the segments :
    //f1(x) = A1*x + b1 = y
    //f2(x) = A2*x + b2 = y
    float A1 = (a[1]-b[1])/(a[0]-b[0]); //Might divide by 0 !
    float A2 = (P[1]-P[3])/(P[0]-P[2]);
    float b1 = a[1]-A1*a[0];
    float b2 = P[1]-A2*P[0];
    if (A1==A2){
      //Segments are parallel, no intersection can be found, check next segment of the mesh.
      return 0;
    }

    float Xi = (b2-b1)/(A1-A2); //Abscisse of the point of intersection of the two lines, we just need to check if it is in the semgents.
    //Test if Xi in in Ii. This is the only test we need because we already have an intersection.
    if ( (Xi < max(min(a[0], b[0]), min(P[0], P[2]))) or (Xi > min(max(a[0], b[0]), max(P[0], P[2]))) ){
      //intersection out of bound
      return 0;
    }else{ //intersection found, we have a collision.
      return 1; //We found one collision, that is enouth, we can exit this function.
    }
   return 0;
}

int main(){
   float * a = new float[2];
   float * P = new float[4];

   a[0]= 5;
   a[1]= 5;

   P[0]= 1;
   P[1]= 5.5;
   P[2]= 4.5;
   P[3]= 7;


   cout << Intersect_segment(a, P)<<endl;

   return 0;
}

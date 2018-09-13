#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector> //for Mesh and Front
#include <math.h> //For sqrt(3)



int Intersect_segment(float * a,float * b, float * P){
   if (max(a[0], b[0]) < min(P[0], P[2])){ //Check if this interval exists
     // There is no mutual abscisses => no intersection possible.
     return 0; //This skips the iteration we are on and we get the next segment.
   }
   // We have the two lines formed by the segments :
   //f1(x) = A1*x + b1 = y
   //f2(x) = A2*x + b2 = y
   if ((P[0]-P[2])==0){ //the segment is vertical, we add a small value to a coordinate.
      P[0] = P[0]+(d_rho/100);
   }else if ((a[0]-b[0])==0){
      a[0] = a[0]+(d_rho/100);
   }
   float A1 = (a[1]-b[1])/(a[0]-b[0]);
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

   vector<float *> point_given;
   float * P1 = new float [4];
   P1[0] = 0;
   P1[1] = 0;
   point_given.push_back(P1);
   float * P2 = new float [4];
   P2[0] = 0;
   P2[1] = 1;
   point_given.push_back(P2);
   float * P3 = new float [4];
   P3[0] = 1;
   P3[1] = 1;
   point_given.push_back(P3);
   float * P4 = new float [4];
   P4[0] = 1;
   P4[1] = 0;
   point_given.push_back(P4);
   float * P5 = new float [4];
   P5[0] = 1;
   P5[1] = 0;
   point_given.push_back(P5);

   float * a = new float[2];
   

   int count = 0;
   Ya[0] = -1
   Ya[1] = a[1]; //Ya[0] = xmin
   for(int i=0; i<point_given.size(); ++i){
      if(1 == Intersect_segment(a, Ya, advance.point_given[i])){
         count = count +1;
      }
   }
   cout << "count = " <<count <<endl;
   if ((count%2) == 0){ //a is outside the polygon.
      cout << "outside"<<endl;
   }
}

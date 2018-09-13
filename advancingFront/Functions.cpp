#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector> //for Mesh and Front
#include <math.h> //For sqrt(3)
#include <fstream> //readfile

using namespace std;

#include "Functions.hpp"


AdvancingFront::AdvancingFront(){}
AdvancingFront::~AdvancingFront(){}

/* Discret is used at the initialisation to Discretise the bondaries and obstacles
Input : a density of mesh (rho),the given points, maybe read it on a .txt.
Output : initialisation of Mesh and Front
point_given.size() = number of point in initialisation + 1
*/
int AdvancingFront::Discret(float rho = 0.1){ //Rho = number of points/volume unit
   //***Initialisation***
   //point initialisation :

      //*Reading file to construct point_given, a vector of points.
      string line;
      ifstream myfile("Points.txt");
      float x, y;
      if (myfile.is_open()){
         getline(myfile,line);
         using namespace boost::algorithm;
         vector<string> tokens;
         split(tokens, line, is_any_of(" ")); // here it is
         x = atof(tokens[0].c_str());
         y = atof(tokens[1].c_str());
         float * First_Point = new float[2];
         float * Point_next = new float[2];
         Point_next[0] = x; Point_next[1] = y;
         First_Point[0] = x;
         First_Point[1] = y;
         point_given.push_back(Point_next);
         int k = 0;
         while (getline(myfile,line)){
            if (line == "****"){ //Seperation for obstacles.
               point_given.push_back(Point_next); //Goes back to the first point
               if (getline(myfile,line)){
                  vector<string> tokens;
                  split(tokens, line, is_any_of(" ")); // here it is
                  x = atof(tokens[0].c_str());
                  y = atof(tokens[1].c_str());
                  float * Point_next = new float[2];
                  Point_next[0] = x; Point_next[1] = y;
                  First_Point[0] = x;
                  First_Point[1] = y;
                  point_given.push_back(Point_next);
               }
            }else{
               vector<string> tokens;
               cout <<"line : "<< line <<endl;
               split(tokens, line, is_any_of(" ")); // here it is
               x = atof(tokens[0].c_str());
               y = atof(tokens[1].c_str());
               float * Point_next = new float[2];
               cout << "(esle)x, y ="<<x<<" "<<y<<endl;
               Point_next[0] = x;
               Point_next[1] = y;
               point_given.push_back(Point_next);
            }
         }
         point_given.push_back(First_Point);
      }
      myfile.close();

      for(int i = 0;i < point_given.size();++i){ //DEBUG
         float * P = point_given[i];
         cout<< "P = "<<P[0]<<" "<<P[1]<<endl;
      }
   //***Discretisation***
   //We take point_given(2*number of initial points) and constitue Front with it :
//   float d_rho = 1/sqrt(M_PI*rho);  //DEBUG: defined in .hpp
   float * Start_Point = point_given[0];
   int start = 0;
   for(int i = 0;i < point_given.size()-1;++i){
      if(( point_given[i] == Start_Point)and (i!=start)){ //Cut for if for obstacles.
         Start_Point = point_given[i+1];
         start = i+1;
         continue;
      }

      float * p0 = new float [2];
      float * p1 = new float [2];
      float * seg_Front; //This is the segment
      float x = 0;
      float y = 0;
      //We take the segment [p0,p1], then we discretise it.
      p0 = point_given[i];
      p1 = point_given[i+1];
      float dist = sqrt(pow(p1[0]-p0[0],2)+pow(p1[1]-p0[1],2)); // distance between p0 and p1
      float n = round(dist/d_rho);//We should get the closest int from dist/d_rho and divide the segment into n=round(dist/d_rho) parts.
      for(int j=1; j < n+1 ; ++j){
         seg_Front = new float[4];
         if (j == 1){
            seg_Front[0] = p0[0];
            seg_Front[1] = p0[1];
         }else{
            seg_Front[0] = x; //We create the new segment with the last point we created and the next one.
            seg_Front[1] = y;
         }
         seg_Front[2] = ((1-j/n)*p0[0]+(j/n)*p1[0]);
         seg_Front[3] = ((1-j/n)*p0[1]+(j/n)*p1[1]);
         x = seg_Front[2];
         y = seg_Front[3];
         Front.push_back( seg_Front );
         Mesh.push_back( seg_Front );

      }
   }
return 0;
}







/*
NewPoint is the function that return a new point from a give segment.
I did not take in account the d_rho, that impact the density of the Mesh.
We could add it in the futur.
*/
void AdvancingFront::NewPoint(const float * seg, float ** return_new_point = nullptr){ //= nullptr){
   float * a = new float[2]; //Creation of the new point
   float * b = new float[2];
   float * c = new float[2];
   b[0]= seg[0]; b[1]= seg[1];
   c[0]= seg[2]; c[1]= seg[3];
   //With a rotation matrix, we can obtain :
   a[0] = (c[0]+b[0])*0.5 + (c[1]-b[1])*0.5*sqrt(3);
   a[1] = (b[0]-c[0])*0.5*sqrt(3) + (c[1]+b[1])*0.5;
   float closest_Front = CheckNeighbors(a, rho);// We check if a neighbor is nearby.
   if (closest_Front != -1){ //The new point not is an existing point. We check if there is a collision.
      if (Collision(a, b, c) == 1){ //We have a collision. We don't take our new point and pass to the next segment of the Front.

         a = nullptr;
         //cout << "Collision trouvée"<< endl; //DEBUG
      }else{//No collision; a = existing point
         a[0] = Front[closest_Front][0];
         a[1] = Front[closest_Front][1];
      }
   }

   return_new_point[0] = a; //Given from new points.
   float * return_me_pointer = new float[1];
   return_me_pointer[0] = closest_Front;
   return_new_point[1] = return_me_pointer;

}









/*
CheckNeighbors is used to check if the new point is near from an existing point in the Front.
We want to check if a point is near a. If so, we take this new point, with closest_Front.
*/
float AdvancingFront::CheckNeighbors(float * a, float rho = 0.1){
   float closest_Front = -1 ;//The index of the futur closest front. If closest_Front = -1 : no neighbor was found.
   float r_test = d_rho/1.5; //r_test is the distance from the closest neighbor acceptable.1/2 of d_rho : Imperical value.

   for (int i=0; i<Front.size() ; ++i){ //We browse the Front to find if a point from it is close enouth.
      float * p_Front = Front[i]; //We take a point form the Front. Front is a n*4 so we only consider the first point of each segment.
      float dist_from_a = sqrt(pow(a[0]-p_Front[0],2)+pow(a[1]-p_Front[1],2)); //distance between the Front's point and the created point a.
      if(dist_from_a <r_test){
         closest_Front = i;    //We stock the index of the closest neighbor.
         //cout << ">> We have Neighbors, closest_Front = "<< closest_Front <<endl; //DEBUG
         //cout << "r_test = "<<r_test << endl;
         //cout << "dist_from_a = "<<dist_from_a<< endl;
         r_test = dist_from_a; // By doing this, if we find multiple neighbors to a, we'll get the closest
      }
   }
   return closest_Front; //closest_Front should be an int but some difficulties makes it difficult to keep it as an int.
}





/*
b is the point from the segment from which we generated a. We check if [ab] creates a collision
*/
int AdvancingFront::Collision(float * a, float * b, float * c){
   //float xa = a[0];
   //float ya = a[1];
   int coll_test = 0; //Test if there is a collision. If so, coll_test = 1
   vector<float *> Mesh_copy;
   Mesh_copy = Mesh;
   while(!Mesh_copy.empty()){
      float * P = new float[4];
      P = Mesh_copy.back(); //P is a segment 1*4 [x1, y1, x2, y2]
      Mesh_copy.pop_back();//Remove the last element.
      for (int k = 0; k<2; k++){
         if(k == 1){b = c;}
         if (Intersect_segment(a, b, P) == 1){
            return 1;
         }
      }
   }
   return 0;
}






/*
The function that tells us whether two segments intersect or not. 1 if there is an intersection, 0 if not.
a and b are two points([2*1]) and P is a segment([4*1]).
*/
int AdvancingFront::Intersect_segment(float * a,float * b, float * P){
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


/*
This function round the values indide a segment seg at the n decimal.
It only works with 4*1 segments.
*/
void AdvancingFront::Round(float * seg = nullptr, int n =2){
   int rnd = pow(10,n);
   seg[0] = roundf(seg[0] * rnd) / rnd;
   seg[1] = roundf(seg[1] * rnd) / rnd;
   seg[2] = roundf(seg[2] * rnd) / rnd;
   seg[3] = roundf(seg[3] * rnd) / rnd;

}




/*
We write in ReturnPoints.txt every segments from Mesh form the last added to the first.
*/
void AdvancingFront::WritePoints(){
   ofstream myfile("ReturnPoints.txt"); // /media/sf_Shared/Matlab read point/
//   while(!Mesh.empty()){ //DEBUG
   for(int k = 0; Mesh.size(); ++k){
      float * Point = Mesh.back();
      Mesh.pop_back();
      myfile << Point[0] <<","<< Point[1] << "," << Point[2] <<","<< Point[3]<< "\n";
   }
/*
      if(Mesh.empty()){
         myfile << Point[0] <<","<< Point[1]<< "\n";
      } //DEBUG : should not be useful.
   }*/
   myfile.close();

}

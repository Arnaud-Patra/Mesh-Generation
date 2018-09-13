#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <vector> //for Mesh and Front
#include <math.h> //For sqrt(3)
#include <fstream> //readfile

#include "Functions.hpp"
using namespace std;



int main (){

   //**Initialisation**
   AdvancingFront advance;
   advance.Discret(advance.rho);

   vector<float*> Front_New; //Creation of a the Front that will get in Front went it's empty.

   //Initialisation for the boundaries test.
   float x_min;
   float * Ya = new float[2];
   cout << "advance.point_given.size() = " << advance.point_given.size()<< endl;
   for(int i=0; i<advance.point_given.size(); ++i){ //DEBUG get this outside the loop.
      if (x_min > advance.point_given[i][0]){
         x_min = advance.point_given[i][0];
      }
   }
   cout << "x_min =" << x_min << endl;
   Ya[0] = x_min-1;


   int iteration = 0 ; //DEBUG

   while(!advance.Front.empty()){
//   for(int poop = 0; poop<2000; poop++){ //DEBUG
      iteration = iteration+1;
      if (iteration > 20000){ //DEBUG: avoid infinite loop.
         break;
      }
      //DEBUG
      /*
      cout << "***";
      cout << "mesh size = "<< advance.Mesh.size();
      cout << "; Front size = "<< advance.Front.size()<<endl;
      */
      float * seg = advance.Front.back(); //We consider the segment at the to of the Front
      advance.Front.pop_back();
      float ** return_new_point = new float*[2]; // = nullptr
      advance.NewPoint(seg, return_new_point); //Calling the function to get return_new_point
      float * a = return_new_point[0];
      float * return_me = return_new_point[1];
      float closest_Front = return_me[0];
      if (closest_Front != -1){
         //cout << "Main : closest_Front != -1 ;  "; //DEBUG
      }
      //cout << "Main : closest_Front = " << closest_Front << endl; //DEBUG

      if (advance.Front.size() == 0){
         //cout <<"Front : 'Je suis vide'" << ", iterator = " << iteration <<endl;
         advance.Front = Front_New;
      }

      /*Tests on the new point*/

      /*collision test*/
      if(a==0){ //a creates a collision
         continue;
      }

      /*Creation of a polygon*/
      int start = 0;
      vector<float *> Polygon;
      float * Start_Point = advance.point_given[0];
      for(int i = 0; i< advance.point_given.size()-1; ++i){

         if(( advance.point_given[i] == Start_Point)and (i!=start)){ //Cut for if for obstacles.
            Start_Point = advance.point_given[i+1];
            start = i+1;
            continue;
         }
         float * New_seg = new float[4];
         New_seg[0] = advance.point_given[i][0];
         New_seg[1] = advance.point_given[i][1];
         New_seg[2] = advance.point_given[i+1][0];
         New_seg[3] = advance.point_given[i+1][1];
         Polygon.push_back(New_seg);
      }

      /*Test boundaries: check if the point is inside the boundaries of the map or in an obstacle*/
      int count = 0;
      Ya[1] = a[1]; //Ya[0] = xmin
      for(int i=0; i<Polygon.size(); ++i){
         if(1 == advance.Intersect_segment(a, Ya,Polygon[i] )){
            count = count +1;
         }
      }
      if ((count%2) == 0){ //a is outside the polygon.
         continue;
      }






      //Initialisation of the new edges.
      int n_round = 2; //How many decimals we want for the round function
      float* edge_1 = new float[4];  //creation a the new edges.
      float* edge_2 = new float[4];
      edge_1[0]=seg[0] ;edge_1[1]=seg[1] ;edge_1[2]=a[0] ;edge_1[3]=a[1];
      edge_2[0]=a[0] ;edge_2[1]=a[1] ;edge_2[2]=seg[2] ;edge_2[3]=seg[3];// The edge closer to the end of the Front.
      float* edge_1_copy = new float[4];  //creation identical edges for the tests.
      float* edge_2_copy = new float[4];
      edge_1_copy[0]=edge_1[0] ;edge_1_copy[1]=edge_1[1] ;edge_1_copy[2]=edge_1[2] ;edge_1_copy[3]=edge_1[3];
      edge_2_copy[0]=edge_2[0] ;edge_2_copy[1]=edge_2[1] ;edge_2_copy[2]=edge_2[2] ;edge_2_copy[3]=edge_2[3];
      advance.Round(edge_1_copy,n_round);//We use round to tet if segments are the same. Otherwise we have rounding errors.
      advance.Round(edge_2_copy,n_round);
      //Test in case of edge fusion
   //   if (closest_Front != -1){ //The new point a is actually an existing point.
         //edge_2 or edge_1 might exist, we need to check it. 4 situations exist here
         int is_edge_1 = 0; //int that will indicate wether edge_1 is in front or not. 0 = no
         int is_edge_2 = 0;
         for (int i=0; i<(-1+advance.Mesh.size()); ++i){
            float * mesh_edge = new float[4];
            mesh_edge[0] = advance.Mesh[i][0];mesh_edge[1] = advance.Mesh[i][1];mesh_edge[2] = advance.Mesh[i][2];mesh_edge[3] = advance.Mesh[i][3];
            advance.Round(mesh_edge,n_round); //We round it the same way as the edges

            if( ((edge_1_copy[0]==mesh_edge[0])and(edge_1_copy[1]==mesh_edge[1])and(edge_1_copy[2]==mesh_edge[2])and(edge_1_copy[3] == mesh_edge[3]))
             or ((edge_1_copy[0]==mesh_edge[2])and(edge_1_copy[1]==mesh_edge[3])and(edge_1_copy[2]==mesh_edge[0])and(edge_1_copy[3] == mesh_edge[1])) ){//we test if edge_1 is in mesh (and only in mesh).
               //Should we remove mesh[i] too?
               is_edge_1 = 1; //Yes
            }else if(((edge_2_copy[0]==mesh_edge[0])and(edge_2_copy[1]==mesh_edge[1])and(edge_2_copy[2]==mesh_edge[2])and(edge_2_copy[3] == mesh_edge[3]))
            or ((edge_2_copy[0]==mesh_edge[2])and(edge_2_copy[1]==mesh_edge[3])and(edge_2_copy[2]==mesh_edge[0])and(edge_2_copy[3] == mesh_edge[1]))){//we test if edge_2 is in mesh
               is_edge_2 = 1;
            }
         }
         if ((is_edge_1 == 1) and (is_edge_2 == 1)){ //Both in :
            //They should already be in Mesh, we do nothing.

         }else if((is_edge_1 == 0) and (is_edge_2 == 0)){//Both out : we had both of them
            Front_New.push_back(edge_1);
            advance.Mesh.push_back(edge_1);
            Front_New.push_back(edge_2);
            advance.Mesh.push_back(edge_2);
         }else if((is_edge_1 == 1) and (is_edge_2 == 0)){//edge_1 in.
            //This case and the next one can be problematic because Front[i] is still "in" Front but it won't create a new point. Collision() should resolve this.
            Front_New.push_back(edge_2);
            advance.Mesh.push_back(edge_2);
         }else if((is_edge_1 == 0) and (is_edge_2 == 1)){//edge_2 in.
            Front_New.push_back(edge_1);
            advance.Mesh.push_back(edge_1);//At what moment do we pop Front?
   //      }

      }else { //a is a totaly new point, we add the 2 new edges.

         //DEBUG
         //cout<<"edge_1 ="<<edge_1[0]<<" "<<edge_1[1]<<" "<<edge_1[2]<<" "<<edge_1[3]<<endl;
         //cout<<"edge_2 ="<<edge_2[0]<<" "<<edge_2[1]<<" "<<edge_2[2]<<" "<<edge_2[3]<<endl;

         Front_New.push_back(edge_1); //The order is important here : edge_2 is closer to the end.
         Front_New.push_back(edge_2);
         advance.Mesh.push_back(edge_1);
         advance.Mesh.push_back(edge_2);
         //continue;//DEBUG : what?
      }



   }//End of the for loop

   advance.WritePoints();

return 0;
}

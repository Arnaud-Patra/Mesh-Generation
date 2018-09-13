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

   int iteration = 0 ; //DEBUG

   while(!advance.Front.empty()){
//   for(int poop = 0; poop<2000; poop++){ //DEBUG
      iteration = iteration+1;
      if (iteration > 16000){ //DEBUG

         break;
      }
      //DEBUG
      //cout << ">> Nouvelle boucle For"<< endl;
/*
      cout << "*           *"<<endl;
      cout << "mesh size = "<< advance.Mesh.size()<<endl;
      cout << "Front size = "<< advance.Front.size()<<endl;
      cout << "Front_New size = "<< Front_New.size()<<endl;
*/
      float * seg = advance.Front.back(); //We consider the segment at the to of the Front
      advance.Front.pop_back();
      float ** return_new_point= new float*[2]; // = nullptr
      advance.NewPoint(seg, return_new_point); //Calling the function to get return_new_point
      float * a = return_new_point[0];
      float * return_me = return_new_point[1];
      float closest_Front = return_me[0];
      cout << "Main : closest_Front = " << closest_Front << endl; //DEBUG
      if (advance.Front.size() == 0){
         cout <<"Front : 'Je suis vide'" << ", iterator = " << iteration <<endl;
         advance.Front = Front_New;
      }
      /*
      //Tests on the new point
      if(a!=0){//No collision
         // cout << "a = "<<a[0] << " "<<a[1]<<endl;//DEBUG : this creates a bug if a = nullptr
         if((a[0]<0) or (a[0]>10) or(a[1]<0) or (a[1]>10)){ //Checking the bounds //DEBUG : only wo
            //cout << " a out of bounds"<<endl; //DEBUG
            continue; //DEBUG : does it works well?
         }
      }else{//Our new point creates a collision, we continue to check the next segment of the Front.
         //cout << "!> collision trouvée"<<endl; //DEBUG
         continue;
      }*/

      //collision test
/*
      if(a==nullptr){ //a creates a collision
         cout << "a = nullptr"<<endl;
         continue;
      }*/
      //boundaries test //DEBUG
      if((a[0]<0)or(a[0]>10)or(a[1]<0)or(a[1]>10)){
         continue;
      }
      //DEBUG : this seems like a temporary solution
      int test_count = 0;
      for(int k = 0; k<advance.Mesh.size(); ++k){
         float * Point_mesh  = advance.Mesh[k];
         if ((a[0] == Point_mesh[0])and(a[1]==Point_mesh[1])){
            test_count = test_count +1;
         }
      }
      if (test_count >3){ //a can only be part of 1 hexagon at most.
         continue;
      }
      //Test inside polygon
      int count = 0;
      float * Ya = new float[2];
      Ya[0] = 0; //DEBUG : might cause a problem is the figure goes x <0.
      Ya[1] = a[1];
      for(int i=0; i<advance.Front.size();++i){
         if(1 == advance.Intersect_segment(a,Ya,advance.Front[i])){
            count = count +1;
         }
      }
      /*
      if ( (count != 0) and (count%2) == 0){ //a is outside the polygon.
         //cout << "!>> a outside the polygon" << endl; //DEBUG
         continue;
      }*/

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
      if (closest_Front != -1){ //The new point a is actually an existing point.
         //edge_2 or edge_1 might exist, we need to check it. 4 situations exist here
         int is_edge_1 = 0; //int that will indicate wether edge_1 is in front or not. 0 = no
         int is_edge_2 = 0;
         cout << "closest_Front !=-1 "<< endl;//DEBUG
         for (int i=0; i<(-1+advance.Front.size()); ++i){
            float * Front_edge = new float[4];
            Front_edge[0] = advance.Front[i][0];Front_edge[1] = advance.Front[i][1];Front_edge[2] = advance.Front[i][2];Front_edge[3] = advance.Front[i][3];
            //cout << "Front_edge = "<< Front_edge[0] <<" "<< Front_edge[1] <<" "<<Front_edge[2] << " " <<Front_edge[2] <<endl; //DEBUG
            advance.Round(Front_edge,n_round); //We round it the same way as the edges
            //cout << "Front_edge rounded = "<< Front_edge[0] <<" "<< Front_edge[1] <<" "<<Front_edge[2] << " " <<Front_edge[2] <<endl; //DEBUF

            if(((edge_1_copy[0]==Front_edge[0])and(edge_1_copy[1]==Front_edge[1])and(edge_1_copy[2]==Front_edge[2])and(edge_1_copy[3] == Front_edge[3])) or ((edge_1_copy[0]==Front_edge[2])and(edge_1_copy[1]==Front_edge[3])and(edge_1_copy[2]==Front_edge[0])and(edge_1_copy[3] == Front_edge[1]))){//we test if edge_1 is in Front (and only in Front).
               //Should we remove Front[i] too?
               cout <<"JE SUIS DANS LE IF ! "<< endl; //DEBUG
               is_edge_1 = 1; //Yes
            }else if(((edge_2_copy[0]==Front_edge[0])and(edge_2_copy[1]==Front_edge[1])and(edge_2_copy[2]==Front_edge[2])and(edge_2_copy[3] == Front_edge[3])) or ((edge_2_copy[0]==Front_edge[2])and(edge_2_copy[1]==Front_edge[3])and(edge_2_copy[2]==Front_edge[0])and(edge_2_copy[3] == Front_edge[1]))){//we test if edge_2 is in Front
               cout <<"JE SUIS DANS LE IF ! "<< endl; //DEBUG
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
         }

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

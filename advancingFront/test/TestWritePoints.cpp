#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <fstream>

#include <vector>

using namespace std;

int main(){
   //For the test :
   float * P0 = new float[4];
   float * P1 = new float[4];
   P0[0] = 1.9;//(1.9,2,0,0)
   P0[1] = 2;
   P0[2] = 0;
   P0[3] = 0;
   P1[0] = 0; //(0,0 ,1.2,1.3)
   P1[1] = 0;
   P1[2] = 1.2;
   P1[3] = 1.3;
   vector<float *> Mesh;
   Mesh.push_back(P0);
   Mesh.push_back(P1);


   ofstream myfile("ReturnPoints.txt");
   while(!Mesh.empty()){
      float *Point = Mesh.back();
      Mesh.pop_back();
      myfile << Point[0] <<","<< Point[1] << "," << Point[2] <<","<< Point[3]<< "\n";

   }


   myfile.close();
   return  0;
}

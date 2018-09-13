#include <iostream>
#include <ctime>
#include <cstdlib>
#include <string>
#include <stack> //for Front
#include <vector> //for Mesh
#include <math.h> //For sqrt(3)
#include <fstream> //readfile

using namespace std;


int main(){
   float a = -1;
   while (a<10){
      a=a +1;
      cout << "a = " << a << endl;
      if (a == 3){
         continue;
      }
      cout << "a != 3" << endl;

   }


   return 0;
}

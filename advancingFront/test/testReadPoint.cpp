#include <iostream>
#include <istream>
#include <ctime>
#include <cstdlib>
#include <string>


//#include <cstdlib>
#include <fstream> //readfile
#include <vector> //for mesh

#include <boost/algorithm/string/split.hpp>
#include <boost/algorithm/string/classification.hpp>

//#include <stdio>
//#include<sstream>
using namespace std;


int main(){

   vector<float *> point_given;
   string line;
   ifstream myfile("Points.txt");
   float x, y;
   if (myfile.is_open()){
      while (getline(myfile,line)){
         using namespace boost::algorithm;
         vector<string> tokens;
         split(tokens, line, is_any_of(" ")); // here it is
         x = atof(tokens[0].c_str());
         y = atof(tokens[1].c_str());
         cout <<x << " " << y << endl;
         float * Point_next = new float[2];
         Point_next[0] = x;
         Point_next[1] = y;
         point_given.push_back(Point_next);
      }
      cout << "coucou" <<endl;
      myfile.close();
   }

/*
{
  std::string orbits ("686.97 365.24");
  std::string::size_type sz;     // alias of size_t

  float mars = std::stof (orbits,&sz);
  float earth = std::stof (orbits.substr(sz));
  std::cout << "One martian year takes " << (mars/earth) << " Earth years.\n";
  return 0;
}
*/


cout << point_given.size()<< endl;
   for(int k = 0; k<point_given.size(); k++){

      float * testRead = point_given[k];
      cout << testRead[0] << "  " << testRead[1] <<endl; //x
  //y
   }

return 0;
}

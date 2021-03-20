#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Eigen/Core>
#include "json_struct.h"
#include "json.hpp"
#include <cassert>


using json = nlohmann::json;


int get_dayoftheweek(int y, int m, int d){
//0 on sunday, 6 on saturday
  return (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;

}

int get_dayoftheyear(int m, int d){
  int doy = 0;
  for(int i = 1; i < m; i++){
    if(i == 1 ||i == 3||i == 5||i == 7||i == 8||i == 10||i==12) doy += 31 ;
    else if(i == 2) doy += 28;
    else if(i == 4|| i == 6||i==9||i==11) doy += 30;
  }
  doy += d;
  return doy-1;
}

void get_index(const json& weather_data, const std::string& string, unsigned& index1, unsigned& index2){

  std::string year = string.substr(0, 4);
  std::string month = string.substr(5,2);
  std::string day = string.substr(8,2);
  std::string hour = string.substr(11,2);

  int y = std::stoi(year);
  int m = std::stoi(month);
  int d = std::stoi(day);
  int h = std::stoi(hour);

  std::cout<<"Day of the week: "<<get_dayoftheweek(y,m,d)<<"\n";
  index1 = get_dayoftheweek(y,m,d)* 24 + h;

  double precipitation = weather_data[get_dayoftheyear(m, d)*24 + h].value("precipMM",1.0);
  index2 = (bool) precipitation;
}


int main(int argc, char const *argv[]) {

  json data, weather_data;

  std::string path = "/home/ryan/starthack/data";
  std::string file_name1 = "data";
  std::string file_name2 = "weather";

  std::ifstream file(path + "/" + file_name1 + ".json");
  file >> data;
  std::ifstream file2(path + "/" + file_name2 + ".json");
  file2 >> weather_data;

  /*
  std::string x = data[2].value("start","oops");
  unsigned int ind1, ind2;
  get_index(weather_data, x,ind1, ind2);
  std::cout<<ind1<<" "<<ind2<<std::endl;
  */

  int occ [168][2];

  for(unsigned rat = 0;rat < 19521; rat++){
    std::string xstart = data[rat].value("start","oops");
    std::string xend = data[rat].value("end","oops");
    //
    unsigned int ind1, ind2;
    std::cout<< xstart<<"\n";
    //std::cout<<rat<<"\n";
    get_index(weather_data, xstart,ind1, ind2);
    std::cout<< ind1<<"  "<<ind2<<"\n";

    occ[ind1][ind2] += 1;
    //
  }



  return 0;
}

#include <string>
#include <iostream>
#include <fstream>
#include <sstream>
#include <Eigen/Core>
#include <Eigen/Dense>
#include "json_struct.h"
#include "json.hpp"
#include <cassert>

using json = nlohmann::json;

int get_dayoftheweek(int y, int m, int d){
//0 on sunday, 6 on saturday
  return (d += m < 3 ? y-- : y - 2, 23*m/9 + d + 4 + y/4- y/100 + y/400)%7;
}

int daysofmonth(int month){
  if(month == 1 ||month== 3||month== 5||month== 7||month == 8||month == 10||month==12) return 31 ;
  else if(month == 2) return 28;
  else if(month == 4|| month == 6||month ==9||month==11) return 30;
  else return 0;
}

int get_dayoftheyear(int m, int d){
  int doy = 0;
  for(int i = 1; i < m; i++){
    doy += daysofmonth(i);
  }
  doy += d;
  return doy-1;
}

void get_index(const json& weather_data,  int y,  int m,  int d,  int h, unsigned& index1, unsigned& index2){
  index1 = get_dayoftheweek(y,m,d)* 24 + h;

  double precipitation = weather_data[get_dayoftheyear(m, d)*24 + h].value("precipMM",1.0);
  index2 = (bool) precipitation;
}

void get_occupancy(json& data, json& weather_data, int(&occ)[168][2]){
  for(unsigned rat = 0;rat < 19521; rat++){
    std::string xstart = data[rat].value("start","oops");
    std::string xend = data[rat].value("end","oops");

    std::string syear = xstart.substr(0, 4);
    std::string smonth = xstart.substr(5,2);
    std::string sday = xstart.substr(8,2);
    std::string shour = xstart.substr(11,2);

    int sy = std::stoi(syear);
    int sm = std::stoi(smonth);
    int sd = std::stoi(sday);
    int sh = std::stoi(shour);

    std::string eyear = xend.substr(0, 4);
    std::string emonth = xend.substr(5,2);
    std::string eday = xend.substr(8,2);
    std::string ehour = xend.substr(11,2);

    int ey = std::stoi(eyear);
    int em = std::stoi(emonth);
    int ed = std::stoi(eday);
    int eh = std::stoi(ehour);


    while(sh <= eh || sd <= ed|| sm <= em){

      unsigned int ind1, ind2;

      get_index(weather_data, sy, sm, sd, sh, ind1, ind2);
      //std::cout <<"sy,sm,sd,sh: "<<sy<<" "<<sm<<" "<<sd<<" "<<sh<<"\n";
      occ[ind1][ind2] += 1;

      if(sh == 23 && sd < ed && sm == em || sh == 23 && sm < em && sd < daysofmonth(sm)){
        sh = 0;
        sd++;
      }else if (sh == 23 && sd == daysofmonth(sm)&& sm <em){
        sh = 0;
        sd = 1;
        sm++;
      }else if (sh > eh && sd == ed && sm == em)
        break;
      else if(sh == eh && sd == ed && sm == em) break;
      else sh++;
    }
  }
}
void get_weather_occurrence(json& weather_data, int(&avg)[168][2]){
  int size = weather_data.size();

  for(int i=0; i < size; i++){
    std::string date = weather_data[i].value("date","oops");
    int hour = i%24;
    double precipitation = weather_data[i].value("precipMM",1.0);

    std::string year = date.substr(0, 4);
    std::string month = date.substr(5,2);
    std::string day = date.substr(8,2);

    int y = std::stoi(year);
    int m = std::stoi(month);
    int d = std::stoi(day);

    int index1 = get_dayoftheweek(y,m,d)* 24 + hour;
    int index2 = (bool)precipitation;
    avg[index1][index2]++;
  }
}

void solve(double occd[][2], Eigen::VectorXd& beta){
  Eigen::MatrixXd x(336,6);
  Eigen::VectorXd y(336);
  for(int i = 0; i < 336; i++){
    y(i) = occd[i/2][i%2];
    x(i,5) = i%2;
  }
  x.block<336,1>(0,0).setOnes();
  x.block<168,1>(0,1) = Eigen::VectorXd::LinSpaced(168,0,168);
  x.block<168,1>(168,1) = Eigen::VectorXd::LinSpaced(168,0,168);
  Eigen::VectorXd help = x.block<336,1>(0,1);
  for(int i = 0; i < 336; i++){
    int help = x(i,1);
    x(i,2) = help*help;
    x(i,3) = help*help*help;
    x(i,4) = help*x(i,3);
  }
  for(int i=0;i<336;i++){
    for(int j=0;j<6;j++){
      std::cout<<x(i,j)<<std::endl;
    }
    std::cout<<std::endl;
  }
  Eigen::MatrixXd xtx(6,6);
  xtx = x.transpose()*x;
  beta = xtx.inverse()*(x.transpose()*y);
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


   int occ [168][2];
   double occd[168][2];

  for(int i = 0; i< 168; i++){
    for(int j = 0; j < 2; j++)
      occ[i][j]=0;
  }

  get_occupancy(data, weather_data, occ);

  ////////////////////////AVERAGING OVER OCCURRENCES/////////////////////////////////////
  int avg[168][2];

  for(int i = 0; i< 168; i++){
    for(int j = 0; j < 2; j++){
      occd[i][j] = occ[i][j];
      avg[i][j] = 0;
    }
  }
  get_weather_occurrence(weather_data, avg);

  for(int i = 0; i< 168; i++){
    for(int j = 0; j < 2; j++){
      occd[i][j] /= avg[i][j];
    }
  }


  ///////////////////////////FINDING WEIGHTS//////////////////////////////////
  Eigen::VectorXd beta(6);
  solve(occd, beta);
  for(int j = 0; j < 6; j++)
    std::cout<<beta[j]<<" ";

  return 0;
}

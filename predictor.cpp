#include <string>
#include <iostream>

double weights[6] = {58.212, -1.74869, 0.0514098, -0.000439267, 1.15227e-06, 2.88893};

int main(int argc, char const *argv[]) {
  double estimate = 0;
  int day;
  int hour;
  int rain;

  std::cout << "Input day: ";
  std::cin >> day;
  std::cout << std::endl;
  std::cout << "Input hour of day: ";
  std::cin >> hour;
  std::cout << std::endl;
  std::cout << "Input 1 for rain and 0 for none: ";
  std::cin >> rain;
  std::cout<<std::endl;

  double weekhour = 24 * day + hour;

  estimate = weights[0] +
             (weights[1]*weekhour) +
             (weights[2]*weekhour*weekhour) +
             (weights[3]*weekhour*weekhour*weekhour) +
             (weights[4]*weekhour*weekhour*weekhour*weekhour) +
             (weights[5]*rain);
  std::cout<<"estimated # cars out of 280: " << estimate << std::endl;
  return 0;
}

#include <Eigen/Dense>
int main(int argc, char const *argv[]) {
  /* code */
  return 0;
}

struct data_entry{
  std::String start;
  std::String end;
};

struct weather_data{
  std::String date;
  int time;
  double precip;
};

struct parking {
private:
  unsigned int nparam = 2;
  int occ [24*7][2];

  unsigned int degree = 3;
  Eigen::VectorXd<int> Y (7*24*2);
  Eigen::MatrixXd<int> X (7*24*2, nparam * degree);

  Eigen::VectorXd<double> beta (nparam * degree);

public:
  void get_data();
  void fill_occ(){
    //////1. read entry from entry vector
    //////2. read entry from weather_data
    //////3. add one to corresponding positions in occ[times][weather]
  }

  void calculate_parameters(){
    //LU_solver solve for beta whatever...
  }
}

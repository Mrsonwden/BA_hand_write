#ifndef BA_TEST_H__
#define BA_TEST_H__

#include <Eigen/Core>
#include <Eigen/Dense>

#include <vector>
using namespace std;
using namespace Eigen;

void say_hello();

void generate_data(int nums, double para_a, double para_b, double para_c, double para_d , vector<double> &data_x, vector<double> &data_y);
double formular(double para_a, double para_b, double para_c, double para_d , double x);
Vector4d computer_J(double para_a, double para_b, double para_c, double para_d , double x);
double computer_acc_error_H_b(vector<double> & data_x, vector<double> & data_y,double para_a, double para_b, double para_c, double para_d, Matrix4d  &H, Vector4d &b );



#endif

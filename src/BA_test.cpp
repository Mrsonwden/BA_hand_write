#include <iostream>
#include <vector>
#include <Eigen/Core>
#include <Eigen/Dense>
#include <opencv2/core/core.hpp>
#include "BA_test.h"

using namespace std;
using namespace Eigen;

void say_hello()
{
    cout << "hello! the new slam  world" << endl;
}

//生成 含有高斯噪声的 曲线数据，用于模拟实际采集到的数据；
void generate_data(int nums, double para_a, double para_b, double para_c, double para_d , vector<double> &data_x, vector<double> &data_y)
{
           double sigma = 1.0;
           cv::RNG rng;
            double y = 0;
            double x = 0;
            for(int  i = 1; i <= nums; i++)
            {
                x = i/(double)nums;
                data_x.push_back(x);
                y = formular(para_a,para_b,para_c,para_d ,x);
                y = y + rng.gaussian(sigma);
                data_y.push_back(y);

                // cout << "raw _x : " << x << " raw_y : " <<  exp(para_a * x * x * x + para_b * x * x + para_c * x + para_d)    << "            ||            gs_x : " << x << " gs_y : " <<  y << endl;  
            }            
}

double formular(double para_a, double para_b, double para_c, double para_d , double x)
{
     return exp(para_a * x * x * x + para_b * x * x + para_c * x + para_d);
}

double computer_acc_error_H_b(vector<double> & data_x, vector<double> & data_y,double para_a, double para_b, double para_c, double para_d, Matrix4d  &H, Vector4d &b )
{
    double acc_error = 0; 
    double residual_error = 0;
    for(int i = 0; i < data_x.size(); i++)
    {
        residual_error = data_y[i] - formular(para_a,para_b,para_c,para_d,data_x[i]);  // 计算误差；
        Vector4d jacobi =  computer_J(para_a,para_b,para_c,para_d,data_x[i])  ;  // 计算雅各比；
        H = H + jacobi * jacobi.transpose();
        b = b - residual_error * jacobi;
        acc_error += residual_error * residual_error;
        
    }
    return acc_error;
}

Vector4d computer_J(double para_a, double para_b, double para_c, double para_d , double x)
{
    Vector4d Jacobi;
    Jacobi[0] = -(x*x*x) * exp( para_a * x*x*x + para_b * x *x + para_c * x + para_d);
    Jacobi[1] = -(x*x) * exp( para_a * x*x*x + para_b * x *x + para_c * x + para_d);
    Jacobi[2] = -(x) * exp( para_a * x*x*x + para_b * x *x + para_c * x + para_d);
    Jacobi[3] = -exp( para_a * x*x*x + para_b * x *x + para_c * x + para_d);
    return Jacobi;
} 


#include <iostream>
#include <vector>
#include "BA_test.h"

using namespace std;	


int main()
{
// step1 生成伪数据；
	int total_data = 10000;
	double a_t = 5;
	double b_t = 1;
	double c_t = 1;
	double d_t = 1;
	vector<double> data_x;
	vector<double> data_y;
	 generate_data(total_data, a_t, b_t, c_t, d_t , data_x, data_y);
//step2 设定ae,be,ce,de 的初值；
	double a_e = 3;
	double b_e = 10;
	double c_e  =1;
	double d_e = 1;
//step3 构建最小二乘法；
	int iterator_times = 2000;
	double threshold = 0.005;   // 
	double last_acc_error = 100000;
	double curr_acc_error = 0;
	int continue_success_time = 0;

	for(int i  = 0; i < iterator_times; i++)
	{
		Matrix4d H = Matrix4d::Zero();
		Vector4d b = Vector4d::Zero();
		Vector4d dx = Vector4d::Zero();

		if(continue_success_time >= 5)
		{
			break;
		}
		curr_acc_error = computer_acc_error_H_b(data_x,data_y,a_e,b_e,c_e, d_e ,H,b);
		if((  last_acc_error - curr_acc_error  < last_acc_error * threshold )   && (curr_acc_error < total_data * 0.01))
		{
			cout << "last_acc_error - curr_acc_error  < threshold " << "        last_acc_error: " << last_acc_error << "        curr_acc_error:  " << curr_acc_error << endl;
			break;
		}
		if( (last_acc_error == curr_acc_error) && (continue_success_time < 5) )
		{
			continue_success_time++;
			cout << " come in the min point" << endl;
			continue;
		}
		continue_success_time = 0;
		//step5 构建增量方程；
		dx = H.ldlt().solve(b);

		//step6 检验并修改增量；
		if(isnan(dx[0]))
		{
			cout << " dx is nan ****************************************************************************************************************************************************************" << endl;
			break;
		}
		a_e += dx[0];
		b_e += dx[1];
		c_e += dx[2];
		d_e += dx[3];

		last_acc_error = curr_acc_error;

		cout << " iterator : " << i << "    acc error : " << curr_acc_error <<  "     a :  " << a_e << "   b: " << b_e << "  c:   " << c_e << "   d:  " << d_e << endl;
	}
	cout << " estimate " <<  "     a :  " << a_e << "   b: " << b_e << "  c:   " << c_e << "   d:  " << d_e << endl;
	cout << " true " <<  "     a :  " << a_t << "   b: " << b_t << "  c:   " << c_t << "   d:  " << d_t << endl;
 
}

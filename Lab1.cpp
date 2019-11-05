// NumAnalysisLab1.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
#define _USE_MATH_DEFINES
#include<math.h>
double cos_func(double res,double elem ,int*k,double x,double eps,double*Remainder_term) {
	elem = -x * x * elem / ((2.0 * (*k)) * (2.0 * (*k) - 1));
	res += elem;
	(*k)++;
	double next_elem = -x * x * elem / ((2.0 * (*k)) * (2.0 * (*k) - 1));
	if (abs(next_elem) < eps) {
		*Remainder_term = abs(next_elem);
		return res;
	}
	return cos_func(res,elem,k,x,eps,Remainder_term);
}
double cos_func(double res,double elem, int k, int n, double x, double* Remainder_term) {
	elem = -x * x * elem / ((2.0 * k) * (2.0 * k - 1));
	if (k == n) {
		*Remainder_term = abs(elem);
		return res;
	}
	res += elem;
	k++;
	return cos_func(res, elem,k, n, x,Remainder_term);
}
double first_table_create(double a, double b) {
	cout << "\t\t\t\t\tTable #1" << endl;
	cout << "--------------------------------------------------------------------------------------------------------" << endl;
	cout << "|\t  eps     \t|\tn    \t|          Absolute error\t|          Remainder term\t|" << endl;
	cout << "--------------------------------------------------------------------------------------------------------" << endl;
	double second_task_n;
	double x = fmod((a + b) / 2, 2*M_PI);
	for (double i = 1e-2; i >= 1e-14; i*=1e-3) {
		double Remainder_term = 0;
		int n = 1;
		double absolute_error = abs(abs(cos(x)) - abs(cos_func(1, 1,&n, x,i,&Remainder_term)));
		if (i == 1e-8) {
			second_task_n = n;
		}
		printf("|\t %.2e\t|\t%d\t|\t    %.2e\t\t|\t    %.2e\t\t|\n", i, n, absolute_error, Remainder_term);
		printf("--------------------------------------------------------------------------------------------------------\n");
	}
	return second_task_n;
}
void second_table_create(double a, double b, int n) {
	cout << "\t\t\t\t	   Table #2" << endl;
	cout << "------------------------------------------------------------------------------------------------" << endl;
	cout << "|\t       Xi  \t\t|\t  Absolute error  \t|        Remainder term\t\t|" << endl;
	cout << "------------------------------------------------------------------------------------------------" << endl;
	for (int i = 0; i < 10; i++) {
		double x = a + i * (b - a) / 10;
		double Remainder_term;
		double absolute_error = abs(abs(cos(fmod(x,2*M_PI))) - abs(cos_func(1,1,1, n, fmod(x,2*M_PI) , &Remainder_term)));
		printf("|\t    %.2lf\t\t|\t    %.3e\t\t|\t  %.3e\t\t|\n", x, absolute_error, Remainder_term);
		printf("-------------------------------------------------------------------------------------------------\n");
	}
}
int main()
{
	double a = -30.3;
	double b = 7.4;
	int second_task_n = first_table_create(a,b);
	second_table_create(a, b, second_task_n);
	
	system("pause");
}



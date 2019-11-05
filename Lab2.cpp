// Lab2AMO.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;
#include<cmath>
double* create_array_with_necessary_parts(int*number_of_parts,double a,double b) {
	double*array_with_necessary_parts = new double[3];

	*number_of_parts = 0;

	for(double i = a;i < b;i += 0.05){
		if ((sin(i * i) - 0.5 * i + 0.5)*(sin((i + 0.05) * (i + 0.05)) - 0.5 * (i + 0.05) + 0.5) < 0){

			array_with_necessary_parts[*number_of_parts] = i;
			(*number_of_parts)++;

		}
	}

	return array_with_necessary_parts;
}

double iteration_method(double a,double b,double lmbd,double q,double eps,double*accuracy,int& iterations,int maxit,bool& done) {
	double x1 = (a + b) / 2;

	double x0;

	iterations = 0;

	do {

		x0 = x1;
		x1 = x0- lmbd*(sin(x0*x0) - 0.5 * x0 + 0.5);
		iterations++;

	} while ((abs(x1 - x0) > (1 - q)*eps / q) && (iterations < maxit));
	
	if (iterations < maxit) {
		done = true;
	}
	else {
		done = false;
		cout << "Specified approximation wasn't reached" << endl;
	}

	*accuracy = abs((q / (1 - q)) * (x1 - x0));

	return x1;
}

void iteration_method_table(double*array_with_necessary_parts,int num_of_parts) {
	cout << "\t\t\t\tIteration Method" << endl;
	cout << "---------------------------------------------------------------------------------------------------------" << endl;
	cout << "|\t  Eps     \t\t|           Root\t\t\t|          Accuracy\t\t|" << endl;
	cout << "---------------------------------------------------------------------------------------------------------" << endl;

	for (int array_count = 0; array_count < num_of_parts; array_count++) {
		for (double eps = 1e-2; eps >= 1e-11; eps *= 1e-3) {

			double accuracy = 0;

			double lmbd;

			double q;

			double a = array_with_necessary_parts[array_count];

			double b = array_with_necessary_parts[array_count] + 0.05;

			if (abs(2 * a * cos(a * a) - 0.5) > abs(2 * b * cos(b * b) - 0.5)) {
				lmbd = 1/(2 * a * cos(a * a) - 0.5);
				q =1 - abs((2 * b * cos(b * b) - 0.5)/(2 * a * cos(a * a) - 0.5));
			}
			else {
				lmbd = 1 /(2 * b * cos(b * b) - 0.5);
				q = 1 - abs((2 * a * cos(a * a) - 0.5) / (2 * b * cos(b * b) - 0.5));
			}

			int iterations;

			bool done;

			double root = iteration_method(a, b, lmbd, q, eps, &accuracy,iterations,150,done);

			printf("|\t    %.1e\t\t|\t    %.7e\t\t|\t  %.7e\t\t|\n", eps, root, accuracy);

			printf("--------------------------------------------------------------------------------------------------------\n");
		}
	}
}
double bisection_method(double a, double b, double eps,double *accuracy,int& iterations,int maxit,bool& done) {
	iterations = 0;
	do {
		double half = (b - a) / 2;

		if (((sin(a * a) - 0.5 * a + 0.5)*(sin((a + half) * (a + half)) - 0.5 * (a + half) + 0.5)) < 0) {
			b = a + half;
		}
		else {
			a = a + half;
		}

		iterations++;

	} while (((b - a) >= 2 * eps) && (iterations<maxit));

	if (iterations < maxit)
		done = true;
	else {
		done = false;
		cout << "Specified approximation wasn't reached" << endl;
	}

	*accuracy = (b - a) / 2;

	return (a + b) / 2;
}
void bisection_method_table(double* array_with_necessary_parts, int num_of_parts) {
	cout << "\t\t\t\tBisection Method" << endl;
	cout << "---------------------------------------------------------------------------------------------------------" << endl;
	cout << "|\t  Eps     \t\t|           Root\t\t\t|          Accuracy\t\t|" << endl;
	cout << "---------------------------------------------------------------------------------------------------------" << endl;
	for (int array_count = 0; array_count < num_of_parts; array_count++) {
		for (double eps = 1e-2; eps >= 1e-11; eps *= 1e-3) {

			int iterations;
			
			bool done;

			double a = array_with_necessary_parts[array_count];

			double b = array_with_necessary_parts[array_count] + 0.05;

			double accuracy;

			double root = bisection_method(a, b, eps, &accuracy,iterations, 150, done);

			printf("|\t    %.1e\t\t|\t    %.7e\t\t|\t  %.7e\t\t|\n", eps, root,accuracy);

			printf("--------------------------------------------------------------------------------------------------------\n");
		}
	}
}

void comparing_table(double necessary_part) {
	cout << "\t\t\t\t\tComparing Table" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;
	cout << "|\t     Eps  \t\t|        Iteration Method\t|      Bisection Method\t\t|" << endl;
	cout << "-------------------------------------------------------------------------------------------------" << endl;

	double lmbd;

	double q;

	double a = necessary_part;

	double b = necessary_part + 0.05;
	
	if (abs(2 * a * cos(a * a) - 0.5) > abs(2 * b * cos(b * b) - 0.5)) {
		lmbd = 1 / (2 * a * cos(a * a) - 0.5);
		q = 1 - abs((2 * b * cos(b * b) - 0.5) / (2 * a * cos(a * a) - 0.5));
	}
	else {
		lmbd = 1 / (2 * b * cos(b * b) - 0.5);
		q = 1 - abs((2 * a * cos(a * a) - 0.5) / (2 * b * cos(b * b) - 0.5));
	}

	double accuracy;

	int number_of_iterations_IM;

	bool done;

	int number_of_iterations_BM;


	for (double eps = 1e-2; eps >= 1e-11; eps *= 1e-3) {
		
		iteration_method(a, b, lmbd, q, eps,&accuracy,number_of_iterations_IM,150,done);
		
		bisection_method(a, b, eps,&accuracy,number_of_iterations_BM,150,done);

		printf("|\t    %.1e\t\t|\t         %d\t\t|\t     %d\t\t\t|\n", eps, number_of_iterations_IM, number_of_iterations_BM);

		printf("-------------------------------------------------------------------------------------------------\n");
	}
	

}
int main()
{
	double a = 1;
	double b = 4;

	int number_of_necessary_parts;

	double* array_with_necessary_parts = create_array_with_necessary_parts(&number_of_necessary_parts,a,b);

	iteration_method_table(array_with_necessary_parts,number_of_necessary_parts);

	bisection_method_table(array_with_necessary_parts, number_of_necessary_parts);

	comparing_table(array_with_necessary_parts[0]);

	delete[] array_with_necessary_parts;

	system("pause");
}

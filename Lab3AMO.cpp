// Lab3AMO.cpp : This file contains the 'main' function. Program execution begins and ends there.
//

#include <iostream>
using namespace std;

#define number_of_lines 4
#define number_of_columns 5

void Prepare_Matrix(double Mtrx[number_of_lines][number_of_columns]) {

	for (int columns_count = 0; columns_count < number_of_columns - 1; columns_count++) {

		for (int lines_count = 0; lines_count < number_of_lines; lines_count++) {

			if (abs(Mtrx[columns_count][columns_count]) < abs(Mtrx[lines_count][columns_count])) {

				for (int swap_count = 0; swap_count < number_of_columns; swap_count++) {

					double tmp = Mtrx[columns_count][swap_count];
					Mtrx[columns_count][swap_count] = Mtrx[lines_count][swap_count];
					Mtrx[lines_count][swap_count] = tmp;

				}
			}
		}
	}
}



bool Simple_Iteration_Method(double Mtrx[number_of_lines][number_of_columns],double eps,double maxit) {
	Prepare_Matrix(Mtrx);

	double Decisions[number_of_lines] = {0};
	double Previous_Decisions[number_of_lines] = {0};
	bool got_all_decisions = false;
	int iterations = 0;

	while ((!got_all_decisions)&&(iterations<maxit)) {

		for (int Decision_count = 0; Decision_count < number_of_lines; Decision_count++) {
			Decisions[Decision_count] = Mtrx[Decision_count][number_of_columns - 1];

			for (int i = 0; i < number_of_columns - 1; i++) {
				if (i != Decision_count) {
					Decisions[Decision_count] = Decisions[Decision_count] + Mtrx[Decision_count][i]*Decisions[i]*(-1);
				}
			}
			if( Mtrx[Decision_count][Decision_count]!=0 )
				Decisions[Decision_count] = Decisions[Decision_count] / Mtrx[Decision_count][Decision_count];
		}


		got_all_decisions = true;
		for (int i = 0; i < number_of_lines; i++) {
			if (abs(Decisions[i] - Previous_Decisions[i]) > eps) {
				got_all_decisions = false;
			}
			Previous_Decisions[i] = Decisions[i];
		}

		iterations++;
		
	}
	cout << "Simple Iteration Method"<<endl;
	
	if (iterations < maxit) {
		for (int i = 0; i < number_of_lines; i++) {
			printf("%.16e\t\n\n",Decisions[i]);
		}
		return true;
	}
	else {
		cout << "Can't find Decisions" << endl << endl;
		return false;
	}
}



void Calculate_Multipliers(double*Multipliers, double** Matrix,int count,double Max_Element,int Max_Element_Line,int Max_Element_Column) {
	for (int i = 0; i < number_of_lines - count; i++) {
		if (i == Max_Element_Line)
			continue;
		Multipliers[i] = -Matrix[i][Max_Element_Column] / Max_Element;
	}
}



double** Create_New_Matrix(double** Matrix, int count, int Max_Element_Line, int Max_Element_Column) {
	double** New_Matrix = new double* [number_of_lines - count - 1];
	for (int i = 0; i < number_of_lines - count - 1; i++) {
		New_Matrix[i] = new double[number_of_columns - count - 1];
	}
	int pass_line = 0,pass_column = 0;
	for (int i = 0; i < number_of_lines - count; i++) {
		if (i == Max_Element_Line) {
			pass_line=1;
			continue;
		}
		for (int j = 0; j < number_of_columns - count; j++) {
			if (j == Max_Element_Column) {
				pass_column=1;
				continue;
			}
			New_Matrix[i-pass_line][j-pass_column] = Matrix[i][j];
		}
		pass_column = 0;
	}

	
	for (int i = 0; i < number_of_lines-count; i++) {
		delete[] Matrix[i];
	}
	delete[]Matrix;

	return New_Matrix;
}



bool Select_Main_Element_Method(double Mtrx[number_of_lines][number_of_columns]) {
	//Primary Matrix Initialization 
	double**Matrix = new double*[number_of_lines];
	for (int i = 0; i < number_of_lines; i++) {
		Matrix[i] = new double[number_of_columns];
	}
	for (int i = 0; i < number_of_lines; i++) {
		for (int j = 0; j < number_of_columns; j++) {
			Matrix[i][j] = Mtrx[i][j];
		}
	}

	double** Matrix_With_Main_Rows_Coef = new double* [number_of_lines];

	
	int X_Positions_In_Main_Rows_Matrix[number_of_lines][number_of_lines];
	for (int j = 0; j < number_of_columns; j++) {
		X_Positions_In_Main_Rows_Matrix[0][j] = j;
	}

	//First main loop that creates matrixes one by one and finds main elements
	for (int count = 0; count < number_of_lines - 1; count++) {
		double Max_Element = Matrix[0][0];
		int Max_Element_Line, Max_Element_Column;
		for (int i = 0; i < number_of_lines-count; i++) {
			for (int j = 0; j < number_of_columns-count-1; j++) {
				if (Matrix[i][j] != 0 && abs(Matrix[i][j]) > abs(Max_Element)) {
					Max_Element = Matrix[i][j];
					Max_Element_Line = i;
					Max_Element_Column = j;
				}
			}
		}

		if (Max_Element == 0) {
			cout << "Can't find Decisions with method of selecting main element"<<endl;
			return false;
		}

		for (int i = 0; i < Max_Element_Column; i++) {
			X_Positions_In_Main_Rows_Matrix[count + 1][i] = X_Positions_In_Main_Rows_Matrix[count][i];
		}
		
		for (int i = Max_Element_Column + 1; i < number_of_lines - count; i++) {
			X_Positions_In_Main_Rows_Matrix[count + 1][i - 1] = X_Positions_In_Main_Rows_Matrix[count][i];
		}

		

		double*Multipliers = new double[number_of_lines - count];

		Calculate_Multipliers(Multipliers, Matrix, count, Max_Element,Max_Element_Line,Max_Element_Column);
		

		for (int i = 0; i < number_of_lines - count; i++) {
			if (i == Max_Element_Line)
				continue;
			for (int j = 0; j < number_of_columns - count; j++) {
				Matrix[i][j] += Multipliers[i] * Matrix[Max_Element_Line][j];
			}
		}

		
		Matrix_With_Main_Rows_Coef[count] = new double[number_of_columns - count];
		for (int i = 0; i < number_of_columns - count; i++) {
			Matrix_With_Main_Rows_Coef[count][i] = Matrix[Max_Element_Line][i];
		}

		delete[]Multipliers;
		
		

		Matrix = Create_New_Matrix(Matrix,count,Max_Element_Line,Max_Element_Column);
	}



	double Decisions[number_of_lines];
	Decisions[X_Positions_In_Main_Rows_Matrix[number_of_lines-1][0]] = Matrix[0][1]/Matrix[0][0];
	
	delete[]Matrix[0];
	delete[]Matrix;

	
	int number_of_parts = 3;
	double parts_sum = 0;
	//Second main loop that finds all roots from triangle
	for (int i = number_of_lines-2 ; i >= 0; i--) {

		double coef_of_unknown_x;
		int line_of_unknown_x_coef, column_of_unknown_x_coef;

		for (int j = 0; j < number_of_parts-1; j++) {

			bool x_was_in_previous_main_row = false;
			for (int count_column = 0; count_column < number_of_parts-1; count_column++) {
				if (X_Positions_In_Main_Rows_Matrix[i][j] == X_Positions_In_Main_Rows_Matrix[i+1][count_column]) {
					x_was_in_previous_main_row = true;
					break;
				}
			}

			if (!x_was_in_previous_main_row) {
				coef_of_unknown_x = Matrix_With_Main_Rows_Coef[i][j];
				line_of_unknown_x_coef = i;
				column_of_unknown_x_coef = j;
				continue;
			}

			parts_sum += -Matrix_With_Main_Rows_Coef[i][j] * Decisions[X_Positions_In_Main_Rows_Matrix[i][j]];
		}
		Decisions[X_Positions_In_Main_Rows_Matrix[line_of_unknown_x_coef][column_of_unknown_x_coef]] = 
									(Matrix_With_Main_Rows_Coef[i][number_of_parts - 1] + parts_sum)/coef_of_unknown_x;
		
		number_of_parts++;
		parts_sum = 0;
	}

	cout << "Select Main Element Method" << endl;
	for (int i = 0; i <number_of_lines; i++) {
		printf("%.16e\t\n\n",Decisions[i]);
	}

	for (int i = 0; i < number_of_lines-1; i++) {
		delete[]Matrix_With_Main_Rows_Coef[i];
	}
	delete[]Matrix_With_Main_Rows_Coef;

	return true;
}


int main() 
{

	double Mtrx[number_of_lines][number_of_columns]{ 
		{8,4,8,20,148},
		{8,27,12,6,87},
		{16,13,46,16,157},
		{19,10,17,17,169}
	};

	Simple_Iteration_Method(Mtrx,1e-8,150);

	Select_Main_Element_Method(Mtrx);

	system("pause");
}


#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include<stdio.h>
#include<conio.h>
using std::cout;
using std::cin;
using std::endl;
using std::vector;
using std::string;


struct Matrix
{
	int rows;
	int cols;
	vector<vector<int> > mat;
	string matLink; 
	string dimLink;
	Matrix(int vRows, int vCols)
	{
		rows = vRows;
		cols = vCols;
	}

	//draw matrix from .txt file
	void DrawMat()
	{
		vector<vector<int> > mx(this->rows, vector<int>(this->cols));
		vector<int> tempVec(this->rows * this->cols);
		this->mat = mx;
		std::ifstream fin;
		fin.open(this->matLink);
		char ch;
		int c1 = 0, c2 = 0;
		while (fin.get(ch))
		{
			if (std::isdigit(ch))
			{
				tempVec[c1] = ch - '0';
				c1 += 1;
			}
		}
		if ((this->rows < 26) and (this->cols < 26))
		{
			for (int i = 0; i < this->rows; i++)
			{
				for (int j = 0; j < this->cols; j++)
				{
					this->mat[i][j] = tempVec[c2];
					c2 += 1;
				}
			}
		}
		else
		{
			cout << "Матрица слишком большого размера" << endl;
		}

		fin.close();
	}
	//console output
	void printMat()
	{
		for (int i = 0; i < this->rows; i++)
		{
			for (int j = 0; j < this->cols; j++)
			{
				printf("%d\t", this->mat[i][j]);
			}
			printf("\n");
		}
		printf("\n");
	}
	int DrawRows()
	{
		std::ifstream fin;
		fin.open(this->dimLink);
		string str;
		if (!fin.eof())
		{
			fin >> str;
		}
		if (std::stoi(str.substr(0, 2)) < 25)
		{
			this->rows = std::stoi(str.substr(0, 2));
		}
		else
		{
			cout << "Слишком много строк" << endl;
		}
		fin.close();
		return rows;
	}
	int DrawCols()
	{
		std::ifstream fin;
		fin.open(this->dimLink);
		string str;
		if (!fin.eof())
		{
			fin >> str;
		}
		if (std::stoi(str.substr(3, 5)) < 25)
		{
			this->cols = std::stoi(str.substr(3, 5));
		}
		else
		{
			cout << "Слишком много столбцов" << endl;
		}
		fin.close();
		return cols;
	}
};
//транспонирование матрицы
Matrix transpose(Matrix M1)
{
	vector<vector<int> > transposed(M1.cols, vector<int>(M1.rows));
	for (int i = 0; i < M1.rows; i++)
	{
		for (int j = 0; j < M1.cols; j++)
		{
			transposed[j][i] = M1.mat[i][j];
		}
	}
	int tempDim = M1.cols;
	M1.cols = M1.rows;
	M1.rows = tempDim;
	M1.mat = transposed;
	return M1;
}
//сумма двух матриц M1 и M2
Matrix summa(Matrix M1, Matrix M2) {
	if ((M1.rows == M2.rows and (M1.cols == M2.cols)))
	{
		int rows = M1.rows;
		int cols = M1.cols;
		Matrix M3(rows, cols);
		vector<vector<int> > result(rows, vector<int>(cols));
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				result[i][j] = M1.mat[i][j] + M2.mat[i][j];
			}
		}
		M3.mat = result;
		return M3;
	}
	else
	{
		cout << "Ошибка, размеры матриц отличаются" << endl;
		Matrix M3(0, 0);
		return M3;
	}
}
//разность двух матриц M1 и M2
Matrix substract(Matrix M1, Matrix M2) {
	if ((M1.rows == M2.rows and (M1.cols == M2.cols)))
	{
		int rows = M1.rows;
		int cols = M1.cols;
		Matrix M3(rows, cols);
		vector<vector<int> > result(rows, vector<int>(cols));
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				result[i][j] = M1.mat[i][j] - M2.mat[i][j];
			}
		}
		M3.mat = result;
		return M3;
	}
	else
	{
		cout << "Ошибка, размеры матриц отличаются" << endl;
		Matrix M3(0, 0);
		return M3;
	}
}
//произведение двух матриц M1 и M2
Matrix mult(Matrix M1, Matrix M2)
{
	if (M1.cols == M2.rows)
	{
		int rows = M1.rows;
		int cols = M2.cols;
		vector<vector<int> > result(rows, vector<int>(cols));
		Matrix M3(rows, cols);
		for (int i = 0; i < rows; i++)
		{
			for (int j = 0; j < cols; j++)
			{
				for (int k = 0; k < M1.cols; k++)
				{
					result[i][j] += M1.mat[i][k] * M2.mat[k][j];
				}
			}
		}
		M3.mat = result;
		return M3;
	}
	else
	{
		cout << "Матричное умножение невозможно!" << endl;
		Matrix M3(0, 0);
		return M3;
	}
}


int main()
{
	setlocale(LC_ALL, "Russian");
	Matrix A(0, 0);
	Matrix B(0, 0);
	Matrix C(0, 0);
	A.dimLink = "dim.txt";
	B.dimLink = "dim2.txt";
	C.dimLink = "dim3.txt";
	A.matLink = "matrix.txt";
	B.matLink = "matrix2.txt";
	C.matLink = "matrix3.txt";
	A.DrawRows();
	A.DrawCols();
	B.DrawRows();
	B.DrawCols();
	C.DrawRows();
	C.DrawCols();
	A.DrawMat();
	B.DrawMat();
	C.DrawMat();
	//решение задачи:
	//Условие: D = A^T*(C^T-B*A)
	cout << "Matrix A:" << endl;
	A.printMat();
	cout << "Matrix B:" << endl;
	B.printMat();
	cout << "Matrix C:" << endl;
	C.printMat();
	Matrix D = mult(transpose(A), substract(transpose(C), mult(B, A)));
	cout << "Result: " << endl;
	D.printMat();
	std::ofstream fout;
	fout.open("output.txt");
	for (uint32_t i = 0; i < D.rows; i++)
	{
		for (uint32_t j = 0; j < D.cols; j++)
		{
			fout << D.mat[i][j] << "\t";
		}
		cout << endl;
	}
	fout.close();
}


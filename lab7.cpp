#include <iostream>

class Test
{

	// конструктор по умолчанию
	// деструктор по умолчанию
	// конструктор копирования по умолчанию
};

class Matrix
{
// Абстракция
// Инкапсуляция
// Использование вне класса
public:
	// Конструктор
	Matrix(int n, int m)
	{
		std::cout << "Constructor" << std::endl;
		m_n = n;
		m_m = m;
		m_mat = new int* [m_n];
		for (int i = 0; i < m_n; i++)
			m_mat[i] = new int[m_m];
	}

	// Конструктор копирования
	Matrix(const Matrix& mat)
	{
		std::cout << "Copy constructor" << std::endl;

		m_n = mat.m_n;
		m_m = mat.m_m;

		m_mat = new int* [m_n];
		for (int i = 0; i < m_n; i++)
			m_mat[i] = new int[m_m];

		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				m_mat[i][j] = mat.m_mat[i][j];
	}

	// Присваивание
	Matrix& operator=(const Matrix& mat)
	{
		std::cout << "Operator =" << std::endl;

		m_n = mat.m_n;
		m_m = mat.m_m;

		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				m_mat[i][j] = mat.m_mat[i][j];

		return *this;
	}

	// Оператор сложения
	Matrix operator+(const Matrix& mat) {
		std::cout << "operator+" << std::endl;
		Matrix tmp(mat.m_n, mat.m_m);
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
		return tmp;
	}

	// Оператор сложения  C += A <=> C = C + A
	Matrix operator+=(const Matrix& mat) {
		std::cout << "operator+=" << std::endl;
		Matrix tmp(mat.m_n, mat.m_m);
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = m_mat[i][j] + mat.m_mat[i][j];
		return tmp;
	}

	// Оператор умножения
	Matrix operator*(const Matrix& mat) {
		std::cout << "operator*" << std::endl;
		Matrix tmp(mat.m_n, mat.m_m);
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = 0;
		for (int i = 0; i < m_n; i++)
			for (int q = 0; q < m_m; q++)
				for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][q] = m_mat[i][j] * mat.m_mat[j][q] + tmp.m_mat[i][q];
		return tmp;
	}

	// Оператор вычитания
	Matrix operator-(const Matrix& mat) {
		std::cout << "operator-" << std::endl;
		Matrix tmp(mat.m_n, mat.m_m);
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = m_mat[i][j] - mat.m_mat[i][j];
		return tmp;
	}

	// Оператор вычитания  C -= A <=> C = C - A
	Matrix operator-=(const Matrix& mat) {
		std::cout << "operator-=" << std::endl;
		Matrix tmp(mat.m_n, mat.m_m);
		for (int i = 0; i < m_n; i++)
			for (int j = 0; j < m_m; j++)
				tmp.m_mat[i][j] = m_mat[i][j] - mat.m_mat[i][j];
		return tmp;
	}



	    int det(const Matrix & mat) {
			std::cout << "determinal" << std::endl;
			if ((m_n == 2 and m_m == 2) or (m_n == 3 and m_m == 3)) {
				if (m_n == 2 and m_m == 2) {
					int tmp;
					tmp = m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0];
					return tmp;
				}
				else {
					int tmp;
					tmp = m_mat[0][0] * m_mat[1][1] * m_mat[2][2] + m_mat[1][0] * m_mat[2][1] * m_mat[0][2] + m_mat[0][1] * m_mat[1][2] * m_mat[2][0] - m_mat[0][2] * m_mat[1][1] * m_mat[2][0] - m_mat[0][0] * m_mat[1][2] * m_mat[2][1] - m_mat[0][1] * m_mat[1][0] * m_mat[2][2];
					return tmp;
				}
			}
			else {
				std::cout << "ERROR";
			}
		}


		Matrix inv(const Matrix& mat) {
			std::cout << "inversion" << std::endl;
			if ((m_n == 2 and m_m == 2) or (m_n == 3 and m_m == 3)) {
				if (m_n == 2 and m_m == 2) {
					Matrix tmp(2, 2);


					int k;
					k = m_mat[0][0] * m_mat[1][1] - m_mat[0][1] * m_mat[1][0];


					tmp.m_mat[0][0] = m_mat[1][1]/k;
					tmp.m_mat[0][1] = m_mat[0][1]/k;
					tmp.m_mat[1][0] = m_mat[1][0]/k;
					tmp.m_mat[1][1] = m_mat[0][0]/k;
					return tmp;
				}
				else {
					Matrix tmp(3,3);
					int k;
					k = m_mat[0][0] * m_mat[1][1] * m_mat[2][2] + m_mat[1][0] * m_mat[2][1] * m_mat[0][2] + m_mat[0][1] * m_mat[1][2] * m_mat[2][0] - m_mat[0][2] * m_mat[1][1] * m_mat[2][0] - m_mat[0][0] * m_mat[1][2] * m_mat[2][1] - m_mat[0][1] * m_mat[1][0] * m_mat[2][2];


					tmp.m_mat[0][0] = (m_mat[1][1] * m_mat[2][2] - m_mat[2][1] * m_mat[1][2])/k;
					tmp.m_mat[1][0] = (m_mat[1][0] * m_mat[2][2] - m_mat[2][0] * m_mat[1][2])/k;
					tmp.m_mat[2][0] = (m_mat[1][0] * m_mat[2][1] - m_mat[2][0] * m_mat[1][1])/k;
					tmp.m_mat[0][1] = (m_mat[0][1] * m_mat[2][2] - m_mat[2][1] * m_mat[0][2])/k;
					tmp.m_mat[1][1] = (m_mat[0][0] * m_mat[2][2] - m_mat[2][0] * m_mat[0][2])/k;
					tmp.m_mat[2][1] = (m_mat[0][0] * m_mat[2][1] - m_mat[2][0] * m_mat[0][1])/k;
					tmp.m_mat[0][2] = (m_mat[0][1] * m_mat[1][2] - m_mat[1][1] * m_mat[0][2])/k;
					tmp.m_mat[1][2] = (m_mat[0][0] * m_mat[1][2] - m_mat[1][0] * m_mat[0][2])/k;
					tmp.m_mat[2][2] = (m_mat[0][0] * m_mat[1][1] - m_mat[1][0] * m_mat[0][1])/k;
				
					return tmp;
				}
			}
			else {
				std::cout << "ERROR";
			}
		}



		Matrix tran(const Matrix& mat) {
			std::cout << "transponirovanie" << std::endl;
			Matrix tmp(mat.m_m, mat.m_n);
			for (int i = 0; i < m_n; i++)
				for (int j = 0; j < m_m; j++)
					tmp.m_mat[j][i] = m_mat[i][j];
			return tmp;
		}

	

	
	// Деструктор
	~Matrix()
	{
		std::cout << "Destructor" << std::endl;
		for (int i = 0; i < m_n; i++)
			delete[] m_mat[i];
		delete m_mat;
	}

	// friend - позволяет функции иметь доступ к private полям/методам класса
	friend std::istream& operator>>(std::istream& os, Matrix& mat);
	friend std::ostream& operator<<(std::ostream& os, const Matrix& mat);

// Использование внутри класса
private:
	int m_n, m_m;		// Поле
	int n;
	int** m_mat;
};

// Перегрузка оператора ввода
// 
std::istream& operator>>(std::istream& in, Matrix& mat)
{
	for (int i = 0; i < mat.m_n; i++)
		for (int j = 0; j < mat.m_m; j++)
			in >> mat.m_mat[i][j];
	return in;
}

// Перегрузка оператора вывода
std::ostream& operator<<(std::ostream& out, const Matrix& mat)
{
	out << "Matrix " << mat.m_n << "x" << mat.m_m << std::endl;
	for (int i = 0; i < mat.m_n; i++) {
		for (int j = 0; j < mat.m_m; j++)
			out << mat.m_mat[i][j] << " ";
		out << std::endl;
	}
	return out;
}

void print(Matrix& mat)
{
	std::cout << "111" << std::endl;
}

int main()
{
	Test test;

	Matrix A(3, 3);

	std::cin >> A;
	std::cout << A << std::endl; 
	Matrix B(3, 3);
	std::cin >> B;
	std::cout << B << std::endl;
	Matrix C(3, 3);
	C = A * B;
	std::cout << C << std::endl;



	return 0;
}

#include "Matrix.h"

Matrix::Matrix()
{
	this->cols = 0;
	this->rows = 0;
	this->step = 0;
	this->copy = (int*)malloc(sizeof(int));
	this->copy[0] = 0;
	this->data = (float*)malloc(sizeof(float));
	this->data[0] = 0;
}

Matrix::Matrix(const size_t& cols, const size_t& rows)
{
	if ((cols < 0) || (rows < 0))
	{
		this->cols = 0;
		this->rows = 0;
		this->step = 0;
		this->copy = (int*)malloc(sizeof(int));
		this->copy[0] = 0;
		this->data = (float*)malloc(sizeof(float));
		this->data[0] = 0;
	}
	else
	{
		this->cols = cols;
		this->rows = rows;
		this->step = cols;
		this->copy = (int*)malloc(sizeof(int));
		this->copy[0] = 0;
		this->data = (float*)malloc(cols * rows * sizeof(float));
		memset(this->data, 0, cols * rows * sizeof(float));
	}
}

Matrix::Matrix(const size_t& cols, const size_t& rows, const float* mat)
{
	if ((cols < 0) || (rows < 0))
	{
		this->cols = 0;
		this->rows = 0;
		this->step = 0;
		this->copy = (int*)malloc(sizeof(int));
		this->copy[0] = 0;
		this->data = (float*)malloc(sizeof(float));
		this->data[0] = 0;
	}
	else
	{
		this->cols = cols;
		this->rows = rows;
		this->step = cols;
		this->copy = (int*)malloc(sizeof(int));
		this->copy[0] = 0;
		this->data = (float*)malloc(cols * rows * sizeof(float));
		for (size_t i = 0; i < rows; i++)
		{
			for (size_t j = 0; j < cols; j++)
			{
				this->data[i * cols + j] = mat[i * cols + j];
			}
		}
	}
}

Matrix::Matrix(Matrix& mat)
{
	this->cols = mat.cols;
	this->rows = mat.rows;
	this->step = mat.step;
	this->copy = mat.copy;
	this->data = mat.data;
	this->copy[0]++;
}

void Matrix::operator=(Matrix& mat)
{
	this->cols = mat.cols;
	this->rows = mat.rows;
	this->step = mat.step;
	this->copy = mat.copy;
	this->data = mat.data;
	this->copy[0]++;
}

size_t Matrix::getSize()
{
	return this->rows * this->cols;
}

size_t Matrix::getRows()
{
	return this->rows;
}

size_t Matrix::getCols()
{
	return this->cols;
}

int Matrix::getCopy()
{
	return this->copy[0];
}

float Matrix::getPlace(const size_t& cols, const size_t& rows)
{
	if ((cols >= this->cols) || (cols < 0) 
		|| (rows >= this->rows) || (rows < 0))
	{
		std::cout << "Your input is out of place.\n";
		return 0;
	}
	return this->data[rows * this->step + cols];
}

void Matrix::setPlace(const size_t& cols, const size_t& rows, const float& k)
{
	if ((cols >= this->cols) || (cols < 0)
		|| (rows >= this->rows) || (rows < 0))
	{
		std::cout << "Your input is out of place.\n";
	}
	this->data[rows * this->step + cols] = k;
}

void Matrix::transposition()
{
	float* temp = (float*)malloc(cols * rows * sizeof(float));
	for (size_t i = 0; i < this->rows; i++)
	{
		for (size_t j = 0; j < this->cols; j++)
		{
			temp[j * this->rows + i] = this->data[i * this->cols + j];
		}
	}
	free(this->data);
	this->data = temp;
	size_t a;
	a = this->cols;
	this->cols = this->rows;
	this->rows = a;
	this->step = this->cols;
}

Matrix& Matrix::operator+(const Matrix& mat) const
{
	if ((this->rows != mat.rows) || ((this->cols != mat.cols)))
	{
		std::cout << "Matrices doesn't match!" << endl;
		return *(new Matrix());
	}
	Matrix* temp = new Matrix(this->cols, this->rows);
	for (size_t i = 0; i < temp->rows; i++)
	{
		for (size_t j = 0; j < temp->cols; j++)
		{
			temp->data[i * temp->step + j] =
				this->data[i * temp->step + j] +
				mat.data[i * temp->step + j];
		}
	}
	return *temp;
}

Matrix& Matrix::operator+(const float k) const
{
	Matrix* temp = new Matrix(this->cols, this->rows);
	for (size_t i = 0; i < temp->rows; i++)
	{
		for (size_t j = 0; j < temp->cols; j++)
		{
			temp->data[i * temp->step + j] =
				this->data[i * temp->step + j] + k;
		}
	}
	return *temp;
}

Matrix& Matrix::operator-(const Matrix& mat) const
{
	if ((this->rows != mat.rows) || ((this->cols != mat.cols)))
	{
		std::cout << "Matrices doesn't match!" << endl;
		return *(new Matrix());
	}
	Matrix* temp = new Matrix(this->cols, this->rows);
	for (size_t i = 0; i < temp->rows; i++)
	{
		for (size_t j = 0; j < temp->cols; j++)
		{
			temp->data[i * temp->step + j] =
				this->data[i * temp->step + j] -
				mat.data[i * temp->step + j];
		}
	}
	return *temp;
}

Matrix& Matrix::operator-(const float k) const
{
	Matrix* temp = new Matrix(this->cols, this->rows);
	for (size_t i = 0; i < temp->rows; i++)
	{
		for (size_t j = 0; j < temp->cols; j++)
		{
			temp->data[i * temp->step + j] =
				this->data[i * temp->step + j] - k;
		}
	}
	return *temp;
}

Matrix& Matrix::operator*(const Matrix& mat) const
{
	if (this->cols != mat.rows)
	{
		std::cout << "Matrices doesn't match!" << endl;
		return *(new Matrix());
	}
	Matrix* temp = new Matrix(this->cols, this->rows);
	for (size_t i = 0; i < temp->rows; i++)
	{
		for (size_t j = 0; j < temp->cols; j++)
		{
			float result = 0;
			for (int k = 0; k < this->cols; k++)
			{
				result += this->data[i * this->step + k] 
					* mat.data[k * mat.step + j];
			}
			temp->data[i * temp->step + j] = result;
		}
	}
	return *temp;
}

Matrix& Matrix::operator*(const float k) const
{
	Matrix* temp = new Matrix(this->cols, this->rows);
	for (size_t i = 0; i < temp->rows; i++)
	{
		for (size_t j = 0; j < temp->cols; j++)
		{
			temp->data[i * temp->step + j] =
				this->data[i * temp->step + j] * k;
		}
	}
	return *temp;
}

Matrix* Matrix::operator &()
{
	return this;
}

const Matrix* Matrix::operator &() const
{
	return this;
}

const float& Matrix::operator[](size_t place) const
{
	return this->data[place];
}

Matrix& operator+(float k, Matrix& mat)
{
	Matrix* temp = new Matrix(mat.cols, mat.rows);
	for (size_t i = 0; i < temp->rows; i++)
	{
		for (size_t j = 0; j < temp->cols; j++)
		{
			temp->data[i * temp->step + j] =
				k + mat.data[i * temp->step + j];
		}
	}
	return *temp;
}

Matrix& operator-(float k, Matrix& mat)
{
	Matrix* temp = new Matrix(mat.cols, mat.rows);
	for (size_t i = 0; i < temp->rows; i++)
	{
		for (size_t j = 0; j < temp->cols; j++)
		{
			temp->data[i * temp->step + j] =
				k - mat.data[i * temp->step + j];
		}
	}
	return *temp;
}

Matrix& operator*(float k, Matrix& mat)
{
	Matrix* temp = new Matrix(mat.cols, mat.rows);
	for (size_t i = 0; i < temp->rows; i++)
	{
		for (size_t j = 0; j < temp->cols; j++)
		{
			temp->data[i * temp->step + j] =
				k * mat.data[i * temp->step + j];
		}
	}
	return *temp;
}

bool operator==(Matrix& mat1, Matrix& mat2)
{
	if(mat1.data == mat2.data)
	{
		return true;
	}
	return false;
}

ostream& operator<<(ostream& os, const Matrix& mat)
{
	for (size_t i = 0; i < mat.rows; i++)
	{
		for (size_t j = 0; j < mat.cols; j++)
		{
			os << mat.data[i * mat.step + j] << " ";
		}
		os << "\n";
	}
	return os;
}

Matrix::~Matrix()
{
	if (this->copy[0] == 0)
	{
		free(this->copy);
		free(this->data);
	}
	else
	{
		this->copy[0]--;
	}
}

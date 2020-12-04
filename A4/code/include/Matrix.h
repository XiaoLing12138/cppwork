#ifndef _Matrix_H_
#define _Matrix_H_

#include <iostream>
#include <cstdio>

using namespace std;

class Matrix
{
private:
	size_t cols;
	size_t rows;
	size_t step;
	int* copy;
	float* data;
public:
	Matrix();
	Matrix(const size_t& cols, const size_t& rows);
	Matrix(const size_t& cols, const size_t& rows, const float* mat);
	Matrix(Matrix& mat);
	void operator=(Matrix& mat);

	size_t getRows();
	size_t getCols();
	size_t getSize();
	int getCopy();
	float getPlace(const size_t& cols, const size_t& rows);
	void setPlace(const size_t& cols, const size_t& rows, const float& k);
	void transposition();
	
	const float& operator[](const size_t place) const;

	Matrix& operator+(const Matrix& mat) const;
	Matrix& operator+(const float k) const;
	Matrix& operator-(const Matrix& mat) const;
	Matrix& operator-(const float k) const;
	Matrix& operator*(const Matrix& mat) const;
	Matrix& operator*(const float k) const;

	Matrix* operator &();
	const Matrix* operator &() const;

	friend Matrix& operator+(float k, Matrix& mat);
	friend Matrix& operator-(float k, Matrix& mat);
	friend Matrix& operator*(float k, Matrix& mat);
	friend bool operator==(Matrix& mat1, Matrix& mat2);

	friend ostream& operator<<(ostream& os, const Matrix& mat);

	~Matrix();
};
#endif // _Matrix_H_

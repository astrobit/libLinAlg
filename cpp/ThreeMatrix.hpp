#pragma once
#include <ThreeVector.hpp>

/** 
@brief A javascript implementation of a 3x3 Matrix
@details 
@author Brian W. Mulligan
@version 1.0.0
@date May 2020
@copyright MIT License
*/

class ThreeMatrix
{
private:
	float _data[3][3];
public:
/** 
ThreeMatrix constructor. If the parameter is null or not a valid type, the matrix will be initiailized as a zero matrix.
@param otherThreeMatrix a structure containing the value with which to initialize the matrix. otherThreeMatrix may be a ThreeMatrix, an Array with 9 values (assumed to be in row order, or an Array containing three Arrays, each with length 3, and assumed to be in [row][column] order.
*/
	ThreeMatrix(void)
	{
		loadZero();
	}
	ThreeMatrix (float ** initData)
	{
		int TcI,TcJ;
		if (initData != nullptr)
		{
			for (TcI = 0; TcI < 3; TcI++)
			{
				for (TcJ = 0; TcJ < 3; TcJ++)
				{
					_data[TcI][TcJ] = initData[TcI][TcJ];
				}
			}
		}
	}
	ThreeMatrix (float * initData)
	{
		int TcI,TcJ;
		if (initData != nullptr)
		{
			for (TcI = 0; TcI < 3; TcI++)
			{
				for (TcJ = 0; TcJ < 3; TcJ++)
				{
					_data[TcI][TcJ] = initData[TcI * 3 + TcJ];
				}
			}
		}
	}
	ThreeMatrix (const std::vector<std::vector<float>> &initData)
	{
		int TcI,TcJ;
		if (initData.size() >= 3 && initData[0].size() >= 3 && initData[1].size() >= 3 && initData[2].size() >= 3)
		{
			for (TcI = 0; TcI < 3; TcI++)
			{
				for (TcJ = 0; TcJ < 3; TcJ++)
				{
					_data[TcI][TcJ] = initData[TcI][TcJ];
				}
			}
		}
		else
			loadZero();
	}
/** 
Retreive the value of the element at the given row and column, zero indexed
@param row the zero indexed row from which to retrieve an element
@param column the zero indexed column from which to retrieve an element
@returns the value at the selected row and column, null otherwise
*/
	float at(int row, int column) const
	{
		if (row >= 0 && row < 3 && column >= 0 && column < 3 )
			return _data[row][column];
		else
			return 0.0;
	}

/** 
Set the value of the element at the given row and column, zero indexed
@param row the zero indexed row from which to set an element
@param column the zero indexed column from which to set an element
@param value the value to insert into the matrix.
*/
	void setAt(int row,int column,float value)
	{
		if (row >= 0 && row < 3 && column >= 0 && column < 3 )
			_data[row][column] = value;
	}

/** 
Set the values of the elements int the given column, zero indexed
@param column the zero indexed column from which to set the elements
@param value the values to insert into the matrix.
*/
	void setColumn(int column,const ThreeVector & value)
	{
		if (column >= 0 && column < 3 )
		{
			_data[0][column] = value._x;
			_data[1][column] = value._y;
			_data[2][column] = value._z;
		}
	}
/** 
Set the values of the elements int the given row, zero indexed
@param row the zero indexed row from which to set an element
@param value the values to insert into the matrix.
*/
	void setRow(int row,const ThreeVector & value)
	{
		if (row >= 0 && row < 3 )
		{
			_data[row][0] = value._x;
			_data[row][1] = value._y;
			_data[row][2] = value._z;
		}
	}

/** 
Retrieve a row vector for a given row
@param row the zero indexed row from which to retrieve
@returns If row is a valid index, then a ThreeVector containing the row data, otherwise null
*/
	ThreeVector row(int rowNum) const
	{
		if (rowNum >= 0 && rowNum < 3)
		{
			return ThreeVector(_data[rowNum][0],_data[rowNum][1],_data[rowNum][2]);
		}
		else
			return ThreeVector();
	}
/** 
Retrieve a column vector for a given column
@param column the zero indexed column from which to retrieve
@returns If column is a valid index, then a ThreeVector containing the column data, otherwise null
*/
	ThreeVector column(int columnNum) const
	{
		if (columnNum >= 0 && columnNum < 3)
		{
			return ThreeVector(_data[0][columnNum],_data[1][columnNum],_data[2][columnNum]);
		}
		else
			return ThreeVector();
	}

/** 
Perform a matrix multiplication with a column vector
@param vector the ThreeVector by which the matrix is multiplied
@returns the value at the selected row and column, null otherwise
*/
	ThreeVector operator *(const ThreeVector &vector) const
	{
		return ThreeVector(_data[0][0] * vector._x + _data[0][1] * vector._y + _data[0][2] * vector._z,
						_data[1][0] * vector._x + _data[1][1] * vector._y + _data[1][2] * vector._z,
						_data[2][0] * vector._x + _data[2][1] * vector._y + _data[2][2] * vector._z
						);
	}
/** 
Perform a scalar multiplication of a three matrix
@param matrix the ThreeMatrix by which the matrix is multiplied
@returns if matrix is a ThreeMatrix, then a new ThreeMatrix containing the result of the multiplication, otherwise null
*/
	ThreeMatrix operator *(float scalar) const
	{
		ThreeMatrix ret;

		int TcI,TcJ;
		for (TcI = 0; TcI < 3; TcI++)
		{
			for (TcJ = 0; TcJ < 3; TcJ++)
			{
				ret._data[TcI][TcJ] = _data[TcI][TcJ] * scalar;
			}
		}
		return ret;
	}
/** 
Perform a matrix multiplication with a ThreeMatrix
@param matrix the ThreeMatrix by which the matrix is multiplied
@returns if matrix is a ThreeMatrix, then a new ThreeMatrix containing the result of the multiplication, otherwise null
*/
	ThreeMatrix operator *(const ThreeMatrix &matrix) const
	{
		ThreeMatrix ret;

		int TcI,TcJ;
		for (TcI = 0; TcI < 3; TcI++)
		{
			for (TcJ = 0; TcJ < 3; TcJ++)
			{
				ret.setAt(TcI,TcJ,row(TcI).dot(matrix.column(TcJ)));
			}
		}
		return ret;
	}
/** 
Perform a matrix addition with a ThreeMatrix
@param matrix the ThreeMatrix which the matrix is added
@returns if matrix is a ThreeMatrix, then a new ThreeMatrix containing the result of the addition, otherwise null
*/
	ThreeMatrix operator +(const ThreeMatrix &matrix) const
	{
		ThreeMatrix ret;

		int TcI,TcJ;
		for (TcI = 0; TcI < 3; TcI++)
		{
			for (TcJ = 0; TcJ < 3; TcJ++)
			{
				ret._data[TcI][TcJ] = _data[TcI][TcJ] + matrix._data[TcI][TcJ];
			}
		}
		return ret;
	}
/** 
Perform a matrix subtraction with a ThreeMatrix
@param matrix the ThreeMatrix which is to be subtracted from this matrix
@returns if matrix is a ThreeMatrix, then a new ThreeMatrix containing the result of the subtraction, otherwise null
*/
	ThreeMatrix operator -(const ThreeMatrix &matrix) const
	{
		ThreeMatrix ret;

		int TcI,TcJ;
		for (TcI = 0; TcI < 3; TcI++)
		{
			for (TcJ = 0; TcJ < 3; TcJ++)
			{
				ret._data[TcI][TcJ] = _data[TcI][TcJ] - matrix._data[TcI][TcJ];
			}
		}
		return ret;
	}
/** 
Perform a matrix transpose
@returns A new ThreeMatrix containing the result of the transposition
*/
	ThreeMatrix transpose(void) const
	{
		ThreeMatrix ret;
		int TcI,TcJ;
		for (TcI = 0; TcI < 3; TcI++)
		{
			for (TcJ = 0; TcJ < 3; TcJ++)
			{
				ret._data[TcI][TcJ] = _data[TcJ][TcI];
			}
		}
		return ret;
	}
/** 
Get the additive inverse of a matrix
@returns A new ThreeMatrix containing the result of the negation
*/
	ThreeMatrix operator- (void) const
	{
		ThreeMatrix ret;
		int TcI,TcJ;
		for (TcI = 0; TcI < 3; TcI++)
		{
			for (TcJ = 0; TcJ < 3; TcJ++)
			{
				ret._data[TcI][TcJ] = -_data[TcI][TcJ];
			}
		}
		return ret;
	}
/**
Get the determinant of the matrix
@returns The determinant of the matrix
*/
	float determinant(void) const
	{
		return _data[0][0] * (_data[1][1] * _data[2][2] - _data[1][2] * _data[2][1]) +
				_data[0][1] * (_data[1][2] * _data[2][0] - _data[1][0] * _data[2][2]) +
				_data[0][2] * (_data[1][0] * _data[2][1] - _data[1][1] * _data[2][0]);
	}
	
/**
Get the trace of the matrix
@returns The trace of the matrix
*/
	float trace(void) const
	{
		return _data[0][0] + _data[1][1] + _data[2][2];
	}
/**
Get the inverse of the matrix
@returns A new ThreeMatrix containing the multiplicitave inverse
*/
	ThreeMatrix invert(void) const
	{
		ThreeMatrix ret;
		float det = determinant();
		if (det != 0.0)
		{
			float invdet = 1.0 / det;
			ret._data[0][0] = invdet * (_data[1][1] * _data[2][2] - _data[1][2] * _data[2][1]);
			ret._data[1][0] = invdet * (_data[1][2] * _data[2][0] - _data[1][0] * _data[2][2]);
			ret._data[2][0] = invdet * (_data[1][0] * _data[2][1] - _data[1][1] * _data[2][0]);
			ret._data[0][1] = invdet * (_data[0][2] * _data[2][1] - _data[0][1] * _data[2][2]);
			ret._data[1][1] = invdet * (_data[0][0] * _data[2][2] - _data[0][2] * _data[2][0]);
			ret._data[2][1] = invdet * (_data[0][1] * _data[2][0] - _data[0][0] * _data[2][1]);
			ret._data[0][2] = invdet * (_data[0][1] * _data[1][2] - _data[0][2] * _data[1][1]);
			ret._data[1][2] = invdet * (_data[0][2] * _data[1][0] - _data[0][0] * _data[1][2]);
			ret._data[2][2] = invdet * (_data[0][0] * _data[1][1] - _data[0][1] * _data[1][0]);
		}
		return ret;
	}
/** 
Load the zero matrix
@returns none
*/
	void loadZero(void)
	{
		int TcI,TcJ;
		for (TcI = 0; TcI < 3; TcI++)
		{
			for (TcJ = 0; TcJ < 3; TcJ++)
			{
				_data[TcI][TcJ] = 0;
			}
		}
	}
/** 
Load the identity matrix
@returns none
*/
	void loadIdentity(void)
	{
		int TcI,TcJ;
		for (TcI = 0; TcI < 3; TcI++)
		{
			for (TcJ = 0; TcJ < 3; TcJ++)
			{
				if (TcI == TcJ)
					_data[TcI][TcJ] = 1.0;
				else
					_data[TcI][TcJ] = 0;
			}
		}
	}
};

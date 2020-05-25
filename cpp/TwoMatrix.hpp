#pragma once
#include <TwoVector.hpp>

/** 
@brief A javascript implementation of a 2x2 Matrix
@details 
@author Brian W. Mulligan
@version 1.0.0
@date May 2020
@copyright MIT License
*/

class TwoMatrix
{
private:
	float _data[2][2];
public:
/** 
TwoMatrix constructor. If the parameter is null or not a valid type, the matrix will be initiailized as a zero matrix.
@param otherTwoMatrix a structure containing the value with which to initialize the matrix. otherTwoMatrix may be a TwoMatrix, an Array with 9 values (assumed to be in row order, or an Array containing three Arrays, each with length 3, and assumed to be in [row][column] order.
*/
	TwoMatrix(void)
	{
		loadZero();
	}
	TwoMatrix (float ** initData)
	{
		int TcI,TcJ;
		if (initData != nullptr)
		{
			for (TcI = 0; TcI < 2; TcI++)
			{
				for (TcJ = 0; TcJ < 2; TcJ++)
				{
					_data[TcI][TcJ] = initData[TcI][TcJ];
				}
			}
		}
	}
	TwoMatrix (float * initData)
	{
		int TcI,TcJ;
		if (initData != nullptr)
		{
			for (TcI = 0; TcI < 2; TcI++)
			{
				for (TcJ = 0; TcJ < 2; TcJ++)
				{
					_data[TcI][TcJ] = initData[TcI * 2 + TcJ];
				}
			}
		}
	}
	TwoMatrix (const std::vector<std::vector<float>> &initData)
	{
		int TcI,TcJ;
		if (initData.size() >= 2 && initData[0].size() >= 2 && initData[1].size() >= 2)
		{
			for (TcI = 0; TcI < 2; TcI++)
			{
				for (TcJ = 0; TcJ < 2; TcJ++)
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
		if (row >= 0 && row < 2 && column >= 0 && column < 2 )
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
		if (row >= 0 && row < 2 && column >= 0 && column < 2 )
			_data[row][column] = value;
	}

/** 
Set the values of the elements int the given column, zero indexed
@param column the zero indexed column from which to set the elements
@param value the values to insert into the matrix.
*/
	void setColumn(int column,const TwoVector & value)
	{
		if (column >= 0 && column < 2 )
		{
			_data[0][column] = value._x;
			_data[1][column] = value._y;
		}
	}
/** 
Set the values of the elements int the given row, zero indexed
@param row the zero indexed row from which to set an element
@param value the values to insert into the matrix.
*/
	void setRow(int row,const TwoVector & value)
	{
		if (row >= 0 && row < 2 )
		{
			_data[row][0] = value._x;
			_data[row][1] = value._y;
		}
	}

/** 
Retrieve a row vector for a given row
@param row the zero indexed row from which to retrieve
@returns If row is a valid index, then a TwoVector containing the row data, otherwise null
*/
	TwoVector row(int rowNum) const
	{
		if (rowNum >= 0 && rowNum < 2)
		{
			return TwoVector(_data[rowNum][0],_data[rowNum][1]);
		}
		else
			return TwoVector();
	}
/** 
Retrieve a column vector for a given column
@param column the zero indexed column from which to retrieve
@returns If column is a valid index, then a TwoVector containing the column data, otherwise null
*/
	TwoVector column(int columnNum) const
	{
		if (columnNum >= 0 && columnNum < 2)
		{
			return TwoVector(_data[0][columnNum],_data[1][columnNum]);
		}
		else
			return TwoVector();
	}

/** 
Perform a matrix multiplication with a column vector
@param vector the TwoVector by which the matrix is multiplied
@returns the value at the selected row and column, null otherwise
*/
	TwoVector operator *(const TwoVector &vector) const
	{
		return TwoVector(_data[0][0] * vector._x + _data[0][1] * vector._y,
						_data[1][0] * vector._x + _data[1][1] * vector._y
						);
	}
/** 
Perform a scalar multiplication of a three matrix
@param matrix the TwoMatrix by which the matrix is multiplied
@returns if matrix is a TwoMatrix, then a new TwoMatrix containing the result of the multiplication, otherwise null
*/
	TwoMatrix operator *(float scalar) const
	{
		TwoMatrix ret;

		int TcI,TcJ;
		for (TcI = 0; TcI < 2; TcI++)
		{
			for (TcJ = 0; TcJ < 2; TcJ++)
			{
				ret._data[TcI][TcJ] = _data[TcI][TcJ] * scalar;
			}
		}
		return ret;
	}
/** 
Perform a matrix multiplication with a TwoMatrix
@param matrix the TwoMatrix by which the matrix is multiplied
@returns if matrix is a TwoMatrix, then a new TwoMatrix containing the result of the multiplication, otherwise null
*/
	TwoMatrix operator *(const TwoMatrix &matrix) const
	{
		TwoMatrix ret;

		int TcI,TcJ;
		for (TcI = 0; TcI < 2; TcI++)
		{
			for (TcJ = 0; TcJ < 2; TcJ++)
			{
				ret.setAt(TcI,TcJ,row(TcI).dot(matrix.column(TcJ)));
			}
		}
		return ret;
	}
/** 
Perform a matrix addition with a TwoMatrix
@param matrix the TwoMatrix which the matrix is added
@returns if matrix is a TwoMatrix, then a new TwoMatrix containing the result of the addition, otherwise null
*/
	TwoMatrix operator +(const TwoMatrix &matrix) const
	{
		TwoMatrix ret;

		int TcI,TcJ;
		for (TcI = 0; TcI < 2; TcI++)
		{
			for (TcJ = 0; TcJ < 2; TcJ++)
			{
				ret._data[TcI][TcJ] = _data[TcI][TcJ] + matrix._data[TcI][TcJ];
			}
		}
		return ret;
	}
/** 
Perform a matrix subtraction with a TwoMatrix
@param matrix the TwoMatrix which is to be subtracted from this matrix
@returns if matrix is a TwoMatrix, then a new TwoMatrix containing the result of the subtraction, otherwise null
*/
	TwoMatrix operator -(const TwoMatrix &matrix) const
	{
		TwoMatrix ret;

		int TcI,TcJ;
		for (TcI = 0; TcI < 2; TcI++)
		{
			for (TcJ = 0; TcJ < 2; TcJ++)
			{
				ret._data[TcI][TcJ] = _data[TcI][TcJ] - matrix._data[TcI][TcJ];
			}
		}
		return ret;
	}
/** 
Perform a matrix transpose
@returns A new TwoMatrix containing the result of the transposition
*/
	TwoMatrix transpose(void) const
	{
		TwoMatrix ret;
		int TcI,TcJ;
		for (TcI = 0; TcI < 2; TcI++)
		{
			for (TcJ = 0; TcJ < 2; TcJ++)
			{
				ret._data[TcI][TcJ] = _data[TcJ][TcI];
			}
		}
		return ret;
	}
/** 
Get the additive inverse of a matrix
@returns A new TwoMatrix containing the result of the negation
*/
	TwoMatrix operator- (void) const
	{
		TwoMatrix ret;
		int TcI,TcJ;
		for (TcI = 0; TcI < 2; TcI++)
		{
			for (TcJ = 0; TcJ < 2; TcJ++)
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
		return _data[0][0] * _data[1][1] - _data[0][1] * _data[1][0];
	}
	
/**
Get the trace of the matrix
@returns The trace of the matrix
*/
	float trace(void) const
	{
		return _data[0][0] + _data[1][1];
	}
/**
Get the inverse of the matrix
@returns A new TwoMatrix containing the multiplicitave inverse
*/
	TwoMatrix invert(void) const
	{
		TwoMatrix ret;
		float det = determinant();
		if (det != 0.0)
		{
			float invdet = 1.0 / det;
			ret._data[0][0] = invdet * _data[1][1];
			ret._data[0][1] = -invdet * _data[0][1];
			ret._data[1][0] = -invdet * _data[1][0];
			ret._data[1][1] = invdet * _data[0][0];
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
		for (TcI = 0; TcI < 2; TcI++)
		{
			for (TcJ = 0; TcJ < 2; TcJ++)
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
		for (TcI = 0; TcI < 2; TcI++)
		{
			for (TcJ = 0; TcJ < 2; TcJ++)
			{
				if (TcI == TcJ)
					_data[TcI][TcJ] = 1.0;
				else
					_data[TcI][TcJ] = 0;
			}
		}
	}
};

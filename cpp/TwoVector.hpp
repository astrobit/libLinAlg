#pragma once
#include <cmath>
/** 
@brief A c++ implementation of a 2-dimensional vector
@details 
@author Brian W. Mulligan
@version 1.0.0
@date May 2020
@copyright MIT License
*/

class TwoVector
{
friend class TwoMatrix;
private:
	float _x;
	float _y;
public:
	TwoVector(void)
	{
		loadZero();
	}

/** 
TwoVector constructor
@param x The x component or a TwoVector 
@param y The y component, ignored if x is a TwoVector
@param z The z component, ignored if x is a TwoVector
*/
	TwoVector(float x, float y)
	{
		_x = x;
		_y = y;
	}
/** 
TwoVector constructor
@param data An array of length 3 or greater with which to initialize the vector
*/
	TwoVector(float * data)
	{
		_x = data[0];
		_y = data[1];
	}
/** 
TwoVector constructor
@param data An std::vector<float> of length 3 or greater with which to initialize the vector
*/
	TwoVector(const std::vector<float> &data)
	{
		if (data.size() >= 2)
		{
			_x = data[0];
			_y = data[1];
		}
		else
			loadZero();
	}
/** 
Get for the x component
@returns The x component
*/
	float getX(void) const {return _x;}
/** 
Get for the y component
@returns The y component
*/
	float getY(void) const {return _y;}

/** 
Set for the x component
@param value The new value for the x component
@returns none
*/
	void setX(float value) {_x = value;}
/** 
Set for the z component
@param value The new value for the y component
@returns none
*/
	void setY(float value) {_y = value;}

/** 
Add one vector to another: \f$\vec{a} + \vec{b} = <a_x + b_x,a_y + b_y, a_z + b_z>\f$.
@param vectB the vector to add to this vector.
@returns a TwoVector with the result of the addition.
*/
	TwoVector operator +(const TwoVector & vectB) const
	{
		return TwoVector(_x + vectB._x,_y + vectB._y);
	}
	TwoVector operator +=(const TwoVector & vectB)
	{
		_x += vectB._x;
		_y += vectB._y;
		return *this;
	}
/** 
Create the additive inverse of a vector: \f$-\vec{a} = <-a_x,-a_y,-a_z>\f$
@returns a TwoVector containing the additive inverse of this vector.
*/
	TwoVector operator -(void) const
	{
		return TwoVector(-_x,-_y);
	}
/** 
Subtract one vector from another: \f$\vec{a} - \vec{b} = <a_x - b_x,a_y - b_y, a_z - b_z>\f$.
@param vectB the vector to subtract from this vector.
@returns a TwoVector with the result of the subtraction.
*/
	TwoVector operator -(const TwoVector & vectB) const
	{
		return *this + (-vectB);
	}
	TwoVector operator -=(const TwoVector & vectB)
	{
		return (*this += (-vectB));
	}
/** 
Scale the vector by a scalar factor: \f$s\vec{a} = <s x, s y, s z>\f$.
@param scalar the factor by which to scale the vector
@returns the scaled TwoVector 
*/
	TwoVector operator *(float scalar) const
	{
		return TwoVector(_x * scalar,_y * scalar);
	}
	TwoVector & operator *=(float scalar)
	{
		_x *= scalar;
		_y *= scalar;
		return *this;
	}
/** 
Divide the vector by a scalar factor: \f$\dfrac{1}{s}\vec{a} = <\dfrac{x}{s}, \dfrac{y}{s}, \dfrac{z}{s}>\f$.
@param scalar the factor by which to divide the vector
@returns the scaled TwoVector 
*/
	TwoVector operator /(float scalar) const
	{
		return *this * (1.0 / scalar);
	}
	TwoVector operator /=(float scalar)
	{
		return ((*this) *= (1.0 / scalar));
	}
/** 
Retrieve a scalar (dot) product for this vector: \f$\vec{a}\bullet\vec{b} = a_x b_x + a_y b_y + a_z b_z\f$
@returns the dot product 
*/
	float dot(const TwoVector &vectB) const
	{
		return _x * vectB._x + _y * vectB._y;
	}
/** 
Retrieve a cross product for these vector: \f$\vec{a}\times\vec{b} = a_xb_y - a_yb_x\f$
@returns the cross product
*/
	float cross(const TwoVector & vectB) const
	{
		return _x * vectB._y - _y * vectB._x;
	}
/** 
Get the magnitude (length) of the vector
@returns the magnitude of the vector \f$(\sqrt{x^2 + y^2})\f$
*/
	float magnitude(void)
	{
		return std::sqrt(dot(*this));
	}
	
/** 
Retrieve a unit vector for this vector
@returns the unit vector \f$(\dfrac{1}{\sqrt{x^2 + y^2}})<x,y>\f$
*/
	TwoVector unit(void)
	{
		float mag = magnitude();
		if (mag != 0.0)
			mag = 1.0 / mag;
		return TwoVector(_x * mag,_y * mag);
	}
	/**
Load the vector with a zero vector
@returns none
*/
	void loadZero(void)
	{
		_x = _y = 0.0;
	}
/**
Load the vector with a unit vector in the x direction
@returns none
*/
	void loadUnitX(void)
	{
		_x = 1.0;
		_y = 0.0;
	}
/**
Load the vector with a unit vector in the y direction
@returns none
*/
	void loadUnitY(void)
	{
		_y = 1.0;
		_x = 0.0;
	}
	
	float operator[] (int idx) const
	{
		float ret;
		switch (idx)
		{
		case 0:
		default:
			ret = _x;
			break;
		case 1:
			ret = _y;
			break;
		}
		return ret;
	}
};


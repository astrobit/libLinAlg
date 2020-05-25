#pragma once
#include <cmath>
/** 
@brief A c++ implementation of a 3-dimensional vector
@details 
@author Brian W. Mulligan
@version 1.0.0
@date May 2020
@copyright MIT License
*/

class ThreeVector
{
friend class ThreeMatrix;
private:
	float _x;
	float _y;
	float _z;
public:
	ThreeVector(void)
	{
		loadZero();
	}

/** 
ThreeVector constructor
@param x The x component or a ThreeVector 
@param y The y component, ignored if x is a ThreeVector
@param z The z component, ignored if x is a ThreeVector
*/
	ThreeVector(float x, float y, float z)
	{
		_x = x;
		_y = y;
		_z = z;
	}
/** 
ThreeVector constructor
@param data An array of length 3 or greater with which to initialize the vector
*/
	ThreeVector(float * data)
	{
		_x = data[0];
		_y = data[1];
		_z = data[2];
	}
/** 
ThreeVector constructor
@param data An std::vector<float> of length 3 or greater with which to initialize the vector
*/
	ThreeVector(const std::vector<float> &data)
	{
		if (data.size() >= 3)
		{
			_x = data[0];
			_y = data[1];
			_z = data[2];
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
Get for the z component
@returns The z component
*/
	float getZ(void) const {return _z;}

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
Set for the y component
@param value The new value for the z component
@returns none
*/
	void setZ(float value) {_z = value;}

/** 
Add one vector to another: \f$\vec{a} + \vec{b} = <a_x + b_x,a_y + b_y, a_z + b_z>\f$.
@param vectB the vector to add to this vector.
@returns a ThreeVector with the result of the addition.
*/
	ThreeVector operator +(const ThreeVector & vectB) const
	{
		return ThreeVector(_x + vectB._x,_y + vectB._y,_z + vectB._z);
	}
	ThreeVector operator +=(const ThreeVector & vectB)
	{
		_x += vectB._x;
		_y += vectB._y;
		_z += vectB._z;
		return *this;
	}
/** 
Create the additive inverse of a vector: \f$-\vec{a} = <-a_x,-a_y,-a_z>\f$
@returns a ThreeVector containing the additive inverse of this vector.
*/
	ThreeVector operator -(void) const
	{
		return ThreeVector(-_x,-_y,-_z);
	}
/** 
Subtract one vector from another: \f$\vec{a} - \vec{b} = <a_x - b_x,a_y - b_y, a_z - b_z>\f$.
@param vectB the vector to subtract from this vector.
@returns a ThreeVector with the result of the subtraction.
*/
	ThreeVector operator -(const ThreeVector & vectB) const
	{
		return *this + (-vectB);
	}
	ThreeVector operator -=(const ThreeVector & vectB)
	{
		return (*this += (-vectB));
	}
/** 
Scale the vector by a scalar factor: \f$s\vec{a} = <s x, s y, s z>\f$.
@param scalar the factor by which to scale the vector
@returns the scaled ThreeVector 
*/
	ThreeVector operator *(float scalar) const
	{
		return ThreeVector(_x * scalar,_y * scalar,_z * scalar);
	}
	ThreeVector & operator *=(float scalar)
	{
		_x *= scalar;
		_y *= scalar;
		_z *= scalar;
		return *this;
	}
/** 
Divide the vector by a scalar factor: \f$\dfrac{1}{s}\vec{a} = <\dfrac{x}{s}, \dfrac{y}{s}, \dfrac{z}{s}>\f$.
@param scalar the factor by which to divide the vector
@returns the scaled ThreeVector 
*/
	ThreeVector operator /(float scalar) const
	{
		return *this * (1.0 / scalar);
	}
	ThreeVector operator /=(float scalar)
	{
		return ((*this) *= (1.0 / scalar));
	}
/** 
Retrieve a scalar (dot) product for this vector: \f$\vec{a}\bullet\vec{b} = a_x b_x + a_y b_y + a_z b_z\f$
@returns the dot product 
*/
	float dot(const ThreeVector &vectB) const
	{
		return _x * vectB._x + _y * vectB._y + _z * vectB._z;
	}
/** 
Retrieve a vector (cross) product for this vector: \f$\vec{a}\times\vec{b} = <a_yb_z - a_zb_y,a_zb_x - a_xb_z,a_xb_y - a_yb_x>\f$
@returns the cross product as a ThreeVector
*/
	ThreeVector cross(const ThreeVector & vectB) const
	{
		return ThreeVector(_y * vectB._z - _z * vectB._y, _z * vectB._x - _x * vectB._z, _x * vectB._y - _y * vectB._x);
	}
/** 
Get the magnitude (length) of the vector
@returns the magnitude of the vector \f$(\sqrt{x^2 + y^2 + z^2})\f$
*/
	float magnitude(void)
	{
		return std::sqrt(dot(*this));
	}
	
/** 
Retrieve a unit vector for this vector
@returns the unit vector \f$(\dfrac{1}{\sqrt{x^2 + y^2 + z^2}})<x,y,z>\f$
*/
	ThreeVector unit(void)
	{
		float mag = magnitude();
		if (mag != 0.0)
			mag = 1.0 / mag;
		return ThreeVector(_x * mag,_y * mag,_z * mag);
	}
	/**
Load the vector with a zero vector
@returns none
*/
	void loadZero(void)
	{
		_x = _y = _z = 0.0;
	}
/**
Load the vector with a unit vector in the x direction
@returns none
*/
	void loadUnitX(void)
	{
		_x = 1.0;
		_y = _z = 0.0;
	}
/**
Load the vector with a unit vector in the y direction
@returns none
*/
	void loadUnitY(void)
	{
		_y = 1.0;
		_x = _z = 0.0;
	}
/**
Load the vector with a unit vector in the z direction
@returns none
*/
	void loadUnitZ(void)
	{
		_z = 1.0;
		_x = _y = 0.0;
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
		case 2:
			ret = _z;
			break;
		}
		return ret;
	}
};


#include "Vector2D.h"

Vector2D::Vector2D()
{
	x = 0;
	y = 0;
	magnitude = 0.0;
}

Vector2D::Vector2D(int VectorX, int VectorY)
{
	this->x = VectorX;
	this->y = VectorY;
	this->magnitude = 0.0;
}

Vector2D& Vector2D::Add(const Vector2D& vec)
{
	this->x += vec.x;
	this->y += vec.y;
	this->magnitude = magnitude;

	return *this;
}

Vector2D& Vector2D::Subtract(const Vector2D& vec)
{
	this->x -= x;
	this->y -= x;
	this->magnitude = magnitude;

	return *this;
}

Vector2D& Vector2D::Multiply(const Vector2D& vec)
{
	this->x *= x;
	this->y *= x;
	this->magnitude = magnitude;

	return *this;
}

Vector2D& Vector2D::Devide(const Vector2D& vec)
{
	this->x /= x;
	this->y /= x;
	this->magnitude = magnitude;

	return *this;
}

Vector2D& Vector2D::operator+=(const Vector2D& vec)
{
	return this->Add(vec);
}

Vector2D& Vector2D::operator-=(const Vector2D& vec)
{
	return this->Subtract(vec);
}

Vector2D& Vector2D::operator*=(const Vector2D& vec)
{
	return this->Multiply(vec);
}

Vector2D& Vector2D::operator/=(const Vector2D& vec)
{
	return this->Devide(vec);
}

#ifndef VECTOR2D_H
#define VECTOR2D_H

class Vector2D
{
public:
	Vector2D();
	Vector2D(int VectorX, int VectorY);

	Vector2D& Add(const Vector2D& vec);
	Vector2D& Subtract(const Vector2D& vec);
	Vector2D& Multiply(const Vector2D& vec);
	Vector2D& Devide(const Vector2D& vec);

	Vector2D& operator+=(const Vector2D& vec);
	Vector2D& operator-=(const Vector2D& vec);
	Vector2D& operator*=(const Vector2D& vec);
	Vector2D& operator/=(const Vector2D& vec);

	int x, y;
	float magnitude;
};
#endif // VECTOR2_H

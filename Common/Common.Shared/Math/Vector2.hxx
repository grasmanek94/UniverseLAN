#pragma once
#include "Math.hxx"

class Vector2
{
public:
	float x;
	float y;

	Vector2()
	{
		x = y = 0.0f;
	}

	Vector2(float _x, float _y)
	{
		x = _x; y = _y;
	}

	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(x, y);
	}

	bool IsEmpty() const
	{
		return (x == 0 && y == 0);
	}

	float Length() const
	{
		return sqrt(x * x + y * y);
	}

    float LengthSquared() const
    {
        return (x * x) + (y * y);
    }

    Vector2 operator + (const Vector2& right) const
    {
        return Vector2(x + right.x, y + right.y);
    }

    Vector2 operator - (const Vector2& right) const
    {
        return Vector2(x - right.x, y - right.y);
    }

    Vector2 operator * (const Vector2& right) const
    {
        return Vector2(x * right.x, y * right.y);
    }

    Vector2 operator * (float fRight) const
    {
        return Vector2(x * fRight, y * fRight);
    }

    Vector2 operator / (const Vector2& right) const
    {
        return Vector2(x / right.x, y / right.y);
    }

	Vector2 operator / (float right) const
    {
        float rcpValue = 1 / right;
        return Vector2(x * rcpValue, y * rcpValue);
    }

    Vector2 operator - () const
    {
        return Vector2(-x, -y);
    }

    void operator += (float fRight)
    {
        x += fRight;
        y += fRight;
    }

    void operator += (const Vector2& right)
    {
        x += right.x;
        y += right.y;
    }

    void operator -= (float fRight)
    {
        x -= fRight;
        y -= fRight;
    }

    void operator -= (const Vector2& right)
    {
        x -= right.x;
        y -= right.y;
    }

    void operator *= (float fRight)
    {
        x *= fRight;
        y *= fRight;
    }

    void operator *= (const Vector2& right)
    {
        x *= right.x;
        y *= right.y;
    }

    void operator /= (float fRight)
    {
        float fRcpValue = 1 / fRight;

        x *= fRcpValue;
        y *= fRcpValue;
    }

    void operator /= (const Vector2& right)
    {
        x /= right.x;
        y /= right.y;
    }

    bool operator== (const Vector2& param) const
    {
        return ((fabs(x - param.x) < FLOAT_EPSILON) &&
                (fabs(y - param.y) < FLOAT_EPSILON));
    }

    bool operator!= (const Vector2& param) const
    {
        return ((fabs(x - param.x) >= FLOAT_EPSILON) ||
                (fabs(y - param.y) >= FLOAT_EPSILON));
    }
};

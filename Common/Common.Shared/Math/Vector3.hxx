#pragma once
#include "Math.hxx"

class Vector3
{
public:
	float x;
	float y;
	float z;

	Vector3()
	{
		x = y = z = 0.0f;
	}

	Vector3(float _x, float _y, float _z)
	{
		x = _x; y = _y; z = _z;
	}

	template<class Archive>
	void serialize(Archive & ar)
	{
		ar(x, y, z);
	}

	bool IsEmpty() const
	{
		return (x == 0 && y == 0 && z == 0);
	}

	float Length() const
	{
		return sqrt(x * x + y * y + z * z);
	}

    float LengthSquared() const
    {
        return (x * x) + (y * y) + (z * z);
    }

	float DotProduct(const Vector3* param) const
    {
        return (x * param->x) + (y * param->y) + (z * param->z);
    }

    void CrossProduct(const Vector3* param) 
    { 
        float _x = x, _y = y, _z = z;

        x = y * param->z - param->y * z;
        y = z * param->x - param->z * x;
        z = x * param->y - param->x * y;
    }

	double Normalize()
    {
        double t = sqrt(x * x + y * y + z * z);

        if(t > 0.000001f)
        {
			double rcpt = 1 / t;

            x *= (float)rcpt;
            y *= (float)rcpt;
            z *= (float)rcpt;
        }
        else
		{
			x = y = z = 0.0f;

            t = 0;
		}

        return t;
    }

	Vector3 ToRotation() const
    {
        Vector3 vecRotation;
        vecRotation.z = atan2(y, x);
		Vector3 vecTemp(sqrt(x * x + y * y), z, 0);
        vecTemp.Normalize();
        vecRotation.y = atan2(vecTemp.x, vecTemp.y) - PI / 2;
        return vecRotation;
    }

	Vector3 GetOtherAxis() const
    {
		Vector3 result;

        if (abs(x) > abs(y))
	        result = Vector3(z, 0, -x);
        else
	        result = Vector3(0, -z, y);

        result.Normalize();
        return result;
    }

    Vector3 operator + (const Vector3& right) const
    {
        return Vector3(x + right.x, y + right.y, z + right.z);
    }

    Vector3 operator - (const Vector3& right) const
    {
        return Vector3(x - right.x, y - right.y, z - right.z);
    }

    Vector3 operator * (const Vector3& right) const
    {
        return Vector3(x * right.x, y * right.y, z * right.z);
    }

    Vector3 operator * (float fRight) const
    {
        return Vector3(x * fRight, y * fRight, z * fRight);
    }

    Vector3 operator / (const Vector3& right) const
    {
        return Vector3(x / right.x, y / right.y, z / right.z);
    }

	Vector3 operator / (float right) const
    {
        float rcpValue = 1 / right;
        return Vector3(x * rcpValue, y * rcpValue, z * rcpValue);
    }

    Vector3 operator - () const
    {
        return Vector3(-x, -y, -z);
    }

    void operator += (float fRight)
    {
        x += fRight;
        y += fRight;
        z += fRight;
    }

    void operator += (const Vector3& right)
    {
        x += right.x;
        y += right.y;
        z += right.z;
    }

    void operator -= (float fRight)
    {
        x -= fRight;
        y -= fRight;
        z -= fRight;
    }

    void operator -= (const Vector3& right)
    {
        x -= right.x;
        y -= right.y;
        z -= right.z;
    }

    void operator *= (float fRight)
    {
        x *= fRight;
        y *= fRight;
        z *= fRight;
    }

    void operator *= (const Vector3& right)
    {
        x *= right.x;
        y *= right.y;
        z *= right.z;
    }

    void operator /= (float fRight)
    {
        float fRcpValue = 1 / fRight;

        x *= fRcpValue;
        y *= fRcpValue;
        z *= fRcpValue;
    }

    void operator /= (const Vector3& right)
    {
        x /= right.x;
        y /= right.y;
        z /= right.z;
    }

    bool operator== (const Vector3& param) const
    {
        return ((fabs(x - param.x) < FLOAT_EPSILON) &&
                (fabs(y - param.y) < FLOAT_EPSILON) &&
                (fabs(z - param.z) < FLOAT_EPSILON));
    }

    bool operator!= (const Vector3& param) const
    {
        return ((fabs(x - param.x) >= FLOAT_EPSILON) ||
                (fabs(y - param.y) >= FLOAT_EPSILON) ||
                (fabs(z - param.z) >= FLOAT_EPSILON));
    }
};

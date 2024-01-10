#include "Float/float3.hpp"
#include "Matrix/matrix3.hpp"



float3::float3()
{
    x = y = z = 0;
}

float3::~float3()
{

}

float3::float3(float _x, float _y, float _z)
{
    x = _x;
    y = _y;
    z = _z;

}

float3::float3(float3 a, float3 b)
{
    x = b.x - a.x;
    y = b.y - a.y;
    z = b.z - a.z;
}


void float3::print() const
{
    std::cout << "{ " << this->x << " ; " << this->y << " ; " << this->z << "}\n";
}

void float3::print(std::string name) const
{
    std::cout << std::string(name) << " : { " << this->x << " ; " << this->y << " ; " << this->z << " }\n";
}


float3 float3::normalize() const
{
    float3 temp = { x, y, z };
    float l = temp.length();
    return float3(x / l, y / l, z / l);	// temp / l
}

float float3::length() const
{
    return sqrtf(x * x + y * y + z * z);
}

float float3::lengthSq() const
{
    return (x * x) + (y * y) + (z * z);
}

float float3::dist(float3 a, float3 b) const
{
    return (b - a).length();
}

/* rotate vector with angle in radians */
float3 float3::rotate(float XangleRad, float YangleRad, float ZangleRad) const
{
    float3 temp = { x, y, z };

    matrix3 rmX = matrix3::RotateX(XangleRad);
    matrix3 rmY = matrix3::RotateY(YangleRad);
    matrix3 rmZ = matrix3::RotateZ(ZangleRad);

    float3 result = (rmZ * rmY * rmX) * temp;
    return result;
}

float float3::dot(float3 a, float3 b)
{
    return a.x * b.x + a.y * b.y + a.z * b.z;
}

/* Note: I had troubles in the past with this function.The cross product only worked if I calculated it using a matrix,
 * so if weird results occur using cross product, always check here too. 
 */
float3 float3::cross(float3 a, float3 b)
{
    float3 temp(
        ((a.y * b.z) - (a.z * b.y)),
        ((a.z * b.x) - (a.x * b.z)),
        ((a.x * b.y) - (a.y * b.x))
    );
    return temp;
}

float3 float3::scaleMatrix3(float sx, float sy, float sz) const
{
    matrix3 scaleMat3(
        sx, 0, 0,
        0, sy, 0,
        0, 0, sz
    );
    float3 temp = { x, y, z };
    float3 result = scaleMat3 * temp;
    return result;
}


#pragma region Point related

/* returns center gravity point of triangle abc */
float3 float3::isobaryCenterTriangle(float3 a, float3 b, float3 c)
{
    float Xi = (1.f / 3.f) * (a.x + b.x + c.x);
    float Yi = (1.f / 3.f) * (a.y + b.y + c.y);
    float Zi = (1.f / 3.f) * (a.z + b.z + c.z);
    return { Xi, Yi, Zi };
}

/* returns center point of circle going through all corners of triangle abc*/
float3 float3::circumcenterTriangle(float3 a, float3 b, float3 c)
{
    // TODO

    //float3 P1;
    //float3 P2;
    //float3 P3;

    //P1.x = a.x;
    //P1.y = a.y;
    //P1.z = a.z;

    //P2.x = b.x;
    //P2.y = b.y;
    //P2.z = b.z;

    //P3.x = c.x;
    //P3.y = c.y;
    //P3.z = c.z;

    //float rNUM = length(P1 - P2) * length(P2 - P3) * length(P3 - P1);
    //float rDENUM = 2 * (length(crossProductVector3(substractVector3(P1, P2), substractVector3(P2, P3))));
    //float r = rNUM / rDENUM;

    //float commomDENUM = 2 * powf(normVector3(crossProductVector3(substractVector3(P1, P2), substractVector3(P2, P3))), 2.0);

    //float alphaNUM = powf(normVector3(substractVector3(P2, P3)), 2.0) * (dotProductVector3(substractVector3(P1, P2), substractVector3(P1, P3)));
    //float alpha = alphaNUM / commomDENUM;

    //float betaNUM = powf(normVector3(substractVector3(P1, P3)), 2.0) * (dotProductVector3(substractVector3(P2, P1), substractVector3(P2, P3)));
    //float beta = betaNUM / commomDENUM;

    //float gammaNUM = powf(normVector3(substractVector3(P1, P2)), 2.0) * (dotProductVector3(substractVector3(P3, P1), substractVector3(P3, P2)));
    //float gamma = gammaNUM / commomDENUM;

    //Point3 toCenter;
    //toCenter.x = alpha * P1.x + beta * P2.x + gamma * P3.x;
    //toCenter.y = alpha * P1.y + beta * P2.y + gamma * P3.y;
    //toCenter.z = alpha * P1.z + beta * P2.z + gamma * P3.z;

    //return toCenter;

    return { 0, 0, 0 };

}

#pragma endregion Point related


#pragma region Operators

float3 operator+(float3 a, float b)
{
    return { a.x + b, a.y + b, a.z + b };
}

float3 operator-(float3 a, float b)
{
    return { a.x - b, a.y - b, a.z - b };
}

float3 operator*(float3 a, float s)
{
    return { a.x * s, a.y * s, a.z * s };
}

float3 operator/(float3 a, float s)
{
    return { a.x / s, a.y / s, a.z / s };
}

float3 operator+(float3 a, float3 b)
{
    return { a.x + b.x, a.y + b.y, a.z + b.z };
}

float3 operator-(float3 a, float3 b)
{
    return { a.x - b.x, a.y - b.y, a.z - b.z };
}
float3 operator*(float3 a, float3 b)
{
    return { a.x * b.x, a.y * b.y, a.z * b.z };
}

float3 operator*(matrix3 a, float3 b)
{
    return {
        a.data[0][0] * b.x + a.data[0][1] * b.y + a.data[0][2] * b.z,
        a.data[1][0] * b.x + a.data[1][1] * b.y + a.data[1][2] * b.z,
        a.data[2][0] * b.x + a.data[2][1] * b.y + a.data[2][2] * b.z
    };
}


std::ostream& operator<<(std::ostream& os, const float3& f)
{
    return os << "{ " << f.x << " ; " << f.y << " ; " << f.z << " }\n";
}

#pragma endregion Operators
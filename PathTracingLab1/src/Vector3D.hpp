#ifndef _VECTOR3D_HPP_
#define _VECTOR3D_HPP_

#include <bits/stdc++.h>
#include "json/CJsonObject.hpp"

struct Vector3D
{
    double x, y, z;

    Vector3D() : x(0), y(0), z(0)
    {
        return;
    }

    Vector3D(double x_, double y_, double z_) : x(x_), y(y_), z(z_)
    {
        return;
    }

    Vector3D(const Vector3D &src) : x(src.x), y(src.y), z(src.z)
    {
        return;
    }

    friend Vector3D operator+(const Vector3D &lhs, const Vector3D &rhs)
    {
        return {lhs.x + rhs.x, lhs.y + rhs.y, lhs.z + rhs.z};
    }

    friend Vector3D operator-(const Vector3D &lhs, const Vector3D &rhs)
    {
        return {lhs.x - rhs.x, lhs.y - rhs.y, lhs.z - rhs.z};
    }

    Vector3D operator+=(const Vector3D &rhs)
    {
        (*this).x += rhs.x;
        (*this).y += rhs.y;
        (*this).z += rhs.z;
        return *this;
    }

    Vector3D operator-=(const Vector3D &rhs)
    {
        (*this).x -= rhs.x;
        (*this).y -= rhs.y;
        (*this).z -= rhs.z;
        return *this;
    }

    friend Vector3D operator*(const Vector3D &lhs, double rhs)
    {
        return {lhs.x * rhs, lhs.y * rhs, lhs.z * rhs};
    }

    Vector3D operator*=(double rhs)
    {
        (*this).x *= rhs;
        (*this).y *= rhs;
        (*this).z *= rhs;
        return *this;
    }

    friend Vector3D operator*(double lhs, const Vector3D &rhs)
    {
        return {rhs.x * lhs, rhs.y * lhs, rhs.z * lhs};
    }

    friend Vector3D operator/(const Vector3D &lhs, double rhs)
    {
        return {lhs.x / rhs, lhs.y / rhs, lhs.z / rhs};
    }

    Vector3D operator/=(double rhs)
    {
        (*this).x /= rhs;
        (*this).y /= rhs;
        (*this).z /= rhs;
        return *this;
    }

    friend Vector3D Directmult(const Vector3D &lhs, const Vector3D &rhs)
    {
        return {lhs.x * rhs.x, lhs.y * rhs.y, lhs.z * rhs.z};
    }

    Vector3D Directmult(const Vector3D &rhs)
    {
        Vector3D res;
        res.x *= rhs.x;
        res.y *= rhs.y;
        res.z *= rhs.z;
        return res;
    }

    friend double Dot(const Vector3D &lhs, const Vector3D &rhs)
    {
        return lhs.x * rhs.x + lhs.y * rhs.y + lhs.z * rhs.z;
    }

    double Dot(const Vector3D &rhs)
    {
        return x * rhs.x + y * rhs.y + z * rhs.z;
    }

    friend Vector3D Cross(const Vector3D &lhs, const Vector3D &rhs)
    {
        Vector3D res;
        res.x += lhs.y * rhs.z;
        res.y += lhs.z * rhs.x;
        res.z += lhs.x * rhs.y;
        res.z -= lhs.y * rhs.x;
        res.y -= lhs.x * rhs.z;
        res.x -= lhs.z * rhs.y;
        return res;
    }

    Vector3D Cross(const Vector3D &rhs)
    {
        Vector3D res;
        res.x += (*this).y * rhs.z;
        res.y += (*this).z * rhs.x;
        res.z += (*this).x * rhs.y;
        res.z -= (*this).y * rhs.x;
        res.y -= (*this).x * rhs.z;
        res.x -= (*this).z * rhs.y;
        return res;
    }

    double Norm()
    {
        return sqrt((*this).x * (*this).x + (*this).y * (*this).y + (*this).z * (*this).z);
    }

    friend double Norm(const Vector3D &opd)
    {
        return sqrt(opd.x * opd.x + opd.y * opd.y + opd.z * opd.z);
    }

    Vector3D operator-()
    {
        return {-(*this).x, -(*this).y, -(*this).z};
    }

    friend Vector3D operator-(const Vector3D &opd)
    {
        return {-opd.x, -opd.y, -opd.z};
    }

    jsonobj::CJsonObject ToJsonObject()
    {
        jsonobj::CJsonObject jsonobj;
        jsonobj.Add("x",this->x);
        jsonobj.Add("y",this->y);
        jsonobj.Add("z",this->z);
        return jsonobj;
    }

    friend jsonobj::CJsonObject ToJsonObject(const Vector3D &opd)
    {
        jsonobj::CJsonObject jsonobj;
        jsonobj.Add("x",opd.x);
        jsonobj.Add("y",opd.y);
        jsonobj.Add("z",opd.z);
        return jsonobj;
    }

    void FromJsonObject(const std::string &str)
    {
        jsonobj::CJsonObject jsonobj;
        jsonobj.Parse(str);
    }
};

#endif
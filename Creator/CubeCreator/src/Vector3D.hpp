#ifndef _VECTOR3D_HPP_
#define _VECTOR3D_HPP_

#include <bits/stdc++.h>
#include "Json.hpp"

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

    Vector3D(const cjsonobj::CJsonObject &jsonobj)
    {
        FromJsonObject(jsonobj);
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
        Vector3D res = *this;
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

    Vector3D Unit()
    {
        double norm = Norm();
        return {x / norm, y / norm, z / norm};
    }

    Vector3D operator-()
    {
        return {-(*this).x, -(*this).y, -(*this).z};
    }

    friend Vector3D operator-(const Vector3D &opd)
    {
        return {-opd.x, -opd.y, -opd.z};
    }

    cjsonobj::CJsonObject ToJsonObject()
    {
        cjsonobj::CJsonObject jsonobj;
        jsonobj.Add("x", this->x);
        jsonobj.Add("y", this->y);
        jsonobj.Add("z", this->z);
        return jsonobj;
    }

    friend cjsonobj::CJsonObject ToJsonObject(const Vector3D &opd)
    {
        cjsonobj::CJsonObject jsonobj;
        jsonobj.Add("x", opd.x);
        jsonobj.Add("y", opd.y);
        jsonobj.Add("z", opd.z);
        return jsonobj;
    }

    void FromJsonObject(const cjsonobj::CJsonObject &jsonobj)
    {
        jsonobj.Get("x", x);
        jsonobj.Get("y", y);
        jsonobj.Get("z", z);
    }

    friend Vector3D Vector3DFromJsonObject(const cjsonobj::CJsonObject &jsonobj)
    {
        Vector3D ans;
        jsonobj.Get("x", ans.x);
        jsonobj.Get("y", ans.y);
        jsonobj.Get("z", ans.z);
        return ans;
    }

    friend cjsonobj::CJsonObject ToJsonObject(Vector3D &opd, const std::string &str)
    {
        cjsonobj::CJsonObject jsonobj;
        jsonobj.Parse(str);
        jsonobj.Get("x", opd.x);
        jsonobj.Get("y", opd.y);
        jsonobj.Get("z", opd.z);
        return jsonobj;
    }

    friend cjsonobj::CJsonObject ToJsonObject(const std::string &str, Vector3D &opd)
    {
        cjsonobj::CJsonObject jsonobj(str);
        jsonobj.Get("x", opd.x);
        jsonobj.Get("y", opd.y);
        jsonobj.Get("z", opd.z);
        return jsonobj;
    }

    friend std::istream &operator>>(std::istream &lhs, Vector3D &rhs)
    {
        std::string jsonstr;
        lhs >> jsonstr;
        rhs.FromJsonObject(jsonstr);
        return lhs;
    }

    friend std::ostream &operator<<(std::ostream &lhs, Vector3D rhs)
    {
        std::string jsonstr = rhs.ToJsonObject().ToString();
        lhs << jsonstr;
        return lhs;
    }

    bool operator==(const Vector3D &rhs)
    {
        return abs(x - rhs.x) < 1e-6 && abs(y - rhs.y) < 1e-6 && abs(z - rhs.z) < 1e-6;
    }

    bool operator!=(const Vector3D &rhs)
    {
        return !(*this == rhs);
    }

    double Average() const
    {
        return (x + y + z) / 3;
    }
};

typedef Vector3D Vertex3D;
typedef Vector3D Point3D;
typedef Point3D Point;
typedef Vector3D Radiance3;

#endif
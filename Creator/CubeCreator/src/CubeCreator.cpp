#include <bits/stdc++.h>
using namespace std;

#include "Json.hpp"
#include "Vector3D.hpp"
#include "Material.hpp"
#include "Ray.hpp"
#include "Plane.hpp"
#include "Scene.hpp"
#include "Triangle.hpp"

vector<Triangle> CreateRectangle(Point3D p0, Point3D p1, Point3D p2, Point3D p3, Material material)
{
    return vector<Triangle>{Triangle(p0, p1, p2, material), Triangle(p2, p3, p0, material)};
}

void Append(vector<Triangle> &vec, vector<Triangle> tmp)
{
    for (auto t : tmp)
    {
        vec.push_back(t);
    }
}

int main(int argc, char *argv[])
{
    cout << "Cube Creator ... Hello !" << endl;

    if (argc <= 6)
    {
        cerr << "Invalid parameter list!" << endl;
        return 0;
    }

    // 坐标预处理

    char *argv_x[2] = {argv[1], argv[2]};
    char *argv_y[2] = {argv[3], argv[4]};
    char *argv_z[2] = {argv[5], argv[6]};

    Point3D p[2][2][2];
    for (int i = 0; i < 2; i++)
    {
        for (int j = 0; j < 2; j++)
        {
            for (int k = 0; k < 2; k++)
            {
                p[i][j][k] = Point3D(atof(argv_x[i]), atof(argv_y[j]), atof(argv_z[k]));
            }
        }
    }

    // 材质读取预处理
    Material material = MaterialFromJsonObject(ReadJSON("material.json"));

    vector<Triangle> vec;

    Append(vec, CreateRectangle(p[0][0][0], p[0][0][1], p[0][1][1], p[0][1][0], material));
    Append(vec, CreateRectangle(p[1][0][0], p[1][1][0], p[1][1][1], p[1][0][1], material));

    Append(vec, CreateRectangle(p[0][0][0], p[0][0][1], p[1][0][1], p[1][0][0], material));
    Append(vec, CreateRectangle(p[0][1][0], p[1][1][0], p[1][1][1], p[0][1][1], material));

    Append(vec, CreateRectangle(p[0][0][0], p[0][1][0], p[1][1][0], p[1][0][0], material));
    Append(vec, CreateRectangle(p[0][0][1], p[1][0][1], p[1][1][1], p[0][1][1], material));

    Scene scene;
    scene.FromJsonObject(ReadJSON("scene.json"));

    for (auto t : vec)
    {
        scene.Push(t);
    }

    WriteJSON("scene.json", scene.ToJsonObject());

    cout << "Succeed !" << endl;

    return 0;
}

#include <bits/stdc++.h>
#include "../json/CJsonObject.hpp"
#include "../Vector3D.hpp"

void moduleTest_Vector3D()
{
    std::cout<<"Run test for Vector3D"<<std::endl;

    using namespace std;
    {
        Vector3D vec;
        cout<<vec<<endl;
    }

    {
        Vector3D vec(1,2,3);
        cout<<vec<<endl;
    }

    {
        Vector3D vec(1,1,1);
        cout<<(vec+Vector3D(0,1,2))<<endl;
        cout<<(vec-Vector3D(0,1,2))<<endl;
        cout<<(vec.Directmult(Vector3D(0,1,2)))<<endl;
        cout<<(vec.Dot(Vector3D(0,1,2)))<<endl;
        cout<<(vec.Cross(Vector3D(0,1,2)))<<endl;
    }

    {
        
    }


}
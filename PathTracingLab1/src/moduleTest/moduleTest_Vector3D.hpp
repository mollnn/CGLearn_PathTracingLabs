#ifndef _MODULETEST_VECTOR3D_HPP_
#define _MODULETEST_VECTOR3D_HPP_

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
        cout<<endl;
    }

    {
        Vector3D vec(1,2,3);
        cout<<vec<<endl;
        cout<<endl;

    }

    {
        Vector3D vec(1,1,1);
        cout<<(vec+Vector3D(0,1,2))<<endl;
        cout<<(vec-Vector3D(0,1,2))<<endl;
        cout<<(vec.Directmult(Vector3D(0,1,2)))<<endl;
        cout<<(vec.Dot(Vector3D(0,1,2)))<<endl;
        cout<<(vec.Cross(Vector3D(0,1,2)))<<endl;
        // 1 1 1
        // 0 1 2 
        // => (1, -2, 1)
        cout<<(vec*2)<<endl;
        cout<<endl;

    }

    {
        Vector3D vec(0,0,0);
        cout<<(vec+=Vector3D(1,2,3))<<endl;
        cout<<(vec-=-Vector3D(1,2,3))<<endl;
        cout<<(vec*=2)<<endl;
        cout<<endl;

    }


}

#endif
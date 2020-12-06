#include <bits/stdc++.h>

#include "Vector3D.hpp"
#include "Material.hpp"
#include "Ray.hpp"
#include "Sphere.hpp"
#include "Scene.hpp"

void module_test_scene_test()
{
    Scene scene(Sphere(Vector3D(0,0,0),1));
    std::cout<<scene.ToJsonObject().ToString()<<std::endl;
    scene.Push(Sphere(Vector3D(1,1,1),2));
    std::string tmp=scene.ToJsonObject().ToString();
    std::cout<<scene.ToJsonObject().ToString()<<std::endl;
    cjsonobj::CJsonObject jsonobj;
    jsonobj.Parse(tmp);
    Scene scene_rev=SceneFromJsonObject(jsonobj);
    std::cout<<scene_rev.ToJsonObject().ToString()<<std::endl;
}

int main()
{
    module_test_scene_test();
}
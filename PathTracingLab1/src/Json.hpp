#ifndef _JSON_HPP_
#define _JSON_HPP_

#include "json/CJsonObject.hpp"
#include <bits/stdc++.h>

void ReadJSON(std::string filename, cjsonobj::CJsonObject &jsonobj)
{
    std::ifstream jsonifs(filename);
    std::stringstream jsonifs_buffer;
    jsonifs_buffer << jsonifs.rdbuf();
    std::string jsonstr_scene(jsonifs_buffer.str());
    jsonobj.Parse(jsonstr_scene);
}

cjsonobj::CJsonObject ReadJSON(std::string filename)
{
    cjsonobj::CJsonObject jsonobj;
    ReadJSON(filename, jsonobj);
    return jsonobj;
}

void WriteJSON(std::string filename, const cjsonobj::CJsonObject &jsonobj)
{
    std::ofstream jsonofs(filename);
    jsonofs << jsonobj.ToFormattedString();
}


#endif
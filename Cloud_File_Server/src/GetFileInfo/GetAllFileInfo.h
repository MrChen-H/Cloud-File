#pragma once
#include <fcgiapp.h>
#include <iostream>
#include <vector>
#include <fstream>
#include <cstring>
#include <fcntl.h>
#include <errno.h>
#include <sys/types.h>
#include <wait.h>
#include "json.hpp"
#include "fcgi_stdio.h"
#include "fcgio.h"
#include "fcgiapp.h"
#include "db_opteration.hpp"
#include "File_Info.hpp"
using json = nlohmann::json;
std::string GetPathInfo(int Data_size, FCGX_Stream *data_strean,std::string& path_info)
{
    auto fileInfoarray = FileInfoArray::getInstance();
    fileInfoarray->updateInfo();
    auto fileInfo = fileInfoarray->getFileInfoArray();

    json res_json;

    for(auto info : fileInfo)
    {
        res_json[info.id.second][info.file_name.first] = info.file_name.second;
        res_json[info.id.second][info.id.first] = info.id.second;
        res_json[info.id.second][info.file_size.first] = info.file_size.second;
        res_json[info.id.second][info.type_name.first] = info.type_name.second;
        res_json[info.id.second][info.type_comment.first] = info.type_comment.second;
        res_json[info.id.second][info.file_dir.first] = info.file_dir.second;
    }
    if(res_json.empty())
    {
        return "";
    }
    return res_json.dump();
}
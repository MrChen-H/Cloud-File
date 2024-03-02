#pragma once
#include <fcgiapp.h>
#include <spdlog/sinks/rotating_file_sink.h>
#include <spdlog/sinks/base_sink.h>
#include <spdlog/spdlog.h>
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

bool testFunc(int data_len, FCGX_Stream *data_stream)
{

    if (spdlog::get("Upload_logger") == nullptr) // 如果不存在名为 Delete_File 的日志管理器则创建
    {
        auto logger_db = spdlog::rotating_logger_mt("Upload_logger", "./Upload.log", 1024 * 1024 * 3, 3); // 初始化日志
        logger_db->flush_on(spdlog::level::trace);
    }
    auto logger = spdlog::get("Upload_logger");
    std::vector<std::string> data_arr;//存放数据的数组
    std::string one_line_data;//单行数据

    int index = 0;//数据总行数
    for (int i = 0; i < data_len;i++)
    {
        int bytes = FCGX_GetChar(data_stream); // 读取所有数据
        one_line_data += (char)bytes;
        if((char)bytes == '\n')//遇到换行
        {
            data_arr.push_back(one_line_data);//加入到数组中
            index++;
            one_line_data.clear();//清除单行数据
        }
        
    }
   
    for(auto it : data_arr)
    {
        if(it =="\r\n")
        {
            break;
        }
    }
    std::string Boundary; // 边界字符
    for(auto it : data_arr[0])
    {
        if(it == '\r')
        {
            break;
        }
        Boundary += it;
    }
    std::string fileName;
    for (int i = data_arr[1].find("filename")+10; i < data_len;i++)//获取文件名
    {
        if(data_arr[1][i] == '"')
        {
            break;
        }
        fileName += data_arr[1][i];
    }
    // 创建目录
    std::filesystem::path dirPath("../userFile");
    if (!std::filesystem::exists(dirPath)) 
    {
        std::filesystem::create_directories(dirPath);
    }

    // 然后尝试打开文件
    std::ofstream file(dirPath/fileName,std::ios::out | std::ios::binary);
    if (!file) 
    {
        logger->info("Open file {} filed!",std::string(dirPath/fileName));
        file.close();
        return false;
    }
    
    for (int i = 3; i < index; i++)//提取文件内容
    {
        if (data_arr[i].find(Boundary)!=std::string::npos)
        {
            continue;
        }
        for(auto it : data_arr[i])
        {
            file << it;
            
        }
        
        
    }
    file.close();
    return true;
}
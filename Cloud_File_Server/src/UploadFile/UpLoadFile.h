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

std::string testFunc(int Data_size, FCGX_Stream *data_strean,std::string& path_info)
{
    if (spdlog::get("file_logger") == nullptr) // 如果不存在名为 Delete_File 的日志管理器则创建
    {
        auto logger_db = spdlog::rotating_logger_mt("file_logger", "../../logs/basic-log.txt", 1024 * 1024 * 3, 3); // 初始化日志
        logger_db->flush_on(spdlog::level::trace);
        logger_db->set_level(spdlog::level::info);
    }
    auto logger_db = spdlog::get("file_logger");
    logger_db->info("Data_size is {}", path_info);

    return std::string();
}
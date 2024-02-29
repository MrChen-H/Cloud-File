#pragma once

#include <iostream>
#include "db_opteration.hpp"
#include "vector"
const std::string GET_ALL_FILE_INFO_QUERY = \
"select \
    tf.id,\
    tf.file_name,\
    tf.file_size,\
    tf.file_dir,\
    ts.suffix,\
    tt.type_name,\
    tt.type_comment \
from t_file_info as tf,t_file_type as tt,t_suffix_indx as ts \
where tf.file_type = tt.type_id and tf.file_suffix = ts.suffix_id";

//File info struct
struct FileInfo
{
    std::pair<std::string, std::string> id;
    std::pair<std::string, std::string> file_name;
    std::pair<std::string, std::string> file_size;
    std::pair<std::string, std::string> file_dir;
    std::pair<std::string, std::string> suffix;
    std::pair<std::string, std::string> type_name;
    std::pair<std::string, std::string> type_comment;
};

class FileInfoArray {
public:
    static FileInfoArray *instance;
    static FileInfoArray *getInstance() {
        return instance;
    }
    void updateInfo();
    std::vector<FileInfo> getFileInfoArray() const {return this->file_type_info;}
private:
    FileInfoArray();
    std::vector<FileInfo> file_type_info;

};

FileInfoArray* FileInfoArray::instance = new FileInfoArray();
FileInfoArray::FileInfoArray() {
    this->updateInfo();
}
void FileInfoArray::updateInfo() {
    auto sql_opt = Db_Operation::getInstance();

    std::vector<std::string> file_info;
    std::string query = GET_ALL_FILE_INFO_QUERY;
    std::string errorString;
    sql_opt->execute(query,errorString);
    MYSQL_RES* sql_res = sql_opt->getMysqlResult();
    int num = mysql_num_fields(sql_res);
    
    MYSQL_FIELD * fields = mysql_fetch_fields(sql_res);

    MYSQL_ROW row;
    while( (row = mysql_fetch_row(sql_res)) != NULL)
    {
        // 将当前行中的每一列信息读出
        FileInfo info;
        info.id.first = fields[0].name;
        info.id.second = row[0];

        info.file_name.first = fields[1].name;
        info.file_name.second = row[1];

        info.file_size.first = fields[2].name;
        info.file_size.second = row[2];

        info.file_dir.first = fields[3].name;
        info.file_dir.second = row[3];

        info.suffix.first = fields[4].name;
        info.suffix.second = row[4];

        info.type_name.first = fields[5].name;
        info.type_name.second = row[5];

        info.type_comment.first = fields[6].name;
        info.type_comment.second = row[6];

        file_type_info.push_back(info);
    }
}

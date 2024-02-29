#pragma once

#include "./mysql/mysql.h"

class Db_Operation
{
private:
    Db_Operation();
public:
    static Db_Operation* getInstance();
    bool execute(const std::string& sql,std::string& errorString);
    MYSQL_RES* getMysqlResult();
    
private:
    ~Db_Operation();

    static Db_Operation* instance;
    MYSQL* mysql=nullptr;
};

Db_Operation* Db_Operation::instance = new Db_Operation();


Db_Operation::~Db_Operation()
{
    if(mysql!=nullptr)
    {
        delete mysql;
        mysql = nullptr;
    }
    mysql_close(mysql);
}

Db_Operation::Db_Operation() {

    /// init mysql
    mysql = mysql_init(NULL);
    if (mysql == NULL) {
        /// Need log in here
        // printf("mysql init error\n");
        return;
    }
    /// connect to Cloud_File_Server_DB Here need Config file
    if (mysql_real_connect(mysql, "127.0.0.1", "root", "chh20020729", "Cloud_File_Server_DB", 0, NULL, 0) == NULL) 
    {
        /// Need log in here
        return;
    }
    /// set character to utf8
    mysql_set_character_set(mysql, "utf8");
}

Db_Operation* Db_Operation::getInstance()
{
    return instance;
}

bool Db_Operation::execute(const std::string& sql,std::string& errorString) 
{
    if (mysql_query(mysql, sql.c_str()) != 0) 
    {
        return false;
    }
    return true;
}

MYSQL_RES* Db_Operation::getMysqlResult()
{
    return mysql_store_result(mysql);
}
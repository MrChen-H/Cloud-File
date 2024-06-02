#!/bin/bash

# 设置数据库环境变量
export DB_NAME="Cloud_File_Server_DB"   #数据库名,该名称的数据库必须存在
export DB_USER="root"                   #数据库账户名,该账户需要拥有可以创建数据表的权限
export DB_PASSWORD="root"               #数据库账户密码
export DB_HOST="localhost"            #数据库ip
export DB_PORT="3306"       

#创建数据库迁移文件,并应用迁移文件(创建数据库表)
python3 manage.py makemigrations
python3 manage.py migrate

python3 manage.py runserver 0.0.0.0:8000
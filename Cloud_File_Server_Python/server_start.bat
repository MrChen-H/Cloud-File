@echo off

:: 设置数据库环境变量
set DB_NAME=Cloud_File_Server_DB   ::数据库名,该名称的数据库必须存在
set DB_USER=root                  ::数据库账户名,该账户需要拥有可以创建数据表的权限
set DB_PASSWORD=root              ::数据库账户密码
set DB_HOST=localhost             ::数据库ip
set DB_PORT=3306                 ::数据库端口

:: 创建数据库迁移文件,并应用迁移文件(创建数据库表)
python manage.py makemigrations
python manage.py migrate

:: 启动Django服务
python manage.py runserver 0.0.0.0:8000
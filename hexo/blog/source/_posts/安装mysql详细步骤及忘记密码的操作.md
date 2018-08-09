---
title: 安装mysql详细步骤及忘记密码的操作
date: 2018-08-03 13:19:48
tags:
	- mysql
categories: 基础
---

## **第一部分** **:**  **windows下安装及启动**

 MySQL 下载地址为： [MySQL 下载](https://dev.mysql.com/downloads/mysql/).  

![img](安装mysql详细步骤及忘记密码的操作\1.png) 

![img](安装mysql详细步骤及忘记密码的操作\2.png) 

点击 Download 按钮进入下载页面，点击下图中的 No thanks, just start my download. 就可立即下载;

下载完后，将 zip 包解压到相应的目录 ;

一定要以管理员身份打开 cmd 命令行工具，然后切换目录到安装目录，

输入安装命令：

> mysqld install

启动输入以下命令即可： 

> net start mysql

注意: 在 5.7 需要初始化 data 目录：

```
cd C:\web\mysql-8.0.11\bin 
mysqld --initialize-insecure 
```

初始化后再运行 net start mysql 即可启动 mysql。

## **MySQL 重置密码** 

### 一、

如果你忘记 MySQL 密码，可以通过修改 my.cnf 文件添加 skip-grant-tables 来重置密码，步骤如下：

**1、打开 my.cnf 配置文件，找到 [mysqld] ，然后在该行下面添加以下参数：**

![img](安装mysql详细步骤及忘记密码的操作\3.jpg) 

重启 MySQL 服务：

```
service mysql restart
```

登录 MySQL，此时不需要密码，直接回车:

```
# mysql -u root -p
```

更改 **root** 密码 为 **123456**：

```
mysql> use mysql;
mysql>  update user set authentication_string=password("123456") where user='root';
mysql> flush privileges;  # 刷新权限
```

注意密码字段名 5.7 版本的是 **authentication_string**，之前的为 **password**。

修改完后，记得注释掉 **my.cnf** 中的 skip-grant-tables 参数，重启 MySQL 服务，就可以用你设置的密码登录了。

### 二、

关闭 MySQL 服务器：

```
service mysql stop
```

进入目录，以安全模式启动 MySQL

```
cd /usr/local/mysql/bin  
./mysqld_safe --skip-grant-tables & 
```

> **注意：**
>
> 可能你的系统没有 safe_mysqld 程序(Windows 或 Ubuntu操作系统) ,可以使用 mysqld：
>
> ```
> mysqld --skip-grant-tables &
> ```

启动后， root 用户以空密码登录 mysql：

```
# mysql -u root

mysql> update mysql.user set password=PASSWORD('123456') where User='root';   # 修改密码
mysql> flush privileges;  # 刷新权限
mysql> quit 
```

启动 MySQL：

```
service mysql start
```

这是就可以使用新密码 **123456** 登录了。

如果你知道密码，可以使用以下命令：

```
# mysqladmin -u root -p password 新密码
```
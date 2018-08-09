---
title: mysql5.5压缩包安装辛酸历程
date: 2018-08-09 09:42:39
tags:
	- mysql
categories: 基础
---

接上篇：[安装mysql详细步骤及忘记密码的操作](http://www.ilcyz.com/2018/08/03/%E5%AE%89%E8%A3%85mysql%E8%AF%A6%E7%BB%86%E6%AD%A5%E9%AA%A4%E5%8F%8A%E5%BF%98%E8%AE%B0%E5%AF%86%E7%A0%81%E7%9A%84%E6%93%8D%E4%BD%9C/)

上篇安装mysql 8并没有成功，使用时出现一些问题，所以打算删除mysql 8，但是！！，千万不要想着删除mysql的时候只删除文件夹就万事大吉了，因为你会发现，删除了文件夹以后就找不到mysql文件了，在卸载软件的地方也没有了，但是电脑上却真真正正地存在着mysqld服务，删除也删除不掉。本文就在卸载mysql 8，并重新安装mysql 5.5的排坑过程做详细记录。

## 卸载MySQL 8.0

如果你不小心地，抱着删除了MySQL文件夹就万事大吉的心态把MySQL文件夹删除掉了，并且它还顽强地存在在你的电脑中，宛如挥之不去的噩梦一样，折磨着你脆弱幼小的心灵，那么本篇文章将讲述不用重装系统就可以完美解决这个问题的有效办法。

注：编者是手动删除了mysql解压后的文件的基础上进行卸载的 

### 1、

进入“服务”：

开始->运行->服务

或者其他方式

### 2、

暂停或停止mysql服务 

### 3、

进入注册表（regedit）：

开始->运行->regedit

或者

其他方式

### 4、

删除注册表中与mysql有关的内容：

1）HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Services\EventLog\Application\MySQL

2）HKEY_LOCAL_MACHINE\SYSTEM\ControlSet001\Services\MySQL

3）HKEY_LOCAL_MACHINE\SYSTEM\ControlSet002\Services\EventLog\Application\MySQL

4）HKEY_LOCAL_MACHINE\SYSTEM\ControlSet002\Services\MySQL

5）HKEY_LOCAL_MACHINE\SYSTEM\CurrentControlSet\Services\MySQL

一般在上述里面有有关mysql的注册表

没有就不用理会

### 5、

以管理员方式启动cmd：

开始->运行->鼠标右键->以管理员身份运行

### 6、

进入准备安装的MySQL的bin目录：

输入mysqld -remove或者mysqld -nt -remove命令 

显示successfully，并且“服务”里面没有MySQL，则说明已彻底卸载 

## **安装MySQL 5.5**

终于把噩梦清理干净了，就开始正式地安装心心念念的MySQL5.5咯。

### 下载MySQL压缩版，并配置环境变量

到官网下载mysql-5.5.10-win32.zip，然后将mysql解压到任意路径，如：C:\mysql-5.5.10-win32

打开计算机->属性->高级系统设置->环境变量，新建一个环境变量，变量名为：MYSQL_HOME，变量值为你的mysql根目录，如：C:\mysql-5.5.10-win32 
然后在系统变量Path中添加：;%MYSQL_HOME%\bin

### 修改MySQL配置文件

在此处百度到的所有都有配置一个my.ini文件，此处并不知道为什么要新建这么一个文件，声明：我的电脑上新建文件后

在启动MySQL的时候会报 1067的错误，所以，此处列出配置文件，若启动时出错删除即可。

在根目录下面有几个已经写好的”my-“开头的ini文件，选一个适合你的，如：my-small.ini。复制一份，将文件名修改为my.ini，添加以下内容： 

> [mysqld] 
> default-character-set = utf8 
> basedir = C:/mysql-5.5.10-win32 
> datadir = C:/mysql-5.5.10-win32/data
>
> [client] 
> default-character-set = utf8
>
> [WinMySQLadmin] 
> Server = C:/mysql-5.5.10-win32/bin/mysqld.exe

### 安装 

打开命令提示符，进入%MYSQL_HOME%/bin目录，  执行命令：mysqld -install将mysql安装到windows的服务。  执行成功后会提示：C:\mysql-5.5.10-win32\bin>Service successfully installed.  如果想要卸载服务执行命令：mysqld -remove。 

### 启动MySQL服务

然后在命令提示符下执行：net start mysql就能启动mysql了，停止服务输入命令：net stop mysql。如果想设置mysql是否自动启动，可以在开始菜单->运行中输入service.msc打开服务管理进行设置。

### 首次连接

在命令行输入

> mysql

若显示如下图，则安装是成功的

![安装成功](mysql压缩包安装辛酸历程\1.png)

新开一个命令行，cd到bin目录下，输入

> mysql -u root mysql

可以进入到mysql

输入下述命令修改密码

> update user set password=PASSWORD('123456') where user='root';

到此，整个就结束了！
---
title: 用idea打包spring boot gradle项目为war包并部署到云服务器
date: 2018-08-03 13:53:57
tags:
	- 部署
	- idea
	- spring boot
categories: 基础
---

## 使用工具

IDE：idea

项目：spring boot的gradle项目

云服务器：阿里云服务器、centOS、Tomcat9、jdk8



## 打包为war

为测试用随便建了一个helloboot的gradle项目，项目目录如下：

![目录](用idea打包spring-boot-gradle项目打包war并上传云服务器\2.png)

运行类：

> ```
> import org.springframework.boot.SpringApplication;
> import org.springframework.boot.autoconfigure.SpringBootApplication;
> import org.springframework.web.bind.annotation.RequestMapping;
> import org.springframework.web.bind.annotation.RestController;
> 
> @RestController
> @SpringBootApplication
> public class DemoApplication {
>     @RequestMapping("/hello")
>     public String hello(){
>         return "Hello Boot!";
>     }
>     public static void main(String[] args) {
>         SpringApplication.run(DemoApplication.class, args);
>     }
> }
> ```

这里还需要有一个类，用来云架构需要：

> ```
> @SpringBootApplication
> public class SSOApplication extends SpringBootServletInitializer {
> 
>     public static void main(String[] args) {
>         SpringApplication.run(SSOApplication.class, args);
>     }
> 
>     /**
>      *重写configure
>      * @param builder
>      * @return
>      */
>     @Override
>     protected SpringApplicationBuilder configure(SpringApplicationBuilder builder) {
>         return builder.sources(SSOApplication.class);
>     }
> }
> ```

配置文件：application.properties

> ```
> server.port=8443
> #如果war包名称与前缀名相同的话，调试环境和正式部署环境就是一个request地址
> server.servlet.context-path=/demo/
> ```

这里还有一个坑就是，我的用springboot的gradle项目打包为war，所以要在build.gradle配置文件加上以下语句：

> ```
> apply plugin: 'war'
> ```

设置artifacts:

![](用idea打包spring-boot-gradle项目打包war并上传云服务器\1.png)

如果artifacts是空的点加号以后配置如下：

![](用idea打包spring-boot-gradle项目打包war并上传云服务器\5.png)

![](用idea打包spring-boot-gradle项目打包war并上传云服务器\3.png)

output directory是war包输出目录；



点击build-build Artifacts...

![](用idea打包spring-boot-gradle项目打包war并上传云服务器\4.png)

到输出目录里找到war包；

## 部署到云服务器

云服务器需要安装Tomcat，建议如果使用云端服务器可以使用宝塔来管理，十分方便；

将war包放到服务器的Tomcat目录下的webapps里，然后重启Tomcat就可以运行了，运行时URL应为ip+项目名+controller，如：localhost：8080/demo/hello

至此，打包并部署完成！
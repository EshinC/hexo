---
title: 本地项目上传到Github
date: 2018-07-23 20:49:54
tags: 
	- git
	- github 
categories: 基础
---

git的安装
---
安装过程就不再做笔记；

创建本地库
---

 在本地创建一个版本库（即文件夹），通过点击空白右键，点击git bush，输入
 > git init
 把本文件夹变成Git仓库；

将项目添加、提交到仓库
---
把项目复制到这个文件夹里面，再通过
> git add .
把整个项目添加到仓库，或者
> git add+项目名
把目添加到仓库，再通过git commit -m "注释内容"把项目提交到仓库；

设置ssh key
---
先看一下你C盘用户目录下有没有.ssh目录，有的话看下里面有没有id_rsa和id_rsa.pub这两个文件，有就跳到下一步，没有就通过下面命令创建
> ssh-keygen -t rsa -C "youremail@example.com"
回车后在C盘用户目录下的.ssh目录里找到id_rsa和id_rsa.pub这两个文件；

登录Github,找到右上角的图标，打开点进里面的Settings，再选中里面的SSH and GPG KEYS，点击右上角的New SSH key，然后Title里面随便填，再把刚才id_rsa.pub里面的内容复制到Title下面的Key内容框里面，最后点击Add SSH key，这样就完成了SSH Key的加密。 



在Github上创建一个Git仓库。
---
可以直接点New repository来创建，写上项目名，项目描述，点击Creat就ok；

连接GitHub
---
在Github上设置好SSH密钥，新建好远程仓库后，通过
> git remote add origin +你的github获取到的url，将本地仓库和远程仓库进行关联；

将项目放到GitHub
---
最后通过
> git push -u origin master
把本地仓库的项目推送到远程仓库（也就是Github）上；

报错处理
---
第4步创建远程仓库的时候，如果勾选了Initialize this repository with a README（就是创建仓库的时候自动给你创建一个README文件），那么到了第6步将本地仓库内容推送到远程仓库的时候就会报一个failed to push some refs to https://github.com/++++ 的错。 这是由于新创建的那个仓库里面的README文件不在本地仓库目录中，这时可以通过以下命令先将内容合并以下：
> git pull --rebase origin master

后续维护上传
---

> git add .     或者    git add +项目修改名
> git commit -m "注释内容"
> git push -u origin master

完毕！

完
---

以上，百度+实践后简单总结了一下上传到GitHub项目的过程，日后望能记住！

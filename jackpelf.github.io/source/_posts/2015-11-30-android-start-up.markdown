---
layout: post
title: "android_start_up"
date: 2015-11-30 21:13:04 +0800
comments: true
categories: 
---
# android启动

安卓启动过程  
init进程建立  
    挂载目录  
    解析rc脚本(Actions动作Commands命令Services服务Options启动服务)  
    servicemanager的启动(用来管理binder service)  
zygote进程的启动  
    进入androidruntime类  
        启动startVM  
        注册JNI方法  
        ZygoteInit  
            registerZygoteSocket注册socket  
            fork startSystemServer启系统服务  
            runSelectLoopMode函数等待socket连接并fork进程  

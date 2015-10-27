---
layout: post
title: "isg_webroid"
date: 2015-10-27 00:35:55 +0800
comments: true
categories: 
---

###0x00 apk re
反编译工具  
jeb查看源码  
apkIDE、apktools可以解包APK  
IDA查看so文件,IDA也可远程调试  



###0x01 分析
JSON(JavaScript Object Notation) 是一种轻量级的数据交换格式  
PHP ======是包括变量值与类型完全相等  
apk向一个地址提交了一个post请求

     new DefaultHttpClient();
                HttpPost v4 = new HttpPost("http://202.120.7.135:8888/html/api.php");
                JSONObject v3 = new JSONObject();
                v3.put("secret", secret);
                v4.setEntity(new StringEntity(v3.toString()));
                v5 = EntityUtils.toString(new DefaultHttpClient().execute(((HttpUriRequest)v4)).getEntity
                        ());




###0x02 java
toString().trim()获得对象的字段的值，然后转成string类型，并且去掉前后空白  
Java中，通过关键字extends继承一个已有的类  
在Java中不允许多继承  
super关键字表示超（父）类的意思  
新的package放在lib\ext  
JAVA文件中只能含有一个Public类  
一个文件的其他类不能使用修饰符  
StringEntity是一个字符串Entity

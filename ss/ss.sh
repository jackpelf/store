#!/bin/python
from httplib import *
import urllib
from time import *
from os import *

sleep(3)

while True:

	#first
	url = '/login'
	params = "email=17854290512%40sina.cn&redirect=%2Fmy&password=d54d1702ad0f8326224b817c796763c9"
	headers = {'Host':'www.ss-link.com',\
	'User-Agent':'Mozilla/5.0 (X11; Linux x86_64; rv:31.0) Gecko/20100101 Firefox/31.0 Iceweasel/31.5.0',\
	'Accept':'text/plain, */*; q=0.01',\
	'Accept-Language':'en-US,en;q=0.5',\
	'Accept-Encoding':'gzip, deflate',\
	'Content-Type':'application/x-www-form-urlencoded; charset=UTF-8',\
	'X-Requested-With':'XMLHttpRequest',\
	'Referer':'https://www.ss-link.com/login',\
	'Content-Length': '84',\
	'Connection':'keep-alive',\
	'Pragma':'no-cache',\
	'Cache-Control':'no-cache' }
	print '[+]first logging'
	con = HTTPSConnection("www.ss-link.com")
	con.request('POST', url, params, headers )
	res = con.getresponse()
	res.status
	setcookie1 = res.msg.get('Set-Cookie')[17:57]
	res.read()
	sleep(1)


	#second
	print '[+]second loging'
	url = '/my'
	headers = {'Host':'www.ss-link.com',\
	'User-Agent':'Mozilla/5.0 (X11; Linux x86_64; rv:31.0) Gecko/20100101 Firefox/31.0 Iceweasel/31.5.0',\
	'Accept':'text/plain, */*; q=0.01',\
	'Accept-Language':'en-US,en;q=0.5',\
	'Accept-Encoding':'gzip, deflate',\
	'Referer':'https://www.ss-link.com/login',\
	'X-Requested-With':'XMLHttpRequest',\
	'Content-Type':'application/x-www-form-urlencoded; charset=UTF-8',\
	'Cookie':'webpy_session_id=' + setcookie1,\
	'Connection':'keep-alive',\
	'Pragma':'no-cache',\
	'Cache-Control':'no-cache' }
	con.request('GET', url, '', headers)
	res = con.getresponse()
	print res.status
	res.read()
	sleep(1)


	#third
	print '[+]third loging'
	url = '/my'
	headers = {'Host':'www.ss-link.com',\
	'User-Agent':'Mozilla/5.0 (X11; Linux x86_64; rv:31.0) Gecko/20100101 Firefox/31.0 Iceweasel/31.5.0',\
	'Accept':'text/plain, */*; q=0.01',\
	'Accept-Language':'en-US,en;q=0.5',\
	'Accept-Encoding':'gzip, deflate',\
	'Referer':'https://www.ss-link.com/login',\
	'Cookie':'webpy_session_id=' + setcookie1,\
	'Connection':'keep-alive'}

	con.request('GET', url, '', headers)
	res = con.getresponse()
	print res.status
	res.read()



	print '[+]getting accounts'
	url = '/my/free'
	headers = {'Host':'www.ss-link.com',\
	'User-Agent':'Mozilla/5.0 (X11; Linux x86_64; rv:31.0) Gecko/20100101 Firefox/31.0 Iceweasel/31.5.0',\
	'Accept':'text/plain, */*; q=0.01',\
	'Accept-Language':'en-US,en;q=0.5',\
	'Cookie':'webpy_session_id=' + setcookie1,\
	'Connection':'keep-alive'}
	con.request('GET', url, '', headers)
	res = con.getresponse()
	print res.status
	res.msg
	data = res.read()
	index = data.find('173.252.220.201')

	password = data[index+65: index+73]

	system("sslocal -s 173.252.220.201 -p 9980 -b 192.168.56.102 -l 1080 -k " + password + " -t 600 -m aes-256-cfb")
	try:
		cmd = "sslocal -s 173.252.220.201 -p 9980 -b 192.168.56." + argv[1] +\
		" -l 1080 -k " + password + " -t 600 -m aes-256-cfb"
		system(s)
		sleep(2)
	except:
		system("sslocal -s 173.252.220.201 -p 9980 -b 192.168.56.102 -l 1080 -k " + password + " -t 600 -m aes-256-cfb")
	print '------'

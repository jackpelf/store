---
layout: post
title: "isg-encrypt"
date: 2015-10-22 14:33:41 +0800
comments: true
categories: 
---
n=0xA41006DEFD378B7395B4E2EB1EC9BF56A61CD9C3B5A0A73528521EEB2FB817A7
e=65537
p=0xD7DB8F68BCEC6D7684B37201385D298B
q=0xC292A272E8339B145D9DF674B9A875D5
d=0x330228A0BBE9C119B6B9FEB34B673E6D9AAC3AD81409694B576871521254A2C1


def exgcd(a, b):
    x0=1; y0=0;
    x1=0; y1=1;
    x=0; y=1;
    r=a%b;
    q=(a-r)/b;
    while r!=0:
        x=x0-q*x1
	y=y0-q*y1
        x0=x1
	y0=y1
        x1=x
	y1=y
        a=b
	b=r
	r=a%b
        q=(a-r)/b
    return (b,x,y)

print hex(exgcd(e,(p-1)*(q-1))[1])

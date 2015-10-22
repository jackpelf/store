---
layout: post
title: "Diffe-Hellman"
date: 2015-10-22 01:08:28 +0800
comments: true
categories: 
---

##0x00 Diffie-Hellman密钥交换协议算法
可以在需要安全通信的双方确定对称密钥，是一种建立密钥的方法  
###0x01 算法描述
1.Alice和Bob先说好一个大素数p和它的原始根  
2.Alice随机产生一个数x，计算X=a^x mod p,然后把X发给Bob  
3.Bob随机产生一个随机数y,计算Y=a^y mod p,然后把Y发给  Alice  
4.Alice计算k=Y^x mod p
5.Bob计算k*=X^y mod p

因为k = Y^x mod p = (a^y)^x mod p = (a^x)^y mod p = X^y mod p = K*

####0x02 DH算法易受中间人攻击
1.Alice公开发送值a和p给Bob，攻击者Carol截获这  
2.Bob 公开发送a和p的值被Carol截获，并把自己的公开值发给Alice  
3.Alice和 Carol计算两人之间的共享密钥k1  
4.Bob和Carol计算两人之间的共享密钥k2  
Alice用密钥k1给Bob发送消息，Carol截获后k1解密，并把明文用k2加密发给Bob...  


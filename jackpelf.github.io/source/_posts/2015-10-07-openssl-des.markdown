---  
layout: post  
title: "openssl_des"  
date: 2015-10-07 13:41:33 +0800  
comments: true  
categories:   
---  
###0x00  
DES ECB 电子密本方式  
将数据按照8个字节一段进行DES加密或解密得到一段段的8个字节的密文或者明文，最后一段不足8个字节padding,按照需求补足8个字节进行计算（并行计算），之后按照顺序将计算所得的数据连在一起即可，各段数据之间互不影响  
  
DES CBC 密文分组链接方式  
1. 首先将数据按照8个字节一组进行分组得到D1D2......Dn（若数据不是8的整数倍，用指定的PADDING数据补位）  
2. 第一组数据D1与初始化向量I异或后的结果进行DES加密得到第一组密文C1（初始化向量I为全零）  
3. 第二组数据D2与第一组的加密结果C1异或以后的结果进行DES加密，得到第二组密文C2  
4. 之后的数据以此类推，得到Cn  
5. 按顺序连为C1C2C3......Cn即为加密结果。  
  
  
###0x01 des ebc  
  
gcc descbc.c -lcrypto  
  
  
	#include <stdio.h>  
	#include <stdlib.h>  
	#include <string.h>  
	#include <openssl/des.h>  
  
	char* hex2bin(char* okey, int len, int* nlen)  
	{  
		char tmp;  
		char *res = malloc(len/2);  
		int i;  
		*nlen = len/2;  
		for(i=0; i<len/2; i++)  
		{  
			if(okey[2*i] <= 0x39)  
				tmp = 16*(okey[2*i]-'0');  
			else if(okey[2*i]>'F')  
				tmp = 16*(okey[2*i]-'a'+10);  
			else   
				tmp = 16*(okey[2*i]-'A'+10);  
			if(okey[2*i+1] <= 0x39)  
				tmp += okey[2*i+1]-'0';  
			else if(okey[2*i]>'F')  
				tmp += (okey[2*i+1]-'a'+10);  
			else   
				tmp += (okey[2*i+1]-'A'+10);  
			res[i]=tmp;  
		}  
		return res;  
	}  
  
  
  
  
	int main(int argc, char *argv[])  
	{  
	    DES_key_schedule ks;  
	   
	    int i = 0;  
	    int len = 0;  
	    int nlen = 0;  
	    int count = 0;  
	   
	    char *data = "12345678123456781234567812345678";  /* 原始明文, 十六进制字符串 */  
	    char *okey = "0000000000000000";                  /* 原始密钥, 十六进制字符串 */  
	   
	    unsigned char ch = '\0';  
	    unsigned char *ptr = NULL;  
	   
	    unsigned char src[16] = {0}; /* 补齐后的明文, data补齐后的1/2长度 */  
	    unsigned char dst[16] = {0}; /* 解密后的明文, data补齐后的1/2长度 */  
	   
	    unsigned char out[8] = {0};  
	    unsigned char tmp[8] = {0};  
	    unsigned char block[8] = {0};  
	   
	    /* 设置密码表 */  
	    ptr = hex2bin(okey, strlen(okey), &nlen);  
	    memcpy(block, ptr, 8);  
	    free(ptr);  
	    DES_set_key_unchecked((const_DES_cblock*)block, &ks);  
	   
	    /* 分析补齐明文所需空间及补齐填充数据 */  
	    len = strlen((char *)data);  
	    ptr = hex2bin(data, len, &nlen);  
	    len = (nlen / 8 + (nlen % 8 ? 1: 0)) * 8;  
	    memcpy(src, ptr, len);  
	    free(ptr);  
	   
	    ch = 8 - nlen % 8;  
	    memset(src + nlen, ch, 8 - nlen % 8);  
	   
	    printf("加密之前: ");  
	    for (i = 0; i < len; i++) {  
		printf("%.2X", *(src + i));  
	    }  
	    printf("\n");  
	   
	    /* 分组加密，每8字节一组 */  
	    count = len / 8;  
	    for (i = 0; i < count; i++) {  
		memcpy(tmp, src + 8 * i, 8);  
		DES_ecb_encrypt((const_DES_cblock*)tmp, (DES_cblock*)out, &ks, DES_ENCRYPT);  
		memcpy(dst + 8 * i, out, 8);  
	    }  
	   
	    printf("加密之后: ");  
	    for (i = 0; i < len; i++) {  
		printf("%.2X", *(dst + i));  
	    }  
	    printf("\n");  
	   
	    return 0;  
	}  
  
###0x02 des cbc  
  
	#include <stdio.h>  
	#include <stdlib.h>  
	#include <string.h>  
	#include <openssl/des.h>  
	  
	char* hex2bin(char* okey, int len, int* nlen)  
	{  
		char tmp;  
		char *res = malloc(len/2);  
		int i;  
		*nlen = len/2;  
		for(i=0; i<len/2; i++)  
		{  
			if(okey[2*i] <= 0x39)  
				tmp = 16*(okey[2*i]-'0');  
			else if(okey[2*i]>'F')  
				tmp = 16*(okey[2*i]-'a'+10);  
			else   
				tmp = 16*(okey[2*i]-'A'+10);  
			if(okey[2*i+1] <= 0x39)  
				tmp += okey[2*i+1]-'0';  
			else if(okey[2*i]>'F')  
				tmp += (okey[2*i+1]-'a'+10);  
			else   
				tmp += (okey[2*i+1]-'A'+10);  
			res[i]=tmp;  
		}  
		return res;  
	}  
	  
	  
	  
	int main(int argc, char *argv[])  
	{  
	    DES_key_schedule ks;  
	    DES_cblock ivec = {0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00, 0x00};  
	   
	    int i = 0;  
	    int len = 0;  
	    int nlen = 0;  
	   
	    char *data = "12345678123456781234567812345678";  /* 原始明文, 十六进制字符串 */  
	    char *okey = "0000000000000000";                  /* 原始密钥, 十六进制字符串 */  
	   
	    unsigned char ch = '\0';  
	    unsigned char *ptr = NULL;  
	   
	    unsigned char src[16] = {0}; /* 补齐后的明文, data补齐后的1/2长度 */  
	    unsigned char dst[16] = {0}; /* 解密后的明文, data补齐后的1/2长度 */  
	   
	    unsigned char block[8] = {0};  
	   
	    /* 设置密码表 */  
	    ptr = hex2bin(okey, strlen(okey), &nlen);  
	    memcpy(block, ptr, 8);  
	    free(ptr);  
	    DES_set_key_unchecked((const_DES_cblock*)block, &ks);  
	   
	    /* 分析补齐明文所需空间及补齐填充数据 */  
	    len = strlen((char *)data);  
	    ptr = hex2bin(data, len, &nlen);  
	    len = (nlen / 8 + (nlen % 8 ? 1: 0)) * 8;  
	    memcpy(src, ptr, len);  
	    free(ptr);  
	   
	    ch = 8 - nlen % 8;  
	    memset(src + nlen, ch, 8 - nlen % 8);  
	   
	    printf("加密之前: ");  
	    for (i = 0; i < len; i++) {  
		printf("%.2X", *(src + i));  
	    }  
	    printf("\n");  
	   
	    /* 加密块链式加密 */  
	    DES_ncbc_encrypt(src, dst, sizeof(src), &ks, &ivec, DES_ENCRYPT);  
	   
	    printf("加密之后: ");  
	    for (i = 0; i < len; i++) {  
		printf("%.2X", *(dst + i));  
	    }  
	    printf("\n");  
	   
	    return 0;  
	}  

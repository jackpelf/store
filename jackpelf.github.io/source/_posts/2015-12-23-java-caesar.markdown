---
layout: post
title: "java-caesar"
date: 2015-12-23 14:18:07 +0800
comments: true
categories: 
---
```java
import java.util.Scanner;

public class caesar
{
	public static void main(String[] args)
	{
		System.out.println("Welcome to Caesar cipher!");
		Scanner sc=new Scanner(System.in);
	 	while(true)
		{ 
			System.out.println("Input text you want to cihper:");
			String str=null;
			str=sc.nextLine();
			System.out.println(cipher(str));
		}
	}
	private static String cipher(String data)
	{
		String res = new String();
		for(int i = 0; i < data.length(); i++)
		{
			int tmp;
			tmp = data.charAt(i);
			if(tmp >= 97 && tmp <= 122)
			{
				tmp = 97 + (tmp - 97 + 5) % 26;
			}		
			else if(tmp >= 65 && tmp <= 90)
			{
				tmp = 65 + (tmp - 65 + 5) % 26;
			}
			else
				tmp = tmp;
			res += (char)tmp;
		}
		return res;
	}
}

```

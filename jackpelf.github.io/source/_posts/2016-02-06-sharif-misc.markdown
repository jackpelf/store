---
layout: post
title: "sharif-misc"
date: 2016-02-06 21:39:15 +0800
comments: true
categories: 
---
'''java
package test;

import java.awt.image.BufferedImage;
import java.io.File;

import javax.imageio.ImageIO;

public class test {
	public static void main(String [] args)
	{
		int m=7;
		int c = 0;
		int sum = 0;
		byte buf[] = new byte[10000] ;
		try{
			BufferedImage bf = ImageIO.read(new File("G:\\AsianCheetah1.png"));
			int i=-1,j;
			try{
				for(i=0; i<450; i++)
				{
					for(j=0; j<600; j++)
					{

						//System.out.println("j: " + Integer.valueOf(j));
						//System.out.println("c: " + Integer.valueOf(c));
						try{
							String str = new String();
							int tmp=0;
							tmp = (bf.getRGB(j, i) & 1);
							try{
								buf[c] = (byte) (buf[c] | (tmp << m));
							}catch(Exception e)
							{
								System.out.println("mov error");
								System.out.println("c: " + Integer.valueOf(c));
								System.exit(0);
							}
						}catch(Exception e)
						{
							System.out.println("RGB error");
							System.out.println(j);
							System.out.println(i);
							System.exit(0);
						}
						//System.out.println(sum++);
						m--;
						if(m == -1){
							m = 7;
							c++;
						}
					}
					//System.in.read();
					int k=0;
					try{
						for(k=0; k<100; k++)
							System.out.print((char)buf[k]);
					}catch(Exception e)
					{

					}
				}
			}catch(Exception e){
				System.out.println("outside for error");
				System.out.println(i);
				System.out.println(i);
			}

		}catch(Exception e)
		{

		}

		System.out.println("end");
	}
}
'''

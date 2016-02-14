package test;

import java.awt.image.BufferedImage;
import java.io.File;

import javax.imageio.ImageIO;

public class test {
	public static void main(String [] args)
	{
		int m=7;
		int sum = 0;
		int c = 0;
		byte buf[] = new byte[10000] ;
		try{
			BufferedImage bf0 = ImageIO.read(new File("G:\\00000000.png"));
			BufferedImage bf1 = ImageIO.read(new File("G:\\00003754.png"));
			int i=-1,j;
			System.out.println("start");
			try{
				for(i=0; i<bf0.getHeight(); i++)
				{
					for(j=0; j<bf0.getWidth(); j++)
					{
						try{
							String str = new String();
							int tmp0 = bf0.getRGB(j, i);
							int tmp1 = bf1.getRGB(j, i);
							if(tmp0 != tmp1)
							{
								//System.out.printf("x, y: %d, %d\n", j, i);
								//System.out.printf("%x ", (tmp0 >> 16) & 0xff);
								//System.out.printf("%x\n", (tmp1 >> 16) & 0xff);
								buf[c] = (byte) (buf[c] | (((tmp1 >> 16) & 1) << m ));
									//System.out.println(m);
								m --;
								if(m == -1){
									//System.out.printf("%c", buf[c]);
									m = 7;
									c++;
								}
							}
							sum ++;
						}catch(Exception e)
						{
							System.out.println("RGB error");
							System.exit(0);
						}
					}
				}
				System.out.printf("count: %d\n", sum);
			}catch(Exception e){
				System.out.println("error");
			}
			System.out.println(new String(buf));
			
		}catch(Exception e)
		{
			
		}
		
		System.out.println("end");
	}
}


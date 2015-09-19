import java.util.Scanner;

public class find_str
{
	public static void main(String[] args)
	{
		System.out.println("Hello World!");
		Scanner sc=new Scanner(System.in);
	 	while(true)
		{ 
			String str=null;
			str=sc.nextLine();
			int i = str.indexOf("cook");
			 
			System.out.println("i:"+i);	
			System.out.println("ÄãÊäÈëµÄ×Ö·ûÎª:"+str);	
		}
	}
}

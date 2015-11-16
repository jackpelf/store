import org.apache.http.client.ClientProtocolException;
import org.apache.http.client.methods.HttpPost;
import org.apache.http.client.methods.HttpUriRequest;
import org.apache.http.entity.StringEntity;
import org.apache.http.util.EntityUtils;
import org.apache.http.impl.client.DefaultHttpClient;
import java.util.Scanner;
import org.json.JSONObject;

public class test
{
	public static void main(String[] args)
	{
		Scanner sc = new Scanner(System.in);
		System.out.println("please input url");
		String s = new String();
		s = sc.nextLine();
		post p = new post();
		p.func("http://" + s);
	}
}
class post
{
	public void func(String a)
	{
		HttpPost tmp = new HttpPost(a);
		try{
			JSONObject ob = new JSONObject();
			ob.put("secret", "cont");
			StringEntity s = new StringEntity("string string");
			System.out.println(ob.toString());
			String t = EntityUtils.toString(new DefaultHttpClient().execute((HttpUriRequest)tmp).getEntity());
			System.out.println(t);
	
		}catch(Exception e)
		{
			System.out.println("IO error");
		}	
	}

}

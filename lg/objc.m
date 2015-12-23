#import <Foundation/Foundation.h>
NSString* Cipher(NSString *text)
{
	NSLog(@"length is %d",[text length]);
	int i;
	char buf[2000];
	NSLog(@"Answer is: "); 
	for(i = 0; i < [text length]; i++)
	{
		int tmp = [text characterAtIndex:i];
		if( tmp >= 'a' && tmp <= 'z')		
			buf[i] = 'a' + (tmp - 'a' + 5) % 26 ;
		else if( tmp >= 'A' && tmp <= 'Z')		
			buf[i] = 'A' + (tmp - 'A' + 5) % 26 ;
		else 
			buf[i] = tmp;
	}
	NSString *ans= [[NSString alloc] initWithCString:buf];
	return ans;
}
int main(int argc, const char * argv[])
{
	NSLog(@"Welcome to Caesar cipher\n");
	char buf[2000];
	NSString *text = [[NSString alloc] initWithCString:buf];
	while(1)
	{
		NSLog(@"Input text you want to cipher");
		scanf("%2000s", buf);
		NSString *text = [[NSString alloc] initWithCString:buf];
		NSLog( Cipher(text) );
		[text release];
	}
	return 0;
}

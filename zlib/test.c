#include<stdio.h>
#include<string.h>
#include<zlib.h>
int main()
{
	int i;
	z_stream strm;
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	deflateInit(&strm, 6);
	unsigned char in[100] = "Blah blah blah blah blah!";
	unsigned char out[100];
	memset(out, 0, sizeof(out));
	puts("in");
	for(i=0; i<100; i++)
	{
		if(i % 16 == 0)
			puts("");
		if(i % 8 == 0)
			printf(" ");
		printf("%02x ",in[i]);
	}
	puts("");
	strm.avail_in = strlen(in);
	strm.next_in = in;
	strm.avail_out = 16;
	strm.next_out = out;
	deflate(&strm, Z_FINISH);
	printf("avail out: %d ",strm.avail_out);
	deflateEnd(&strm);
	puts("out");
	for(i=0; i<100; i++)
	{
		if(i % 16 == 0)
			puts("");
		if(i % 8 == 0)
			printf(" ");
		printf("%02x ",out[i]);
	}
	puts("");
	return 0;
}


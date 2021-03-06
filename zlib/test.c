#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<zlib.h>
int lz77(unsigned char *in, int len, int level)
{
	int i;
	z_stream strm;
	strm.zalloc = Z_NULL;
	strm.zfree = Z_NULL;
	strm.opaque = Z_NULL;
	deflateInit(&strm, level);
	unsigned char out[1000];
	memset(out, 0, sizeof(out));
	puts("__________________________");
	for(i=0; i<len; i++)
	{
		if(i % 16 == 0)
			puts("");
		if(i % 8 == 0)
			printf(" ");
		printf("%02x ",in[i]);
	}
	puts("");
	strm.avail_in = len;
	strm.next_in = in;
	strm.avail_out = 1000;
	strm.next_out = out;
	deflate(&strm, Z_FINISH);
	deflateEnd(&strm);
	for(i=0; i<(1000 - strm.avail_out) + 0x10; i++)
	
	{
		if(i % 16 == 0)
			puts("");
		if(i % 8 == 0)
			printf(" ");
		printf("%02x ",out[i]);
	}
	puts("");
	return 1000 - strm.avail_out;
}
int main(int argc, char **argv)
{
	char in[1000] = "\x02\x01\x02\x03\x02\x04\x02\x05\x02\x06\x02\x07\x02\x08\x02\x09\x02\x0b\x02\x0c\x02\x0d\x02\x0e\x02\x0f\x02\x10\x02\x11\x02\x12\x02\x13\x02\x14\x02\x15\x02\x16\x02\x17\x02\x18\x02\x19\x02\x1a\x02\x1b\x02\x1c\x02\x1d\x02\x1e\x02\x1f\x02\x20\x02\x21\x02\x22\x02\x23\x02\x24\x02\x25\x02\x26\x02\x27\x02\x28\x02\x29\x02\x2a\x02\x2b\x02\x2c\x02\x2d\x02\x2e\x02\x2f\x02\x30\x02\x31\x02\x32\x02\x33\x02\x34\x02\x35\x02\x36\x02\x37\x02\x38\x02\x39\x02\x3a\x02\x3b\x02\x3c\x02\x3d\x02\x3e\x02\x3f\x02\x40\x02\x41\x02\x42\x02\x43\x02\x44\x02\x45\x02\x46\x02\x47\x02\x48\x02\x49\x02\x4a\x02\x4b\x02\x4c\x02\x4d\x02\x4e\x02\x4f\x02\x50\x02\x51\x02\x52\x02\x53\x02\x54\x02\x55\x02\x56\x02\x57\x02\x58\x02\x59\x02\x5a\x02\x5b\x02\x5c\x02\x5d\x02\x5e\x02\x5f\x02\x60\x02\x61\x02\x62\x02\x63\x02\x64\x02\x65\x02\x66\x02\x67\x02\x68\x02\x69\x02\x6a\x02\x6b\x02\x6c\x02\x6d\x02\x6e\x02\x6f\x02\x70\x02\x71\x02\x72\x02\x73\x02\x74\x02\x75\x02\x76\x02\x77\x02\x79\x02\x7a\x02\x7b\x02\x7c\x02\x7d\x02\x7e\x02\x7f\x02\x80\x02\x81\x02\x82\x02\x83\x02\x84\x02\x85\x02\x86\x02\x87\x02\x88\x02\x89\x02\x8a\x02\x8b\x02\x8c\x02\x8d\x02\x8e\x02\x8f\x02\x90\x02\x91\x02\x92\x02\x93\x02\x94\x02\x95\x02\x96\x02\x97\x02\x98\x02\x99\x02\x9a\x02\x9b\x02\x9d\x02\x9e\x02\x9f\x02\xa0\x02\xa1\x02\xa2\x02\xa3\x02\xa4\x02\xa5\x02\xa6\x02\xa7\x02\xa8\x02\xa9\x02\xaa\x02\xab\x02\xac\x02\xad\x02\xae\x02\xaf\x02\xb0\x02\xb1\x02\xb2\x02\xb3\x02\xb4\x02\xb5\x02\xb6\x02\xb7\x02\xb8\x02\xb9\x02\xba\x02\xbb\x02\xbc\x02\xbd\x02\xbe\x02\xbf\x02\xc0\x02\xc1\x02\xc2\x02\xc3\x02\xc4\x02\xc5\x02\xc6\x02\xc7\x02\xc8\x02\xc9\x02\xca\x02\xcb\x02\xcc\x02\xcd\x02\xce\x02\xcf\x02\xd0\x02\xd1\x02\xd2\x02\xd3\x02\xd4\x02\xd5\x02\xd6\x02\xd7\x02\xd8\x02\xd9\x02\xda\x02\xdb\x02\xdc\x02\xdd\x02\xde\x02\xdf\x02\xe0\x02\xe1\x02\xe2\x02\xe3\x02\xe4\x02\xe5\x02\xe6\x02\xe7\x02\xe8\x02\xe9\x02\xea\x02\xeb\x02\xec\x02\xed\x02\xee\x02\xef\x02\xf0\x02\xf1\x02\xf2\x02\xf3\x02\xf4\x02\xf5\x02\xf6\x02\xf7\x02\xf8\x02\xf9\x02\xfa\x02\xfb\x02\xfc\x02\xfd\x02\xfe\x02\xff\xff\x0a\x00\x46";
	int r = lz77(in, 506, atoi(argv[1]));
	printf("%d\n", r);
	return 0;
}

#include <inttypes.h>
#include <stdio.h>
#include <string.h>

int base64encode(const void* data_buf, size_t dataLength, char* result, size_t resultSize)
{
   const char base64chars[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz0123456789+/";
   const uint8_t *data = (const uint8_t *)data_buf;
   size_t resultIndex = 0;
   size_t x;
   uint32_t n = 0;
   int padCount = dataLength % 3;
   uint8_t n0, n1, n2, n3;
   for (x = 0; x < dataLength; x += 3) 
   {
      n = ((uint32_t)data[x]) << 16; 
      if((x+1) < dataLength)
         n += ((uint32_t)data[x+1]) << 8;
      if((x+2) < dataLength)
         n += data[x+2];
      n0 = (uint8_t)(n >> 18) & 63;
      n1 = (uint8_t)(n >> 12) & 63;
      n2 = (uint8_t)(n >> 6) & 63;
      n3 = (uint8_t)n & 63;
      if(resultIndex >= resultSize) return 1;   
      result[resultIndex++] = base64chars[n0];
      if(resultIndex >= resultSize) return 1;  
      result[resultIndex++] = base64chars[n1];
      if((x+1) < dataLength)
      {
         if(resultIndex >= resultSize) return 1;   
         result[resultIndex++] = base64chars[n2];
      }
      if((x+2) < dataLength)
      {
         if(resultIndex >= resultSize) return 1;   
         result[resultIndex++] = base64chars[n3];
      }
   }  
   if (padCount > 0) 
   { 
      for (; padCount < 3; padCount++) 
      { 
         if(resultIndex >= resultSize) return 1;   
         result[resultIndex++] = '=';
      } 
   }
   if(resultIndex >= resultSize) return 1;   
   result[resultIndex] = 0;
   return 0;   
}
int main()
{
	char buf[20] = "testtesttest";
	char result[40];
	base64encode(buf, strlen(buf), result, 40);
	printf("%s\n",result);
	return 0;
}

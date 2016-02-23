/*
3598180
*/
#include<stdio.h>
int main()
{
	int card[13];
	int count = 0;
	for(card[0]=0; card[0]<= 4; card[0]++)
	for(card[1]=0; card[1]<= 4; card[1]++)
	for(card[2]=0; card[2]<= 4; card[2]++)
	for(card[3]=0; card[3]<= 4; card[3]++)
	for(card[4]=0; card[4]<= 4; card[4]++)
	for(card[5]=0; card[5]<= 4; card[5]++)
	for(card[6]=0; card[6]<= 4; card[6]++)
	for(card[7]=0; card[7]<= 4; card[7]++)
	for(card[8]=0; card[8]<= 4; card[8]++)
	for(card[9]=0; card[9]<= 4; card[9]++)
	for(card[10]=0; card[10]<= 4; card[10]++)
	for(card[11]=0; card[11]<= 4; card[11]++)
	for(card[12]=0; card[12]<= 4; card[12]++)
	{
		if(card[0] + card[1] + card[2] + card[3] + card[4] + card[5] + card[6] + card[7] + card[8] + card[9] + card[10] + card[11] + card[12] == 13)
		{
			count++;
		}
	}
	printf("%d\n", count);
	return 0;
}

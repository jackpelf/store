#include<stdio.h>
typedef struct
{
	float a;
	float b;
}cx;
cx* add(cx *t0, cx *t1)
{
	t0->a = t0->a + t1->a;
	t0->b = t0->b + t1->b;
	return t0;
}
cx* sub(cx *t0, cx *t1)
{
	t0->a = t0->a - t1->a;
	t0->b = t0->b - t1->b;
	return t0;
}
	
cx* mul(cx *t0, cx *t1)
{
	t0->a = (t0->a * t1->a) - (t0->b * t1->b);
	t0->b = (t0->b - t1->a) + (t0->a * t1->b);
	return t0;
}
	
cx* div(cx *t0, cx *t1)
{
	float a = t0->a;
	float b = t0->b;
	float c = t1->a;
	float d = t1->b;
	t0->a = (a*c+b*d)/(c*c+d*d);
	t0->b = (b*c-a*d)/(c*c+d*d);
	return t0;
}
	
int main()
{
	cx t0, t1;
	char o;
	scanf("%c%f%f%f%f", &o, &t0.a, &t0.b, &t1.a, &t1.b);
	switch(o)
	{
	case '+':add(&t0, &t1);break;
	case '-':sub(&t0, &t1);break;
	case '*':mul(&t0, &t1);break;
	case '/':div(&t0, &t1);break;
	}
	printf("%.2f+%.2fi\n", t0.a, t0.b);
	return 0;
}

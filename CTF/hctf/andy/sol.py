from base64 import *

#zhihuan
fs = 'SRlhb70YZHKvlTrNrt08F=DX3cdD3txmg'
str1 = "W,p,X,4,5,B,q,A,6,a,V,3,r,b,U,s,E,d,C,c,D,O,t,T,Y,v,9,Q,2,e,8,P,f,h,J,N,g,u,K,k,H,x,L,w,R,I,j,i,y,l,m,S,M,1,0,O,n,2,G,7,=,F,Z"
str2 = "0 1 2 3 4 5 6 7 8 9 a b c d e f g h i j k l m n o p q r s t u v w x y z = A B C D E F G H I J K L M E O P Q R S T U V W X Y Z"
str1 = str1.replace(',', '')
str2 = str2.replace(' ', '')
res = ''
for i in fs:
	res += str2[ str1.index(i) ]

res0 = 'OHMxdWRoZDBpMnczcmRuYXk2bjhkbmEE='

#basede
res1 = b64decode(res0)

print 'flag is:'
print res1[::-1][:-6]

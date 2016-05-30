#include <stdio.h> 
2  #include <string.h>
3  #define StoD(x) (x==0? 0:x-'0') //숫자를 문자열로 입력받은 후 숫자로 바꿈 
    void integerize(char num[]) //실수 정수화 완료.
4   void mod(char*arr,int len); 
5        int main(){ 
6        char a[3][10002]={0}; //배열 3개 선언하면서 0으로 초기화 
7        int len,i; 
8        printf("A= "); 
9        scanf("%s",a[0]); //a[0]에 숫자를 문자로 입력받음 
         integerize (a[0])
10       printf("B= ");
11       scanf("%s",a[1]); //a[1]에 숫자를 문자로 입력받음 
12       integerize (a[1])
13       if(strlen(a[0])>strlen(a[1])){ //배열의 길이를 int형으로 변환 
14           len=strlen(a[0]); 
15       }else len=strlen(a[1]); // A,B중에 더 긴 문자열의 길이 입력받음 
16   
17       for(i=0;i<=len;i++){ 
18       a[2][i]=((StoD(a[0][i]))%(StoD(a[1][i]))); 
19       } 
20       if(a[2][len]=='0') a[2][len]=0; 
21       printf("A%%B=%s\n",a[2]); 
22       return 0; 
23   } 
24   void mod(char*arr,int len){ 
25       char temp; 
26       int i; 
27       for(i=0;i<len;i++){ 
28           temp=arr[i]; 
29           arr[i]=arr[len-1-i]; 
30           arr[len-1-i]=temp; 
31   } 
32 } 

void integerize(char num[]) //실수 정수화 완료. 
2 { 
3 	int i,point=0,cnt=0,cnt_0=0,cnt_f=0,cnt_str=0; 
4 	//i는 for문 임시변수, point 소수점의 위치,cnt 0을 붙인 후의 배열의 길이 
5 	//cnt_0 앞의 0을 제거하기 위한 0의 개수 
6 	//cnt_f 소수점 이후부터의 배열길이, cnt_str 처음 입력 받은 배열의 길이 
7 
 
8 	for(i=0;num[i]!='\0';i++) 
9 	{ 
10 		if(num[i]=='.') 
11 		{ 
12 			point=i; 
13 
 
14 			for(i=point;num[i]!='\0';i++) 
15 			{	 
16 				cnt_f++; 
17 				num[i]=num[i+1]; 
18 			} 
19 		} 
20 		cnt_str++; 
21 	} 
22 	if(point>0) 
23 	{ 
24 		for(i=point-1+cnt_f;i<=point-1+9;i++) 
25 			num[i]='0'; 
26 	}else{ 
27 		 for(i=cnt_str;i<=cnt_str+8;i++) 
28 			  num[i]='0'; 
29 	} 
30 
 
31 	for(i=0;num[i]=='0';i++) 
32 		cnt_0++; 
33 
 
34 	for(i=0;num[i]!='\0';i++) 
35 		cnt++; 
36 
 
37 	for(i=0;i<cnt;i++) 
38 		num[i]=num[i+cnt_0]; 
39 } 
 








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
 





Status
 API
 Training
 Shop
 Blog
 About
   © 2016 GitHub, Inc.
 Terms
 Privacy
 Security
 Contact
 Help
 

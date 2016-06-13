#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void mult(char a[],char b[],char c[]);
void integerize1(char num[]);  //소수점을 빼고 나머지 소수자리를 모두 0으로 채워 정수화 0.000001 >> 1000
void integerize2(char num[]);  //소수점을 제거하여 정수화 22.22 >> 2222
void change_int(char num[],int);  //char 형으로 저장된 값들을 int형으로 변환
void change_char(char num[],int);  //int 형으로 저장된 값들을 char형으로 변환
void floatlize(char num[]);  //소수를 정수화 시켜 계산한 값을 소수로 전환
void floatlize2(char num[]);
void swap(char num1[],char num2[]);  //두 배열의 값을 서로 바꿈
int what_big(char num1[],char num2[]);  //어떤 수가 더 큰가 판별
void comma(char a[]);  //숫자 세 자리마다 콤마 출력

void mult(char num1_1[],char num2_1[],char num4[])
{
	char num1_2[62]={0},num2_2[62]={0},num3[124]={0};
	int len1,len2,len3,plus=0,temp=0,i,j,extra=0;
	char tmp;

	integerize1(num1_1);
	integerize1(num2_1);

	len1=strlen(num1_1);
	len2=strlen(num2_1);
	len3=len1+len2;

	for(i=0;i<len1;i++)
		num1_2[len1-1-i]=num1_1[i];

	for(i=0;i<len2;i++)
		num2_2[len2-1-i]=num2_1[i];

//	printf("%s\n",num1_2);
//	printf("%s\n",num2_2);

	for(i=0;i<len1;i++)
		if(num1_2[i]==0)
			num1_2[i]=0;
		else
			num1_2[i]-='0';

	for(i=0;i<len2;i++)
		if(num2_2[i]==0)
			num2_2[i]=0;
		else
			num2_2[i]-='0';

//	for(i=0;i<strlen(num1_1);i++)
//		printf("%d",num1_2[i]);
//	printf("\n");

//	for(i=0;i<strlen(num2_1);i++)
//		printf("%d",num2_2[i]);	
//	printf("\n");

	for(i=0;i<=len3;i++)
	{
		for(j=0;j<=i;j++)
		{
			if((i-j<len1)&&(j<len2))
				temp+=num1_2[i-j]*num2_2[j];
			if(j==0)
			{
				temp+=plus;
				plus=0;
			}
		}
		plus+=temp / 10;
		num3[i]=(temp-plus*10)+'0';
//		printf("num3[%d]: %c",i,num3[i]);
//		printf("\n");
		temp=0;
	}

	if(num3[len3]=='0')
		num3[len3]=0;
	if(num3[len3-1]=='0')
	{
		num3[len3-1]=0;
		extra=1;
	}

//	printf("\nnum3(1): %s\n",num3);
//	for(i=len3-extra;i>=0;i--)
//		printf("%d",num3[i]);

	for(i=0;i<(len3-extra)/2;i++)
	{
		tmp=num3[i];
		num3[i]=num3[len3-extra-1-i];
		num3[len3-extra-1-i]=tmp;
	}

//	printf("\nnum3(2): %s\n",num3);

	floatlize2(num3);

//	printf("\nnum3(3): %s\n",num3);

//	floatlize(num3);
//	floatlize(num3);

	for(i=0;i<num3[i]!='\0';i++)
		num4[i]=num3[i];

//	floatlize(num4);
}

void integerize1(char num[]) //실수 정수화 완료.
{
	int i,point=0,cnt=0,cnt_0=0,cnt_f=0,cnt_str=0;

	for(i=0;num[i]!='\0';i++)
	{
		if(num[i]=='.')
		{
			point=i;

			for(i=point;num[i]!='\0';i++)
			{	
				cnt_f++;
				num[i]=num[i+1];
			}
		}
		cnt_str++;
	}
	if(point>0)
	{
		for(i=point-1+cnt_f;i<=point-1+9;i++)
			num[i]='0';
	}else{
		for(i=cnt_str;i<=cnt_str+8;i++)
			num[i]='0';
	}

	for(i=0;num[i]=='0';i++)
		cnt_0++;

	for(i=0;num[i]!='\0';i++)
		cnt++;

	for(i=0;i<cnt;i++)
		num[i]=num[i+cnt_0];
}

void integerize2(char num[])
{
	int i,point,cnt_f=0,cnt_0=0,cnt=0;

	for(i=0;num[i]!='\0';i++)
	{
		if(num[i]=='.')
		{
			point=i;

			for(i=point;num[i]!='\0';i++)
			{	
				cnt_f++;
				num[i]=num[i+1];
			}
		}
	}

	for(i=0;num[i]=='0';i++)
		cnt_0++;

	for(i=0;num[i]!='\0';i++)
		cnt++;

	for(i=0;i<cnt;i++)
		num[i]=num[i+cnt_0];
}

void change_int(char num[],int cnt) // 문자열 정수화 완료.
{
	int i;
	for(i=0;i<cnt;i++)
	{
		if(num[i]==0)
			num[i]=0;
		else
			num[i]-='0';
	}
}

void change_char(char num[],int cnt)//정수열 문자열화 완료.
{
	int i;
	for(i=0;i<cnt;i++)
		num[i]+='0';
}

void sub(char num1_1[61],char num2_1[61],char num3[61])
{

	char num1_2[61]={0},num2_2[61]={0};
	int len,i,plus=0,minus=0,temp;
	int cnt1=0,cnt2=0,cnt_0=0;


	for(i=0;num1_1[i]!='\0';i++)
		cnt1++;

	for(i=0;num2_1[i]!='\0';i++)
		cnt2++;

	if(cnt1>cnt2)
		len=cnt1;
	else
		len=cnt2;

	for(i=0;i<cnt1;i++)
	{
		num1_2[cnt1-1-i]=num1_1[i];
	}


	for(i=0;i<cnt2;i++)
	{
		num2_2[cnt2-1-i]=num2_1[i];
	}

	for(i=0;i<cnt1;i++)
	{
		if(num1_2[i]==0)
			num1_2[i]=0;
		else
			num1_2[i]-='0';
	}

	for(i=0;i<cnt2;i++)
	{
		if(num2_2[i]==0)
			num2_2[i]=0;	
		else
			num2_2[i]-='0';
	}

	for(i=0;i<=len;i++)
	{
		if(num1_2[i]-minus<num2_2[i])
			plus=10;
		else
			plus=0;

		num3[i]=(num1_2[i]-num2_2[i]+plus-minus)%10;

		if(num1_2[i]-minus<num2_2[i])
			minus=1;
		else
			minus=0;

		num3[i]+='0';

	}

	if(num3[len]=='0')
		num3[len]=0;

	for(i=0;i<len/2;i++)
	{
		temp=num3[i];
		num3[i]=num3[len-1-i];
		num3[len-1-i]=temp;
	}

	for(i=0;num3[i]=='0';i++)
		cnt_0++;

	if(cnt_0!=len)
		for(i=0;i<len;i++)
			num3[i]=num3[i+cnt_0];


	for(i=0;num3[i]!='\0';i++)
		if(num3[i]!='0')
			break;

	//	printf("%d %d %d\n",i,len,strlen(num3));

	if(i==strlen(num3))
		for(int j=1;j<strlen(num3);j++)
			num3[j]='\0';

	//	printf("%s\n",num3);
}

void floatlize(char num[])
{
	int i,cnt=0,cnt_0=0;

	for(i=0;num[i]!='\0';i++)
		cnt++;

	if(cnt<10)
	{
		for(i=0;i<cnt;i++)
			num[9-i]=num[cnt-1-i];

		for(i=0;i<10-cnt;i++)
			num[i]='0';	
	}

	cnt=0;

	for(i=0;num[i]!='\0';i++)
		cnt++;

	for(i=0;i<9;i++)
		num[cnt-i]=num[cnt-1-i];

	num[cnt-9]='.';

	for(i=cnt;num[i]=='0';i--)
		cnt_0++;

	if(cnt_0==9)
		for(i=0;i<9;i++)
			num[cnt-1-i]='\0';
	else
		for(i=0;i<cnt_0;i++)
			num[cnt-i]='\0';

	if((num[0]=='0')&&((num[1]>='1')&&(num[1]<='9')))
		for(i=0;i<=strlen(num);i++)
			num[i]=num[i+1];

	for(i=0;num[i]!='\0';i++)
		if(num[i]!='0')
			break;

	//	printf("%d %d\n",i,strlen(num));

	if(i==strlen(num))
		for(int j=1;j<strlen(num);j++)
			num[j]='\0';

	//	printf("%s\n",num);
}

void floatlize2(char num[])
{
	int i,cnt=0,cnt_0=0;

	for(i=0;num[i]!='\0';i++)
		cnt++;

	if(cnt<19)
	{
		for(i=0;i<cnt;i++)
			num[18-i]=num[cnt-1-i];

		for(i=0;i<19-cnt;i++)
			num[i]='0';	
	}

	cnt=0;

	for(i=0;num[i]!='\0';i++)
		cnt++;

	for(i=0;i<18;i++)
		num[cnt-i]=num[cnt-1-i];

	num[cnt-18]='.';

	for(i=cnt;num[i]=='0';i--)
		cnt_0++;

	if(cnt_0==18)
		for(i=0;i<18;i++)
			num[cnt-1-i]='\0';
	else
		for(i=0;i<cnt_0;i++)
			num[cnt-i]='\0';

	if((num[0]=='0')&&((num[1]>='1')&&(num[1]<='9')))
		for(i=0;i<=strlen(num);i++)
			num[i]=num[i+1];

	for(i=0;num[i]!='\0';i++)
		if(num[i]!='0')
			break;

	//	printf("%d %d\n",i,strlen(num));

	if(i==strlen(num))
		for(int j=1;j<strlen(num);j++)
			num[j]='\0';

	//	printf("%s\n",num);
}

void swap(char num1[],char num2[])
{
	int i;
	char tmp[61]={0};

	for(i=0;i<61;i++)
		tmp[i]=num1[i];

	for(i=0;i<61;i++)
		num1[i]=num2[i];

	for(i=0;i<61;i++)
		num2[i]=tmp[i];
}

int what_big(char num1[],char num2[])
{

	char num1_2[61]={0},num2_2[61]={0};
	int i;
	int big=1;

	for(i=0;i<strlen(num1);i++)
		num1_2[i]=num1[i];

	for(i=0;i<strlen(num2);i++)
		num2_2[i]=num2[i];

	integerize1(num1_2);
	integerize1(num2_2);

	if(strlen(num1_2)<strlen(num2_2))
		big=2;
	else if(strlen(num1_2)==strlen(num2_2)){
		for(i=0;i<strlen(num1_2);i++)
			if(num1_2[i]>num2_2[i])
				break;
			else if(num1_2[i]<num2_2[i]){
				big=2;
				break;
			}
	}

	return big;

}

void comma(char input[])
{
	int len=0,i;
	int count_p=0,point=0,sign=0;

	if(input[0]=='-')
		sign=1;

	if(sign==1){
		for(i=0;i<62;i++)
			input[i]=input[i+1];

		printf("-");
	}

	for(i=0;input[i]!='\0';i++)
	{
		len++;

		if(input[i]==46)
			point=1;
	}

	if(point==1)
	{
		for(i=0;input[i]!=46;i++)
			count_p++;
	}


	if(point==0)	//정수부분
	{
		for(i=len;i>0;i--)
		{
			if((i!=len)&&(i%3==0))
			{
				printf(",");
			}
			printf("%c",input[len-i]);
		}
	}
	else if(point==1) //소수부분
	{
		for(i=count_p;i>0;i--)
		{
			if((i!=count_p)&&(i%3==0))
			{
				printf(",");
			}
			printf("%c",input[count_p-i]);
		}

		printf(".");

		for(i=0;i<len-count_p-1;i++)
		{
			if((i!=0)&&(i%3==0))
			{
				printf(",");
			}
			printf("%c",input[count_p+1+i]);
		}
	}
	printf("\n");

	if(sign==1){
		for(i=62;i>0;i--)
			input[i]=input[i-1];

		input[0]='-';
	}
}

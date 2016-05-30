#include <stdio.h>
#include <string.h>

void integerize(char num[]);
void change_int(char num[],int);
void change_char(char num[],int);
void add(char a[],char b[],char c[]);
void sub(char a[],char b[],char c[]);

int main(void)
{
	char num1[61]={0},num2[61]={0},num3[61]={0},num4[61]={0};
	int i,j,k,strlen1=0,strlen2=0,strlen1_2=0,strlen2_2=0,strlen4=0,cnt=1,plus=0,minus=0;
	int stop=0;

	printf("첫번째 수 입력: ");
	scanf("%s",num1);
	printf("두번째 수 입력: ");
	scanf("%s",num2);

	integerize(num1);
	integerize(num2);

	printf("num1: %s\n",num1);
	printf("num2: %s\n",num2);

	for(i=0;num1[i]!='\0';i++)
		strlen1++;

	for(i=0;num2[i]!='\0';i++)
		strlen2++;

	printf("strlen1: %d strlen2: %d\n",strlen1,strlen2);

	if(strlen1>strlen2)
		for(j=0;j<strlen1-strlen2;j++)
			num2[strlen2+j]='0';

	printf("num2-2: %s\n",num2);

	for(k=0;num2[k]!=0;k++)
		strlen2_2++;

	printf("strlen2-2(1): %d\n",strlen2_2);

	for(i=0;strlen2_2-i>=strlen2;i++)
	{
		num2[strlen2_2-i]=0;

		for(j=1;;j++)//언제 sub와 add를 쓸 것인지 고민할 것
		{
			strlen2_2=0;

			sub(num1,num2,num1);

			for(k=0;num2[k]!=0;k++)
				strlen2_2++;

			printf("strlen2-2(2): %d\n",strlen2_2);

			printf("num2-2: %s\n",num2);

			for(k=0;k<strlen2_2;k++)
				if(num1[k]>num2[k])
					break;
				else if(num1[k]<num2[k])
				{
					stop=1;
					break;
				}

			printf("stop: %d\n",stop);


			if(stop==1)
			{
				printf("num1-3: %s\n",num1);
				printf("cnt: %d\n",j);
				num4[i]=j;
				break;
			}
		}
	}


	change_char(num4,i);

	printf("num1:%s\n",num1);
	printf("num2:%s\n",num2);
	printf("num4:%s\n",num4);

	return 0;
}

void integerize(char num[]) //실수 정수화 완료.
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

void add(char num1_1[],char num2_1[],char num3[])
{	
	char num1_2[61]={0},num2_2[61]={0};
	int len,i,plus=0,temp;
	int cnt1=0,cnt2=0;

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

	change_int(num1_2,cnt1);
	change_int(num2_2,cnt2);

	for(i=0;i<=len;i++)
	{
		num3[i]=(num1_2[i]+num2_2[i]+plus)%10;
		num3[i]+='0';

		if((num1_2[i]+num2_2[i]+plus)>9)
			plus=1;
		else
			plus=0;
	}

	if(num3[len]=='0')
		num3[len]=0;

	for(i=0;i<len/2;i++)
	{
		temp=num3[i];
		num3[i]=num3[len-1-i];
		num3[len-1-i]=temp;
	}
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

}

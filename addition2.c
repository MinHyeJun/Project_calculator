#include <stdio.h>
#include <string.h>

void integerize(char num[]);

int main(void)
{
	char num1_1[1024]={0},num2_1[1024]={0};
	char num1_2[1024]={0},num2_2[1024]={0};
	char num3[1024]={0};
	int len,i,plus=0,tmp;
	int cnt1=0,cnt2=0;

	printf("1번째 입력: ");
	scanf("%s",num1_1);
	printf("2번째 입력: ");
	scanf("%s",num2_1);

//	printf("%s\n",num1_1);
//	printf("%s\n",num2_1);

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

/*	printf("%s\n",num1_2);
	printf("%s\n",num2_2);
*/
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

/*	for(i=0;i<strlen(num1_1);i++)
	{
		printf("%d",num1_2[i]);
	}
	printf("\n");

	for(i=0;i<strlen(num2_1);i++)
	{
		printf("%d",num2_2[i]);
	}
	printf("\n");
*/


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

	for(i=len;i>=0;i--)
		printf("%c",num3[i]);

	return 0;
}

void integerize(char num[]) //실수 정수화 완료.
{
	int i,point=0,cnt=0,cnt_0=0,cnt_f=0,cnt_str=0;
	//i는 for문 임시변수, point 소수점의 위치,cnt 0을 붙인 후의 배열의 길이
	//cnt_0 앞의 0을 제거하기 위한 0의 개수
	//cnt_f 소수점 이후부터의 배열길이, cnt_str 처음 입력 받은 배열의 길이

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

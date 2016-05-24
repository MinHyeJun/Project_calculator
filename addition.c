#include <stdio.h>
#include <string.h>

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

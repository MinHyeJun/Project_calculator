#include <stdio.h>
#include <string.h>
int main(void)
{
	char input[100];
	int len=0,i;

	printf("입력: ");
	scanf("%s",input);

	for(i=0;input[i]!='\0';i++)
		len++;
							
	printf("출력: ");
								
	for(i=len;i>0;i--)
	{
		if((i!=len)&&(i%3==0))
		{
			printf(",");
		}
		printf("%c",input[len-i]);
	}
		printf("\n");

	return 0;
}

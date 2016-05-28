void integerize(char num[]) //실수 정수화 완료. ex)1.3 >> 1300000000, 0.00002 >> 20000
{
	int i,point,cnt_0=0,cnt=0;
	//i는 for문 위한 임시 변수, point는 소수점의 위치, cnt_0은 앞의 0을 제거하기위한 0의 개수,cnt는 배열의 길이

	for(i=0;num[i]!='\0';i++)
	{
		if(num[i]=='.')
		{
			point=i;

			for(i=point;num[i]!='\0';i++)
			{	
				cnt++;
				num[i]=num[i+1];
			}

			break;
		}
	}

	for(i=point-1+cnt;i<=point-1+9;i++)
		num[i]='0';

	for(i=0;num[i]=='0';i++)
		cnt_0++;
	
	cnt=0;

	for(i=0;num[i]!='\0';i++)
		cnt++;

	for(i=0;i<cnt;i++)
		num[i]=num[i+cnt_0];
}

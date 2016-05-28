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

void swap(char num1[],char num2[])
{
	int change=0,i;
	char tmp[61]={0};

	if(strlen(num1)<strlen(num2))
	{
		change=1;
	}else if(strlen(num1)==strlen(num2)){
		for(i=0;i<strlen(num1);i++)
			if(num1[i]>num2[i])
				break;
			else if(num1[i]<num2[i]){
				change=1;
				break;
			}
	}

	if(change==1)
	{
		for(i=0;i<61;i++)
			tmp[i]=num1[i];

		for(i=0;i<61;i++)
			num1[i]=num2[i];

		for(i=0;i<61;i++)
			num2[i]=tmp[i];
	}
}

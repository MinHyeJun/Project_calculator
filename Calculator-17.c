/*
   해결해야할 문제들
   1. 소수 10번째 자리에서 올림을 해줘야하는가?
   2. * 8 연산시 error가 아닌 0이 뜸
   3. B = -A * 1000000이 안됨
   4. 
   */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void division(char a[],char b[],char c[]);  //나누기
void rem(char a[],char b[],char c[]);  //나머지
void sub(char a[],char b[],char c[]);  //빼기
void mult(char a[],char b[],char c[]);
void sum(char a[],char b[],char c[]);  //더하기
void integerize1(char num[]);  //소수점을 빼고 나머지 소수자리를 모두 0으로 채워 정수화 0.000001 >> 1000
void integerize2(char num[]);  //소수점을 제거하여 정수화 22.22 >> 2222
void change_int(char num[],int);  //char 형으로 저장된 값들을 int형으로 변환
void change_char(char num[],int);  //int 형으로 저장된 값들을 char형으로 변환
void floatlize(char num[]);  //소수를 정수화 시켜 계산한 값을 소수로 전환
void floatlize2(char num[]);
void swap(char num1[],char num2[]);  //두 배열의 값을 서로 바꿈
int what_big(char num1[],char num2[]);  //어떤 수가 더 큰가 판별
void comma(char a[]);  //숫자 세 자리마다 콤마 출력

int main(void)
{
	char input[100000]={0},Var[10]={0},Var_v[10][62]={0},SVar[10]={0},SVar_v[10][62]={0},num[3][62]={0};
	//input 입력받는 계산식/Var 저장되는 변수/Var_v 변수의 값/SVar, SVar_v 변수값을 읽어올 때 필요한 배열/num[3] 계산을 위해 수를 저장하기 위한 배열
	char view_var[4]="VAR",clear[6]="clear",end[4]="end",save_v[5]="save",load_v[5]="load";
	//view_var VAR 명령 위해 명령어 저장/clear clear명령 위해 저장/end end명령 위해 저장/save_v save 명령 위해 저장/load_v load 명령 위해 저장
	char c,sign;
	//c 식을 입력받기 위한 임시변수/sign 부호 판별
	int i,j,k,var_cal=0,var_before,var_save,var_sp,var_cnt=0,cnt1,cnt2,var1,var2,cal;
	//i,j,k for문을 위한 변수/var_before  변수 저장을 위한 계산/var_cnt 변수 n번째 표시/cnt1,cnt2 계산할 숫자의 길이/var1,2 변수 유무/cal 변수 저장이 아닌 계산임을 나타냄
	int tmp,big,what_m=0,error,point;
	//tmp 계산한 수와, 식에서 수가 들어갈 자리의 차/big 계산할 두 수 중 더 큰 수를 판별/what_m 어떤수가 음수인지 판별/error 에러 표시/point 소수점의 자리
	char Error[60]={'~','`','!','@','#','$','^','&','(',')','_','\\','{','}','[',']',';',':','?','<','>','\'','\"',','};
	//Error 계산식에서 제공하지 않는 특수 기호 모음

	printf("Start....\n");  // 계산 시작

	while(1) // 사용자가 종료할 때까지 무한반복
	{

		FILE *save=NULL;

		printf("(Input)");

		c=0;  // 입력임시변수 초기화
		i=0;  // 연산자의 위치를 나타낼 i 초기화
		point=0;  //소수 자리 표시할 변수 초기화
		error=0;  //error 상태 표시 변수 초기화

		for(int i=0;i<62;i++)  // 입력받은 식 초기화
			input[i]=0;

		while((c=getchar())!='\n') //계산식 입력
			input[i++]=c;

		var_cal=0;  //변수 계산식 유무 초기화
		var_before=0;  //기존에 입력받았던 변수인지 확인 초기화
		var_save=0;  //변수 저장하는 식인가 판별 초기화
		var_sp=0;  //기존의 입력받았던 변수의 값 출력하는 식에서의 변수가 몇번째 자리인가 저장 초기화

		/* 명령어 확인*/
		if(strcmp(input,clear)==0){  //clear 명령 확인
			system("clear");
			continue;
		}else if(strcmp(input,end)==0)  //end 명령 확인
			exit(0);
		else if(strcmp(input,save_v)==0){  //save 명령 확인

			int i;

			if((save=fopen("save.txt","w"))==NULL)  //파일을 열 수 없나 확인 
			{
				printf("오류: save 파일을 열 수 없습니다.\n");
				continue;
			}

			for(i=0;Var[i]!='\0';i++)  //변수값 기록
				fprintf(save,"%c = %s\n",Var[i],Var_v[i]);

			fclose(save);

			if(i==0)  //기록할 게  없다면 에러 출력
				error=1;
			else
				continue;

		}else if(strcmp(input,load_v)==0){  //load 명령 확인

			int i=0;

			if((save=fopen("save.txt","r"))==NULL)  //파일을 열 수 없나 확인
			{
				printf("오류: save 파일을 열 수 없습니다.\n");
				continue;
			}

			while((fscanf(save,"%c = %s\n",&SVar[i],SVar_v[i]))!=EOF)  //변수값 읽어오기
			{
				int j;

				for(j=0;j<var_cnt;j++)
					if((SVar[i]==Var[j])||(SVar[i]==Var[j]-32)||(SVar[i]==Var[j]+32))
					{
						Var[j]=SVar[i];
						strcpy(Var_v[j],SVar_v[i]);
						var_cnt++;
					}

				if(j==var_cnt)
				{	
					Var[var_cnt]=SVar[i];
					strcpy(Var_v[var_cnt],SVar_v[i]);

					var_cnt++;
				}
			}

			fclose(save);

			continue;

		}else if(strcmp(input,view_var)==0){ //VAR 명령 확인
			if(var_cnt>0){  //변수가 있을 경우 출력
				for(i=0;i<var_cnt;i++)
				{
					printf("       %c = ",Var[i]);
					comma(Var_v[i]);
				}
			}else{
				printf("       = 정의된 변수 없음\n");  //출력할 변 수 없을 경우 출력
			}

			continue;
		}


		printf("       = "); //값 계산하여 출력할 부분

		if((((input[0]>='a')&&(input[0]<='z'))||((input[0]>='A')&&(input[0]<='Z')))||((strlen(input)==2)&&((input[1]>='a')&&(input[1]<='z'))||((input[1]>='A')&&(input[1]<='Z')))) // 변수 인식
		{
			if((input[0]!='-')&&(strlen(input)==2)) //잘못된 형태의 식
				error=1;
			else{
				if(strlen(input)==2){
					for(i=0;i<10;i++)  // 변수가 이전에 있던 변수인지 확인
						if((Var[i]==input[1])||(Var[i]==input[1]-32)||(Var[i]==input[1]+32))
							break;
				}else{
					for(i=0;i<10;i++)  // 변수가 이전에 있던 변수인지 확인
						if((Var[i]==input[0])||(Var[i]==input[0]-32)||(Var[i]==input[0]+32))
							break;
				}

				if((strlen(input)>2)&&(input[2]=='=')){ //올바른 식의 형태
					if(i<10)  //변수가 이전에 있던 변수임
					{
						Var[i]=input[0];
						var_before=i+1;
					}else if(i==10){  //새로운 변수임
						if(var_cnt>=10)  //이제까지 받은 변수가 10개가 됨>>에러
						{
							error=1;
						}else{  // 저장
							var_save=1;
							Var[var_cnt]=input[0];
							var_cnt++;
						}
					}
					var_cal=1;
				}else if((strlen(input)==1)||((strlen(input)==2)&&(input[0]=='-')))  //연산이 변수 하나뿐임
					if(i==10){  // 새로운 변수
						printf("undefined\n");  //저장되지 않았음을 출력
						continue;
					}else if(i<10){  //이전에 있던 변수임
						var_sp=i+1;
						var_cal=1;
					}
			}
		}

		for(i=0;input[i]!='\0';i++)  //계산식이 제공하지 않는 특수문자가 있나 확인
			for(j=0;Error[j]!='\0';j++)
				if(input[i]==Error[j])
					error=1;

		if(error==1)  //에러가 있었던 경우 에러 출력
		{
			printf("error\n");
			continue;
		}

		for(i=0;input[i]!='\0';i++)  //연산 시작
		{
			cnt1=0;  //첫번째 수 길이 초기화
			cnt2=0;  //두번째 수 길이 초기화
			var1=0;  //첫번째 수가 변수인가 초기화
			var2=0;  //두번째 수가 변수인가 초기화
			sign='+';  //부호를 +로 초기화
			big=0;  //어떤 수가 더 큰지 판별 초기화
			what_m=0;  //어떤 수가 마이너스 인지 판별 초기화

			for(j=0;j<62;j++){  //계산할 때 필요한 배열 초기화
				num[0][j]=0;
				num[1][j]=0;
				num[2][j]=0;
			}
			cal=0;  //계산에 들어감을 확인 초기화

			if((input[i]=='/')||(input[i]=='*')||(input[i]=='%')) //우선순위 연산 나누기, 곱하기, 나머지 초기화
			{
				if((input[i-1]!=' ')||(input[i+1]!=' '))  //연산자 앞뒤에 띄어쓰기 없을 경우 오류 출력
				{
					printf("1\n");
					error=1;
					break;
				}

				cal=1;  //계산함을 확인

				for(j=i-2;j>=0;j--) //첫번째 수 확인
				{
					if(((input[j]>='a')&&(input[j]<='z'))||((input[j]>='A')&&(input[j]<='Z'))){  //변수가 들어가나 확인
						var1=1;  //변수임 확인
						cnt1++;
						if(input[j-1]=='-')
							cnt1++;
						break; 
					}else if(((input[j]<'0')||(input[j]>'9'))&&(input[j]!='-')&&(input[j]!='.'))
						//숫자가 아니거나 부호가아니거나 소수점이 아닐때까지 입력받기
						break;
					else if(input[j]=='-')  //만약 마이너스를 만났을 경우
						if((j!=0)&&((input[j-1]=='/')||(input[j-1]=='%')||(input[j-1]=='*')||(input[j-1]=='+')||(input[j-1]=='-')))
							break;
					cnt1++;
				}

				for(j=i+2;j<=62;j++) //두번째 수 확인
				{
					if(((input[j]>='a')&&(input[j]<='z'))||((input[j]>='A')&&(input[j]<='Z'))){
						var2=1;
						cnt2++;
						if(input[j-1]=='-')
							cnt2++;
						break; 
					}else if(((input[j]<'0')||(input[j]>'9'))&&(input[j]!='-')&&(input[j]!='.'))
						break;
					else if(input[j]=='-')
						if((j!=i+2)&&((input[j-1]=='/')||(input[j-1]=='%')||(input[j-1]=='*')||(input[j-1]=='+')||(input[j-1]=='-')))
							break;
					cnt2++;
				}

				//첫번째 수 저장
				if((cnt1>0)&&(var1==0)){  //첫번째수가 존재하나 변수가 아님
					for(j=0;j<cnt1;j++)
						num[0][j]=input[i-1-cnt1+j];  //첫번째 수 연산 위해 따로 저장
				}else if(var1==1){  //첫번째 수가 변수임
					for(j=0;j<10;j++)
						if((Var[j]==input[i-2])||(Var[j]==input[i-2]-32)||(Var[j]==input[i-2]+32)) //해당 변수와 일치하는 저장된 변수 인식
							break;

					if(j==10)  //저장된 변수가 없음 >> 에러
					{
						error=1;
						break;
					}

					for(k=0;k<62;k++) //해당 변수값을 연산 위해 따로 저장
						num[0][k]=Var_v[j][k];

				}

				//두번째 수 저장
				if((cnt2>0)&&(var2==0)){  //두번째 수가 존재하나 변수가 아님(첫번째수와 같은 방식)
					for(j=0;j<cnt2;j++)
						num[1][j]=input[i+2+j];
				}else if(var2==1){
					for(j=0;j<10;j++)
						if((Var[j]==input[i+2])||(Var[j]==input[i+2]-32)||(Var[j]==input[i+2]+32))
							break;

					if(j==10)
					{
						error=1;
						break;
					}

					for(k=0;k<62;k++)
						num[1][k]=Var_v[j][k];
				}

				if(var1==1)
					if(cnt1==2)
						if(num[0][0]=='-')
							for(k=0;k<61;k++)
								num[0][k]=num[0][k+1];
						else if(num[0][0]!='-'){
							for(k=61;k>=0;k--)
								num[0][k+1]=num[0][k];
							num[0][0]='-';
						}
				if(var2==1)
					if(cnt2==2)
						if(num[1][0]=='-')
							for(k=0;k<61;k++)
								num[1][k]=num[1][k+1];
						else if(num[1][0]!='-'){
							for(k=61;k>=0;k--)
								num[1][k+1]=num[1][k];
							num[1][0]='-';
						}

				if((num[0][0]=='-')&&(num[1][0]=='-')){  // 둘 다 음수임을 확인
					for(k=0;k<61;k++)
					{
						num[0][k]=num[0][k+1];  //부호를 제거함(양수가 되므로)
						num[1][k]=num[1][k+1];
					}
				}else if((num[0][0]=='-')||(num[1][0]=='-')){ //둘 중 하나만 음수임
					sign='-';  //부호는 마이너스
					if(num[0][0]=='-')  //첫번째 수가 음수일 경우 첫번째 수의 부호만 제거
						for(k=0;k<61;k++)
							num[0][k]=num[0][k+1];
					else  //두번째 수가 음수일 경우 두번째 수의 부호만 제거
						for(k=0;k<61;k++)
							num[1][k]=num[1][k+1];
				}

				for(k=0;k<62;k++){  //첫번째 수가 소수인 경우 소수점 판별
					if(num[0][k]=='.')
						point=k;
					if(num[0][k]=='\0')
						break;
				}

				if((k==0)||((point==0)&&(k>50))||(point>=51)||((point>0)&&(k-point>10))){
					//수가 존재하지 않거나 정수부분이 50이 넘어가거나 소수부분이 9자리를 넘어갈 경우 에러
					error=1;
					break;
				}

				point=0;  //포인트 판별 초기화

				for(k=0;k<62;k++){  //두번째수가 소수인 경우 소수점 판별
					if(num[1][k]=='.')
						point=k;
					if(num[1][k]=='\0')
						break;
				}

				if((i==0)||((point==0)&&(k>50))||(point>=51)||((point>0)&&(k-point>10))){
					error=1;
					break;
				}

				if(input[i]=='/')  //연산자가 나누기인 경우
					division(num[0],num[1],num[2]);
				else if(input[i]=='*')  //연산자가 곱하기인 경우
					mult(num[0],num[1],num[2]);
				else if(input[i]=='%')  //연산자가 나머지인 경우
					rem(num[0],num[1],num[2]);
			}

			if((sign=='-')&&(num[2][0]!='0'))  //부호가 마이너스이고, 연산 답이 0이 아닌 경우 부호 붙이기
			{
				for(j=61;j>=0;j--)
					num[2][j+1]=num[2][j];
				num[2][0]='-';
			}

			if(cal==1)  //연산이 실행 된 경우
			{
				if(cnt1+cnt2+3<strlen(num[2])){  //연산한 두 숫자 사이 빈 자리보다 답의 배열 길이가 더 긴 경우 자리를 만들기
					tmp=strlen(num[2])-(cnt1+cnt2+3);
					for(j=strlen(input)-i-1-cnt2-1;j>=0;j--)
						input[i+1+cnt2+tmp+j]=input[i+1+cnt2+j];
				}else if(cnt1+cnt2+3>strlen(num[2])){  //짧은 경우 수식을 남는 자리만큼 땡기기
					tmp=cnt1+cnt2+3-strlen(num[2]);
					for(j=0;j<strlen(input)-i-1-cnt2+tmp;j++)
						input[i+1+cnt2-tmp+j]=input[i+1+cnt2+j];
				}

				for(j=0;j<strlen(num[2]);j++) //계산된 값 수식에 넣기
					input[i-1-cnt1+j]=num[2][j];

				i=0;  //연산 초기화 후 다시 처음부터 연산시작
			}else
				continue; //연산 안했으면 계속해서 연산자 찾기
		}


		if(error==1)
		{
			printf("error\n");
			continue;
		}


		for(i=0;input[i]!='\0';i++) //다음 연산자 더하기, 빼기
		{
			cnt1=0;
			cnt2=0;
			var1=0;
			var2=0;
			sign='+';
			big=0;
			what_m=0;

			for(j=0;j<62;j++){
				num[0][j]=0;
				num[1][j]=0;
				num[2][j]=0;
			}
			cal=0;

			if((input[i]=='+')||((input[i]=='-')&&(input[i+1]==' '))){  //더하기이거나 부호가 아닌 빼기인 경우

				if((input[i-1]!=' ')||(input[i+1]!=' '))
				{
					error=1;
					break;
				}

				cal=1;

				for(j=i-2;;j--)
				{
					if(((input[j]>='a')&&(input[j]<='z'))||((input[j]>='A')&&(input[j]<='Z'))){
						var1=1;
						cnt1++;
						if(input[j-1]=='-')
							cnt1++;
						break; 
					}else if(((input[j]<'0')||(input[j]>'9'))&&(input[j]!='-')&&(input[j]!='.'))
						break;
					else if(input[j]=='-')
						if((j!=0)&&((input[j-1]=='/')||(input[j-1]=='%')||(input[j-1]=='*')||(input[j-1]=='+')||(input[j-1]=='-')))
							break;
					cnt1++;
				}

				for(j=i+2;;j++)
				{
					if(((input[j]>='a')&&(input[j]<='z'))||((input[j]>='A')&&(input[j]<='Z'))){
						var2=1;
						cnt2++;
						if(input[j-1]=='-')
							cnt2++;
						break; 
					}else if(((input[j]<'0')||(input[j]>'9'))&&(input[j]!='-')&&(input[j]!='.'))
						break;
					else if(input[j]=='-')
						if((j!=i+2)&&((input[j-1]=='/')||(input[j-1]=='%')||(input[j-1]=='*')||(input[j-1]=='+')||(input[j-1]=='-')))
							break;
					cnt2++;
				}

				if((cnt1>0)&&(var1==0)){
					for(j=0;j<cnt1;j++)
						num[0][j]=input[i-1-cnt1+j];
				}else if(var1==1){
					for(j=0;j<10;j++)
						if((Var[j]==input[i-2])||(Var[j]==input[i-2]-32)||(Var[j]==input[i-2]+32))
							break;

					if(j==10)
					{
						error=1;
						break;
					}

					for(k=0;k<62;k++)
						num[0][k]=Var_v[j][k];

				}

				if((cnt2>0)&&(var2==0)){
					for(j=0;j<cnt2;j++)
						num[1][j]=input[i+2+j];
				}else if(var2==1){
					for(j=0;j<10;j++)
						if((Var[j]==input[i+2])||(Var[j]==input[i+2]-32)||(Var[j]==input[i+2]+32))
							break;

					if(j==10)
					{
						error=1;
						break;
					}

					for(k=0;k<62;k++)
						num[1][k]=Var_v[j][k];
				}
				if(var1==1)
					if(cnt1==2)
						if(num[0][0]=='-')
							for(k=0;k<61;k++)
								num[0][k]=num[0][k+1];
						else if(num[0][0]!='-'){
							for(k=61;k>=0;k--)
								num[0][k+1]=num[0][k];
							num[0][0]='-';
						}
				if(var2==1)
					if(cnt2==2)
						if(num[1][0]=='-')
							for(k=0;k<61;k++)
								num[1][k]=num[1][k+1];
						else if(num[1][0]!='-'){
							for(k=61;k>=0;k--)
								num[1][k+1]=num[1][k];
							num[1][0]='-';
						}

				//부호 판별
				if((num[0][0]=='-')&&(num[1][0]=='-')){  //둘 다 마이너스인 경우
					for(k=0;k<61;k++)  //각 수의 부호 삭제
					{
						num[0][k]=num[0][k+1];  
						num[1][k]=num[1][k+1];
					}

					big=what_big(num[0],num[1]);  //무엇이 더 큰가 판별

					if(input[i]=='+')  //더하기 연산자일 경우 무조건 부호는 마이너스
						sign='-';
					else if(input[i]=='-'){  //빼기 연산자일 경우 크기에 따라 부호를 바꿈
						if(big==1)
							sign='-';
						else if(big==2)
							swap(num[0],num[1]);  //연산은 큰수에서 작은수로 되기 때문에 큰 수에서 작은 수 연산을 위한 배열 교환 작업
					}

				}else if((num[0][0]=='-')||(num[1][0]=='-')){  //둘 중 하나가 마이너스인 경우
					if(num[0][0]=='-')  //첫번째 수가 마이너스인 경우
					{
						for(k=0;k<61;k++)
							num[0][k]=num[0][k+1];  //부호 삭제

						what_m=1;  //첫번째 수가 마이너스임을 표시
					}else{  //두번째수가 마이너스인 경우
						for(k=0;k<61;k++)  
							num[1][k]=num[1][k+1];

						what_m=2;
					}

					big=what_big(num[0],num[1]);  //무엇이 더 큰가 비교

					if(what_m==1){	 //첫번째 수가 마이너스인 경우의 연산
						if(input[i]=='+'){  //연산자가 더하기일 경우 필요에 따라 연산을 바꾸고 부호를 붙임
							if(big==1){
								input[i]='-';
								sign='-';
							}else if(big==2){
								input[i]='-';
								swap(num[0],num[1]);
							}
						}else if(input[i]=='-'){  //연산자가 마이너스일 경우 부호를 마이너스로 바꾸고 연산자를 더하기로 바꿈
							sign='-';
							input[i]='+';
						}
					}else if(what_m==2){  //두번째 수가 마이너스인 경우의 연산
						if(input[i]=='+'){ //필요에 따라 연산자를 바꾸거나 부호를 마이너스로 바꾸거나함
							if(big==2)  
							{
								input[i]='-';
								sign='-';
								swap(num[0],num[1]);
							}
						}else if(input[i]=='-') 
							input[i]='+';
					}

				}else if(input[i]=='-'){ //부호가 마이너스일 경우
					big=what_big(num[0],num[1]); //무엇이 더 큰가 비교 후 필요에 따라 연산

					if(big==2)
					{
						sign='-';
						swap(num[0],num[1]);
					}
				}

//				printf("num[0]:%s\n",num[0]);
//				printf("num[1]:%s\n",num[1]);
//				printf("sign:%c\n",sign);

				point=0;

				for(k=0;k<62;k++){
					if(num[0][k]=='.')
						point=k;
					if(num[0][k]=='\0')
						break;
				}

				if((k==0)||((point==0)&&(k>50))||(point>=51)||((point>0)&&(k-point>10))){
					error=1;
					break;
				}

				point=0;

				for(k=0;k<62;k++){
					if(num[1][k]=='.')
						point=k;
					if(num[1][k]=='\0')
						break;
				}

				if((k==0)||((point==0)&&(k>50))||(point>=51)||((point>0)&&(k-point>10))){
					error=1;
					break;
				}

				if(input[i]=='-'){  //마이너스 연산일 경우
					integerize1(num[0]);  //마이너스 연산 경우 나누기에 응용을 위해 정수화와 소수화를 따로 함
					integerize1(num[1]);
					sub(num[0],num[1],num[2]);
					floatlize(num[2]);
				}else if(input[i]=='+'){  //더하기 연산일 경우
					sum(num[0],num[1],num[2]);
					floatlize(num[2]);
				}
			}

			if((sign=='-')&&(num[2][0]!='0'))  //부호가 마이너스인 경우
			{
				for(j=61;j>=0;j--)
					num[2][j+1]=num[2][j];

				num[2][0]='-';
			}

			if(cal==1)  //연산을 한 경우
			{
				if(cnt1+cnt2+3<strlen(num[2])){
					tmp=strlen(num[2])-(cnt1+cnt2+3);
					for(j=strlen(input)-i-1-cnt2-1;j>=0;j--)
						input[i+1+cnt2+tmp+j]=input[i+1+cnt2+j];
				}
				else if(cnt1+cnt2+3>strlen(num[2])){
					tmp=cnt1+cnt2+3-strlen(num[2]);
					for(j=0;j<strlen(input)-i-1-cnt2+tmp;j++)
						input[i+1+cnt2-tmp+j]=input[i+1+cnt2+j];
				}

				for(j=0;j<strlen(num[2]);j++)
					input[i-1-cnt1+j]=num[2][j];

				i=0;
			}else
				continue; //연산 안했으면 계속해서 연산자 찾기

//			printf("2. 다음 연산:%s\n",input);
		}

		if(var_cal==0){  //변수가 있는 연산이 아닐경우
			for(i=0;input[i]!='\0';i++)  //최종답을 검사하여 잘못된 결과인 경우 에러출력
			{
				if((i!=0)&&(input[i]=='-')){
					error=1;
				}else if(input[i]==' '){
					error=1;
				}
			}
		}else if(var_cal==1){  //변수가 있는 연산일 경우 최종 답을 검사하여 잘못된 결과인 경우 에러 출력

			for(i=4;input[i]!='\0';i++)
			{
				if((i!=4)&&(input[i]=='-')){
					error=1;
				}else if(input[i]==' '){
					error=1;
				}
			}
		}
		point=0;

		for(k=0;input[k]!='\0';k++){
			if(input[k]=='.')
				point=k;
		}

		if(var_cal==0)  //변수가 없는 연산인 경우 결과가 자리값을 넘어가면 에러 출력
		{
			if((k==0)||((input[0]!='-')&&(((point==0)&&(k>50))||(point>=51)||((point>0)&&(k-point>10))))){
				error=1;
			}else if((input[0]=='-')&&(((point==0)&&(k>51))||(point>=52)||((point>0)&&(k-point>10))))
				error=1;
		}else if(var_cal==1){  //변수가 있는 연산인 경우의 결과가 자리값을 넘어가면 에러 출력
			if(((k<5)&&(var_sp==0))||((input[0]!='-')&&(((point==0)&&(k-4>50))||(point-4>=51)||((point>0)&&(k-point>10))))){
				error=1;
			}else if((input[0]=='-')&&(((point==0)&&(k-4>51))||(point-4>=52)||((point>0)&&(k-point>10)))){
				error=1;
			}
		}

		if(error==1)
		{
			if((var_cal==1)&&(var_save==1))  //에러인 경우 잘못 저장된 변수는 삭제함
			{
				Var[var_cnt-1]=0;
				var_cnt--;
			}

			printf("error\n");
			continue;
		}

		if(var_cal==1)  //변수 계산인 경우
		{
			if(var_before>0){  //이전에 있던 변수에 새롭게 저장하는 경우
				for(i=0;;i++)
				{
					Var_v[var_before-1][i]=input[4+i];
					input[i]=input[4+i];

					if(input[i]=='\0')
						break;
				}
			}else if(var_save==1){  //변수를 새로이 저장하는 경우
				for(i=0;;i++)
				{
					Var_v[var_cnt-1][i]=input[4+i];
					input[i]=input[4+i];

					if(input[i]=='\0')
						break;
				}
			}
		}

		if(var_cal==1){  //변수 계산을 한 경우
			if(var_sp>0){  //변수 확인을 위한 연산인 경우
				if((strlen(input)==1))  //변수만 출력?
					comma(Var_v[var_sp-1]);
				else if((strlen(input)==2)){  //-변수 출력?
					printf("-");
					comma(Var_v[var_sp-1]);
				}
			}else if(var_before>0)  //이전의 변수를 출력하는 경우
				comma(Var_v[var_before-1]);
			else if(var_save==1) //저장된 변수를 출력하는 경우
				comma(Var_v[var_cnt-1]);
		}else  //그냥 계산한 값을 출력하는 경우
			comma(input);

	}
	return 0;  //종료
}

void division(char num1[],char num2[],char num4[])  //나누기 연산
{

	int i,j,k,point=0,strlen=0,strlen_p=0,strlen1=0,strlen2=0,strlen1_2=0,strlen2_2=0,strlen4=0,plus=0,minus=0;
	int stop=0;
	int tmp=0;

	for(i=0;num2[i]!='\0';i++)
	{
		if(num2[i]=='.')
			point=1;
		strlen2++;
	}

	if(point==1)
		for(i=strlen2-1;num2[i]!='.';i--)
			strlen_p++;

	integerize1(num1);
	integerize2(num2);


	for(i=0;num1[i]!='\0';i++)
		strlen1++;

	for(i=0;i<strlen_p;i++)
		num1[strlen1+i]='0';

	strlen1=0;
	strlen2=0;

	for(i=0;num1[i]!='\0';i++)
		strlen1++;

	for(i=0;num2[i]!='\0';i++)
		strlen2++;

	if(strlen1>strlen2)
		for(j=0;j<strlen1-strlen2;j++)
			num2[strlen2+j]='0';

	for(i=0;num2[i]!='\0';i++)
		strlen2_2++;

	strlen1_2=strlen1;

	for(i=0;strlen2_2>=strlen2;i++)
	{
		num2[strlen2_2]=0;

		for(j=0;;j++)
		{
			stop=0;

			if(strlen1_2<strlen2_2)
			{
				stop=1;
				tmp=1;
			}else if(strlen1_2==strlen2_2){
				for(k=0;k<strlen2_2;k++)
					if(num1[k]>num2[k])
						break;
					else if(num1[k]<num2[k])
					{
						stop=1;
						tmp=2;
						break;
					}
			}

			if((stop==1)||(num1[0]=='0')){
				num4[i]=j;
				break;
			}else{
				sub(num1,num2,num1);

				strlen1_2=0;

				for(k=0;num1[k]!='\0';k++)
					strlen1_2++;

				if(j==1)
					stop=1;
			}
		}
		strlen2_2--;

	}

	change_char(num4,i);

	floatlize(num4);

}

void rem(char num1[],char num2[],char num3[])  //나머지 연산
{
	int i,j,k,strlen1=0,strlen2=0,strlen1_2=0,strlen2_2=0,strlen4=0,plus=0,minus=0;
	int stop=0;

	integerize1(num1);
	integerize1(num2);

	for(i=0;num1[i]!='\0';i++)
		strlen1++;

	for(i=0;num2[i]!='\0';i++)
		strlen2++;

	if(strlen1>strlen2)
		for(j=0;j<strlen1-strlen2;j++)
			num2[strlen2+j]='0';

	for(i=0;num2[i]!='\0';i++)
		strlen2_2++;

	strlen1_2=strlen1;

	for(i=0;strlen2_2>=strlen2;i++)
	{
		num2[strlen2_2]=0;

		for(j=0;;j++)
		{
			stop=0;

			if(strlen1_2<strlen2_2)
			{
				stop=1;
			}else if(strlen1_2==strlen2_2){
				for(k=0;k<strlen2_2;k++)
					if(num1[k]>num2[k])
						break;
					else if(num1[k]<num2[k])
					{
						stop=1;
						break;
					}
			}

			if(stop==1){
				break;
			}else{
				sub(num1,num2,num1);

				strlen1_2=0;

				for(k=0;num1[k]!='\0';k++)
					strlen1_2++;

			}
		}
		strlen2_2--;

	}

	floatlize(num1);

	for(i=0;i<62;i++)
		num3[i]=num1[i];
}

void mult(char num1_1[],char num2_1[],char num4[])  //곱하기 연산
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
		temp=0;
	}

	if(num3[len3]=='0')
		num3[len3]=0;
	if(num3[len3-1]=='0')
	{
		num3[len3-1]=0;
		extra=1;
	}


	for(i=0;i<(len3-extra)/2;i++)
	{
		tmp=num3[i];
		num3[i]=num3[len3-extra-1-i];
		num3[len3-extra-1-i]=tmp;
	}


	floatlize2(num3);

	for(i=0;i<num3[i]!='\0';i++)
		num4[i]=num3[i];

}

void sum(char num1_1[],char num2_1[],char num3[])  //더하기 연산
{
	char num1_2[62]={0},num2_2[62]={0};
	int len,i,plus=0,temp;
	int cnt1=0,cnt2=0;

	integerize1(num1_1);
	integerize1(num2_1);

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

void integerize1(char num[]) //실수 정수화(뒤에 9자리)
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

void integerize2(char num[]) //실수 정수화2(뒤에 18자리)
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

void change_int(char num[],int cnt) // 문자열 정수화
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

void change_char(char num[],int cnt)//정수열 문자열화
{
	int i;
	for(i=0;i<cnt;i++)
		num[i]+='0';
}

void sub(char num1_1[61],char num2_1[61],char num3[61]) //빼기
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

	if(i==strlen(num3))
		for(int j=1;j<strlen(num3);j++)
			num3[j]='\0';
}

void floatlize(char num[])  //소수화(뒤에 9자리 삭제)
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

	if(i==strlen(num))
		for(int j=1;j<strlen(num);j++)
			num[j]='\0';
}

void floatlize2(char num[])  //소수화2(뒤에 18자리 삭제)
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

	if(i==strlen(num))
		for(int j=1;j<strlen(num);j++)
			num[j]='\0';
}

void swap(char num1[],char num2[])  //문자열 교환
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

int what_big(char num1[],char num2[])  //어떤 수가 더 큰가
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

void comma(char input[])  //세자리마다 콤마찍기
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


	if(point==0)	//정수
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
	else if(point==1) //소수
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

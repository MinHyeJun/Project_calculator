 #include <stdio.h>
 #include <string.h>
 #define StoD(x) (x==0? 0:x-'0') //숫자를 문자열로 입력받은 후 숫자로 바꿈
  void mod(char*arr,int len);
       int main(){
       char a[3][10002]={0}; //배열 3개 선언하면서 0으로 초기화
       int len,i;
       printf("A= ");
       scanf("%s",a[0]); //a[0]에 숫자를 문자로 입력받음
      printf("B= ");
      scanf("%s",a[1]); //a[1]에 숫자를 문자로 입력받음
 
      if(strlen(a[0])>strlen(a[1])){ //배열의 길이를 int형으로 변환
          len=strlen(a[0]);
      }else len=strlen(a[1]); // A,B중에 더 긴 문자열의 길이 입력받음
 
      for(i=0;i<=len;i++){
      a[2][i]=((StoD(a[0][i]))%(StoD(a[1][i])));
      }
      if(a[2][len]=='0') a[2][len]=0;
      printf("A%%B=%s\n",a[2]);
      return 0;
  }
  void mod(char*arr,int len){
      char temp;
      int i;
      for(i=0;i<len;i++){
          temp=arr[i];
          arr[i]=arr[len-1-i];
          arr[len-1-i]=temp;
  }
}

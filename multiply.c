#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000




void swap( char* arr, int x, int y )
{
    char temp;
    temp = arr[x];
    arr[x] = arr[y];
    arr[y] = temp;




}




void rev(char* arr)
{
    int i;
    long length;
    length = strlen(arr);




    for(i=0 ; i< length/2 ; i++)
        swap(arr, i, length-i-1 );
}//변수길이의 절반만큼을 인수로 받고 교체를 swap해줌




void process( char* arr1, char* arr2, char* arr3 ) // 실질적인 곱셈함수
{
    long len1, len2, carry=0, temp=0;
    int i, j; // i 는 새로 만들 결과값의 자릿수




    len1 = strlen(arr1);
    len2 = strlen(arr2);




    for(i=0 ;i< len1+len2-1 ; i++)
    {
        for(j=0 ; j<=i ; j++)
        {
            // 3번째 자릿수를 만들 경우
            // temp = arr1[2]*arr2[0] + arr1[1]*arr2[1] + arr1[0]*arr2[2]
            if( i-j < len1 && j < len2)
                temp += (arr1[i-j] - '0') * (arr2[j] - '0') ;
            if( j == 0 )
            { // 이전 자리에서의 carry 더함
                temp += carry;
                carry = 0;
            }
        }




        carry += temp / 10;
        arr3[i] = (temp - carry*10) + '0';
        temp = 0;
     }
 }





 void main()
 {
     char mul_1[MAX];
     char mul_2[MAX];
     char* mul_3;




     printf("mul_1: ");
     scanf("%s", mul_1);
     printf("mul_2: ");
     scanf("%s", mul_2);




     mul_3 = (char*)calloc(strlen(mul_1)+strlen(mul_2), sizeof(char)); //calloc 함수를 통해서 메모리 할당




     rev(mul_1); //배열에 넣은 값 뒤집음
     rev(mul_2); //배열에 넣은 값 뒤집음
     process(mul_1, mul_2, mul_3);
     rev(mul_3); // 결과값 뒤집음으로 정상 출력 완료




     printf("output : %s\n", mul_3);
 }

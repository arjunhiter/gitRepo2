#include<stdio.h> 

int main602(void)
{ 

     char s[80]; 

	/*ͬ��������fgets �Ľ����Ϊfputs���� */ 

     fputs(fgets(s,80,stdin),stdout); 

} 

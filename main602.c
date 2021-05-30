#include<stdio.h> 

int main602(void)
{ 

     char s[80]; 

	/*同上例，把fgets 的结果作为fputs的输 */ 

     fputs(fgets(s,80,stdin),stdout); 

} 

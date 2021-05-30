
#include <stdio.h>
#include <stdlib.h>

int main601(void);
int main602(void);
int main603(void);
int main801(void);
int main1001(void);


int main(int argc,char *argv[])
{
	int i = 1000;

	while (i)
	{
		printf("%s", "Input the command:");
		scanf("%d", &i);

		switch (i)
		{
		  case 1:
	
			break;
		  case 2:	  	
		    	break;
		  case 601:
		  	main601();
		    	break;
		  case 602:
		  	main602();
		    	break;
		  case 603:
		  	main603();
		    	break;	
		  case 801:
		  	main801();
		    	break;		
		  case 1001:
		  	main1001();
		    	break;	
		  default:
		    break;

		}
	}

	exit(0);
}
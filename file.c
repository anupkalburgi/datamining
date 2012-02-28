#include <stdio.h>
main()
{
	FILE *fp;
	char s[100];
	fp = fopen("data.txt","r");
	printf("File Openied");
	if(fp = NULL)
	{
		puts("cannot open the file");
		return(0);
	}
	
	while( fgets (s,999,fp) != NULL )
	{
		printf("%s",s);
	}

	fclose(fp);
}

/*Cameron Brown, my-cat.c*/
/*Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*main function*/
int main(int argc, char *argv[])
{
	
	/*This loop will iterate through the arguments, handling each one.
	 Each argument should be a file*/
	int i;
	for(i=1;argv[i];++i)
	{
		/*Open file*/
		FILE *fp = fopen(argv[i], "r");
		/*Check that the file was valid and opened.
		If not, the program prints out an error message and exits*/
		if(fp == NULL)
		{
			printf("my-cat: cannot open file\n");
			exit(1);
		}

		/*Time to print the file!*/
		char buffer[BUFSIZ];
		
		/*While a character exists, print the character.
		fgets() outputs a null character at the end of a file,
		so this loop will terminate.*/
		while(fgets(buffer,sizeof(buffer),fp))
		{
			printf("%s",buffer);
		}
		/*Close file*/
		fclose(fp);
	}
return 0;
}

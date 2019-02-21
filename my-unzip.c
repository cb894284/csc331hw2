/*Cameron Brown, my-cat.c*/
/*Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*a simple binary to decimal converter*/
int binaryToDecimal(int binary)
{
	int decimal = 0;
	int i = 0;
	int remainder;
	while(binary!=0)
	{
		remainder = binary%10;
		binary /= 10;
		decimal += remainder*(2^i);
		++i;
	}
	return decimal;
}

/*main function*/
int main(int argc, char *argv[])
{
	/*This loop will iterate through the arguments, handling each one.
	 Each argument should be a file*/
	int i;
	for(i=1;i<argc;i++)
	{
		/*Open file*/
		FILE *fp = fopen(argv[i], "r");
		/*Check that the file was valid and opened.
		If not, the program prints out an error message and exits*/
		if(fp == NULL)
		{
			printf("my-unzip: file1.z [...] \n");
			exit(1);
		}

		/*Time to unzip!*/
		char numbers[4];
		char *numbersptr;
		numbersptr=&numbers[0];

		char symbol;
		char *symbolptr;
		symbolptr=&symbol;

		do
		{
			fread(numbersptr,sizeof(char),4,fp);
			fread(symbolptr,sizeof(char),1,fp);
			int t;
			int count = binaryToDecimal(atoi(numbersptr));
			for(t=0;t<count;t++)
			{
				printf("%c",symbol);
			}
		}
		while(!feof(fp));
		/*Close file*/
		fclose(fp);
	}
printf("\n");
return 0;
}

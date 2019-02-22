/*Cameron Brown, my-unzip.c*/
/*Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*a simple binary to decimal converter*/
int binaryToDecimal(int binary)
{
	int decimal = 0;
	int i = 1;
	int remainder;
	while(binary!=0)
	{
		remainder = binary%10;
		binary /= 10;
		decimal += remainder*(i);
		i*=2;
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
		/*Check that the file and format was valid and opened.
		If not, the program prints out an error message and exits*/
		if(fp == NULL)
		{
			printf("my-unzip: file1.z [...] \n");
			exit(1);
		}

		/*Time to unzip! read binary number (length of 4) first, and then the symbol (1 character)*/
		char numbers[4];
		char *numbersptr;
		numbersptr=&numbers[0];

		char symbol;
		char *symbolptr;
		symbolptr=&symbol;
		
		/*prime the loop, with will iterate through the file*/
		fread(numbersptr,sizeof(char),4,fp);
		fread(symbolptr,sizeof(char),1,fp);

		do
		{
			int t;
			/*atoi() is a funcion in the standard libaries which gets an int from a string*/
			int count = binaryToDecimal(atoi(numbersptr));
			/*We use our number (converted to decimal)...*/
			for(t=0;t<count;t++)
			{
				/*to loop and output that many symbols*/
				printf("%c",symbol);
			}
			/*and we do it again until the file is completely read!*/
			fread(numbersptr,sizeof(char),4,fp);
			fread(symbolptr,sizeof(char),1,fp);
		}
		while(!feof(fp));
		/*Close file*/
		fclose(fp);
	}
printf("\n");
return 0;
}

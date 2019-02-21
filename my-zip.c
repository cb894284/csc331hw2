/*Cameron Brown, my-cat.c*/
/*Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*a simple decimal to binary converter*/
int decimalToBinary(int decimal)
{
	int remainder;
	int binary = 0;
	int i = 1;
	while(decimal != 0)
	{
		remainder = decimal % 2;
		decimal = decimal / 2;
		binary = binary + remainder*i;
		i=i*10;
	}
	return binary;
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
			printf("my-zip: file1 [file2 ...]\n");
			exit(1);
		}

		/*Time to zip! Declare and populate variables with the first two characters*/
		char buffer;
		char bufferprevious;
		
		bufferprevious=fgetc(fp);
		buffer=fgetc(fp);

		int count = 1;
		while(!feof(fp))
		{
			/*If we have a match of the last two characters, increment the character count*/
			if(buffer == bufferprevious)
			{			
				count++;
			}
			/*Otherwise, we have reached new characters. Write the last entry to our zip file*/
			else
			{
				/*Convert our count to binary!*/
				int b=decimalToBinary(count);
				/*Add leading zeros, if the binary value's length is less than 4*/
				char binaryarray[16];
				snprintf(binaryarray,16,"%04d",b);
				/*I did not find success with fwrite(). printf() achieves the desired result into stdout (into the .z file)*/
				printf("%s%c",binaryarray,(char)(bufferprevious));
				/*Reset the count. Time for the next set of characters*/
				count=1;
			}
			/*Move char values up 1*/
			bufferprevious=buffer;
			buffer=fgetc(fp);
			
		}
		/*Close file*/
		fclose(fp);
	}
return 0;
}

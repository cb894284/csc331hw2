/*Cameron Brown, my-grep.c*/
/*Libraries*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

/*a simple function to compare arrays*/
int compare(char a[], char b[], size_t n)
{
	int i;
	for(i=0;i<n;i++)
	{
		if(a[i]!=b[i]) return 0;
	}
	return 1;
}

/*get the length of an array*/
size_t getlength(char *a[])
{
	return sizeof(a)/sizeof(a[0]);
}

/*main function*/
int main(int argc, char *argv[])
{
	/*If there are not enough arguments, either a search or a file was not given.
	The program exits.*/
	if(argc < 1)
	{
		printf("my-grep: searchterm [file ...]");
		exit(1);
	}	
	/*Initialize the search term*/
	/*char searchterm[sizeof(argv[1])] = argv[1];*/

	/*This loop will iterate through the files, searching each one.
	 These arguments should be files*/
	int i;
	for(i=2;argv[i];++i)
	{
		/*Open file*/
		FILE *fp = fopen(argv[i], "r");
		/*Check that the file was valid and opened.
		If not, the program prints out an error message and exits*/
		if(fp == NULL)
		{
			printf("my-grep: cannot open file\n");
			exit(1);
		}

		/*Time to search the file!*/
		char buffer[BUFSIZ];
		
		/*While a line in a file exists, store that line in buffer*/
		while(getline(buffer,sizeof(buffer),fp))
		{

		/*These variables will be used in a loop to iterate through the line. Each time it loops, the program will create a new term for buffer and try to match it to the search term. If the match is correct, the line is printed*/
		int t;
		size_t searchtermlength = getlength(argv[1]);
		size_t bufferlength = getlength(buffer);
		/*We don't need to keep searching the line if the length of our buffer is less than the search term. So...*/
		size_t limit = bufferlength - searchtermlength;

			for(t=0;t<limit;t++)
			{
				/*Create the field in question. I called it "attempt"*/
				char attempt[(int)searchtermlength];
				int x;
				for(x=0;x<searchtermlength;x++)
				{
					attempt[x] = buffer[t+x];
				}
				/*Now we have an attempt to try to compare to the search. Print this line if the comparison is successful*/
				if(compare(argv[1],attempt,searchtermlength)) printf(buffer);
			}
		}
		/*Close file*/
		fclose(fp);
	}
return 0;
}

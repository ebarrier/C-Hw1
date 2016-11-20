#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

int getStringFromFile(char* fileName, char** out)
{
	FILE* file;
	errno_t returned = fopen_s(&file, fileName, "r");

	if (returned != 0)
	{
		return -1;
	}

	//We run from the beginning of the file until the end
	fseek(file, 0, SEEK_END);

	//We get the position we have reached (how many characters)
	long numChar = ftell(file);

	//Allocate memory array for file content AND the null terminator
	//The allocation must be done in bytes. That's why we multiply the sizeof a char (in bytes) by the num of char we need.
	*out = malloc((numChar + 1) * sizeof(char));

	//we check if malloc failed (null or 0) or not
	if (*out == NULL)
	{
		return -1;
	}

	//We go back to the beginning of the file
	rewind(file);

	//We put the content of 'file' inside the buffer
	fgets(*out, numChar + 1, file);
	
	//We output the buffer to console
	//printf("%s", *out);
	//printf("\n");

	//We close the file
	fclose(file);

	return 1;
}

char** separateString(char** buffer)
{
	double** arrayNum = NULL;
	char sep[] = ";";
	char* token1 = NULL;
	char* next_token1;
	int arraySize = 0, i;

	token1 = strtok_s(*buffer, sep, &next_token1);

	while ((token1 != NULL))
	{
		if (arrayNum == NULL)
		{
			arrayNum = malloc(sizeof(double*));
			if (arrayNum == NULL)
			{
				exit(-1); //memory allocation failed
			}
		}
		
		arrayNum = realloc(arrayNum, sizeof(double*) * ++arraySize);

		arrayNum[arraySize - 1] = token1; //we add the token into the array
		printf(token1);
		printf("\n");

		token1 = strtok_s(NULL, sep, &next_token1); //we get the next token
	}
	
	//realloc one extra element for the array's last NULL
	//arrayNum = realloc(arrayNum, sizeof(double*) * (arraySize + 1));
	//arrayNum[arraySize] = "\0";
	
	// print the result
	for (i = 0; i < arraySize; ++i)
		printf("res[%d] = %s\n", i, arrayNum[i]);
	printf("\n");

	return arrayNum;
}

int main()
{	
	//************ Copy file's content into a buffer ************
	
	char* fileName = "input.txt";
	char* buffer = NULL;
	getStringFromFile(fileName, &buffer);
	char** arrayNum = separateString(&buffer);
	

	//************ Sort array in ascending order based on index of index:value pairs ************
	/*char* arrayNum2 = malloc(sizeof(char) * arraySize);
	if (arrayNum2 == NULL)
	{
		exit(-1); //memory allocation failed
	}

	for (int i = 0; i < (arraySize +1); i++)
	{
		if ((arrayNum[i][0] - 0) == i)
		{
			arrayNum2[i] = arrayNum[i][3];
		}
	}
	
	for (i = 0; i < (arraySize +1); ++i)
		printf("res[%d] = %c\n", i, arrayNum2[i]);
	printf("\n");*/
	

	//We deallocate buffer's memory
	free(buffer);

	// free the memory allocated
	free(arrayNum);
	
}


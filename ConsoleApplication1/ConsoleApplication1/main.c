#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

struct inputElement { 
	//Struct what we use to store char* in array and int to store its length (nbr of array elements)
	int length;
	char** data;
};

int getStringFromFile(char* fileName, char** out)
{
	FILE* file;
	errno_t returned = fopen_s(&file, fileName, "r");

	if (returned != 0)
	{
		return -1;
	}

	//Run from the beginning of the file until the end
	fseek(file, 0, SEEK_END);

	//Get the position we have reached (how many characters)
	long numChar = ftell(file);

	//Allocate memory array for file content AND the null terminator
	//Allocation must be done in bytes. That's why we multiply the sizeof a char (in bytes) by the num of char we need.
	*out = malloc((numChar + 1) * sizeof(char));

	//Check if malloc failed (null or 0) or not
	if (*out == NULL)
	{
		return -1;
	}

	//Go back to the beginning of the file
	rewind(file);

	//Put the content of 'file' inside the buffer
	fgets(*out, numChar + 1, file);

	//Output the buffer to console
	//printf("%s", *out);
	//printf("\n");

	//Close the file
	fclose(file);

	return 1;
}

int* separateIndexValue(struct inputElement* inputElement) //we want to return an array of int
{
	//Separate the index,value pairs by the comma between them
	//and store the value in an array of int by its paired index.

	int count = inputElement->length; //Nbr of elements in the parameter array
	char** arrayOfKeyValue = inputElement->data; //Parameter's array to deal with

	int* arrayDecimal = malloc(count * sizeof(int)); //Allocate memory to store our returning var (array of int) 
	if (arrayDecimal == NULL) //Check if allocation succeeded
	{
		exit(-1);
	}
	char sepComma[] = ",";
	char* token2 = NULL;
	char* next_token2;

	for (int j = 0; j < count; j++)
	{
		token2 = strtok_s(arrayOfKeyValue[j], sepComma, &next_token2); //Separate the string by the comma.
		unsigned int index;
		sscanf_s(token2, "%i", &index); //Store index of index,value pair to unsigned int var

		int value;
		sscanf_s(next_token2, "%i", &value); //Store value of index,value pair to int var

		arrayDecimal[index] = value; //Assign index and value to the result array

		//printf("res[%i] = %i\n", index, arrayDecimal[index]);
		//printf("\n");
	}

	return arrayDecimal;
}

char** separateStringBySemicolon(char** buffer, int* numberElements) //Return an array of pointers to char
{
	//Separate the buffer string by the semi-colon to put pairs of "index,value" in array
	const char** arrayNum = NULL; //advised on SOF
	char sep[] = ";";
	char* token1;
	char* next_token1;
	int arraySize = 0; //Store the number of elements in the returned array

	token1 = strtok_s(*buffer, sep, &next_token1);

	while ((token1 != NULL))
	{
		if (arrayNum == NULL)
		{
			arrayNum = malloc(sizeof(char*));
			if (arrayNum == NULL)
			{
				exit(-1); //memory allocation failed
			}
		}

		arrayNum = realloc(arrayNum, sizeof(char*) * ++arraySize); //Allocate memory for array of pointers to char

		arrayNum[arraySize - 1] = token1; //Add the token (pointer) into the array
		//printf(token1);
		//printf("\n");

		token1 = strtok_s(NULL, sep, &next_token1); //Get the next token
	}

	*numberElements = arraySize; //Store the array length to a parameter

	//for (int i = 0; i < (arraySize); ++i)
	//{
	//	printf("res[%d] = %s\n", i, arrayNum[i]);
	//}
	//printf("\n");

	return arrayNum;
}

int main()
{
	char* fileName = "input.txt";
	char* buffer = NULL;
	struct inputElement Element1;

	getStringFromFile(fileName, &buffer);
	Element1.data = separateStringBySemicolon(&buffer, &Element1.length);
	int* arrayValue = separateIndexValue(&Element1);

	if (Element1.length == 1)
	{
		printf_s("0");
	}

	for (int i = 1; i < Element1.length; i++)
	{
		printf_s("%i", arrayValue[i] - arrayValue[i - 1]);
		if (i != (Element1.length - 1))
		{
			printf_s(",");
		}
	}
	printf("\n");

	// free the memory allocated
	free(buffer);
	free(Element1.data);
	free(arrayValue);

}
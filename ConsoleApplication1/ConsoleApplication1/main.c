#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <search.h>

struct inputElement {
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

double* separateKeyValue(struct inputElement* inputElement)
{
	int count = inputElement->length;
	char** arrayOfKeyValue = inputElement->data;

	double* arrayDecimal = malloc(count * sizeof(double));
	if (arrayDecimal == NULL)
	{
		exit(-1);
	}
	char sepComma[] = ",";
	char* token2 = NULL;
	char* next_token2;

	for (int j = 0; j < count; j++)
	{
		token2 = strtok_s(arrayOfKeyValue[j], sepComma, &next_token2);
		unsigned int index;
		sscanf_s(token2, "%d", &index);

		double value;
		sscanf_s(next_token2, "%d", &value);

		arrayDecimal[index] = value;

		printf("res[%o] = %o\n", index, arrayDecimal[index]);
		printf("\n");
	}

	return arrayDecimal;
}

char** separateStringBySemicolon(char** buffer, int* numberElements)
{
	char** arrayNum = NULL; //add const
	char sep[] = ";";
	char* token1;
	char* next_token1;
	int arraySize = 0;

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

		arrayNum = realloc(arrayNum, sizeof(char*) * ++arraySize);

		arrayNum[arraySize - 1] = token1; //we add the token into the array
		printf(token1);
		printf("\n");

		token1 = strtok_s(NULL, sep, &next_token1); //we get the next token
	}

	*numberElements = arraySize;

	for (int i = 0; i < (arraySize); ++i)
		printf("res[%d] = %s\n", i, arrayNum[i]);
	printf("\n");

	return arrayNum;
}

int main()
{
	char* fileName = "input.txt";
	char* buffer = NULL;
	int numberOfElementsInArray;
	struct inputElement Element1;

	getStringFromFile(fileName, &buffer);
	Element1.data = separateStringBySemicolon(&buffer, &Element1.length);

	//Element1.data = arrayKeyValue;
	//Element1.length = numberOfElementsInArray;

	double* arrayValue = separateKeyValue(&Element1);

	printf("res[0] = %o\n", &arrayValue[0]);
	printf("res[1] = %o\n", &arrayValue[1]);
	printf("res[2] = %o\n", &arrayValue[2]);
	printf("res[3] = %o\n", &arrayValue[3]);
	printf("\n");
	printf("\n");

	double test = (double) arrayValue[0];
	printf("%d", test);
	printf("\n");

	for (int i = 1; i < Element1.length; i++)
	{
		double first =  (double) arrayValue[i];
		printf("First: %d", first);
		printf("\n");
		double second = (double) arrayValue[i-1];
		printf("Second: %d", second);
		printf("\n");
		double result = (double) (first - second);
		printf_s("Result: %d", result);
		printf("\n");
		if (i != (Element1.length - 1))
		{
			printf_s(",");
		}
	}



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

	// free the memory allocated
	free(buffer);
	//free(arrayKeyValue);
	free(arrayValue);

}
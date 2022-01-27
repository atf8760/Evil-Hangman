#include "my_string.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

struct my_string
{
	char* data;
	int capacity;
	int size;
};
typedef struct my_string My_string;


MY_STRING my_string_init_default(void)
{
	My_string* pmy_string = (My_string*)malloc(sizeof(My_string));
	if (pmy_string != NULL)
	{
		pmy_string->size = 0;
		pmy_string->capacity = 7;
		pmy_string->data = (char*)malloc(sizeof(char) * pmy_string->capacity);
		if (pmy_string->data == NULL)
		{
			free(pmy_string);
			return NULL;
		}
	}
	return (MY_STRING)pmy_string;

}

MY_STRING my_string_init_c_string(const char* c_string)
{
	My_string* pmy_string = (My_string*)malloc(sizeof(My_string));
	if (pmy_string != NULL)
	{
		pmy_string->size = strlen(c_string);
		pmy_string->capacity = strlen(c_string) + 1;
		pmy_string->data = (char*)malloc(sizeof(char) * pmy_string->capacity);
		if (pmy_string == NULL)
		{
			free(pmy_string);
			return NULL;
		}

		for (int i = 0; i < pmy_string->capacity; i++)
		{
			pmy_string->data[i] = c_string[i];
		}
	}
	return (MY_STRING)pmy_string;

}


int my_string_get_capacity(MY_STRING hMy_string)
{
	return ((My_string*)hMy_string)->capacity;
}

int my_string_get_size(MY_STRING hMy_string)
{
	return ((My_string*)hMy_string)->size;
}

int my_string_compare(MY_STRING hLeft_string, MY_STRING hRight_string)
{
	My_string* pLeft_string = (My_string*)hLeft_string;
	My_string* pRight_string = (My_string*)hRight_string;
	int size;
	if (pLeft_string->size > pRight_string->size)
	{
		size = pRight_string->size;
	}
	else 
	{
		size = pLeft_string->size;
	}

	for (int i = 0; i < size; i++)
	{
		
		//Compare each letter and see if one is greater than the other
		if ((int)(pLeft_string->data[i]) > (int)(pLeft_string->data[i]))
		{
			return 1;
		}
		else if ((int)(pLeft_string->data[i]) < (int)(pLeft_string->data[i]))
		{
			return 1;
		}
		
		else
		{
			if (i >= size - 1)
			{
				if (pLeft_string->size > pRight_string->size)
				{
					return 1;
				}
				if (pLeft_string->size < pRight_string->size)
				{
					return -1;
				}
			}
			//continue;
		}

		
	}
	return 0;
}

Status my_string_extraction(MY_STRING hMy_string, FILE* fp)
{
	My_string* pMy_string = (My_string*)hMy_string;
	pMy_string->size = 0;
	char letter;
	int noc;


	while ((noc = fscanf(fp, "%c", &letter)))
	{
		if (feof(fp))
		{
			return FAILURE;
		}

		if (noc == EOF || letter == '.')
		{
			if (letter == '.')
			
			{	
				ungetc(letter, fp);
			}
			break;
		}

		if (letter == ' ' || letter == '\n')
		{
			ungetc(letter,fp);
			break;
		}

		if (pMy_string->size >= pMy_string->capacity)//Old box too small
		{
			char* temp;
			temp = (char*)malloc(sizeof(char) * pMy_string->capacity * 2); // Make a bigger box

			if (temp == NULL)
			{
				return FAILURE;
			}
			

			for (int i = 0; i < pMy_string->size; i++) // Copy old stuff into new box
			{
				temp[i] = pMy_string->data[i];
			}
			free(pMy_string->data);
			pMy_string->data = temp; // old box becomes new box
			pMy_string->capacity *= 2;
			
		}
		
		pMy_string->data[pMy_string->size++] = letter;
		
	}
	return SUCCESS;
}

Status my_string_insertion(MY_STRING hMy_string, FILE* fp)
{
	My_string* pMy_string = (My_string*)hMy_string;
	if (fp == NULL)
	{
		return FAILURE;
	}
	for (int i = 0; i < pMy_string->size; i++)
	{
		fprintf(fp, "%c", pMy_string->data[i]);
	}
	return SUCCESS;
}

void my_string_destroy(MY_STRING* phMy_string)
{
	My_string* pmy_string = (My_string*)*phMy_string;
	free(pmy_string->data);
	pmy_string->data = NULL;
	free(pmy_string);
	pmy_string = NULL;
	printf("Successfully destroyed object.\n");

}

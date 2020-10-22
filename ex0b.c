/*
 * ex0b.c
 *
 *  Created on: Oct 22, 2020
 *      Author: sharonlevi
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>

/************CONST*****************/
#define END_OF_ARR -1
#define LEN_OF_SENTENCE 1000
#define MAX_FILE_NAME_LEN  50
/************STRUCTS***************/
struct Sentences
{
	char** _data;
	int _num_of_sentences;
};
/**********PROTOTYPES**************/
FILE *open_files(char *);
int terminate(FILE *);
void read_data(struct Sentences*,FILE*);
int get_sentences_number(FILE *);
void terminate_all();
struct Sentences build_new_struct(struct Sentences*);
int count_strs_in_arr(const char* , int**, int*,int*);
int count_strs_in_struct(struct Sentences*,int**,int*);
/************MAIN*****************/
int main()
{
	FILE *input_file;

	    input_file = open_files("r");

	struct Sentences user_struct;
	read_data(&user_struct,input_file);
	//new_struct = build_new_struct(user_struct);
    //print_struct(new_struct);
//------------delete pointers-------------------------------
	/*user_struct._data[user_struct._num_of_sentences] = NULL;
	int i;
	for (i = 0; i < user_struct._num_of_sentences; i++)
		free(user_struct._data[i]);

	free(user_struct._data);

	for (i = 0; i < new_struct._num_of_sentences; i++)
		free(new_struct._data[i]);

	free(new_struct._data);*/
free(input_file);
	return (EXIT_SUCCESS);
}
/***********FUNCTIONS************/
FILE *open_files(char *opening_mode)
{
    char *file_name = NULL;
    unsigned long file_len;
    size_t filename_len = MAX_FILE_NAME_LEN;  // as size_t to use in 'getline'
    getline(&file_name, &filename_len, stdin);
    file_len = strlen(file_name);
    file_name[file_len - 1] = '\0';  // to remove '\n' from the name we got into 'file_name'
    FILE *file_to_open = fopen(file_name, opening_mode);
    terminate(file_to_open);
    free(file_name);  // to free memory of ptr
    return file_to_open;
}
//------------------------------------------------------------------
int terminate(FILE *p2file)
{
    if (p2file == NULL)
    {
        printf("can't open file\n");
        exit(1);
    }
    if(p2file!=NULL)
    {
    printf("open file success\n");
    }
    return 0;
}
//------------------------------------------------------------------
void read_data(struct Sentences* user_struct,FILE* input)
{
	int endl;
	int i;
	user_struct->_num_of_sentences=get_sentences_number(input);
	endl=fgetc(input);

	user_struct->_data = (char*) malloc (sizeof(user_struct->_num_of_sentences));

	if(user_struct->_data==NULL)
	{
		terminate_all();
	}

	for(i=0;i<user_struct->_num_of_sentences ; i++)
	{
		user_struct->_data[i] = malloc (sizeof(LEN_OF_SENTENCE));
		if(user_struct->_data[i]==NULL)
		{
			terminate_all();
		}
		fscanf(input,"%[^\n]",user_struct->_data[i]);
		endl=fgetc(input);
		printf("%s\n",user_struct->_data[i]);
	}
}
//------------------------------------------------------------------
int get_sentences_number(FILE *input_file)
{
    int sentences_amount;
    fscanf(input_file, "%d", &sentences_amount);
    return sentences_amount;
}
//------------------------------------------------------------------
void terminate_all()
{
	printf("cannot allocate memory\n");
	exit(1);
}
//------------------------------------------------------------------
struct Sentences build_new_struct(struct Sentences* user_struct)
{
	struct Sentences new_struct;
	int num_of_strs, *strs_len;
    int num_strs = 1;
    strs_len=malloc (1);
    if(strs_len==NULL)
    {
    	terminate_all();
    }
    strs_len[0] = END_OF_ARR;
    //find how many words there is in the sentences:
    num_of_strs = count_strs_in_struct(user_struct, strs_len, num_strs);
    //num of the words = num of rows/lines in the new struct:
    new_struct._num_of_sentences=num_of_strs;
    new_struct._data=malloc(sizeof(new_struct._num_of_sentences));
    if(new_struct._data==NULL)
    {
    	terminate_all();
    }
    copy_strs_new_struct(user_struct, new_struct, strs_len);
    free(strs_len);
	return new_struct;
}
//------------------------------------------------------------------
int count_strs_in_struct(struct Sentences* user_struct, int** strs_len,
		int* num_strs)
{

}
//------------------------------------------------------------------
int count_strs_in_arr(const char* arr, int** strs_len, int* num_strs,
		int* strs_counter)
{

}
//------------------------------------------------------------------




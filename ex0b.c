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
    if (p2file == NULL) {
        printf("can't open file\n");
        exit(1);
    }
    return 0;
}
//------------------------------------------------------------------
void read_data(struct Sentences* user_struct,FILE* input)
{
	user_struct->_num_of_sentences=get_sentences_number(input);

	return;
}
//------------------------------------------------------------------
int get_sentences_number(FILE *input_file)
{
    int sentences_amount;
    fscanf(input_file, "%d", &sentences_amount);
    return sentences_amount;
}






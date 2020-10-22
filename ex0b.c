
/*
 * ex0b.c
 *
 *  Created on: Oct 22, 2020
 *      Author: sharonlevi
 */
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

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
void terminate_all(void);
struct Sentences build_new_struct(struct Sentences*);
int count_strs_in_arr(const char* , int**, int*);
int count_strs_in_struct(struct Sentences*,int**,int*);
void copy_strs_new_struct(struct Sentences *in_struct ,struct Sentences *out_struct, int *strs_len);
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
// this func opens the file, sends back 'pointer' to beggining of file.
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
void read_data(struct Sentences* user_struct, FILE* input)
{
    int endl;
    int i;      // for loop index
    user_struct->_num_of_sentences = get_sentences_number(input);
    endl=fgetc(input);

    user_struct->_data = (char**) malloc (sizeof(user_struct->_num_of_sentences));

    if(user_struct->_data == NULL)
    {
        terminate_all();
    }

    for(i = 0 ; i < user_struct->_num_of_sentences ; i++)
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
    int num_of_strs, *strs_len_array;
    int num_strs = 0;
    strs_len_array=malloc (1);
    if(strs_len_array==NULL)
    {
        terminate_all();
    }
    strs_len_array[0] = END_OF_ARR;
    //find how many words there is in the sentences:
    num_of_strs = count_strs_in_struct(user_struct, &strs_len_array, &num_strs);
    //num of the words = num of rows/lines in the new struct:
    new_struct._num_of_sentences=num_of_strs;
    new_struct._data=malloc(sizeof(new_struct._num_of_sentences));
    if(new_struct._data==NULL)
    {
        terminate_all();
    }
    copy_strs_new_struct(user_struct, &new_struct, strs_len_array);
    free(strs_len_array);
    return new_struct;
}
//------------------------------------------------------------------
void copy_strs_new_struct(struct Sentences *in_struct ,struct Sentences *out_struct, int *strs_len_array) {
    
}
//------------------------------------------------------------------
// this func calls 'count_strs_in_arr'
// this func creats array, with amount of strings in the struct as length
// every cell containes the lenghof the string inside of it.
int count_strs_in_struct(struct Sentences* user_struct, int** strs_len_array,
        int* num_strs)
{
    int strs_counter = 0, row;
    for (row = 0; row < user_struct->_num_of_sentences; row++){
        // this adds the amount of strings that return from func.
        // to use in innitializing a new struct later
        strs_counter += count_strs_in_arr(user_struct->_data[row], strs_len_array, num_strs);
    }
    return strs_counter;
}
//------------------------------------------------------------------
// this function counts how many strings (words) are inside the given row.

int count_strs_in_arr(const char* arr, int** strs_len_array, int* num_strs)
{
    int strs_counter = 0;           // return value- how namy strings (words) are in this given array.
    int i;                          // for loop index
    int str_len_counter = 0;        // lenght of a word in array.
    for (i = 0; arr[i] != '\0'; i++) {
        if (!isspace(arr[i]))
            str_len_counter++;
        if (isspace(arr[i]) || arr[i + 1] == '\0') {
            if (strs_counter == *(num_strs - 1)) {
                num_strs++;                             // adds 1 for new allocation
                strs_len_array = realloc(strs_len_array, sizeof(num_strs));
            }
            strs_len_array[*num_strs] = &str_len_counter;           // array in place of (num_str)
            str_len_counter = 0;                                    // zeros counter to next string
            strs_counter++;                                         // ++ for amount of strings in this array
        }
    }
    // will return how many strings are in this array.
    return strs_counter;

}
//------------------------------------------------------------------

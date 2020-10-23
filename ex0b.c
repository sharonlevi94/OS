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
FILE *open_file(int argc, char **argv);
void read_data(struct Sentences*,FILE*);
int get_sentences_number(FILE *);
void terminate_all(void);
struct Sentences build_new_struct(struct Sentences*);
int count_strs_in_arr(const char* , int**, int*);
int count_strs_in_struct(struct Sentences*,int**,int*);
void copy_strs_new_struct(struct Sentences * ,struct Sentences *, int *s, int *);
/************MAIN*****************/
int main(int argc, char **argv)
{
    FILE *input_file;
    input_file = open_file(argc, argv);
    struct Sentences input_sentences, output_sentences;
    read_data(&input_sentences,input_file);
    output_sentences = build_new_struct(&input_sentences);
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
FILE *open_file(int argc, char **argv){
    FILE *input_file;
    // to check if an argument was passed, if not- will exit.
    if(argc < 2){
        printf("No files passed in argument vector\n");
        exit(0);
    }
    input_file = fopen(argv[1], "r");
    return input_file;
}

//------------------------------------------------------------------
void read_data(struct Sentences* input_sentences, FILE* input)
{
    int endl;
    int i;      // for loop index
    input_sentences->_num_of_sentences = get_sentences_number(input);
    endl=fgetc(input);

    input_sentences->_data = (char**) malloc (sizeof(input_sentences->_num_of_sentences));

    if(input_sentences->_data == NULL)
    {
        terminate_all();
    }

    for(i = 0 ; i < input_sentences->_num_of_sentences ; i++)
    {
        input_sentences->_data[i] = malloc (sizeof(LEN_OF_SENTENCE));
        if(input_sentences->_data[i]==NULL)
        {
            terminate_all();
        }
        // reads a line from the input file, adds '\n' in the end.
        fscanf(input,"%[^\n]",input_sentences->_data[i]);
        endl=fgetc(input);
        printf("%s\n",input_sentences->_data[i]);
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
struct Sentences build_new_struct(struct Sentences* input_sentences)
{
    struct Sentences new_struct;
    int num_of_strs, *strs_amount_array;
    int num_strs = 0;
    strs_amount_array = malloc (sizeof(int));
    if(strs_amount_array == NULL)
    {
        terminate_all();
    }
//    strs_amount_array[0] = END_OF_ARR;
    //find how many words there is in the sentences:
    num_of_strs = count_strs_in_struct(input_sentences, &strs_amount_array, &num_strs);
    //num of the words = num of rows/lines in the new struct:
    new_struct._num_of_sentences = num_of_strs;
    new_struct._data = malloc(sizeof(new_struct._num_of_sentences));
    if(new_struct._data==NULL)
    {
        terminate_all();
    }
    copy_strs_new_struct(input_sentences, &new_struct, strs_amount_array, &num_of_strs);
    free(strs_amount_array);
    
    return new_struct;
}
//------------------------------------------------------------------
void copy_strs_new_struct(struct Sentences *in_struct ,struct Sentences *out_struct, int *strs_amount_array, int *num_of_strs) {
    int i = 0;          // out struct data index
//    int j = 0;          // string copy index
    int k = 0;          //in struct index
    char *moving_string = NULL;
    out_struct->_data = malloc((char)num_of_strs);  // allocating memory for the pointers array
    while (in_struct->_data != NULL && i < *num_of_strs) {
        out_struct->_data[i] = malloc((char)(strs_amount_array[i]));   // allocating memory for a word
        moving_string = malloc((char)(strs_amount_array[i]));          // allocating memory for 'temp' string- holds a value of one word.
        //moving_string = gets(in_struct->_data[k]);
        strcpy(out_struct->_data[i], in_struct->_data[k]);
        if (in_struct->_data[k] == NULL) {                        // move to next line in 'in_struct'
            k++;
        }
    }
    
}
//------------------------------------------------------------------
// this func calls 'count_strs_in_arr'
// this func creats array, with amount of strings in the struct as length
// every cell containes the lenghof the string inside of it.
int count_strs_in_struct(struct Sentences* input_sentences, int** strs_amount_array,
        int* num_strs)
{
    int strs_counter = 0, row;
    for (row = 0; row < input_sentences->_num_of_sentences; row++){
        // this adds the amount of strings that return from func.
        // to use in innitializing a new struct later
        strs_counter += count_strs_in_arr(input_sentences->_data[row], strs_amount_array, num_strs);
    }
    return strs_counter;
}
//------------------------------------------------------------------
// this function counts how many strings (words) are inside the given row.

int count_strs_in_arr(const char *arr, int **strs_amount_array, int *num_strs)
{
    int strs_counter = 0;           // return value- how namy strings (words) are in this given array.
    int i;                          // for loop index
    int str_len_counter = 0;        // lenght of a word in array.
    for (i = 0; arr[i] != '\0'; i++) {
        if (!isspace(arr[i]))
            str_len_counter++;
        if (isspace(arr[i]) || arr[i + 1] == '\0') {
            if (strs_counter == *(num_strs)) {
                *num_strs = strs_counter + 1;                             // adds 1 for new allocation
                strs_amount_array[strs_counter] = malloc(sizeof(int));
                strs_amount_array[strs_counter] = &str_len_counter;
            }
            strs_amount_array[*num_strs] = &str_len_counter;           // array in place of (num_str)
            str_len_counter = 0;                                    // zeros counter to next string
            strs_counter++;                                         // ++ for amount of strings in this array
        }
    }
    // will return how many strings are in this array.
    return strs_counter;
}
//------------------------------------------------------------------


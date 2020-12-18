//ex0b

// OS course 2020, first semester.
// assignement by:
// Sharon Levi-  login- sharonlevi
// Bar Ifrah-  login- barif
// October 29th, 2020
// This program gets 1 input file from the argument vector.
// this input file contains a number- that stand for the amount
// of sentences in the file.
// this program takes the sentences from the file, and moves them to
// a struct. after all data is in struct, the program will break the
// sentences into single words, and re-assign them to a new struct variable,
// which will be our output struct.
// after all words has moved to the new struct, we wil lprint the data

// compiled via linux terminal- using the command 'gcc -Wall <filename.c> -o <run_name>
// no input is reqired from user into terminal in this program.
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
#include <ctype.h>

//CONSTS
//------------------------------------------------------------------
#define LEN_OF_SENTENCE 1000
#define MAX_STR_LEN 100
//STRUCTS
//------------------------------------------------------------------
struct Sentences {
    char** _data;
    int _num_of_sentences;
};

//PROTOTYPES
//------------------------------------------------------------------
FILE *open_file(int argc, char **argv);
void read_data(struct Sentences *,FILE *);
int get_sentences_number(FILE *);
void terminate_all(void);
struct Sentences build_new_struct(struct Sentences*);
int count_strs_in_arr(const char * , int *);
int count_strs_in_struct(struct Sentences * ,int *);
size_t get_word_len(char *);
void copy_string (struct Sentences * ,int , char *);
void allocate_mem_for_struct(struct Sentences * , int, size_t);
void copy_strs_new_struct(struct Sentences * ,struct Sentences * , int *);
char *get_string_from_old_struct(char * , char * , int *);
void print_data_in_struct(struct Sentences *);
void check_allocation(int *);
void string_elegible_to_move_into_output(struct Sentences *, int *, size_t , char *);
void free_memory(struct Sentences *);
//MAIN
//------------------------------------------------------------------
int main(int argc, char **argv)
{
    FILE *input_file;
    input_file = open_file(argc, argv);
    struct Sentences input_sentences, output_sentences;
    read_data(&input_sentences,input_file);
    output_sentences = build_new_struct(&input_sentences);
    print_data_in_struct(&output_sentences);
    free_memory(&input_sentences);
    free_memory(&output_sentences);
    fclose(input_file);
    return (EXIT_SUCCESS);
}
//FUNCTIONS
//------------------------------------------------------------------
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
void read_data(struct Sentences *input_sentences, FILE* input)
{
    
    int i;      // for loop index
    input_sentences->_num_of_sentences = get_sentences_number(input);
    fgetc(input);
    // initiallizing a ** array tp hold all data from the argv[] file
    input_sentences->_data = (char**) malloc (sizeof(char*)*(input_sentences->_num_of_sentences));
    if(input_sentences->_data == NULL)
    {
        terminate_all();
    }
    for(i = 0 ; i < input_sentences->_num_of_sentences ; i++)
    {
        input_sentences->_data[i] = (char*)malloc (sizeof(char)*(LEN_OF_SENTENCE));
        // if memory allocation failed
        if(input_sentences->_data[i] == NULL)
        {
            terminate_all();
        }
        // reads a line from the input file, adds '\n' in the end.
        fscanf(input,"%[^\n]",input_sentences->_data[i]);
        fgetc(input);
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
    int num_of_strs;
    int num_strs = 0;
    //find how many words there is in the sentences:
    num_of_strs = count_strs_in_struct(input_sentences, &num_strs);
    //num of the words = num of rows/lines in the new struct:
    new_struct._num_of_sentences = num_of_strs;
    if(new_struct._data==NULL)
    {
        terminate_all();
    }
    copy_strs_new_struct(input_sentences, &new_struct, &num_of_strs);
    return new_struct;
}
//------------------------------------------------------------------
// this function moves all the data to the new struct, one word in a line.
void copy_strs_new_struct(struct Sentences *in_struct ,struct Sentences *out_struct, int *num_of_strs) {
    int out_struct_index = 0;          // out struct data index
    int letter_in_old_array_index = 0;          // string copy index
    int old_struct_line_index = 0;          //in struct index
    size_t word_len_for_struct_allocation = 0;
    char *moving_string = malloc(sizeof(char)*(MAX_STR_LEN));
    out_struct->_data = (char**)malloc(sizeof(char*)*(*num_of_strs));  // allocating memory for the pointers array
    while (in_struct->_data != NULL && out_struct_index < *num_of_strs) {
        // allocating memory for 'temp' string- holds a value of one word.
        moving_string = get_string_from_old_struct(in_struct->_data[old_struct_line_index], moving_string, &letter_in_old_array_index);
        if (strcmp(moving_string,"")) {
            string_elegible_to_move_into_output(out_struct, &out_struct_index,
                                                word_len_for_struct_allocation, moving_string);
        }
        if (in_struct->_data[old_struct_line_index][letter_in_old_array_index] == '\0') {
            // move to next line in 'in_struct'
            old_struct_line_index++;
            letter_in_old_array_index = 0;       // next line to start at 0 index
        }
    }
    free(moving_string);
}
//------------------------------------------------------------------
// this func calls 'count_strs_in_arr'
// this func creats array, with amount of strings in the struct as length
// every cell containes the lenghof the string inside of it.
int count_strs_in_struct(struct Sentences* input_sentences, int* num_strs)
{
    int strs_counter = 0, row;
    for (row = 0; row < input_sentences->_num_of_sentences; row++){
        // this adds the amount of strings that return from func.
        // to use in innitializing a new struct later
        strs_counter += count_strs_in_arr(input_sentences->_data[row], num_strs);
    }
    return strs_counter;
}
//------------------------------------------------------------------
// this function counts how many strings (words) are inside the given row.

int count_strs_in_arr(const char *arr, int *num_strs)
{
    int strs_counter = 0;           // return value- how namy strings (words) are in this given array.
    int i;                          // for loop index
    int str_len_counter = 0;        // lenght of a word in array.
    for (i = 0; arr[i] != '\0'; i++) {
        if (!isspace(arr[i]))
            str_len_counter++;
        if (isspace(arr[i]) || arr[i + 1] == '\0') {
            if (strs_counter == *(num_strs)) {
                *num_strs = strs_counter + 1;    // adds 1 for new allocation
            }
            str_len_counter = 0;                 // zeros counter to next string
            strs_counter++;                       // ++ for amount of strings in this array
        }
    }
    // will return how many strings are in this array.
    return strs_counter;
}
//------------------------------------------------------------------
// this funtion copies an entire string into a single word string in the new (output) struct.
char *get_string_from_old_struct(char *old_struct_line, char *returning_string, int *letter_in_old_array_index) {
    int letter_in_new_word_index = 0;
    while (old_struct_line[*letter_in_old_array_index] != '\0') {
        // while theres still memory allocated for this string-- go in
        if (!isspace(old_struct_line [*letter_in_old_array_index])){
            returning_string[letter_in_new_word_index] = old_struct_line[*letter_in_old_array_index];
            letter_in_new_word_index++;
            *letter_in_old_array_index += 1;  // not writing '++' due to a debuungig problem
        } else{
            *letter_in_old_array_index += 1;  // to moveto next char in the string.
            break;
        }
        // when code gets here, it will end the func. 'break' added for safety reasons.
    }
    returning_string[letter_in_new_word_index] = '\0';  // NULL terminated string
    return returning_string;
}
//------------------------------------------------------------------
// this function moves the data to the new struct line.
void string_elegible_to_move_into_output(struct Sentences *output_struct, int *out_struct_index,
                                         size_t string_len, char *string_to_copy) {
    string_len = get_word_len(string_to_copy);
    allocate_mem_for_struct(output_struct, *out_struct_index,
                            string_len);
    copy_string(output_struct, *out_struct_index, string_to_copy);
    string_to_copy [string_len] = '\0';
    *out_struct_index += 1;
}
//------------------------------------------------------------------
// this function checks the length of a string to allocate memory later
size_t get_word_len(char *word_from_old_struct) {
    size_t word_len;
    word_len = strlen(word_from_old_struct) + 1;
    return word_len;
}
//------------------------------------------------------------------
// this function allocates memory for a new line in the output struct.
void allocate_mem_for_struct(struct Sentences *output_struct, int index, size_t string_len) {
    output_struct->_data[index] = malloc(sizeof(char)*(string_len));
}
//------------------------------------------------------------------
// this function copies the string from given string top output struct
void copy_string (struct Sentences *output_struct, int index, char *string_to_copy){
    strcpy(output_struct->_data[index], string_to_copy);
}
//------------------------------------------------------------------
// this function prints the valuen is the required struct
void print_data_in_struct(struct Sentences *struct_to_print) {
    int i;
    for (i = 0; i < struct_to_print->_num_of_sentences; ++i) {
        printf("%s\n", struct_to_print->_data[i]);
    }
}
//------------------------------------------------------------------
void free_memory(struct Sentences *struct_to_print) {
    int i;
    for (i = 0; i < struct_to_print->_num_of_sentences; i++) {
        free(struct_to_print->_data[i]);
    }
    free(struct_to_print->_data);
}

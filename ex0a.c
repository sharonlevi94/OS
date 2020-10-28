// ex0a
// OS course 2020, first semester.
// assignement by:
// Sharon Levi- ID 311593313, login- sharonlevi
// Bar Ifrah- OD 315566810, login- barif
// October 29th, 2020

// Get 2 input files and one output file from the user.
// The input files has name and grade data on students, output file is empty.
// The program reads the names of the students from the files,
// and prints them by ABC order to both console and output file.
// Wanted input from user- 3 names of txt files- i.e "filename.txt"

// compiled via linux terminal- using the command 'gcc -Wall <filename.c> -o <run_name>
// no input is reqired from user into terminal in this program.
#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/************CONST*****************/
#define _GNU_SOURCE
#define MAX_FILE_NAME_LEN  1000
#define STUDENT_NAME_LEN  50
//------------------------------------------------------------------
int terminate(FILE *);
FILE *open_files(char *);
void get_student_name(FILE *, char *);
void print_grades_to_output(FILE *, FILE *);
void print_student_name(FILE *, FILE *, char *);
void print_new_line(FILE *);
void close_file(FILE *);
void run_on_both_files(FILE *, FILE *, FILE *, char *, char *);
void run_on_one_file(FILE *, FILE *, char *);
//------------------------------------------------------------------
int main(){
    // input files read
    FILE *file_one = open_files("r");
    FILE *file_two = open_files("r");
    //output file read
    FILE *output = open_files("w");
    char stud_name1[STUDENT_NAME_LEN];
    char stud_name2[STUDENT_NAME_LEN];
    // while both files holds data
    run_on_both_files(file_one, file_two, output, stud_name1, stud_name2);
    // if the second file is empty
    if (!feof(file_one)) {
        run_on_one_file(file_one, output, stud_name1);
    }
    // if the first file is empty
    if (!feof(file_two)) {
        run_on_one_file(file_two, output, stud_name2);
    }
    close_file(file_one);
    close_file(file_two);
    close_file(output);
    return 0;
}

//------------------------------------------------------------------
int terminate(FILE *p2file){
    if (p2file == NULL) {
        printf("can't open file\n");
        exit(1);
    }
    return 0;
}
//------------------------------------------------------------------
FILE *open_files(char *opening_mode){
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
void print_grades_to_output(FILE *input_file, FILE *output_file) {
    char rest_of_line_grades;
    fscanf(input_file, "%c", &rest_of_line_grades);        // inserts a grade to 'grade'.
    while (rest_of_line_grades != '\n' && rest_of_line_grades != '\r' && rest_of_line_grades != '\0') {
        fprintf(output_file, "%c", rest_of_line_grades);    // prints 'grade' into output file.
        printf("%c", rest_of_line_grades);                       // prints 'grade' to consule.
        fscanf(input_file, "%c", &rest_of_line_grades);        // inserts a grade to 'grade'.
    }
}
//------------------------------------------------------------------
void print_student_name(FILE *input_file, FILE *output_file, char *stud_name) {
    fprintf(output_file, "%s", stud_name);               // prints the first student name to output file.
    printf("%s ", stud_name);                      // prints the first student name to console.
    print_grades_to_output(input_file, output_file);       // prints the rest of the line.
    fscanf(input_file, "%s", stud_name);             // reads the next student name in the file.
}
//------------------------------------------------------------------
void print_new_line(FILE *output_file) {
    fprintf(output_file, "%c", '\n');
    printf("\n");
}
//------------------------------------------------------------------
void close_file(FILE *file_to_close) {
    fclose(file_to_close);
}
//------------------------------------------------------------------
void get_student_name(FILE *input_file, char *student_name){
    fscanf(input_file, "%s", student_name);
}
//------------------------------------------------------------------
void run_on_both_files(FILE *input_file_1, FILE *input_file_2, FILE *output, char *stud_name1, char *stud_name2){
    
    //enter student names from each file:
    get_student_name(input_file_1, stud_name1);
    get_student_name(input_file_2, stud_name2);
    // runs untill one file is NULL(EOF)
    while ((input_file_1 != NULL && input_file_2 != NULL) && (!feof(input_file_1) && !feof(input_file_2))){
        // compares names between two files. if 1st name comes first in alphabetical order- goes into 'if'.
        if (strcmp(stud_name1, stud_name2) < 0){
            //we have to send the name to the output file - in this case the name from the first file.
            print_student_name(input_file_1, output, stud_name1);
        } else{
            
            if (strcmp(stud_name1, stud_name2) > 0){     // if the second name is first in alphabetical order- goes into 'else if'.
                print_student_name(input_file_2, output, stud_name2);
            } else{                                             // if both names are the same- will go in 'else'
                print_student_name(input_file_1, output, stud_name1);
                print_grades_to_output(input_file_2, output);       // to make one line with the student name.
                fscanf(input_file_2, "%s", stud_name2);             // for both files- because they held the same name.
            }
        }
        print_new_line(output);
    }
}
//------------------------------------------------------------------
void run_on_one_file(FILE *input_file, FILE *output, char *stud_name) {
    while (!feof(input_file)) {
        print_student_name(input_file, output, stud_name);
        print_new_line(output);
    }
}
//------------------------------------------------------------------

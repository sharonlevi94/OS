#include <stdlib.h>
#include <string.h>
#include <stdio.h>
/************CONST*****************/
#define _GNU_SOURCE
#define MAX_FILE_NAME_LEN  50
#define STUDENT_NAME_LEN  50
//------------------------------------------------------------------
int terminate(FILE *p2file);
FILE *open_files(char *opening_mode);
void print_grades_to_output(FILE *input_file, FILE *output_file);
void print_student_name(FILE *input_file, FILE *output_file, char *stud_name);
void print_new_line(FILE *output_file);
void close_files(FILE *input_file_1, FILE *input_file_2, FILE *output);
//------------------------------------------------------------------
int main(){
    // input files read
    FILE *file_one = open_files("r");
    FILE *file_two = open_files("r");
    //output file read
    FILE *output = open_files("w");
    //------------------------------------------------------------------
    // reads students names from files
    char stud_name1[STUDENT_NAME_LEN ];
    char stud_name2[STUDENT_NAME_LEN ];
    //enter student names from each file:
    fscanf(file_one, "%s", stud_name1);
    fscanf(file_two, "%s", stud_name2);
    //------------------------------------------------------------------
    //int *grade = NULL;
    // runs untill one file is NULL(EOF)
    while ((file_one != NULL && file_two != NULL) && (!feof(file_one) && !feof(file_two))){
        // compares names between two files. if 1st name comes first in alphabetical order- goes into 'if'.
        if (strcmp(stud_name1, stud_name2) < 0){
            //we have to send the name to the output file - in this case the name from the first file.
            print_student_name(file_one, output, stud_name1);
        } else{
            
            if (strcmp(stud_name1, stud_name2) > 0){     // if the second name is first in alphabetical order- goes into 'else if'.
                print_student_name(file_two, output, stud_name2);
            } else{                                             // if both names are the same- will go in 'else'
                print_student_name(file_one, output, stud_name1);
                print_grades_to_output(file_two, output);       // to make one line with the student name.
                fscanf(file_two, "%s", stud_name2);             // for both files- because they held the same name.
            }
        }
        print_new_line(output);
    }
    while (!feof(file_one)) {
        print_student_name(file_one, output, stud_name1);
        print_new_line(output);
    }
    
    while (!feof(file_two))
    {
        print_student_name(file_two, output, stud_name2);
        print_new_line(output);
    }
    close_files(file_one, file_two, output);
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
    while (rest_of_line_grades != '\n' && rest_of_line_grades != '\r') {
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
void close_files(FILE *input_file_1, FILE *input_file_2, FILE *output) {
    fclose(input_file_1);
    fclose(input_file_2);
    fclose(output);
}

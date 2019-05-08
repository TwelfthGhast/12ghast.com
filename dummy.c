// Dummy program to check for memory manipulation
// Coded by Dennis Ying
// Last updated: 08/05/2019
// Contact: z5163983@unsw.edu.au

#include <stdio.h>
#include <strings.h>

int main(void) {
    int number = 123456789;
    int *ptr_to_int = &number;
    int **ptr_to_ptr = &ptr_to_int;
    char fixed_string[128];
    strcpy(fixed_string, "This is in a buffer of length 128");
    char initial_string[] = "InitialValueString";
    char *string_literal = "StringLiteral";

    int c = 0;
    // Check for EOF
    // Ctrl-Z to exit program in Windows
    while (c != EOF) {
        printf("number:\t\t\t0x%X\t%d\n", &number, number);
        printf("ptr_to_int:\t\t0x%X\t0x%X\n", &ptr_to_int, ptr_to_int);
        printf("ptr_to_ptr:\t\t0x%X\t0x%X\n", &ptr_to_ptr, ptr_to_ptr);
        printf("fixed_string:\t\t0x%X\t%s\n", &fixed_string, fixed_string);
        printf("fixed_string:\t\t0x%X\t%s\n", &initial_string, initial_string);
        printf("string_literal:\t\t0x%X\t%s\n", &string_literal, string_literal);

        printf("\n------------------------------------\n\n");
        printf("Press ENTER to print again\n");
        getchar();
        printf("------------------------------------\n\n");
    }
}

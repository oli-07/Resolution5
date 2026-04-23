#include <ctype.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define INPUT_LENGTH 100
#define MAX_CONTACTS 100

char *FILENAME = "contact_book_data.csv";

typedef struct Contact {
    char name[INPUT_LENGTH];
    char address[INPUT_LENGTH];
    char email[INPUT_LENGTH];
    char number[INPUT_LENGTH];
} Contact;

Contact contact_array[MAX_CONTACTS];

int add_new_entry();
int list_contacts();
int read_from_csv(Contact contact_array[]);
void print_contact(const Contact *contact);
void show_help();
void trim_newline(char *str);

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILENAME = argv[1];
    }

    char input[INPUT_LENGTH];

    while (1) {
        printf("Contact Book Menu\n");
        printf("A - Add new contact\n");
        printf("L - List all contacts\n");
        printf("H - Help\n");
        printf("Q - Quit\n");
        printf("Choice: ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        trim_newline(input);
        char choice = tolower((unsigned char)input[0]);

        if (choice == 'a') {
            add_new_entry();
        } else if (choice == 'l') {
            list_contacts();
        } else if (choice == 'h') {
            show_help();
        } else if (choice == 'q') {
            return 0;
        } else {
            printf("'%c' is not a known command.\n\n", input[0]);
        }
    }

    return 0;
}

void trim_newline(char *str) {
    str[strcspn(str, "\r\n")] = '\0';
}

void show_help() {
    printf("\nCommands:\n");
    printf("A - Add new contact\n");
    printf("L - List all contacts\n");
    printf("H - Help\n");
    printf("Q - Quit\n\n");
}
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

void trim_newline(char *str);
void show_help();
int add_new_entry();
int list_contacts();
int read_from_csv(Contact contact_array[]);
void print_contact(const Contact *contact);

int main(int argc, char *argv[]) {
    if (argc > 1) {
        FILENAME = argv[1];
    }

    char input[INPUT_LENGTH];

    while (1) {
        printf("\nContact Book\n");
        printf("a - add new contact\n");
        printf("l - list contacts\n");
        printf("h - help\n");
        printf("q - quit\n");
        printf("enter command: ");

        if (fgets(input, sizeof(input), stdin) == NULL) {
            break;
        }

        trim_newline(input);

        if (input[0] == '\0') {
            printf("please type something\n");
            continue;
        }

        char choice = tolower((unsigned char)input[0]);

        if (choice == 'a') {
            add_new_entry();
        } else if (choice == 'l') {
            list_contacts();
        } else if (choice == 'h') {
            show_help();
        } else if (choice == 'q') {
            printf("bye\n");
            return 0;
        } else {
            printf("%c is not a command\n", input[0]);
        }
    }

    return 0;
}

void trim_newline(char *str) {
    str[strcspn(str, "\r\n")] = '\0';
}

void show_help() {
    printf("\ncommands:\n");
    printf("a = add new contact\n");
    printf("l = list contacts\n");
    printf("h = help\n");
    printf("q = quit\n\n");
}

int add_new_entry() {
    FILE *fptr;
    char name[INPUT_LENGTH];
    char address[INPUT_LENGTH];
    char email[INPUT_LENGTH];
    char number[INPUT_LENGTH];

    printf("name: ");
    if (fgets(name, sizeof(name), stdin) == NULL) return 1;
    trim_newline(name);

    printf("address: ");
    if (fgets(address, sizeof(address), stdin) == NULL) return 1;
    trim_newline(address);

    printf("email: ");
    if (fgets(email, sizeof(email), stdin) == NULL) return 1;
    trim_newline(email);

    printf("number: ");
    if (fgets(number, sizeof(number), stdin) == NULL) return 1;
    trim_newline(number);

    fptr = fopen(FILENAME, "a");
    if (fptr == NULL) {
        printf("could not open file\n");
        return 1;
    }

    fprintf(fptr, "%s,%s,%s,%s\n", name, address, email, number);
    fclose(fptr);

    printf("saved contact\n");
    return 0;
}

void print_contact(const Contact *contact) {
    printf("Name: %s\n", contact->name);
    printf("Address: %s\n", contact->address);
    printf("Email: %s\n", contact->email);
    printf("Number: %s\n", contact->number);
    printf("\n");
}

int list_contacts() {
    int contact_count = read_from_csv(contact_array);

    if (contact_count == 0) {
        printf("no contacts found\n");
        return 0;
    }

    for (int i = 0; i < contact_count; i++) {
        print_contact(&contact_array[i]);
    }

    return 0;
}

int read_from_csv(Contact contact_array[]) {
    FILE *fptr;
    char buffer[(INPUT_LENGTH * 4) + 5];
    int i = 0;

    fptr = fopen(FILENAME, "r");
    if (fptr == NULL) {
        printf("could not open %s\n", FILENAME);
        return 0;
    }

    while (fgets(buffer, sizeof(buffer), fptr)) {
        char *field;
        int x = 0;

        char *new_line_pointer = strchr(buffer, '\n');
        if (new_line_pointer) {
            *new_line_pointer = '\0';
        }

        field = strtok(buffer, ",");

        while (field != NULL) {
            if (x == 0) {
                strncpy(contact_array[i].name, field, INPUT_LENGTH - 1);
                contact_array[i].name[INPUT_LENGTH - 1] = '\0';
            } else if (x == 1) {
                strncpy(contact_array[i].address, field, INPUT_LENGTH - 1);
                contact_array[i].address[INPUT_LENGTH - 1] = '\0';
            } else if (x == 2) {
                strncpy(contact_array[i].email, field, INPUT_LENGTH - 1);
                contact_array[i].email[INPUT_LENGTH - 1] = '\0';
            } else if (x == 3) {
                strncpy(contact_array[i].number, field, INPUT_LENGTH - 1);
                contact_array[i].number[INPUT_LENGTH - 1] = '\0';
            }

            x++;
            field = strtok(NULL, ",");
        }

        i++;
        if (i >= MAX_CONTACTS) {
            break;
        }
    }

    fclose(fptr);
    return i;
} 
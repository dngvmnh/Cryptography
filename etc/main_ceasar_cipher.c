#include<stdio.h>
#include<ctype.h>


int main(int argc, char const *argv[]) {
    char text[500], ch;
    int key;

    // Taking user input.
    printf("Enter a message to encrypt: ");
    scanf("%s", text);

    printf("Enter the key: ");
    scanf("%d", & key);

    // Visiting character by character.
    for (int i = 0; text[i] != '\0'; ++i) {
        ch = text[i];

        // Check for valid characters.
        if (isalnum(ch)) {
            //Lowercase characters.
            if (islower(ch)) 
                ch = (ch - 'a' + key) % 26 + 'a';

            // Uppercase characters.
            if (isupper(ch)) 
                ch = (ch - 'A' + key) % 26 + 'A';
            
            // Numbers.
            if (isdigit(ch)) 
                ch = (ch - '0' + key) % 10 + '0';
        }
        // Invalid character.
        else
            printf("Invalid Message");

        // Adding encoded answer.
        text[i] = ch;
    }

    printf("Encrypted message: %s", text);
    return 0;
}
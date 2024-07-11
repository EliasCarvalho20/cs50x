#include <cs50.h>
#include <ctype.h>
#include <stdio.h>
#include <string.h>

bool is_key_valid(string message, int message_len);
void encrypt_message(string key, string message, int message_len);

int main(int argc, string argv[])
{
    // Check if the program is being executed with an argument.
    if (argc != 2)
    {
        printf("You must provide a key as argument.");
        return 1;
    }

    // Get the key
    const string key = argv[1];
    int key_len = strlen(key);

    // Checks for a valid key
    if (!is_key_valid(key, key_len))
    {
        return 1;
    }

    // Get the message that will be encrypted
    string message = get_string("Message: ");
    int message_len = strlen(message);
    
    encrypt_message(key, message, message_len);
    return 0;
}

bool is_key_valid(string key, int key_len)
{
    // Check if the length of provided key equals 26
    if (key_len != 26)
    {
        printf("Key must contain 26 characters.");
        return false;
    }

    // Checks for duplicated letters in the key
    bool is_duplicated[26] = {false};
    for (int i = 0; i < key_len; i++)
    {
        // If the current character is not a letter, break the loop
        if (!isalpha(key[i]))
        {
            printf("Key contains an invalid character, only letters allowed.");
            return false;
        }

        // Convert the letter to uppercase and then get its index
        key[i] = toupper(key[i]);
        int index = key[i] - 'A';
        // If the current letter is already in the array, break the loop
        if (is_duplicated[index]) {
            printf("Duplicated character found in the key.");
            return false;
        }

        is_duplicated[index] = true;
    }
    return true;   
}

void encrypt_message(string key, string message, int message_len)
{
    printf("ciphertext: ");
    for (int i = 0; i < message_len; i++)
    {
        // Get the letter index in the message
        char current_char = message[i];
        int index = toupper(current_char) - 'A';

        // Checks if the current character is a letter or a special character
        if (index >= 0 && index < 26)
        {
            /* Checks whether the current letter is lowercase or uppercase,
             * and prints the corresponding encrypted letter
            */
            if (islower(current_char))
            {
                printf("%c", tolower(key[index]));
            }
            else
            {
                printf("%c", toupper(key[index]));
            }
        }
        else
        {
            printf("%c", current_char);
        }
    }
    printf("\n");
}

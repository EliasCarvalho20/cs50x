#include <stdio.h>
#include <cs50.h>
#include <string.h>
#include <ctype.h>
#include <stdlib.h>


bool check_digits(int digits_len, string numbers) {
    for (int i = 0; i < digits_len; i++) {
        if (!isdigit(numbers[i])) {
            return false;
        }
    }
    return true;
}

int main(void) {
    string numbers = get_string("Number: ");
    int digits_len = strlen(numbers);
    if (digits_len < 13) {
        printf("INVALID\n");
        return 0;
    }
    while (!check_digits(digits_len, numbers)) {
        numbers = get_string("Number: ");
        digits_len = strlen(numbers);
    }

    int sum = 0;
    for (int i = digits_len - 1; i >= 0; i--) {
        int digit = numbers[i] - '0';

        if ((digits_len - i) % 2 == 0) {
            digit *= 2;

            if (digit > 9) {
                digit -= 9;
            }
        }
        sum += digit;
    }

    if (sum % 10 != 0) {
        printf("INVALID\n");
        return 0;
    }

    int first_index = numbers[0] - '0';
    char substring[3];
    strncpy(substring, numbers, 2);
    substring[2] = '\0';
    int first_two_index = atoi(substring);
    if (digits_len == 15 && (first_two_index == 34 || first_two_index == 37)) {
        printf("AMEX\n");
        return 0;
    } else if (digits_len == 16 && (first_two_index >= 51 && first_two_index <= 55)) {
        printf("MASTERCARD\n");
    } else if ((digits_len == 13 || digits_len == 16) && first_index == 4) {
        printf("VISA\n");
    } else {
        printf("INVALID\n");
    }

    return 0;
}

#include <cs50.h>
#include <ctype.h>
#include <math.h>
#include <stdio.h>
#include <string.h>

float get_number_of_words_in_text(char text[]);

float get_avg_letters_in_text(string text, float words_count);

float get_avg_sentence_in_text(char text[], float words_count);

void calculate_readability(int score);

int main(void)
{
    string text = get_string("");
    float words_count = get_number_of_words_in_text(text);
    float avg_letters = get_avg_letters_in_text(text, words_count);
    float avg_sentence = get_avg_sentence_in_text(text, words_count);
    int index_score = (int) round(0.0588 * avg_letters - 0.296 * avg_sentence - 15.8);

    calculate_readability(index_score);

    return 0;
}

float get_number_of_words_in_text(char text[])
{
    float words_count = 1.0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isblank(text[i]))
        {
            words_count += 1;
        }
    }
    return words_count;
}

float get_avg_letters_in_text(string text, float words_count)
{
    float avg_letters = 0.0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (isalpha(text[i]))
        {
            avg_letters += 1.0;
        }
    }
    return (avg_letters / words_count) * 100;
}

float get_avg_sentence_in_text(char text[], float words_count)
{
    float avg_sentence = 0.0;
    for (int i = 0; i < strlen(text); i++)
    {
        if (text[i] == '.' || text[i] == '!' || text[i] == '?')
        {
            avg_sentence += 1.0;
        }
    }
    return (avg_sentence / words_count) * 100;
}

void calculate_readability(int score)
{
    if (score < 1)
    {
        printf("Before Grade 1\n");
    }
    else if (score <= 2)
    {
        printf("Grade 2\n");
    }
    else if (score > 2 && score <= 16)
    {
        printf("Grade %d\n", score);
    }
    else
    {
        printf("Grade 16+\n");
    }
}

import math


def get_number_of_words_in_text(text: str) -> float:
    return len(text.split())


def get_avg_letters_in_text(text: str, words_count: float) -> float:
    avg_letters = 0.0
    for letter in text:
        if letter.isalpha():
            avg_letters += 1.0

    return (avg_letters / words_count) * 100


def get_avg_sentence_in_text(text: str, words_count: float) -> float:
    avg_sentence = 0.0
    for sentence in text:
        if sentence == "." or sentence == "!" or sentence == "?":
            avg_sentence += 1.0

    return (avg_sentence / words_count) * 100


def calculate_readability(score: float):
    if score < 1:
        print("Before Grade 1")
    elif score <= 2:
        print("Grade 2")
    elif 2 < score <= 16:
        print(f"Grade {score}")
    else:
        print("Grade 16+")


def main():
    text = input("Text: ")
    words_count = get_number_of_words_in_text(text)
    avg_letters = get_avg_letters_in_text(text, words_count)
    avg_sentence = get_avg_sentence_in_text(text, words_count)

    index_score = int(round(0.0588 * avg_letters - 0.296 * avg_sentence - 15.8))
    calculate_readability(index_score)


if __name__ == "__main__":
    main()

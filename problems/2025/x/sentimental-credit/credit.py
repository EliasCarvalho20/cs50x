def is_valid(card_number):
    if not card_number.isdigit():
        return False

    total = 0
    for i in range(len(card_number) - 1, -1, -1):
        digit = int(card_number[i])
        if (len(card_number) - i) % 2 == 0:
            digit *= 2
            if digit > 9:
                digit -= 9
        total += digit

    return total % 10 == 0


def get_card_type(card_number):
    length = len(card_number)
    if length == 15 and (
        card_number.startswith("34") or card_number.startswith("37")
    ):
        return "AMEX"
    elif length == 16 and (
        51 <= int(card_number[:2]) <= 55
    ):
        return "MASTERCARD"
    elif (length == 13 or length == 16) and card_number.startswith("4"):
        return "VISA"
    else:
        return "INVALID"


def main():
    card_number = input("Number: ")
    if is_valid(card_number):
        card_type = get_card_type(card_number)
        print(card_type)
    else:
        print("INVALID")


if __name__ == "__main__":
    main()


# check50 cs50/problems/2024/x/sentimental/credit

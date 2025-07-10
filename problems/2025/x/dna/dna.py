import csv
import sys
import re


def get_args() -> list:
    args = sys.argv

    if len(args) != 3:
        exit(1)

    return args


def read_database(filename: str) -> list:
    rows = []
    with open(filename) as file:
        reader = csv.DictReader(file)
        for row in reader:
            rows.append(row)
    return rows


def read_dna_sequence(filename: str) -> str:
    with open(filename) as file:
        return file.read()


def main() -> None:
    args = get_args()

    database = read_database(args[1])
    dna_sequence = read_dna_sequence(args[2])

    matches = {}
    for k in database[0].keys():
        if k == "name":
            continue

        matches[k] = longest_match(dna_sequence, k)

    match = False
    for row in database:
        name = row["name"]
        del row["name"]
        if row == matches:
            match = True
            print(name)
            break

    if not match:
        print("No match")

    return


def longest_match(sequence: str, subsequence: str) -> str:
    """Returns length of longest run of subsequence in sequence."""

    # Initialize variables
    longest_run = 0
    subsequence_length = len(subsequence)
    sequence_length = len(sequence)

    # Check each character in sequence for most consecutive runs of subsequence
    for i in range(sequence_length):

        # Initialize count of consecutive runs
        count = 0

        # Check for a subsequence match in a "substring" (a subset of characters) within sequence
        # If a match, move substring to next potential match in sequence
        # Continue moving substring and checking for matches until out of consecutive matches
        while True:

            # Adjust substring start and end
            start = i + count * subsequence_length
            end = start + subsequence_length

            # If there is a match in the substring
            if sequence[start:end] == subsequence:
                count += 1

            # If there is no match in the substring
            else:
                break

        # Update most consecutive matches found
        longest_run = max(longest_run, count)

    # After checking for runs at each character in seqeuence, return longest run found
    return str(longest_run)


if __name__ == "__main__":
    main()

"""Module to ingest a CSV file downloaded from this google sheet template:
https://docs.google.com/spreadsheets/d/1Ykk0tgYsliaIzMqltVZ3Ye2wybARJx4l-eyqKgYxkgA

Notes:
    This script reformats a CSV file into an array & saves it to main/quotes.h
"""
import csv
import pathlib
import os


def ingest_quotes_csv(csv_file="quote_ingestion_example.csv", skip_first_line=True):
    """Ingest the quotes from the given CSV file.

    Args:
        csv_file (str): Path to csv file.
        skip_first_line (bool): Whether the first line (usually contains labels)
            should be skipped.
    """
    with open(csv_file, "r") as f:
        reader = csv.reader(f)
    
        # Skip the headers
        if skip_first_line:
            next(reader, None)

        quotes = []
        for row in reader:
            is_joke, author, message = row
            # Either the author or the message of a quote must exist.
            if not (author or message):
                continue
            
            # Escape double quotes in message
            message = message.replace('"', r'\"')

            # Format the quote appropriately for Arduino.
            quote_string = '{{{}, "{}", "{}"}},'.format(
                is_joke.lower(), author, message
            )
            quotes.append(quote_string)

    # Concatenate all quotes and store them to the quotes.h file.
    output_string = "Quote availableQuotes [{}] = {{\n  {}\n}};".format(
        len(quotes), "\n  ".join(quotes)
    )

    base_path = pathlib.Path(__file__).parent.absolute()
    quotes_file = os.path.join(base_path, "main", "quotes.h")
    with open(quotes_file, "w") as _f:
        _f.write(output_string)

    print("Ingested a total of {} quotes!".format(len(quotes)))


if __name__ == "__main__":
    ingest_quotes_csv()

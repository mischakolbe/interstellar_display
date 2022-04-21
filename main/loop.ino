/*Repeat while microprocessor is running.*/
void loop() {
  getRandomQuoteId();
  prepareForNextQuote();

  printAuthor();
  printQuote();

  holdQuote();
}

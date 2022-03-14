/*XYZ*/
void loop() {
  getRandomQuoteId();
  prepareForNextQuote();

  printAuthor();
  printQuote();

  holdQuote();
}

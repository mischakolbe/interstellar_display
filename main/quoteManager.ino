/*Get a random quote, except for DEBUG mode, which returns quotes in order.*/
void getRandomQuoteId() {
  if (DEBUG) {
    currentQuoteId = (currentQuoteId + 1) % numAvailableQuotes;
  } else {
    currentQuoteId = random(numAvailableQuotes);
  }
}


/*Set parameters up for printing the next quote.*/
void prepareForNextQuote() {
  String author = availableQuotes[currentQuoteId].author;
  if (author.length() == 0 && !availableQuotes[currentQuoteId].isJoke) {
    startLine = 0;
  } else {
    startLine = 1;
  }
  numLines = numMaxLines - startLine;
}


/*Animate on the Author in the top right of the display.*/
void printAuthor() {
  String author = availableQuotes[currentQuoteId].author;

  if (author.length() == 0) {
    return;
  }
  
  for (int i = author.length(); i > -1; i--) {
    display.clearDisplay();

    author = availableQuotes[currentQuoteId].author;
    author.remove(author.length()-i, i);
    author = authorPrefix + author;

    display.setCursor(cursorWidth*(maxCharPerLine - author.length()), 0);
    display.print(author);
    
    display.display();

    delay(random(minWriteTime, maxWriteTime));
  }
  delay(random(maxWriteTime*4, maxWriteTime*8));
}


/*Animate on the current quote.*/
void printQuote() {
  String quoteInProgress = availableQuotes[currentQuoteId].text;
  Serial.print("Printing new quote: ");
  Serial.println(quoteInProgress);

  // Reset line and cursor
  currentLine = startLine;
  currentPosition = 0;
  updateCursorPosition();

  // Print as long as there is still text to print from this current quote.
  while(quoteInProgress.length() > 0){
    // Shuffle up display, if running out of space.
    if (currentLine - startLine >= numLines) {
      shuffleUpDisplayLines();
    }
    currentLine = min(currentLine, numMaxLines - 1);
    
    lineString = "";
    for (currentPosition = 0; currentPosition < min(maxCharPerLine, quoteInProgress.length()); currentPosition++) {
      display.clearDisplay();

      addAuthor();

      addCurrentDisplayLines();

      display.setCursor(0, lineHeight * currentLine);
      lineString += quoteInProgress.charAt(currentPosition);

      updateCursorPosition();
      addCursor();

      display.print(lineString);
      display.display();

      delay(random(minWriteTime, maxWriteTime));
    }

    currentDisplayLines[currentLine - startLine] = lineString;

    // Remove the newly printed line of characters from the quote
    quoteInProgress.remove(0, maxCharPerLine);

    currentLine++;
  }
}


/*Hold the current quote on the display, while blinking the cursor.*/
void holdQuote() {
  bool isCursorVisible = true;
  int startTime = millis();
  int jokeIndicatorDelay = random(minJokeIndicatorDelay, maxJokeIndicatorDelay);
  for (int i = 0; i < holdBlinkNumTimes*2; i++) {
    display.clearDisplay();
    
    addAuthor();

    addCurrentDisplayLines();

    if (isCursorVisible) {
      addCursor();
    }
    isCursorVisible = !isCursorVisible;

    if (availableQuotes[currentQuoteId].isJoke && millis()-startTime > jokeIndicatorDelay) {
      addJokeIndicator();
    }

    display.display();
    delay(cursorBlinkSpeed);
  }
}

/*Add the lines that should currently be shown to the display.*/
void addCurrentDisplayLines() {
  for (int i = 0; i < currentLine - startLine; i++) {
    display.setCursor(0, lineHeight * (i + startLine));
    display.print(currentDisplayLines[i]);
  }
}


/*Adds the author at the top right of the display.*/
void addAuthor() {
  String author = availableQuotes[currentQuoteId].author;
  if (author.length() == 0) {
    return;
  }
  author = authorPrefix + author;
  display.setCursor(cursorWidth*(maxCharPerLine - author.length()), 0);
  display.print(author);
}


/*Adds the cursor at the current cursor position.*/
void addCursor() {
  display.fillRect(
    cursorWidth*currentCursorPosition,  // x corner
    lineHeight*currentCursorLine,  // y corner
    cursorWidth,  // width
    cursorHeight,  // height
    WHITE  // color
  );
}


/*Adds the joke indicator at the top left of the display.*/
void addJokeIndicator() {
  // (x corner, y corner, width, height, color)
  display.fillRect(0, 1, jokeIndicatorWidth, jokeIndicatorHeight-2, WHITE); 
  display.fillRect(1, 0, jokeIndicatorWidth-2, jokeIndicatorHeight, WHITE); 
}


/*Update the cursor to be ahead of the text to be printed.*/
void updateCursorPosition() {
  currentCursorPosition = currentPosition + 1;
  currentCursorLine = currentLine;
  if (currentCursorPosition >= maxCharPerLine){
    // Wrap cursor onto next line, if it would be off-screen.
    currentCursorPosition = 0;
    currentCursorLine++;
  } 
}


/*Move all lines that are currently being displayed up by 1.*/
void shuffleUpDisplayLines() {
  for (int i = 0; i < numLines-1; i++){
    currentDisplayLines[i] = currentDisplayLines[i + 1];
  }
}

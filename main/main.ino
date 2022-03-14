#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

#include <Fonts/FreeMono9pt7b.h>

#include "dataStructures.h"
#include "quotes.h"


// GLOBAL VARIABLES
const int cursorWidth = 6;
const int cursorHeight = 8;
const int jokeIndicatorWidth = 6;
const int jokeIndicatorHeight = 7;
String lineString = "";
int currentPosition = 0;
int currentLine = 0;  // Always the actual line on the display: currentLine=3 is line 3 on the display, even if the startLine is 2.
int currentCursorPosition = 0;
int currentCursorLine = 0;
int currentQuoteId = -1;
int startLine = 1; // Determines how many lines are left blank (from the top)
const int numMaxLines = 8;  // Relies on font size etc.
int numLines = numMaxLines - startLine;  // Relies on font size etc.
String currentDisplayLines[numMaxLines];
int numAvailableQuotes = sizeof (availableQuotes) / sizeof (availableQuotes[0]);


// Declaration for an SSD1306 display connected to I2C (SDA, SCL pins)
#define SCREEN_ADDRESS 0x3C
#define SCREEN_WIDTH 128 // OLED display width, in pixels
#define SCREEN_HEIGHT 64 // OLED display height, in pixels
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, -1);


// LOW LEVEL SETTINGS
const int maxCharPerLine = 21;  // max characters per line (to avoid cut off characters)


// SETTINGS
const int lineHeight = 8;
const int cursorBlinkSpeed = 500;
const int holdBlinkNumTimes = 5; // A blink is a full cycle: On & Off
const int minJokeIndicatorDelay = cursorBlinkSpeed*holdBlinkNumTimes/3;
const int maxJokeIndicatorDelay = cursorBlinkSpeed*holdBlinkNumTimes;
const int minWriteTime = 15; // Shortest time to write new character.
const int maxWriteTime = 250;  // Longest time to write new character.
const String authorPrefix = ">";
const bool DEBUG = false;

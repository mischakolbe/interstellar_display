/*Initialize the microprocessor.*/
void setup() {
  Serial.begin(9600);
  Serial.println("Setting up!");
  if(!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;); // Don't proceed, loop forever
  }

  display.clearDisplay();  // Clear the buffer

  display.setTextColor(SSD1306_WHITE);
  display.setTextWrap(false);

  // Increase A/D converter resolution to 12-bits, for values between 0 and 4095 
  analogReadResolution(12);
  // Use a floating analog pin to generate a random seed value.
  randomSeed(analogRead(A2));

  if (DEBUG) {
    cursorBlinkSpeed = 150;
    holdBlinkNumTimes = 5; // A blink is a full cycle: On & Off
    minWriteTime = 5; // Shortest time to write new character.
    maxWriteTime = 15;  // Longest time to write new character.
  }

}

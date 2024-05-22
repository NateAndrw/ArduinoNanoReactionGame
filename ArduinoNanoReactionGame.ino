// PROJECT  :Arduino Reaction Time Game
// PURPOSE  :ISP
// COURSE   :ICD2O
// AUTHOR   :Nathan Andrew
// DATE     :2024 05 22
// MCU      :328P
// STATUS   :Working
// REFERENCE:

// Pin definitions
#define STARTSWITCH 4  // Pin for the on/off switch
#define SIGNALED 3     // Pin for LED indicator
#define STOPBUTTON 2   // Pin for stop button
// Seven Segment Display A
#define DISPLAYAG 12  // G pin for display A
#define DISPLAYAF 11  // F pin for display A
#define DISPLAYAA 10  // A pin for display A
#define DISPLAYAB 9   // B pin for display A
#define DISPLAYAE A0  // E pin for display A
#define DISPLAYAD A1  // D pin for display A
#define DISPLAYAC A2  // C pin for display A
// Seven Segment Display B
#define DISPLAYBG 8   // G pin for display B
#define DISPLAYBF 7   // F pin for display B
#define DISPLAYBA 6   // A pin for display B
#define DISPLAYBB 5   // B pin for display B
#define DISPLAYBE A3  // E pin for display B
#define DISPLAYBD A4  // D pin for display B
#define DISPLAYBC A5  // C pin for display B

// Variables
bool gameStarted = false;   // Track if the game is started
bool gameEnded = false;     // Track if the game is ended
uint8_t scoreA = 0;         // Score for display A
uint8_t scoreB = 0;         // Score for display B
uint16_t reactionTime = 0;  // Store reaction time
bool prevSwitchState = LOW; // Previous state of the start switch

void setup() {
  pinMode(STARTSWITCH, INPUT);
  pinMode(SIGNALED, OUTPUT);
  pinMode(STOPBUTTON, INPUT_PULLUP);
  // Seven Segment Display A
  pinMode(DISPLAYAG, OUTPUT);  // G pin for display A
  pinMode(DISPLAYAF, OUTPUT);  // F pin for display A
  pinMode(DISPLAYAA, OUTPUT);  // A pin for display A
  pinMode(DISPLAYAB, OUTPUT);  // B pin for display A
  pinMode(DISPLAYAE, OUTPUT);  // E pin for display A
  pinMode(DISPLAYAD, OUTPUT);  // D pin for display A
  pinMode(DISPLAYAC, OUTPUT);  // C pin for display A
  // Seven Segment Display B
  pinMode(DISPLAYBG, OUTPUT);  // G pin for display B
  pinMode(DISPLAYBF, OUTPUT);  // F pin for display B
  pinMode(DISPLAYBA, OUTPUT);  // A pin for display B
  pinMode(DISPLAYBB, OUTPUT);  // B pin for display B
  pinMode(DISPLAYBE, OUTPUT);  // E pin for display B
  pinMode(DISPLAYBD, OUTPUT);  // D pin for display B
  pinMode(DISPLAYBC, OUTPUT);  // C pin for display B

  Serial.begin(9600);
}

void startGame() {
  gameStarted = true;  // Start Game
  gameEnded = false;   // Reset Game

  uint32_t randomDelay = random(5000, 10000);  // Corrected range for random delay
  delay(randomDelay);
  digitalWrite(SIGNALED, HIGH);
  reactionTime = millis();  // Starts the time when the LED goes HIGH
}

void endGame() {
  gameEnded = true;
  digitalWrite(SIGNALED, LOW);  // Turn off the LED when button is pressed (LOW)
}

void resetGame() {
  gameStarted = false;
  gameEnded = false;
  scoreA = 0;
  scoreB = 0;
  reactionTime = 0;
}

void loop() {
  bool currentSwitchState = digitalRead(STARTSWITCH);

  // Detect if the switch was turned off and then back on
  if (prevSwitchState == HIGH && currentSwitchState == LOW) {
    resetGame();
  }
  prevSwitchState = currentSwitchState;

  // Start the game if the start switch is HIGH and the game is not already started
  if (currentSwitchState == HIGH && !gameStarted && !gameEnded) {
    startGame();
  }

  // If the stop button is pressed, calculate the reaction time
  if (digitalRead(STOPBUTTON) == LOW && gameStarted && !gameEnded) {
    uint32_t stopTime = millis();
    reactionTime = stopTime - reactionTime;  // Calculate the reaction time
    gameStarted = false;
    endGame();

    if (reactionTime != 0) {
      // Calculate Game Score
      if (reactionTime >= 1000) {
        scoreA = 0;
        scoreB = 1;
      } else if (reactionTime >= 950) {
        scoreA = 0;
        scoreB = 2;
      } else if (reactionTime >= 900) {
        scoreA = 0;
        scoreB = 3;
      } else if (reactionTime >= 850) {
        scoreA = 0;
        scoreB = 4;
      } else if (reactionTime >= 800) {
        scoreA = 0;
        scoreB = 5;
      } else if (reactionTime >= 750) {
        scoreA = 0;
        scoreB = 6;
      } else if (reactionTime >= 700) {
        scoreA = 0;
        scoreB = 7;
      } else if (reactionTime >= 650) {
        scoreA = 0;
        scoreB = 8;
      } else if (reactionTime >= 600) {
        scoreA = 0;
        scoreB = 9;
      } else if (reactionTime >= 550) {
        scoreA = 1;
        scoreB = 0;
      } else if (reactionTime >= 500) {
        scoreA = 1;
        scoreB = 1;
      } else if (reactionTime >= 450) {
        scoreA = 1;
        scoreB = 2;
      } else if (reactionTime >= 400) {
        scoreA = 1;
        scoreB = 3;
      } else if (reactionTime >= 350) {
        scoreA = 1;
        scoreB = 4;
      } else if (reactionTime >= 300) {
        scoreA = 1;
        scoreB = 5;
      } else if (reactionTime >= 250) {
        scoreA = 1;
        scoreB = 6;
      } else if (reactionTime >= 200) {
        scoreA = 1;
        scoreB = 7;
      } else if (reactionTime >= 150) {
        scoreA = 1;
        scoreB = 8;
      } else if (reactionTime >= 100) {
        scoreA = 1;
        scoreB = 9;
      } else {
        scoreA = 2;
        scoreB = 0;
      }
    }
  }

  // Display Score A
  if (scoreA == 0) {
    digitalWrite(DISPLAYAG, LOW);
    digitalWrite(DISPLAYAF, HIGH);
    digitalWrite(DISPLAYAA, HIGH);
    digitalWrite(DISPLAYAB, HIGH);
    digitalWrite(DISPLAYAE, HIGH);
    digitalWrite(DISPLAYAD, HIGH);
    digitalWrite(DISPLAYAC, HIGH);
  } else if (scoreA == 1) {
    digitalWrite(DISPLAYAG, LOW);
    digitalWrite(DISPLAYAF, LOW);
    digitalWrite(DISPLAYAA, LOW);
    digitalWrite(DISPLAYAB, HIGH);
    digitalWrite(DISPLAYAE, LOW);
    digitalWrite(DISPLAYAD, LOW);
    digitalWrite(DISPLAYAC, HIGH);
  } else if (scoreA == 2) {
    digitalWrite(DISPLAYAG, HIGH);
    digitalWrite(DISPLAYAF, LOW);
    digitalWrite(DISPLAYAA, HIGH);
    digitalWrite(DISPLAYAB, HIGH);
    digitalWrite(DISPLAYAE, HIGH);
    digitalWrite(DISPLAYAD, HIGH);
    digitalWrite(DISPLAYAC, LOW);
  }

  // Display Score B
  if (scoreB == 0) {
    digitalWrite(DISPLAYBG, LOW);
    digitalWrite(DISPLAYBF, HIGH);
    digitalWrite(DISPLAYBA, HIGH);
    digitalWrite(DISPLAYBB, HIGH);
    digitalWrite(DISPLAYBE, HIGH);
    digitalWrite(DISPLAYBD, HIGH);
    digitalWrite(DISPLAYBC, HIGH);
  } else if (scoreB == 1) {
    digitalWrite(DISPLAYBG, LOW);
    digitalWrite(DISPLAYBF, LOW);
    digitalWrite(DISPLAYBA, LOW);
    digitalWrite(DISPLAYBB, HIGH);
    digitalWrite(DISPLAYBE, LOW);
    digitalWrite(DISPLAYBD, LOW);
    digitalWrite(DISPLAYBC, HIGH);
  } else if (scoreB == 2) {
    digitalWrite(DISPLAYBG, HIGH);
    digitalWrite(DISPLAYBF, LOW);
    digitalWrite(DISPLAYBA, HIGH);
    digitalWrite(DISPLAYBB, HIGH);
    digitalWrite(DISPLAYBE, HIGH);
    digitalWrite(DISPLAYBD, HIGH);
    digitalWrite(DISPLAYBC, LOW);
  } else if (scoreB == 3) {
    digitalWrite(DISPLAYBG, HIGH);
    digitalWrite(DISPLAYBF, LOW);
    digitalWrite(DISPLAYBA, HIGH);
    digitalWrite(DISPLAYBB, HIGH);
    digitalWrite(DISPLAYBE, LOW);
    digitalWrite(DISPLAYBD, HIGH);
    digitalWrite(DISPLAYBC, HIGH);
  } else if (scoreB == 4) {
    digitalWrite(DISPLAYBG, HIGH);
    digitalWrite(DISPLAYBF, HIGH);
    digitalWrite(DISPLAYBA, LOW);
    digitalWrite(DISPLAYBB, HIGH);
    digitalWrite(DISPLAYBE, LOW);
    digitalWrite(DISPLAYBD, LOW);
    digitalWrite(DISPLAYBC, HIGH);
  } else if (scoreB == 5) {
    digitalWrite(DISPLAYBG, HIGH);
    digitalWrite(DISPLAYBF, HIGH);
    digitalWrite(DISPLAYBA, HIGH);
    digitalWrite(DISPLAYBB, LOW);
    digitalWrite(DISPLAYBE, LOW);
    digitalWrite(DISPLAYBD, HIGH);
    digitalWrite(DISPLAYBC, HIGH);
  } else if (scoreB == 6) {
    digitalWrite(DISPLAYBG, HIGH);
    digitalWrite(DISPLAYBF, HIGH);
    digitalWrite(DISPLAYBA, HIGH);
    digitalWrite(DISPLAYBB, LOW);
    digitalWrite(DISPLAYBE, HIGH);
    digitalWrite(DISPLAYBD, HIGH);
    digitalWrite(DISPLAYBC, HIGH);
  } else if (scoreB == 7) {
    digitalWrite(DISPLAYBG, LOW);
    digitalWrite(DISPLAYBF, HIGH);
    digitalWrite(DISPLAYBA, HIGH);
    digitalWrite(DISPLAYBB, HIGH);
    digitalWrite(DISPLAYBE, LOW);
    digitalWrite(DISPLAYBD, LOW);
    digitalWrite(DISPLAYBC, HIGH);
  } else if (scoreB == 8) {
    digitalWrite(DISPLAYBG, HIGH);
    digitalWrite(DISPLAYBF, HIGH);
    digitalWrite(DISPLAYBA, HIGH);
    digitalWrite(DISPLAYBB, HIGH);
    digitalWrite(DISPLAYBE, HIGH);
    digitalWrite(DISPLAYBD, HIGH);
    digitalWrite(DISPLAYBC, HIGH);
  } else if (scoreB == 9) {
    digitalWrite(DISPLAYBG, HIGH);
    digitalWrite(DISPLAYBF, HIGH);
    digitalWrite(DISPLAYBA, HIGH);
    digitalWrite(DISPLAYBB, HIGH);
    digitalWrite(DISPLAYBE, LOW);
    digitalWrite(DISPLAYBD, HIGH);
    digitalWrite(DISPLAYBC, HIGH);
  }
}

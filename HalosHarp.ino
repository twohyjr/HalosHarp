#include <LiquidCrystal.h>
#include "core/eeprom_store.h"
#include "core/constants.h"
#include "core/pin_assignment.h"
#include "controllers/display_controller.h"
#include "controllers/sound_controller.h"
#include "models/photocell.h"
#include "models/lazer.h"
#include "controllers/lazer_controller.h"
#include "controllers/random_controller.h"
#include "controllers/score_controller.h"

void setup() {
    // eeprom_read_string(1, name, 4);
    // eeprom_write_string(1, name);
    initializeDisplay();
    initializeSound();
    initializeRandomness();

}

void loop() {
    runGame();
    // delay(60);
}

int roundNumber = 0;
bool isGameOver = false;
int roundValues[1000];
int score = 0;
int gameSpeed = 200;
void runGame(){
    isGameOver = false;
    displayTop("Twohy Says");
    doTouchToStart();
    clearDisplay();
    playStartupSequence();
    initializeCountdown();
    while(!isGameOver){
        doNewRound();
        displayOutOfScore(score);
        playBackRounds();
        if(verifyUserInputSequence()){
            score++;
        }else{
            isGameOver = true;
            clearDisplay();
            bool isHigh = checkAndUpdateHighScoring(score);
            if(!isHigh){
                displayTop("Game Over");
                displayFinalScore();
                playTone(G, 128);
            }else{
                clearDisplay();
                loadNameSave();
            }
            allLazersOff();

        }
        delay(gameSpeed);
    }

}

void resetHighScore(){
    storeHighScore(0);
}

bool checkAndUpdateHighScoring(int newScore){
    int highScore = getHighScore();
    bool isHighScore = newScore > highScore;
    if(isHighScore){
        playTwohySaysHighScore(newScore);
        storeHighScore(newScore);
        displayHighScore();
    }
    return isHighScore;
}

void playStartupSequence(){
    int melody[] = {  A,  A,  A,  A,  A,   E,  C,  C,  A,  A, G, F };
    int beats[]  = { 16, 16, 16,  8,  8,  16, 32, 16, 16, 16, 8, 32 };
    int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.
    for (int i=0; i<MAX_COUNT; i++) {
        allLazersOff();
        int lazer = rand() % 3 + 1;
        lazerOn(lazer);
        tone_ = melody[i];
        beat = beats[i];
        playTone(tone_,beat);
        delayMicroseconds(pause);
    }
    allLazersOff();
}

void initializeCountdown(){
    delay(1000);
    allLazersOff();
    displayBottom(" 3");
    playTone(G,8);
    lazerOn(1);
    delay(1000);
    displayBottom(" 3   2");
    playTone(G,8);
    lazerOn(2);
    delay(1000);
    displayBottom(" 3   2   1");
    playTone(G,8);
    lazerOn(3);
    delay(1000);
    displayBottom(" 3   2   1   GO");
    playTone(A,36);
    allLazersOff();
    delay(300);
    clearDisplay();
    displayTop("Twohy Says");
}

void displayOutOfScore(int currentRound){
    int highScore = getHighScore();
    char str[15];
    sprintf(str, "Round: %d / %d", currentRound, highScore);
    displayBottom(str);
}

void doTouchToStart(){
    allLazersOn();
    clearDisplay();
    bool isStarted = false;
    while(!isStarted){
        clearDisplay();
        displayTop("Twohy Says");
        displayHighScore();
        if(getLazer(1).isOnQuick() || getLazer(2).isOnQuick() || getLazer(3).isOnQuick()){
            isStarted = true;
            resetGame();
        }
        delay(100);
    }
}

int timeShowingScore = 0;
void displayHighScore(){
    if(timeShowingScore <= 25){
        int highScore = getHighScore();
        char str[16];
        sprintf(str, "High Score: %d ", highScore);
        displayBottom(str);
    }
    if(timeShowingScore > 25){
        char name[4];
        eeprom_read_string(1, name, 4);
        char str[16];
        sprintf(str, "High Score: %s", name);
        displayBottom(str);
    }
    if(timeShowingScore >= 50){
        timeShowingScore = 0;
    }
    timeShowingScore++;
}

void resetGame(){
    clearDisplay();
    isGameOver = false;
    score = 0;
    roundNumber = 0;
}



void displayFinalScore(){
    char str[15];
    sprintf(str, "Final Score: %d ", score);
    displayBottom(str);
}

void displayRoundNumber(){
    char str[15];
    sprintf(str, "Round: %d ", roundNumber);
    displayBottom(str);
}

bool verifyUserInputSequence(){
    allLazersOn();
    bool doingGood = true;
    for(int i = 0; i < roundNumber; i++){
        int currentCorrectLazer = roundValues[i];
        int selection = getNextLazerLong();
        if(currentCorrectLazer != selection){
            return false;
        }
    }
    allLazersOff();
    return doingGood;
}

void doNewRound(){
    int nextNum = getRandomLazer();
    roundNumber++;
    roundValues[roundNumber - 1] = nextNum;
}

void playBackRounds(){

    for(int i = 0; i < roundNumber; i++){
        allLazersOff();
        delay(100);
        Lazer l = getLazer(roundValues[i]);
        lazerOn(roundValues[i]);
        l.doTone(32);
    }
}

int getNextLazerLong(){
    allLazersOn();
    int val = 0;
    while(val == 0){
        if(getLazer(1).isOnLong()){
            val = 1;
        }else if(getLazer(2).isOnLong()){
            val = 2;
        }else if(getLazer(3).isOnLong()){
            val = 3;
        }
    }
    getLazer(val).doTone(32);
    return val;
}

void playTwohySaysHighScore(int roundNumber){
    clearDisplay();
     displayBottom(" New High Score");
     int melody[] = {Bb, G, G, Bb, G, G, Bb, G, G, Bb, G, G, Bb, G, C, G, Bb, G, G, Bb, G, G, Bb, G, G, Bb, G, G, Bb, G, F, D, F, D, G, F, D, C, Bb, G, Bb, C, C1, C, Bb, F, D, Bb, G, F, D, C, Bb, D, C, Bb, G};
     int beats[] = {8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8, 8};
     int MAX_COUNT = sizeof(melody) / 2; // Melody length, for looping.
     for (int i=0; i<MAX_COUNT; i++) {
          allLazersOff();
            int lazer = rand() % 3 + 1;
            lazerOn(lazer);
            tone_ = melody[i];
            beat = beats[i];
            if(i >= MAX_COUNT/2){
                 char str[15];
                 clearDisplay();
                 sprintf(str, "New High: %d", roundNumber);
                 displayBottom(str);
            }
            displayTop("WOOHOO TOP SCORE!! ");
          //   duration = beat * tempo; // Set up timing

            playTone(tone_,beat);
            // A pause between notes...
            delayMicroseconds(pause);
     }
     clearDisplay();
}


int time = 0;
int currentLetter = 'A';
void loadNameSave(){
    allLazersOn();
     int nameIndex = 0;
     char* name = "AAA";
     lazerOn(2);
     delay(20);
     int count = 0;
     bool nameIsCreated = false;
     while(!nameIsCreated){
         int direction = -99;
         Lazer lazer1 = getLazer(1);
         Lazer lazer2 = getLazer(2);
         Lazer lazer3 = getLazer(3);

         if(lazer1.isOnLong()){
             playTone(C, 8);
             direction = -1; //Go back
         }else if(lazer2.isOnLong()){
             playTone(A, 20);
             direction = 0; //Select Option
         }if(lazer3.isOnLong()){
             playTone(C, 8);
             direction = 1; //Go Forward
         }
         char letter = "";
         if(direction > -2){
             letter = selectLetter(direction);
             currentLetter = letter;
             name[nameIndex] = currentLetter;
             if(direction == 0){
                  nameIndex++;
             }
             if(nameIndex == 3){
                 nameIsCreated = true;
             }
         }
         if(time <= 4){
             name[nameIndex] = currentLetter;
         }else if(time >= 7){
             name[nameIndex] = ' ';
         }
         if(time >= 11){
             time = 0;
         }
         time++;

         displayTop("Enter Initials");
         char display[16];
         sprintf(display, "%s", name);
         displayBottom(display);

          if(nameIsCreated){
               eeprom_write_string(1, name);
          }else{
              delay(60);
          }

     }
}

int currentLetterIndex = 0;
char selectLetter(int direction){
     char letters[] = {'A','B','C','D','E','F','G','H','I','J','K','L','M','N','O','P','Q','R','S','T','U','V','W','X','Y','Z','1','2','3','4','5','6','7','8','9'};
     int totalChars = sizeof(letters);

     currentLetterIndex += direction;
     if(currentLetterIndex <= -1){
         currentLetterIndex = totalChars-1;
     }else if(currentLetterIndex >= totalChars-1){
         currentLetterIndex = 0;
     }
     char letter = letters[currentLetterIndex];
     char myStg[10];
     sprintf(myStg, "%c", letter);
     return myStg[0];
}

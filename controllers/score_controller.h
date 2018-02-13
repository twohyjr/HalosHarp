
long highScore = 0;

void initializeScoreKeeper(){
     highScore = EEPROM.read(0);
}

void storeHighScore(int score){
     EEPROM.write(0, score);
     highScore = EEPROM.read(0);
}

long getHighScore(){
     highScore = EEPROM.read(0);
     return highScore;
}

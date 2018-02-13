void clearDisplay();

LiquidCrystal lcd(rs, en, d4, d5, d6, d7);

void initializeDisplay(){
    lcd.begin(16, 2);
    clearDisplay();
}

//#####################################################
//------ Instatiate Methods Here -----
void clearDisplay();
//#####################################################
void displayTop(String text){
    int blankSpaces = 16 - text.length();
    blankSpaces = blankSpaces >= 0 ? ceil(blankSpaces / 2) : 0;
    lcd.setCursor(blankSpaces,0);
    lcd.print(text);
}

void displayTop(int text){
    lcd.setCursor(0,0);
    lcd.print(text);
}

void displayBottom(int text){
    lcd.setCursor(0,1);
    lcd.print(text);
}

void displayBottom(String text){
    int blankSpaces = 16 - text.length();
    blankSpaces = blankSpaces >= 0 ? ceil(blankSpaces / 2) : 0;
    lcd.setCursor(blankSpaces,1);
    lcd.print(text);
}

void clearDisplay(){
     lcd.clear();
}

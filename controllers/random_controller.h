void initializeRandomness(){
    randomSeed(analogRead(20));
}

int getRandomLazer(){
    return random(1, 4);
}

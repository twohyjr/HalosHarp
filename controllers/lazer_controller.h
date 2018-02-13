

void lazerOn(int lazerNumber);

Lazer lazers[3] = {Lazer(lazer1, photocell1, A), Lazer(lazer2, photocell2, B), Lazer(lazer3, photocell3, C)};

void allLazersOn(){
     for(int i = 0; i < sizeof(lazers); i++){
          lazers[i].turnOn();
     }
}

void allLazersOff(){
    for(int i = 0; i < sizeof(lazers); i++){
         lazers[i].turnOff();
    }
}

void lazerOn(int lazerNumber){
    lazers[lazerNumber - 1].turnOn();
}

void lazerOff(int lazerNumber){
    lazers[lazerNumber - 1].turnOff();
}

Lazer getLazer(int lazerNumber){
    return lazers[lazerNumber - 1];
}

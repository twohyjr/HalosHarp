bool soundOn = true;

int tone_ = 0;
int beat = 0;
long duration  = 0;

long tempo = 10000;
// Set length of pause between notes
int pause = 10000;
// Loop variable to increase Rest length
int rest_count = 100;

#define C    1911
#define C1    1804
#define D    1703
#define Eb    1607
#define E    1517
#define F    1432
#define F1    1352
#define G    1276
#define Ab    1204
#define A    1136
#define Bb    1073
#define B    1012
#define c       955
#define c1      902
#define d       851
#define eb      803
#define e       758
#define f       716
#define f1      676
#define g       638
#define ab      602
#define a       568
#define bb      536
#define b       506

#define   R         0        //0hz           //Rest

void initializeSound(){
    pinMode(speakerOut, OUTPUT);
}

void playTone(int note,long dur) {

            dur = dur * tempo;
            long elapsed_time = 0;
            if (note > 0) { // if this isn't a Rest beat, while the tone has
              //  played less long than 'duration', pulse speaker HIGH and LOW
              while (elapsed_time < dur) {
if(soundOn){
                digitalWrite(speakerOut,HIGH);
}
                delayMicroseconds(note / 2);
                if(soundOn){
                digitalWrite(speakerOut, LOW);
            }
                delayMicroseconds(note / 2);

                // Keep track of how long we pulsed
                elapsed_time += (note);
              }
            }
            else { // Rest beat; loop times delay
              for (int j = 0; j < 100; j++) { // See NOTE on rest_count
                delayMicroseconds(dur);
              }
            }


}


class Lazer{
    public:
        Lazer(int lazerPin, int photocellPin, int tone);
    private:
        int m_LazerPin;
        Photocell *m_Photocell;
        bool m_IsOn;
        int m_Tone;
    public:
        void turnOn();
        void turnOff();
        bool isOnQuick();
        bool isOnLong();
        void doTone(int count);
    private:
        void activatePinMode();
};

Lazer::Lazer(int lazerPin, int photocellPin, int tone){
    this->m_Photocell = new Photocell(photocellPin);
    this->m_LazerPin = lazerPin;
    this->m_Tone = tone;
    this->activatePinMode();
}
void Lazer::activatePinMode(){
    pinMode(m_LazerPin, OUTPUT);
}
void Lazer::turnOn(){
    digitalWrite(m_LazerPin, HIGH);
}
void Lazer::turnOff(){
    digitalWrite(m_LazerPin, LOW);
}

bool Lazer::isOnQuick(){
    m_IsOn = m_Photocell->getValue() > photocellThreshold;
    return m_IsOn;
}

bool Lazer::isOnLong(){
    bool photocell1IsActive = false;
    bool isActive = false;
    int photocellReading1 = m_Photocell->getValue();
    if(photocellReading1 > photocellThreshold){
         photocell1IsActive = true;
    }
    delay(10);
    while(photocell1IsActive){
         photocellReading1 = m_Photocell->getValue();
         if(photocellReading1 < photocellThreshold){
              photocell1IsActive = true;
              return true;
         }
    }
    return false;
}

void Lazer::doTone(int count){
    playTone(m_Tone, count);
}

// bool isOn(){
//     if(photocell(lazerPin).get)
// }

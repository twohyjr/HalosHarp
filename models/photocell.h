
class Photocell{
    public:
        Photocell(int photocellPin);
    public:
        int getValue();
    private:
        int m_photocellPin;
    private:
        void activatePinMode();
};

Photocell::Photocell(int photocellPin){
    this->m_photocellPin = photocellPin;
    activatePinMode();
}

int Photocell::getValue(){
    return analogRead(m_photocellPin);
}

void Photocell::activatePinMode(){
    pinMode(m_photocellPin, INPUT_PULLUP);
}

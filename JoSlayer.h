#ifndef JOSLAYER_H
#define JOSLAYER_H
class JoSlayer {
    private:
        bool debug = false;
        int countExacute = 0;
        int somkeDetection = 0;
        int motor1Pin1 = 0;
        int motor1Pin2 = 0;
        int motor2Pin1 = 0;
        int motor2Pin2 = 0;
        void lockDoor() ;
        void unLockDoor();
        void waterShowerOn() ;
        void waterShowerOff() ;
        void sandLine();
        void killJo() ;
        void stop();
 
    public:
        JoSlayer();
       void Begin(bool debug,int motor1Pin,int motor1Pin2,int motor2Pin1,int motor2Pin2);
        void SomkeDetect();

};

extern JoSlayer JO;

#endif
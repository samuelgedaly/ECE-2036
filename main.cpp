// code must be added by students
#include <stdio.h>      /* printf */
#include <math.h>
#include <vector>
//#include "SDFileSystem.h"
#include "mbed.h"
//#include "wave_player.h"
//#include "SDFileSystem.h"
//#include "TMP36.h"
#include "uLCD_4DGL.h"
#include "PinDetect.h"
#include "lame.h"
#include "Speaker.h"

//#include "Speaker.h"
// must add your new class code to the project file Shiftbrite.h
//#include "Shiftbrite.h"
#define WHITE   0xFFFFFF
#define BLACK   0x000000
#define RED         0xFF0000
#define GREEN   0x00FF00
#define BLUE        0x0000FF
#define LGREY   0xBFBFBF
#define DGREY   0x5F5F5F
//SDFileSystem sd(p5, p6, p7, p8, "sd");
uLCD_4DGL uLCd(p9, p10, p11); // create a global lcd object
DigitalIn left_pb(p23);
DigitalIn right_pb(p22);
DigitalIn shoot_pb(p24);
//SDFileSystem sd(p5, p6, p7, p8, "sd");
Speaker mySpeaker(p21);

DigitalOut myled(LED1);
//AnalogOut DACout(p21);      // speaker
//wave_player waver(&DACout);



int main() {
srand(time(NULL));
left_pb.mode(PullUp);  // The variable left_pb will be zero when the pushbutton for moving the player left is pressed    
right_pb.mode(PullUp);
shoot_pb.mode(PullUp);
time_t startTime;
startTime = time(0);
int num_aliens = 6;
std::vector<ScreenAliens *> vec(num_aliens);
int initial_y[6] = {10,25,40,55,70,85};//array that will contain 6 different y positions
SpaceShip sh;
Bullet b;
bool bullet_moving = false;
int distX;
int distY;

for (int i = 0; i < 6; i++) {
        int r = rand()%4;
        if(r == 0) {
             vec[i] = new AlienBob();
        }else if(r == 1){
            vec[i] = new AlienAlice();
        } else if(r == 2) {
            vec[i] = new AlienSam();
        } else {
            vec[i] = new AlienGedaly();
        }
        vec[i]->setX(rand()%100 + 10);
        vec[i]->setY(initial_y[i]);
        vec[i]->setDirection(true);
        vec[i]->draw();
    }
    sh.draw();
    
    //playSound("/sd/wavfiles/pacman_beginning.wav");//sounds
    
while(num_aliens > 0){
    for(int i = 0; i < vec.size(); i++) {
        vec[i]->update();
        distX = b.getX() - vec[i]->getX();
        distY = b.getY() - vec[i]->getY();
        if (distX < 11 && distX >= 0 && distY < 8 && distY >= 0) {
            uLCd.filled_rectangle(b.getX(), b.getY(), b.getX() + 3, b.getY() + 5, BLACK);
            uLCd.filled_rectangle(vec[i]->getX(), vec[i]->getY(), vec[i]->getX() + 11, vec[i]->getY() + 8, BLACK);
            bullet_moving = false;
            vec.erase (vec.begin()+i);
            num_aliens--;
            mySpeaker.PlayNote(400.0,0.25,0.1);
        }
    }
    if (!left_pb.read()) {
        sh.move(false);
    }else if(!right_pb.read()) {
        sh.move(true);
    }
    if(b.getY() <= 0) {
        bullet_moving = false;
    }
    if (!shoot_pb.read() && !bullet_moving) {
        b.draw(sh.getX() + 8);
        bullet_moving = true;
        mySpeaker.PlayNote(200.0,0.25,0.1);  
    }
    if (b.getX() < 0) {
        bullet_moving = false;
    }
    if (bullet_moving) {
        b.move();
    }
    
}
//double tick = timer.read_ms();
time_t endTime = time(0)-startTime;

uLCd.printf("\n\n Congratulations!!\n\n Earth Saved!\n\n\n (%d Seconds)",
endTime);
}


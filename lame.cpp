#include <stdio.h> 
#include "lame.h"
#include "uLCD_4DGL.h"

using namespace std;
#define ALIEN_HEIGHT 8
#define ALIEN_WIDTH 11
#define _ 0x000000 //BLACK
#define X 0xFFFFFF //WHITE

uLCD_4DGL uLCD(p9, p10, p11); 

int alienBobDown_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
     _,_,X,_,_,_,_,_,X,_,_,
     _,_,_,X,_,_,_,X,_,_,_,
     _,_,X,X,X,X,X,X,X,_,_,
     _,X,X,_,X,X,X,_,X,X,_,
     X,X,X,X,X,X,X,X,X,X,X,
     X,_,X,X,X,X,X,X,X,_,X,
     X,_,X,_,_,_,_,_,X,_,X,
     _,_,_,X,X,_,X,X,_,_,_,
    };
int alienBobUp_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
     _,_,X,_,_,_,_,_,X,_,_,
     X,_,_,X,_,_,_,X,_,_,X,
     X,_,X,X,X,X,X,X,X,_,X,
     X,X,X,_,X,X,X,_,X,X,X,
     X,X,X,X,X,X,X,X,X,X,X,
     _,_,X,X,X,X,X,X,X,_,_,
     _,_,X,_,_,_,_,_,X,_,_,
     _,X,_,_,_,_,_,_,_,X,_,
    };
int alienAlice_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
     _,_,_,_,X,X,X,_,_,_,_,
     _,X,X,X,X,X,X,X,X,X,_,
     X,X,X,X,X,X,X,X,X,X,X,
     X,X,X,_,_,X,_,_,X,X,X,
     X,X,X,X,X,X,X,X,X,X,X,
     _,_,_,X,X,_,X,X,_,_,_,
     _,_,X,X,_,_,_,X,X,_,_,
     X,X,_,_,_,X,_,_,_,X,X,
    };
    
int spaceShip_sprite[20 * 4] = {
     X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
     X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
     X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
     X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,X,
    };
int bullet_sprite[3*5] = {
    X,X,X,
    X,X,X,
    X,X,X,
    X,X,X,
    X,X,X,
};
int alienSam_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
     X,X,X,X,X,X,X,X,X,X,X,
     X,X,X,X,_,_,_,X,X,X,X,
     X,X,X,_,X,_,X,_,X,X,X,
     X,X,X,X,_,_,_,X,X,X,X,
     X,X,X,X,X,X,X,X,X,X,X,
     X,X,X,_,_,_,_,_,X,X,X,
     X,X,X,X,_,_,_,X,X,X,X,
     X,X,X,X,X,X,X,X,X,X,X,
};
int alienGedaly_sprite[ALIEN_HEIGHT * ALIEN_WIDTH] = {
     _,_,_,X,X,X,X,X,_,_,_,
     _,_,X,X,_,_,_,X,X,_,_,
     _,X,X,_,X,_,X,_,X,X,_,
     _,X,X,X,_,_,_,X,X,X,_,
     X,_,X,X,X,X,X,X,X,_,X,
     _,X,_,_,_,_,_,_,_,X,_,
     _,_,X,X,_,_,_,X,X,_,_,
     _,_,_,X,X,X,X,X,_,_,_,
};
void ScreenAliens::draw(){}
void ScreenAliens::update(){}
int ScreenAliens::getX(){
    return this->x_pos;    
}
int ScreenAliens::getY(){
    return this->y_pos;    
}
bool ScreenAliens::getDirection(){
    return this->direction;    
}
void ScreenAliens::setX(int x) {
    this->x_pos = x;
}
void ScreenAliens::setY(int y) {
    this->y_pos = y;
}
void ScreenAliens::setDirection(bool d) {
    this->direction = d;
}


void AlienBob::draw() { //I should update the x and y positions and then call this function
    uLCD.BLIT(this->x_pos, this->y_pos, ALIEN_WIDTH, ALIEN_HEIGHT, alienBobUp_sprite);
    this->arms_pos = false;
}
 void AlienBob::update() { //I should update the x and y positions
// and then call this function and see if it is a valid position or it should move to the other side
    //uLCD.BLIT(this->x_pos, this->y_pos, ALIEN_WIDTH, ALIEN_HEIGHT, alien_clear);
    uLCD.filled_rectangle(this->x_pos, this->y_pos, this->x_pos + ALIEN_WIDTH, this->y_pos + ALIEN_HEIGHT, BLACK);
    if (this->x_pos > 80) {
        this->direction = false;
    } else if (this->x_pos < 10) {
        this->direction = true;
    }
    if (this->direction) {
        this->x_pos += 6; 
    } else {
        this->x_pos -= 6;
    }
    if (this->arms_pos) {
        uLCD.BLIT(this->x_pos, this->y_pos, ALIEN_WIDTH, ALIEN_HEIGHT, alienBobUp_sprite);
        this->arms_pos = false;
    }else {
        uLCD.BLIT(this->x_pos, this->y_pos, ALIEN_WIDTH, ALIEN_HEIGHT, alienBobDown_sprite);
        this->arms_pos = true;
    }
}

void AlienAlice::draw() { //I should update the x and y positions and then call this function
    //this->x_pos = rand()%69 + 16;
    //this->y_pos = (rand()%6)*10 + 15;
    uLCD.BLIT(this->x_pos, this->y_pos, ALIEN_WIDTH, ALIEN_HEIGHT, alienAlice_sprite);
}
void AlienAlice::update() { //I should update the x and y positions
// and then call this function and see if it is a valid position or it should move to the other side
    //uLCD.BLIT(this->x_pos, this->y_pos, ALIEN_WIDTH, ALIEN_HEIGHT, alien_clear);
    uLCD.filled_rectangle(this->x_pos, this->y_pos, this->x_pos + ALIEN_WIDTH, this->y_pos + ALIEN_HEIGHT, BLACK);
    if (this->x_pos > 100) {
        this->direction = false;
    } else if (this->x_pos < 10) {
        this->direction = true;
    }
    if (this->direction) {
        this->x_pos += 6; 
    } else {
        this->x_pos -= 6;
    }
    uLCD.BLIT(this->x_pos, this->y_pos, ALIEN_WIDTH, ALIEN_HEIGHT, alienAlice_sprite);
}
void AlienSam::draw() { //I should update the x and y positions and then call this function
    //this->x_pos = rand()%69 + 16;
    //this->y_pos = (rand()%6)*10 + 15;
    uLCD.BLIT(this->x_pos, this->y_pos, ALIEN_WIDTH, ALIEN_HEIGHT, alienSam_sprite);
}
void AlienSam::update() { //I should update the x and y positions
// and then call this function and see if it is a valid position or it should move to the other side
    //uLCD.BLIT(this->x_pos, this->y_pos, ALIEN_WIDTH, ALIEN_HEIGHT, alien_clear);
    uLCD.filled_rectangle(this->x_pos, this->y_pos, this->x_pos + ALIEN_WIDTH, this->y_pos + ALIEN_HEIGHT, BLACK);
    if (this->x_pos > 100) {
        this->direction = false;
    } else if (this->x_pos < 10) {
        this->direction = true;
    }
    if (this->direction) {
        this->x_pos += 6; 
    } else {
        this->x_pos -= 6;
    }
    uLCD.BLIT(this->x_pos, this->y_pos, ALIEN_WIDTH, ALIEN_HEIGHT, alienSam_sprite);
}
void AlienGedaly::draw() { //I should update the x and y positions and then call this function
    //this->x_pos = rand()%69 + 16;
    //this->y_pos = (rand()%6)*10 + 15;
    uLCD.BLIT(this->x_pos, this->y_pos, ALIEN_WIDTH, ALIEN_HEIGHT, alienGedaly_sprite);
}
void AlienGedaly::update() { //I should update the x and y positions
// and then call this function and see if it is a valid position or it should move to the other side
    //uLCD.BLIT(this->x_pos, this->y_pos, ALIEN_WIDTH, ALIEN_HEIGHT, alien_clear);
    uLCD.filled_rectangle(this->x_pos, this->y_pos, this->x_pos + ALIEN_WIDTH, this->y_pos + ALIEN_HEIGHT, BLACK);
    if (this->x_pos > 100) {
        this->direction = false;
    } else if (this->x_pos < 10) {
        this->direction = true;
    }
    if (this->direction) {
        this->x_pos += 6; 
    } else {
        this->x_pos -= 6;
    }
    uLCD.BLIT(this->x_pos, this->y_pos, ALIEN_WIDTH, ALIEN_HEIGHT, alienGedaly_sprite);
}
void SpaceShip::draw() {
    uLCD.BLIT(54, 117, 20, 4, spaceShip_sprite);
    this->x_pos = 54;
}
void SpaceShip::move(bool direc) { //right is true and left is false
    //uLCD.BLIT(this->x_pos, 117, 20, 4, spaceship_clear);
    uLCD.filled_rectangle(this->x_pos, 117, this->x_pos + 20, 117 + 4, BLACK);
    if(direc){
       this->x_pos += 6;
    } else {
        this->x_pos -= 6;     
    }
    if (this->x_pos < 0) {
        this->x_pos = 0;
    } else if (this->x_pos > 108) {
        this->x_pos = 108;
    }
    uLCD.BLIT(this->x_pos, 117, 20, 4, spaceShip_sprite);
}
int SpaceShip::getX() {
    return this->x_pos;
}
void Bullet::draw(int x) {
    //uLCD.BLIT(this->x_pos, 110, 3, 5, bullet_clear);
    uLCD.filled_rectangle(this->x_pos, this->y_pos, this->x_pos + 3, this->y_pos + 5, BLACK);
    uLCD.BLIT(x, 110, 3, 5, bullet_sprite);
    this->x_pos = x;
    this->y_pos = 110;
}
void Bullet::move(){
    if (this->y_pos > 0){
        uLCD.filled_rectangle(this->x_pos, this->y_pos, this->x_pos + 3, this->y_pos + 5, BLACK);
    }
    this->y_pos -= 4;
    if (this->y_pos > 0) {
        uLCD.BLIT(this->x_pos, y_pos, 3, 5, bullet_sprite);
    }
}
int Bullet::getX() {
    return this->x_pos;
}
int Bullet::getY() {
    return this->y_pos;
}

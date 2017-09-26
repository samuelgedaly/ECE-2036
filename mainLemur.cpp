// skeleton code for ECE 2036 thermostat lab
// code must be added by students
#include <stdio.h>      /* printf */
#include <math.h>
#include "SDFileSystem.h"
#include "mbed.h"
#include "TMP36.h"
#include "uLCD_4DGL.h"
#include "PinDetect.h"

#include "Speaker.h"
// must add your new class code to the project file Shiftbrite.h
#include "Shiftbrite.h"
#define WHITE   0xFFFFFF
#define BLACK   0x000000
#define RED         0xFF0000
#define GREEN   0x00FF00
#define BLUE        0x0000FF
#define LGREY   0xBFBFBF
#define DGREY   0x5F5F5F
SDFileSystem sd(p5, p6, p7, p8, "sd");
uLCD_4DGL uLCD(p9, p10, p11); // create a global lcd object
DigitalIn left_pb(p23);
DigitalIn right_pb(p22);
DigitalIn exit_pb(p24);

int main(){
    left_pb.mode(PullUp);  // The variable left_pb will be zero when the pushbutton for moving the player left is pressed    
    right_pb.mode(PullUp);
    exit_pb.mode(PullUp);  // The variable left_pb will be zero when the pushbutton for moving the player left is pressed    
    //wait(0.1);
    
    srand(time(NULL));
    Timer timer;
    timer.start();
    double tick = timer.read_ms();
    double pretick = tick;
    uLCD.printf("\nWelcome to the Lemur Training\n");
    while(pretick - tick <= 2000) {
        pretick = timer.read_ms();
    }
    uLCD.cls();
    bool start = true;
    int trial = 1;
    int r;
    int r2;
    int correct_trial = 0;
    
    mkdir("/sd/mydir", 0777); // set up directory and permissions
    FILE *fp = fopen("/sd/mydir/LResults.txt", "w"); //open SD
    fprintf(fp,"Hello Lemur\n");
    if(fp == NULL) {
        uLCD.printf("Could not open file for write\n");
        wait(2.0);
    }
 
    
    while(exit_pb.read()){
        uLCD.cls();
        if (start){
            uLCD.rectangle(62, 122, 2, 2, WHITE);
            uLCD.rectangle(126, 122, 64, 2, WHITE);
             r = rand()%15 + 1;
            int ra;
            int arr[14];
            for (int i = 0; i < r; i++) {
                 bool check;
                 
                 do{
                     ra = rand()%18 + 1;
                     check = true;
                     for(int j = 0; j < i; j++) {
                         if (arr[j] == ra){ 
                           check = false;
                           break;
                        }
                    }
                    
                 }while(!check);
                 arr[i] = ra;
                 
                 int x_pos = ra % 3;
                 int y_pos = (int)ceil((float)ra/3);
                 if (x_pos == 0) {
                    x_pos = 3;
                 }
                 int radius = rand()%10 + 1; 
                 int random_shape2 = rand()%3 + 1;
                 if(random_shape2 == 1){
                     uLCD.circle(20*x_pos - 10 + 2, 20*y_pos - 10 + 2, radius, WHITE);
                 } else if (random_shape2 == 2) {
                     uLCD.triangle(20*x_pos - 10 + 2, 20*y_pos - 10 + 2 - radius, 20*x_pos - 10 + 2 - (int)(ceil(radius/1.41)), 20*y_pos - 10 + 2 + (int)(ceil(radius/1.41)), 20*x_pos - 10 + 2 + (int)(ceil(radius/1.41)), 20*y_pos - 10 + 2 + (int)(ceil(radius/1.41)), WHITE);
                 }else {
                     uLCD.rectangle(20*x_pos - 10 + 2 + (int)(ceil(radius/1.41)), 20*y_pos - 10 + 2 + (int)(ceil(radius/1.41)), 20*x_pos - 10 + 2 - (int)(ceil(radius/1.41)), 20*y_pos - 10 + 2 - (int)(ceil(radius/1.41)), WHITE);
                 }
                 
                 
                 
                 
            }
            
            r2 = rand()%15 + 1;
            while(r2 == r) {
                r2 = rand()%15 + 1;
            }
            int arr2[14];
            for (int i = 0; i < r2; i++) {
                 bool check;
                 
                 do{
                     ra = rand()%18 + 1;
                     check = true;
                     for(int j = 0; j < i; j++) {
                         if (arr2[j] == ra){ 
                           check = false;
                           break;
                        }
                    }
                    
                 }while(!check);
                 arr2[i] = ra;
                 int x_pos = ra % 3;
                 int y_pos = (int)ceil((float)ra/3);
                 if (x_pos == 0) {
                    x_pos = 3;
                 }
                 int radius = rand()%10 + 1; 
                 int random_shape2 = rand()%3 + 1;
                 if(random_shape2 == 1){
                     uLCD.circle(20*x_pos - 10 + 2 + 62, 20*y_pos - 10 + 2, radius, WHITE);
                 } else if (random_shape2 == 2) {
                     uLCD.triangle(20*x_pos - 10 + 2 + 62, 20*y_pos - 10 + 2 - radius, 20*x_pos - 10 + 2 + 62 - (int)(ceil(radius/1.41)), 20*y_pos - 10 + 2 + (int)(ceil(radius/1.41)), 20*x_pos - 10 + 2 + 62 + (int)(ceil(radius/1.41)), 20*y_pos - 10 + 2 + (int)(ceil(radius/1.41)), WHITE);
                 }else {
                     uLCD.rectangle(20*x_pos - 10 + 2 + 62 + (int)(ceil(radius/1.41)), 20*y_pos - 10 + 2 + (int)(ceil(radius/1.41)), 20*x_pos - 10 + 2 + 62 - (int)(ceil(radius/1.41)), 20*y_pos - 10 + 2 - (int)(ceil(radius/1.41)), WHITE);
                 }
                 
                 
                 
            }
            
        }
        tick = timer.read_ms();
    
        bool next = true;
        bool correct = false;
        while(next) {
            if (!left_pb.read() || !right_pb.read() || !exit_pb.read()){
                next = false;
                pretick = timer.read_ms() - tick;
                if (!((!left_pb.read() && r > r2) || (!right_pb.read() && r < r2))) {
                    correct = true;
                    correct_trial++;
                }
                if (!exit_pb.read()) {
                    start = false;
                    
                }    
            }
        }
         uLCD.cls();
        fprintf(fp, "Hello SD Card World!"); // write SD
         
         
        if(start){
            if(correct) {
                uLCD.printf("\nYou are CORRECT lemur!\n");
                fprintf(fp, "\nYou are CORRECT lemur!\n");
            } else {
                uLCD.printf("\nYou are INCORRECT lemur... sorry\n");
                fprintf(fp, "\nYou are INCORRECT lemur... sorry\n");
            }
            uLCD.printf("\nTrial number: %d\n", trial);
            fprintf(fp, "\nTrial number: %d\n", trial);
            uLCD.printf("\nAccuracy: %.1f\n", (double)correct_trial/trial);
            fprintf(fp, "\nAccuracy: %.1f\n", (double)correct_trial/trial);
            uLCD.printf("\nLemur time: %.1f\n", pretick);
            fprintf(fp, "\nLemur time: %.1f\n", pretick);
            trial++;
             
            tick = timer.read_ms();
            pretick = tick;
            while(pretick - tick <= 100) {
                pretick = timer.read_ms();
            }
        }
        
    }
    fclose(fp);
    uLCD.cls();
    uLCD.printf("\nYOU JUST EXIT THE GAME\n");
}




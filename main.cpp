#include "mbed.h"
#include "TextLCD.h"

TextLCD lcd(D5, D6, D7, D8, D9, D10);
Ticker ticker;
DigitalOut led1(D2);
PwmOut buzzer(D3);
InterruptIn incrementButton(D13);
InterruptIn decrementButton(D12);
InterruptIn concertABut(D4);    
volatile float beat_rate = 100.0;
float G_note = 0.00255754475;
float concertA_note = 0.00227272727;
bool g_note = true;


void oneTick() {
    buzzer = 0.5f;
    led1 = 1;
    wait(.1);
    buzzer = 0;
    led1 = 0;
}
void incrementButPress(){
    if (beat_rate < 208){
        beat_rate += 4.0;
        ticker.detach();
        ticker.attach(&oneTick, (60/beat_rate));
        }
}
void decrementButPress(){
    if (beat_rate > 40){
        beat_rate -= 4.0;
        ticker.detach();
        ticker.attach(&oneTick, (60/beat_rate));
        }
}
void changeNoteButPress(){
    if (g_note){
        buzzer.period(concertA_note);
        g_note = false;
    }else{
        buzzer.period(G_note);
        g_note = true;
    }
}

int main() {
    buzzer.period(G_note);
    buzzer = 0;
    led1 = 0;
    ticker.attach(&oneTick, (60/beat_rate));
    incrementButton.fall(&incrementButPress);
    decrementButton.fall(&decrementButPress);
    concertABut.fall(&changeNoteButPress);
    while(1){
        lcd.printf("Bpm is %f\n\n\n", beat_rate);
   }
}

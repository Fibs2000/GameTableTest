
#include "Rainbow.h"
#include "MegaMaze.h"
#include "Tetris.h"
#include "Snake.h"
#include "ConnectFour.h"

////***********************  MATRIX
#include "Adafruit_GFX.h" // Core graphics library
#include "RGBmatrixPanel.h" // Hardware-specific library

#define CLK 12  // MUST be on PORTB!
#define LAT A3
#define OE  9
#define A   A0
#define B   A1
#define C   A2
RGBmatrixPanel myMatrix(A, B, C, CLK, LAT, OE, false);

char   str1[]   = "GAME";
char   str2[]   = "table";
char   str3[]   = "tetris";
char   str4[]   = "MAZE";
char   str5[]   = "Snake";
char   str6[]   = "4WINS";
char   str7[]   = "Color";
long   hue     = 0;


// **********************   MATRIX end

#include "stdint.h"
#include "pitches.h"



// Melodien:

// notes in the melody:
int melody1[] = {
 // NOTE_C4, NOTE_CS4,NOTE_D4, NOTE_DS4, NOTE_E4, NOTE_F4, NOTE_C4, NOTE_C5, NOTE_A6
 NOTE_E5, NOTE_E3, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_E5, NOTE_D5, NOTE_C5, 
  NOTE_B4, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_C5, NOTE_E5, NOTE_A3, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_G4, NOTE_C5, NOTE_D5, NOTE_E3, NOTE_E5,
  NOTE_E3, NOTE_C5, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_A4, NOTE_A3, NOTE_B2, 
  NOTE_C3, NOTE_D3, NOTE_D5, NOTE_F5, NOTE_A5, NOTE_C5, NOTE_C5, NOTE_G5, 
  NOTE_F5, NOTE_E5, NOTE_C3, 0, NOTE_C5, NOTE_E5, NOTE_A4, NOTE_G4, NOTE_D5,
  NOTE_C5, NOTE_B4, NOTE_E4, NOTE_B4, NOTE_C5, NOTE_D5, NOTE_G4, NOTE_E5, 
  NOTE_G4, NOTE_C5, NOTE_E4, NOTE_A4, NOTE_E3, NOTE_A4, 0,
 
 };

// note durations: 4 = quarter note, 8 = eighth note, etc.:
int noteDurations1[] = {
  //32,32,32,32,32,32,16,8,8 
8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,8,
  8,4,8,8,16,16,8,8,8,8,8,8,8,16,16,8,8,8,8,8,8,8,8,8,8,8,8,8,8,4,4,


};



const int controllerLatchPin = 14; // set the controller latch pin - Orange
const int controllerClockPin = 15; // set the controller clock pin - Red
const int controllerDataPin = 16; // set the controller data in pin - Yellow
const int pixelsDataPin = 10; // Yellow wire on Adafruit Pixels
const int pixelsClockPin = 11; // Green wire on Adafruit Pixels


Adafruit_WS2801 *strip;
NESController *controller;

int curGame=0;
int displayedGame=0;
Game *currentGame = NULL;
bool paused = true;
String gameNames[] = {"Tetris","Mega Maze","Snake","Connect Four","Rainbow"};

int main(void) {
	init();
	setup();
	while (true) {
		loop();
	}
}

//******************************************************  SETUP  ***

// The setup() method runs once, when the sketch starts
void setup() {
	// Set the first variable to the NUMBER of pixels. 25 = 25 pixels in a row
	strip = new Adafruit_WS2801(10,20, pixelsDataPin, pixelsClockPin,0);
	controller = new NESController(controllerLatchPin,controllerClockPin,controllerDataPin);
	
	pinMode(controllerLatchPin, OUTPUT);
	pinMode(controllerClockPin, OUTPUT);
	pinMode(controllerDataPin, INPUT);
	digitalWrite(controllerLatchPin, HIGH);
	digitalWrite(controllerClockPin, HIGH);
	strip->begin();
	strip->show();
	
// *** MATRIX ***

  myMatrix.begin();
  myMatrix.setTextWrap(false); // Allow text to run off right edge
  myMatrix.setTextSize(1);
  myMatrix.fillScreen(0);   //CLEAR
  
  myMatrix.drawRect(0, 0, 32, 16, myMatrix.Color333(7, 7, 0));
  myMatrix.setCursor(5, 1);
  myMatrix.setTextColor(myMatrix.Color333(1,5,0));
  myMatrix.print(str1);
  delay(200);
  myMatrix.setCursor(2, 8);
   myMatrix.setTextColor(myMatrix.Color333(2,0,7));
  myMatrix.print(str2);    

for (int thisNote = 0; thisNote < 64; thisNote++) {

    int noteDuration1 = 2000/noteDurations1[thisNote];
    tone(8, melody1[thisNote],noteDuration1);
    int pauseBetweenNotes = noteDuration1 * 0.70;
    delay(pauseBetweenNotes);
    noTone(8);
    int randX;
    int randY;
   
    int randR;int randG;int randB;
    
    randX = random(10);
    randY = random(20);
    randR = random(0,255);
    randG = random(0,255);
    randB = random(0,255);
    strip->setPixelColor(randX, randY ,randR,randG,randB);
    strip->show();
  }

}

void loop() {
	controller->controllerRead();
	if(paused && controller->buttonPressed(controller->BUTTON_LEFT) &&
			!controller->buttonHandled(controller->BUTTON_LEFT)){
		controller->handleButton(controller->BUTTON_LEFT);
	
                  
		if(displayedGame==0){
			displayedGame = (sizeof(gameNames)/sizeof(String)) - 1;
		}else{
			displayedGame=(displayedGame-1)%(sizeof(gameNames)/sizeof(String));
		}
               /*   myMatrix.fillScreen(0);   //CLEAR
                 myMatrix.setCursor(5, 5);
                   myMatrix.setTextColor(myMatrix.Color333(1,1,4));
                  myMatrix.print(displayedGame);
                 
                  */
                    
	}
	if(paused && controller->buttonPressed(controller->BUTTON_RIGHT) &&
			!controller->buttonHandled(controller->BUTTON_RIGHT)){
		controller->handleButton(controller->BUTTON_RIGHT);
		
		displayedGame=(displayedGame+1)%(sizeof(gameNames)/sizeof(String));

             /*     myMatrix.fillScreen(0);   //CLEAR
                 myMatrix.setCursor(5, 5);
                   myMatrix.setTextColor(myMatrix.Color333(1,4,1));
                  myMatrix.print(displayedGame);
            */
		
	}
	if(controller->buttonPressed(controller->BUTTON_START) && !controller->buttonHandled(controller->BUTTON_START)){
		
		controller->handleButton(controller->BUTTON_START);
		paused = !paused;
		if(!paused){
			if(displayedGame!=curGame || currentGame==NULL){
				curGame = displayedGame;
				delete currentGame;
				switch(displayedGame){
				case 0:
					currentGame = new Tetris(controller,strip);
                                        
					break;
				case 1:
					currentGame = new MegaMaze(controller,strip);
					break;
				case 2:
					currentGame = new Snake(controller,strip);
					break;
				case 3:
					currentGame = new ConnectFour(controller,strip);
					break;
				case 4:
					
					currentGame = new Rainbow(controller,strip);
					break;
				}
			}else{
				currentGame->resume();
			}
		}
		if(paused){
  
                     myMatrix.fillScreen(0); 
  
  myMatrix.drawRect(0, 0, 32, 16, myMatrix.Color333(5, 3, 5));
  myMatrix.setCursor(2, 8);
  myMatrix.setTextColor(myMatrix.Color333(1,5,7));
  myMatrix.print(str4);
			
		}
	}
	if(paused){
		for(int i=0;i<200;i++){
			strip->setPixelColor(i, 0x0);
		}
		int redPixels[] = {11,12,13,14,15,27,33,47,51,52,53,54,55};
		for(int i=0;i<((int)sizeof(redPixels)/2);i++){
			strip->setPixelColor(redPixels[i],0xFF0000);
		}
		int greenPixels[] = {64,65,66,67,68,71,73,75,84,86,88,91,93,95};
		for(int i=0;i<((int)sizeof(greenPixels)/2);i++){
			strip->setPixelColor(greenPixels[i],0x00FF00);
		}
		int bluePixels[] = {104,105,106,107,108,112,126,134,144,145,146,147,148};
		for(int i=0;i<((int)sizeof(bluePixels)/2);i++){
			strip->setPixelColor(bluePixels[i],0x0000FF);
		}
		int yellowPixels[] = {151,152,153,154,164,175,185,186,187,188};
		for(int i=0;i<((int)sizeof(yellowPixels)/2);i++){
			strip->setPixelColor(yellowPixels[i],0xFFFF00);
		}
		int whitePixels[] = {17,22,37,42,57,62,77,82,97,98,99,100,101,102,117,122,137,142,157,162,177,182};
		for(int i=0;i<((int)sizeof(whitePixels)/2);i++){
			strip->setPixelColor(whitePixels[i],0xFFFFFF);
		}
		strip->show();

// Display Menue




                myMatrix.fillScreen(0);   //CLEAR
  
  myMatrix.drawRect(0, 0, 32, 16, myMatrix.Color333(7, 0, 7));
  myMatrix.setCursor(4, 2);
  myMatrix.setTextColor(myMatrix.Color333(1,5,7));
  if(displayedGame==0){
			myMatrix.print(str3);
		}else if(displayedGame==1){
			myMatrix.print(str4);
		}else if(displayedGame==2){
			myMatrix.print(str5);
		}else if(displayedGame==3){
			myMatrix.print(str6);
		}else if(displayedGame==4){
			myMatrix.print(str7);
		}
  
	}else{
		currentGame->run();
	}

 


}

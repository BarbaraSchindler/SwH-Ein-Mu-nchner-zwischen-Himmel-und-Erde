#include <Adafruit_NeoPixel.h>

//Variablen
#define LEDPIN 11

// Parameter 1 = number of pixels in strip
// Parameter 2 = pin number (most are valid)
// Parameter 3 = pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
Adafruit_NeoPixel ledStrip = Adafruit_NeoPixel(34, LEDPIN, NEO_GRB + NEO_KHZ800);
uint16_t numberLEDs = ledStrip.numPixels();

//Pins fuer die Kontakte der Boards
const int boardZeroPin = 2;
const int boardOnePin = 3;
const int boardTwoPin = 4;
const int boardThreePin = 5;
const int boardFourPin = 6;
const int boardFivePin = 7;
const int boardSixPin = 8;
const int boardSevenPin = 9;

//Levels
int delayBeforeChoreography = 1000;
//Level 1
int delayChoreographyOneLED = 1000;
int beforeMessureLevelOne = 500;
int afterMessureLevelOne = 1000;
boolean levelOneNotDone = true;
int redLevelOne = 255;
int greenLevelOne = 255;
int blueLevelOne = 255;
int levelOneDoneRed = 0;
int levelOneDoneGreen = 255;
int levelOneDoneBlue = 0;
//Level zwei
int delayChoreographyTwoLED = 1000;
int beforeMessureLevelTwo = 500;
int afterMessureLevelTwo = 1000;
boolean levelTwoNotDone = true;
int redLevelTwo = 255;
int greenLevelTwo = 255;
int blueLevelTwo = 255;
int levelTwoDoneRed = 0;
int levelTwoDoneGreen = 255;
int levelTwoDoneBlue = 0;
//Level drei
int delayChoreographyThreeLED = 1000;
int beforeMessureLevelThree = 500;
int afterMessureLevelThree = 1000;
boolean levelThreeNotDone = true;
int redLevelThree = 255;
int greenLevelThree = 255;
int blueLevelThree = 255;

//Countdown
int redCountdown = 0;
int greenCountdown = 0;
int blueCountdown = 255;
int delayCountdown = 650;

//Delays
int delayInvitation = 500;
int delayPulseBoardZero = 500;
int levelShow = 0;
int delayError = 500;
int delayDone = 500;
int delayDirections = 300;
unsigned long oldTime;
unsigned long newTime;
unsigned long hopTime = 4000;
unsigned long timeDifference;


//Iterations
int iterationsChoreographyOne = 2;
int timeBetweenBoards = 4;
int iterationsLevelOneDone = 6;
int iterationsLevelTwoDone = 6;
int pulseError = 5;

//Booleans
boolean notStart;  
boolean further;
boolean notJumped;

    


//Methoden
void ledStripShow(long timeDelay){
    ledStrip.show();
    delay(timeDelay);
}


void allLEDOn(int red, int green, int blue, long timeDelay){
    allLEDOut(0);
    for(int n = 0; n<numberLEDs; n++){
      ledStrip.setPixelColor(n, ledStrip.Color(red, green, blue));
    }
    ledStripShow(timeDelay);;
}

void allLEDOut(long timeDelay){
    for(int n = 0; n<numberLEDs; n++){
      ledStrip.setPixelColor(n, ledStrip.Color(0, 0, 0));
    }
    ledStripShow(timeDelay);
}

void boardLED(int red, int green, int blue, int boardId, int anzahlLED){
    for(int n=boardId*4; n<boardId*4+anzahlLED; n++) {
      ledStrip.setPixelColor(n, ledStrip.Color(red, green, blue));
    }
}

void boardOutLED(int boardId, int anzahlLED){
    for(int n=boardId*4; n<boardId*4+anzahlLED; n++) {
      ledStrip.setPixelColor(n, ledStrip.Color(0, 0, 0));
    }
}


void pulseBoardZero(int red, int green, int blue, long timeDelay){
    allLEDOut(0);
    boardLED(red, green, blue, 0, 4);
    ledStripShow(timeDelay);
    boardOutLED(0, 4);
    ledStripShow(timeDelay);
}



void pulseAllBoardsLED(int red, int green, int blue, long timeDelay){
    allLEDOut(0);
    allLEDOn(red, green, blue, timeDelay);
    allLEDOut(timeDelay);
}


void choreographyOneLED(int red, int green, int blue, long timeDelay){
  allLEDOut(0);
  
  boardLED(red, green, blue, 0, 4);
  ledStripShow(timeDelay);

  boardOutLED(0, 4);
  boardLED(red, green, blue, 1, 4);
  ledStripShow(timeDelay);
  
  boardOutLED(1, 4);
  boardLED(red, green, blue, 2, 4);
  boardLED(red, green, blue, 3, 4);
  ledStripShow(timeDelay);
  
  boardOutLED(2, 4);
  boardOutLED(3, 4);
  boardLED(red, green, blue, 4, 4);
  ledStripShow(timeDelay);

  boardOutLED(4, 4);
  boardLED(red, green, blue, 5, 4);
  boardLED(red, green, blue, 6, 4);
  ledStripShow(timeDelay);

  boardOutLED(5, 4);
  boardOutLED(6, 4);
  boardLED(red, green, blue, 7, 6);
  ledStripShow(timeDelay);
  
  boardOutLED(7, 6);
  ledStripShow(timeDelay);
}


void choreographyTwoLED(int red, int green, int blue, long timeDelay){
  allLEDOut(0);

  boardLED(red, green, blue, 0, 4);
  ledStripShow(timeDelay);

  boardOutLED(0, 4);
  boardLED(red, green, blue, 2, 4);
  boardLED(red, green, blue, 3, 4);
  ledStripShow(timeDelay);
  
  boardOutLED(2, 4);
  boardOutLED(3, 4);
  boardLED(red, green, blue, 5, 4);
  boardLED(red, green, blue, 6, 4);
  ledStripShow(timeDelay);

  boardOutLED(5, 4);
  boardOutLED(6, 4);
  boardLED(red, green, blue, 7, 6);
  ledStripShow(timeDelay);
  
  boardOutLED(7, 6);
  ledStripShow(timeDelay);
}


void choreographyThreeLED(int red, int green, int blue, long timeDelay){
  allLEDOut(0);
  boardLED(red, green, blue, 0, 4);
  ledStripShow(timeDelay);

  boardOutLED(0, 4);
  boardLED(red, green, blue, 1, 4);
  ledStripShow(timeDelay);
  
  boardOutLED(1, 4);
  boardLED(red, green, blue, 2, 4);
  ledStripShow(timeDelay);
  
  boardOutLED(2, 4);
  boardLED(red, green, blue, 4, 4);
  ledStripShow(timeDelay);

  boardOutLED(4, 4);
  boardLED(red, green, blue, 6, 4);
  ledStripShow(timeDelay);

  boardOutLED(6, 4);
  boardLED(red, green, blue, 7, 6);
  ledStripShow(timeDelay);
  
  boardOutLED(7, 6);
  boardLED(red, green, blue, 5, 4);
  ledStripShow(timeDelay);

  boardOutLED(5, 4);
  boardLED(red, green, blue, 4, 4);
  ledStripShow(timeDelay);

  boardOutLED(4, 4);
  boardLED(red, green, blue, 3, 4);
  ledStripShow(timeDelay);

  boardOutLED(3, 4);
  boardLED(red, green, blue, 1, 4);
  ledStripShow(timeDelay);

  boardOutLED(1, 4);
  boardLED(red, green, blue, 0, 4);
  ledStripShow(timeDelay);

  boardOutLED(0, 4);
  ledStripShow(timeDelay);
}


void countdownLED(long timeDelay){
      delay(1000);
      allLEDOut(0);
      boardLED(0, 255, 0, 0, 4);
      boardLED(0, 255, 0, 1, 4);
      boardLED(255, 215, 0, 2, 4);
      boardLED(255, 215, 0, 3, 4);
      boardLED(255, 215, 0, 4, 4);
      boardLED(255, 0, 0, 5, 4);
      boardLED(255, 0, 0, 6, 4);
      boardLED(255, 0, 0, 7, 6);
      ledStripShow(timeDelay);

      boardOutLED(7, 6);
      ledStripShow(timeDelay);

      boardOutLED(6, 4);
      boardOutLED(5, 4);
      ledStripShow(timeDelay);

      boardOutLED(4, 4);
      ledStripShow(timeDelay);

      boardOutLED(3, 4);
      boardOutLED(2, 4);
      ledStripShow(timeDelay);

      boardOutLED(1, 4);
      ledStripShow(timeDelay);

      boardOutLED(0, 4);
      ledStripShow(timeDelay);
}


void north(int red, int green, int blue, int iterations){
  for(int i=0; i<iterations; i++){
    allLEDOut(0);
    
    boardLED(red, green, blue, 0, 4);
    ledStripShow(delayDirections);

    boardOutLED(0, 4);
    boardLED(red, green, blue, 1, 4);
    ledStripShow(delayDirections);

    boardOutLED(1, 4);
    boardLED(red, green, blue, 2, 4);
    boardLED(red, green, blue, 3, 4);
    ledStripShow(delayDirections);

    boardOutLED(2, 4);
    boardOutLED(3, 4);
    boardLED(red, green, blue, 4, 4);
    ledStripShow(delayDirections);

    boardOutLED(4, 4);
    boardLED(red, green, blue, 5, 4);
    boardLED(red, green, blue, 6, 4);
    ledStripShow(delayDirections);

    boardOutLED(5, 4);
    boardOutLED(6, 4);
    boardLED(red, green, blue, 7, 6);
    ledStripShow(delayDirections);
  }
}

void south(int red, int green, int blue, int iterations){
  for(int i=0; i<iterations; i++){
    allLEDOut(0);
    
    boardLED(red, green, blue, 7, 6);
    ledStripShow(delayDirections);

    boardOutLED(7, 6);
    boardLED(red, green, blue, 5, 4);
    boardLED(red, green, blue, 6, 4);
    ledStripShow(delayDirections);

    boardOutLED(5, 4);
    boardOutLED(6, 4);
    boardLED(red, green, blue, 4, 4);
    ledStripShow(delayDirections);

    boardOutLED(4, 4);
    boardLED(red, green, blue, 2, 4);
    boardLED(red, green, blue, 3, 4);
    ledStripShow(delayDirections);

    boardOutLED(2, 4);
    boardOutLED(3, 4);
    boardLED(red, green, blue, 1, 4);
    ledStripShow(delayDirections);

    boardOutLED(1, 4);
    boardLED(red, green, blue, 0, 4);
    ledStripShow(delayDirections);
  }
}

void east(int red, int green, int blue, int iterations){
  for(int i=0; i<iterations; i++){
    allLEDOut(0);

    boardLED(red, green, blue, 3, 4);
    boardLED(red, green, blue, 6, 4);
    ledStrip.setPixelColor(30, ledStrip.Color(red, green, blue));
    ledStrip.setPixelColor(32, ledStrip.Color(red, green, blue));
    ledStripShow(delayDirections);

    boardOutLED(3, 4);
    boardOutLED(6, 4);
    ledStrip.setPixelColor(30, ledStrip.Color(0, 0, 0));
    ledStrip.setPixelColor(32, ledStrip.Color(0, 0, 0));
    boardLED(red, green, blue, 0, 4);
    boardLED(red, green, blue, 1, 4);
    boardLED(red, green, blue, 4, 4);
    ledStrip.setPixelColor(29, ledStrip.Color(red, green, blue));
    ledStrip.setPixelColor(33, ledStrip.Color(red, green, blue));
//    boardLED(red, green, blue, 7, 6);
    ledStripShow(delayDirections);

    boardOutLED(0, 4);
    boardOutLED(1, 4);
    boardOutLED(4, 4);
    ledStrip.setPixelColor(29, ledStrip.Color(0, 0, 0));
    ledStrip.setPixelColor(33, ledStrip.Color(0, 0, 0));
//    boardOutLED(7, 4);
    boardLED(red, green, blue, 2, 4);
    boardLED(red, green, blue, 5, 4);
    ledStrip.setPixelColor(28, ledStrip.Color(red, green, blue));
    ledStrip.setPixelColor(31, ledStrip.Color(red, green, blue));
    ledStripShow(delayDirections);
  }
}

void west(int red, int green, int blue, int iterations){
  for(int i=0; i<iterations; i++){
    allLEDOut(0);

    boardLED(red, green, blue, 2, 4);
    boardLED(red, green, blue, 5, 4);
    ledStripShow(delayDirections);

    boardOutLED(2, 4);
    boardOutLED(5, 4);
    boardLED(red, green, blue, 0, 4);
    boardLED(red, green, blue, 1, 4);
    boardLED(red, green, blue, 4, 4);
    boardLED(red, green, blue, 7, 6);
    ledStripShow(delayDirections);

    boardOutLED(0, 4);
    boardOutLED(1, 4);
    boardOutLED(4, 4);
    boardOutLED(7, 4);
    boardLED(red, green, blue, 3, 4);
    boardLED(red, green, blue, 6, 4);
    ledStripShow(delayDirections);
  }
}


void invitationLED(long timeDelay){
  allLEDOut(0);
  
  ledStripShow(timeDelay);
}


void doneLED(){
east(186, 85, 211, 8);
}

void errorLED(){
    allLEDOut(0);
    for(int i=0; i<pulseError; i++){
       pulseAllBoardsLED(255, 0, 0, delayError);  
    }
}

void error(){
     errorLED();
     further = false;
     notJumped = false;
}

void levelOneDoneLED(int red, int green, int blue, long timeDelay){
  for(int i=0; i<iterationsLevelOneDone; i++){
    choreographyOneLED(red, green, blue, timeDelay);
  }
}

void levelTwoDoneLED(int red, int green, int blue, long timeDelay){
  for(int i=0; i<iterationsLevelTwoDone; i++){
    choreographyTwoLED(red, green, blue, timeDelay);
  }
}


void levelStart(){
    notStart = true;
    notJumped = true;
    while(notStart){
      pulseBoardZero(255, 255, 255, delayPulseBoardZero);
      if (digitalRead(boardZeroPin) == LOW){
        notStart = false;
        allLEDOut(0);
      }
    }
}

void levelOne(){
    levelStart();
    for(int i=0; i<iterationsChoreographyOne; i++){
        delay(delayBeforeChoreography);
        choreographyOneLED(redCountdown, greenCountdown, blueCountdown, delayChoreographyOneLED);
    }
    countdownLED(delayCountdown);
      while(hopTime >= 0 && notJumped){
          newTime = millis();
          timeDifference = newTime - oldTime;
          hopTime = hopTime - timeDifference;      
          delay(beforeMessureLevelOne);
          
      if(digitalRead(boardZeroPin) == LOW){
        if(digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
          notJumped = false;
          boardLED(redLevelOne, greenLevelOne, blueLevelOne, 0, 4);
          ledStripShow(levelShow);
          further = true;
           
        }
        else{
          error();
       }
      }
      else if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
      }
      else{
      error();
      }
      delay(afterMessureLevelOne);
    }
      
        if(further){
          notJumped = true;
          while(hopTime >= 0 && notJumped){
               newTime = millis();
               timeDifference = newTime - oldTime;
               hopTime = hopTime - timeDifference;
                      
                delay(beforeMessureLevelOne);
                if(digitalRead(boardOnePin) == LOW){
                  if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                    //boardOutLED(0, 4);
                    notJumped = false;
                    boardLED(redLevelOne, greenLevelOne, blueLevelOne, 1, 4);
                    ledStripShow(levelShow);
                    further = true;
                  }
                  else{
                    error();
                 }
                }
                else if(digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                 }
                else{
                     error();
                 }
                delay(afterMessureLevelOne);
              }          


              if(further){
                    notJumped = true;
                    while(hopTime >= 0 && notJumped){
                      newTime = millis();
                      timeDifference = newTime - oldTime;
                      hopTime = hopTime - timeDifference;
                      
                      delay(beforeMessureLevelOne);

                      
                      if(digitalRead(boardTwoPin) == LOW && digitalRead(boardThreePin) == LOW){
                        if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                          //boardOutLED(1, 4);
                          notJumped = false;
                          boardLED(redLevelOne, greenLevelOne, blueLevelOne, 2, 4);
                          boardLED(redLevelOne, greenLevelOne, blueLevelOne, 3, 4);
                          ledStripShow(levelShow);
                          further = true;
                           
                        }
                        else{
                          error();
                       }
                      }
                      else if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                       }
                      else{
                               error();
                        }
                      delay(afterMessureLevelOne);

                    }        
                  


                    if(further){
                      notJumped = true;
                      while(hopTime >= 0 && notJumped){
                        newTime = millis();
                        timeDifference = newTime - oldTime;
                        hopTime = hopTime - timeDifference;
                            delay(beforeMessureLevelOne);
                            if(digitalRead(boardFourPin) == LOW){
                              if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                //boardOutLED(2, 4);
                                //boardOutLED(3, 4);
                                notJumped = false;
                                boardLED(redLevelOne, greenLevelOne, blueLevelOne, 4, 4);
                                ledStripShow(levelShow);
                                further = true;
                                 
                              }
                              else{
                                error();
                             }
                            }
                              else if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                              }
                              else{
                                error();
                              }
                            delay(afterMessureLevelOne);
                          }          
                  

                            if(further){
                                notJumped = true;
                                while(hopTime >= 0 && notJumped){
                                    newTime = millis();
                                    timeDifference = newTime - oldTime;
                                     hopTime = hopTime - timeDifference;                                    
                                     delay(beforeMessureLevelOne);
                                     
                                    if(digitalRead(boardFivePin) == LOW && digitalRead(boardSixPin) == LOW){
                                      if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                        //boardOutLED(4, 4);
                                        notJumped = false;
                                        boardLED(redLevelOne, greenLevelOne, blueLevelOne, 5, 4);
                                        boardLED(redLevelOne, greenLevelOne, blueLevelOne, 6, 4);
                                        ledStripShow(levelShow);
                                        further = true;
                                         
                                      }
                                      else{
                                        error();
                                     }
                                    }
                                    else if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                    }
                                    else{
                                        error();
                                    }
                                    delay(afterMessureLevelOne);
                                  }          

                                          if(further){
                                              notJumped = true;
                                              while(hopTime >= 0 && notJumped){
                                              newTime = millis();
                                              timeDifference = newTime - oldTime;
                                              hopTime = hopTime - timeDifference;   
                                                                                             
                                              delay(beforeMessureLevelOne);
                                              
                                                  if(digitalRead(boardSevenPin) == LOW){
                                                    if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH){
                                                      //boardOutLED(5, 4);
                                                      //boardOutLED(6, 4);
                                                      notJumped = false;
                                                      boardLED(redLevelOne, greenLevelOne, blueLevelOne, 7, 4);
                                                      ledStripShow(levelShow);
                                                      levelOneNotDone = false;
                                                      levelOneDoneLED(levelOneDoneRed, levelOneDoneGreen, levelOneDoneBlue, 200);
                                                    }
                                                    else{
                                                      error();
                                                   }
                                                  }
                                                   else if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                                    }
                                                    else{
                                                        error();
                                                    }
                                                 delay(afterMessureLevelOne);
                                                }   
                                          }
                            }
                    }       
            }
        }   
}


void levelTwo(){
    levelStart();
    delay(delayBeforeChoreography);
    choreographyTwoLED(redCountdown, greenCountdown, blueCountdown, delayChoreographyTwoLED);
    countdownLED(delayCountdown);
      while(hopTime >= 0 && notJumped){
          newTime = millis();
          timeDifference = newTime - oldTime;
          hopTime = hopTime - timeDifference;      
          delay(beforeMessureLevelTwo);
          
      if(digitalRead(boardZeroPin) == LOW){
        if(digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
          boardLED(redLevelOne, greenLevelOne, blueLevelOne, 0, 4);
          ledStripShow(levelShow);
          further = true;
           
        }
        else{
          error();
       }
      } else if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
        }
       else{
           error();
       }
      delay(afterMessureLevelTwo);
    }
      

      if(further){
            notJumped = true;
            while(hopTime >= 0 && notJumped){
                      newTime = millis();
                      timeDifference = newTime - oldTime;
                      hopTime = hopTime - timeDifference;                      
                      delay(beforeMessureLevelTwo);
                      
                      if(digitalRead(boardTwoPin) == LOW && digitalRead(boardThreePin) == LOW){
                        if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                          notJumped = false;
                          boardOutLED(0, 4);
                          boardLED(redLevelOne, greenLevelOne, blueLevelOne, 2, 4);
                          boardLED(redLevelOne, greenLevelOne, blueLevelOne, 3, 4);
                          ledStripShow(levelShow);
                          further = true;
                           
                        }
                        else{
                          error();
                       }
                      }
                      else if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                      }
                      else{
                        error();
                      }
                      delay(afterMessureLevelTwo);
                    }          
                 
                  

                    if(further){
                          notJumped = true;
                          while(hopTime >= 0 && notJumped){
                              newTime = millis();
                              timeDifference = newTime - oldTime;
                              hopTime = hopTime - timeDifference;                                    
                              delay(beforeMessureLevelTwo);
                              
                                    if(digitalRead(boardFivePin) == LOW && digitalRead(boardSixPin) == LOW){
                                      if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                        boardOutLED(2, 4);
                                        boardOutLED(3, 4);
                                        boardLED(redLevelOne, greenLevelOne, blueLevelOne, 5, 4);
                                        boardLED(redLevelOne, greenLevelOne, blueLevelOne, 6, 4);
                                        ledStripShow(levelShow);
                                        further = true;
                                         
                                      }
                                      else{
                                        error();
                                     }
                                    }
                                    else if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                    }
                                    else{
                                        error();
                                    }
                                    delay(afterMessureLevelTwo);
                                  }          

                                          if(further){
                                              notJumped = true;
                                              while(hopTime >= 0 && notJumped){
                                              newTime = millis();
                                              timeDifference = newTime - oldTime;
                                              hopTime = hopTime - timeDifference;                                                  
                                              delay(beforeMessureLevelTwo);
                                              
                                                  if(digitalRead(boardSevenPin) == LOW){
                                                    if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH){
                                                      notJumped = false;
                                                      boardOutLED(5, 4);
                                                      boardOutLED(6, 4);
                                                      boardLED(redLevelOne, greenLevelOne, blueLevelOne, 7, 4);
                                                      ledStripShow(levelShow);
                                                      levelOneNotDone = false; 
                                                      levelTwoDoneLED(levelTwoDoneRed, levelTwoDoneGreen, levelTwoDoneBlue, 200);
                                                       
                                                    }
                                                    else{
                                                      error();
                                                   }
                                                  }
                                                  else if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                                  }
                                                  else{
                                                      error();
                                                  }
                                                  delay(afterMessureLevelTwo);
                                                }   
                                          }     
            }
        }   
}


void levelThree(){
    levelStart();
    delay(delayBeforeChoreography);
    choreographyThreeLED(redCountdown, greenCountdown, blueCountdown, delayChoreographyThreeLED);
    countdownLED(delayCountdown);
          while(hopTime >= 0 && notJumped){
              newTime = millis();
              timeDifference = newTime - oldTime;
              hopTime = hopTime - timeDifference;      
              delay(beforeMessureLevelThree);
              
      if(digitalRead(boardZeroPin) == LOW){
        if(digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
          notJumped = false;
          boardLED(redLevelOne, greenLevelOne, blueLevelOne, 0, 4);
          ledStripShow(levelShow);
          further = true;
           
        }
        else{
          error();
       }
      }
      else if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
      }
      else{
            error();
     }
      delay(afterMessureLevelThree);
    }

    if(further){
        notJumped = true;
        while(hopTime >= 0 && notJumped){
               newTime = millis();
               timeDifference = newTime - oldTime;
               hopTime = hopTime - timeDifference;      
               delay(beforeMessureLevelThree);
               
      if(digitalRead(boardOnePin) == LOW){
        if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
          notJumped = false;
          boardLED(redLevelOne, greenLevelOne, blueLevelOne, 1, 4);
          ledStripShow(levelShow);
          further = true;
           
        }
        else{
          error();
       }
      }
      else if(digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
      }
      else{
            error();
     }
      delay(afterMessureLevelThree);
    }
    
      

      if(further){
              notJumped = true;
              while(hopTime >= 0 && notJumped){
                      newTime = millis();
                      timeDifference = newTime - oldTime;
                      hopTime = hopTime - timeDifference;                      
                      
                      delay(beforeMessureLevelThree);
                      
                      if(digitalRead(boardTwoPin) == LOW){
                        if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                          notJumped = false;
                          boardOutLED(0, 4);
                          boardLED(redLevelOne, greenLevelOne, blueLevelOne, 2, 4);
                          ledStripShow(levelShow);
                          further = true;
                           
                        }
                        else{
                          error();
                       }
                      }
                      else if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                      }
                      else{
                          error();
                     }
                      delay(afterMessureLevelThree);
                    }          
                 
                  

                    if(further){
                          notJumped = true;
                          while(hopTime >= 0 && notJumped){
                              newTime = millis();
                              timeDifference = newTime - oldTime;
                              hopTime = hopTime - timeDifference;                                    
                              delay(beforeMessureLevelThree);
                              
                                    if(digitalRead(boardFourPin) == LOW){
                                      if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                        notJumped = false;
                                        boardOutLED(2, 4);
                                        boardLED(redLevelOne, greenLevelOne, blueLevelOne, 4, 4);
                                        ledStripShow(levelShow);
                                        further = true;
                                         
                                      }
                                      else{
                                        error();
                                     }
                                    }
                                    else if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                    }
                                    else{
                                        error();
                                    }
                                    delay(afterMessureLevelThree);
                                  }  

                                   if(further){
                                        notJumped = true;
                                        while(hopTime >= 0 && notJumped){
                                            newTime = millis();
                                            timeDifference = newTime - oldTime;
                                            hopTime = hopTime - timeDifference;                                                  
                                            delay(beforeMessureLevelThree);
                                            
                                                  if(digitalRead(boardSixPin) == LOW){
                                                    if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                                      notJumped = false;
                                                      boardOutLED(4, 4);
                                                      boardLED(redLevelOne, greenLevelOne, blueLevelOne, 6, 4);
                                                      ledStripShow(levelShow);
                                                      further = true;
                                                       
                                                    }
                                                    else{
                                                      error();
                                                   }
                                                  }
                                                  else if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                                  }
                                                  else{
                                                      error();
                                                  }
                                                  delay(afterMessureLevelThree);
                                                }          


                                                  if(further){
                                                      notJumped = true;
                                                      while(hopTime >= 0 && notJumped){
                                                          newTime = millis();
                                                          timeDifference = newTime - oldTime;
                                                           hopTime = hopTime - timeDifference;                                                          
                                                           delay(beforeMessureLevelThree);
                                                           
                                                          if(digitalRead(boardSevenPin) == LOW){
                                                            if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH){
                                                              notJumped = false;
                                                              boardOutLED(6, 4);
                                                              boardLED(redLevelOne, greenLevelOne, blueLevelOne, 7, 4);
                                                              ledStripShow(levelShow);
                                                              further = true;
                                                               
                                                            }
                                                            else{
                                                              error();
                                                           }
                                                          }
                                                          else if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                                          }
                                                          else{
                                                              error();
                                                          }
                                                          delay(afterMessureLevelThree);
                                                        } 

                                                          
                                                              if(further){
                                                                  notJumped = true;
                                                                  while(hopTime >= 0 && notJumped){
                                                                      newTime = millis();
                                                                      timeDifference = newTime - oldTime;
                                                                      hopTime = hopTime - timeDifference;                                                                      
                                                                      delay(beforeMessureLevelThree);
                                                                      
                                                                      if(digitalRead(boardFivePin) == LOW){
                                                                        if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                                                          notJumped = false;
                                                                          boardOutLED(7, 4);
                                                                          boardLED(redLevelOne, greenLevelOne, blueLevelOne, 5, 4);
                                                                          ledStripShow(levelShow);
                                                                          further = true;
                                                                           
                                                                        }
                                                                        else{
                                                                          error();
                                                                       }
                                                                      }
                                                                      else if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH){
                                                                      }
                                                                      else{
                                                                          error();
                                                                      }
                                                                      delay(afterMessureLevelThree);
                                                                    } 

                                                                      if(further){
                                                                              notJumped = true;
                                                                              while(hopTime >= 0 && notJumped){
                                                                                  newTime = millis();
                                                                                  timeDifference = newTime - oldTime;
                                                                                  hopTime = hopTime - timeDifference;  
                                                                                  delay(beforeMessureLevelThree);
                                                                                  
                                                                                        if(digitalRead(boardFourPin) == LOW){
                                                                                          if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                                                                            notJumped = false;
                                                                                            boardOutLED(5, 4);
                                                                                            boardLED(redLevelOne, greenLevelOne, blueLevelOne, 4, 4);
                                                                                            ledStripShow(levelShow);
                                                                                            further = true;
                                                                                             
                                                                                          }
                                                                                          else{
                                                                                            error();
                                                                                         }
                                                                                        }
                                                                                        else if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                                                                        }
                                                                                        else{
                                                                                            error();
                                                                                        }
                                                                                        delay(afterMessureLevelThree);
                                                                                      } 
                                                                                       
                                                                                      if(further){
                                                                                            notJumped = true;
                                                                                            while(hopTime >= 0 && notJumped){
                                                                                                  newTime = millis();
                                                                                                  timeDifference = newTime - oldTime;
                                                                                                  hopTime = hopTime - timeDifference;     
                                                                                                  delay(beforeMessureLevelThree);
                                                                                                  
                                                                                                    if(digitalRead(boardThreePin) == LOW){
                                                                                                      if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                                                                                        notJumped = false;
                                                                                                        boardOutLED(4, 4);
                                                                                                        boardLED(redLevelOne, greenLevelOne, blueLevelOne, 3, 4);
                                                                                                        ledStripShow(levelShow);
                                                                                                        further = true;
                                                                                                         
                                                                                                      }
                                                                                                      else{
                                                                                                        error();
                                                                                                     }
                                                                                                    }
                                                                                                    else if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                                                                                    }
                                                                                                    else{
                                                                                                        error();
                                                                                                    }
                                                                                                    delay(afterMessureLevelThree);
                                                                                                  } 

                                                                                                   if(further){
                                                                                                          notJumped = true;
                                                                                                          while(hopTime >= 0 && notJumped){
                                                                                                                                newTime = millis();
                                                                                                                                timeDifference = newTime - oldTime;
                                                                                                                                hopTime = hopTime - timeDifference;
                                                                                                                                delay(beforeMessureLevelThree);
                                                                                                                                
                                                                                                                if(digitalRead(boardOnePin) == LOW){
                                                                                                                  if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH  && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                                                                                                    notJumped = false;
                                                                                                                    boardOutLED(3, 4);
                                                                                                                    boardLED(redLevelOne, greenLevelOne, blueLevelOne, 1, 4);
                                                                                                                    ledStripShow(levelShow);
                                                                                                                    further = true;
                                                                                                                     
                                                                                                                  }
                                                                                                                  else{
                                                                                                                    error();
                                                                                                                 }
                                                                                                                }
                                                                                                                  else if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                                                                                                  }
                                                                                                                  else{
                                                                                                                      error();
                                                                                                                  }
                                                                                                                delay(afterMessureLevelThree);
                                                                                                              }  

                                                                                                              if(further){
                                                                                                                    notJumped = true;
                                                                                                                    while(hopTime >= 0 && notJumped){
                                                                                                                                          newTime = millis();
                                                                                                                                          timeDifference = newTime - oldTime;
                                                                                                                                          hopTime = hopTime - timeDifference; 
                                                                                                                                          delay(beforeMessureLevelThree);
                                                                                                                        if(digitalRead(boardZeroPin) == LOW){
                                                                                                                          if(digitalRead(boardOnePin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH  && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                                                                                                            notJumped = false;
                                                                                                                            boardOutLED(1, 4);
                                                                                                                            boardLED(redLevelOne, greenLevelOne, blueLevelOne, 0, 4);
                                                                                                                            ledStripShow(levelShow);
                                                                                                                            levelThreeNotDone = false;
                                                                                                           
                                                                                                                             
                                                                                                                          }
                                                                                                                          else{
                                                                                                                            error();
                                                                                                                         }
                                                                                                                        }
                                                                                                                        else if(digitalRead(boardZeroPin) == HIGH && digitalRead(boardTwoPin) == HIGH && digitalRead(boardThreePin) == HIGH && digitalRead(boardFourPin) == HIGH && digitalRead(boardFivePin) == HIGH && digitalRead(boardSixPin) == HIGH && digitalRead(boardSevenPin) == HIGH){
                                                                                                                        }
                                                                                                                        else{
                                                                                                                            error();
                                                                                                                        }
                                                                                                                       delay(afterMessureLevelThree);
                                                                                                                      } 
                                                                                                              }
                                                                                                   }
                                                                                      }
                                                                      }
                                                              }         }
                                          }     
            }
        }   
  }
}


void allLevels(){
  while(levelOneNotDone){
    levelOne();
  }
//  while(levelTwoNotDone){
//   levelTwo();
//  }
  while(levelThreeNotDone){
    levelThree();
  }
}

void start(){
  invitationLED(delayInvitation);
}

void ende(){
  doneLED();
  allLEDOut(0);
}

void mainHimmelHoelle(){
//  start();
  allLevels();
  ende();
}




void setup() {
  
   oldTime = millis();
   notJumped = true;
    ledStrip.begin();
    pinMode(boardZeroPin, INPUT);
  digitalWrite(boardZeroPin, HIGH);
    pinMode(boardOnePin, INPUT);
  digitalWrite(boardOnePin, HIGH);
    pinMode(boardTwoPin, INPUT);
  digitalWrite(boardTwoPin, HIGH);
    pinMode(boardThreePin, INPUT);
  digitalWrite(boardThreePin, HIGH);
    pinMode(boardFourPin, INPUT);
  digitalWrite(boardFourPin, HIGH);
    pinMode(boardFivePin, INPUT);
  digitalWrite(boardFivePin, HIGH);
    pinMode(boardSixPin, INPUT);
  digitalWrite(boardSixPin, HIGH);
    pinMode(boardSevenPin, INPUT);
  digitalWrite(boardSevenPin, HIGH);

}


void loop() {
  mainHimmelHoelle();
}

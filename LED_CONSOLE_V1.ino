
int totalchannels = 6;
int index = 0;
int brightness = 0;
int dimInput = 1;
int dimSpeed = 1;
int dwell = (3600);

int channel[] = {3, 5, 6, 9, 10, 11};
int currentBrightness[] = {0, 0, 0, 0, 0, 0};
int setBrightness[] = {0, 0, 0, 0, 0, 0};
int uiDirty[] = {0, 0, 0, 0, 0, 0};
long previousMillis[] = {0, 0, 0, 0, 0, 0};
int interval[] = {0, 0, 0, 0, 0, 0};


void setup() {
  
   Serial.begin(19200);
   randomSeed(analogRead(0)); 
 
   TCCR0B = TCCR0B & 0b11111000 | 0x01; //sets pins 5 and 6 to 62.5kHz
  //TIMER0 (PINS 5&6 CONTROL THE MILLIS() AND DELAY*() FUNCTIONS
  //AT 62kHz: delay(64000) or 64000 millis() ~ 1 second
  
   TCCR1B = TCCR1B & 0b11111000 | 0x01; //sets pins 10 and 9 to 31.2kHz
   TCCR2B = TCCR2B & 0b11111000 | 0x01; //sets pins 3 and 11 to 31.2kHz
   


  //Give Instructions on Console
  Serial.println("* FADING LED STRIP CONSOLE *");
  Serial.println("");
  Serial.println("Instructions: Change a channel brightness by entering values in the format i,n,s where:");
  Serial.println("i is the channel number (1 through 6), ");
  Serial.println("n is the 8-bit brightness values (0 to 255), and");
  Serial.println("s is the speed factor (1 = very slow, 3600 = instant).");
  //Serial.println("Line Ending must be set to Newline.");
  Serial.println("");
}



void loop() {
  // If there's any serial available, read it:
 
  
  while (Serial.available() > 0) {

    //Read the CSV from the serial port and parse to separate varibles:
    index = Serial.parseInt();
    brightness = Serial.parseInt();
    dimInput = Serial.parseInt(); 
    
    setBrightness[index -1] = brightness;
    dimSpeed = dimInput;
    interval[index -1] = (3600 / dimSpeed);
    

    //Continue after newline is detected
    if (Serial.read() == '\n' ) {
      
      //Check to make sure pixel is within range
      if (index > totalchannels || index <= 0){
        Serial.println("Invalid Channel!");
      }
      if (brightness > 255 || brightness < 0){
        Serial.println("Invalid Brighness!");
        index = 255;
      }
      if (dimInput  <= 0){
        dimInput = 1;
      }
      
      
      
      
      
      
    }
 
 else{
 
 
 
 }
 
  }
 
 
 unsigned long currentMillis = millis();
 
 for (int i = 0; i < 6 ; i++) {
  
   if (setBrightness[i] > currentBrightness[i] && currentMillis - previousMillis[i] >= interval[i]) {
    
     previousMillis[i] = currentMillis;
    currentBrightness[i]++;
    uiDirty[i]= 1;    
    int pin = channel[i];     
    analogWrite(pin, currentBrightness[i]);

  }    
  
  
  if (setBrightness[i] < currentBrightness[i] && currentMillis - previousMillis[i] >= interval[i]) {

    previousMillis[i] = currentMillis;
    currentBrightness[i]--;
    uiDirty[i] = 1;
    int pin = channel[i];
    analogWrite(pin, currentBrightness[i]);

  }    
  
  
  if (setBrightness[i] == currentBrightness[i] && uiDirty[i] == 1 ){

      int pin = channel[i];
      Serial.print("Channel Number ");
      Serial.print(i+1);
      Serial.print(" set to ");      
      Serial.print(currentBrightness[i]);
      Serial.print(" (Digital Pin #");      
      Serial.print(pin);
      Serial.print(")"); 
      Serial.println(""); 
      uiDirty[i] = 0;
  }
  

 
}
 
 
 
 
 
}
 

 
 
 

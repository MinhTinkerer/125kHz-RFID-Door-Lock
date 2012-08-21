/******************* ARDUINO_RFID_read.ino ********************
This code is a simple RFID tag reader and checker.  As of now, can only check one tag.
Uses the seeedstudio 125kHz tag reader (UART) and an Arduino Duemilanove.

By: Nicholas McGill
**************************************************************/

// DEFINES
#define STARTBIT 2
#define TAG_LENGTH 12

// SUBROUTINES
void read_tag(void);
void compare_tag(void);

// GLOBAL VARIABLES
int data1;
int tag[TAG_LENGTH];
int nick_tag[TAG_LENGTH] = {0,0,0,0,0,0,0,0,0,0,0,0};   // Put your tag here.
int all_equal = 0;


// *********************** SETUP ***********************
void setup()
{
  Serial.begin(9600);
}

// *********************** MAIN LOOP ***********************
void loop() 
{
  
  if (Serial.available() > 0) {
    read_tag();
    compare_tag();
    reset_tag();
  } // END OF SERIAL AVAILABLE IF
} // END OF LOOP


// *********************** READ_TAG ***********************
void read_tag(void){
    data1 = Serial.read();  // read the incoming number on serial RX
    
    if (data1 == STARTBIT){
      for(int i=0; i<TAG_LENGTH; i++){
        while(!Serial.available());
        tag[i]=Serial.read();
        
        // display incoming number	
        Serial.print(" ");
        Serial.println(tag[i], DEC);
       }  // END OF FOR      
     }
     data1 = Serial.read();  // read the ENDBIT to flush buffer
}

// *********************** COMPARE_TAG ***********************
void compare_tag(void){
     // Compare tags with database
     for(int i=0; i<TAG_LENGTH; i++){
       if(tag[i] == nick_tag[i]){
         all_equal++;
       }
     }
     if(all_equal == TAG_LENGTH){
       Serial.print("\nERMERGERD IT WERKS!!!");      
     }
     else{
      Serial.print("\nERCERSS DERNERDDD");
     }
     all_equal = 0;
}

// *********************** RESET_TAG ***********************
void reset_tag(void){
  for(int i=0; i<TAG_LENGTH; i++){ 
    tag[i] = 0;
  }
}

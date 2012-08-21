/******************* ARDUINO_RFID_read.ino ********************
This code is a simple RFID tag reader and checker.  As of now, can only check one tag.
Uses the seeedstudio 125kHz tag reader (UART) and an Arduino Duemilanove.

By: Nicholas McGill
**************************************************************/

// DEFINES
#define STARTBYTE 2
#define ENDBYTE 3
#define TAG_LENGTH 12  // The 125 kHz tags have 12 unique bytes, with a total of 14 bytes including the STARTBYTE and ENDBYTE

// SUBROUTINES
void readTag(void);
void compareTag(void);
void resetTag(void);

// GLOBAL VARIABLES
int rfid_data;
int read_tag[TAG_LENGTH];
int nick_tag[TAG_LENGTH] = {0,0,0,0,0,0,0,0,0,0,0,0};   // Put your tag here.


// *********************** SETUP ***********************
void setup()
{
  Serial.begin(9600);
}

// *********************** MAIN LOOP ***********************
void loop(){
    readTag();
} // END OF LOOP


// *********************** READ_TAG ***********************
void readTag(void){
  
  if (Serial.available() > 0) { // If there's data coming in over the serial port...
    rfid_data = Serial.read();  // ... read the incoming byte on serial RX line into rfid_data

    if (rfid_data == STARTBYTE){  // If rfid_data is the STARTBYTE...
      while(!Serial.available()); // ... wait until the next serial buffer byte is available to read
      rfid_data = Serial.read();  // ... read the second byte into rfid_data
      
      int index = 0;                // Create an index variable for saving the unique tag bytes into the tag
      Serial.print("\nRead tag: ");
      while( (rfid_data != ENDBYTE) && (index < TAG_LENGTH) ){  // While we have not received the ENDBYTE...
        read_tag[index] = rfid_data;// ... save this byte into the read_tag array for future comparison
        Serial.print(" "); Serial.print(read_tag[index], DEC);  // Display the unique tag numbers in the serial monitor.
        index++;                    // ... increment the index
        while(!Serial.available()); // ... wait until the next serial buffer byte is available to read
        rfid_data = Serial.read();  // ... read the next byte into rfid_data
       }  // END OF FOR LOOP   
    }  // END OF STARTBYTE IF   
    
    compareTag();  // Compare the read_tag array with the stored tag arrays
    resetTag();    // Reset the read_tag array to all zeros
  } // END OF SERIAL AVAILABLE IF
}

// *********************** COMPARE_TAG ***********************
void compareTag(void){
  int all_equal = 0;
  
  // +++++ Compare tags with database +++++
  for( int i=0; i<TAG_LENGTH; i++ ){    // Loop over the length of read_tag
    if(read_tag[i] == nick_tag[i]){
      all_equal++;  // 
    }
  }  // END OF FOR LOOP
  
  // +++++ Determine if the tag matches the saved tags +++++
  if(all_equal == TAG_LENGTH){
    Serial.print("\nERMERGERD IT WERKS!!!");  }
  else{
    Serial.print("\nERCERSS DERNERDDD");  }
}  // END OF COMPARETAG

// *********************** RESET_TAG ***********************
void resetTag(void){
  for( int i=0; i<TAG_LENGTH; i++ ){ 
    read_tag[i] = 0;
  }
}

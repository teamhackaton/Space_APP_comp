
#include <SPI.h>
#include <MFRC522.h>

#include <Bridge.h>
#include <Temboo.h>
#include "TembooAccount.h" // contains Temboo account information

#define SS_PIN          10          // Configurable, see typical pin layout above

const uint8_t RST_PIN = 5; //for yun

const int WAITTIME = 50;
const int STEP = 5;

int led = 5;                // the pin that the LED is atteched to
int state = LOW;             // by default, no motion detected
int val = 0;                 // variable to store the sensor status (value)

MFRC522 mfrc522(SS_PIN, RST_PIN);   // Create MFRC522 instance

/*** SUBSTITUTE YOUR VALUES BELOW: ***/

// Note that for additional security and reusability, you could
// use #define statements to specify these values in a .h file.

// your Gmail username, formatted as a complete email address, eg "bob.smith@gmail.com"
const String GMAIL_USER_NAME = "teamhackaton@gmail.com";

// your Gmail App-Specific Password
const String GMAIL_PASSWORD = "kcuzrdlivwneqspu";

// the email address you want to send the email to, eg "jane.doe@temboo.com"
const String TO_EMAIL_ADDRESS = "m.elkadirielhassani@aui.ma";


boolean success = false; // a flag to indicate whether we've sent the email yet or not

void setup() {
  pinMode(led, OUTPUT);      // initalize LED as an output
  analogWrite(led,0);
  Serial.begin(9600);
   // for debugging, wait until a serial console is connected
  delay(4000);
  while(!Serial);

  Bridge.begin();
  SPI.begin();                                                  // Init SPI bus
  mfrc522.PCD_Init();                                              // Init MFRC522 card
  Serial.println(F("Read personal data on a MIFARE PICC:"));    //shows in serial that it is ready to read
 
}

void loop()
{

  // Prepare key - all keys are set to FFFFFFFFFFFFh at chip delivery from the factory.
  MFRC522::MIFARE_Key key;
  for (byte i = 0; i < 6; i++) key.keyByte[i] = 0xFF;

  //some variables we need
  byte block;
  byte len;
  MFRC522::StatusCode status;

  //-------------------------------------------

  // Reset the loop if no new card present on the sensor/reader. This saves the entire process when idle.
  if ( ! mfrc522.PICC_IsNewCardPresent()) {
    return;
  }

  // Select one of the cards
  if ( ! mfrc522.PICC_ReadCardSerial()) {
    return;
  }

  Serial.println(F("**Card Detected:**"));
  
  // send info to the main and save log_in based on activity  (sleep, exercise ...)
  
  //-------------------------------------------

  mfrc522.PICC_DumpDetailsToSerial(&(mfrc522.uid)); //dump some details about the card

  //mfrc522.PICC_DumpToSerial(&(mfrc522.uid));      //uncomment this to see all blocks in hex

  //-------------------------------------------
    
  // only try to send the email if we haven't already sent it successfully
    if (!success) {
  
      Serial.println("Running SendAnEmail...");
    
      TembooChoreo SendEmailChoreo;
  
      // invoke the Temboo client
      // NOTE that the client must be reinvoked, and repopulated with
      // appropriate arguments, each time its run() method is called.
      SendEmailChoreo.begin();
      
      // set Temboo account credentials
      SendEmailChoreo.setAccountName(TEMBOO_ACCOUNT);
      SendEmailChoreo.setAppKeyName(TEMBOO_APP_KEY_NAME);
      SendEmailChoreo.setAppKey(TEMBOO_APP_KEY);
  
      // identify the Temboo Library choreo to run (Google > Gmail > SendEmail)
      SendEmailChoreo.setChoreo("/Library/Google/Gmail/SendEmail");
   
  
      // set the required choreo inputs
      // see https://www.temboo.com/library/Library/Google/Gmail/SendEmail/ 
      // for complete details about the inputs for this Choreo
  
      // the first input is your Gmail email address
      SendEmailChoreo.addInput("Username", GMAIL_USER_NAME);
      // next is your Gmail App-Specific password.
      SendEmailChoreo.addInput("Password", GMAIL_PASSWORD);
      // who to send the email to
      SendEmailChoreo.addInput("ToAddress", TO_EMAIL_ADDRESS);
      // then a subject line
      SendEmailChoreo.addInput("Subject", "RFID SCANNED!");
  
       // next comes the message body, the main content of the email   
      SendEmailChoreo.addInput("MessageBody", "Astronaut_Test is logged in");
  
      // tell the Choreo to run and wait for the results. The 
      // return code (returnCode) will tell us whether the Temboo client 
      // was able to send our request to the Temboo servers
      unsigned int returnCode = SendEmailChoreo.run();
  
      // a return code of zero (0) means everything worked
      if (returnCode == 0) {
          Serial.println("Success! Email sent!");
          success = true;
      } else {
        // a non-zero return code means there was an error
        // read and print the error message
        while (SendEmailChoreo.available()) {
          char c = SendEmailChoreo.read();
          Serial.print(c);
        }
      } 
      SendEmailChoreo.close();
  
      // do nothing for the next 10 seconds
      delay(10000);
    }
  
  
  Serial.print(F("Name: "));

  byte buffer1[18];

  block = 4;
  len = 18;

  //------------------------------------------- GET FIRST NAME
  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 4, &key, &(mfrc522.uid)); //line 834 of MFRC522.cpp file
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer1, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //PRINT FIRST NAME
  
  for (uint8_t i = 0; i < 16; i++)
  {
    if (buffer1[i] != 32)
    {
      Serial.write(buffer1[i]);
    }
  }

  
  Serial.print(" ");

  //---------------------------------------- GET LAST NAME

  byte buffer2[18];
  block = 1;

  status = mfrc522.PCD_Authenticate(MFRC522::PICC_CMD_MF_AUTH_KEY_A, 1, &key, &(mfrc522.uid)); //line 834
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Authentication failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  status = mfrc522.MIFARE_Read(block, buffer2, &len);
  if (status != MFRC522::STATUS_OK) {
    Serial.print(F("Reading failed: "));
    Serial.println(mfrc522.GetStatusCodeName(status));
    return;
  }

  //PRINT LAST NAME
  for (uint8_t i = 0; i < 16; i++) {
    Serial.write(buffer2[i] );
  }


  //----------------------------------------

  Serial.println(F("\n**End Reading**\n"));

  delay(5000); //change value if you want to read cards faster // Change it in order to detect the card in case of mis-detection

  mfrc522.PICC_HaltA();
  mfrc522.PCD_StopCrypto1();
}

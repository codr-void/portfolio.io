#include <Wire.h>
#include <LiquidCrystal.h>
#include <LiquidCrystal_I2C.h>
#include <WiFi.h>
#include <WebServer.h>
#include "index.h"  //Web page header file
#include "FS.h"
#include "SD.h"
#include "SPI.h"
#include <NTPClient.h>
#include <WiFiUdp.h>

// these are used to grap the epoch timestamp
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org");

// this is the object used to interact with the lcd screen
// NOTE: IF 0x27 does not work, try 0x3F as suggested by some sources online 
LiquidCrystal_I2C lcd(0x27, 16, 2); // I2C address 0x27, 16 column and 2 rows
//LiquidCrystal lcd(5, 18, 19, 16, 17, 21);

// define the gpios for parking sensors
#define parking_1_sensor 33
#define parking_2_sensor 25
#define parking_3_sensor 27
#define parking_4_sensor 26
#define CHIP_SELECT_PIN 5

// we will use this to get the value of the time value epoch


// this is the total spots that are in the parking lot
const int total_spots_in_parking = 4;

// each spot will correspond to a sensor
// if the parking spot is occupied , spot# = 1
// if the parking spot is empty, spot# = 0
int spot1 = 0; 
int spot2 = 0; 
int spot3 = 0; 
int spot4 = 0; 

// this variable represent how many spots are full
int total_full_spots = spot1 + spot2 + spot3 + spot4 ;

// this variable represent how many spots are empty
int total_empty_spots = total_spots_in_parking - total_full_spots;

//
int counter_for_sending_data_to_sd_card = 0;

//network credentials and creating the webserver 
WebServer server(80);
const char* ssid = "Strategic Vision";
const char* password = "Oman2040";


void setup() {
  Serial.begin(115200); 

  // Initialize the GPIO pins to be inputs
  pinMode(parking_1_sensor, INPUT);
  pinMode(parking_2_sensor, INPUT);
  pinMode(parking_3_sensor, INPUT);
  pinMode(parking_4_sensor, INPUT);
  setupWiFi();
  setupRoutes();

  // this is used to get the epoch timestamp
  timeClient.begin();
  timeClient.setTimeOffset(28800);

  //Wire.begin(I2C_SDA, I2C_SCL);
  // initialize screen and intro here
  //lcd.begin(16,2);
  lcd.init(); // initialize the lcd
  lcd.backlight();

  //***** SD card initializations *****
  if(!SD.begin(CHIP_SELECT_PIN)){
        Serial.println("Card Mount Failed");
        //return;
  }
  uint8_t cardType = SD.cardType();
  if(cardType == CARD_NONE){
        Serial.println("No SD card attached");
        //return;
  }
  uint64_t cardSize = SD.cardSize() / (1024 * 1024);
  Serial.printf("SD Card Size: %lluMB\n", cardSize);
  writeFile(SD, "/data.txt", "");

  // print quick setup message as an intro
  lcd.clear();
  lcd.setCursor(5, 0);
  lcd.print("WELCOME");
  delay(2000);
  lcd.setCursor(1, 1);
  lcd.print("Parking Counter");
  delay(3000);
  lcd.clear();

}

void loop() {
  // handles incoming HTTP requests from client
  server.handleClient();

  // read all the sensor and update global vars
  read_sensors_and_update_values();
  // update the lcd screen with the new values
  update_lcd_screen();
  // do a small delay between each set - not needed 
  // we do not want things to break. "safety"

  //let the system breathe
  delay(50);

  counter_for_sending_data_to_sd_card += 1;
  // 300 equates to update every 15 seconds (but it is really 30-45 sec)
  if(counter_for_sending_data_to_sd_card == 300)
  { 
    // this is used to get the epoch time stamp
    timeClient.update();
    unsigned long epochTime = timeClient.getEpochTime();
    //get the epoch time stamp good with portland oregon time
    epochTime -= 25200;
    //reset the counter
    counter_for_sending_data_to_sd_card = 0;
    //pass the data available and write it to the sd card
    String data = String(epochTime) + "," + String(total_empty_spots) + "," + String(total_full_spots) + "\n";
    const char * data_as_const_char = data.c_str();
    appendFile(SD, "/data.txt", data_as_const_char);
  }
}
 
void read_sensors_and_update_values() {
  // a million ways to do this
  // i think this might be the easiest

  // go ahead set all the values to be 0 
  // and then we will scan each sensor again
  spot1 = 0;
  spot2 = 0;
  spot3 = 0;
  spot4 = 0;
 
  // read all sensors 
  if (digitalRead(parking_1_sensor) == 0) 
  {
    spot1 = 1;
  }
  if (digitalRead(parking_2_sensor) == 0) 
  {
    spot2 = 1;
  }
  if (digitalRead(parking_3_sensor) == 0) 
  {
    spot3 = 1;
  }
  if (digitalRead(parking_4_sensor) == 0) 
  {
    spot4 = 1;
  }

  //update the total values
  total_full_spots = spot1 + spot2 + spot3 + spot4;
  total_empty_spots = total_spots_in_parking - total_full_spots;


}

void update_lcd_screen() {
  // update lcd screen here.
  //clear screen 
  lcd.clear();
  //set the cursor in the top left corner
  lcd.setCursor(0,0);
  //print the following to show everything 
  lcd.print("Empty parking: ");
  lcd.print(total_empty_spots);

  // set the cursor in the bottom left corner
  lcd.setCursor(0,1);
  //print the following
  lcd.print("full parking: ");
  lcd.print(total_full_spots);

}

void setupWiFi() {
  // this connects the esp32 to the wifi network of our choice
  WiFi.begin(ssid, password);

  // this is a while loop that will wait and not move
  // until it connects to the network
  while (WiFi.status() != WL_CONNECTED) {
    //check every half a sec
    delay(500);
    Serial.println("Connecting to WiFi...");
  }

  Serial.println("Connected to WiFi");
  //display the ip we will use to access the webpage
  Serial.println(WiFi.localIP());
}

void setupRoutes() {
  // this function will read the html contents of index.h 
  // it will also send a request as well
  server.on("/", handleRoot);      //This is display page

  //this will call a function which passes 
  // the amount of empty spots in the parking 
  // lot to  
  server.on("/readADC", handleADC);

  //it will begin the web server 
  server.begin();
  Serial.println("HTTP server started");
}

void handleRoot() {
 String s = MAIN_page; //Read HTML contents
 server.send(200, "text/html", s); //Send web page
}
 
void handleADC() {

 String empty_spaces = String(total_empty_spots); //change format of data
 server.send(200, "text/plane", empty_spaces); //Send data in
}

// *********************** THESE functions are for SD card reader ***********************
void listDir(fs::FS &fs, const char * dirname, uint8_t levels){
    Serial.printf("Listing directory: %s\n", dirname);

    File root = fs.open(dirname);
    if(!root){
        Serial.println("Failed to open directory");
        return;
    }
    if(!root.isDirectory()){
        Serial.println("Not a directory");
        return;
    }

    File file = root.openNextFile();
    while(file){
        if(file.isDirectory()){
            Serial.print("  DIR : ");
            Serial.println(file.name());
            if(levels){
                listDir(fs, file.path(), levels -1);
            }
        } else {
            Serial.print("  FILE: ");
            Serial.print(file.name());
            Serial.print("  SIZE: ");
            Serial.println(file.size());
        }
        file = root.openNextFile();
    }
}

void createDir(fs::FS &fs, const char * path){
    Serial.printf("Creating Dir: %s\n", path);
    if(fs.mkdir(path)){
        Serial.println("Dir created");
    } else {
        Serial.println("mkdir failed");
    }
}

void removeDir(fs::FS &fs, const char * path){
    Serial.printf("Removing Dir: %s\n", path);
    if(fs.rmdir(path)){
        Serial.println("Dir removed");
    } else {
        Serial.println("rmdir failed");
    }
}

void readFile(fs::FS &fs, const char * path){
    Serial.printf("Reading file: %s\n", path);

    File file = fs.open(path);
    if(!file){
        Serial.println("Failed to open file for reading");
        return;
    }

    Serial.print("Read from file: ");
    while(file.available()){
        Serial.write(file.read());
    }
    file.close();
}

void writeFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Writing file: %s\n", path);

    File file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }
    if(file.print(message)){
        Serial.println("File written");
    } else {
        Serial.println("Write failed");
    }
    file.close();
}

void appendFile(fs::FS &fs, const char * path, const char * message){
    Serial.printf("Appending to file: %s\n", path);

    File file = fs.open(path, FILE_APPEND);
    if(!file){
        Serial.println("Failed to open file for appending");
        return;
    }
    if(file.print(message)){
        Serial.println("Message appended");
    } else {
        Serial.println("Append failed");
    }
    file.close();
}

void renameFile(fs::FS &fs, const char * path1, const char * path2){
    Serial.printf("Renaming file %s to %s\n", path1, path2);
    if (fs.rename(path1, path2)) {
        Serial.println("File renamed");
    } else {
        Serial.println("Rename failed");
    }
}

void deleteFile(fs::FS &fs, const char * path){
    Serial.printf("Deleting file: %s\n", path);
    if(fs.remove(path)){
        Serial.println("File deleted");
    } else {
        Serial.println("Delete failed");
    }
}

void testFileIO(fs::FS &fs, const char * path){
    File file = fs.open(path);
    static uint8_t buf[512];
    size_t len = 0;
    uint32_t start = millis();
    uint32_t end = start;
    if(file){
        len = file.size();
        size_t flen = len;
        start = millis();
        while(len){
            size_t toRead = len;
            if(toRead > 512){
                toRead = 512;
            }
            file.read(buf, toRead);
            len -= toRead;
        }
        end = millis() - start;
        Serial.printf("%u bytes read for %u ms\n", flen, end);
        file.close();
    } else {
        Serial.println("Failed to open file for reading");
    }


    file = fs.open(path, FILE_WRITE);
    if(!file){
        Serial.println("Failed to open file for writing");
        return;
    }

    size_t i;
    start = millis();
    for(i=0; i<2048; i++){
        file.write(buf, 512);
    }
    end = millis() - start;
    Serial.printf("%u bytes written for %u ms\n", 2048 * 512, end);
    file.close();
}
// ************************************************************************

//**************code that might come in handy later *************
  // server.on("/", HTTP_GET, []() {
  
  //   String html = "<html><body>";
  //   html += "<h1>Parking Status</h1>";
  //   html += "<p>Current date and time: </p>";
  //   html += "<p>Empty parking: " + String(total_empty_spots) + "</p>";
  //   html += "<p>Full parking: " + String(total_full_spots) + "</p>";
  //   html += "</body></html>";

  //   server.send(200, "text/html", html);
  // });


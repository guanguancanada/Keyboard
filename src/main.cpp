#include <Keypad.h>
#include <Keyboard.h>
#include <Mouse.h>
#include <EEPROM.h>

// OLED
#include <SPI.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>

// RGB
#include <FastLED.h>

// #include <HID-Project.h>

// Customize value 
#define WHEEL_DOWN 0xEE // Mouse wheel down
#define WHEEL_UP 0xEF   // Mouse wheel up



const byte ROWS = 4; //2 rows
const byte COLS = 4; //3 columns


char keys[ROWS][COLS] = {
  {'a', 'b', 'c', 'd'},
  {'e', 'f', 'g', 'h'},
  {'i', 'j', 'k', 'l'},
  {'m', 'n', 'o', 'p'}
}; 

int layerLeds[4][3] = {
  {20, 19, 18},
  {17, 16, 15},
  {14, 13, 12},
  {10,  9,  8}
};



//Create an object of keypad
byte rowPins[ROWS] = {18,19,20,21};    //connect to the row pinouts of the keypad
byte colPins[COLS] = {10,16,14,15}; //connect to the column pinouts of the keypad
Keypad keypad = Keypad(makeKeymap(keys), rowPins, colPins, ROWS, COLS);


// #define TEST true

#ifdef TEST
  int LAYERS = 2;
#endif

#ifndef TEST
  int LAYERS;
#endif


int LAYERS_ADDR = 1020;
int KEYS_PER_LAYER_ADDR = 1021;
int COMMANDS_PER_KEY_ADDR = 1022;

// Test data for key configuration, to reduce write EEPROM during test
#ifdef TEST
  #define ARRAY_SIZE 280//420
  int ramCommandArray[ARRAY_SIZE] = {};
  const int testCommandArray[ARRAY_SIZE] PROGMEM =
      {
          // layer 1
          // row 0
          2, 130, 91, 255, 255,//a
          2, 130, 93, 255, 255,
          2, 131, 98, 255, 255,
          241, 255, 255, 255, 255,//d
          
          // row1
          1, 32, 255, 255, 255,//e
          2, 131, 99, 255, 255,//f
          3, 131, 129, 118, 255,//g
          242, 242, 255, 255, 255,//h

          // row 2
          3, 131, 130, 218, 255, 
          3, 131, 130, 217, 255, 
          1, 178, 255, 255, 255, 
          240, 255, 255, 255, 255,//l
          
          // row3
          2, 130, 91, 255, 255,//m
          2, 130, 93, 255, 255,
          2, 131, 98, 255, 255,
          2, 129, 122, 255, 255, // 

          //EC1
          2, 129, 239, 255, 255,//q 
          2, 129, 238, 255, 255,
          2, 131, 215, 255, 255,
          2, 131, 216, 255, 255, 
          //EC2

          2, 128, 61, 255, 255,//u
          2, 128, 45, 255, 255,  
          1, 50, 255, 255, 255,
          1, 51, 255, 255, 255,
          // EC3
          2, 131, 61, 255, 255,// y
          2, 131, 45, 255, 255,//z
          1, 67, 255, 255, 255,
          1, 68, 255, 255, 255,


          // layer 2
          // row 0
          2, 130, 91, 255, 255,//a
          2, 130, 93, 255, 255,
          2, 131, 98, 255, 255,
          240, 255, 255, 255, 255,
          
          // row1
          241, 255, 255, 255, 255,//e
          242, 255, 255, 255, 255,//f
          243, 255, 255, 255, 255,//g
          3, 131, 129, 118, 255,//h

          // row 2
          2, 128, 45, 255, 255,//i
          2, 131, 215, 255, 255,
          2, 131, 216, 255, 255,
          240, 255, 255, 255, 255,//l
          
          // row3
          2, 130, 91, 255, 255,//m
          2, 130, 93, 255, 255,
          2, 131, 98, 255, 255,
          240, 255, 255, 255, 255,// x

          //EC1
          2, 129, 239, 255, 255,//q 
          2, 129, 238, 255, 255,
          2, 131, 61, 255, 255,
          2, 131, 45, 255, 255,
          //EC2
          1, 52, 255, 255, 255,//u 
          1, 53, 255, 255, 255,
          1, 54, 255, 255, 255,
          1, 55, 255, 255, 255,
          // EC3
          1, 69, 255, 255, 255,// y
          1, 70, 255, 255, 255,// z
          1, 71, 255, 255, 255,
          1, 72, 255, 255, 255
          // ,

          
          // layer3
          // 2, 130, 91, 255, 255,//a
          // 2, 130, 93, 255, 255,
          // 2, 131, 98, 255, 255,
          // 241, 255, 255, 255, 255,//d
          
          // // row1
          // 1, 32, 255, 255, 255,//e
          // 2, 131, 99, 255, 255,//f
          // 3, 131, 129, 118, 255,//g
          // 242, 242, 255, 255, 255,//h

          // // row 2
          // 3, 131, 130, 218, 255, 
          // 3, 131, 130, 217, 255, 
          // 1, 178, 255, 255, 255, 
          // 240, 255, 255, 255, 255,//l
          
          // // row3
          // 2, 130, 91, 255, 255,//m
          // 2, 130, 93, 255, 255,
          // 2, 131, 98, 255, 255,
          // 2, 129, 122, 255, 255, // 

          // //EC1
          // 2, 129, 239, 255, 255,//q 
          // 2, 129, 238, 255, 255,
          // 2, 131, 215, 255, 255,
          // 2, 131, 216, 255, 255, 
          // //EC2

          // 2, 128, 61, 255, 255,//u
          // 2, 128, 45, 255, 255,  
          // 1, 50, 255, 255, 255,
          // 1, 51, 255, 255, 255,
          // // EC3
          // 2, 131, 61, 255, 255,// y
          // 2, 131, 45, 255, 255,//z
          // 1, 67, 255, 255, 255,
          // 1, 68, 255, 255, 255
  };

#endif

#define LOGO_HEIGHT 24
#define LOGO_WIDTH 16

#define ICON_HEIGHT 16
#define ICON_WIDTH 16

const unsigned char blankImg [] PROGMEM = {
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,
  0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF,0xFF};

const unsigned char caps_lock_on [] PROGMEM = {
  0xFF,0xFF,0x80,0x01,0x80,0x01,0x81,0x81,0x82,0x41,0x84,0x21,0x88,0x11,0x88,0x11,
  0x88,0x11,0x88,0x11,0x8F,0xF1,0x88,0x11,0x88,0x11,0x80,0x01,0x80,0x01,0xFF,0xFF};

const unsigned char caps_lock_off [] PROGMEM = {
  0xFF,0xFF,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x80,0x01,0x83,0x81,0x80,0x41,
  0x80,0x41,0x83,0xC1,0x84,0x41,0x83,0xC1,0x80,0x01,0x80,0x01,0x80,0x01,0xFF,0xFF};


const unsigned char num_lock_on [] PROGMEM = {
  0xFF,0xFF,0x80,0x01,0x80,0x01,0x8F,0xF1,0x88,0x01,0x88,0x01,0x88,0x01,0x8F,0xE1,
  0x80,0x11,0x80,0x11,0x80,0x11,0x88,0x11,0x87,0xE1,0x80,0x01,0x80,0x01,0xFF,0xFF};

const unsigned char num_lock_off [] PROGMEM = {
  0xFF,0xFF,0x81,0x01,0x82,0x81,0x85,0x41,0x81,0x01,0x91,0x09,0xA0,0x05,0xDC,0x3B,
  0xA0,0x05,0x90,0x09,0x81,0x01,0x81,0x01,0x85,0x41,0x82,0x81,0x81,0x01,0xFF,0xFF};


int CHANGE_LAYER = 0xF0;    // Change layer
int EC1_CHANGE_MODE = 0xF1; //  EC1_CHANGE_MODE 241
int EC2_CHANGE_MODE = 0xF2; //   EC2_CHANGE_MODE 242
int EC3_CHANGE_MODE = 0xF3; //  EC3_CHANGE_MODE 243
int EC4_CHANGE_MODE = 0xF4; //   EC4_CHANGE_MODE 244

boolean initLoad = true;
boolean Caps_Lock;
boolean Num_Lock;
boolean Caps_Lock2;
boolean Num_Lock2;

unsigned long lastECTime = 0;    //millis();
unsigned long currentECTime = 0; //millis();
int ECSpeed = 0;

int ECModeLayer0 = 0;
int ECModeLayer1 = 0;
int ECModeLayer2 = 0;
int ECModeLayer3 = 0;
int currentLayer = 0;

int EC1Ring = 0;
int dirValue = 0;
int EC1ModeLayerArray[4] = {0,0,0,0};
int EC2ModeLayerArray[4] = {0,0,0,0};
int EC3ModeLayerArray[4] = {0,0,0,0};

int counter1 = 0;        
int currentStateClock1;  
int lastStateClock1;     
String currentDir1 = ""; 

int counter2 = 0;                    
int currentStateClock2;             
int lastStateClock2;                
String currentDir2 = "";             

int counter3 = 0;                   
int currentStateClock3;             
int lastStateClock3;                 
String currentDir3 = "";   

String COMMAND;
int READ_DATA_CMD = 0;

const int BUFFER_SIZE = 5;
char buf[BUFFER_SIZE];

// keyboard setting, using keypad.h col to row



// Rotary Encoder Inputs
#define Data1 6  //Data pin connected to D2
#define Clock1 7 //Clock pin connected to D3

#define Data2 8    //Data pin connected to D2
#define Clock2 9   //Clock pin connected to D3

#define Data3 4    //Data pin connected to D2
#define Clock3 5   //Clock pin connected to D3// data transfer flags

int runningMode = 0;
int datalength = 0;

int MACRO_LENGTH; // Command length, cmd1, cmd2,cmd3, cmd4
int KEY_PER_LAYER;



// OLED setting
#define OLED_RESET -1 // SSD1306 OLED default soft reset , no pin use
#define SCREEN_WIDTH 128    // OLED display width, in pixels
#define SCREEN_HEIGHT 32    // OLED display height, in pixels
#define SCREEN_ADDRESS 0x3C ///< See datasheet for Address; 0x3D for 128x64, 0x3C for 128x32
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

int screenTimeout = 0;
boolean screenStatus = true; 

// RGB LED pin
#define NUM_LEDS 21
#define DATA_PIN 1
CRGB leds[NUM_LEDS];


/* 
  Functions.
*/
void log(String info)
{
  #ifdef TEST
    if (TEST){
      display.setCursor(0, 16);
      int infoLength = info.length();
      if(infoLength < 32){
        for (int i = infoLength; i < 32; i ++){
          info = info + " ";
        }
      }
      display.println(info);
      display.display();
    }
  #endif
}

void processSerialRead(int currentLayerNumber, int h_addr, int l_addr)
{
  int size = h_addr * 128 + l_addr;
  int startAddress = currentLayerNumber * KEY_PER_LAYER * MACRO_LENGTH;
  int endAddress = startAddress + size;
  delay(100);

  for (int i = startAddress; i < endAddress; i++)
  {
    #ifdef TEST
      int value = ramCommandArray[i];
    #endif

    #ifndef TEST
      int value = EEPROM.read(i);
    #endif
  
    Serial.write(value);
    delay(20);
  }
}

void processSerialWrite(int h_addr, int l_addr, int value)
{
  int address = h_addr * 128 + l_addr;
  delay(10);
    #ifdef TEST
      ramCommandArray[address] = value;
    #endif

    #ifndef TEST
      EEPROM.update(address, value);
    #endif
}

void processReadKeyboardInfo(int h_addr, int l_addr)
{ 
  delay(100);
  for (int i = 1020; i < 1024; i++)
  {
    int value = EEPROM.read(i);
    Serial.write(value);
    delay(20);
  }
}

void displayLayer(int layer)
{
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(2);
  display.setCursor(4, 18);
  display.println(String(layer + 1));
  display.display();
  display.setTextSize(1);

  // for(int i = 0; i < LAYERS; i ++){
  //   if(i != layer){
  //     leds[i] = CRGB(0, 0, 0);
  //   }
  // }

  // leds[layer] = CRGB(255, 0, 0);
  // FastLED.show();

  int currentLayerLeds[3] ;

  // String ss = "";
  for(int i = 0; i < 21; i++){
    leds[i] = CRGB(0, 0, 0);
  }
   FastLED.show();
  for(int i = 0; i < 3; i++){
    currentLayerLeds[i] = layerLeds[layer][i];
    leds[currentLayerLeds[i]] = CRGB(255, 0, 0);
    // ss = ss + String(currentLayerLeds[i]) + ",";
  }
  // log(ss);
  FastLED.show();

}

void showInfo(int x, int y, String str, boolean show){
    display.setCursor(x, y);
    display.print(str);
    if(show){
      display.display();
    }
}


void updateECMode(int EC_CHANGE_MODE, int ECModeValueByLayer, boolean show ){
  int x = 84 + (EC_CHANGE_MODE - 241) * 16;
  showInfo(x, 20, String(ECModeValueByLayer), show);
}


void changeLayer()
{
  if (currentLayer < LAYERS)
  {
    currentLayer = currentLayer + 1;
    if (currentLayer == LAYERS)
    {
      currentLayer = 0;
    }

    displayLayer(currentLayer);
    updateECMode(EC1_CHANGE_MODE, EC1ModeLayerArray[currentLayer], false);
    updateECMode(EC2_CHANGE_MODE, EC2ModeLayerArray[currentLayer],false);
    updateECMode(EC3_CHANGE_MODE, EC3ModeLayerArray[currentLayer], true);
  }
}

void drawbitmap(const uint8_t bitmap[])
{
  display.clearDisplay();

  display.drawBitmap(
      (display.width() - LOGO_WIDTH) / 2,
      (display.height() - LOGO_HEIGHT) / 2,
      bitmap, LOGO_WIDTH, LOGO_HEIGHT, 1);
  display.display();
  delay(1000);
}

void activeOLED(){
    screenTimeout = 0;
    if(screenStatus == false){
      display.ssd1306_command(SSD1306_DISPLAYON); 
      screenStatus = true;
    }
}

void drawIcon(int x, int y, String status, const uint8_t bitmap_on[], const uint8_t bitmap_off[] )
{
  activeOLED();
  display.drawBitmap(x, y, blankImg, ICON_WIDTH, ICON_HEIGHT, 0);
 
  if(status == "1"){
      display.drawBitmap(x, y, bitmap_on, ICON_WIDTH, ICON_HEIGHT, 1);
  }else{
      display.drawBitmap(x, y, bitmap_off, ICON_WIDTH, ICON_HEIGHT, 1);
  }
  display.display();
}

void dispLedStatus(int x, int y, String str){
  display.setTextColor(WHITE, BLACK);
  display.setTextSize(2);
  display.setCursor(x, y);
  display.println(str);
  display.display();
  display.setTextSize(1);
}

void checkLedStatus()
{

  Caps_Lock = Keyboard.getLedStatus(LED_CAPS_LOCK);
  Num_Lock = Keyboard.getLedStatus(LED_NUM_LOCK);

  if(initLoad){
    Caps_Lock2 = !Caps_Lock;
    Num_Lock2 = !Num_Lock;
    initLoad = false;
  }
  if (Caps_Lock2 != Caps_Lock){
    String status = Caps_Lock ? "1" : "0";
    drawIcon(28, 16, status, caps_lock_on, caps_lock_off);
    Caps_Lock2 = Caps_Lock;
  }

  if (Num_Lock2 != Num_Lock){
    String status = Num_Lock ? "1" : "0";
    drawIcon(52, 16, status, num_lock_on, num_lock_off);
    
    Num_Lock2 = Num_Lock;
  }
}

void checkSerialPort()
{
  if (Serial.available()){
    int rlen = Serial.readBytes(buf, BUFFER_SIZE);
    if (buf[rlen - 1] == 0x0A){
      if (buf[0] == 114){ // Ascii('r') = 114
        processSerialRead(buf[1], buf[2], buf[3]);
      }else if (buf[0] == 119){                                             // Ascii('w') = 119
        processSerialWrite(buf[1], buf[2], buf[3]); // address:value
      }else if (buf[0] == 103){                                          // Ascii ('g') = 103
        processReadKeyboardInfo(buf[1], buf[2]); // address:
      }
    }else{
      String cmd = "";
      for (int i = 0; i < rlen; i++){
        cmd = cmd + String(buf[i]) + " ";
      }
    }
  }
};

void showRainbow(){

  uint8_t thisSpeed = 10;
  uint8_t deltaHue= 10;
  uint8_t thisHue = beat8(thisSpeed,255); 
  fill_rainbow(leds, NUM_LEDS, thisHue, deltaHue);            
  FastLED.show();
}


void initRGB(){
  FastLED.addLeds<NEOPIXEL, DATA_PIN>(leds, NUM_LEDS);
  // showRainbow();

  delay(1000);

  for (int i = 7; i >= 0; i--){
    leds[i] = CRGB(0, 0, 0);
    // FastLED.show();
  }

  leds[0] = CRGB::Red;
  FastLED.show();

  display.clearDisplay();

  showInfo(8,0,"L", false);
  showInfo(32,0,"C", false);
  showInfo(56,0,"N", false);

  showInfo(84,0,"R1", false);
  showInfo(100,0,"R2", false);
  showInfo(116,0,"R3", false);

  displayLayer(0);// power on default layer = 0;

  updateECMode(EC1_CHANGE_MODE, EC1ModeLayerArray[currentLayer], false);
  updateECMode(EC2_CHANGE_MODE, EC2ModeLayerArray[currentLayer],false);
  updateECMode(EC3_CHANGE_MODE, EC3ModeLayerArray[currentLayer], true);
};





void initOLED()
{
  if (!display.begin(SSD1306_SWITCHCAPVCC, SCREEN_ADDRESS))
  {
    // Serial.println("SSD1306 allocation failed");
  }
  else
  {

    display.begin(SSD1306_SWITCHCAPVCC, 0x3C); //turning on the oled
    display.clearDisplay();
    display.setTextColor(WHITE, BLACK);
    display.setTextSize(2);
    display.setCursor(14, 0);
    display.println(" Smart  ");
    display.setCursor(14, 16);
    display.print("Keyboard");
    display.display();
    display.setTextSize(1);
    delay(200);
  }
};



void loadConfig()
{
    #ifdef TEST
      LAYERS = 2;
    #endif

    #ifndef TEST
      LAYERS = EEPROM.read(LAYERS_ADDR);
    #endif

  MACRO_LENGTH = EEPROM.read(COMMANDS_PER_KEY_ADDR);
  KEY_PER_LAYER = EEPROM.read(KEYS_PER_LAYER_ADDR);
};

void initPins()
{
  // EC pins
  pinMode(Clock1, INPUT_PULLUP);
  pinMode(Data1, INPUT_PULLUP);
  lastStateClock1 = digitalRead(Clock1);
  
  pinMode(Clock2, INPUT_PULLUP);
  pinMode(Data2, INPUT_PULLUP);
  lastStateClock2 = digitalRead(Clock2);

  pinMode(Clock3, INPUT_PULLUP);
  pinMode(Data3, INPUT_PULLUP);
  lastStateClock3 = digitalRead(Clock3);
  // RGB pin
  pinMode(DATA_PIN, OUTPUT);
};



void processEC(int address){
    activeOLED();

    #ifdef TEST
      int m_length = ramCommandArray[address];
    #endif

    #ifndef TEST
      int m_length = EEPROM.read(address);
    #endif   

    String cmd = "";
  
    if (m_length > 0 && m_length < 10){
      for (int i = 1; i <= m_length; i++){
        int cmd_address = address + i;

        #ifdef TEST
          int eeprom_val = ramCommandArray[cmd_address];
        #endif

        #ifndef TEST
          int eeprom_val = EEPROM.read(cmd_address);
        #endif

        cmd = cmd + String(eeprom_val) + ", ";

        if (eeprom_val == WHEEL_DOWN || eeprom_val == WHEEL_UP){
          if (eeprom_val == WHEEL_DOWN){
            Mouse.move(0, 0, -1);
          }
          if (eeprom_val == WHEEL_UP){
            Mouse.move(0, 0, 1);
          }
        }else{
          Keyboard.press(eeprom_val);
        }
      }
      delay(10);
      Keyboard.releaseAll();
    }
}


void setup()
{
  // Setup Serial Monitor
  Serial.begin(115200);
  Keyboard.begin();
  Mouse.begin();

  initPins();

  loadConfig();
    #ifdef TEST
      memcpy_P(ramCommandArray, testCommandArray, sizeof ramCommandArray);
    #endif

  // INIT OLED SSD1306
  initOLED();

  // INIT WS2812 REG LED
  initRGB();
}

void loop()
{
  if(screenTimeout < 6000){
    screenStatus = true;
    screenTimeout++;

  }else{
    screenStatus = false;
    display.ssd1306_command(SSD1306_DISPLAYOFF); 
  }

  checkLedStatus();

  checkSerialPort();

  char key = keypad.getKey(); // Read the keys
  if (key)
  {

    activeOLED();

    int keyValue = key - 'a';
    int address = currentLayer * MACRO_LENGTH * KEY_PER_LAYER + keyValue * MACRO_LENGTH;

    #ifdef TEST
      int m_length = ramCommandArray[address];
    #endif

    #ifndef TEST
      int m_length = EEPROM.read(address);
    #endif

    if (m_length < 0){
      m_length = 256 + m_length;
    } 
  
    if (m_length > 0 && m_length < 10) {
      for (int i = 1; i <= m_length; i++){
        int cmd_address = address + i;

        #ifdef TEST
          int eeprom_val = ramCommandArray[cmd_address]; 
        #endif

        #ifndef TEST
          int eeprom_val = EEPROM.read(cmd_address);
        #endif

        Keyboard.press(eeprom_val);
      }
      delay(100);
      Keyboard.releaseAll();
    }else if (m_length == CHANGE_LAYER){
      changeLayer();
    } else if (m_length == EC1_CHANGE_MODE){
      if (EC1ModeLayerArray[currentLayer] == 0){
        EC1ModeLayerArray[currentLayer] = 1;
      } else{
        EC1ModeLayerArray[currentLayer] = 0;
      }
      updateECMode(EC1_CHANGE_MODE, EC1ModeLayerArray[currentLayer] ,true);
    }else if (m_length == EC2_CHANGE_MODE){
      if (EC2ModeLayerArray[currentLayer] == 0){
        EC2ModeLayerArray[currentLayer] = 1;
      } else{
        EC2ModeLayerArray[currentLayer] = 0;
      }
      updateECMode(EC2_CHANGE_MODE, EC2ModeLayerArray[currentLayer], true);
    }else if (m_length == EC3_CHANGE_MODE){
      if (EC3ModeLayerArray[currentLayer] == 0){
        EC3ModeLayerArray[currentLayer] = 1;
      } else{
        EC3ModeLayerArray[currentLayer] = 0;
      }  
      updateECMode(EC3_CHANGE_MODE, EC3ModeLayerArray[currentLayer], true);          
    }
  }

  
  // EC1
  currentStateClock1 = digitalRead(Clock1);
  if (currentStateClock1 != lastStateClock1 && currentStateClock1 == 1){
    
    // int dirValue = 0;
    if (digitalRead(Data1) != currentStateClock1){
      dirValue = 1;
      EC1Ring ++;
    }else{
      dirValue = 0;
      EC1Ring --;
    }
    if(EC1Ring < 0){
      EC1Ring = 80;
    }else if(EC1Ring > 80){
      EC1Ring = 0;
    }
    int ringValue = abs(EC1Ring/2 % 4);
 
    for (int i = 0; i < 4; i++){
      if (i != ringValue){
        leds[4 + i] = CRGB(0, 0, 0);
      }else{
        leds[4+ i] = CRGB::Blue;
      }
    }
    FastLED.show();

    key = 'q';
    int keyValue = key - 'a';
    int offset = 0;

    offset = (dirValue + EC1ModeLayerArray[currentLayer] * 2) * MACRO_LENGTH;

    int address = currentLayer * MACRO_LENGTH * KEY_PER_LAYER + keyValue * MACRO_LENGTH + offset;

    processEC(address);
  }

// EC2
  currentStateClock2 = digitalRead(Clock2);
  if (currentStateClock2 != lastStateClock2 && currentStateClock2 == 1)
  {
    if (digitalRead(Data2) != currentStateClock2){
      dirValue = 1;
    }else{
      dirValue = 0;
    }

    key = 'u';
    int keyValue = key - 'a';
    int offset = 0;

    offset = (dirValue + EC2ModeLayerArray[currentLayer] * 2) * MACRO_LENGTH;

    int address = currentLayer * MACRO_LENGTH * KEY_PER_LAYER + keyValue * MACRO_LENGTH + offset;
    processEC(address);
  }

// EC3
  currentStateClock3 = digitalRead(Clock3);
  if (currentStateClock3 != lastStateClock3 && currentStateClock3 == 1)
  {
    // int dirValue = 0;
    if (digitalRead(Data3) != currentStateClock3){
      dirValue = 1;
    }else{
      dirValue = 0;
    }

    key = 'y';
    int keyValue = key - 'a';
    int offset = 0;
    offset = (dirValue + EC3ModeLayerArray[currentLayer] * 2) * MACRO_LENGTH;

    int address = currentLayer * MACRO_LENGTH * KEY_PER_LAYER + keyValue * MACRO_LENGTH + offset;
    processEC(address);
  }

  // Save last Clock state for next loop
  lastStateClock1 = currentStateClock1;
  lastStateClock2 = currentStateClock2;
  lastStateClock3 = currentStateClock3;

  // Put in a slight delay to help debounce the reading
  delay(1);
}

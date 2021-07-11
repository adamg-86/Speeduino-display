/////////////////////////
// Seeeduino Xiao oled display for speeduino
// by Adam Gauthier
// 01/02/2021
////////////////////////


#include "comms.h"
#include "display.h"
#include "SDLogger.h"
#include "statuses.h"
#include "alarms.h"

bool Button();

//////// Buttons /////////
struct button {
  uint8_t pin;
  bool state;
  bool lastState;
};

struct button button1;
struct button button2;

bool flag = 0;

//// timed loop //////
uint long lastTime;

void setup()
{
  button1.pin = 1;
  button2.pin = 2;

  pinMode(button1.pin, INPUT_PULLUP);
  pinMode(button2.pin, INPUT_PULLUP);

  Serial1.begin(115200);
  // Serial.begin(115200); //  console Serial

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.display();
  delay(2000); // Pause for 2 seconds

  display.clearDisplay();

  noSDcard = !SD.begin(chipSelect);
  
}

void loop()
{
  sendComms('n');

  if (Serial1.available())
  {
    reciveComms('n');
  }

  convertData();

  if (Button(button1))
  {
    if (page % 2)
    {
      page++;
    }

    else
    {
      page += 2;
    }
  }

  if (Button(button2))
  {
    if (page % 2)
    {
      page--;
    }

    else
    {
      page++;
    }
  }

  if ((page > maxPage) && (page != 100))
  {
    page = 0;
  }

  if (Alarm())
  {
    if ((page != lastPage) && (page != 100))
      lastPage = page;
      
    page = 100;
  }


  display.clearDisplay();

  if (logFlag)
  {
    status.Time = (float)(millis() / 1000.0) ;
    SDlog();
    logging();
  }

  displayPage(page);

  delay(40); 
}

//////////Button short press function ///////////////// logic to avoid changing page if press for too long 
bool Button (button &Button)
{
  Button.state = digitalRead(Button.pin);
  bool flag = 0;

  if ((Button.state != Button.lastState) && (digitalRead(Button.pin) == 0))
  {
    flag = 1;
  }
  Button.lastState = Button.state;

  return flag;
}
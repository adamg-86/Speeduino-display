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

#include "bitmap.h"

bool Button();

//////// Buttons /////////
struct button {
  uint8_t pin;
  bool state;
  bool lastState;
};

struct button button1;
struct button button2;

long int loopTimer = 0;

//// flag for new data ////
bool newData = 0;

void setup()
{
  button1.pin = 1;
  button2.pin = 2;

  pinMode(button1.pin, INPUT_PULLUP);
  pinMode(button2.pin, INPUT_PULLUP);

  Serial1.begin(115200);
  //Serial.begin(115200); //  console Serial for debug

  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();

  // display startup Logo
  display.drawBitmap(0, 0, Miata, 128, 64, WHITE);
  display.display();
  delay(3000); // Pause for 3 seconds

  codeVersion = getVersion();
  codeVersion += ": SD Data Logger by Adam Gauthier \n\n";

  logNumber = LogNumberMem.read();
  pullNumber = PullNumberMem.read();

  display.clearDisplay();

  noSDcard = !SD.begin(chipSelect);
  
}

void loop()
{
  if ((millis() - loopTimer) >= 80) // 100ms = 10 hz 
  {
    loopTimer = millis();

    sendComms('n');

    if (Serial1.available())
    {
      reciveComms('n');
      newData = 1;
    }

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

    if (newData)
    {
      lastTime = status.Time;
      status.Time = (float)millis() / 1000.0 ;
      lastSpeed = status.VSSms;
      lastSpeedRPM = status.speedFromRPMms;
      display.clearDisplay();
      convertData();
      speedFromRPM();
      calculateHP();
      calculateCdA();

      ///// Debug////////////
      //Serial.println(status.TPS);

      if (logFlag)
      {
        SDlog(1);
        logging();
      }

      if (pullFlag)
      {
        SDlog(2);
        logging();
      }

      if (timerFlag)
      {
        zeroTo100();
      }

      displayPage(page);
    }

    Serial1.flush();
    newData = 0;
  }
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
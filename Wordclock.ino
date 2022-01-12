// This Code is a wordclock
// Original programmed by Sven Kruse

#include <WiFi.h>
#include <WiFiMulti.h>

#include <Adafruit_NeoPixel.h>

// Which pin on the Arduino is connected to the NeoPixels?
// On a Trinket or Gemma we suggest changing this to 1:
#define LED_PIN    15

// How many NeoPixels are attached to the Arduino?
#define LED_COUNT 99

// Declare our NeoPixel strip object:
Adafruit_NeoPixel strip(LED_COUNT, LED_PIN, NEO_GRB + NEO_KHZ800);
// Argument 1 = Number of pixels in NeoPixel strip
// Argument 2 = Arduino pin number (most are valid)
// Argument 3 = Pixel type flags, add together as needed:
//   NEO_KHZ800  800 KHz bitstream (most NeoPixel products w/WS2812 LEDs)
//   NEO_KHZ400  400 KHz (classic 'v1' (not v2) FLORA pixels, WS2811 drivers)
//   NEO_GRB     Pixels are wired for GRB bitstream (most NeoPixel products)
//   NEO_RGB     Pixels are wired for RGB bitstream (v1 FLORA pixels, not v2)
//   NEO_RGBW    Pixels are wired for RGBW bitstream (NeoPixel RGBW products)

//timedelay between every word while refreshing
const int delayTime = 1000 ;
const int refresh_time = 30000; //ping time in ms -> optimize to save power

byte hours;
byte minutes;

// Setting clock via ntp...
void setClock() {
  configTime(3600, 3600, "pool.ntp.org", "time.nist.gov"); //switzerland UTC+1, Daylight sayings time

  Serial.print(F("Waiting for NTP time sync: "));
  time_t nowSecs = time(nullptr);
  while (nowSecs < 8 * 3600 * 2) {
    delay(500);
    Serial.print(F("."));
    yield();
    nowSecs = time(nullptr);
  }

  Serial.println();
  struct tm timeinfo;
  gmtime_r(&nowSecs, &timeinfo);
  Serial.print(F("Current time: "));
  Serial.print(asctime(&timeinfo));
}


void setup() {
  
  Serial.begin(115200);

  strip.begin();           // INITIALIZE NeoPixel strip object (REQUIRED)
  strip.show();            // Turn OFF all pixels ASAP
  strip.setBrightness(100); // Set BRIGHTNESS to about 1/5 (max = 255)

  WiFi.mode(WIFI_STA);
  WiFi.begin("<ssid>", "<password>");
  Serial.print("Connecting to WiFi ..");
  while (WiFi.status() != WL_CONNECTED) {
    Serial.print('.');
    delay(1000);
  }
  
  Serial.println(WiFi.localIP());

  setClock();
     
}

void LED_clear() {
 for(int i=0; i<strip.numPixels(); i++) { // For each pixel in strip...
    strip.setPixelColor(i, strip.Color(0,   0,   0));         //  Set pixel's color (in RAM)
  }
  strip.show();                          //  Update strip to match
  
}

void loop() {

  struct tm timeinfo;
  if(!getLocalTime(&timeinfo)){
    Serial.println("Failed to obtain time");
    return;
  }
  Serial.println(&timeinfo, "%A, %B %d %Y %H:%M:%S");

  hours = timeinfo.tm_hour;
  minutes = timeinfo.tm_min;

if (hours >= 13) { // convert 24h settings in 12 h display mode by substracting 12
  hours = hours - 12;
}
    Serial.print(hours);
    Serial.print(":");
    Serial.print(minutes);
    Serial.print("->");

LED_clear();

//test_all(); // enable this to test all words before displaying the current time-> test will be done every refreshing cycle

es_ist();


  if (minutes >= 2 && minutes < 7) {
    fuenf_oben();
    nach();
  } else if (minutes >= 7 && minutes < 12) {
    zehn_oben();
    nach();
  } else if (minutes >= 12 && minutes < 17) {
    viertel();
    nach();

    //alternative without "nach();" for Badisch
    
  } else if (minutes >= 17 && minutes < 22) {
    zwanzig();
    nach();
  }else if(minutes >=22  && minutes < 27){
    fuenf_oben();
    vor();
    halb();    
  }else if (minutes >= 27 && minutes < 32) {
    halb();
  }else if(minutes >=32 && minutes < 37){
    fuenf_oben();
    nach();
    halb();
  } else if (minutes >= 37 && minutes < 42) {
    zwanzig();
    vor();
  } else if (minutes >= 42 && minutes < 47) {
    viertel();
    vor();

    //dreiviertel();
    
  } else if (minutes >= 47 && minutes < 52) {
    zehn_oben();
    vor();
  } else if ( minutes >= 52 && minutes < 57) {
    fuenf_oben();
    vor();
  }else if( minutes >=57 && minutes <2){
  uhr();
  } else {
// Else for condition failure
  }


//following lines represent the Hour-Display Conditions

  if (hours == 0 && minutes >= 57) {
   // eins();
    ein();
    uhr();
  
    }else if( hours == 0 && minutes > 22 && minutes < 57){
    eins();

}else if(hours ==1 && minutes <=2){
    ein();
    uhr();
    
} else if (hours == 1 && minutes <22 && minutes >= 2) {
    eins();
  
  }else if(hours == 1 &&  minutes >22){
    zwei();
  } else if (hours == 2 && minutes < 22) {
    zwei();
  } else if (hours == 2 && minutes >= 22) {
    drei();
  } else if (hours == 3 && minutes < 22) {
    drei();
  } else if (hours == 3 && minutes >= 22) {
    vier();
  } else if (hours == 4 && minutes <= 22) {
    vier();
  }else if( hours == 4 && minutes > 22){
     fuenf_unten();
  } else if (hours == 5 && minutes < 22) {
    fuenf_unten();
  } else if (hours == 5 && minutes >= 22) {
    sechs();
  } else if (hours == 6 && minutes < 22) {
    sechs();
  } else if (hours == 6 && minutes >= 22) {
    sieben();
  } else if (hours == 7 && minutes < 22) {
    sieben();
  } else if (hours == 7 && minutes >= 22) {
    acht();

  } else if (hours == 8 && minutes < 22) {
    acht();
  } else if (hours == 8 && minutes >= 22) {
    neun();
  } else if (hours == 9 && minutes < 22) {
    neun();
  } else if (hours == 9 && minutes >= 22) {
    zehn_unten();
  }else if( hours == 10 && minutes < 22){
    zehn_unten();
  } else if (hours == 10 && minutes >= 22) {
    elf();
  } else if (hours == 11 && minutes < 22) {
    elf();
  } else if (hours == 11 && minutes >= 22) {
    zwoelf();
  } else if (hours == 12 && minutes < 22) {
    zwoelf();
  } else if (hours == 12 && minutes >= 22) {
    eins();
    }else if(hours == 0 && minutes < 22){
      zwoelf();
      
    }

  delay(refresh_time);

}

void es_ist() {
  Serial.print("Es ist");
  int i = 0;
  strip.setPixelColor(i,strip.Color(255,   255,   255));//e
  strip.setPixelColor(i+1,strip.Color(255,   255,   255)); //s
  delay(delayTime);
  strip.setPixelColor(i + 3, strip.Color(255,   255,   255)); //i
  strip.setPixelColor(i + 4, strip.Color(255,   255,   255)); //s
  strip.setPixelColor(i + 5, strip.Color(255,   255,   255)); //t
  delay(delayTime);
  strip.show();
}


void fuenf_oben() {
  Serial.print(" fuenf");
  int i = 7;
  strip.setPixelColor(i, strip.Color(255,   255,   255));//F
  strip.setPixelColor(i + 1, strip.Color(255,   255,   255)); //ü
  strip.setPixelColor(i + 2, strip.Color(255,   255,   255)); //n
  strip.setPixelColor(i + 3, strip.Color(255,   255,   255)); //F
  delay(delayTime);
  strip.show();
}
void zehn_oben() {
  Serial.print(" zehn");
  int i = 18;
  strip.setPixelColor(i, strip.Color(255,   255,   255));//z
  strip.setPixelColor(i + 1, strip.Color(255,   255,   255)); //e
  strip.setPixelColor(i + 2, strip.Color(255,   255,   255)); //h
  strip.setPixelColor(i + 3, strip.Color(255,   255,   255)); //n
  delay(delayTime);
  strip.show();
}


void zwanzig() {
  Serial.print(" zwanzig");
  int i = 11;
  strip.setPixelColor(i, strip.Color(255,   255,   255));//z
  strip.setPixelColor(i + 1, strip.Color(255,   255,   255)); //w
  strip.setPixelColor(i + 2, strip.Color(255,   255,   255)); //a
  strip.setPixelColor(i + 3, strip.Color(255,   255,   255)); //n
  strip.setPixelColor(i + 4, strip.Color(255,   255,   255)); //z
  strip.setPixelColor(i + 5, strip.Color(255,   255,   255)); //i
  strip.setPixelColor(i + 6, strip.Color(255,   255,   255)); //g
  delay(delayTime);
  strip.show();
}

void dreiviertel() {
  Serial.print(" dreiviertel");
  int i = 22 ;
  strip.setPixelColor(i, strip.Color(255,   255,   255));//d
  strip.setPixelColor(i + 1, strip.Color(255,   255,   255)); //r
  strip.setPixelColor(i + 2, strip.Color(255,   255,   255)); //e
  strip.setPixelColor(i + 3, strip.Color(255,   255,   255)); //i
  strip.setPixelColor(i + 4, strip.Color(255,   255,   255)); //v
  strip.setPixelColor(i + 5, strip.Color(255,   255,   255)); //i
  strip.setPixelColor(i + 6, strip.Color(255,   255,   255)); //e
  strip.setPixelColor(i + 7, strip.Color(255,   255,   255)); //r
  strip.setPixelColor(i + 8, strip.Color(255,   255,   255)); //t
  strip.setPixelColor(i + 9, strip.Color(255,   255,   255)); //e
  strip.setPixelColor(i + 10, strip.Color(255,   255,   255)); //l
  delay(delayTime);
  strip.show();
}
void viertel() {
  Serial.print(" viertel");
  int i = 26;
  strip.setPixelColor(i, strip.Color(255,   255,   255));//
  strip.setPixelColor(i + 1, strip.Color(255,   255,   255)); //
  strip.setPixelColor(i + 2, strip.Color(255,   255,   255)); //
  strip.setPixelColor(i + 3, strip.Color(255,   255,   255)); //
  strip.setPixelColor(i + 4, strip.Color(255,   255,   255)); //
  strip.setPixelColor(i + 5, strip.Color(255,   255,   255)); //
  strip.setPixelColor(i + 6, strip.Color(255,   255,   255)); //
  delay(delayTime);
  strip.show();
}

void nach() {
  Serial.print(" nach");
  int i = 38 ; //h
  strip.setPixelColor(i, strip.Color(255,   255,   255));//
  strip.setPixelColor(i + 1, strip.Color(255,   255,   255)); //
  strip.setPixelColor(i + 2, strip.Color(255,   255,   255)); //
  strip.setPixelColor(i + 3, strip.Color(255,   255,   255)); //
  delay(delayTime);
  strip.show();
}

void vor() {
  Serial.print(" vor");
  int i = 35;
  strip.setPixelColor(i, strip.Color(255,   255,   255));//v
  strip.setPixelColor(i + 1, strip.Color(255,   255,   255)); //o
  strip.setPixelColor(i + 2, strip.Color(255,   255,   255)); //R
  delay(delayTime);
  strip.show();
}

void halb() {
  Serial.print(" halb");
  int i = 33;
  strip.setPixelColor(i, strip.Color(255,   255,   255));//h
  delay(delayTime);
  strip.show();
}

void zwoelf() {
  Serial.print(" zwoelf");
  zw();
  strip.setPixelColor(59, strip.Color(255,   255,   255));//ö
 strip.setPixelColor(60, strip.Color(255,   255,   255)); //L
 strip.setPixelColor(61, strip.Color(255,   255,   255));//f von fünf unten
 delay(delayTime);
   strip.show();
}

void zw() {
  int i = 44;//W
  strip.setPixelColor(i, strip.Color(255,   255,   255));
  strip.setPixelColor(i + 1, strip.Color(255,   255,   255));
}

void ei() {
  int i = 46;//i
  strip.setPixelColor(i, strip.Color(255,   255,   255));
  strip.setPixelColor(i + 1, strip.Color(255,   255,   255));
}
void n() {
    strip.setPixelColor(48, strip.Color(255,   255,   255));
}

void ein() {
 Serial.print(" ein");
 ei();
 n();
 delay(delayTime);
   strip.show();
}
void s() {
   strip.setPixelColor(49, strip.Color(255,   255,   255));
}

void eins() {
  Serial.print(" eins");
  ei();
  n();
  s();
  delay(delayTime);
  strip.show();
}
void zwei() {
  zw();
  ei();
  delay(delayTime);
  strip.show();
}

void sieben() {  
  Serial.print(" sieben");
  int i = 50; // eqal to n
  strip.setPixelColor(i, strip.Color(255,   255,   255));
  strip.setPixelColor(i + 1, strip.Color(255,   255,   255));
  strip.setPixelColor(i + 2, strip.Color(255,   255,   255));
  strip.setPixelColor(i + 3, strip.Color(255,   255,   255));
  strip.setPixelColor(i + 4, strip.Color(255,   255,   255));
  strip.setPixelColor(i + 5, strip.Color(255,   255,   255));
  delay(delayTime);
    strip.show();
}

void drei() {
  Serial.print(" drei");
  int i = 62;
  strip.setPixelColor(i, strip.Color(255,   255,   255));//d
  strip.setPixelColor(i + 1, strip.Color(255,   255,   255)); //r
  strip.setPixelColor(i + 2, strip.Color(255,   255,   255)); //e
  strip.setPixelColor(i + 3, strip.Color(255,   255,   255)); //i
  delay(delayTime);
  strip.show();
}

void fuenf_unten() {
  Serial.print(" fuenf");
  int i = 56;
  strip.setPixelColor(i, strip.Color(255,   255,   255));//f
  strip.setPixelColor(i + 1, strip.Color(255,   255,   255)); //ü
  strip.setPixelColor(i + 2, strip.Color(255,   255,   255)); //n
  strip.setPixelColor(i + 3, strip.Color(255,   255,   255)); //F
  delay(delayTime);
    strip.show();
}

void elf() {
  Serial.print(" elf");
  int i = 67;
  strip.setPixelColor(i, strip.Color(255,   255,   255));//e
  strip.setPixelColor(i + 1, strip.Color(255,   255,   255)); //l
  strip.setPixelColor(i + 2, strip.Color(255,   255,   255)); //f
  delay(delayTime);
    strip.show();
}


void neun() {
  Serial.print(" neun");
  int i =70;
  strip.setPixelColor(i, strip.Color(255,   255,   255));//n
  strip.setPixelColor(i + 1, strip.Color(255,   255,   255)); //e
  strip.setPixelColor(i + 2, strip.Color(255,   255,   255)); //u
  strip.setPixelColor(i + 3, strip.Color(255,   255,   255)); //n
  delay(delayTime);
}

void vier() {
  Serial.print(" vier");
  int i = 74;
  strip.setPixelColor(i, strip.Color(255,   255,   255));//v
  strip.setPixelColor(i + 1, strip.Color(255,   255,   255)); //i
  strip.setPixelColor(i + 2, strip.Color(255,   255,   255)); //e
  strip.setPixelColor(i + 3, strip.Color(255,   255,   255)); //r
  delay(delayTime);
    strip.show();
}

void acht() {
  Serial.print(" acht");
  int i = 84;
  strip.setPixelColor(i, strip.Color(255,   255,   255));//a
  strip.setPixelColor(i + 1, strip.Color(255,   255,   255)); //c
  strip.setPixelColor(i + 2, strip.Color(255,   255,   255)); //h
  strip.setPixelColor(i + 3, strip.Color(255,   255,   255)); //t
  delay(delayTime);
      strip.show();
}
void zehn_unten() {
  Serial.print(" zehn");
  int i = 80;
  strip.setPixelColor(i, strip.Color(255,   255,   255));
  strip.setPixelColor(i + 1, strip.Color(255,   255,   255));
  strip.setPixelColor(i + 2, strip.Color(255,   255,   255));
  strip.setPixelColor(i + 3, strip.Color(255,   255,   255));
  delay(delayTime);
      strip.show();
}

void sechs() {
  Serial.print(" sechs");
  int i = 90;
  strip.setPixelColor(i, strip.Color(255,   255,   255));
  strip.setPixelColor(i + 1, strip.Color(255,   255,   255));
  strip.setPixelColor(i + 2, strip.Color(255,   255,   255));
  strip.setPixelColor(i + 3, strip.Color(255,   255,   255));
  strip.setPixelColor(i + 4, strip.Color(255,   255,   255));
  delay(delayTime);
      strip.show();
}

void uhr() {
  Serial.print(" uhr");
  int i = 97;
  strip.setPixelColor(i, strip.Color(255,   255,   255));
  strip.setPixelColor(i + 1, strip.Color(255,   255,   255));
  strip.setPixelColor(i + 2, strip.Color(255,   255,   255));
  delay(delayTime);
      strip.show();
}

void test_all(){

  int t= 500;
es_ist();
delay(t);
zwoelf();
delay(t);
fuenf_oben();
delay(t);
halb();
delay(t);
zehn_oben();
delay(t);
zwanzig();
delay(t);
dreiviertel();
delay(t);
nach();
delay(t);
vor();
delay(t);
sieben();
delay(t);
zwei(); 
delay(t);
ein(); 
delay(t);
eins();
delay(t);
drei();
delay(t);
fuenf_unten();
delay(t);
elf();
delay(t);
neun();
delay(t);
vier();
delay(t);
acht();
delay(t);
zehn_unten();
delay(t);
sechs();
delay(t);
uhr();
delay(t*100);
LED_clear();
}

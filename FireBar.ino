//#include <Adafruit_NeoPixel.h>  // Library Manager > Adafruit NeoPixel Version >= 1.2.2
#include <WS2812FX.h>             // Library Manager > WS2812FX >= 1.1.9

//Led strip WS2812
#define WS2812PIN 3
#define WS2812PIXELS 100

//Lighting Mode
int speed = -10;

int potLightLevelLast = -10;
int potSpeedLast = -10;

//Light configuration
#define FIRE_START 0
#define FIRE_LENGTH 50

WS2812FX ws2812fx = WS2812FX(WS2812PIXELS, WS2812PIN, NEO_GRB + NEO_KHZ800);

void setup() {
	Serial.begin(115200);
	Serial.println("Start Elements light");
	ws2812fx.init();
	ws2812fx.setBrightness(1);
	ws2812fx.start();
}

void checkLightLevelPot() {
	int potLightLevel = analogRead(A1);
	potLightLevel = map(potLightLevel, 0, 960, 1, 255);
	//To avaoid flicker, only change level if +/-4 steps
	if ((potLightLevelLast-potLightLevel > 4) || (potLightLevelLast-potLightLevel < -4)) {
		Serial.print("Light level changed to ");
		Serial.println(potLightLevel);
		ws2812fx.setBrightness(potLightLevel);
		potLightLevelLast = potLightLevel;
	}

	int potSpeed = analogRead(A2);
	potSpeed = map(potSpeed, 0, 960, 1000, 10);
	//To avaoid flicker, only change speed if +/-4 steps
	if ((potSpeedLast-potSpeed > 4) || (potSpeedLast-potSpeed < -4)) {
		Serial.print("Speed changed to ");
		Serial.println(potSpeed);
		speed = potSpeed;
		potSpeedLast = potSpeed;
		changeMode();
	}
}

void changeMode() {
	Serial.println("Changed mode");
	ws2812fx.setSpeed(speed*14);
	ws2812fx.setColor(0xFF6600);
	ws2812fx.setMode(FX_MODE_FIRE_FLICKER_INTENSE);
}

void tick() {
	ws2812fx.service();
}

void loop() {
	checkLightLevelPot();
	tick();
	delay(20);
}

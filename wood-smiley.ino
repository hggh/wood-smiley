#include <CapacitiveSensor.h>
#include <FastLED.h>
#include <Bounce2.h>

#define PIN_LEDS 1
#define PIN_CAP_SEND_PIN 2
#define PIN_CAP_RECEIVE_PIN 3
#define PIN_BUTTOM_MODE 4
#define PIN_BUTTOM_VALUE 5

// #define DEBUG 0
#define LED_COUNT 10

const static CRGB::HTMLColorCode colors[35] = {
  CRGB::Crimson,
  CRGB::Red,
  CRGB::DarkRed,
  CRGB::DeepPink,
  CRGB::OrangeRed,
  CRGB::Orange,
  CRGB::Gold,
  CRGB::Yellow,
  CRGB::Violet,
  CRGB::Navy,
  CRGB::RosyBrown,
  CRGB::Fuchsia,
  CRGB::MediumOrchid,
  CRGB::BlueViolet,
  CRGB::Purple,
  CRGB::Indigo,
  CRGB::DarkSlateBlue,
  CRGB::GreenYellow,
  CRGB::Lime,
  CRGB::MediumSpringGreen,
  CRGB::ForestGreen,
  CRGB::DarkGreen,
  CRGB::LightSeaGreen,
  CRGB::Teal,
  CRGB::Cyan,
  CRGB::CadetBlue,
  CRGB::SteelBlue,
  CRGB::SkyBlue,
  CRGB::Blue,
  CRGB::DarkBlue,
  CRGB::Chocolate,
  CRGB::SaddleBrown,
  CRGB::Maroon,
  CRGB::DarkSlateGray,
  CRGB::Brown
};



CRGB leds[LED_COUNT];
CapacitiveSensor cap_sensor = CapacitiveSensor(PIN_CAP_SEND_PIN, PIN_CAP_RECEIVE_PIN);
CHSV hsv;
Bounce button_mode = Bounce();
Bounce button_value = Bounce();
uint8_t led_brightness = 30;

/*
 * set LED Brightness
 */
void set_led_brightness(uint8_t value) {
  led_brightness = value;
  FastLED.setBrightness(value);
}

/*
 * update all push Buttons
 */
void update_buttons() {
  button_mode.update();
  button_value.update();
}

/*
 * update Cap Sensor
 */
void update_cap_sensor() {
  long cap_value = cap.capacitiveSensor(30);
  // FIXME:---------------------------
}

void setup() {
#ifdef DEBUG
  Serial.begin(9600);
#endif
  FastLED.addLeds<WS2812, PIN_LEDS>(leds, LED_COUNT);
  FastLED.clear(true);

  hsv.hue = 1;
  hsv.val = 255;
  hsv.sat = 240;

  button_mode.attach(PIN_BUTTOM_MODE);
  button_mode.interval(5);

  button_value.attach(PIN_BUTTOM_VALUE);
  button_value.interval(5);
}

void loop() {
  update_buttons();
  update_cap_sensor();

}

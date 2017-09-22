#include <avr/power.h>
#include <FastLED.h>

#include "config.h"

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
volatile unsigned long show_smiley_time;
volatile unsigned short timer_runs;

void leds_clear() {
  FastLED.clear(true);
  FastLED.show();
}

void show_smiley() {
  if (! (micros() > show_smiley_time + 30)) {
    return;
  }
  CRGB::HTMLColorCode v;

  // the eyes
  v = colors[random(34)];
  leds[0] = v;
  leds[1] = v;

  // the nose
  v = colors[random(34)];
  leds[2] = v;
  leds[3] = v;

  // the mouth
  v = colors[random(34)];
  leds[4] = v;
  leds[5] = v;
  leds[6] = v;
  leds[7] = v;

  FastLED.setBrightness(led_brightness);
  FastLED.show();
  show_smiley_time = millis();

  cli();
  TCCR1A = 0;
  TCCR1B = 0;
  TCNT1  = 0;

  TCCR1B |= (1 << CS12) | (1 << CS10);
  TIMSK1 |= (1 << TOIE1);
  sei();
  timer_runs = 0;
}


void setup() {
  show_smiley_time = millis();

  power_adc_disable();
  power_twi_disable();
  power_spi_disable();
  power_timer2_disable();
  power_usart0_disable();

  randomSeed(analogRead(0));
  pinMode(PIN_MOTION, INPUT);

  attachInterrupt(digitalPinToInterrupt(PIN_MOTION), show_smiley, FALLING);

  FastLED.addLeds<PL9823, PIN_LEDS>(leds, LED_COUNT);
  FastLED.setBrightness(led_brightness);
  leds_clear();

}

ISR(TIMER1_OVF_vect) {
  TCNT1 = 0;
  timer_runs++;

  if (timer_runs > 3) {
    leds_clear();

    cli();
    TCCR1A = 0;
    TCCR1B = 0;
    sei();
  }
}

void loop() {
}

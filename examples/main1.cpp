/////////////////////////////////////////////////////////////////

#include "Button2.h"
#include <esp32_touch.hpp>


/////////////////////////////////////////////////////////////////

#define BUTTON_PIN  2

/////////////////////////////////////////////////////////////////

Button2 button = Button2(BUTTON_PIN);

/////////////////////////////////////////////////////////////////

// LED pin
constexpr uint8_t led_pin = 12;     // GPIO 2

// Touch button GPIO pins
constexpr int touch_io_off = 5;    // GPIO 12
constexpr int touch_io_on = 2;     // GPIO 13
constexpr int touch_io_toggle = 3; // GPIO 15

// Touch button touch detection threshold in percent of the
// calibration-time (i.e. idle-state) sensor readout value.
constexpr uint8_t touch_threshold = 92;

// Standard serial port setup
constexpr unsigned long serial_baudrate = 9600;

// Instantiate touch button driver
ESP32Touch buttons{};

// Define callback functions
void enable_led() {
  Serial.println("Switching ON the LED!");
  digitalWrite(led_pin, HIGH);
  //SINGLE_CLICK;
}
void disable_led() {
  Serial.println("Switching the LED off!");
  digitalWrite(led_pin, LOW);
}

/////////////////////////////////////////////////////////////////

void handler(Button2& btn) {
    switch (btn.getClickType()) {
        case SINGLE_CLICK:
            break;
        case DOUBLE_CLICK:
            Serial.print("double ");
            break;
        case TRIPLE_CLICK:
            Serial.print("triple ");
            break;
        case LONG_CLICK:
            Serial.print("long");
            break;
    }
    Serial.print("click");
    Serial.print(" (");
    Serial.print(btn.getNumberOfClicks());    
    Serial.println(")");
}
/////////////////////////////////////////////////////////////////

void setup() {
    // Enable serial output
  Serial.begin(serial_baudrate);
  // Setup LED GPIO pin
  pinMode(led_pin, OUTPUT);
  // Register above callback functions with the touch button driver
  buttons.configure_input(touch_io_on, touch_threshold, enable_led);
  buttons.configure_input(touch_io_off, touch_threshold, disable_led);
  // You can also directly register a lambda:
  buttons.configure_input(touch_io_toggle, touch_threshold, []() {
      Serial.println("Toggling the LED!");
      bool current_led_state = (bool)digitalRead(led_pin);
      digitalWrite(led_pin, !current_led_state);
  });
  // Call this once and you are done..
  buttons.begin();
  Serial.println("\n\nMulti Handler Demo");
  
  button.setClickHandler(handler);
  button.setLongClickHandler(handler);
  button.setDoubleClickHandler(handler);
  button.setTripleClickHandler(handler);
}

/////////////////////////////////////////////////////////////////

void loop() {
  button.loop();
}


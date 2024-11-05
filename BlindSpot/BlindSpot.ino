// Updated pin assignments
const int trigPin = 2;  // Ultrasonic sensor Trig pin
const int echoPin = 3;  // Ultrasonic sensor Echo pin
const int ledPin = 4;   // LED pin

// OLED display SPI pins (unchanged)
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_MOSI   11
#define OLED_CLK    13
#define OLED_CS     10
#define OLED_DC     9
#define OLED_RESET  8

#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <SPI.h>

const int distanceThreshold = 10;  // Distance threshold in cm for LED to turn on

// OLED display initialization
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &SPI, OLED_DC, OLED_RESET, OLED_CS);

void setup() {
  // Initialize Serial for debugging
  Serial.begin(9600);
  
  // Initialize pins
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(ledPin, OUTPUT);

  // Initialize OLED display
  if (!display.begin(SSD1306_SWITCHCAPVCC)) {
    Serial.println(F("SSD1306 allocation failed"));
    for(;;);  // Infinite loop if initialization fails
  }
  
  display.display();
  delay(2000);  // Pause for 2 seconds
  display.clearDisplay();  // Clear the OLED buffer
}

void loop() {
  // Variables for duration and distance calculation
  long duration, distance;
  
  // Trigger the ultrasonic sensor
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  
  // Read the echo time
  duration = pulseIn(echoPin, HIGH);
  
  // Calculate the distance (duration / 2) / 29.1
  distance = (duration / 2) / 29.1;

  // Display distance on Serial Monitor for debugging
  Serial.print("Distance: ");
  Serial.print(distance);
  Serial.println(" cm");

  // Display the distance on OLED
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 0);
  display.print("Distance: ");
  display.print(distance);
  display.println(" cm");
  display.display();

  // Control LED based on distance
  if (distance <= distanceThreshold && distance > 0) {
    digitalWrite(ledPin, HIGH);  // Turn on LED if within threshold
  } else {
    digitalWrite(ledPin, LOW);   // Turn off LED if outside threshold
  }
  
  delay(100);  // Small delay for stability
}

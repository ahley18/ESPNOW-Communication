#include <ESP8266WiFi.h>
#include <espnow.h>

#define BUTTON_PIN_16 16  // GPIO16
#define BUTTON_PIN_5  5   // GPIO5
#define BUTTON_PIN_4  4   // GPIO4
#define BUTTON_PIN_0  0   // GPIO0
#define BUTTON_PIN_2  2   // GPIO2
#define BUTTON_PIN_14 14  // GPIO14
#define BUTTON_PIN_12 12  // GPIO12
#define BUTTON_PIN_13 13  // GPIO13

// REPLACE WITH YOUR RECEIVER MAC Address
uint8_t broadcastAddress[] = { 0xEC, 0x64, 0xC9, 0xDC, 0xA1, 0x9C };

char myData[2]; // Array to hold the data to send
bool button16Pressed = false;  
bool button5Pressed = false;
bool button4Pressed = false;
bool button0Pressed = false;
bool button2Pressed = false;
bool button14Pressed = false;
bool button12Pressed = false;
bool button13Pressed = false;

// Callback function called when data is sent
void OnDataSent(uint8_t *mac_addr, uint8_t status) {
  Serial.print("\r\nLast Packet Send Status:\t");
  Serial.println(status == 0 ? "Delivery Success" : "Delivery Fail");
}

void setup() {
  // Init Serial Monitor
  Serial.begin(74880);

  // Set all GPIOs as inputs with pullup resistors
  pinMode(BUTTON_PIN_16, INPUT_PULLUP);
  pinMode(BUTTON_PIN_5, INPUT_PULLUP);
  pinMode(BUTTON_PIN_4, INPUT_PULLUP);
  pinMode(BUTTON_PIN_0, INPUT_PULLUP);
  pinMode(BUTTON_PIN_2, INPUT_PULLUP);
  pinMode(BUTTON_PIN_14, INPUT_PULLUP);
  pinMode(BUTTON_PIN_12, INPUT_PULLUP);
  pinMode(BUTTON_PIN_13, INPUT_PULLUP);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  } else {
    Serial.println("Initialized ESP-NOW");
  }

  // Register for Send Callback
  esp_now_set_self_role(ESP_NOW_ROLE_CONTROLLER);
  esp_now_register_send_cb(OnDataSent);

  // Add peer
  if (esp_now_add_peer(broadcastAddress, ESP_NOW_ROLE_SLAVE, 0, NULL, 0) != 0) {
    Serial.println("Failed to add peer");
    return;
  } else {
    Serial.println("Added peer");
  }

  if (esp_now_is_peer_exist(broadcastAddress)) {
    Serial.println("Peer exists");
  } else {
    Serial.println("No peer exists");
  }
}

void loop() {
  // Check the state of each button and send the appropriate message
  checkButtonState(BUTTON_PIN_16, button16Pressed, 'R');
  checkButtonState(BUTTON_PIN_5, button5Pressed, 'U');
  checkButtonState(BUTTON_PIN_4, button4Pressed, 'CO');
  checkButtonState(BUTTON_PIN_0, button0Pressed, 'D');
  checkButtonState(BUTTON_PIN_2, button2Pressed, 'CC');
  checkButtonState(BUTTON_PIN_14, button14Pressed, 'L');
  checkButtonState(BUTTON_PIN_12, button12Pressed, 'B');
  checkButtonState(BUTTON_PIN_13, button13Pressed, 'F');
}

void checkButtonState(int buttonPin, bool &buttonPressed, char message) {
  if (digitalRead(buttonPin) == LOW) {
    if (!buttonPressed) {  // Check if it was already pressed
      Serial.println(message);
      myData[0] = message;  // Set myData to the corresponding character
      buttonPressed = true;  // Mark as pressed
    }
    sendESPNowMessage();
    delay(10);  // Throttle the sending while holding the button
  } else {
    buttonPressed = false;  // Reset the pressed state when released
  }
}

void sendESPNowMessage() {
  // Send message via ESP-NOW
  int result = esp_now_send(broadcastAddress, (uint8_t *)myData, sizeof(myData));

  if (result == 0) {
    Serial.println("Sent with success");
  } else {
    Serial.println("Error sending the data");
  }
}

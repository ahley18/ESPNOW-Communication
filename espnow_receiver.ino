#include <ESP8266WiFi.h>
#include <espnow.h>

int in1 = 5;   //left forward
int in2 = 4;   //left back
int in3 = 14;  //right forward
int in4 = 16;  //right back

String receivedData = "O";  // Variable to store received data, default to "O"
unsigned long lastReceivedTime = 0;  // Timestamp of the last received data
unsigned long timeout = 10;  // Timeout in milliseconds

// Callback function that will be executed when data is received
void OnDataRecv(uint8_t *mac_addr, uint8_t *incomingData, uint8_t len) {
  char buffer[len + 1];  // Buffer to hold received data
  memcpy(buffer, incomingData, len);  // Copy received data into buffer
  buffer[len] = '\0';  // Null-terminate the string

  receivedData = String(buffer);  // Update the receivedData variable
  lastReceivedTime = millis();  // Reset the last received timestamp

  // Print the received data
  Serial.print("Received: ");
  Serial.println(receivedData);
}

void setup() {
  // Init Serial Monitor
  Serial.begin(74880);

  // Set GPIO 2 as an output (LED control pin)
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  // Set device as a Wi-Fi Station
  WiFi.mode(WIFI_STA);

  // Initialize ESP-NOW
  if (esp_now_init() != 0) {
    Serial.println("Error initializing ESP-NOW");
    return;
  }
  Serial.println("Initialized ESP-NOW");

  // Register for Receive Callback
  esp_now_set_self_role(ESP_NOW_ROLE_SLAVE);
  esp_now_register_recv_cb(OnDataRecv);
}

void forward() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void backward() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void left() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void right() {
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
}

void stop() {
  digitalWrite(in1, LOW);
  digitalWrite(in2, LOW);
  digitalWrite(in3, LOW);
  digitalWrite(in4, LOW);
}

void loop() {
  // Check for timeout if no data has been received in the last X milliseconds
  if (millis() - lastReceivedTime > timeout) {
    receivedData = "O";  // Set receivedData to "O" if timeout occurs
  }

  // Control based on received data
  if (receivedData == "F") {
    forward();  // 
  }
  else if (receivedData == "B") {
    backward();   // 
  }
  else if (receivedData == "L") {
    left();   // 
  }
  else if (receivedData == "R") {
    right();   // 
  }
  else if (receivedData == "O") {
    stop();   // 
  }
  else{
    stop();
  }

  // Continuously print the current receivedData
  Serial.print("Current Data: ");
  Serial.println(receivedData);

  delay(3);  // Delay for 1 second between prints
}

# ESP_now_Anne_Simeon
This repository holds the code the code to connect the fall and presence detection system to an alert system

The ESP_send code uses the ESPNow library to initialize communication between the two ESP32 and send data to the ESP32 connected to the actuator. It generates random drop sensor data, encapsulates it in a two-byte array (with the drop sensor ID and sensor value) and sends it to the broadcast MAC address (0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF) to be received by the ESP32 connected to the actuator.

The ESP_recv_alert code uses the ESPNow library to initialize communication between the two ESP32 and receive data from the ESP32 that sends the information. It defines a callback function that is called each time a message is received, which pulls the ID of the drop sensor and the value of the received message, lights the green LED if the value of the drop sensor is less than 512, otherwise lights the red LED and activates the buzzer for 1 second.

We chose to activate the buzzer for a second in our code for testing and demonstration purposes. However, in a real-life situation where the sensor detects a fall, the buzzer should continue to ring until it is turned off by a button provided for that purpose. The duration of the ringing could be defined according to the specific needs of the application and the preferences of the end user. For example, some users may prefer a short, quiet ringing, while others may prefer a longer, louder ringing to ensure the alert is heard.

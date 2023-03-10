#include <esp_now.h>
#include <WiFi.h>

// structure pour stocker l'adresse MAC de l'autre ESP32
typedef struct esp_now_peer_info_t {
  uint8_t peer_addr[6];
  esp_now_peer_info_t *next;
} esp_now_peer_info_t;

// broches pour les LED RGB
const int redPin = 25;
const int greenPin = 26;
const int bluePin = 27;

// broche pour le buzzer
const int buzzerPin = 14;

// fonction pour initialiser la communication ESPNow
void initESPNow() {
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erreur lors de l'initialisation d'ESPNow");
    return;
  }

  // définir la fonction de rappel pour la réception des messages
  esp_now_register_recv_cb([](uint8_t *mac, uint8_t *data, uint8_t len) {
    // extraire l'identifiant du capteur de chute et la valeur du message reçu
    uint8_t sensorId = data[0];
    bool sensorValue = data[1];

    // allumer la LED verte si la valeur du capteur de chute est vraie,
    // sinon allumer la LED rouge et activer le buzzer pendant 1 seconde
    if (sensorValue) {
      digitalWrite(greenPin, HIGH);
      digitalWrite(redPin, LOW);
      tone(buzzerPin, 2000, 1000);
    } else {
      digitalWrite(greenPin, LOW);
      digitalWrite(redPin, HIGH);
      tone(buzzerPin, 1000, 1000);
    }

    // afficher les données reçues sur la console série
    Serial.print("Capteur ");
    Serial.print(sensorId);
    Serial.print(" : ");
    Serial.println(sensorValue);
  });

  Serial.println("ESPNow initialisé avec succès");
}

void setup() {
  Serial.begin(115200);
  pinMode(redPin, OUTPUT);
  pinMode(greenPin, OUTPUT);
  pinMode(bluePin, OUTPUT);
  pinMode(buzzerPin, OUTPUT);

  WiFi.mode(WIFI_STA);

  // initialiser la communication ESPNow
  initESPNow();
}

void loop() {
  // ne rien faire dans la boucle principale
}

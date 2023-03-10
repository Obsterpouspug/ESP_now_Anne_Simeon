#include <esp_now.h>
#include <WiFi.h>

// structure pour stocker l'adresse MAC de l'autre ESP32
typedef struct esp_now_peer_info_t {
  uint8_t peer_addr[6];
  esp_now_peer_info_t *next;
} esp_now_peer_info_t;

// identifiant du capteur de chute
#define SENSOR_ID 1

// adresse MAC de l'ESP32 connecté à l'actionneur
uint8_t broadcastAddress[] = {0xFF, 0xFF, 0xFF, 0xFF, 0xFF, 0xFF};

// fonction pour initialiser la communication ESPNow
void initESPNow() {
  if (esp_now_init() != ESP_OK) {
    Serial.println("Erreur lors de l'initialisation d'ESPNow");
    return;
  }

  // ajouter l'adresse MAC de l'ESP32 connecté à l'actionneur
  esp_now_peer_info_t *peer = new esp_now_peer_info_t();
  memcpy(peer->peer_addr, broadcastAddress, 6);
  esp_now_add_peer(peer);

  // définir la fonction de rappel pour la réception des messages
  esp_now_register_recv_cb([](uint8_t *mac, uint8_t *data, uint8_t len) {});

  Serial.println("ESPNow initialisé avec succès");
}

void setup() {
  Serial.begin(115200);
  WiFi.mode(WIFI_STA);

  // initialiser la communication ESPNow
  initESPNow();
}

void loop() {
  // générer des données de capteur de chute aléatoires (entre 0 et 1023)
  int sensorValue = random(1024);

  // préparer les données à envoyer
  uint8_t data[2];
  data[0] = SENSOR_ID;    // identifiant du capteur de chute
  data[1] = sensorValue;  // valeur du capteur de chute

  // envoyer les données à l'ESP32 connecté à l'actionneur
  esp_err_t result = esp_now_send(broadcastAddress, data, sizeof(data));

  if (result == ESP_OK) {
    Serial.println("Données envoyées avec succès");
  } else {
    Serial.println("Erreur lors de l'envoi des données");
  }

  // attendre 5 secondes avant d'envoyer de nouvelles données
  delay(5000);
}

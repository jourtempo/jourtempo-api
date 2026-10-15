// ESP32 : lampe témoin de la couleur Tempo (API gratuite Jour Tempo, données RTE). Doc : https://jourtempo.fr/api/
// Bibliothèque : ArduinoJson 7 (gestionnaire de bibliothèques de l'IDE Arduino).
#include <WiFi.h>
#include <WiFiClientSecure.h>
#include <HTTPClient.h>
#include <ArduinoJson.h>

const char* WIFI_NOM = "MonWifi";
const char* WIFI_CLE = "MonMotDePasse";
const char* URL_TEMPO = "https://jourtempo.fr/api/v1/tempo.json";

void setup() {
  Serial.begin(115200);
  WiFi.begin(WIFI_NOM, WIFI_CLE);
  while (WiFi.status() != WL_CONNECTED) delay(500);
  Serial.println("Wi-Fi connecté");
}

void loop() {
  WiFiClientSecure client;
  client.setInsecure();              // simple ; pour vérifier le certificat, utilisez client.setCACert()
  HTTPClient http;
  http.useHTTP10(true);              // réponse non découpée : lecture directe par ArduinoJson
  http.begin(client, URL_TEMPO);
  int code = http.GET();
  if (code == 200) {
    // Le filtre ne garde que les valeurs utiles : peu de mémoire, même quand le calendrier s'allonge.
    JsonDocument filtre;
    filtre["aujourdhui"]["code"] = true;
    filtre["demain"]["code"] = true;
    filtre["saison"]["compteurs"]["rouge"]["restants"] = true;
    JsonDocument tempo;
    DeserializationError err = deserializeJson(tempo, http.getStream(), DeserializationOption::Filter(filtre));
    if (!err) {
      const char* aujourdhui = tempo["aujourdhui"]["code"];   // "bleu", "blanc" ou "rouge"
      const char* demain = tempo["demain"]["code"];           // idem, ou "inconnu" avant l'annonce
      int rouges = tempo["saison"]["compteurs"]["rouge"]["restants"];
      Serial.printf("Aujourd'hui %s, demain %s, %d rouges restants\n", aujourdhui, demain, rouges);
      // Ici : allumer la LED de la couleur de demain, par exemple.
    } else {
      Serial.printf("JSON illisible : %s\n", err.c_str());
    }
  } else {
    Serial.printf("HTTP %d, nouvel essai plus tard\n", code);
  }
  http.end();
  delay(30UL * 60 * 1000);           // un relevé toutes les 30 minutes (jamais moins de 10)
}

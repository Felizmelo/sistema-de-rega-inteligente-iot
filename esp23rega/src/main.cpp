#include <Arduino.h>
// DHT Temperature & Humidity Sensor
// Unified Sensor Library Example
// Written by Tony DiCola for Adafruit Industries
// Released under an MIT license.

// REQUIRES the following Arduino libraries:
// - DHT Sensor Library: https://github.com/adafruit/DHT-sensor-library
// - Adafruit Unified Sensor Lib: https://github.com/adafruit/Adafruit_Sensor

#include <Adafruit_Sensor.h>
#include <DHT.h>
#include <DHT_U.h>
#include "USB.h"

#define DHTPIN 2        // Pino ao qual o sensor DHT11 está conectado
#define DHTTYPE DHT11    // Tipo do sensor DHT
#define SOIL_MOISTURE_PIN 15  // Pino ao qual o medidor de umidade do solo está conectado
#define RELAY_PIN 5      // Pino ao qual o relé está conectado

//const char* ssid = "nome_da_rede_wifi";
//const char* password = "senha_da_rede_wifi";

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600);
  pinMode(RELAY_PIN, OUTPUT);
  
  // Inicializa o sensor DHT
  dht.begin();

  // Conecta ao WiFi
  //Serial.println();
  //Serial.println();
  //Serial.print("Conectando ao ");
  //Serial.println(ssid);
  
  //WiFi.begin(ssid, password);
  
  //while (WiFi.status() != WL_CONNECTED) {
   // delay(500);
   // Serial.print(".");
  //}
  
  //Serial.println("");
  //Serial.println("WiFi conectado");
  //Serial.println("Endereço IP: ");
  //Serial.println(WiFi.localIP());
}

void loop() {
  // Leitura da temperatura e umidade
  float h = dht.readHumidity();
  float t = dht.readTemperature();

  // Leitura da umidade do solo
  int soilMoisture = analogRead(SOIL_MOISTURE_PIN);

  // Verifica se as leituras foram bem-sucedidas
  if (isnan(h) || isnan(t)) {
    Serial.println("Erro ao ler o sensor DHT!");
    return;
  }

  // Exibe os valores de temperatura, umidade e umidade do solo
  Serial.print("Umidade: ");
  Serial.print(h);
  Serial.print("%\t");
  Serial.print("Temperatura: ");
  Serial.print(t);
  Serial.println("°C");
  Serial.print("Umidade do Solo: ");
  Serial.println(soilMoisture);

  // Verifica se a temperatura está acima de um certo limite (exemplo: 25°C) e se o solo está seco
  if (t > 25 && soilMoisture < 500) {
    // Liga o relé (inverte o estado do pino)
    digitalWrite(RELAY_PIN, HIGH);
    Serial.println("Ligando o sistema de irrigação");
  } else {
    // Desliga o relé (inverte o estado do pino)
    digitalWrite(RELAY_PIN, LOW);
    Serial.println("Desligando o sistema de irrigação");
  }

  delay(5000); // Espera 5 segundos antes de realizar a próxima leitura
}
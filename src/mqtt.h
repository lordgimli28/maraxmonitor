#ifndef MQTT_H
#define MQTT_H
    
void callback(char* topic, byte* payload, unsigned int length) 
{
  Serial.print("Message arrived [");
  Serial.print(topic);
  Serial.print("] ");
  for (int i = 0; i < length; i++) {
    Serial.print((char)payload[i]);
  }
  Serial.println();
}

PubSubClient mqttClient(mqtt_broker, mqtt_port, callback, wifiClient);


void setup_mqtt() 
{
  if(mqttClient.connect(mqtt_clientId.c_str(), mqttUser, mqttPassword))
  {
      Serial.print("connection to mqtt client successful");
  }
  mqttClient.setServer(mqtt_broker, mqtt_port);
  mqttClient.setCallback(callback);
}
void reconnect() {
  // Loop until we're reconnected
  while (!mqttClient.connected()) {
    //Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (mqttClient.connect(mqtt_clientId.c_str(), mqttUser, mqttPassword)) {
      //Serial.println("connected");
    } else {
      //Serial.print("failed, rc=");
      //Serial.print(mqttClient.state());
      //Serial.println(" try again in 5 seconds");
      // Wait 5 seconds before retrying
      delay(5000);
    }
  }
}



void sendDiscoveryMessage(const char* topic, const char* name, const char* deviceClass, const char* unitOfMeasurement, const char* uniqueID) {
  config_doc["name"] = name; // Name setzen
  config_doc["device_class"] = deviceClass; // Geräteklasse setzen
  config_doc["unit_of_measurement"] = unitOfMeasurement; // Maßeinheit setzen
  config_doc["state_topic"] = topic; // Zustandsthema setzen
  config_doc["value_template"] = "{{ value }}"; // Wertvorlage setzen
  config_doc["unique_id"] = uniqueID; 
  config_doc["state_class"] = "measurement";

  serializeJson(config_doc, config_buffer); // JSON-Objekt serialisieren
  Serial.println(config_buffer);
  mqttClient.publish(("homeassistant/sensor/arduino/" + String(name) + "/config").c_str(), config_buffer, true); // Auto-Discovery-Nachricht veröffentlichen
}


void update_mqtt() 
{
 if (!mqttClient.connected()) {
    reconnect();
  }

  mqttClient.loop();

  if (millis() - previousMillis >= interval) 
  {
    previousMillis = millis();

    sendDiscoveryMessage("MaraX/sensor/temp_steam", "SteamTemp", "temperature", "C", "8e65a01b-8b4d-4dc3-a98c-3e7f3441ad0a");
    sendDiscoveryMessage("MaraX/sensor/temp_coffee", "CoffeeTemp", "temperature", "C", "85e45268-3306-4567-bec0-9c7b33547281");

    mqttClient.publish("MaraX/sensor/temp_steam", String(tempSteam).c_str());
    mqttClient.publish("MaraX/sensor/temp_coffee", String(tempCoffee).c_str());

  }

}
#endif
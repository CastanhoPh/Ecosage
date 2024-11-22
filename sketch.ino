#include <WiFi.h>
#include <PubSubClient.h>

// Configurações de rede Wi-Fi e ao MQTT mosquitto
const char* ssid = "Wokwi-GUEST";
const char* password = "";
const char* mqtt_server = "test.mosquitto.org";

// Configuração do cliente MQTT
WiFiClient WOKWI_Client;
PubSubClient client(WOKWI_Client);

// Definição dos pinos
#define GREEN 2     
#define YELLOW 0    
#define RED 4   
#define RELAY_PIN 15
#define ANALOG_PIN A0 // ADC no ESP8266
#define ANALOG_THRESHOLD 500
#define WIFI 22
#define MOSQUITTO 23

// Variáveis
int valor;
int valorCorrente;
String aviso = "Tudo certo!";
String relay = "Desativado";

void setup_wifi() {
  delay(10);
  Serial.println();
  Serial.print("Connectando...");
  Serial.println(ssid);

  WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);

  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }

  Serial.println("");
  Serial.println("WiFi conectado");
  Serial.println("Endereço de IP: ");
  Serial.println(WiFi.localIP());
}

void reconnect() {
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    if (client.connect("WOKWI_Client")) {
      Serial.println("connected");
    } else {
      Serial.print("failed, rc=");
      Serial.print(client.state());
      Serial.println(" try again in 5 seconds");
      delay(5000);
    }
  }
}

void Control_Leds() {
  valor = analogRead(34);
  valorCorrente = map(valor, 0, 4095, 2, 10);

  Serial.print("Valor lido: ");
  Serial.print(valor);
  Serial.print(" Mapeado: ");
  Serial.println(valorCorrente);

  digitalWrite(GREEN, LOW);
  digitalWrite(YELLOW, LOW);
  digitalWrite(RED, LOW);

  if (valorCorrente <= 3) {  
    digitalWrite(GREEN, HIGH);
    Serial.println("Tudo certo!"); 
    aviso = "Tudo certo!";
  } 
  else if (valorCorrente > 3 && valorCorrente <= 9) { 
    digitalWrite(YELLOW, HIGH); 
    Serial.println("Corrente elétrica um pouco acima cuidado!");
    aviso = "Corrente elétrica um pouco acima cuidado!";
  } 
  else if (valorCorrente == 9){
    Serial.println("Corrente elétrica muito alta, caso aumente iremos desligar o dispositvo");
    aviso = "Corrente elétrica muito alta, caso aumente iremos desligar o dispositvo";
  }
  else if (valorCorrente >= 10) {  
    digitalWrite(RED, HIGH); 
    Serial.println("Corrente elétrica extremamente alta, Desligando dispositvo...");
    aviso = "Corrente elétrica extremamente alta, Desligando dispositvo...";

  }

  delay(200);
}

void RelayControl() {
  if (valorCorrente >= 10) {
    digitalWrite(RELAY_PIN, HIGH);
    relay = "Ativado! Dispositivo desligado";
  } else {
    digitalWrite(RELAY_PIN, LOW);
    relay = "Desativado";
  }
}

void Conectado_Wifi(){
  if(WiFi.status())
  digitalWrite(WIFI, HIGH);
  else
  digitalWrite(WIFI, LOW);

}

void Conectado_Mosquitto(){
  if (client.connected())
  digitalWrite(MOSQUITTO, HIGH);
  else
  digitalWrite(MOSQUITTO, LOW);
}

void Publica_Dados(){
  client.publish("Corrente_Elétrica",String(valorCorrente).c_str());
  client.publish("Aviso",String(aviso).c_str());
  client.publish("Relay",String(relay).c_str());
  delay(500);

}

void setup() {
  pinMode(GREEN, OUTPUT);
  pinMode(YELLOW, OUTPUT);
  pinMode(RED, OUTPUT);
  pinMode(RELAY_PIN, OUTPUT);

  pinMode(WIFI, OUTPUT);
  pinMode(MOSQUITTO, OUTPUT);

  Serial.begin(115200);
  setup_wifi();
  client.setServer(mqtt_server, 1883);
}

void loop() {
  reconnect();
  Conectado_Wifi();
  Conectado_Mosquitto();
  Control_Leds();
  RelayControl();
  Publica_Dados();
}

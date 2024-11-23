# Projeto: Monitoramento de Corrente Elétrica com ESP32 e MQTT

Este projeto utiliza um ESP32 para monitorar a corrente elétrica, controlar LEDs indicativos e um relé, além de se comunicar com o servidor MQTT Mosquitto para publicar dados em tempo real. Os dados podem ser visualizados e interagidos por meio de um dashboard criado no Node-RED.

---

## **Componentes e Hardware**

### **Hardware necessário**
- ESP32
- Resistores e LEDs (Verde, Amarelo e Vermelho)
- Sensor de corrente (simulado no Wokwi)
- Relé
- Conexão Wi-Fi
- Broker MQTT (Mosquitto)

### **Pinos utilizados no ESP32**
| Pino | Função                        |
|------|-------------------------------|
| 2    | LED Verde                     |
| 0    | LED Amarelo                   |
| 4    | LED Vermelho                  |
| 15   | Controle do Relé              |
| 34 | Leitura do sensor analógico |
| 22   | Indicador de Wi-Fi conectado  |
| 23   | Indicador de conexão ao Mosquitto |

---

## **Funcionamento do Código**

1. **Conexão Wi-Fi e MQTT**
   - O ESP32 conecta-se à rede Wi-Fi configurada.
   - Conecta ao broker MQTT Mosquitto no endereço `test.mosquitto.org`.

2. **Monitoramento da Corrente**
   - Lê os valores do sensor analógico.
   - Converte os valores lidos para uma escala simulada de corrente (2 a 10 A).

3. **Controle dos LEDs**
   - Dependendo do valor da corrente, os LEDs Verde, Amarelo ou Vermelho indicam:
     - **Verde:** Corrente normal (<= 3 A).
     - **Amarelo:** Corrente moderada (> 3 A e <= 9 A).
     - **Vermelho:** Corrente alta (>= 10 A).

4. **Controle do Relé**
   - Desativa o relé (desligando o dispositivo) quando a corrente atinge valores perigosos (>= 10 A).

5. **Publicação de Dados via MQTT**
   - Publica os seguintes tópicos:
     - **`Corrente_Elétrica`**: Valor da corrente lida.
     - **`Aviso`**: Mensagem de alerta sobre o status da corrente.
     - **`Relay`**: Status do relé (Ativado/Desativado).

6. **Indicadores Wi-Fi e MQTT**
   - LEDs nos pinos 22 e 23 indicam se o ESP32 está conectado ao Wi-Fi e ao broker MQTT.

---

## **Configuração do Node-RED**

1. **Instalação do Node-RED**
   - Instale o Node-RED e o nó MQTT.
   - Configure a conexão ao broker Mosquitto (`test.mosquitto.org`) no nó MQTT.

2. **Fluxo no Node-RED**
   - **Assinatura dos Tópicos MQTT**
     - `Corrente_Elétrica`
     - `Aviso`
     - `Relay`
   - **Visualização no Dashboard**
     - Crie um dashboard interativo com os seguintes elementos:
       - **Gauge (Medidor):** Mostra a corrente elétrica em tempo real.
       - **Indicador de Status:** Exibe o aviso sobre a corrente elétrica.
       - **Botão para Controle do Relé:** Permite ligar/desligar manualmente o relé (opcional).

3. **Configuração do Dashboard**
   - Utilize o nó `ui_gauge` para exibir o valor de `Corrente_Elétrica`.
   - Utilize o nó `ui_text` para mostrar os avisos recebidos do tópico `Aviso`.
   - Utilize o nó `ui_text` para exibir estado do relay por meio do tópico `Relay`.

---

## **Fluxo de Dados**

1. O ESP32 lê a corrente e determina o status.
2. Publica os dados nos tópicos MQTT.
3. O Node-RED recebe os dados e atualiza o dashboard.

---

## **Simulação no Wokwi**

Este projeto pode ser simulado no Wokwi para testes sem necessidade de hardware físico. No Wokwi, o sensor de corrente pode ser substituído por um potenciômetro ajustável para simular diferentes valores de corrente.

---

Com esse projeto, é possível criar um sistema completo de monitoramento e controle de corrente elétrica com comunicação IoT via MQTT, oferecendo insights e ações interativas em tempo real!

## **Fotos dos dashboards e fluxos**
[Acesse a pasta no Google Drive](https://drive.google.com/drive/folders/1JdKA_l8NR0mpUKcBIBIFY5eMIhQ_Xyrv?usp=drive_link)

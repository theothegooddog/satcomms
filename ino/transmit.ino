#define TX_PIN 2
//params
#define SFT "STCM"
#define ID "001"
#define VER "1-0-5"

String current = "";
bool available = Serial.available();

void sendBit(bool bit) {
  digitalWrite(TX_PIN, bit);
  delayMicroseconds(500);
}

void sendByte(byte b) {
  for (int i = 7; i >= 0; i--) {
    sendBit(bitRead(b, i));
  }
}

void transmit(String data) {
  Serial.println("Transmitting " + data);

  // sync pulse
  digitalWrite(TX_PIN, HIGH);
  delayMicroseconds(2000);
  digitalWrite(TX_PIN, LOW);
  delayMicroseconds(2000);

  // send characters
  for (int i = 0; i < data.length(); i++) {
    sendByte(data[i]);
  }

  // end pulse
  digitalWrite(TX_PIN, LOW);
}

void transmitinit(){
  digitalWrite(3, HIGH);
  digitalWrite(4, HIGH);
}
void setup() {
  pinMode(2,OUTPUT);
  pinMode(3,OUTPUT);
  pinMode(4,OUTPUT);
  Serial.begin(115200);
  Serial.println("init");
  if (!(Serial.available())) {
    delay(10);
    transmit(String(SFT)+ID+VER+"tt");
  }
}

void loop() {
  if (Serial.available()) {
    String incoming = Serial.readStringUntil(';');

    if (incoming != current) {
      current = incoming;
      transmit(current);
    } else {
      current = "";
    }
  }
}

// MX-RM-5V raw receiver
// No RadioHead
// Pure pulse decoding
//
// MX-RM-5V:
// VCC  -> 5V
// GND  -> GND
// DATA -> D2
//
// Works with simple FS1000A-style transmitters

#define RX_PIN 2

String incoming = "";

volatile byte currentByte = 0;
volatile int bitCount = 0;

volatile unsigned long lastTime = 0;

String KEY = "123456";

// =====================================

String stringConv1(String str) {
  String out = "";
  String num = "";

  for (int i = 0; i < str.length(); i++) {

    char c = str[i];

    if (c == ',') {

      if (num.length() > 0) {
        out += (char)num.toInt();
        num = "";
      }

    } else {
      num += c;
    }
  }

  if (num.length() > 0) {
    out += (char)num.toInt();
  }

  return out;
}

String numbersOnly(String s) {

  String out = "";

  for (int i = 0; i < s.length(); i++) {

    char c = s[i];

    if (c >= '0' && c <= '9') {
      out += c;
    }
  }

  return out;
}

String moveMotor(String m, String d) {

  String inst = "";

  inst += "Instruction: mm (Move Motor)\n";

  String motorname = "";

  if (m == "lt") {
    motorname = "Left; Top";
  }
  else if (m == "rt") {
    motorname = "Right; Top";
  }
  else if (m == "lb") {
    motorname = "Left; Bottom";
  }
  else if (m == "rb") {
    motorname = "Right; Bottom";
  }
  else {
    return "[rej]";
  }

  inst += "Motor: " + m + " (" + motorname + ")\n";
  inst += "Direction: " + d + "°";

  return inst;
}

String parseInstruction(String inst) {

  int p1 = inst.indexOf('+');

  if (p1 == -1)
    return "[rej]";

  String cmd = inst.substring(0, p1);

  if (cmd == "mm") {

    int p2 = inst.indexOf('+', p1 + 1);

    if (p2 == -1)
      return "[rej]";

    String motor = inst.substring(p1 + 1, p2);
    String direction = inst.substring(p2 + 1);

    return moveMotor(motor, direction);
  }

  else if (cmd == "cp") {

    return "Photo captured";
  }

  return "[rej]";
}

// =====================================
// VERY SIMPLE BIT DECODER
//
// Long pulse  = 1
// Short pulse = 0
//
// This MUST match transmitter timing
// =====================================

void rxISR() {

  unsigned long now = micros();

  unsigned long dur = now - lastTime;

  lastTime = now;

  // ignore sync gap
  if (dur > 5000) {

    currentByte = 0;
    bitCount = 0;

    return;
  }

  // threshold
  int bit = (dur > 1000) ? 1 : 0;

  currentByte <<= 1;
  currentByte |= bit;

  bitCount++;

  if (bitCount == 8) {

    incoming += (char)currentByte;

    bitCount = 0;
    currentByte = 0;
  }
}

void setup() {

  Serial.begin(115200);

  pinMode(RX_PIN, INPUT);

  attachInterrupt(
    digitalPinToInterrupt(RX_PIN),
    rxISR,
    CHANGE
  );

  Serial.println("Receiver ready");
}

void loop() {

  static unsigned long lastData = 0;

  if (incoming.length() > 0) {
    lastData = millis();
  }

  // packet timeout
  if (
    incoming.length() > 0 &&
    millis() - lastData > 200
  ) {

    String code = incoming;

    incoming = "";

    Serial.println("RAW: " + code);

    int colon = code.indexOf(':');

    if (colon == -1) {

      Serial.println("REJECT");
      return;
    }

    String keyPart = code.substring(0, colon);
    String dataPart = code.substring(colon + 1);

    String received = numbersOnly(keyPart);

    String expected = String(KEY.toInt() * 2573);

    if (received == expected) {

      String decoded = stringConv1(dataPart);

      Serial.println("Decoded: " + decoded);

      String result = parseInstruction(decoded);

      if (result == "[rej]") {
        Serial.println("REJECT [invalid instructions.]");
      }
      else {
        Serial.println(result);
      }

    } else {

      Serial.println("REJECT");
    }
  }
}

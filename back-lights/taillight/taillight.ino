const uint8_t LED_PIN = 9;
// Onboard LED mirrors the pattern as on/off (pin 13 has no PWM), confirming the sketch runs.
const uint8_t BOARD_LED_PIN = LED_BUILTIN;
const float BOARD_LED_THRESHOLD = 0.5;

// Toggle switch from D2 to GND; the internal pull-up reads HIGH while it's open.
const uint8_t SWITCH_PIN = 2;

const float GAMMA = 2.2;
const float MIN_LEVEL = 0.25;

const unsigned long PULSE_MS = 2800;

float pulseWave(unsigned long now) {
  float phase = (now % PULSE_MS) / float(PULSE_MS);
  return 0.5 - 0.5 * cos(phase * TWO_PI);
}

uint8_t toPwm(float wave) {
  float level = MIN_LEVEL + (1.0 - MIN_LEVEL) * wave;
  return round(pow(level, GAMMA) * 255);
}

bool steadySelected() {
  return digitalRead(SWITCH_PIN) == LOW;
}

void setup() {
  pinMode(LED_PIN, OUTPUT);
  pinMode(BOARD_LED_PIN, OUTPUT);
  pinMode(SWITCH_PIN, INPUT_PULLUP);
}

void loop() {
  float wave = steadySelected() ? 1.0 : pulseWave(millis());
  analogWrite(LED_PIN, toPwm(wave));
  digitalWrite(BOARD_LED_PIN, wave >= BOARD_LED_THRESHOLD ? HIGH : LOW);
}


const int LDR_DO_PIN = 4;   // LDR Digital Output
const int PIR_PIN = 27;     // PIR OUT connected to GPIO 27

const int LED_PIN = 2;      // LED 1
const int LED2_PIN = 18;    // LED 2
const int LED3_PIN = 19;    // LED 3

const int PWM_FREQ = 5000;
const int PWM_RESOLUTION = 8;

const int BRIGHT_100 = 255;
const int DIM_50 = 128;
const int OFF_0 = 0;

int currentBrightness = 0;
int motionCount = 0;
const int motionThreshold = 3;

void setup() {
  Serial.begin(115200);

  pinMode(LDR_DO_PIN, INPUT);
  pinMode(PIR_PIN, INPUT);

  // Setup PWM for all three LEDs
  if (!ledcAttach(LED_PIN, PWM_FREQ, PWM_RESOLUTION)) {
    Serial.println("LED 1 PWM setup failed!");
    while (true) {
      delay(1000);
    }
  }

  if (!ledcAttach(LED2_PIN, PWM_FREQ, PWM_RESOLUTION)) {
    Serial.println("LED 2 PWM setup failed!");
    while (true) {
      delay(1000);
    }
  }

  if (!ledcAttach(LED3_PIN, PWM_FREQ, PWM_RESOLUTION)) {
    Serial.println("LED 3 PWM setup failed!");
    while (true) {
      delay(1000);
    }
  }

  ledcWrite(LED_PIN, OFF_0);
  ledcWrite(LED2_PIN, OFF_0);
  ledcWrite(LED3_PIN, OFF_0);

  Serial.println("Smart Street Lighting System");
  Serial.println("PIR warming up. Wait 40 seconds...");
  delay(40000);

  Serial.println("System active!");
}

void loop() {
  int ldrState = digitalRead(LDR_DO_PIN);
  int pirState = digitalRead(PIR_PIN);

  // Assumes LDR output is HIGH in darkness
  bool isNight = (ldrState == HIGH);

  // Confirm motion after 3 consecutive HIGH readings
  if (pirState == HIGH) {
    if (motionCount < motionThreshold) {
      motionCount++;
    }
  } else {
    motionCount = 0;
  }

  bool motionActive = (motionCount >= motionThreshold);

  int targetBrightness;

  if (!isNight) {
    targetBrightness = OFF_0;
  } else if (motionActive) {
    targetBrightness = BRIGHT_100;
  } else {
    targetBrightness = DIM_50;
  }

  // Smooth LED fading for all three LEDs
  if (currentBrightness < targetBrightness) {
    currentBrightness += 5;

    if (currentBrightness > targetBrightness) {
      currentBrightness = targetBrightness;
    }

    ledcWrite(LED_PIN, currentBrightness);
    ledcWrite(LED2_PIN, currentBrightness);
    ledcWrite(LED3_PIN, currentBrightness);

    delay(5);

  } else if (currentBrightness > targetBrightness) {
    currentBrightness -= 3;

    if (currentBrightness < targetBrightness) {
      currentBrightness = targetBrightness;
    }

    ledcWrite(LED_PIN, currentBrightness);
    ledcWrite(LED2_PIN, currentBrightness);
    ledcWrite(LED3_PIN, currentBrightness);

    delay(10);
  }

  // Display readings every 400 milliseconds
  static unsigned long lastPrint = 0;

  if (millis() - lastPrint >= 400) {
    Serial.print("LDR (Dark): ");
    Serial.print(isNight ? "YES" : "NO");

    Serial.print(" | PIR Output: ");
    Serial.print(pirState);

    Serial.print(" | Motion: ");
    Serial.print(motionActive ? "YES" : "NO");

    Serial.print(" | LED Brightness: ");
    Serial.print((currentBrightness * 100) / 255);
    Serial.println("%");

    lastPrint = millis();
  }
}

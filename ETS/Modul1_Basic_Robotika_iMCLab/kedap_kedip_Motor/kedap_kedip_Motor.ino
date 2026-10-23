// ============================================================
// iMCLab - Motor DC + LED Kedap-Kedip (Blink) beberapa detik
// Modifikasi dari on_off_Motor.ino
//
// Perintah via Serial Monitor / Python (baud 115200):
//   '1' -> Motor + LED ON terus-menerus
//   '0' -> Motor + LED OFF (juga membatalkan kedap-kedip)
//   'b' -> Kedap-kedip selama BLINK_DURATION_MS lalu otomatis OFF
//
// Kedap-kedip memakai millis() (non-blocking), jadi perintah '0'
// tetap bisa diterima saat kedap-kedip sedang berjalan.
// ============================================================

int ledPin = 2;

int motor1Pin1 = 27;
int motor1Pin2 = 26;
int enable1Pin = 12;

// Setting PWM properties
const int freq = 30000;
const int pwmChannel = 0;
const int resolution = 8;
int dutyCycle = 200;

// ---------------- Pengaturan kedap-kedip ----------------
const unsigned long BLINK_INTERVAL_MS = 100;   // lama 1 fase ON / OFF (ms)
const unsigned long BLINK_DURATION_MS = 5000;  // total waktu kedap-kedip (ms)
const bool BLINK_MOTOR = true;                 // true  = LED + motor ikut kedip
                                               // false = hanya LED yang kedip

bool blinking = false;
bool blinkState = false;
unsigned long blinkStart = 0;
unsigned long lastToggle = 0;

void setup()
{
  pinMode(ledPin, OUTPUT);
  Serial.begin(115200);

  pinMode(motor1Pin1, OUTPUT);
  pinMode(motor1Pin2, OUTPUT);
  pinMode(enable1Pin, OUTPUT);

  // configure PWM
  ledcSetup(pwmChannel, freq, resolution);
  ledcAttachPin(enable1Pin, pwmChannel);

  MotorOff();   // pastikan motor mati saat start

  Serial.println("Testing DC Motor - mode kedap-kedip");
  Serial.println("Perintah: 1 = ON, 0 = OFF, b = kedap-kedip");
}

void MotorOn()
{
  dutyCycle = 205;
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  ledcWrite(pwmChannel, dutyCycle);
}

void MotorOff()
{
  dutyCycle = 0;
  digitalWrite(motor1Pin1, HIGH);
  digitalWrite(motor1Pin2, LOW);
  ledcWrite(pwmChannel, dutyCycle);
}

void mulaiKedip()
{
  blinking = true;
  blinkState = false;
  blinkStart = millis();
  lastToggle = blinkStart - BLINK_INTERVAL_MS;  // langsung toggle di loop berikutnya
  Serial.print("Kedap-kedip dimulai selama ");
  Serial.print(BLINK_DURATION_MS / 1000.0, 1);
  Serial.println(" detik");
}

void hentikanKedip()
{
  blinking = false;
  blinkState = false;
  digitalWrite(ledPin, LOW);
  MotorOff();
}

void updateKedip()
{
  if (!blinking) return;

  unsigned long now = millis();

  // Waktu kedap-kedip habis -> matikan semuanya
  if (now - blinkStart >= BLINK_DURATION_MS)
  {
    hentikanKedip();
    Serial.println("Kedap-kedip selesai. LED & motor OFF.");
    return;
  }

  // Ganti fase ON/OFF setiap BLINK_INTERVAL_MS
  if (now - lastToggle >= BLINK_INTERVAL_MS)
  {
    lastToggle = now;
    blinkState = !blinkState;

    digitalWrite(ledPin, blinkState ? HIGH : LOW);

    if (BLINK_MOTOR)
    {
      if (blinkState) MotorOn();
      else            MotorOff();
    }
  }
}

void loop()
{
  if (Serial.available() > 0)
  {
    char myData = Serial.read();

    if (myData == '1')
    {
      blinking = false;
      Serial.println("LED is on !!!");
      digitalWrite(ledPin, HIGH);
      MotorOn();
    }
    else if (myData == '0')
    {
      blinking = false;
      Serial.println("LED is off !!!");
      digitalWrite(ledPin, LOW);
      MotorOff();
    }
    else if (myData == 'b' || myData == 'B')
    {
      mulaiKedip();
    }
  }

  updateKedip();
}
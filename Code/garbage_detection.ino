
#define onTime 10;       // Number of cycles to count down to switch off
const byte motionDelta = 30;  // Sensitivity 
const int readDelay = 1000;
unsigned int val, lastVal, diff;
byte latch = 0;

// Start a new countdown if more motion or continue if not
void countDown(boolean motion) {
  if (motion) {
    latch = onTime;
    Serial.println("Motion! Starting countdown..");
  }
  else if (latch > 0) {
    latch--;
    Serial.print(latch);
    Serial.println(" more to deactivate");
  }
  
  if (latch <= 0) {
    digitalWrite(PIN_D6, LOW);
  }
  else {
    digitalWrite(PIN_D6, HIGH);
  }
}

void setup() {                
  Serial.begin(38400);
  pinMode(PIN_D6, OUTPUT);
  digitalWrite(PIN_D6, LOW);
}

void loop() {
  lastVal = val;        // Store the previous value
  val = analogRead(0);  // Read analog value
  
  // We do not want negative results
  if (val > lastVal) {
    diff = val - lastVal;
  } 
  else {
    diff = lastVal - val;
  }
  
  // Debug printout
  Serial.print("val, lastVal, diff: ");
  Serial.print(val);
  Serial.print(" - ");
  Serial.print(lastVal);
  Serial.print(" - ");
  Serial.println(diff);

  // Start a new countdown if more motion or timeout if not
  if (diff > motionDelta) { 
    countDown(true);
  }
  else {
    countDown(false);
  }
  
  // Delay between actions 
  delay(readDelay);
}

void setup() {
  // initialize digital pin LED_BUILTIN as an output.
}

// the loop function runs over and over again forever
void loop() {
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, INPUT);
  delay(400);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  delay(400);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  delay(400);
  pinMode(11, INPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT); 
  delay(400);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW);
  delay(400);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH); 
  delay(400);
  pinMode(11, OUTPUT);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
  delay(400);
  digitalWrite(13, HIGH);
  digitalWrite(11, LOW);
  delay(400);
  digitalWrite(13, LOW);
  digitalWrite(11, HIGH); 
  delay(400);
  pinMode(11, OUTPUT);
  pinMode(12, INPUT);
  pinMode(13, OUTPUT);
  delay(400);
  digitalWrite(13, LOW);
  digitalWrite(11, HIGH);
  delay(400);
  digitalWrite(13, HIGH);
  digitalWrite(11, LOW); 
  delay(400);
  pinMode(11, INPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT); 
  delay(400);
  digitalWrite(12, LOW);
  digitalWrite(13, HIGH);
  delay(400);
  digitalWrite(12, HIGH);
  digitalWrite(13, LOW); 
  delay(400);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, INPUT);
  delay(400);
  digitalWrite(11, LOW);
  digitalWrite(12, HIGH);
  delay(400);
  digitalWrite(11, HIGH);
  digitalWrite(12, LOW);
  delay(400);
}

#define relay 2
#define button 3
#define interval 5
void setup() {
  
  pinMode(relay,OUTPUT);
  pinMode(button,INPUT_PULLUP);
  digitalWrite(relay,LOW);
  Serial.begin(115200);
  Serial.println("Manual irrigation Controller v 0.1");

}

void loop() {
  if(digitalRead(button)==LOW)
  {
    unsigned long time;
    digitalWrite(relay,HIGH);
    time=millis()/1000;
    Serial.print("Irrigation started at ");
    Serial.print(time);
    Serial.println(" seconds");
    delay(interval*1000);
    digitalWrite(relay,LOW);
    
    time=millis()/1000;
    Serial.print("Irrigation stopped at ");
    Serial.print(time);
    Serial.println(" seconds");
    
    while(digitalRead(button)==LOW)
     delay(200);//debounce
  }

}
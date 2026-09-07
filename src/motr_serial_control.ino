const int pwm = 5;
const int valve = 7;

volatile int mtr_speed = 0;
volatile boolean EStop = false;

void setup()
{
  pinMode(pwm, OUTPUT);
  pinMode(valve, OUTPUT);
  // Initialize outputs as OFF
  digitalWrite(valve, LOW);
  analogWrite(pwm, 0);
  Serial.begin(9600);
  Serial.println("PWM based Motor and Valve Control with Emergency Stop Button");
  Serial.println("Type X for Emergency Stop");
  Serial.println("Type: SPEED <Number>, where number ranges from 0 to 255");
}

void estop()
{
  Serial.println("Emergency Stop Enabled");
  Serial.println("Mannually Reset to Start again");
  analogWrite(pwm, 0);
  digitalWrite(valve, LOW);
  EStop = true;
}

void loop()
{
  if (Serial.available() > 0)
  {
    String command = Serial.readStringUntil('\n');
    command.trim();
    command.toUpperCase();
    if (command.startsWith("SPEED"))
    {
      int spaceindex = command.indexOf(' ');
      if (spaceindex != -1)
      {
        int speed = command.substring(spaceindex + 1).toInt();
        if (speed >= 0 && speed <= 255)
        {
          
          if (!EStop)
          {
            digitalWrite(valve,HIGH);
            mtr_speed = speed;
            analogWrite(pwm, mtr_speed);
            Serial.print("Motor speed set to: ");
            Serial.println(mtr_speed);
          }
          else
          {
            Serial.println("Emergency Stop Activated!!");
          }
        }
        else
        {
          Serial.println("Error: Enter a number between 0 and 255");
        }
      }
    }
    else if (command == "X")
    {
      estop();
    }

    else
    {
      Serial.println("Unknown command.");
      Serial.println("Use: SPEED <0-255> or X");
    }
  }
}
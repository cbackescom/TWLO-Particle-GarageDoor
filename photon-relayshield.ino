//Door1 PIN
int DOOR1 = D3;
//Door2 PIN
int DOOR2 = D4;
//Door1 Sensor
const int D1sensor = D0;
//Door2 Sensor
const int D2sensor = D1;



void setup()
{
   //Initilize the relay control pins as output
   pinMode(DOOR1, OUTPUT);
   pinMode(DOOR2, OUTPUT);
   //Initialize the garage door sensor pings as INPUT
   pinMode(D1sensor, INPUT_PULLUP);
   pinMode(D2sensor, INPUT_PULLUP);
   // Initialize all relays to an OFF state
   digitalWrite(DOOR1, LOW);
   digitalWrite(DOOR2, LOW);
   //register the Particle function
   Particle.function("relay", relayControl);
   Particle.function("status", obtainStatus);
}

void loop()
{
  //add anything here...
}

// command format r1,ON
int relayControl(String command)
{
  if(command == "D1")
  {
      digitalWrite(DOOR1, HIGH);
      delay(750); //change based on how long you want the relay to act as button press
      digitalWrite(DOOR1, LOW);
      return 1;
  }
  else if(command == "D2")
  {
      digitalWrite(DOOR2, HIGH);
      delay(750); //change based on how long you want the relay to act as button press
      digitalWrite(DOOR2, LOW);
      return 1;
  }
  else return -1;
}

int obtainStatus(String command)
{
    if(command == "Status")
    {
        if((digitalRead(D1sensor) == HIGH)&(digitalRead(D2sensor) == HIGH)){
            Particle.publish("status", "both doors are open", PRIVATE);
        }
        else if((digitalRead(D1sensor) == LOW)&(digitalRead(D2sensor) == HIGH)){
            Particle.publish("status", "D1 closed D2 open", PRIVATE);
        }
        else if((digitalRead(D1sensor) == HIGH)&(digitalRead(D2sensor) == LOW)){
            Particle.publish("status", "D1 open D2 closed", PRIVATE);
        }
        else if((digitalRead(D1sensor) == LOW)&(digitalRead(D2sensor) == LOW)){
            Particle.publish("status", "both doors are closed", PRIVATE);
        }
    }
}

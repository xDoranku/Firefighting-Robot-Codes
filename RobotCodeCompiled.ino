// motor driver pins
int en1 = 2;
int en2 = 3;
int in1 = 22;
int in2 = 24;
int in3 = 25;
int in4 = 26;

// pump pins
int enp = 4;
int inp1 = 50;
int inp2 = 51;

// flame sensor pins
int F_left = 40;
int F_right = 41;
int B_left = 42;
int B_right = 43;
int middle = 44;
int F_leftR;
int F_rightR;
int B_leftR;
int B_rightR;
int middleR;

// ultrasonic sensor pins and definition
int trigPin = 32;    // Trigger
int echoPin = 33  ;    // Echo
long duration, cm, inches;

void setup() {
  Serial.begin(9600);
  // put your setup code here, to run once:
  // dc motors
  pinMode(en1, OUTPUT);
  pinMode(en2, OUTPUT);
  pinMode(in1, OUTPUT);
  pinMode(in2, OUTPUT);
  pinMode(in3, OUTPUT);
  pinMode(in4, OUTPUT);

  //pump
  pinMode(enp, OUTPUT);
  pinMode(inp1, OUTPUT);
  pinMode(inp2, OUTPUT);

  // flame sensors
  pinMode(F_left, INPUT);
  pinMode(F_right, INPUT);
  pinMode(B_left, INPUT);
  pinMode(B_right, INPUT);
  pinMode(middle, INPUT);

  // ultrasonic sensors
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
}

void water_pump()
{
  analogWrite(enp, 255);
  digitalWrite(inp1, HIGH);
  digitalWrite(inp2, LOW);
}

void forward_motor()
{
  // motor 1
  analogWrite(en1, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // motor 2
  analogWrite(en2, 255);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
}

void reverse_motor()
{
  // motor 1
  analogWrite(en1, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // motor 2
  analogWrite(en2, 255);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);
  delay(2550);
}

void turn_left()
{
  // motor 1
  analogWrite(en1, 255);
  digitalWrite(in1, HIGH);
  digitalWrite(in2, LOW);
  // motor 2
  analogWrite(en2, 255);
  digitalWrite(in3, HIGH);
  digitalWrite(in4, LOW);
  if (F_leftR == 1 && F_rightR == 1 && B_leftR == 1 && B_rightR == 1)
  {
    // motor 1
    analogWrite(en1, 255);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    // motor 2
    analogWrite(en2, 255);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    water_pump();
  }
}

void turn_right()
{
  // motor 1
  analogWrite(en1, 255);
  digitalWrite(in1, LOW);
  digitalWrite(in2, HIGH);
  // motor 2
  analogWrite(en2, 255);
  digitalWrite(in3, LOW);
  digitalWrite(in4, HIGH);

  if (F_leftR == 1 && F_rightR == 1 && B_leftR == 1 && B_rightR == 1)
  {
    // motor 1
    analogWrite(en1, 255);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    // motor 2
    analogWrite(en2, 255);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);

    water_pump();
  }
}

void stop_motor()
{
    // motor 1
    analogWrite(en1, 255);
    digitalWrite(in1, LOW);
    digitalWrite(in2, LOW);
    // motor 2
    analogWrite(en2, 255);
    digitalWrite(in3, LOW);
    digitalWrite(in4, LOW);
}

void loop() 
{
  // put your main code here, to run repeatedly:
  // flame sensors
  F_leftR = digitalRead(F_left);
  F_rightR = digitalRead(F_right);
  B_leftR = digitalRead(B_left);
  B_rightR = digitalRead(B_right);
  middleR = digitalRead(middle);
  
  if (F_leftR == 1 && F_rightR == 1 && B_leftR == 1 && B_rightR == 1 && middleR == 1)
  {
    Serial.println("No Fire");
  }
  else if (F_leftR == 1 && B_leftR == 1 && B_rightR == 1 && middleR == 1)
  {
    
    
    turn_right();
    delay(2550);
    
    
   
  }
  else if (F_rightR == 1 && B_leftR == 1 && B_rightR == 1 && middleR == 1) 
  {
    
    
    turn_left();
    delay(2550);
    
    
  }
  else if (F_leftR == 1 && F_rightR == 1 && B_leftR == 1 && middleR == 1)
  {
   
   turn_right();
   delay(4000);
   
   
  }
  else if (F_leftR == 1 && F_rightR == 1 && B_rightR == 1 && middleR == 1)
  {
    
    
    turn_left();
    delay(4000);
    
    
  }
  else if (F_leftR == 1 && F_rightR == 1 && B_leftR == 1 && B_rightR == 1)
  {
    // motor 1
   analogWrite(en1, 255);
   digitalWrite(in1, LOW);
   digitalWrite(in2, LOW);
   // motor 2
   analogWrite(en2, 255);
   digitalWrite(in3, LOW);
   digitalWrite(in4, LOW);
   delay(500);
   analogWrite(en1, 200);
   digitalWrite(in1, LOW);
   digitalWrite(in2, HIGH);
   // motor 2
   analogWrite(en2, 200);
   digitalWrite(in3, HIGH);
   digitalWrite(in4, LOW);
   delay(1000);
    
    water_pump();
  }
  else
  {
    Serial.println("Fire All Around");
  }

  // ultrasonic sensor
  delay(100);
  // The sensor is triggered by a HIGH pulse of 10 or more microseconds.
  // Give a short LOW pulse beforehand to ensure a clean HIGH pulse:
  digitalWrite(trigPin, LOW);
  delayMicroseconds(5);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
 
  // Read the signal from the sensor: a HIGH pulse whose
  // duration is the time (in microseconds) from the sending
  // of the ping to the reception of its echo off of an object.
  pinMode(echoPin, INPUT);
  duration = pulseIn(echoPin, HIGH);
 
  // Convert the time into a distance
  cm = (duration/2) / 29.1;     // Divide by 29.1 or multiply by 0.0343
  Serial.print(cm);
  Serial.print("cm");
  Serial.println();
  if (cm > 15)
  {
   forward_motor();
  }
  else
  {
   reverse_motor();
  }
   
}

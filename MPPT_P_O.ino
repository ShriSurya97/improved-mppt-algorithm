//#include <LiquidCrystal.h>
//LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

float sensorValue1 = 0;
float sensorValue2 = 0;
float voltageValue = 0;
float currentValue = 0;
float Power_now = 0, Power_anc = 0, voltage_anc = 0, Power_new = 0;
float delta = 3;
float pwm = 128;
void setup()
{
  Serial.begin(9600);
  //pinMode(6, OUTPUT);
  //lcd.begin(16, 2);
}

void loop()
{
  sensorValue1 = analogRead(A1);
  sensorValue2 = analogRead(A0);
  voltageValue = (sensorValue1 * 5.0 / 1023.0) * 5;
  currentValue = (sensorValue2 * 5.0 / 1023.0);
  //lcd.setCursor(0, 0);
  Power_now = voltageValue * currentValue;

  Serial.print("Ppv=");
  Serial.println(" ");
  Serial.print(Power_now);
  Serial.println(" ");
  Serial.print("W");
  Serial.println(" ");
  Serial.print(pwm);
  Serial.println(" ");
  //lcd.setCursor(0, 1);
  Serial.print("V=");
  Serial.println(" ");
  Serial.print(voltageValue);
  Serial.println(" ");
  Serial.print("I=");
  Serial.println(" ");
  Serial.print(currentValue);
  Serial.println(" ");
  Serial.print("New Power");
  Serial.print(Power_new);
  Serial.println(" ");
  delay(5000);



  if (Power_now > Power_anc)
  { if (voltageValue > voltage_anc)
      pwm = pwm - delta;
    else
      pwm = pwm + delta;
  }
  else
  {
    if (voltageValue > voltage_anc)
      pwm = pwm + delta;
    else
      pwm = pwm - delta;
  }
  Power_anc = Power_now;
  voltage_anc = voltageValue;
  if (pwm < 20)
    pwm = 20;
  if (pwm > 150)
    pwm = 150;
 

  Power_new = (voltageValue * currentValue);
  analogWrite(6, pwm);
}

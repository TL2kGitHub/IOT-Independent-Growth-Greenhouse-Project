void MTR_PMP_LCD() {

  //Soil Moisture Code
  float SM = 0;
  for (int i = 0; i <= 100; i++) {
    SM = SM + analogRead(SensorPin);
    delay(1);
  }
  //To get relative percentage for soil moisture content
  SM = SM / 900.0;

  //LDR and RGB Code
  int ldrStatus = analogRead(LDR);
  //Checks if the light amount is comparable to a dull day
  if (ldrStatus <= 550 && ldrStatus >= 400) {
    for (int i = 0; i < NUML; i++) {
      //Blue colour of RGB
      pixels.setPixelColor(i, pixels.Color(0, 0, 255));
      pixels.show();
    }
  }
  else {
    for (int i = 0; i < NUML; i++) {
      pixels.setPixelColor(i, pixels.Color(0, 0, 0));
      pixels.show();
    }
  }
  //Turns on pump if soil moisture is less than 30%
  if (SM <= 30) {
    digitalWrite(PMP, HIGH);
  }
  //Turns off pump if soil moisture is greater than 50%
  else if (SM >= 50) {
    digitalWrite(PMP, LOW);
  }
//Turns on fan if humidity is greater than 70%
  if (DHT.humidity >= 70) {
    digitalWrite(MTR, HIGH);
  }
  else {
    digitalWrite(MTR, LOW);
  }


  int reading = DHT.read11(DHT11_PIN);
 
  lcd.setCursor(0, 0);
  lcd.print("Temp:");
  lcd.print(DHT.temperature);//Prints the temperature on LCD
  lcd.print((char)223);
  lcd.print("C");
  lcd.print(" HM:");
  lcd.setCursor(0, 1);
  lcd.print(DHT.humidity);//Prints the humidity on LCD 
  lcd.print("%");
  lcd.print(" SM:");
  lcd.print(SM);//Prints the soil moisture on LCD 
  lcd.print("%");

  delay(1000);//(1000)
}

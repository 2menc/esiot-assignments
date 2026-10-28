// #include <LiquidCrystal_I2C.h> 

// LiquidCrystal_I2C lcd = LiquidCrystal_I2C(0x27,20,4); 

void setup() {
  // lcd.init();
  // lcd.backlight();
  Serial.begin(9600);
}

void loop() {
  int value = analogRead(A0);

  float value_in_Volt = ((float) value)* 0.00488;   //  5 Volt / 1024 range = 0.00488
 
  /* 
   * Linear characteristics for sensors:
   * - Y(X) = K*X + Y0
   * For TMP36 - Y(X) = Voltage V, X = Temperature T
   * - V(T) = K*T + V0 = 0.01 * T + 0.5
   *  (From the datasheet:
   *   - output scale factor of 10 mV/°C. This means K = 10 mV/C = 0.01 
   *   - 750 mV output at 25°C: 0.0750 = 0.01*25 + V0 => V0 = 0.5)
   * - Reversing the formula: T(V) = (V - 0.5)/0.01
   */
  float value_in_C = (value_in_Volt - 0.5) / 0.01;  

  Serial.println(value_in_C);
  
  /*
  lcd.setCursor(2, 1); // Set the cursor on the third column and first row.
  lcd.print(String("Value in C: ") + value_in_C);
  */
  delay(1000);
}

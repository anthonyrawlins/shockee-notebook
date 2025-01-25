const int maxAngle = 360;  // Full rotation in degrees
float currentAngle = 0.0;  // Current angle of the wheel
float rpm = 10.0;          // Default RPM (revolutions per minute)
unsigned long lastUpdateTime = 0; // Last update time in milliseconds
float msPerDegree = 60000.0 / (rpm * maxAngle);;


void setup() {
    Serial.begin(250000);

    // Wait for the serial input before writing a result
    Serial.println("READY");
}

String data_result() {

    unsigned long currentTime = millis();
    unsigned long elapsedTime = currentTime - lastUpdateTime;

    if (elapsedTime >= msPerDegree) {
        float degreesToAdd = elapsedTime / msPerDegree;
        currentAngle += degreesToAdd;
        currentAngle = fmod(currentAngle, maxAngle);
        lastUpdateTime = currentTime; // Reset the timer
    }


    static int maximum_stroke_length = 78.0;
    static int millivolts_per_unit = 4.9;

    // The Analogue Pins on the UNO R3    
    int a0 = analogRead(A0);
    int a1 = analogRead(A1);
    int a2 = analogRead(A2);
    int a3 = analogRead(A3);
    int a4 = analogRead(A4);
    int a5 = analogRead(A5);

    /*
    Reads the value from the specified analog pin.
    Arduino boards contain a multichannel, 10-bit analog to digital converter.
    This means that it will map input voltages
    between 0 and the operating voltage(5V or 3.3V)
    into integer values between 0 and 1023.
    
    On an Arduino UNO, this yields a resolution between
    readings of: 5 volts / 1024 units or, 0.0049 volts (4.9 mV) per unit. 
    */

    float mv = a0 / 1023.0 * millivolts_per_unit; //millivolts
    float mm = a0 / 1023.0 * maximum_stroke_length;

    // TODO
    float newtons = 0.0;
    float degrees = currentAngle;
    float radians = currentAngle * (PI / 180.0);

    // Output formatting
    /*
        millivolts - a0
        millivolts - a1
        millivolts - a2
        millivolts - a3
        millivolts - a4
        millivolts - a5
        millimeters
        Newtons
        Angle radians
        Angle degrees    
    */
    // Start JSON object or named dict...
    Serial.print("{ ");

    // Analogue Pins raw data...
    Serial.print("'a0': ");
    Serial.print(a0);
    Serial.print(", ");
    
    // Length
    Serial.print("'s (mm)': ");
    Serial.print(mm, 3); // 3 decimal places
    Serial.print(", ");

    // Force
    Serial.print("'n (N)': ");
    Serial.print(newtons, 5);
    Serial.print(", ");

    // Angle
    Serial.print("'a (r)': ");
    Serial.print(radians, 4);
    Serial.print(", ");

    Serial.print("'a (d)': ");
    Serial.print(degrees, 0);
    // Close the Object
    Serial.println(" }");

}

void loop() {
  
      data_result();
      delay(5);
}

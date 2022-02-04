//collects data from an analog sensor

int sensorpin = 0;                 // analog pin used to connect the sharp sensor
int val = 0;                 // variable to store the values from sensor(initially zero)

void setup()
{
  Serial.begin(9600);               // starts the serial monitor
}
 
void loop()
{
  float ADCValue = (float)analogRead(sensorpin);

    // Convert in millimeters and return distance
    val = 200.3775040589502
            - 2.2657665648980 * ADCValue
            + 0.0116395328796 * ADCValue * ADCValue
            - 0.0000299194195 * ADCValue * ADCValue * ADCValue
            + 0.0000000374087 * ADCValue * ADCValue * ADCValue * ADCValue
            - 0.0000000000181 * ADCValue * ADCValue * ADCValue * ADCValue * ADCValue;
  Serial.println(val);            // prints the value of the sensor to the serial monitor
  delay(400);                    // wait for this much time before printing next value
}



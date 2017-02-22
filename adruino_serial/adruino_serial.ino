
#define PSU_pin A0 // assigning psu to pin A0
#define serialbufferSize 50
#define LED1 11
#define LED2 10
#define LED3 9
#define LED4 6
#define LED5 5
#define LED6 3


char inputBuffer[serialbufferSize]   ;
int serialIndex = 0; // keep track of where we are in the buffer

void setup() {
  // put your setup code here, to run once:

  Serial.begin(9600); // baud rate
  pinMode(PSU_pin,INPUT); // setting pin to input mode

  pinMode(LED1,OUTPUT); // setting pin to output mode
  pinMode(LED2,OUTPUT); // setting pin to output mode
  pinMode(LED3,OUTPUT); // setting pin to output mode
  pinMode(LED4,OUTPUT); // setting pin to output mode
  pinMode(LED5,OUTPUT); // setting pin to output mode
  pinMode(LED6,OUTPUT); // setting pin to output mode
}

void loop() {
  // put your main code here, to run repeatedly:
  double scaled_ADC_voltage;

  CheckSerial();

  scaled_ADC_voltage = ReadSerial();
  Serial.println(String(scaled_ADC_voltage));  // sends voltage at pin to serial port

}

double ReadSerial(){
  double adc_value;
  double voltage;  // voltage value from pin
  double scaled_voltage;

  adc_value = analogRead(PSU_pin);   // read psu pin and putting value in voltage variable

  scaled_voltage = (20*adc_value)/1023 - 10;

  return scaled_voltage;
}

void CheckSerial()
{
  boolean lineFound = false;
  // if there's any serial available, read it:
  while (Serial.available() > 0) {
    //Read a character as it comes in:
    //currently this will throw away anything after the buffer is full or the \n is detected
    char charBuffer = Serial.read();
      if (charBuffer == 'q') {
           inputBuffer[serialIndex] = 0; // terminate the string
           lineFound = (serialIndex > 0); // only good if we sent more than an empty line
           serialIndex=0; // reset for next line of data
         }
         else if(charBuffer == '\r') {
           // Just ignore the Carrage return, were only interested in new line
         }
         else if(serialIndex < serialbufferSize && lineFound == false) {
           /*Place the character in the string buffer:*/
           inputBuffer[serialIndex++] = charBuffer; // auto increment index
         }
  }// End of While

  if(lineFound)
  {
      if(strcmp(inputBuffer, "1") == 0)
       {
          digitalWrite(LED1, HIGH);   // turns on LED if theres a match
       }
      else if(strcmp(inputBuffer, "2") == 0)
      {
         digitalWrite(LED2, HIGH);   // turns on LED if theres a match
      }
      else if(strcmp(inputBuffer, "3") == 0)
      {
         digitalWrite(LED3, HIGH);   // turns on LED if theres a match
      }
      else if(strcmp(inputBuffer, "4") == 0)
      {
         digitalWrite(LED4, HIGH);   // turns on LED if theres a match
      }
      else if(strcmp(inputBuffer, "5") == 0)
      {
         digitalWrite(LED5, HIGH);   // turns on LED if theres a match
      }
      else if(strcmp(inputBuffer, "6") == 0)
      {
         digitalWrite(LED6, HIGH);   // turns on LED if theres a match
      }
      else if(strcmp(inputBuffer, "reset") == 0)
      {
         reset_led();
      }

  }

}// End of CheckSerial()

void reset_led(){
  
  digitalWrite(LED1, LOW);   // turns off LED if theres a match
  digitalWrite(LED2, LOW);   // turns off LED if theres a match
  digitalWrite(LED3, LOW);   // turns off LED if theres a match
  digitalWrite(LED4, LOW);   // turns off LED if theres a match
  digitalWrite(LED5, LOW);   // turns off LED if theres a match
  digitalWrite(LED6, LOW);   // turns off LED if theres a match
}


#define PSU_pin A0 // assigning psu to pin A0
#define serialbufferSize 50 

char inputBuffer[serialbufferSize]   ; 
int serialIndex = 0; // keep track of where we are in the buffer

void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600); // baud rate
  pinMode(PSU_pin,INPUT); // setting pin to input mode

  pinMode(13,OUTPUT); // setting pin to input mode
}

void loop() {
  // put your main code here, to run repeatedly:
  double scaled_voltage;

  if(CheckSerial()){
   if(strcmp(inputBuffer, "hello") == 0)
    {
      //Serial.println(inputBuffer); // echos value READ from serial port
      digitalWrite(13, HIGH);
    }

  }
  
  scaled_voltage = ReadSerial();
  Serial.println(String(scaled_voltage));  // sends voltage at pin to serial port
  digitalWrite(13, LOW);
  

}



double ReadSerial(){
  double adc_value;
  double voltage;  // voltage value from pin
  double scaled_voltage;
  

  adc_value = analogRead(PSU_pin);   // read psu pin and putting value in voltage variable
  voltage = adc_value;
  
  if(voltage == 0){
    voltage = 1;
  }
  
  voltage*=5;     //
  voltage/=1024;  // conversion from adc value to voltage

  scaled_voltage = (20*adc_value)/1023 - 10;

  return scaled_voltage;
}

boolean CheckSerial()
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
  return lineFound;
}// End of CheckSerial()


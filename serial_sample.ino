
int PSU_pin = A0; // assigning psu to pin A0
double adc_value;
double voltage;  // voltage value from pin
float m = 0.01955034213; // gradient
double scaled_voltage;
int c = -10;


void setup() {
  // put your setup code here, to run once:
  
  Serial.begin(9600); // baud rate
  pinMode(PSU_pin,INPUT); // setting pin to input mode
}

void loop() {
  // put your main code here, to run repeatedly:

  adc_value = analogRead(PSU_pin);   // read psu pin and putting value in voltage variable
  voltage = adc_value;
  
  if(voltage == 0){
    voltage = 1;
  }
  
  voltage*=5;     //
  voltage/=1024;  // conversion from adc value to voltage

  scaled_voltage = (20*adc_value)/1023 + c;

  Serial.println(String(scaled_voltage));  // 
  
  
}

#define SLAVE '1'
#define PIN_LED 13
#define SS 53

const int RX_TX =  8;


void setup() 
{
  Serial.begin(9600);//velocidade de bits por segundo comunication
  pinMode (PIN_LED, OUTPUT); 
  pinMode (RX_TX, OUTPUT);
  digitalWrite(RX_TX, LOW);  
  delay(500);
}

void loop() 
{
 serial_handle();
 temperature_handle();
}








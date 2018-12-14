char protocol[5], security;
int counter = 0;

//data link com o master 
void serial_handle (void) 
{
  if(Serial.available() > 0) 
  {
    security = Serial.read();
    //Serial.println(security);
    if (security == 'Z')
    {
      counter = 0;
      //Serial.println("Sistema Resetado");
      return;
    }
    protocol [counter]= security;
    counter ++;
    if (counter > 4)
    {
      //Serial.println("Protocol Handle");
       protocol_handle(&protocol[0]);
       counter=0;
    }
   }
}



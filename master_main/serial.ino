
static char security, security2, protocol[5], protocol2[5];
static int counter = 0, counter2 = 0;


// Data link com o computador
void serial_handle(void) 
{
    if(Serial.available() > 0) 
    {
        security = Serial.read();
    
        if (security == 'Z')
        {
          counter   = 0;
          counter2  = 0;
          Ser1.write('Z');
          //Serial.println("Sistema Resetado");
          return;
        }
    
        protocol[counter]= security;
        counter++;
    
        if(counter > 4)
        {
            counter=0;
            //Serial.println("Protocol Handle");
            protocol_handle(&protocol[0]); 
            digitalWrite(RX_TX, HIGH);
            Ser1.write(protocol[0]);
            Ser1.write(protocol[1]);
            Ser1.write(protocol[2]);
            Ser1.write(protocol[3]);
            Ser1.write(protocol[4]);
            digitalWrite(RX_TX, LOW);
        }
   }
}

//data link com o SLAVES
void software_serial_handle (void) 
{
    if(Ser1.available() > 0)
    {
        security2 = Ser1.read();

        if(security2 == 'Z')
        {
            counter2  = 0;
            counter   = 0;
            return;  
        }
      
        protocol2[counter2] = security2;   
        counter2++;

        if(counter2 > 4)
        {
            counter2 = 0;
            protocol_handle(&protocol2[0]);  
        }
    }
}

// Envia os comandos recebidos dos slaves para o computador
void serial_pc_write(void)
{
    Serial.write(protocol2[0]);
    Serial.write(protocol2[1]);
    Serial.write(protocol2[2]);
    Serial.write(protocol2[3]);
    Serial.write(protocol2[4]);
}

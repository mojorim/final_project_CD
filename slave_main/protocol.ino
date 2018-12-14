//COMANDO
#define READ 'R'
#define WRITE 'W'
#define ANSWER 'A'

//REGISTRADOR
#define TEMP 'T'
#define SP_TEMP 'U'
#define LED 'L'
#define LED_STATUS 'M'
#define SYSTEM_STATUS 'S'

void protocol_handle (char*data)
{
  if (data[0] == SLAVE)
  {
    //Serial.println("SLAVE");
    command_handle(data);
  }
}

void command_handle (char*data)
{
  //Serial.println("COMMAND");
  switch (data[1])
  {
    case READ:
    read_handle(data);
    break;

    case WRITE:
    write_handle(data);
    break;

    case ANSWER:
    break;
  }
}

void read_handle (char*data)
{
  int temp=0, sp_temp=0, sys_status=0, led_status=0;
  char c_temp[2], c_answer[5];
  
  //Serial.println("READ");
  switch (data[2])
  {
    case TEMP:
    //Serial.println("TEMP");
    temp=temperature_get();
    int_to_string(temp,c_temp);
    c_answer[2] = TEMP;
    c_answer[3] = c_temp[0];
    c_answer[4] = c_temp[1];
    answer_handle (c_answer);
    break;

    case SP_TEMP:
    //Serial.println("SP_TEMP");
    sp_temp=temperature_get_sp();
    int_to_string(sp_temp,c_temp);
    c_answer[2] = SP_TEMP;
    c_answer[3] = c_temp[0];
    c_answer[4] = c_temp[1];
    answer_handle (c_answer);
    break;

    case LED_STATUS:
    //Serial.println("LED_STATUS");
    led_status = digitalRead (PIN_LED);
    int_to_string(led_status,c_temp);
    c_answer[2] = LED_STATUS;
    c_answer[3] = c_temp[0];
    c_answer[4] = c_temp[1];
    answer_handle (c_answer);
    break;

    case SYSTEM_STATUS:
    //Serial.println("SYSTEM_STATUS");
    sys_status = status_get ();
    int_to_string(sys_status,c_temp);
    c_answer[2] = SYSTEM_STATUS;
    c_answer[3] = c_temp[0];
    c_answer[4] = c_temp[1];
    answer_handle (c_answer);
    break;
  }
}

void write_handle (char*data)
{
  int s_temp=0;

  //Serial.println("WRITE");
  switch (data[2])
  { 
   case LED:
    if (data[4] == '1') digitalWrite(PIN_LED,HIGH);
    else digitalWrite(PIN_LED,LOW);
    break;

    case SP_TEMP:
    s_temp = string_to_int(&data[3]);
    temperature_set_sp (s_temp);
    break; 
  }
}

void answer_handle (char*data)
{
    //Serial.println("ANSWER");
    digitalWrite(RX_TX, HIGH); 
    Serial.write('M');
    Serial.write('A');
    Serial.write(data[2]);
    Serial.write(data[3]);
    Serial.write(data[4]);
    digitalWrite(RX_TX, LOW); 
}



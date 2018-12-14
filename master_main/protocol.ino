

void protocol_handle (char*data)
{
  if (data[0] == MASTER) 
  {
      serial_pc_write();
      wifi_mqtt_answer(data);
  }
  
  if(data[0] == 'W' && data[4] == '1') 
  {
      wifi_init();
      wifi_enable_set(1);                
  }
}

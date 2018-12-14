int system_status=0;

void status_set (int set)
{
  //Serial.print("System Status ");
  //Serial.println(system_status);
  system_status = set;
}

int status_get (void)
{
  //Serial.print("System Status Get ");
  //Serial.println(system_status);
  return system_status;
}


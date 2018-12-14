#include "max6675.h"

int temperatura= 0, sp_temperatura=30;
int thermoDO = 50;
int thermoCS = 53;
int thermoCLK = 52;
long int sys_tick=0, sys_tick_ant=0; 

MAX6675 thermocouple(thermoCLK, thermoCS, thermoDO);

void temperature_handle ()
{
  if (millis() > sys_tick +500) //quando milis for maior que 500ms, logo posso ler o sensor. gravo o tempo que ler o sensor
  {
    sys_tick = millis(); // quando liga arduino millis e systick = 0;
    temperatura = thermocouple.readCelsius();
  }
  if (temperatura > sp_temperatura)
  {
    status_set (1); //OVERSHOOT
  }
  else status_set (0); //
}

int temperature_get ()
{
  //Serial.print("Get Temperatura ");
  //Serial.println(temperatura);
  return temperatura;
}

int temperature_get_sp ()
{
  //Serial.print("Set Point Temperatura ");
  //Serial.println(sp_temperatura);
  return sp_temperatura;
}

void temperature_set_sp (int int_temp)
{
   sp_temperatura = int_temp;
   //Serial.print("New Set Point ");
   //Serial.println(sp_temperatura);
}

// buffer deve ter no minimo 2 posicoes
void int_to_string(int value, char * buffer)
{
    char unidade = 0, dezena = 0;
    while(value >= 10)
    {
        value -= 10;
        dezena++;
    }   
    while(value > 0)
    {
        value -= 1;
        unidade++;
    }   
    buffer[0] = dezena + '0';
    buffer[1] = unidade + '0'; 
}

int string_to_int(char * string)
{
    int data;
  
    data = (string[1] - '0')*10;
    data += (string[0] - '0');
    
    return data;
}

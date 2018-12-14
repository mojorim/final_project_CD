
//informações da rede WIFI
const char* ssid = "AndroidAP";                 //SSID da rede WIFI
const char* password =  "ownb7731";    //senha da rede wifi
 
//informações do broker MQTT - Verifique as informações geradas pelo CloudMQTT
const char* mqttServer = "m11.cloudmqtt.com";   //server
const char* mqttUser = "fagkuzua";              //user
const char* mqttPassword = "wqQvH-bBu4TH";      //password
const int mqttPort = 10077;                     //port
const char* mqttTopicSub ="MASTER";            //tópico que sera assinado
const char* mqttTopicSub2 ="casa/L2";            //tópico que sera assinado
  
WiFiClient espClient;
PubSubClient client(espClient);

#define DEBUG

static int wifi_enable = 0;

void wifi_init(void)
{
    WiFi.begin(ssid, password);
 
    while (WiFi.status() != WL_CONNECTED) 
    {
        delay(500);
        #ifdef DEBUG
        Serial.println("Conectando ao WiFi..");
        #endif
    }
    
    #ifdef DEBUG
    Serial.println("Conectado na rede WiFi");
    #endif
 
    client.setServer(mqttServer, mqttPort);
    client.setCallback(callback);
 
    while (!client.connected())
    {
        #ifdef DEBUG
        Serial.println("Conectando ao Broker MQTT...");
        #endif
 
        if (client.connect("ESP8266Client", mqttUser, mqttPassword ))
        {
            #ifdef DEBUG
            Serial.println("Conectado");  
            #endif
        }   
        else
        {
            #ifdef DEBUG 
            Serial.print("falha estado  ");
            Serial.print(client.state());
            #endif
            delay(2000);
        }
    }
 
    //subscreve no tópico
    client.subscribe(mqttTopicSub);
    client.subscribe(mqttTopicSub2);
} 

void wifi_handle(void)
{
  if(wifi_enable == 0) return;
  
  if (!client.connected()) reconect();
  client.loop();  
}

void callback(char* topic, byte* payload, unsigned int length) 
{ 
  //armazena msg recebida em uma sring
  payload[length] = '\0';
  String strMSG = String((char*)payload);
 
  #ifdef DEBUG
  Serial.print("Mensagem chegou do tópico: ");
  Serial.println(topic);
  Serial.print("Mensagem:");
  Serial.print(strMSG);
  Serial.println();
  Serial.println("-----------------------");
  #endif

  if(strMSG[0] == 'Z')
  {
     Ser1.write('Z');
  }
  else
  { 
    Ser1.write(strMSG[0]);
    Ser1.write(strMSG[1]);
    Ser1.write(strMSG[2]);
    Ser1.write(strMSG[3]);
    Ser1.write(strMSG[4]);
  }
}
 
//função pra reconectar ao servido MQTT
void reconect() 
{
    //Enquanto estiver desconectado
    while (!client.connected()) 
    {
        #ifdef DEBUG
        Serial.print("Tentando conectar ao servidor MQTT");
        #endif
     
        bool conectado = strlen(mqttUser) > 0 ?
                     client.connect("ESP8266Client", mqttUser, mqttPassword) :
                     client.connect("ESP8266Client");
 
        if(conectado) 
        {
            #ifdef DEBUG
            Serial.println("Conectado!");
            #endif
            //subscreve no tópico
            client.subscribe(mqttTopicSub, 1); //nivel de qualidade: QoS 1
        } 
        else
        {
            #ifdef DEBUG
            Serial.println("Falha durante a conexão.Code: ");
            Serial.println( String(client.state()).c_str());
            Serial.println("Tentando novamente em 10 s");
            #endif
            //Aguarda 10 segundos 
            delay(10000);
        }
    }
}

void wifi_mqtt_answer(char * data)
{
    if(wifi_enable == 0) return;
    
    client.publish("SLAVE", data);  
}

void wifi_enable_set(int enable)
{
    wifi_enable = enable;  
}

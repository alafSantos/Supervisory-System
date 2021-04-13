/*--------- Declaracao de bibliotecas necessarias ---------*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <LiquidCrystal_I2C.h>//display lcd com i2c
#include <DHT.h>//biblioteca para o sensor de temperatura e humidade
#include <DHT_U.h>//biblioteca para o sensor de temperatura e humidade
#include <Adafruit_Sensor.h>//biblioteca para o sensor de temperatura e humidade

#define DHTTYPE DHT22 //tipo do dht
#define PIN_DHT_1 12 //porta D6

#ifndef STASSID
#define STASSID "CLARO2G_AP202" //nome da rede wifi
#define STAPSK "33720690"  //senha da rede wifi
#endif

//DEFINIÇÃO DE IP FIXO PARA O NODEMCU
IPAddress ip(192,168,0,203); //COLOQUE UMA FAIXA DE IP DISPONÍVEL DO SEU ROTEADOR. EX: 192.168.1.110 **** ISSO VARIA, NO MEU CASO É: 192.168.0.175
IPAddress gateway(192,168,0,1); //GATEWAY DE CONEXÃO (ALTERE PARA O GATEWAY DO SEU ROTEADOR)
IPAddress subnet(255,255,255,0); //MASCARA DE REDE

ESP8266WebServer server(10050); //o padrao da web eh a porta 80, nao sei pq usou 10050
LiquidCrystal_I2C lcd_1(0x3F, 2, 1, 0, 4, 5, 6, 7, 3, POSITIVE);
DHT DHT_1(PIN_DHT_1,DHTTYPE,11); //Inicializa o sensor
const char *ssid = STASSID, *password = STAPSK;
float READ_TEMPERATURA = 0, READ_UMIDADE = 0;
int LCD_counter = 0, all_counter = 0, tempo_tela = 75;
boolean Conectado = false;

/*--------------- Declaracao dos Metodos ---------------*/
//Escrita no LCD
void LCD_write(int linha, String text)
{
  int max_chars = 19;
  for(int i = 0; i!=max_chars && i!=text.length(); i++)
  {
    lcd_1.setCursor(i, linha);
    lcd_1.print(text[i]);
  }
}
//Atualizacao das telas (3 telas usadas)
void LCD_Update()
{
  if (LCD_counter == tempo_tela*4 + 1)
    LCD_counter = 0;

  if (LCD_counter == 1)
  {
    Serial.println("Tela 1");
    lcd_1.clear();
    LCD_write(0, "MAC: "+String(WiFi.macAddress()));
    LCD_write(1, "IP: "+ WiFi.localIP().toString());
    LCD_write(2,"Gateway: 192.168.0.1");
    LCD_write(3,"Mask: 255.255.255.0");
  }
  if(LCD_counter == tempo_tela*2)
  {
    Serial.println("Tela 2");
    lcd_1.clear();
    LCD_write(0, "NOME: MD0"); //nome dado ao modulo
    LCD_write(1,"LOCAL: TRAFO I");
    if(Conectado == false)
      LCD_write(2, "STATUS: OFFLINE");
    else
      LCD_write(2,"STATUS: ONLINE");
  }
  if (LCD_counter == tempo_tela*3)
  {
    Serial.println("Tela 3");
    lcd_1.clear();
    LCD_write(0, "Temperatura:");
    LCD_write(1, String(READ_TEMPERATURA));
    LCD_write(2, "Umidade:");
    LCD_write(3, String(READ_UMIDADE));
  }
  LCD_counter += 1;
}

//leitura dos sensores
void makeRead()
{
  READ_TEMPERATURA =  DHT_1.readTemperature();
  READ_UMIDADE = DHT_1.readHumidity();
  Serial.print("Temperatura: ");
  Serial.println(READ_TEMPERATURA);
  Serial.print("Umidade: ");
  Serial.println(READ_UMIDADE);
}

String build_KeyValue(String key, String value)
{
  String text = "";
  text += '"';
  text += key;
  text += '"';
  text += " : ";
  text += value;
  return text;
}

//-----------------------------------------------------------------------------------------------------------
void handleRoot()
{
  //gera o código HTML que será exibido ao carregarmos a página inicial do ESP8266
  String text = "";
  text += "{";
  text += build_KeyValue("TEMPERATURA", String(READ_TEMPERATURA));
  text += ",";
  text += build_KeyValue("UMIDADE", String(READ_UMIDADE));
  text += "}";
  //faz o envio para rede
  server.send(200, "application/json", text); //200 significa retorno OK
}

void handleNotFound()
{
  String message = "File Not Found\n\n";
  message += "URI: ";
  message += server.uri();
  message += "\nMethod: ";
  message += (server.method() == HTTP_GET) ? "GET" : "POST";
  message += "\nArguments: ";
  message += server.args();
  message += "\n";
  for (uint8_t i = 0; i < server.args(); i++)
    message += " " + server.argName(i) + ": " + server.arg(i) + "\n";
  server.send(404, "text/plain", message);
}
//-----------------------------------------------------------------------------------------------------------

void setup(void)
{
  DHT_1.begin();             //inicializa o sensor de umidade e temperatura
  
  lcd_1.begin(20, 4);                 // 20x4 LCD module
  lcd_1.setBacklightPin(3, POSITIVE); // BL, BL_POL
  lcd_1.setBacklight(HIGH);

  Serial.begin(115200);
  //WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.config(ip,gateway,subnet);
  
  Serial.println("starting");
  Serial.println("");
  
  lcd_1.clear();
  LCD_write(0, "PROCURANDO A REDE");
  LCD_write(1, STASSID);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
  Conectado = true;
  Serial.println("");
  Serial.print("Connected to ");
  Serial.println(ssid);
  Serial.print("IP address: ");
  Serial.println(WiFi.localIP());

  if (MDNS.begin("esp8266"))
    Serial.println("MDNS responder started");

  server.on("/", handleRoot);
  server.on("/inline", [](){ server.send(200, "text/plain", "this works as well");});
  server.onNotFound(handleNotFound);
  server.begin();
  Serial.println("HTTP server started");

  all_counter = 0; 
}

void loop(void)
{ 
  Conectado = true;
  server.handleClient();
  MDNS.update();
  if(all_counter == 2750)
  {
    makeRead();
    LCD_Update();
    all_counter = 0;
  }
  all_counter = all_counter + 1;
}

/*--------- Declaracao de bibliotecas necessarias ---------*/
#include <ESP8266WiFi.h>
#include <WiFiClient.h>
#include <ESP8266WebServer.h>
#include <ESP8266mDNS.h>
#include <LiquidCrystal_I2C.h>//display lcd com i2c
#include <DHT.h>//biblioteca para o sensor de temperatura e humidade
#include <DHT_U.h>//biblioteca para o sensor de temperatura e humidade
#include <Adafruit_Sensor.h>//biblioteca para o sensor de temperatura e humidade

#define DHTTYPE DHT11 //tipo do dht
#define PIN_DHT_1 12 //porta D6

#ifndef STASSID
#define STASSID "CLARO2G_AP202" //nome da rede wifi
#define STAPSK "33720690"  //senha da rede wifi
#endif

//DEFINIÇÃO DE IP FIXO PARA O NODEMCU
IPAddress ip(192,168,0,203); //COLOCAR UM IP FIXO NA FAIXA DE IP DISPONÍVEL DO SEU ROTEADOR
IPAddress gateway(192,168,0,1); //GATEWAY DE CONEXÃO (ALTERE PARA O GATEWAY DO SEU ROTEADOR)
IPAddress subnet(255,255,255,0); //MASCARA DE REDE

ESP8266WebServer server(10050); //o padrao da seria a porta 80, usou-se a 10050
LiquidCrystal_I2C lcd_1(0x27, 16, 2); //por o endereco identificada
DHT DHT_1(PIN_DHT_1,DHTTYPE,11); //Inicializa o sensor
const char *ssid = STASSID, *password = STAPSK;
float READ_TEMPERATURA = 0, READ_UMIDADE = 0;
int LCD_counter = 0, all_counter = 0, tempo_tela = 50;

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
    LCD_write(0, "IP:"+WiFi.localIP().toString());
    LCD_write(1, "Porta: 10050");
  }
  if(LCD_counter == tempo_tela*2)
  {
    Serial.println("Tela 2");
    lcd_1.clear();
    LCD_write(0, "NOME: MD0"); //nome dado ao modulo
    LCD_write(1,"LOCAL: TRAFO I");
  }
  if (LCD_counter == tempo_tela*3)
  {
    Serial.println("Tela 3");
    lcd_1.clear();
    LCD_write(0, "Temp: " + String(READ_TEMPERATURA)+" oC");
    LCD_write(1, "Umid: " + String(READ_UMIDADE)+" %");
  }
  LCD_counter += 1;
}

//leitura dos sensores
void makeRead()
{
  READ_TEMPERATURA =  DHT_1.readTemperature();
  READ_UMIDADE = DHT_1.readHumidity();
  //READ_TEMPERATURA = 30;
  //READ_UMIDADE = 99;
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
  
  lcd_1.init();                
  lcd_1.backlight();

  Serial.begin(115200);
  //WiFi.mode(WIFI_STA);
  WiFi.begin(ssid, password);
  WiFi.config(ip,gateway,subnet);
  
  Serial.println("starting");
  Serial.println("");
  
  lcd_1.clear();
  LCD_write(0, "Conectando...");
  LCD_write(1, STASSID);

  while (WiFi.status() != WL_CONNECTED)
  {
    delay(500);
    Serial.print(".");
  }
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

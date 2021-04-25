#include <Wire.h>  //INCLUSÃO DE BIBLIOTECA
#include <LiquidCrystal_I2C.h> //INCLUSÃO DE BIBLIOTECA

LiquidCrystal_I2C lcd(0x27, 16, 2); //por o endereco identificada
 
void setup()
{
  lcd.init();   // INICIALIZA O DISPLAY LCD
  lcd.backlight(); // HABILITA O BACKLIGHT (LUZ DE FUNDO) 
}
 
void loop()
{
  lcd.setCursor(0, 0); //SETA A POSIÇÃO EM QUE O CURSOR INCIALIZA(LINHA 1)
  lcd.print("MASTERWALKERSHOP"); //ESCREVE O TEXTO NA PRIMEIRA LINHA DO DISPLAY LCD
  lcd.setCursor(0, 1); //SETA A POSIÇÃO EM QUE O CURSOR RECEBE O TEXTO A SER MOSTRADO(LINHA 2)      
  lcd.print("----NODEMCU----"); //ESCREVE O TEXTO NA SEGUNDA LINHA DO DISPLAY LCD
}

//-------- IDENTIFICAR O ENDEREÇO DA PORTA ----------------
/*#include <Wire.h>
#define TEMPOLEITURA 100
#define TEMPOESPERA 3000
byte endereco;
byte codigoResultado=0;
byte dispositivosEncontrados=0;

void setup() {
  Serial.begin(9600);
  Wire.begin();
  while (!Serial); 
  scanI2c();           
}

void scanI2c(){
    for (endereco=0; endereco<128; endereco++){
    Wire.beginTransmission(endereco);
    codigoResultado = Wire.endTransmission();
    if (codigoResultado==0){
      Serial.print ("Dispositivo I2c detectado no endereço: ");
      Serial.println(endereco,HEX);
      dispositivosEncontrados++;
      delay(TEMPOESPERA);

    }
    delay(TEMPOLEITURA);
  }
  if (dispositivosEncontrados>0){
    Serial.print("Foi encontrado um total de: ");
    Serial.print(dispositivosEncontrados);
    Serial.println(" dispositivos");
  }
  else{
    Serial.println("Nenhum dispositivo foi encontrado !!!");
  }
}


void loop() {

}*/

  #include "WiFi.h" // Biblioteca do ESP32
  #include "ESPAsyncWebServer.h" // Biblioteca da Craicao do Web Server
  #include "SPIFFS.h" // Biblioteca para upar o arquivo no buffer

 
//---------------Declarações de fuções ------------------------//
          
  void IRAM_ATTR gpio_isr_handler_up(void* arg);
  void iniciaVazao(gpio_num_t Port);
  static void atualizaVazao();
  volatile int pulsos_vazao = 0;
  const int portaVazao = GPIO_NUM_35;
  float vazao = 0;
  float aux;


  
//--------------------------------------------------------//


//-----------Definir a maior vazao guardada---------------//

String maior_numero(){

  
    vazao = pulsos_vazao/5.5;
    pulsos_vazao = 0;
  

  if (aux < vazao)
  {
    aux = vazao;
    return String(aux);
  }
   return String(aux);
 
}


//--------------------------------------------------------//


//------------------- Função de Leitura da Vazão-----------------//

String readvazao(){
                
vazao = pulsos_vazao/5.5;
pulsos_vazao = 0;


return String(vazao);
}
              
//--------------------------------------------------------//

//---------------- Parâmetros de conexão ------------------//

  const char* ssid = "p"; //nome da rede
  const char* pass =  "udtqcss8"; //senha da rede

//------------------------------------------------------------//

//-------------------- Inicializando o Server ---------------------//

  AsyncWebServer server(80);

//------------------------------------------------------------//

//-------------------- Fixando coneccao ----------------------//

 /* IPAddress local_IP(192, 168, 206, 197);
  IPAddress gateway(192, 168, 1, 1);
  IPAddress subnet(255, 255, 0, 0);*/
  
//------------------------------------------------------------//

void setup()
{
  
  //-------------------------- Inicia os Seriais ------------------//

  Serial.begin(115200); 

  WiFi.begin(ssid, pass); // Conectando a rede

  SPIFFS.begin(); // Inicia o arquivo interno !

//------------------------------------------------------------//

//----------------- Deixando estatico a coneccao------------------------//

/*if (!WiFi.config(local_IP, gateway, subnet)) {
    Serial.println("Flaha ao Deixar estatico o IP");
}*/
  
//------------------------------------------------------------//

//----------------------Conectando a rede WiFi------------------------//

  while (WiFi.status() != WL_CONNECTED) {
    
    delay(500);
    Serial.println("Conectando ao WiFi..");
    
  }
 
  Serial.println("Connected to the WiFi network");

  Serial.println("");
  Serial.println("WiFi conecatado.");
  Serial.println("Endereco IP: ");
  Serial.println(WiFi.localIP());  // Printando a rede que foi conectado
  
//------------------------------------------------------------//
  

  Serial.println("Servidor inicializado"); // Mostra o Servidor Inicializado


  iniciaVazao((gpio_num_t) portaVazao);



//------------------- Faz a requisicao do Arquivo Mandado via SPIFFS -----------------//
 server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send(SPIFFS, "/index.html");
  });


//------------------------- Faz a requisicao e substitui no codigo o valor Colocado na variavel "readvazao()" -----------//

  server.on("/vazao", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", readvazao().c_str());
  });
//----------------------------------------------//

  server.on("/mr_num", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/plain", maior_numero().c_str());
  });
//----------------------------------------------//

  server.begin(); // Inicializando o Servidor
}

 
void loop() 
{
  delay(2000);
  Serial.println( readvazao());
  delay(2000);
  Serial.println(maior_numero());
}


//----------------------- Funcao para ler o sensor --------------------------------//
void IRAM_ATTR gpio_isr_handler_up(void* arg)
{
  pulsos_vazao++;
  portYIELD_FROM_ISR();
}

void iniciaVazao(gpio_num_t Port){
  gpio_set_direction(Port, GPIO_MODE_INPUT);
  gpio_set_intr_type(Port, GPIO_INTR_NEGEDGE);
  gpio_set_pull_mode(Port, GPIO_PULLUP_ONLY);
  gpio_intr_enable(Port);
  gpio_install_isr_service(0);
  gpio_isr_handler_add(Port, gpio_isr_handler_up, (void*) Port);
}

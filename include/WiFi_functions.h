IPAddress ip;
String wifi;

WebServer server(80);
WebSocketsServer webSocket = WebSocketsServer(81);

void handleRoot()
{
  server.send(200,"text/html", webpageCont);
}

void setupWiFi(){
  WiFi.mode(WIFI_STA); //es un set mode, el esp está preterminado en STA+AP
  Serial.begin(115200); //Comunicación en monitor serie
  WiFiManager wm; //Creamos la instancia o al modo de configuración: "); //LCD
  Serial.println(WiFi.softAPIP());
  Serial.println ("Configurar wifi"); //LCD
  wm.setConfigPortalTimeout(180); //Se establece un tiempo de espera para evitar que el ESP no se cuelgue a ser configurado en caso de un corte de suministro electrico. 
  if(!wm.autoConnect("RED-ESP32")){
        Serial.print("No hay datos guardados");} //Si no hay datos guardados, wm levanta un AP. LCD
  else { 
          Serial.print ("Existen datos guardados");} //Nos conectamos de forma automática. LCD
          wifi= WiFi.SSID();
          Serial.println ("Conectado a la red Wifi: "); //LCD
          Serial.println(wifi);
          ip = WiFi.localIP();
          Serial.print("IP: "); //LCD
          Serial.println(ip);
          server.on("/", handleRoot);
          server.begin(); webSocket.begin();
}

int parseCharToTemp(int arg_start, char arg_test[numChars])
{
    int loc_first= 0;
    int loc_second = 0;
    int loc_third = 0;

    if((int)arg_test[arg_start]>=48)
    {
        loc_first= ((int)arg_test[arg_start]-48)*100;
    }
    if((int)arg_test[arg_start+1]>=48)
    {
        loc_second= ((int)arg_test[arg_start+1]-48)*10;
    }
    if((int)arg_test[arg_start+2]>=48)
    {
        loc_third= (int)arg_test[arg_start+2]-48;
    }
    return loc_first+loc_second+loc_third;
}

String processor(const String& var){
  //Serial.println(var);
  if(var == "COFFEETEMPERATURE"){
    tempCoffee = parseCharToTemp(14, receivedChars);
    return String(tempCoffee);
  }
  else if(var == "STEAMTEMPERATURE"){
    tempSteam = parseCharToTemp(6, receivedChars);
    return String(tempSteam);
  }
  return String();
}

const char index_html[] PROGMEM = R"rawliteral(
<!DOCTYPE HTML><html>
<head>
  <title>ESP Web Server</title>
  <meta name="viewport" content="width=device-width, initial-scale=1">
  <link rel="stylesheet" href="https://use.fontawesome.com/releases/v5.7.2/css/all.css" integrity="sha384-fnmOCqbTlWIlj8LyTjo7mOUStjsKC4pOpQbqyi7RrhN7udi9RwhKkMHpvLbHG9Sr" crossorigin="anonymous">
  <link rel="icon" href="data:,">
  <style>
    html {font-family: Arial; display: inline-block; text-align: center;}
    p { font-size: 1.2rem;}
    body {  margin: 0;}
    .topnav { overflow: hidden; background-color: #50B8B4; color: white; font-size: 1rem; }
    .content { padding: 20px; }
    .card { background-color: white; box-shadow: 2px 2px 12px 1px rgba(140,140,140,.5); }
    .cards { max-width: 800px; margin: 0 auto; display: grid; grid-gap: 2rem; grid-template-columns: repeat(auto-fit, minmax(200px, 1fr)); }
    .reading { font-size: 1.4rem; }
  </style>
</head>
<body>
  <div class="topnav">
    <h1>LELIT MARA X WEBSERVER</h1>
  </div>
  <div class="content">
    <div class="cards">
      <div class="card">
        <p><i class="fas fa-thermometer-half" style="color:#059e8a;"></i> COFFEETEMPERATURE</p><p><span class="reading"><span id="coffeetemp">%COFFEETEMPERATURE%</span> &deg;C</span></p>
      </div>
      <div class="card">
        <p><i class="fas fa-thermometer-half" style="color:#00add6;"></i> STEAMTEMPERATURE</p><p><span class="reading"><span id="steamtemp">%STEAMTEMPERATURE%</span> &deg;C</span></p>
      </div>
    </div>
  </div>
<script>
if (!!window.EventSource) {
 var source = new EventSource('/events');
 
 source.addEventListener('open', function(e) {
  console.log("Events Connected");
 }, false);
 source.addEventListener('error', function(e) {
  if (e.target.readyState != EventSource.OPEN) {
    console.log("Events Disconnected");
  }
 }, false);
 
 source.addEventListener('message', function(e) {
  console.log("message", e.data);
 }, false);
 
 source.addEventListener('tempCoffee', function(e) {
  console.log("tempCoffee", e.data);
  document.getElementById("coffeetemp").innerHTML = e.data;
 }, false);
 
 source.addEventListener('tempSteam', function(e) {
  console.log("tempSteam", e.data);
  document.getElementById("steamtemp").innerHTML = e.data;
 }, false);
 
}
</script>
</body>
</html>)rawliteral";

void initWiFi() {
    WiFi.mode(WIFI_STA);
    WiFi.begin(ssid, password);
    Serial.print("Connecting to WiFi ..");
    while (WiFi.status() != WL_CONNECTED) {
        Serial.print('.');
        delay(1000);
    }
    Serial.println(WiFi.localIP());
}

void handleWebServer()
{
    server.on("/", HTTP_GET, [](AsyncWebServerRequest *request){
    request->send_P(200, "text/html", index_html, processor);
  });

  // Handle Web Server Events
  events.onConnect([](AsyncEventSourceClient *client){
    if(client->lastId()){
      Serial.printf("Client reconnected! Last message ID that it got is: %u\n", client->lastId());
    }
    // send event with message "hello!", id current millis
    // and set reconnect delay to 1 second
    client->send("hello!", NULL, millis(), 10000);
  });
  server.addHandler(&events);
  server.begin();
}

void loopWebServer()
{

    Serial.printf("CoffeeTemperature = %.2f ºC \n", tempCoffee);
    Serial.printf("SteamTemperature = %.2f ºC \n", tempSteam);
    Serial.println();

    // Send Events to the Web Server with the Sensor Readings
    events.send("ping",NULL,millis());
    events.send(String(tempCoffee).c_str(),"tempCoffee",millis());
    events.send(String(tempSteam).c_str(),"tempSteam",millis());
}
#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <WiFiUdp.h>
#include <NTPClient.h>
#include <Wire.h>
#include <Adafruit_GFX.h>
#include <Adafruit_SSD1306.h>
#include <Adafruit_NeoPixel.h>
#include <Servo.h>
#include <OneWire.h>
#include <DallasTemperature.h>
#include <NewPing.h>
const char* ssid = "oreo";
const char* password = "133333333";

const char* username = "admin";
const char* userPassword = "password";  
bool loggedIn = false;

WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 7 * 3600, 60000);
#define ONE_WIRE_BUS D3  // Change this to your actual pin
OneWire oneWire(ONE_WIRE_BUS);
DallasTemperature sensors(&oneWire);
#define SCREEN_WIDTH 128
#define SCREEN_HEIGHT 64
#define OLED_RESET -1
Adafruit_SSD1306 display(SCREEN_WIDTH, SCREEN_HEIGHT, &Wire, OLED_RESET);

#define LED_PIN D5
#define NUM_LEDS 8
Adafruit_NeoPixel strip(NUM_LEDS, LED_PIN, NEO_GRB + NEO_KHZ800);

ESP8266WebServer server(80);
Servo myServo;
// HC-SR04 pins
#define TRIGGER_PIN D7 // Change to your actual pin
#define ECHO_PIN D6    // Change to your actual pin
#define MAX_DISTANCE 200 // Maximum distance (in cm) to check

NewPing sonar(TRIGGER_PIN, ECHO_PIN, MAX_DISTANCE); // Create NewPing object
String currentText = "";
String currentColor = "255,255,255";

const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP8266 Web Server</title>
    <link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons" />
    <link href="https://fonts.googleapis.com/css2?family=Roboto:wght@300;400;700&family=Raleway:wght@400;700&display=swap" rel="stylesheet" />
    <link href="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/css/materialize.min.css" rel="stylesheet" />
    <style>
        html, body { height: 100%; display: flex; flex-direction: column; background-color: #f5f5f5; font-family: 'Roboto', sans-serif; }
        .container { flex: 1; margin-top: 50px; }
        footer { position: relative; bottom: 0; width: 100%; }
        .btn-custom { background-color: #1976d2; transition: background-color 0.3s; font-weight: 700; }
        .btn-custom:hover { background-color: #1565c0; }
        .btn-logout { background-color: #f44336; transition: background-color 0.3s; font-weight: 700; }
        .btn-logout:hover { background-color: #d32f2f; }
        .current-text { font-family: 'Raleway', sans-serif; font-size: 2em; font-weight: 700; color: #333; text-shadow: 1px 1px 2px rgba(0, 0, 0, 0.2); }
        h4 { font-family: 'Raleway', sans-serif; font-weight: 700; color: #1976d2; text-align: center; text-transform: uppercase; letter-spacing: 1px; }
        .card-panel { padding: 20px; border-radius: 10px; margin: 10px; text-align: center; transition: transform 0.3s; font-size: 1.2em; }
        .card-panel:hover { transform: scale(1.05); }
        nav { background-color: #1976d2; box-shadow: 0 2px 5px rgba(0, 0, 0, 0.2); }
        .nav-wrapper { padding: 0 20px; }
        .brand-logo { font-size: 1.8em; margin-right: 30px; }
        .nav-wrapper ul li { margin-left: 20px; }
        .nav-wrapper ul li a { padding: 10px 15px; transition: background-color 0.3s; }
        .nav-wrapper ul li a:hover { background-color: rgba(255, 255, 255, 0.1); }
        .btn-logout { margin-left: 20px; }
    </style>
</head>
<body>
 <div id="navbar" style="display: none;">
             <nav>
            <div class="nav-wrapper">
                <a href="/" class="brand-logo">ESP8266 Display</a>
                <ul id="nav-mobile" class="right hide-on-med-and-down">
                    <li>
                        <a href="/" class="waves-effect waves-light">
                            <i class="material-icons left">home</i>Home
                        </a>
                    </li>
                    <li>
                        <a href="/secondPage" class="waves-effect waves-light">
                            <i class="material-icons left">pageview</i>Second Page
                        </a>
                    </li>
                    <li>
                        <button id="logoutButton" class="btn btn-logout waves-effect waves-light" onclick="logout()">
                           Logout
                        </button>
                    </li>
                </ul>
            </div>
        </nav>
        </div>
    <div class="container">
       
        <div class="row">
            <div class="col s12">
                <h4>Sensors Control on <span>Web Server</span></h4>
            </div>
        </div>
        <div id="loginSection" class="row" style="display: none;">
            <form id="loginForm" class="col s12">
                <div class="input-field">
                    <input id="username" type="text" name="username" class="validate" required>
                    <label for="username">Username</label>
                </div>
                <div class="input-field">
                    <input id="password" type="password" name="password" class="validate" required>
                    <label for="password">Password</label>
                </div>
                <div class="center-align">
                    <button type="submit" class="btn waves-effect waves-light btn-custom">
                        Login
                        <i class="material-icons right">login</i>
                    </button>
                </div>
            </form>
        </div>
        <div id="textSection" class="row" style="display: none;">
            <form id="textForm" class="col s12">
                <div class="input-field">
                    <input id="text" type="text" name="TextContents" class="validate" required>
                    <label for="text">Enter text here</label>
                </div>
                <div class="input-field">
                    <input type="color" id="colorPicker" value="#ffffff">
                    <label for="colorPicker">Pick a Color</label>
                </div>
                <div class="input-field">
                    <label for="servoSlider">Control Servo Angle</label>
                    <input type="range" id="servoSlider" min="0" max="180" value="90" />
                    <span id="servoValue">90</span> degrees
                </div>
                <div class="center-align">
                    <button type="submit" id="submitTextButton" class="btn waves-effect waves-light btn-custom">
                        Submit Text
                        <i class="material-icons right">send</i>
                    </button>
                    <button type="submit" id="submitColorButton" class="btn waves-effect waves-light btn-custom" style="margin-left: 10px;">
                        Submit Color
                        <i class="material-icons right">color_lens</i>
                    </button>
                </div>
            </form>
        </div>
        <div class="row">
            <div id="currentText" class="center-align">
                <p class="current-text">Current Text: <span id="displayedText">{CURRENT_TEXT}</span></p>
            </div>
        </div>
    </div>
    <footer class="page-footer" style="background-color: #1976d2; margin-top: auto;">
        <div class="container">
            <div class="row">
                <div class="col s12">
                    <p style="font-size:1.8em;" class="center-align white-text">สมาชิกภายในกลุ่ม</p>
                </div>
            </div>
            <div class="row">
                <div class="col s12 m3"><div class="card-panel teal darken-1"><span class="white-text">นายภูธนพัฒน์ หนูแก้ว<br>ID: 652021037</span></div></div>
                <div class="col s12 m3"><div class="card-panel amber darken-1"><span class="white-text">นายธนวงศ์ กวดกิจการ<br>ID: 652021053</span></div></div>
                <div class="col s12 m3"><div class="card-panel deep-purple darken-1"><span class="white-text">นายรัฐภูมิ แสงทอง<br>ID: 652021066</span></div></div>
                <div class="col s12 m3"><div class="card-panel lime darken-1"><span class="white-text">นายสกรรจ วกกุม<br>ID: 652021073</span></div></div>
            </div>
        </div>
    </footer>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/js/materialize.min.js"></script>
    <script>
        document.addEventListener('DOMContentLoaded', function() {
            fetch('/checkLogin').then(response => response.json()).then(data => {
                if (data.loggedIn) {
                    document.getElementById('navbar').style.display = 'block';
                    document.getElementById('loginSection').style.display = 'none';
                    document.getElementById('textSection').style.display = 'block';
                    document.getElementById('displayedText').innerText = data.currentText;
                } else {
                    document.getElementById('loginSection').style.display = 'block';
                }
            });
        });

         document.getElementById('loginForm').addEventListener('submit', function(event) {
            event.preventDefault();
            fetch('/login', { method: 'POST', body: new URLSearchParams(new FormData(this)) })
            .then(response => response.text()).then(data => {
                if (data.includes("successful")) window.location.reload();
                else alert(data);
            });
        });

        document.getElementById('submitTextButton').addEventListener('click', function(event) {
            event.preventDefault();
            const text = document.getElementById('text').value;
            fetch('/setText', { method: 'POST', body: new URLSearchParams({ TextContents: text }) })
            .then(response => response.text()).then(data => {
                document.getElementById('displayedText').innerText = data;
            });
        });

        document.getElementById('submitColorButton').addEventListener('click', function(event) {
            event.preventDefault();
            const color = document.getElementById('colorPicker').value;
            fetch('/setColor', { method: 'POST', body: new URLSearchParams({ LEDColor: color }) })
            .then(response => response.text()).then(data => {
                alert(data);
            });
        });

        document.getElementById('servoSlider').addEventListener('input', function() {
            const angle = this.value;
            document.getElementById('servoValue').innerText = angle;
            fetch('/setServo', { method: 'POST', body: new URLSearchParams({ servoAngle: angle }) });
        });

        document.getElementById('logoutButton').addEventListener('click', function() {
            fetch('/logout', { method: 'POST' })
            .then(response => response.text()).then(data => {
                if (data.includes("Logged out")) window.location.reload();
                else alert(data);
            });
        });
    </script>
</body>
</html>
)rawliteral";

const char SECOND_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>Second Page</title>
    <script>
        let ldrData = [];
        const maxDataPoints = 20; // Limit the number of data points displayed

        setInterval(() => {
            fetch('/getTemperature').then(response => response.text()).then(temp => {
                document.getElementById('displayedTemp').innerText = temp;
            });
            fetch('/getLightValue').then(response => response.text()).then(light => {
                const lightValue = parseFloat(light);
                if (!isNaN(lightValue) && lightValue >= 0 && lightValue <= 1023) {
                    ldrData.push(lightValue);
                    if (ldrData.length > maxDataPoints) {
                        ldrData.shift(); // Remove the oldest data point
                    }
                    document.getElementById('displayedLight').innerText = light;
                    drawChart();
                }
            });
            fetch('/getDistance').then(response => response.text()).then(distance => {
                document.getElementById('displayedDistance').innerText = distance;
            });
        }, 1000);

       function drawChart() {
    const canvas = document.getElementById('lightChart');
    const ctx = canvas.getContext('2d');
    ctx.clearRect(0, 0, canvas.width, canvas.height);

    const padding = 40;
    const width = canvas.width - 2 * padding;
    const height = canvas.height - 2 * padding;
    const maxValue = Math.max(...ldrData, 1023); // Set max value to 1023

    // Draw axes
    ctx.beginPath();
    ctx.moveTo(padding, padding);
    ctx.lineTo(padding, height + padding);
    ctx.lineTo(width + padding, height + padding);
    ctx.strokeStyle = '#2980b9';
    ctx.stroke();

    // X-axis label
    ctx.fillStyle = '#000';
    ctx.font = '12px Arial';
    ctx.fillText('Light Bar', width / 2 + padding, height + padding + 20);

    // Y-axis label
    ctx.save();
    ctx.translate(20, height / 2 + padding); // Position for Y label
    ctx.rotate(-Math.PI / 2); // Rotate to make it vertical
    ctx.restore();

    // Draw LDR data
    ctx.beginPath();
    ctx.strokeStyle = 'rgb(75, 192, 192)';
    ctx.lineWidth = 2;
    for (let i = 0; i < ldrData.length; i++) {
        const x = padding + (i * width / maxDataPoints);
        const y = height + padding - (ldrData[i] / maxValue) * height;
        if (i === 0) {
            ctx.moveTo(x, y);
        } else {
            ctx.lineTo(x, y);
        }

        // Draw data point label
        ctx.fillStyle = '#000'; // Black color for text
        ctx.font = '12px Arial';
        ctx.fillText(ldrData[i], x - 10, y - 10); // Adjust position to avoid overlap
    }
    ctx.stroke();

    // Draw data points
    ctx.fillStyle = 'rgb(75, 192, 192)';
    for (let i = 0; i < ldrData.length; i++) {
        const x = padding + (i * width / maxDataPoints);
        const y = height + padding - (ldrData[i] / maxValue) * height;
        ctx.beginPath();
        ctx.arc(x, y, 3, 0, Math.PI * 2);
        ctx.fill();
    }

    // Draw Y-axis ticks
    const yTicks = [0, 255, 511, 767, 1023];
    for (let i = 0; i < yTicks.length; i++) {
        const y = height + padding - (yTicks[i] / maxValue) * height;
        ctx.fillText(yTicks[i], padding - 30, y + 5); // Adjust position to avoid overlap
    }
}
    </script>
    <link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons" />
    <link href="https://fonts.googleapis.com/css2?family=Roboto:wght@300;400;700&family=Raleway:wght@400;700&display=swap" rel="stylesheet" />
    <link href="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/css/materialize.min.css" rel="stylesheet" />
    <style>
        html, body { height: 100%; display: flex; flex-direction: column; background-color: #f5f5f5; font-family: 'Roboto', sans-serif; }
        .container { flex: 1; margin-top: 50px; }
        footer { position: relative; bottom: 0; width: 100%; }
        .btn-custom { background-color: #1976d2; transition: background-color 0.3s; font-weight: 700; }
        .btn-custom:hover { background-color: #1565c0; }
        .btn-logout { background-color: #f44336; transition: background-color 0.3s; font-weight: 700; }
        .btn-logout:hover { background-color: #d32f2f; }
        .current-text { font-family: 'Raleway', sans-serif; font-size: 2em; font-weight: 700; color: #333; text-shadow: 1px 1px 2px rgba(0, 0, 0, 0.2); }
        h4 { font-family: 'Raleway', sans-serif; font-weight: 700; color: #1976d2; text-align: center; text-transform: uppercase; letter-spacing: 1px; }
        .card-panel { padding: 20px; border-radius: 10px; margin: 10px; text-align: center; transition: transform 0.3s; font-size: 1.2em; }
        .card-panel:hover { transform: scale(1.05); }
        nav { background-color: #1976d2; box-shadow: 0 2px 5px rgba(0, 0, 0, 0.2); }
        .nav-wrapper { padding: 0 20px; }
        .brand-logo { font-size: 1.8em; margin-right: 30px; }
        .nav-wrapper ul li { margin-left: 20px; }
        .nav-wrapper ul li a { padding: 10px 15px; transition: background-color 0.3s; }
        .nav-wrapper ul li a:hover { background-color: rgba(255, 255, 255, 0.1); }
        .btn-logout { margin-left: 20px; }
        .chart-container {
    display: flex;
    justify-content: center;
    align-items: center;
    height: 100%;
}
    </style>
</head>
<body>
    <div id="navbar">
        <nav>
            <div class="nav-wrapper">
                <a href="/" class="brand-logo">ESP8266 Display</a>
                <ul id="nav-mobile" class="right hide-on-med-and-down">
                    <li>
                        <a href="/" class="waves-effect waves-light">
                            <i class="material-icons left">home</i>Home
                        </a>
                    </li>
                    <li>
                        <a href="/secondPage" class="waves-effect waves-light">
                            <i class="material-icons left">pageview</i>Second Page
                        </a>
                    </li>
                    <li>
                        <button id="logoutButton" class="btn btn-logout waves-effect waves-light" onclick="logout()">
                           Logout
                        </button>
                    </li>
                </ul>
            </div>
        </nav>
    </div>
    <div class="container">
        <div class="row">
            <div class="col s12">
                <h4>Sensors Display on <span>Web Server</span></h4>
            </div>
        </div>
        <div class="row">
            <div id="currentText" class="center-align">
                <p class="current-text">Current Temperature: <span id="displayedTemp">{CURRENT_TEMP}</span></p>
                <p class="current-text">Light Value: <span id="displayedLight">{CURRENT_LIGHT}</span></p>
                <p class="current-text">Distance: <span id="displayedDistance">{CURRENT_DISTANCE}</span></p>
            </div>
        </div>
        <div class="row">
            <div class="col s12">
                <div class="chart-container" style="display: flex; justify-content: center; align-items: center; height: 100%;">
                    <canvas id="lightChart" width="400" height="200"></canvas>
                </div>
            </div>
        </div>
    </div>
    <footer class="page-footer" style="background-color: #1976d2; margin-top: auto;">
        <div class="container">
            <div class="row">
                <div class="col s12">
                    <p style="font-size:1.8em;" class="center-align white-text">สมาชิกภายในกลุ่ม</p>
                </div>
            </div>
            <div class="row">
                <div class="col s12 m3"><div class="card-panel teal darken-1"><span class="white-text">นายภูธนพัฒน์ หนูแก้ว<br>ID: 652021037</span></div></div>
                <div class="col s12 m3"><div class="card-panel amber darken-1"><span class="white-text">นายธนวงศ์ กวดกิจการ<br>ID: 652021053</span></div></div>
                <div class="col s12 m3"><div class="card-panel deep-purple darken-1"><span class="white-text">นายรัฐภูมิ แสงทอง<br>ID: 652021066</span></div></div>
                <div class="col s12 m3"><div class="card-panel lime darken-1"><span class="white-text">นายสกรรจ วกกุม<br>ID: 652021073</span></div></div>
            </div>
        </div>
    </footer>
    <script src="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/js/materialize.min.js"></script>
    <script>
        document.getElementById('logoutButton').addEventListener('click', function() {
            fetch('/logout', { method: 'POST' })
            .then(response => response.text()).then(data => {
                if (data.includes("Logged out")) window.location.href = "/";
                else alert(data);
            });
        });
    </script>
</body>
</html>
)rawliteral";
// Handle Root
void handleRoot() {
  String response = MAIN_page;
  server.send(200, "text/html", response);
}



// Handle Login
void handleLogin() {
  String user = server.arg("username");
  String pass = server.arg("password");
  if (user == username && pass == userPassword) {
    loggedIn = true;
    server.send(200, "text/plain", "Login successful");
  } else {
    server.send(401, "text/plain", "Unauthorized");
  }
}

// Handle Logout
void handleLogout() {
  loggedIn = false;
  server.send(200, "text/plain", "Logged out");
}

// Handle Setting Text
void handleSetText() {
  if (loggedIn) {
    String text = server.arg("TextContents");
    currentText = text;
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 10);
    display.println(currentText);
    display.display();
    server.send(200, "text/plain", text);
  } else {
    server.send(403, "text/plain", "Forbidden");
  }
}

// Handle Setting Color
void handleSetColor() {
  if (loggedIn) {
    String color = server.arg("LEDColor");
    currentColor = color;
    int r, g, b;
    sscanf(color.c_str(), "#%02x%02x%02x", &r, &g, &b);
    strip.fill(strip.Color(r, g, b));
    strip.show();
    server.send(200, "text/plain", "Color set");
  } else {
    server.send(403, "text/plain", "Forbidden");
  }
}

String readTemperature() {
  sensors.requestTemperatures();
  float tempC = sensors.getTempCByIndex(0);
  return String(tempC) + " °C";
}
String readLightValue() {
  int lightValue = analogRead(A0);  // Read light value from A0
  return String(lightValue);
}

void handleGetTemperature() {
  sensors.requestTemperatures();
  server.send(200, "text/plain", String(sensors.getTempCByIndex(0)) + " °C");
}
// Handle Setting Servo Angle
void handleSetServo() {
  if (loggedIn) {
    int angle = server.arg("servoAngle").toInt();
    myServo.write(angle);
    server.send(200, "text/plain", "Servo angle set to " + String(angle));
  } else {
    server.send(403, "text/plain", "Forbidden");
  }
}
String readDistance() {
  unsigned int distance = sonar.ping_cm();
  return String(distance) + " cm";
}
void handleGetDistance() {
    server.send(200, "text/plain", readDistance());
}

void handleSecondPage() {
    String temperature = String(sensors.getTempCByIndex(0)) + " °C";
    String lightValue = readLightValue();
    String distance = readDistance(); // Get distance reading
    String response = SECOND_page;
    response.replace("{CURRENT_TEMP}", temperature);
    response.replace("{CURRENT_LIGHT}", lightValue);
    response.replace("{CURRENT_DISTANCE}", distance); // Add distance to the response
    server.send(200, "text/html", response);
}
// Check Login Status
void checkLogin() {
  server.send(200, "application/json", "{\"loggedIn\": " + String(loggedIn ? "true" : "false") + ", \"currentText\": \"" + currentText + "\"}");
}

void handleGetLightValue() {
  server.send(200, "text/plain", readLightValue());
}
void displayIPAddress() {
  String ipAddress = WiFi.localIP().toString();
  display.clearDisplay();
  display.setTextSize(2);
  display.setTextColor(SSD1306_WHITE);
  display.setCursor(0, 10);
  display.println("IP Address:");
  display.setCursor(0, 30);
  display.println(ipAddress);
  display.display();
  delay(10000);
  display.clearDisplay();
}
// Setup Function
void setup() {
  sensors.begin();
  Serial.begin(115200);
  display.begin(SSD1306_SWITCHCAPVCC, 0x3C);
  display.clearDisplay();
  strip.begin();
  strip.show();
  myServo.attach(D0, 500, 2500);
  myServo.write(180);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
  }
  displayIPAddress();
  Serial.print("IP Address: ");
  Serial.println(WiFi.localIP());
  timeClient.begin();
  timeClient.setTimeOffset(7 * 3600);
  server.on("/", handleRoot);
  server.on("/secondPage", handleSecondPage);
  server.on("/login", handleLogin);
  server.on("/logout", handleLogout);
  server.on("/checkLogin", checkLogin);
  server.on("/setText", handleSetText);
  server.on("/setColor", handleSetColor);
  server.on("/setServo", handleSetServo);
  server.on("/getTemperature", handleGetTemperature);
  server.on("/getLightValue", handleGetLightValue);
  server.on("/getDistance", handleGetDistance); 
  server.begin();
}


void loop() {
  server.handleClient();
  if (loggedIn) {
    timeClient.update();
    String formattedTime = timeClient.getFormattedTime();
    String temperature = readTemperature();
    String light = readLightValue();  // Read temperature for display
    String dis = readDistance();  // Read temperature for display
    display.clearDisplay();
    display.setTextSize(1);
    display.setTextColor(SSD1306_WHITE);
    display.setCursor(0, 0);
    display.println("Time: " + formattedTime);
    display.setCursor(0, 40);
    display.println(currentText);
    display.setCursor(0, 10);
    display.println("Temp: " + temperature);  // Display temperature
    display.setCursor(0, 20);
    display.println("light: " + light);  // Display temperature
    display.setCursor(0, 30);
    display.println("distance: " + dis);  // Display temperature
    display.display();
    delay(1000);
  }
}

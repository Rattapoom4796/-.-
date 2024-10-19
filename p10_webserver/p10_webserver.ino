#include <ESP8266WiFi.h>
#include <ESP8266WebServer.h>
#include <DMDESP.h>
#include <fonts/ElektronMart6x8.h>
#include <fonts/Mono5x7.h>
#include <EEPROM.h>
#include <WiFiUdp.h>
#include <NTPClient.h>

// Wi-Fi configuration
const char* ssid = "oreo";
const char* password = "133333333";

// User credentials
const char* username = "admin"; 
const char* userPassword = "password"; 
bool loggedIn = false; 
String ipAddress = "";
bool displayingIP = true;
unsigned long ipDisplayStartTime = 0;
// NTP configuration
WiFiUDP ntpUDP;
NTPClient timeClient(ntpUDP, "pool.ntp.org", 7 * 3600, 60000); 

// DMD Configuration
#define DISPLAYS_WIDE 1
#define DISPLAYS_HIGH 1
DMDESP Disp(DISPLAYS_WIDE, DISPLAYS_HIGH);

// Scrolling Text Variables
char Text[100];
String Incoming_Text = "";
String Text_To_EEPROM = "NodeMCU ESP8266";
String Text_From_EEPROM = "";

// HTTP Server
ESP8266WebServer server(80);

// Function prototypes
void handleRoot();
void handleLogin();
void handleLogout();
void checkLogin();
void handle_Incoming_Text();
void Process_Incoming_Text();
void write_String_to_EEPROM(char add, String data);
String read_String_from_EEPROM(char add);
void Scrolling_Text(int y, uint8_t scrolling_speed);
void clearDisplay();
void displayTime();

const char MAIN_page[] PROGMEM = R"rawliteral(
<!DOCTYPE html>
<html lang="en">
<head>
    <meta charset="UTF-8">
    <meta name="viewport" content="width=device-width, initial-scale=1.0">
    <title>ESP8266 Text Display</title>
    <link rel="stylesheet" href="https://fonts.googleapis.com/icon?family=Material+Icons" />
    <link href="https://fonts.googleapis.com/css2?family=Roboto:wght@300;400;700&family=Raleway:wght@400;700&display=swap" rel="stylesheet" />
    <link href="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/css/materialize.min.css" rel="stylesheet" />
    <style>
        html, body {
            height: 100%;
            display: flex;
            flex-direction: column;
            background-color: #f5f5f5;
            font-family: 'Roboto', sans-serif;
        }
        .container {
            flex: 1;
            margin-top: 50px;
        }
        footer {
            position: relative;
            bottom: 0;
            width: 100%;
        }
        .btn-custom {
            background-color: #1976d2;
            transition: background-color 0.3s;
            font-weight: 700;
        }
        .btn-custom:hover {
            background-color: #1565c0;
        }
        .btn-logout {
            background-color: #f44336; /* Red color */
            transition: background-color 0.3s;
            font-weight: 700;
        }
        .btn-logout:hover {
            background-color: #d32f2f; /* Darker red on hover */
        }
        .current-text {
            font-family: 'Raleway', sans-serif;
            font-size: 2em;
            font-weight: 700;
            color: #333;
            text-shadow: 1px 1px 2px rgba(0, 0, 0, 0.2);
        }
        h4 {
            font-family: 'Raleway', sans-serif;
            font-weight: 700;
            color: #1976d2;
            text-align: center;
            text-transform: uppercase;
            letter-spacing: 1px;
        }
        .card-panel {
            padding: 20px;
            border-radius: 10px;
            margin: 10px;
            text-align: center;
            transition: transform 0.3s;
            font-size:1.2em;
        }
        .card-panel:hover {
            transform: scale(1.05);
        }
    </style>
</head>
<body>
    <div class="container">
        <div class="row">
            <div class="col s12">
                <h4>Text Display on <span>LED P10</span></h4>
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
                <div class="center-align">
                    <button type="submit" class="btn waves-effect waves-light btn-custom">
                        Submit
                        <i class="material-icons right">send</i>
                    </button>
                    <button type="button" id="logoutButton" class="btn waves-effect waves-light btn-logout" style="margin-left: 10px;">
                        Logout
                        <i class="material-icons right">logout</i>
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
                <div class="col s12 m3">
                    <div class="card-panel teal darken-1">
                        <span class="white-text">นายภูธนพัฒน์ หนูแก้ว<br>ID: 652021037</span>
                    </div>
                </div>
                <div class="col s12 m3">
                    <div class="card-panel amber darken-1">
                        <span class="white-text">นายธนวงศ์ กวดกิจการ<br>ID: 652021053</span>
                    </div>
                </div>
                <div class="col s12 m3">
                    <div class="card-panel deep-purple darken-1">
                        <span class="white-text">นายรัฐภูมิ แสงทอง<br>ID: 652021066</span>
                    </div>
                </div>
                <div class="col s12 m3">
                    <div class="card-panel lime darken-1">
                        <span class="white-text">นายสกรรจ วกกุม<br>ID: 652021073</span>
                    </div>
                </div>
            </div>
        </div>
    </footer>

    <script src="https://cdnjs.cloudflare.com/ajax/libs/materialize/1.0.0/js/materialize.min.js"></script>
    <script>
        M.updateTextFields();

        document.addEventListener('DOMContentLoaded', function() {
            // Check login state
            fetch('/checkLogin')
                .then(response => response.json())
                .then(data => {
                    if (data.loggedIn) {
                        document.getElementById('loginSection').style.display = 'none';
                        document.getElementById('textSection').style.display = 'block';
                        document.getElementById('displayedText').innerText = data.currentText; // Show current text
                    } else {
                        document.getElementById('loginSection').style.display = 'block';
                    }
                });
        });

        document.getElementById('loginForm').addEventListener('submit', function(event) {
            event.preventDefault();
            var usernameField = document.getElementById('username');
            var passwordField = document.getElementById('password');

            fetch('/login', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded',
                },
                body: new URLSearchParams(new FormData(this)).toString(),
            })
            .then(response => response.text())
            .then(data => {
                if (data.includes("successful")) {
                    window.location.reload(); // Reload page on successful login
                } else {
                    alert(data); // Show error message
                }
            })
            .catch((error) => console.error('Error:', error));
        });

        document.getElementById('textForm').addEventListener('submit', function(event) {
            event.preventDefault();
            var textField = document.getElementById('text');
            var textValue = textField.value;
            if (!textValue.startsWith('ATTX:')) {
                textField.value = 'ATTX:' + textValue;
            }

            fetch('/setText', {
                method: 'POST',
                headers: {
                    'Content-Type': 'application/x-www-form-urlencoded',
                },
                body: new URLSearchParams(new FormData(this)).toString(),
            })
            .then(response => response.text())
            .then(data => {
                textField.value = ''; // Clear the input field
                document.getElementById('displayedText').innerText = data; // Update displayed text
            })
            .catch((error) => console.error('Error:', error));
        });

        // Handle logout button
        document.getElementById('logoutButton').addEventListener('click', function() {
            fetch('/logout', {
                method: 'POST',
            })
            .then(response => response.text())
            .then(data => {
                if (data.includes("Logged out")) {
                    window.location.reload(); // Reload page on successful logout
                } else {
                    alert(data); // Show error message
                }
            })
            .catch((error) => console.error('Error:', error));
        });
    </script>
</body>
</html>
)rawliteral";

// Handle Root
void handleRoot() {
    String currentText = Text_From_EEPROM; 
    String response = MAIN_page;
    response.replace("{CURRENT_TEXT}", currentText); 
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

// Check Login Status
void checkLogin() {
    server.send(200, "application/json", "{\"loggedIn\": " + String(loggedIn ? "true" : "false") + ", \"currentText\": \"" + Text_From_EEPROM + "\"}");
}

// Handle Incoming Text Data
void handle_Incoming_Text() {
    if (!loggedIn) {
        server.send(401, "text/plain", "Unauthorized. Please log in.");
        return;
    }

    Incoming_Text = server.arg("TextContents");
    clearDisplay();

    if (Incoming_Text.substring(0, 5) == "ATTX:") { 
        Text_To_EEPROM = Incoming_Text.substring(5);
        write_String_to_EEPROM(0, Text_To_EEPROM);
        Text_From_EEPROM = read_String_from_EEPROM(0);
        Process_Incoming_Text(); 
    }

    server.send(200, "text/plain", Text_From_EEPROM);
}

// Clear the display
void clearDisplay() {
    Disp.clear();
}

// Process Incoming Text
void Process_Incoming_Text() {
    Text_From_EEPROM.toCharArray(Text, sizeof(Text));
}

// Setup Function
void setup() {
    Serial.begin(115200);
    EEPROM.begin(512);
    Disp.start();
    Disp.setBrightness(50);
    Disp.setFont(Mono5x7);

    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
    }

    timeClient.begin();
    timeClient.setTimeOffset(7 * 3600);
    ipAddress = WiFi.localIP().toString(); // Store the IP address
    Serial.print("IP Address: ");
    Serial.println(ipAddress);

    ipDisplayStartTime = millis(); // Start the timer
    server.on("/", handleRoot);
    server.on("/login", handleLogin);
    server.on("/logout", handleLogout);
    server.on("/checkLogin", checkLogin);
    server.on("/setText", handle_Incoming_Text);
    server.begin();

    Text_From_EEPROM = read_String_from_EEPROM(0);
    Process_Incoming_Text();
}
// Loop Function
void loop() {
    server.handleClient();
    Disp.loop();

    if (displayingIP) {
        // Scroll the IP address
        Scrolling_Text(0, 50); // Adjust the y-coordinate as needed

        // Check the time elapsed
        if (millis() - ipDisplayStartTime > 10000) { // 10 seconds
            clearDisplay();
            displayingIP = false; // Switch to incoming text
            ipDisplayStartTime = millis(); // Reset the timer for the next cycle
        }
    } else {
        // Display incoming text
        displayTime(); // Show the current time
        Scrolling_Text(9, 50); // Scroll the incoming text
    }
}


// Display Current Time
void displayTime() {
    timeClient.update();
    String formattedTime = timeClient.getFormattedTime();
    Disp.drawText(2, 0, formattedTime.c_str()); 
}

// Scrolling Text Function
void Scrolling_Text(int y, uint8_t scrolling_speed) {
    static uint32_t pM;
    static uint32_t x;
    String displayText;

    // Determine what text to scroll
    if (displayingIP) {
        displayText = ipAddress; // Use the IP address for scrolling
    } else {
        displayText = Text; // Use incoming text for scrolling
    }

    int width = Disp.width();
    Disp.setFont(Mono5x7);
    int fullScroll = Disp.textWidth(displayText) + width;

    if ((millis() - pM) > scrolling_speed) { 
        pM = millis();
        if (x < fullScroll) {
            ++x;
        } else {
            x = 0; // Reset scroll position
            return;
        }
        Disp.drawText(width - x, y, displayText.c_str());
    }  
}

// Write String to EEPROM
void write_String_to_EEPROM(char add, String data) {
    int _size = data.length();
    for (int i = 0; i < _size; i++) {
        EEPROM.write(add + i, data[i]);
    }
    EEPROM.write(add + _size, '\0');
    EEPROM.commit();
}

// Read String from EEPROM
String read_String_from_EEPROM(char add) {
    int len = 0;
    char data[100];
    unsigned char k;
    k = EEPROM.read(add);
    while (k != '\0' && len < 100) {    
        k = EEPROM.read(add + len);
        data[len] = k;
        len++;
    }
    data[len] = '\0';
    return String(data);
}

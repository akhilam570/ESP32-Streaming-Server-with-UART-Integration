#include <WiFi.h>
#include <ESPAsyncWebServer.h>
#include <esp_camera.h>
#include <HardwareSerial.h>

// Replace with your network credentials
const char *ssid = "your-ssid";
const char *password = "your-password";

// UART Configuration
const int uartTxPin = 17;  // TX pin for UART
const int uartRxPin = 16;  // RX pin for UART
HardwareSerial Serial2(2); // UART2

// Replace with your Blynk token
const char *blynkToken = "your-blynk-token";

// Photoresistor analog pin
const int photoresistorPin = 36;

// Initialize Blynk and UART
void initBlynk();
void initUART();

// Initialize the camera
void initCamera();

// Callback function to capture a photo and stream it
void capturePhoto(AsyncWebServerRequest *request);

void setup()
{
  // Start Serial for debugging
  Serial.begin(115200);

  // Start UART2
  Serial2.begin(9600, SERIAL_8N1, uartRxPin, uartTxPin);

  // Connect to Wi-Fi
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED)
  {
    delay(1000);
    Serial.println("Connecting to WiFi...");
  }
  Serial.println("Connected to WiFi");

  // Initialize Blynk
  initBlynk();

  // Initialize UART
  initUART();

  // Initialize the camera
  initCamera();

  // Setup MJPEG stream
  server.on("/stream", HTTP_GET, capturePhoto);

  // Start server
  server.begin();
}

void loop()
{
  // Handle Blynk
  Blynk.run();
}

void initBlynk()
{
  Blynk.begin(blynkToken, WiFi);
}

void initUART()
{
  // Initialize UART2
  Serial2.begin(9600, SERIAL_8N1, uartRxPin, uartTxPin);
}

void initCamera()
{
  camera_config_t config;
  config.ledc_channel = LEDC_CHANNEL_0;
  config.ledc_timer = LEDC_TIMER_0;
  config.pin_d0 = 5;
  config.pin_d1 = 18;
  config.pin_d2 = 19;
  config.pin_d3 = 21;
  config.pin_d4 = 36;
  config.pin_d5 = 39;
  config.pin_d6 = 34;
  config.pin_d7 = 35;
  config.pin_xclk = 0;
  config.pin_pclk = 22;
  config.pin_vsync = 25;
  config.pin_href = 23;
  config.pin_sscb_sda = 26;
  config.pin_sscb_scl = 27;
  config.pin_pwdn = 32;
  config.pin_reset = -1;
  config.xclk_freq_hz = 20000000;
  config.pixel_format = PIXFORMAT_JPEG;

  if (psramFound())
  {
    config.frame_size = FRAMESIZE_UXGA;
    config.jpeg_quality = 10;
    config.fb_count = 2;
  }
  else
  {
    config.frame_size = FRAMESIZE_SVGA;
    config.jpeg_quality = 12;
    config.fb_count = 1;
  }

  // Init Camera
  esp_err_t err = esp_camera_init(&config);
  if (err != ESP_OK)
  {
    Serial.printf("Camera init failed with error 0x%x", err);
    return;
  }
}

void capturePhoto(AsyncWebServerRequest *request)
{
  camera_fb_t *fb = NULL;

  // Take a photo with the camera
  fb = esp_camera_fb_get();
  if (!fb)
  {
    Serial.println("Camera capture failed");
    request->send(500, "text/plain", "Camera capture failed");
    return;
  }

  // Send the image to the client
  request->send_P(200, "image/jpeg", fb->buf, fb->len);

  // Return the frame buffer to the camera
  esp_camera_fb_return(fb);
}

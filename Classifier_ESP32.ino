

//#include <Arduino_LSM9DS1.h>
// replace with your actual file
#include "model.h"

#include <Adafruit_MPU6050.h>
#include <Adafruit_Sensor.h>
#include <Wire.h>

#include <ArduinoJson.h>
#include <PubSubClient.h>
#include <WiFi.h>

#define mqttUser ""
#define mqttPass ""
#define mqttPort 1883

Adafruit_MPU6050 mpu;

#define CONVERT_G_TO_MS2    1.0f
#define MAX_ACCEPTED_RANGE  25.0f  


const float accelerationThreshold = 25; // threshold of significant in G's original 2.5
const int numSamples = 225;

float input[numSamples*6];
float output[5];

int samplesRead = numSamples;

// array to map gesture index to a name
const char* GESTURES[] = {
  "fine",
  "hello",
  "sorry",
  "thankyou",
  "yes"
};

const char* ssid = "iPhone de Samantha";          //ssid de la red inalambrica
const char* password = "samantha04";              //password para conectarse a la red
char mqttBroker[] = "broker.mqtt-dashboard.com";  //ip del servidor
char mqttClientId[] = "device1";                  //cualquier nombre
char inTopic[] = "iaiot/proyectoJS";

void callback(char* topic, byte* payload, unsigned int length) {
  String json = String((char*)payload);
  Serial.println();
  StaticJsonDocument<300> doc;
  DeserializationError error = deserializeJson(doc, json);
  if (error) { return; }
  
}
WiFiClient BClient;
PubSubClient client(BClient);

void reconnect() {
  // Loop until we're reconnected
  while (!client.connected()) {
    Serial.print("Attempting MQTT connection...");
    // Attempt to connect
    if (client.connect(mqttClientId, mqttUser, mqttPass)) {
      Serial.println("connected");
      client.subscribe("iaiot/proyectoJS");
    }else {
      Serial.println("failed, rc=");
      Serial.print(client.state());
    }
  }
}
void setup_wifi() {
  delay(10);
  // We start by connecting to a WiFi network
  Serial.println();
  Serial.print("Connecting to ");
  Serial.println(ssid);
  WiFi.begin(ssid, password);
  while (WiFi.status() != WL_CONNECTED) {
    delay(500);
    Serial.print(".");
  }
  Serial.println("");
  Serial.println("WiFi connected");
  Serial.println("IP address: ");
  Serial.println(WiFi.localIP());
}

void setup() {
  Serial.begin(115200);  //Serial connection
  setup_wifi();          //WiFi connection
  client.setServer(mqttBroker, mqttPort);
  client.setCallback(callback);
  Serial.println("Setup done");
  delay(1500);

      while (!MovimientoNN.begin()) {
        Serial.print("Error in NN initialization: ");
        Serial.println(MovimientoNN.getErrorMessage());
      } 
  Serial.begin(115200);
  while (!Serial);
/*
  // print the header
  Serial.println("aX,aY,aZ,gX,gY,gZ");
  */
      while (!Serial);
    delay(10); // will pause Zero, Leonardo, etc until serial console opens

  Serial.println("Adafruit MPU6050 test!");

  // Try to initialize!
  if (!mpu.begin()) {
    Serial.println("Failed to find MPU6050 chip");
    while (1) {
      delay(10);
    }
  }
  Serial.println("MPU6050 Found!");

  mpu.setAccelerometerRange(MPU6050_RANGE_8_G);
  Serial.print("Accelerometer range set to: ");
  switch (mpu.getAccelerometerRange()) {
  case MPU6050_RANGE_2_G:
    Serial.println("+-2G");
    break;
  case MPU6050_RANGE_4_G:
    Serial.println("+-4G");
    break;
  case MPU6050_RANGE_8_G:
    Serial.println("+-8G");
    break;
  case MPU6050_RANGE_16_G:
    Serial.println("+-16G");
    break;
  }
  mpu.setGyroRange(MPU6050_RANGE_500_DEG);
  Serial.print("Gyro range set to: ");
  switch (mpu.getGyroRange()) {
  case MPU6050_RANGE_250_DEG:
    Serial.println("+- 250 deg/s");
    break;
  case MPU6050_RANGE_500_DEG:
    Serial.println("+- 500 deg/s");
    break;
  case MPU6050_RANGE_1000_DEG:
    Serial.println("+- 1000 deg/s");
    break;
  case MPU6050_RANGE_2000_DEG:
    Serial.println("+- 2000 deg/s");
    break;
  }

  mpu.setFilterBandwidth(MPU6050_BAND_21_HZ);
  Serial.print("Filter bandwidth set to: ");
  switch (mpu.getFilterBandwidth()) {
  case MPU6050_BAND_260_HZ:
    Serial.println("260 Hz");
    break;
  case MPU6050_BAND_184_HZ:
    Serial.println("184 Hz");
    break;
  case MPU6050_BAND_94_HZ:
    Serial.println("94 Hz");
    break;
  case MPU6050_BAND_44_HZ:
    Serial.println("44 Hz");
    break;
  case MPU6050_BAND_21_HZ:
    Serial.println("21 Hz");
    break;
  case MPU6050_BAND_10_HZ:
    Serial.println("10 Hz");
    break;
  case MPU6050_BAND_5_HZ:
    Serial.println("5 Hz");
    break;
  }

  Serial.println("");
  delay(100);
  
}


void loop() {
  
  float aX, aY, aZ, gX, gY, gZ;

  // wait for significant motion
  while (samplesRead == numSamples) {
        sensors_event_t a, g, temp;
        mpu.getEvent(&a, &g, &temp);

  aX=a.acceleration.x;
  aY=a.acceleration.y;
  aZ=a.acceleration.z; 
  gX=g.gyro.x;
  gY=g.gyro.y;
  gZ=g.gyro.z;
 // delay(50);

        // sum up the absolutes
      float aSum = fabs(aX) + fabs(aY) + fabs(aZ);

      // check if it's above the threshold
      if (aSum >= accelerationThreshold) {
        // reset the sample read count
        samplesRead = 0;
        break;
      } 
  
  }if (!client.connected()) {
      reconnect();
    }
    client.loop();
  
  while (samplesRead < numSamples) {
    // check if both new acceleration and gyroscope data is
    // available
   // if (IMU.accelerationAvailable() && IMU.gyroscopeAvailable()) {
      // read the acceleration and gyroscope data

   
      
     sensors_event_t a, g, temp;
     mpu.getEvent(&a, &g, &temp);
    aX=a.acceleration.x;
    aY=a.acceleration.y;
    aZ=a.acceleration.z; 
    gX=g.gyro.x;
    gY=g.gyro.y;
    gZ=g.gyro.z;
     
   //  delay(50);

      input[samplesRead * 6 + 0] = (aX + 30.0) / 60.0;
      input[samplesRead * 6 + 1] = (aY + 30.0) / 60.0;
      input[samplesRead * 6 + 2] = (aZ + 30.0) / 60.0;
      input[samplesRead * 6 + 3] = (gX + 8) / 16.0;
      input[samplesRead * 6 + 4] = (gY + 8) / 16.0;
      input[samplesRead * 6 + 5] = (gZ + 8) / 16.0;
     samplesRead++;

           if (samplesRead == numSamples) {
        
       MovimientoNN.predictClass(input);
       

     Serial.print(GESTURES[0]);
    Serial.print(": ");
    Serial.println(MovimientoNN.getScoreAt(0));
    Serial.print(GESTURES[1]);
    Serial.print(": ");
    Serial.println(MovimientoNN.getScoreAt(1));
    Serial.print(GESTURES[2]);
    Serial.print(": ");
    Serial.println(MovimientoNN.getScoreAt(2));
    Serial.print(GESTURES[3]);
    Serial.print(": ");
    Serial.println(MovimientoNN.getScoreAt(3));
    Serial.print(GESTURES[4]);
    Serial.print(": ");
    Serial.println(MovimientoNN.getScoreAt(4));
    Serial.println();
String gesto ="";
    
    if(MovimientoNN.getScoreAt(0) > MovimientoNN.getScoreAt(1) && MovimientoNN.getScoreAt(0) > MovimientoNN.getScoreAt(2) && MovimientoNN.getScoreAt(0) >
MovimientoNN.getScoreAt(3) && MovimientoNN.getScoreAt(0) > MovimientoNN.getScoreAt(4)){
  
 gesto =  GESTURES[0];
     
}else if(MovimientoNN.getScoreAt(1) > MovimientoNN.getScoreAt(0) && MovimientoNN.getScoreAt(1) > MovimientoNN.getScoreAt(2) && MovimientoNN.getScoreAt(1) >
MovimientoNN.getScoreAt(3) && MovimientoNN.getScoreAt(1) > MovimientoNN.getScoreAt(4)){
   gesto =  GESTURES[1];
  
}else if(MovimientoNN.getScoreAt(2) > MovimientoNN.getScoreAt(1) && MovimientoNN.getScoreAt(2) > MovimientoNN.getScoreAt(0) && MovimientoNN.getScoreAt(2) >
MovimientoNN.getScoreAt(3) && MovimientoNN.getScoreAt(2) > MovimientoNN.getScoreAt(4)){
   gesto =  GESTURES[2];
  
}else if(MovimientoNN.getScoreAt(3) > MovimientoNN.getScoreAt(1) && MovimientoNN.getScoreAt(3) > MovimientoNN.getScoreAt(2) && MovimientoNN.getScoreAt(3) >
MovimientoNN.getScoreAt(0) && MovimientoNN.getScoreAt(3) > MovimientoNN.getScoreAt(4)){
   gesto =  GESTURES[3];
  
} else if (MovimientoNN.getScoreAt(4) > MovimientoNN.getScoreAt(1) && MovimientoNN.getScoreAt(4) > MovimientoNN.getScoreAt(2) && MovimientoNN.getScoreAt(4) >
MovimientoNN.getScoreAt(3) && MovimientoNN.getScoreAt(4) > MovimientoNN.getScoreAt(0)){
   gesto =  GESTURES[4];
}

        String json;
        if (!client.connected()) {
      reconnect();
    }
    client.loop();
  StaticJsonDocument<300> doc;
  // doc["fecha"] = F;
  // doc["hora"] = H;
  doc["accx"] = a.acceleration.x;
  doc["accy"] = a.acceleration.y;
  doc["accz"] = a.acceleration.z;
  doc["rotx"] = g.gyro.x;
  doc["roty"] = g.gyro.y;
  doc["rotz"] = g.gyro.z;  
  doc["gesture"] = gesto;
  doc["idnodo"] = 2;

  serializeJson(doc, json);
  Serial.println(json);
  int lon = json.length() + 1;
  char datojson[lon];
  json.toCharArray(datojson, lon);
  
  client.publish(inTopic, datojson);
  delay(5000);
        }

  }
}

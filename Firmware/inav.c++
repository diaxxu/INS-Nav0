#include <Wire.h>
#include <SPI.h>


#define OPM_CS_PIN    5   
#define I2C_SDA_PIN   21  
#define I2C_SCL_PIN   22  


float current_x = 0.0;
float current_y = 0.0;
float heading_rad = 0.0;


const float MAG_X_OFFSET = 0.0;
const float MAG_Y_OFFSET = 0.0;
const float COUNTS_PER_MM = 24.2; 


void initMagnetometer();
void initOpticalFlow();
float readCompassHeading();
void readOpticalFlow(int16_t &deltaX, int16_t &deltaY);

void setup() {
    Serial.begin(115200);
    Wire.begin(I2C_SDA_PIN, I2C_SCL_PIN, 400000); 
    
    Serial.println("--- INS NAV0 NAV DECK INITIALIZATION ---");
    
    initMagnetometer();
    initOpticalFlow();
    
    Serial.println("System fully initialized. Beginning tracking loop...");
}

void loop() {
    int16_t raw_dx = 0;
    int16_t raw_dy = 0;
    
  
    heading_rad = readCompassHeading();
    
   
    readOpticalFlow(raw_dx, raw_dy);
    
   
    float delta_x_mm = (float)raw_dx / COUNTS_PER_MM;
    float delta_y_mm = (float)raw_dy / COUNTS_PER_MM;
    
  
    if (raw_dx != 0 || raw_dy != 0) {
        float world_dx = (delta_x_mm * cos(heading_rad)) - (delta_y_mm * sin(heading_rad));
        float world_dy = (delta_x_mm * sin(heading_rad)) + (delta_y_mm * cos(heading_rad));
        
       
        current_x += world_dx;
        current_y += world_dy;
        
        
        Serial.printf("POS_X: %.2f mm | POS_Y: %.2f mm | HEADING: %.1f deg\n", 
                      current_x, current_y, heading_rad * (180.0 / PI));
    }
    
    delay(10); 
}



void initMagnetometer() {
    
    Wire.beginTransmission(0x0D); 
    Wire.write(0x09);           
    Wire.write(0x1D);              
    if(Wire.endTransmission() == 0) {
        Serial.println("[OK] Magnetometer online.");
    } else {
        Serial.println("[ERROR] Magnetometer handshake failed.");
    }
}

void initOpticalFlow() {
    pinMode(OPM_CS_PIN, OUTPUT);
    digitalWrite(OPM_CS_PIN, HIGH);
    SPI.begin();
    
    
    digitalWrite(OPM_CS_PIN, LOW);
    SPI.transfer(0x3B); 
    SPI.transfer(0x00);
    digitalWrite(OPM_CS_PIN, HIGH);
    delay(20);
    Serial.println("[OK] Optical Flow Sensor configured.");
}

float readCompassHeading() {
    int16_t raw_x = 0, raw_y = 0;
    
    Wire.beginTransmission(0x0D);
    Wire.write(0x00); // Point 
    Wire.endTransmission();
    
    Wire.requestFrom(0x0D, 4);
    if(Wire.available() >= 4) {
        raw_x = (Wire.read() | (Wire.read() << 8));
        raw_y = (Wire.read() | (Wire.read() << 8));
    }
    
   
    float cal_x = (float)raw_x - MAG_X_OFFSET;
    float cal_y = (float)raw_y - MAG_Y_OFFSET;
    
    
    float angle = atan2(cal_y, cal_x);
    if(angle < 0) angle += 2 * PI;
    return angle;
}

void readOpticalFlow(int16_t &deltaX, int16_t &deltaY) {
    digitalWrite(OPM_CS_PIN, LOW);
   
    SPI.transfer(0x02 | 0x80); 
    deltaX = SPI.transfer(0x00);
    deltaY = SPI.transfer(0x00);
    digitalWrite(OPM_CS_PIN, HIGH);
}
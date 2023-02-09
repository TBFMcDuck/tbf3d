// The GY91 reads the data from the GY91 module
#include <GY91.h>
#include <Cansat_RFM96.h>
#define USE_SD 0

float NTC;
int NTC_pin = 10;
float NTC_V;
float temp;

int BUZZER_PIN = 29;

unsigned int counter=0;
unsigned long _time=0;
double ax, ay, az, gx, gy, gz, mx, my, mz, pressure;
GY91 gy91; // We need to make an instance of the GY91 library object
Cansat_RFM96 rfm96(433750, USE_SD);

void setup() {
  Serial.begin(9600);
  while(!Serial);

  analogWriteResolution(16);
  
  digitalWriteFast(BUZZER_PIN, LOW);
  pinMode(BUZZER_PIN, OUTPUT);

  if (!gy91.init()) {
    Serial.println("Could not initiate");
    while(1);
  }
  if (!rfm96.init()) {
    Serial.println("Init of radio failed, stopping");
    while(1);
  }
  rfm96.setTxPower(5);
}

float get_temp() {
  NTC = analogRead(NTC_pin);
  NTC_V = (5.0/1023)*NTC;
  temp = -26.1561 * NTC_V + 115.2828;
  return temp;
}

void print_data(){
    Serial.print(analogRead(A11)*3.3*2/1023); // Multiply with 2, since we have a 1/2 resistor divider
    Serial.print("\t");

    // Temp
    Serial.print("Temp: ");
    Serial.print(get_temp());
    Serial.print(" C");
    Serial.print(" ");

    Serial.print("Acceleration: ");
    Serial.print("x: ");
    Serial.print(ax);
    Serial.print(" ");
    Serial.print("y: ");
    Serial.print(ay);
    Serial.print(" ");
    Serial.print("z: ");
    Serial.print(az);
    Serial.print(" ");

    Serial.print("Gyrometer: ");
    Serial.print("x: ");
    Serial.print(gx);
    Serial.print(" ");
    Serial.print("y: ");
    Serial.print(gy);
    Serial.print(" ");
    Serial.print("z: ");
    Serial.print(gz);
    Serial.print(" ");
    
    Serial.print("Magneticmeter: ");
    Serial.print("x: ");
    Serial.print(mx);
    Serial.print(" ");
    Serial.print("y: ");
    Serial.print(my);
    Serial.print(" ");
    Serial.print("z: ");
    Serial.print(mz);
    Serial.print(" ");

    Serial.print("Pressure: ");
    Serial.print(pressure/1000,4); // it is in Pascals, but we want it in centi bar to make
                                  // it easier to plot, which is one tenth of hPa/mbar
    
    Serial.println();
}

void send_data(){
  // Add the data to the buffer. These functions do not initiate a transfer
    rfm96.printToBuffer("TBF; ");
    rfm96.printToBuffer(millis());
    rfm96.printToBuffer("; ");
    rfm96.printToBuffer(counter++);
    rfm96.printToBuffer("; ");
    rfm96.printToBuffer(pressure);
    rfm96.printToBuffer("; ");
    rfm96.printToBuffer(temp);
    rfm96.printToBuffer("; ");
    rfm96.printToBuffer(ax);
    rfm96.printToBuffer("; ");
    rfm96.printToBuffer(ay);
    rfm96.printToBuffer("; ");
    rfm96.printToBuffer(az);
    rfm96.printToBuffer("; ");
    rfm96.printToBuffer(gx);
    rfm96.printToBuffer("; ");
    rfm96.printToBuffer(gy);
    rfm96.printToBuffer("; ");
    rfm96.printToBuffer(gz);
    rfm96.printToBuffer("; ");
    rfm96.printToBuffer(mx);
    rfm96.printToBuffer("; ");
    rfm96.printToBuffer(my);
    rfm96.printToBuffer("; ");
    rfm96.printToBuffer(mz);
    rfm96.printlnToBuffer();
    // When the buffer is filled up of what we want, then transfer it to send.
    // There is no need to check if Tx is ready, since this function will
    // check if Tx is ready, and if not it will only write to file (if SD
    // is enabled). If neither is ready/enabled, it will do nothing.
    rfm96.sendAndWriteToFile();
 }

void loop() {
  if (millis()-_time > 100) { // Makes sure that we do not send data too often
    _time = millis();

    gy91.read_acc();
    gy91.read_gyro();
    gy91.read_mag();

    pressure = gy91.readPressure();

    ax = gy91.ax;
    ay = gy91.ay;
    az = gy91.az;

    gx = gy91.gx;
    gy = gy91.gy;
    gz = gy91.gz;

    mx = gy91.mx;
    my = gy91.my;
    mz = gy91.mz;

    print_data();
    send_data();
    delay(500);
  }
}

//Created By: Nicholas McCullough ; nmc
//190215

// Feel free to use for anything and everything. If you see errors or a better 
// way to do something please let me know.

// For the MPX4250 manifold absolute pressure sensor. 
// This sensor / code has been tested against a mechanical vacuum gauge, and proved
// to be accurate.

// here we just define which analog pin the Vout of the sensor is connected to
#define mpx 0
float vout; //output voltage of the mpx sensor
int vcc = 5; //change this if your supply voltage is not 5V.
// and now some misc. variables
float absolute;
float gauge;
int inhg;
int psi;


void setup() {
Serial.begin(9600);
}

void loop() {
// Read the sensor and convert the adc reading output voltage of the MPX
vout = ((analogRead(mpx) * 5.0) / 1023.0);
// Convert the output voltage of the MPX to absolute pressure
absolute = (vout / (vcc * 0.004)) + 10 ; // Formula from Fig. 6 of the datasheet
//The we convert from absolute pressure to gauge pressure; 101.325 kPa = 1 atm
gauge = absolute - 101.325;

// Now that this is for the automotive environment, so SOP is for vacuum to be 
//in inHg and positive pressure to be in PSI. So lets do that

if (gauge <= 0) {
  inhg = gauge / 3.386375; // 1 inHg = ~ 3.4 kPa
  Serial.print(inhg);
  Serial.println(" inHg");
}
else if (gauge > 0){
  psi = gauge / 6.89476; // 1 PSI = ~6.9 kPa
  Serial.print(psi);
  Serial.println(" PSI");
}
delay(150);
}

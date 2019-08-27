/*
  Modbus RTU Server for Arduino UNO

  This sketch creates a Modbus RTU Server with read digital and analog inputs
  
  Code is not optimized for readability
*/

#include <ArduinoRS485.h> // ArduinoModbus depends on the ArduinoRS485 library
#include <ArduinoModbus.h>

const int ledPin = LED_BUILTIN;

const int nAnalogInputs = 6;   // A0 .. A5
const int nDigitalInputs = 14; // D0 .. D13

void setup() {
  
  Serial.begin(9600);

  // start the Modbus RTU server, with (slave) id 1
  if (!ModbusRTUServer.begin(1, 9600)) {
    Serial.println("Failed to start Modbus RTU Server!");
    while (1);
  }

  ModbusRTUServer.configureInputRegisters(0x00,nAnalogInputs);

  pinMode(2, INPUT);
  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(5, INPUT);
  pinMode(6, INPUT);
  pinMode(7, INPUT);
  pinMode(8, INPUT);
  pinMode(9, INPUT);
  pinMode(10, INPUT);
  pinMode(11, INPUT);
  pinMode(12, INPUT);
  
  ModbusRTUServer.configureDiscreteInputs(0x00,nDigitalInputs);
}

void loop() {
  // Store analog inputs   
  for (int i=0; i < nAnalogInputs; i++)          
    ModbusRTUServer.inputRegisterWrite(i,analogRead(i));
  
  // Read digital inputs (but 0 and 1)
  for (int i = 0; i < nDigitalInputs; i++)
    ModbusRTUServer.discreteInputWrite(i,digitalRead(i));
   
  // poll for Modbus RTU requests
  ModbusRTUServer.poll();
}

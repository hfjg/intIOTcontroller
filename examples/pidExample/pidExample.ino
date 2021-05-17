#include "intIOTcontroller.h"


intIOTcontroller con;

void setup() {

  Serial.begin(115200);

  // PID controller with hysteresis, e.g. an oven
  con.setup(intIOTcontroller::CON_PID, 0, 200,150,0);
  // set desired oven temperature to 200°C
  con.setSetpoint(2000);

  // set starting temperature to 22°C
  con.setProcessValue(220);
}


void loop(){
char buffer[80];
  // run controller
  con.run();

  // Show data
  sprintf(buffer, "\nSetpoint: %4d,\tProcess Value: %4d, Controller Output: %4d", 
    con.getSetpoint(), con.getProcessValue(), con.getOutput());
  Serial.print(buffer);

  // Simulate process, first term simulates heatup, second term simulates
  // heat loss to ambient
  con.setProcessValue(con.getProcessValue()+ con.getOutput()/5 -(con.getProcessValue()- 230)/90);

  delay(500);
}

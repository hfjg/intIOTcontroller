#include "intIOTcontroller.h"


intIOTcontroller con;

void setup() {
int hysteresis = 20;

  Serial.begin(115200);

  // simple switching controller with hysteresis, e.g. an oven
  con.setup(intIOTcontroller::CON_SWITCHING, 0, hysteresis);
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
  sprintf(buffer, "\nSetpoint: %d,\tProcess Value: %d, Controller Output: %d", 
    con.getSetpoint(), con.getProcessValue(), con.getOutput());
  Serial.print(buffer);

  // Simulate process
  if (con.getOutput()!= 0)
    con.setProcessValue(con.getProcessValue() + 25);
  else
    con.setProcessValue(con.getProcessValue() -10);

  delay(500);
}

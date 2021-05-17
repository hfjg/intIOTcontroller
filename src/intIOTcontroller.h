#ifndef __INTEGER_IOT_CONTROLLER_H__
#define __INTEGER_IOT_CONTROLLER_H__

class intIOTcontroller {
  public:
    enum eControllerType {CON_SWITCHING, CON_PID};
    
    // constructor
    intIOTcontroller();
    
    void setup(eControllerType t, uint8_t inverted, int16_t hysteresis);
    void setup(eControllerType t, uint8_t inverted, int16_t kp, int16_t ki, int16_t kd );

    void setLockup(int32_t lockup);

    void setOutputMin(uint16_t omin){_outMin = omin;}
    void setOutputMax(uint16_t omax){_outMax = omax;}

    void setSetpoint(int16_t setpoint);
    int16_t getSetpoint(void);
    void setProcessValue(int16_t procVal);
    int16_t getOutput(void);
    
    void run(void);
    
  private:
    eControllerType _type;

    int16_t _setpoint;
    int16_t _processValue;
    int16_t _output;
    
    uint8_t _inverted;
    int16_t _outMin, _outMax;
    int16_t _hyst, _kp, _ki, _kd;
    int32_t _dev, _devOld, _esum, _lockup;
};

#endif

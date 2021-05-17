#include <Arduino.h>
#include "intIOTcontroller.h"

// constructor
intIOTcontroller::intIOTcontroller(){
      _type = CON_SWITCHING;
      _inverted = 0;
      _hyst = 0;
      _lockup = 200;
      _outMin = 0;
      _outMax = 255;
      _esum = 0;
      _devOld = 0;
    };
    
void intIOTcontroller::setup(eControllerType t, uint8_t inverted, int16_t hysteresis){
      _type = t;
      _inverted = inverted;
      _hyst = hysteresis;
    }
    
void intIOTcontroller::setup(eControllerType t, uint8_t inverted, int16_t kp, int16_t ki, int16_t kd ){
      _type = t;
      _inverted = inverted;
      _lockup = 100;
      _kp = kp; _ki = ki; _kd = kd; 
    }

void intIOTcontroller::setLockup(int32_t lockup){
      _lockup = lockup;
    }

void intIOTcontroller::run(void){
      switch(_type){
        case CON_SWITCHING:
            if (_processValue > _setpoint+_hyst){
              _output = (_inverted) ? 1 : 0;
            }
            else if (_processValue < _setpoint-_hyst){
              _output = (_inverted) ? 0 : 1;
            }
          break;
          
        case CON_PID:
            _dev =  _setpoint - _processValue;
            if (_inverted != 0) _dev = -_dev;
            
            _esum += _dev;
            
            // lock windup
            if (_esum >= _lockup)_esum=_lockup;
            else if(_esum < -_lockup) _esum=-_lockup;

            _output = 
                (_dev * _kp + _esum * _ki + (_dev-_devOld)*_kd)/100;
                
            _devOld = _dev;
          break;
          
        default:
          break;
      }
    }


void intIOTcontroller::setSetpoint(int16_t setpoint){
  _setpoint = setpoint;
}

int16_t intIOTcontroller::getSetpoint(void){
  return _setpoint;
}

void intIOTcontroller::setProcessValue(int16_t procVal){
  _processValue = procVal;
}

int16_t intIOTcontroller::getOutput(void){
  return _output;
}

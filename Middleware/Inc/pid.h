#ifndef PID_H
#define PID_H


#include "encoder.h"
#include "motor.h"



typedef struct {
    float kp,ki,kd;

    float pid_p,pid_i,pid_d;

    float target;
    float actual0,actual1;
    float error0,error1;


    float out;
    float outMax;
    float outMin;
}pid_t;

void pid_update(pid_t *p);

#endif

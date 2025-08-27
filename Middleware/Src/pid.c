#include "pid.h"


float kp = 1.0 , ki = 0.1, kd = 0.01; // PID??

int target = 0;
int error = 0;
int actual = 0;
int out = 0;

void pid_set()
{
    int last_actual = actual; // ????????
    int pid_p,pid_i = 0,pid_d;


    actual = Encoder1_Position();
    error = target - actual; // ????


    pid_p = error;  // ?????

    pid_i += error;
    if(pid_i > 100 || pid_i < -100) { // ?????
        pid_i = (pid_i > 0) ? 100 : -100;
    }

    pid_d = actual - last_actual; // ?????
    
    out = kp * pid_d + ki * pid_i + kd * pid_d; // PID??
}

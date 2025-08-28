#include "pid.h"




void pid_update(pid_t *p)
{
    p->actual0 = p->actual1;
    p->actual1 = Encoder1_Position();
    p->error0 = p->error1;
    p->error1 = p->target - p->actual1;

    if(fabs(p->error1) < 5)
    {
        p->out = 0;
    }
    else
    {
        
        p->pid_p = p->error1;  //p项

        p->pid_i += p->error1;
        if(fabs(p->pid_i) > 100) {
            p->pid_i = (p->pid_i > 0) ? 100 : -100;
        }                                   //i项积分限幅

        p->pid_d = p->actual1 - p->actual0; //d项
        
        p->out = p->kp * p->pid_p + 
                 p->ki * p->pid_i + 
                 p->kd * p->pid_d;       //用来设定最终值
        
        if(p->out > p->outMax) p->out = p->outMax;
        if(p->out < p->outMin) p->out = p->outMin;//用来规定大小
    }
}

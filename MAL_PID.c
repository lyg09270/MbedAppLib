/*
 * Copyright 2024 Civic_Crab
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *     http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

/*
 * File: MAL_PID.c
 * Author: Civic_Crab
 * Version: 0.0.1
 * Created on: 2025-3-22
 *
 * Description:
 * This file contains the PID controller implementtaion.
 */

 #include "MAL_PID.h"

//void MAL_PID_Update(MAL_PID *pid, float current, float target, float *output):
//Description:
//        This function updates the PID controller with the current input and target output, and returns the output.
//args:
//        MAL_PID *pid   : Pointer to the PID controller structure.
//        float current: Current input value.
//        float target : Target output value.
//        float *output: Pointer to the output value.
//Returns:
//        None
void MAL_PID_Update(MAL_PID *pid, float current, float target, float *output) 
{
    // Calculate error
    float error = target - current;

    // Calculate proportional term
    float p_term = pid->kp * error;

    // Calculate integral term
    pid->integral += error * pid->sample_time;
    if (pid->integral > pid->integral_upper) {
        pid->integral = pid->integral_upper;
    } else if (pid->integral < pid->integral_lower) {
        pid->integral = pid->integral_lower;
    }
    float i_term = pid->ki * pid->integral;

    // Calculate derivative term
    float derivative = (error - pid->prev_error) / pid->sample_time;
    float d_term = pid->kd * derivative;
    pid->prev_error = error;

    // Calculate total output
    float total = p_term + i_term + d_term;
    if (total > pid->output_upper) {
        total = pid->output_upper;
    } else if (total < pid->output_lower) {
        total = pid->output_lower;
    }

    *output = total;
}

//void MAL_PID_Reset(MAL_PID *pid) :
//Description:
//        Resets the PID controller to its initial state.
//args:
//        MAL_PID *pid: Pointer to the PID controller structure.
//Returns:
//        None
void MAL_PID_Reset(MAL_PID *pid) 
{
    pid->integral = 0.0f;
    pid->prev_error = 0.0f;
}
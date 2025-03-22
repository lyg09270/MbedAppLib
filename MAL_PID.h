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
 * File: MAL_PID.h
 * Author: Civic_Crab
 * Version: 0.0.1
 * Created on: 2025-3-22
 *
 * Description:
 * This file contains the PID controller abstraction and interface.
 */


/* You can create a PID controller as follows:

//Define the PID controller parameters
#define MY_PID_CONTROLLER_SAMPLE_TIME 0.01

//Variables for PID controller input and output
float input_value = 0.0;
float target_value = 0.0;
float output_value = 0.0;

//Create the PID controller
MAL_PID MyPIDController = {
    .dim = 1,
    .kp = 1.0,
    .ki = 1.0,
    .kd = 1.0,
    .integral = 0,
    .prev_error = 0,
    .sample_time = MY_PID_CONTROLLER_SAMPLE_TIME,
    .integral_limit = 100,
    .output_limit = 100,
}; 

//To use the PID controller, you can call the following function:
MAL_PID_Update(&MyPIDController, &input_value, &target_value, &output_value);

//To clear the intergral and previous error, you can call the following function:
MAL_PID_Reset(&MyPIDController);

*/


#ifndef MAL_PID_H
#define MAL_PID_H

#ifdef __cplusplus
extern "C" {}
#endif


// PID controller structure
typedef struct {
    float kp;               // Rational coefficient array
    float ki;               // Integral coefficient array
    float kd;               // Differential coefficient array
    float integral;         // Integral accumulation array
    float prev_error;       // Previous error array
    float sample_time;      // Sampling time (seconds)
    float integral_upper;   // Integral upper limit
    float integral_lower;   // Integral lower limit
    float output_upper;     // Output upper limit
    float output_lower;     // Output lower limit
} MAL_PID;

//Public functions
void MAL_PID_Update(MAL_PID *pid, float current, float target, float *output);
void MAL_PID_Reset(MAL_PID *pid);

#endif /* MAL_PID_H */
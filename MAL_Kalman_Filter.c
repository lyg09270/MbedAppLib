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
 * File: MAL_Kalman_Filter.h
 * Author: Civic_Crab
 * Version: 0.0.1
 * Created on: 2025-3-22
 *
 * Description:
 * This file contains the kalman filter implementation.
 */

#include "MAL_Kalman_Filter.h"

//void MAL_Kalman1D_Init(MAL_Kalman1D *filter, float q, float r, float initial_value):
//Description:
//        This function initializes a 1D Kalman filter with the given parameters.
//args:
//        MAL_Kalman1D *filter   : Pointer to the PID controller structure.
//        float q : Process noise covariance (model uncertainty).
//        float r : Observation noise covariance (measurement uncertainty)
//        float initial_value: Pointer to the output value.
//Returns:
//        None
void MAL_Kalman1D_Init(MAL_Kalman1D *filter, float q, float r, float initial_value) 
{
    filter->q = q;
    filter->r = r;
    filter->x = initial_value;
    filter->p = q;
    filter->k = 0;
}

//void MAL_Kalman1D_Update(MAL_Kalman1D *filter, float measurement,float *prediction):
//Description:
//        This function updates the 1D Kalman filter with the current measurement and returns the prediction.
//args:
//        MAL_Kalman1D *filter   : Pointer to the PID controller structure.
//        float measurement: Current measurement value.
//        float *prediction: Pointer to the output value.
//Returns:
//        None
void MAL_Kalman1D_Update(MAL_Kalman1D *filter, float measurement,float *prediction) 
{
    // Prediction
    filter->p += filter->q;  // P = P + Q
    
    // Update
    filter->k = filter->p / (filter->p + filter->r);  // K = P / (P + R)
    filter->x += filter->k * (measurement - filter->x);
    filter->p *= (1 - filter->k);
    
    *prediction = filter->x;
}
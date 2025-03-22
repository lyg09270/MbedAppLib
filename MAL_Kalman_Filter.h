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
 * This file contains the kalman filter abstraction and interface.
 */

 /* For 1D Kalman Filter:

 To initalize the filter:
    1. Create a variable of type MAL_Kalman1D.
    2. Call the MAL_Kalman1D_Init function with the desired parameters.
        MAL_Kalman1D My_Kalman1D;
        MAL_Kalman1D_Init(&My_Kalman1D, q, r, initial_value);

        filter: Pointer to the filter variable.

        q: Process noise covariance (model uncertainty)
            Suggested value: 0.1 - 1.0
            Description:
                A higher value for q will result in a smoother prediction,
                but it will also be more susceptible to noise in the measurement.
                A lower value for q will result in a more responsive prediction,

        r: Observation noise covariance (measurement uncertainty)
            Suggested value: 0.5 - 5.0
            Description:
                A higher value for r will result in a more responsive prediction,
                but it will also be more susceptible to noise in the measurement.
                A lower value for r will result in a smoother prediction,

        initial_value: First measurement


 To update the filter:
    1. Call the MAL_Kalman1D_Update function with the desired parameters.

        MAL_Kalman1D_Update(&My_Kalman1D, measurement, &prediction);

        filter: Pointer to the filter variable.

        measurement: The current measurement.

        prediction: Pointer to the prediction variable.

    2. The prediction variable will be updated with the new prediction.
 */

#ifndef MAL_KALMAN_FILTER_H
#define MAL_KALMAN_FILTER_H

#ifdef __cplusplus
extern "C" {}
#endif

// 1D Kalman filter structure
typedef struct {
    // Public parameters
    float q;        // Process noise covariance (model uncertainty)
    float r;        // Observation noise covariance (measurement uncertainty)
    float x;        // Prediction

    // Private variables
    float p;        // Estimate error covariance
    float k;        // Kalman gain
} MAL_Kalman1D;

// Generic Kalman filter structure



// Initalize the 1D Kalman filter
void MAL_Kalman1D_Init(MAL_Kalman1D *filter, float q, float r, float initial_value);

// Update the 1D Kalman filter with a new measurement
void MAL_Kalman1D_Update(MAL_Kalman1D *filter, float measurement,float *prediction);



#endif /* MAL_KALMAN_FILTER_H */
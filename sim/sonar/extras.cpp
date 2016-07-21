/*
   extras.cpp : Implementation of extra simulator functionality

   Copyright (C) Simon D. Levy, Matt Lubas, and Julio Hidalgo Lopez 2016

   This file is part of Hackflight.

   Hackflight is free software: you can redistribute it and/or modify
   it under the terms of the GNU General Public License as published by
   the Free Software Foundation, either version 3 of the License, or
   (at your option) any later version.
   Hackflight is distributed in the hope that it will be useful,
   but WITHOUT ANY WARRANTY; without even the implied warranty of
   MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
   GNU General Public License for more details.
   You should have received a copy of the GNU General Public License
   along with Hackflight.  If not, see <http://www.gnu.org/licenses/>.
*/

#include "extras.hpp"

#include "v_repExtHackflight.h"
#include "scriptFunctionData.h"
#include "v_repLib.h"

#include <stdio.h>
#include <algorithm>


static const char * sonarNames[5] = {"Sonar_Back", "Sonar_Bottom", "Sonar_Front", "Sonar_Left", "Sonar_Right"};

static int sonarHandles[5];

void extrasStart(void)
{
    for (int k=0; k<5; ++k)
        sonarHandles[k] = simGetObjectHandle(sonarNames[k]);
}

void extrasUpdate(void)
{
    int sonarDistances[5];

    for (int k=0; k<5; ++k) {

        int sonarDistance = 0; 

        float detectedPoint[4];         // X,Y,Z,distance

        if (simReadProximitySensor(sonarHandles[k], detectedPoint, NULL, NULL) > 0)
            sonarDistance = (int)(detectedPoint[3] * 100);   // m to cm

        // Keep in MB142 range
        sonarDistances[k] = std::min(std::max(sonarDistance, 20), 765);

        printf("%s: %d | ", sonarNames[k], sonarDistances[k]);
    }

    printf("\n");
}

void extrasStop(void)
{
}
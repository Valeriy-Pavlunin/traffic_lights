#ifndef TRAFFIC_FSM_H
#define TRAFFIC_FSM_H

#include "stdint.h"

typedef enum {
	RedLight, YellowLight, GreenLight, PedestrianPhase,
} LightState;
typedef enum {
	down, up,
} TrafficDirection;

void TrafficLight();

#endif

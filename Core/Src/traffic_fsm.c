#include "traffic_config.h"
#include "traffic_hw.h"
#include "traffic_fsm.h"

uint8_t state = RedLight;
uint32_t start_lighting = 0;
extern volatile uint32_t trafficc_light_timer;
extern uint32_t last_button_click;
extern volatile uint32_t button_rattle_timer;

void TrafficLight() {

	static uint8_t traffic_direction = down;
	switch (state) {
	case RedLight:
		HW_SetLights_Red();
		if (trafficc_light_timer - start_lighting >= TIME_RED_PHASE) {
			state = YellowLight;
			start_lighting = trafficc_light_timer;
			traffic_direction = down;
		}
		break;
	case YellowLight:
		HW_SetLights_Yellow();
		if (trafficc_light_timer - start_lighting >= TIME_YELLOW_PHASE) {
			if (traffic_direction == down) {
				state = GreenLight;
				start_lighting = trafficc_light_timer;
			} else {
				state = RedLight;
				start_lighting = trafficc_light_timer;
			}
		}
		break;
	case GreenLight:
		HW_SetLights_Green();
		if (trafficc_light_timer - start_lighting >= TIME_GREEN_PHASE) {
			state = YellowLight;
			start_lighting = trafficc_light_timer;
			traffic_direction = up;
		}
		break;
	case PedestrianPhase:
		if (trafficc_light_timer - start_lighting < TIME_PEDESTRIAN_YELLOW) {
			HW_Pedestrian_Phase1();
		} else if (trafficc_light_timer - start_lighting < TIME_PEDESTRIAN_TOTAL) {
			HW_Pedestrian_Phase2();
		} else {
			HW_Pedestrian_Clear();
			traffic_direction = down;
			state = YellowLight;
			start_lighting = trafficc_light_timer;
		}
		break;
	default:
		break;
	}
}

void HAL_GPIO_EXTI_Callback(uint16_t GPIO_Pin) {
	if (GPIO_Pin == (1 << PIN_BUTTON)) {
		if (button_rattle_timer - last_button_click >= TIME_BUTTON_DEBOUNCE) {
			state = PedestrianPhase;
			last_button_click = button_rattle_timer;
		}
	}
}

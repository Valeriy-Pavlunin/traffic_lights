#include "main.h"
#include "traffic_config.h"
#include "traffic_hw.h"

void HW_SetLights_Red() {
	GPIOB->BSRR = (1 << PIN_LED_RED)
			| (1 << (PIN_LED_YELLOW + BSRR_RESET_OFFSET))
			| (1 << (PIN_LED_GREEN + BSRR_RESET_OFFSET));
}
void HW_SetLights_Yellow() {
	GPIOB->BSRR = (1 << (PIN_LED_RED + BSRR_RESET_OFFSET))
			| (1 << PIN_LED_YELLOW)
			| (1 << (PIN_LED_GREEN + BSRR_RESET_OFFSET));
}
void HW_SetLights_Green() {
	GPIOB->BSRR = (1 << (PIN_LED_RED + BSRR_RESET_OFFSET))
			| (1 << (PIN_LED_YELLOW + BSRR_RESET_OFFSET))
			| (1 << PIN_LED_GREEN);
}
void HW_Pedestrian_Phase1() {
	GPIOB->BSRR = (1 << (PIN_LED_RED + BSRR_RESET_OFFSET))
			| (1 << PIN_LED_YELLOW)
			| (1 << (PIN_LED_GREEN + BSRR_RESET_OFFSET));
}
void HW_Pedestrian_Phase2() {
	GPIOB->ODR = (1 << PIN_BUZZER) | (1 << PIN_LED_RED);
}
void HW_Pedestrian_Clear() {
	GPIOB->ODR &= ~((1 << PIN_LED_RED) | (1 << PIN_BUZZER));
}

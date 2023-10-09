void readWaterLevel();
void monitorWaterLevel();

int liquidSensorPin; 
int buzzerPin=0; 
int buzzer_reg;
int main() {

     buzzer_reg = buzzerPin*2;
     asm volatile(
	"or x30, x30, %0\n\t" 
	:
	:"r"(buzzer_reg)
	:"x30"
	);

    while (1) {
        readWaterLevel();
    }
    return 0;
}

// Function to monitor water level and control the buzzer
void monitorWaterLevel() {
 
    asm volatile(
	"andi %0, x30, 1\n\t"
	:"=r"(liquidSensorPin)
	:
	:
	);

        if (liquidSensorPin) {
            // Simulate activating the buzzer (replace with actual buzzer control)
            //digital_write(buzzerPin, 1;
            //printf("Buzzer is ON\n");
            buzzerPin = 1;
            buzzer_reg = buzzerPin*2;
            asm volatile(
		"or x30, x30, %0\n\t" 
		:
		:"r"(buzzer_reg)
		:"x30"
		);
        } else {
            // Simulate deactivating the buzzer (replace with actual buzzer control)
            //digital_write(buzzerPin, 0);
            //printf("Buzzer is OFF\n");
            buzzerPin = 0;
            buzzer_reg = buzzerPin*2;
            asm volatile(
		"or x30, x30, %0\n\t" 
		:
		:"r"(buzzer_reg)
		:"x30"
		);
        }
    }


void readWaterLevel() {
    monitorWaterLevel();
}


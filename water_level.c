void readWaterLevel();
void monitorWaterLevel();

int main() {
    while (1) {
        readWaterLevel();
    }
    return 0;
}

// Function to monitor water level and control the buzzer
void monitorWaterLevel() {
 
    // Replace these variables with actual sensor pins and setup
    int liquidSensorPin; // Replace with the actual GPIO pin connected to the liquid level sensor
    int buzzerPin=0; // Replace with the actual GPIO pin connected to the buzzer
    int buzzer_reg;
    buzzer_reg = buzzerPin*2;
     asm volatile(
	"or x30, x30, %0\n\t" 
	:
	:"r"(buzzer_reg)
	:"x30"
	);
    
    asm volatile(
	"andi %0, x30, 1\n\t"
	:"=r"(liquidSensorPin)
	:
	:
	);
    

    while (1) {
       // int Liquid_level = digital_read(liquidSensorPin);
        //printf("Powered By Techeonics ");
        //printf("Liquid_level= %d\n", Liquid_level);

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
}

void readWaterLevel() {
    monitorWaterLevel();
}

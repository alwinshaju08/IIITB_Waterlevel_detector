#include <stdio.h>

// Function to monitor water level and control the buzzer
void monitorWaterLevel() {
    int Liquid_level = 0;

    // Replace these variables with actual sensor pins and setup
    int liquidSensorPin = 0; // Replace with the actual GPIO pin connected to the liquid level sensor
    int buzzerPin = 1; // Replace with the actual GPIO pin connected to the buzzer

    

    while (1) {
       
        //printf("Powered By Techeonics ");
        //printf("Liquid_level= %d\n", Liquid_level);

        if (Liquid_level == 1) {
            // Simulate activating the buzzer (replace with actual buzzer control)
            // digitalWrite(buzzerPin, HIGH);
            //printf("Buzzer is ON\n");
        } else {
            // Simulate deactivating the buzzer (replace with actual buzzer control)
            // digitalWrite(buzzerPin, LOW);
            //printf("Buzzer is OFF\n");
        }
    }

    // Clean up any resources here if needed
    // For example, you can release GPIO pins
}

void readWaterLevel() {
    monitorWaterLevel();
}

int main() {
    while (1) {
        readWaterLevel();
    }
    return 0;
}

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
 
    int Liquid_level = 0;
    // Replace these variables with actual sensor pins and setup
    int liquidSensorPin = 0; // Replace with the actual GPIO pin connected to the liquid level sensor
    int buzzerPin = 1; // Replace with the actual GPIO pin connected to the buzzer

    

    while (1) {
       // int Liquid_level = digital_read(liquidSensorPin);
        //printf("Powered By Techeonics ");
        //printf("Liquid_level= %d\n", Liquid_level);

        if (Liquid_level == 1) {
            // Simulate activating the buzzer (replace with actual buzzer control)
            //digital_write(buzzerPin, 1;
            //printf("Buzzer is ON\n");
        } else {
            // Simulate deactivating the buzzer (replace with actual buzzer control)
            //digital_write(buzzerPin, 0);
            //printf("Buzzer is OFF\n");
        }
    }
}

void readWaterLevel() {
    monitorWaterLevel();
}
}

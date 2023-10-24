/*
#include<stdio.h>
#include<stdlib.h>
*/

int main() {
    //int test,test1,test2,test3,test4;
    int liquidSensorPin;
    int buzzerPin = 0;
    int buzzer_reg;
    int solenoid ;
    int solenoid_reg; // Register for the solenoid
    int switchValue;  // Input switch pin
    int mask1 = 0xFFFFFFF3;
    buzzer_reg = buzzerPin * 4;
    solenoid_reg = solenoid * 8; // Calculate the register for the solenoid

    asm volatile(
        "and x30, x30, %2\n\t"
        "or x30, x30, %0\n\t"
        "or x30, x30, %1\n\t"
        :
        : "r"(buzzer_reg), "r"(solenoid_reg),"r"(mask1)
        : "x30"
    );
     /*
	    asm volatile(
    	"addi x30, x30, 0\n\t"
    	:"=r"(test)
    	:
    	:"x30"
    	);
    	printf("Test = %d\n",test);
        printf("LiquidSensorPin = %d, switchvalue=%d,buzzer_reg = %d,  solenoid_reg=%d\n",liquidSensorPin,switchValue,buzzer_reg,solenoid_reg);
	//printf("Inside while 1\n");*/
    	//int z;
//for(z=0;z<1;z++)
    while (1) 
    {
        
        asm volatile(
            "andi %0, x30, 1\n\t" // Assuming switch is connected to bit 3 (8 in binary)
            : "=r"(switchValue)
            :
            :
        );

        int solenoid = 1;
        
	/*asm volatile(
    	"addi %0, x30, 0\n\t"
    	:"=r"(test1)
    	:
    	:"x30"
    	);
    	printf("test1 = %d\n",test1);*/
        //switchValue=0;
	//printf("Reset Button_val=%d\n",reset_button);
	

        if (switchValue) {
            // Simulate activating the buzzer and solenoid (replace with actual control)
            asm volatile(
                "andi %0, x30, 2\n\t"
                : "=r"(liquidSensorPin)
                :
                :
            );
           /*asm volatile(
    	"addi %0, x30, 0\n\t"
    	:"=r"(test2)
    	:
    	:"x30"
    	);
    	printf("test2 = %d\n",test2);*/
        //liquidSensorPin=0;

            if (liquidSensorPin) {
                // Simulate activating the buzzer and solenoid (replace with actual control)
                // digital_write(buzzerPin, 1);
                // digital_write(solenoid, 0);
                // printf("Buzzer ON and solenoid are Off\n");
                buzzerPin = 1;
                solenoid = 0;
               /* asm volatile(
    	"addi %0, x30, 0\n\t"
    	:"=r"(test3)
    	:
    	:"x30"
    	);
    	printf("test3 = %d\n",test3);*/
            } else {
                // Simulate deactivating the buzzer and solenoid (replace with actual control)
                // digital_write(buzzerPin, 0);
                // digital_write(solenoid, 1);
                // printf("Buzzer OFF and solenoid are ON\n");
                buzzerPin = 0;
                solenoid = 1;
                 /*asm volatile(
    	"addi %0, x30, 0\n\t"
    	:"=r"(test3)
    	:
    	:"x30"
    	);
    	printf("test3 = %d\n",test3);*/
            }

            // Update the corresponding registers for the buzzer and solenoid
            buzzer_reg = buzzerPin * 4;
            solenoid_reg = solenoid * 8;

            asm volatile(
                "and x30, x30, %2\n\t"
                "or x30, x30, %0\n\t"
                "or x30, x30, %1\n\t"
                :
                : "r"(buzzer_reg), "r"(solenoid_reg),"r"(mask1)
                : "x30"
            );
    /*      
    asm volatile(
    	"addi %0, x30, 0\n\t"
    	:"=r"(test4)
    	:
    	:"x30"
    	);
    	printf("Test4 = %d\n",test4);
    printf("LiquidSensorPin = %d, switchvalue=%d,buzzer_reg = %d,  solenoid_reg=%d\n",liquidSensorPin,switchValue,buzzer_reg,solenoid_reg);
    
    */

        }
    }

    return 0;
}

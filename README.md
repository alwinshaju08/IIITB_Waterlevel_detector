# IIITB_Riscv_Waterlevel_detector

This github repository summarizes the progress made in the ASIC class for the riscv_project. Quick links:

- [Day-0-Introduction to Project](#day-0-Introduction-to-Project)
  
- [Word of Thanks](#Word-of-Thanks)

- [Reference](#reference)

# Aim 

In this project, we aim to create a contactless water level indicator to fully embrace automation. The goal is to implement this system at our college, as our current water purifiers lack an automatic water bottle filling feature. Our plan is to incorporate a water level indicator equipped with a buzzer. When an empty bottle is positioned beneath it, the purifier will fill the bottle until the water level reaches the sensor's position within the purifier. Furthermore, this project can be adapted for use in hospitals to monitor and detect when drip bottles become empty.Best thing about this project is we are implementing this all on riscv processor rather than arduino board .

# Requirements 

Here we are using *DFROBOT SEN0204* which is a Water/Liquid Level Sensor, Non-Contact, Digital Interface . This is a non-contact water / liquid level sensor. It utilizes advanced signal processing technology by using a powerful chip (XKC-Y25-T12V) with high-speed operation capacity to achieve non-contact liquid level detection.
No contact with liquid makes the module suitable for hazardous applications such as detecting toxic substances, strong acid, strong alkali, and all kinds of liquid in an airtight container under high pressure.
There are no special requirements for the liquid or container and this liquid sensor is easy to use and easy to install.
The liquid level sensor is equipped with an interface adapter that makes it compatible with DFRobot "Gravity" interface. Four levels of sensitivity can be configured by pressing the SET button.


# Contactless_Waterlevel_detector

![1](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/2fce7839-cf1c-4690-bfee-2a73fc0c8cf5)

# Block Diagram

<img width="685" alt="Screenshot 2023-10-01 at 5 50 12 PM" src="https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/b8251533-a7e8-4ee4-914b-91b609c3363f">

## Testing

* Open a terminal window.
* Navigate to the directory containing the sample.c file.
* Design a function that executes the intended logic you require.
* Compile the code using the GCC compiler and verify the output:
  
```
gcc water_level.c
./a.out
```

<img width="682" alt="Screenshot 2023-10-01 at 12 35 52 PM" src="https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/dd18791a-d1c5-4a7a-9194-13d574d44238">

## C code

```
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

```
## Assembly code conversion

Compile the c program using RISCV-V GNU Toolchain and dump the assembly code into water_level_assembly.txt using the below commands.

```
riscv64-unknown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o ./out water_level.c
riscv64-unknown-elf-objdump -d  -r out > water_level_assembly.txt

```

### Note:
In the above c program, digital read and digital write functions are commented to show how the inputs and outputs are given. For now, we need only the logic which controls the Water_level_sensor.

```


out:     file format elf32-littleriscv


Disassembly of section .text:

00010054 <main>:
   10054:	fd010113          	addi	sp,sp,-48
   10058:	02812623          	sw	s0,44(sp)
   1005c:	03010413          	addi	s0,sp,48
   10060:	fe042623          	sw	zero,-20(s0)
   10064:	ff300793          	li	a5,-13
   10068:	fef42223          	sw	a5,-28(s0)
   1006c:	fec42783          	lw	a5,-20(s0)
   10070:	00279793          	slli	a5,a5,0x2
   10074:	fef42023          	sw	a5,-32(s0)
   10078:	fdc42783          	lw	a5,-36(s0)
   1007c:	00379793          	slli	a5,a5,0x3
   10080:	fcf42c23          	sw	a5,-40(s0)
   10084:	fe042783          	lw	a5,-32(s0)
   10088:	fd842703          	lw	a4,-40(s0)
   1008c:	fe442683          	lw	a3,-28(s0)
   10090:	00df7f33          	and	t5,t5,a3
   10094:	00ff6f33          	or	t5,t5,a5
   10098:	00ef6f33          	or	t5,t5,a4
   1009c:	001f7793          	andi	a5,t5,1
   100a0:	fcf42a23          	sw	a5,-44(s0)
   100a4:	00100793          	li	a5,1
   100a8:	fef42423          	sw	a5,-24(s0)
   100ac:	fd442783          	lw	a5,-44(s0)
   100b0:	fe0786e3          	beqz	a5,1009c <main+0x48>
   100b4:	002f7793          	andi	a5,t5,2
   100b8:	fcf42823          	sw	a5,-48(s0)
   100bc:	fd042783          	lw	a5,-48(s0)
   100c0:	00078a63          	beqz	a5,100d4 <main+0x80>
   100c4:	00100793          	li	a5,1
   100c8:	fef42623          	sw	a5,-20(s0)
   100cc:	fe042423          	sw	zero,-24(s0)
   100d0:	0100006f          	j	100e0 <main+0x8c>
   100d4:	fe042623          	sw	zero,-20(s0)
   100d8:	00100793          	li	a5,1
   100dc:	fef42423          	sw	a5,-24(s0)
   100e0:	fec42783          	lw	a5,-20(s0)
   100e4:	00279793          	slli	a5,a5,0x2
   100e8:	fef42023          	sw	a5,-32(s0)
   100ec:	fe842783          	lw	a5,-24(s0)
   100f0:	00379793          	slli	a5,a5,0x3
   100f4:	fcf42c23          	sw	a5,-40(s0)
   100f8:	fe042783          	lw	a5,-32(s0)
   100fc:	fd842703          	lw	a4,-40(s0)
   10100:	fe442683          	lw	a3,-28(s0)
   10104:	00df7f33          	and	t5,t5,a3
   10108:	00ff6f33          	or	t5,t5,a5
   1010c:	00ef6f33          	or	t5,t5,a4
   10110:	f8dff06f          	j	1009c <main+0x48>

```
My assembly code contains instructions like addi, srai, sw, and so on. Running the sample.py on this water_level_assembly.txt would yield:

```
Number of different instructions: 10
List of unique instructions:
and
sw
beqz
j
li
lw
or
addi
andi
slli


```

# Spike results:

```
riscv64-unknown-elf-gcc -march=rv64i -mabi=lp64 -ffreestanding -o out water_level.c
spike pk out

```

Here i have done here without -march and -mabi(this commands not supportable in mac) but i checked it out in my friends laptop with -march and -mabi , it is still working for those commands : 

when i am giving switch value as 1 and liquidsensor as 0 : it will enter loop and due to masking of input my input pins will be shown 0 and output onlyy buzzer is ON (0) while solenoid will remain open (1) i.e i am getting test cases as 8

<img width="682" alt="Screenshot 2023-10-24 at 7 59 01 PM" src="https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/05351251-f8bf-498a-8e3d-d5fdc5c1e0c8">

when i am giving switch value as 1 and liquidsensor as 1 : it will enter loop and due to masking of input my input pins will be shown 0 and output onlyy buzzer is ON (1) while solenoid will close (0) i.e i am getting test cases as 4

<img width="638" alt="Screenshot 2023-10-24 at 7 59 51 PM" src="https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/fff57d77-3a7e-4c58-a607-3de64a0c9eee">

when i am giving swicth value as 0 and liquidsensor as 0 : it is stopping in the test case 1 itself as it won't enter loop


<img width="682" alt="Screenshot 2023-10-24 at 8 00 27 PM" src="https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/a7da28fb-9b60-4176-a9ca-557dd898a587">

# Functional Verification : 

Here in First example when switch value and sensor_pin both are zero then there is no output as system is not working state now ,write done basically means uart has done transmitting data

![Screenshot from 2023-10-25 01-57-14](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/1a3a09c0-3d48-458c-a8d5-0df39dcf0ddb)

Here in 2nd example when switch value is 1 and sensor_pin both is 0 then there system is working and solenoid valve is open so that water flows but the buzzer wont buzz that why that bit will be in 0 while solenoid will be High '1' and here solenoid is 2nd bit while buzzer pin is 1st bit .Thats why we are getting ```10```


![Screenshot from 2023-10-25 01-53-14](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/3ddf9098-98fc-4f6b-9c3d-b5f43958fa8c)

Here in 3rd example when switch value is 1 and sensor_pin both is also 1 then the system is done filling water in the bottle and solenoid valve will close that is it will become 0 while buzzer will start buzzing that is it will become High '1' and here solenoid is 2nd bit while buzzer pin is 1st bit .Thats why we are getting ```01```


![Screenshot from 2023-10-25 01-47-27](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/7275355d-c5a3-47ff-b65f-3aa414073ff3)




## Word of Thanks
I sciencerly thank **Mr. Kunal Gosh**(Founder/**VSD**) for helping me out to complete this flow smoothly.

## Acknowledgement
- Kunal Ghosh, VSD Corp. Pvt. Ltd.
- Skywater Foundry
- Chatgpt
- Kanish R,Colleague,IIIT B
- Sumanto Kar,VSD Corp.
- Pruthvi parate,MS
- Bhargav DV,MS
- Emil Jayanth Lal, IIITB
- Shant Rakshit,IIIT B
- N sai Sampath,IIIT B
  
  
## Reference 


- https://github.com/The-OpenROAD-Project/OpenSTA.git
- https://github.com/kunalg123
- https://www.vsdiat.com
- https://github.com/SakethGajawada/RISCV-GNU

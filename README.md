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
int main() {
    int liquidSensorPin;
    int buzzerPin = 0;
    int solenoid = 0; // Additional output pin
    int buzzer_reg;
    int solenoid_reg; // Register for the solenoid
    int switchPin ;// Input switch pin
    int switchValue; 

    buzzer_reg = buzzerPin * 4;
    solenoid_reg = solenoid * 8; // Calculate the register for the solenoid

    asm volatile(
        "or x30, x30, %0\n\t"
        "or x30, x30, %1\n\t"
        :
        : "r"(buzzer_reg), "r"(solenoid_reg)
        : "x30"
    );

    while (1) {
        
        asm volatile(
            "andi %0, x30, 1\n\t" // Assuming switch is connected to bit 3 (8 in binary)
            : "=r"(switchValue)
            :
            :
        );

        if (switchValue) {
            // Simulate activating the buzzer and solenoid (replace with actual control)
            asm volatile(
                "andi %0, x30, 2\n\t"
                : "=r"(liquidSensorPin)
                :
                :
            );

            if (liquidSensorPin) {
                // Simulate activating the buzzer and solenoid (replace with actual control)
                // digital_write(buzzerPin, 1);
                // digital_write(solenoid, 1);
                // printf("Buzzer and solenoid are ON\n");
                buzzerPin = 1;
                solenoid = 1;
            } else {
                // Simulate deactivating the buzzer and solenoid (replace with actual control)
                // digital_write(buzzerPin, 0);
                // digital_write(solenoid, 0);
                // printf("Buzzer and solenoid are OFF\n");
                buzzerPin = 0;
                solenoid = 0;
            }

            // Update the corresponding registers for the buzzer and solenoid
            buzzer_reg = buzzerPin * 4;
            solenoid_reg = solenoid * 8;

            asm volatile(
                "or x30, x30, %0\n\t"
                "or x30, x30, %1\n\t"
                :
                : "r"(buzzer_reg), "r"(solenoid_reg)
                : "x30"
            );
        }
    }

    return 0;
}

```
## Assembly code conversion

Compile the c program using RISCV-V GNU Toolchain and dump the assembly code into water_level_assembly.txt using the below commands.

```
riscv32-unkown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -nostdlib -o ./out water_level.c
riscv32-unknown-elf-objdump -d  -r out > water_level_assembly.txt

```

### Note:
In the above c program, digital read and digital write functions are commented to show how the inputs and outputs are given. For now, we need only the logic which controls the Water_level_sensor.

```



out:     file format elf32-littleriscv


Disassembly of section .text:

00010094 <main>:
   10094:	ff010113          	add	sp,sp,-16
   10098:	00112623          	sw	ra,12(sp)
   1009c:	00812423          	sw	s0,8(sp)
   100a0:	01010413          	add	s0,sp,16
   100a4:	000117b7          	lui	a5,0x11
   100a8:	16c7a783          	lw	a5,364(a5) # 1116c <buzzerPin>
   100ac:	00179713          	sll	a4,a5,0x1
   100b0:	80e1a423          	sw	a4,-2040(gp) # 11170 <buzzer_reg>
   100b4:	8081a783          	lw	a5,-2040(gp) # 11170 <buzzer_reg>
   100b8:	00ff6f33          	or	t5,t5,a5
   100bc:	084000ef          	jal	10140 <readWaterLevel>
   100c0:	ffdff06f          	j	100bc <main+0x28>

000100c4 <monitorWaterLevel>:
   100c4:	ff010113          	add	sp,sp,-16
   100c8:	00812623          	sw	s0,12(sp)
   100cc:	01010413          	add	s0,sp,16
   100d0:	001f7713          	and	a4,t5,1
   100d4:	000117b7          	lui	a5,0x11
   100d8:	16e7a423          	sw	a4,360(a5) # 11168 <__DATA_BEGIN__>
   100dc:	000117b7          	lui	a5,0x11
   100e0:	1687a783          	lw	a5,360(a5) # 11168 <__DATA_BEGIN__>
   100e4:	02078663          	beqz	a5,10110 <monitorWaterLevel+0x4c>
   100e8:	000117b7          	lui	a5,0x11
   100ec:	00100713          	li	a4,1
   100f0:	16e7a623          	sw	a4,364(a5) # 1116c <buzzerPin>
   100f4:	000117b7          	lui	a5,0x11
   100f8:	16c7a783          	lw	a5,364(a5) # 1116c <buzzerPin>
   100fc:	00179713          	sll	a4,a5,0x1
   10100:	80e1a423          	sw	a4,-2040(gp) # 11170 <buzzer_reg>
   10104:	8081a783          	lw	a5,-2040(gp) # 11170 <buzzer_reg>
   10108:	00ff6f33          	or	t5,t5,a5
   1010c:	0240006f          	j	10130 <monitorWaterLevel+0x6c>
   10110:	000117b7          	lui	a5,0x11
   10114:	1607a623          	sw	zero,364(a5) # 1116c <buzzerPin>
   10118:	000117b7          	lui	a5,0x11
   1011c:	16c7a783          	lw	a5,364(a5) # 1116c <buzzerPin>
   10120:	00179713          	sll	a4,a5,0x1
   10124:	80e1a423          	sw	a4,-2040(gp) # 11170 <buzzer_reg>
   10128:	8081a783          	lw	a5,-2040(gp) # 11170 <buzzer_reg>
   1012c:	00ff6f33          	or	t5,t5,a5
   10130:	00000013          	nop
   10134:	00c12403          	lw	s0,12(sp)
   10138:	01010113          	add	sp,sp,16
   1013c:	00008067          	ret

00010140 <readWaterLevel>:
   10140:	ff010113          	add	sp,sp,-16
   10144:	00112623          	sw	ra,12(sp)
   10148:	00812423          	sw	s0,8(sp)
   1014c:	01010413          	add	s0,sp,16
   10150:	f75ff0ef          	jal	100c4 <monitorWaterLevel>
   10154:	00000013          	nop
   10158:	00c12083          	lw	ra,12(sp)
   1015c:	00812403          	lw	s0,8(sp)
   10160:	01010113          	add	sp,sp,16
   10164:	00008067          	ret

```
My assembly code contains instructions like addi, srai, sw, and so on. Running the sample.py on this water_level_assembly.txt would yield:

```
Number of different instructions: 13
List of unique instructions:
ret
li
j
lui
sw
or
and
sll
nop
beqz
lw
add
jal

```

## Word of Thanks
I sciencerly thank **Mr. Kunal Gosh**(Founder/**VSD**) for helping me out to complete this flow smoothly.

## Acknowledgement
- Kunal Ghosh, VSD Corp. Pvt. Ltd.
- Skywater Foundry
- Chatgpt
- Kanish R,Colleague,IIIT B
- Sumanto Kar,VSD Corp.
- Mayank Kabra,imtech
- Pruthvi parate,MS
- Bhargav DV,MS
- Emil Jayanth Lal, IIITB
- Shant Rakshit,IIIT B
  
  
## Reference 


- https://github.com/The-OpenROAD-Project/OpenSTA.git
- https://github.com/kunalg123
- https://www.vsdiat.com
- https://github.com/SakethGajawada/RISCV-GNU

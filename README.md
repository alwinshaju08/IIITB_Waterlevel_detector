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
    int solenoid = 1; // Additional output pin
    int buzzer_reg;
    int solenoid_reg; // Register for the solenoid
    int switchValue;  // Input switch pin

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
                solenoid = 0;
            } else {
                // Simulate deactivating the buzzer and solenoid (replace with actual control)
                // digital_write(buzzerPin, 0);
                // digital_write(solenoid, 0);
                // printf("Buzzer and solenoid are OFF\n");
                buzzerPin = 0;
                solenoid = 1;
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

00010074 <main>:
   10074:	fd010113          	add	sp,sp,-48
   10078:	02812623          	sw	s0,44(sp)
   1007c:	03010413          	add	s0,sp,48
   10080:	fe042623          	sw	zero,-20(s0)
   10084:	00100793          	li	a5,1
   10088:	fef42423          	sw	a5,-24(s0)
   1008c:	fec42783          	lw	a5,-20(s0)
   10090:	00279793          	sll	a5,a5,0x2
   10094:	fef42223          	sw	a5,-28(s0)
   10098:	fe842783          	lw	a5,-24(s0)
   1009c:	00379793          	sll	a5,a5,0x3
   100a0:	fef42023          	sw	a5,-32(s0)
   100a4:	fe442783          	lw	a5,-28(s0)
   100a8:	fe042703          	lw	a4,-32(s0)
   100ac:	00ff6f33          	or	t5,t5,a5
   100b0:	00ef6f33          	or	t5,t5,a4
   100b4:	001f7793          	and	a5,t5,1
   100b8:	fcf42e23          	sw	a5,-36(s0)
   100bc:	fdc42783          	lw	a5,-36(s0)
   100c0:	fe078ae3          	beqz	a5,100b4 <main+0x40>
   100c4:	002f7793          	and	a5,t5,2
   100c8:	fcf42c23          	sw	a5,-40(s0)
   100cc:	fd842783          	lw	a5,-40(s0)
   100d0:	00078a63          	beqz	a5,100e4 <main+0x70>
   100d4:	00100793          	li	a5,1
   100d8:	fef42623          	sw	a5,-20(s0)
   100dc:	fe042423          	sw	zero,-24(s0)
   100e0:	0100006f          	j	100f0 <main+0x7c>
   100e4:	fe042623          	sw	zero,-20(s0)
   100e8:	00100793          	li	a5,1
   100ec:	fef42423          	sw	a5,-24(s0)
   100f0:	fec42783          	lw	a5,-20(s0)
   100f4:	00279793          	sll	a5,a5,0x2
   100f8:	fef42223          	sw	a5,-28(s0)
   100fc:	fe842783          	lw	a5,-24(s0)
   10100:	00379793          	sll	a5,a5,0x3
   10104:	fef42023          	sw	a5,-32(s0)
   10108:	fe442783          	lw	a5,-28(s0)
   1010c:	fe042703          	lw	a4,-32(s0)
   10110:	00ff6f33          	or	t5,t5,a5
   10114:	00ef6f33          	or	t5,t5,a4
   10118:	f9dff06f          	j	100b4 <main+0x40>

```
My assembly code contains instructions like addi, srai, sw, and so on. Running the sample.py on this water_level_assembly.txt would yield:

```
Number of different instructions: 9
List of unique instructions:
or
lw
sll
j
li
sw
beqz
add
and

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

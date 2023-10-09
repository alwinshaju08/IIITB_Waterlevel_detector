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
   10074:	ff010113          	add	sp,sp,-16
   10078:	00112623          	sw	ra,12(sp)
   1007c:	00812423          	sw	s0,8(sp)
   10080:	01010413          	add	s0,sp,16
   10084:	084000ef          	jal	10108 <readWaterLevel>
   10088:	ffdff06f          	j	10084 <main+0x10>

0001008c <monitorWaterLevel>:
   1008c:	fe010113          	add	sp,sp,-32
   10090:	00812e23          	sw	s0,28(sp)
   10094:	02010413          	add	s0,sp,32
   10098:	fe042623          	sw	zero,-20(s0)
   1009c:	fec42783          	lw	a5,-20(s0)
   100a0:	00179793          	sll	a5,a5,0x1
   100a4:	fef42423          	sw	a5,-24(s0)
   100a8:	fe842783          	lw	a5,-24(s0)
   100ac:	00ff6f33          	or	t5,t5,a5
   100b0:	001f7793          	and	a5,t5,1
   100b4:	fef42223          	sw	a5,-28(s0)
   100b8:	fe442783          	lw	a5,-28(s0)
   100bc:	02078263          	beqz	a5,100e0 <monitorWaterLevel+0x54>
   100c0:	00100793          	li	a5,1
   100c4:	fef42623          	sw	a5,-20(s0)
   100c8:	fec42783          	lw	a5,-20(s0)
   100cc:	00179793          	sll	a5,a5,0x1
   100d0:	fef42423          	sw	a5,-24(s0)
   100d4:	fe842783          	lw	a5,-24(s0)
   100d8:	00ff6f33          	or	t5,t5,a5
   100dc:	01c0006f          	j	100f8 <monitorWaterLevel+0x6c>
   100e0:	fe042623          	sw	zero,-20(s0)
   100e4:	fec42783          	lw	a5,-20(s0)
   100e8:	00179793          	sll	a5,a5,0x1
   100ec:	fef42423          	sw	a5,-24(s0)
   100f0:	fe842783          	lw	a5,-24(s0)
   100f4:	00ff6f33          	or	t5,t5,a5
   100f8:	00000013          	nop
   100fc:	01c12403          	lw	s0,28(sp)
   10100:	02010113          	add	sp,sp,32
   10104:	00008067          	ret

00010108 <readWaterLevel>:
   10108:	ff010113          	add	sp,sp,-16
   1010c:	00112623          	sw	ra,12(sp)
   10110:	00812423          	sw	s0,8(sp)
   10114:	01010413          	add	s0,sp,16
   10118:	f75ff0ef          	jal	1008c <monitorWaterLevel>
   1011c:	00000013          	nop
   10120:	00c12083          	lw	ra,12(sp)
   10124:	00812403          	lw	s0,8(sp)
   10128:	01010113          	add	sp,sp,16
   1012c:	00008067          	ret

```
My assembly code contains instructions like addi, srai, sw, and so on. Running the sample.py on this water_level_assembly.txt would yield:

```
Number of different instructions: 12
List of unique instructions:
lw
j
beqz
jal
sw
add
sll
and
or
nop
li
ret

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
  
## Reference 


- https://github.com/The-OpenROAD-Project/OpenSTA.git
- https://github.com/kunalg123
- https://www.vsdiat.com
- https://github.com/SakethGajawada/RISCV-GNU

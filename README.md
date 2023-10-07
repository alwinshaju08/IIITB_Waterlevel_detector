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
```
## Assembly code conversion

Compile the c program using RISCV-V GNU Toolchain and dump the assembly code into sample_assembly.txt using the below commands.

```
riscv32-unkown-elf-gcc -march=rv32i -mabi=ilp32 -ffreestanding -o ./water_level.o water_level.c
riscv32-unknown-elf-objdump -d  water_level.o > water_level_assembly.txt

```

### Note:
In the above c program, digital read and digital write functions are commented to show how the inputs and outputs are given. For now, we need only the logic which controls the Water_level_sensor.

```
water_level.o:     file format elf32-littleriscv


Disassembly of section .text:

00000000 <main>:
   0:	ff010113          	add	sp,sp,-16
   4:	00112623          	sw	ra,12(sp)
   8:	00812423          	sw	s0,8(sp)
   c:	01010413          	add	s0,sp,16

00000010 <.L2>:
  10:	00000097          	auipc	ra,0x0
  14:	000080e7          	jalr	ra # 10 <.L2>
  18:	ff9ff06f          	j	10 <.L2>

0000001c <monitorWaterLevel>:
  1c:	fe010113          	add	sp,sp,-32
  20:	00812e23          	sw	s0,28(sp)
  24:	02010413          	add	s0,sp,32
  28:	fe042623          	sw	zero,-20(s0)
  2c:	fec42783          	lw	a5,-20(s0)
  30:	00179793          	sll	a5,a5,0x1
  34:	fef42423          	sw	a5,-24(s0)
  38:	fe842783          	lw	a5,-24(s0)
  3c:	00ff6f33          	or	t5,t5,a5
  40:	001f7793          	and	a5,t5,1
  44:	fef42223          	sw	a5,-28(s0)

00000048 <.L6>:
  48:	fe442783          	lw	a5,-28(s0)
  4c:	02078263          	beqz	a5,70 <.L4>
  50:	00100793          	li	a5,1
  54:	fef42623          	sw	a5,-20(s0)
  58:	fec42783          	lw	a5,-20(s0)
  5c:	00179793          	sll	a5,a5,0x1
  60:	fef42423          	sw	a5,-24(s0)
  64:	fe842783          	lw	a5,-24(s0)
  68:	00ff6f33          	or	t5,t5,a5
  6c:	fddff06f          	j	48 <.L6>

00000070 <.L4>:
  70:	fe042623          	sw	zero,-20(s0)
  74:	fec42783          	lw	a5,-20(s0)
  78:	00179793          	sll	a5,a5,0x1
  7c:	fef42423          	sw	a5,-24(s0)
  80:	fe842783          	lw	a5,-24(s0)
  84:	00ff6f33          	or	t5,t5,a5
  88:	fc1ff06f          	j	48 <.L6>

0000008c <readWaterLevel>:
  8c:	ff010113          	add	sp,sp,-16
  90:	00112623          	sw	ra,12(sp)
  94:	00812423          	sw	s0,8(sp)
  98:	01010413          	add	s0,sp,16
  9c:	00000097          	auipc	ra,0x0
  a0:	000080e7          	jalr	ra # 9c <readWaterLevel+0x10>
  a4:	00000013          	nop
  a8:	00c12083          	lw	ra,12(sp)
  ac:	00812403          	lw	s0,8(sp)
  b0:	01010113          	add	sp,sp,16
  b4:	00008067          	ret

```
My assembly code contains instructions like addi, srai, sw, and so on. Running the sample.py on this water_level_assembly.txt would yield:

```

Number of different instructions: 13
List of unique instructions:
add
nop
ret
lw
and
beqz
sll
sw
or
jalr
auipc
li
j


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

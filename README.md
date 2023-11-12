# IIITB_Riscv_Waterlevel_detector

This github repository summarizes the progress made in the ASIC class for the riscv_project. Quick links:

- [Introduction to Project](#Introduction-to-Project)
  
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
    int solenoid = 0  ;
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
   10064:	fe042223          	sw	zero,-28(s0)
   10068:	ff300793          	li	a5,-13
   1006c:	fef42023          	sw	a5,-32(s0)
   10070:	fec42783          	lw	a5,-20(s0)
   10074:	00279793          	slli	a5,a5,0x2
   10078:	fcf42e23          	sw	a5,-36(s0)
   1007c:	fe442783          	lw	a5,-28(s0)
   10080:	00379793          	slli	a5,a5,0x3
   10084:	fcf42c23          	sw	a5,-40(s0)
   10088:	fdc42783          	lw	a5,-36(s0)
   1008c:	fd842703          	lw	a4,-40(s0)
   10090:	fe042683          	lw	a3,-32(s0)
   10094:	00df7f33          	and	t5,t5,a3
   10098:	00ff6f33          	or	t5,t5,a5
   1009c:	00ef6f33          	or	t5,t5,a4
   100a0:	001f7793          	andi	a5,t5,1
   100a4:	fcf42a23          	sw	a5,-44(s0)
   100a8:	00100793          	li	a5,1
   100ac:	fef42423          	sw	a5,-24(s0)
   100b0:	fd442783          	lw	a5,-44(s0)
   100b4:	fe0786e3          	beqz	a5,100a0 <main+0x4c>
   100b8:	002f7793          	andi	a5,t5,2
   100bc:	fcf42823          	sw	a5,-48(s0)
   100c0:	fd042783          	lw	a5,-48(s0)
   100c4:	00078a63          	beqz	a5,100d8 <main+0x84>
   100c8:	00100793          	li	a5,1
   100cc:	fef42623          	sw	a5,-20(s0)
   100d0:	fe042423          	sw	zero,-24(s0)
   100d4:	0100006f          	j	100e4 <main+0x90>
   100d8:	fe042623          	sw	zero,-20(s0)
   100dc:	00100793          	li	a5,1
   100e0:	fef42423          	sw	a5,-24(s0)
   100e4:	fec42783          	lw	a5,-20(s0)
   100e8:	00279793          	slli	a5,a5,0x2
   100ec:	fcf42e23          	sw	a5,-36(s0)
   100f0:	fe842783          	lw	a5,-24(s0)
   100f4:	00379793          	slli	a5,a5,0x3
   100f8:	fcf42c23          	sw	a5,-40(s0)
   100fc:	fdc42783          	lw	a5,-36(s0)
   10100:	fd842703          	lw	a4,-40(s0)
   10104:	fe042683          	lw	a3,-32(s0)
   10108:	00df7f33          	and	t5,t5,a3
   1010c:	00ff6f33          	or	t5,t5,a5
   10110:	00ef6f33          	or	t5,t5,a4
   10114:	f8dff06f          	j	100a0 <main+0x4c>

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

Here in First example when switch value and sensor_pin both are zero then there is no output as system is not in working state now ,write done basically means uart has done transmitting data

![Screenshot from 2023-10-26 18-22-58](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/4c5d5287-4ca9-4041-8e40-7a10f3b68c8e)

Here in 2nd example when switch value is 1 and sensor_pin both is 0 then there system is working and solenoid valve is open so that water flows but the buzzer wont buzz that why that bit will be in 0 while solenoid will be High '1' and here solenoid is 2nd bit while buzzer pin is 1st bit .Thats why we are getting ```10```

![Screenshot from 2023-10-26 18-19-17](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/3d013d7c-9ad1-4c46-8b3f-b422fbd1fa18)

Here in 3rd example when switch value is 1 and sensor_pin both is also 1 then the system is done filling water in the bottle and solenoid valve will close that is it will become 0 while buzzer will start buzzing that is it will become High '1' and here solenoid is 2nd bit while buzzer pin is 1st bit .Thats why we are getting ```01```

![Screenshot from 2023-10-26 18-21-36](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/82074ec4-930f-4999-948a-cfe1b112744f)

Here we can see that for 3rd example output is getting high when instruction is becoming **00EF6F33        |  	or	t5,t5,a4**

![Screenshot from 2023-10-31 18-44-18](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/fabb2723-36b0-4ed8-b363-daff983f2977)

Here we can see that for 2nd example output is getting high when instruction is becoming **F8DFF06F        |  	j	100a0 <main+0x4c>** which is the last instruction set

![Screenshot from 2023-10-31 18-58-30](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/f311876b-aca6-41be-b9b3-437d389a8573)


# Instruction verification 

So , Here Signal43,Signal45,Signal58 all are basically registers , Signal43 contains the hardwired wire zero registers(x0), Signal45 contains stack pointer(x2)register, Signal58 is the a5 register.

Here  in this first image we are checking whether it is doing the first assembly instruction ``` addi	sp,sp,-48 ``` as u can default value of sp is ```FF``` after that it becomes ``` CF ```which is -48 in hexadecimal.Here input instruction is  *00000000* , Here output instruction is *FD010113* 

![Screenshot from 2023-10-26 21-40-31](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/5e76f387-8a00-43b6-96e5-7e39ea2d7afd)

Here  in this 2nd image we are checking whether it is doing the first assembly instruction ``` li   a5,-13``` as u can default value of a5 regitser is ```00``` after that it becomes ``` FFFFFFF3 ```which is -13 in hexadecimal. Here output instruction is *FF300793* 

![Screenshot from 2023-10-26 21-44-59](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/29f3c3d8-0d33-4046-b145-0718d469c5b1)

Here  in this 3nd image we are checking whether it is doing the first assembly instruction ``` li   a5,1``` as u can default value of a5 regitser is ```00``` after that it becomes ``` 00000001 ```which is 1 in hexadecimal. Here output instruction is *00100793*

![Screenshot from 2023-10-27 09-53-06](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/0b0411e4-0d4c-411c-a215-99f83b91085c)

Here in this instruction u can also verify it by viewing instruction corresponding to calling of this instructions.(ID_instructions)

# Synthesis

Synthesis transforms the simple RTL design into a gate-level netlist with all the constraints as specified by the designer. In simple language, Synthesis is a process that converts the abstract form of design to a properly implemented chip in terms of logic gates.

Synthesis takes place in multiple steps:

- Converting RTL into simple logic gates.
- Mapping those gates to actual technology-dependent logic gates available in the technology libraries.
- Optimizing the mapped netlist keeping the constraints set by the designer intact.

# Gate Level Simulation :

GLS is generating the simulation output by running test bench with netlist file generated from synthesis as design under test. Netlist is logically same as RTL code, therefore, same test bench can be used for it.We perform this to verify logical correctness of the design after synthesizing it. Also ensuring the timing of the design is met. Folllowing are the commands to we need to convert Rtl code to netlist in yosys for that commands are :

```
read_liberty -lib sky130_fd_sc_hd__tt_025C_1v80_256.lib 
read_verilog processor.v 
synth -top wrapper
dfflibmap -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib 
abc -liberty sky130_fd_sc_hd__tt_025C_1v80_256.lib
write_verilog synth_processor_test.v

```
Folllowing are the commands to run the GLS simulation:

```
iverilog -o test synth_processor_test.v testbench.v sky130_sram_1kbyte_1rw1r_32x256_8.v sky130_fd_sc_hd.v primitives.v

```

The gtkwave output for the netlist should match the output waveform for the RTL design file. As netlist and design code have same set of inputs and outputs, we can use the same testbench and compare the waveforms.

The output waveform of the synthesized netlist given below: 

Example 1:

![Screenshot from 2023-10-30 23-20-07](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/b0071b12-ca38-4f2c-8242-336ee5601a1c)

Example 2:

![Screenshot from 2023-10-30 23-20-54](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/5a5f4fcf-e90e-4cc7-9316-cef7d08000e2)

Example 3:

![Screenshot from 2023-10-30 23-21-52](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/45dbc5e5-cdf5-4026-899e-72cdf2048a16)


**Highlighted the wrapper module after netlist created**

![Screenshot from 2023-10-30 23-29-52](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/305763b0-550f-4bf6-85e8-0017c3407c05)

# PHYSICAL DESIGN

**OVERVIEW OF PHYSICAL DESIGN**

Place and Route (PnR) is the core of any ASIC implementation and Openlane flow integrates into it several key open source tools which perform each of the respective stages of PnR. Below are the stages and the respective tools that are called by openlane for the functionalities as described:

![image](https://user-images.githubusercontent.com/110079648/187492890-1c91bb6d-596e-47da-b4c6-592d25bbec10.png)

Below are the stages and the respective tools that are called by openlane for the functionalities as described:

- Synthesis
        Generating gate-level netlist (yosys).
        Performing cell mapping (abc).
        Performing pre-layout STA (OpenSTA).
- Floorplanning
        Defining the core area for the macro as well as the cell sites and the tracks (init_fp).
        Placing the macro input and output ports (ioplacer).
        Generating the power distribution network (pdn).
- Placement
        Performing global placement (RePLace).
        Perfroming detailed placement to legalize the globally placed components (OpenDP).
- Clock Tree Synthesis (CTS)
        Synthesizing the clock tree (TritonCTS).
- Routing
        Performing global routing to generate a guide file for the detailed router (FastRoute).
        Performing detailed routing (TritonRoute)

- GDSII Generation
        Streaming out the final GDSII layout file from the routed def (Magic).

## 7.2 Openlane

OpenLane is an automated RTL to GDSII flow based on several components including OpenROAD, Yosys, Magic, Netgen, CVC, SPEF-Extractor, CU-GR, Klayout and a number of custom scripts for design exploration and optimization. The flow performs full ASIC implementation steps from RTL all the way down to GDSII.

More about Openlane at : https://github.com/The-OpenROAD-Project/OpenLane

# MAGIC

Magic is a venerable VLSI layout tool, written in the 1980's at Berkeley by John Ousterhout, now famous primarily for writing the scripting interpreter language Tcl. Due largely in part to its liberal Berkeley open-source license, magic has remained popular with universities and small companies. The open-source license has allowed VLSI engineers with a bent toward programming to implement clever ideas and help magic stay abreast of fabrication technology. However, it is the well thought-out core algorithms which lend to magic the greatest part of its popularity. Magic is widely cited as being the easiest tool to use for circuit layout, even for people who ultimately rely on commercial tools for their product design flow.

More about magic at http://opencircuitdesign.com/magic/index.html

# Preparing the Design
Preparing the design and including the lef files: The commands to prepare the design and overwite in a existing run folder the reports and results along with the command to include the lef files is given below:
```
make mount
%./flow.tcl -interactive
% package require openlane 0.9
% prep -design project -verbose 99

```
![Screenshot from 2023-11-12 21-55-03](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/c173b146-05bf-44e9-8c3d-c87b64bcd9fd)

## synthesis 

Logic synthesis uses the RTL netlist to perform HDL technology mapping. The synthesis process is normally performed in two major steps:

    GTECH Mapping – Consists of mapping the HDL netlist to generic gates what are used to perform logical optimization based on AIGERs and other topologies created from the generic mapped netlist.

    Technology Mapping – Consists of mapping the post-optimized GTECH netlist to standard cells described in the PDK

To synthesize the code run the following command

```
run_synthesis

```
**Statistics after synthesis**

![Screenshot from 2023-11-12 21-57-12](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/77a28869-202a-4429-9063-87bda63e7821)

# Floorplan

Goal is to plan the silicon area and create a robust power distribution network (PDN) to power each of the individual components of the synthesized netlist. In addition, macro placement and blockages must be defined before placement occurs to ensure a legalized GDS file. In power planning we create the ring which is connected to the pads which brings power around the edges of the chip. We also include power straps to bring power to the middle of the chip using higher metal layers which reduces IR drop and electro-migration problem.

Floorplan envrionment variables or switches:

**FP_CORE_UTIL** - floorplan core utilisation, **FP_ASPECT_RATIO** - floorplan aspect ratio ,**FP_CORE_MARGIN** - Core to die margin area ,**FP_IO_MODE** - defines pin configurations (1 = equidistant/0 = not equidistant), **FP_CORE_VMETAL** - vertical metal layer, **FP_CORE_HMETAL** - horizontal metal layer

Note: Usually, vertical metal layer and horizontal metal layer values will be 1 more than that specified in the file

Following command helps to run floorplan
```
% run_floorplan
```
![Screenshot from 2023-11-12 21-57-29](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/123dc99f-f45f-41f6-822f-dace7f17f035)

- Post the floorplan run, a .def file will have been created within the results/floorplan directory. We may review floorplan files by checking the floorplan.tcl.
- To view the floorplan: Magic is invoked after moving to the results/floorplan directory,then use the floowing command:
  
```
magic -T /home/parallels/.volare/volare/sky130/versions/1341f54f5ce0c4955326297f235e4ace1eb6d419/sky130A/libs.tech/magic/sky130A.tech lef read ../../tmp/merged.nom.lef def read wrapper.def &

```
![Screenshot from 2023-11-12 23-14-36](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/110af273-b79e-4cb0-8471-dbb89eb9a3d5)

## Die area (post floor plan)

![Screenshot from 2023-11-12 23-16-39](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/b94e94d7-1719-4976-abf4-a14b92ea4421)

## Core area (post floor plan)

![Screenshot from 2023-11-12 23-16-51](https://github.com/alwinshaju08/IIITB_Waterlevel_detector/assets/69166205/c99dcf26-d0bb-41e9-954c-49b495efa5c2)


## Word of Thanks

I sciencerly thank **Mr. Kunal Gosh**(Founder/**VSD**) for helping me out to complete this flow smoothly.

## Acknowledgement

- Kunal Ghosh, VSD Corp. Pvt. Ltd.
- Skywater Foundry
- Kanish R,IIIT B
- Pruthvi parate,MS IIITB
- Bhargav DV,MS IIIT B
- Emil Jayanth Lal, IIITB
- Shant Rakshit,IIIT B
- Sushma R,IIIT B
- N sai Sampath,IIIT B
- Mayank Kabra,Founder,Chipcron Pvt.Ltd.
  
## Reference 


- https://github.com/The-OpenROAD-Project/OpenSTA.git
- https://github.com/kunalg123
- https://www.vsdiat.com
- https://github.com/SakethGajawada/RISCV-GNU

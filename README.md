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
     asm(
	"or x30, x30, %0\n\t" 
	:"=r"(buzzer_reg));
    
    asm(
	"andi %0, x30, 1\n\t"
	:"=r"(liquidSensorPin));
    

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
            asm(
		"or x30, x30, %0\n\t" 
		:"=r"(buzzer_reg));
        } else {
            // Simulate deactivating the buzzer (replace with actual buzzer control)
            //digital_write(buzzerPin, 0);
            //printf("Buzzer is OFF\n");
            buzzerPin = 0;
            buzzer_reg = buzzerPin*2;
            asm(
		"or x30, x30, %0\n\t" 
		:"=r"(buzzer_reg));
        }
    }
}

void readWaterLevel() {
    monitorWaterLevel();
}

```
## Assembly code conversion

Compile the c program using RISCV-V GNU Toolchain and dump the assembly code into sample_assembly.txt using the above commands.

### Note:
In the above c program, digital read and digital write functions are commented to show how the inputs and outputs are given. For now, we need only the logic which controls the Water_level_sensor.

```


water_level.o:     file format elf32-littleriscv


Disassembly of section .text:

00010074 <register_fini>:
   10074:	ffff0797          	auipc	a5,0xffff0
   10078:	f8c78793          	addi	a5,a5,-116 # 0 <register_fini-0x10074>
   1007c:	00078863          	beqz	a5,1008c <register_fini+0x18>
   10080:	00000517          	auipc	a0,0x0
   10084:	12850513          	addi	a0,a0,296 # 101a8 <__libc_fini_array>
   10088:	0d80006f          	j	10160 <atexit>
   1008c:	00008067          	ret

00010090 <_start>:
   10090:	00002197          	auipc	gp,0x2
   10094:	d0018193          	addi	gp,gp,-768 # 11d90 <__global_pointer$>
   10098:	c3418513          	addi	a0,gp,-972 # 119c4 <_edata>
   1009c:	c5018613          	addi	a2,gp,-944 # 119e0 <__BSS_END__>
   100a0:	40a60633          	sub	a2,a2,a0
   100a4:	00000593          	li	a1,0
   100a8:	1f4000ef          	jal	ra,1029c <memset>
   100ac:	00000517          	auipc	a0,0x0
   100b0:	0fc50513          	addi	a0,a0,252 # 101a8 <__libc_fini_array>
   100b4:	0ac000ef          	jal	ra,10160 <atexit>
   100b8:	150000ef          	jal	ra,10208 <__libc_init_array>
   100bc:	00012503          	lw	a0,0(sp)
   100c0:	00410593          	addi	a1,sp,4
   100c4:	00000613          	li	a2,0
   100c8:	080000ef          	jal	ra,10148 <main>
   100cc:	0a80006f          	j	10174 <exit>

000100d0 <__do_global_dtors_aux>:
   100d0:	c341c783          	lbu	a5,-972(gp) # 119c4 <_edata>
   100d4:	04079463          	bnez	a5,1011c <__do_global_dtors_aux+0x4c>
   100d8:	ffff0797          	auipc	a5,0xffff0
   100dc:	f2878793          	addi	a5,a5,-216 # 0 <register_fini-0x10074>
   100e0:	02078863          	beqz	a5,10110 <__do_global_dtors_aux+0x40>
   100e4:	ff010113          	addi	sp,sp,-16
   100e8:	00001517          	auipc	a0,0x1
   100ec:	49850513          	addi	a0,a0,1176 # 11580 <__FRAME_END__>
   100f0:	00112623          	sw	ra,12(sp)
   100f4:	00000097          	auipc	ra,0x0
   100f8:	000000e7          	jalr	zero # 0 <register_fini-0x10074>
   100fc:	00c12083          	lw	ra,12(sp)
   10100:	00100793          	li	a5,1
   10104:	c2f18a23          	sb	a5,-972(gp) # 119c4 <_edata>
   10108:	01010113          	addi	sp,sp,16
   1010c:	00008067          	ret
   10110:	00100793          	li	a5,1
   10114:	c2f18a23          	sb	a5,-972(gp) # 119c4 <_edata>
   10118:	00008067          	ret
   1011c:	00008067          	ret

00010120 <frame_dummy>:
   10120:	ffff0797          	auipc	a5,0xffff0
   10124:	ee078793          	addi	a5,a5,-288 # 0 <register_fini-0x10074>
   10128:	00078c63          	beqz	a5,10140 <frame_dummy+0x20>
   1012c:	c3818593          	addi	a1,gp,-968 # 119c8 <object.5439>
   10130:	00001517          	auipc	a0,0x1
   10134:	45050513          	addi	a0,a0,1104 # 11580 <__FRAME_END__>
   10138:	00000317          	auipc	t1,0x0
   1013c:	00000067          	jr	zero # 0 <register_fini-0x10074>
   10140:	00008067          	ret

00010144 <monitorWaterLevel>:
   10144:	0000006f          	j	10144 <monitorWaterLevel>

00010148 <main>:
   10148:	ff010113          	addi	sp,sp,-16
   1014c:	00112623          	sw	ra,12(sp)
   10150:	ff5ff0ef          	jal	ra,10144 <monitorWaterLevel>

00010154 <readWaterLevel>:
   10154:	ff010113          	addi	sp,sp,-16
   10158:	00112623          	sw	ra,12(sp)
   1015c:	fe9ff0ef          	jal	ra,10144 <monitorWaterLevel>

00010160 <atexit>:
   10160:	00050593          	mv	a1,a0
   10164:	00000693          	li	a3,0
   10168:	00000613          	li	a2,0
   1016c:	00000513          	li	a0,0
   10170:	2080006f          	j	10378 <__register_exitproc>

00010174 <exit>:
   10174:	ff010113          	addi	sp,sp,-16
   10178:	00000593          	li	a1,0
   1017c:	00812423          	sw	s0,8(sp)
   10180:	00112623          	sw	ra,12(sp)
   10184:	00050413          	mv	s0,a0
   10188:	28c000ef          	jal	ra,10414 <__call_exitprocs>
   1018c:	c2818793          	addi	a5,gp,-984 # 119b8 <_global_impure_ptr>
   10190:	0007a503          	lw	a0,0(a5)
   10194:	03c52783          	lw	a5,60(a0)
   10198:	00078463          	beqz	a5,101a0 <exit+0x2c>
   1019c:	000780e7          	jalr	a5
   101a0:	00040513          	mv	a0,s0
   101a4:	38c000ef          	jal	ra,10530 <_exit>

000101a8 <__libc_fini_array>:
   101a8:	ff010113          	addi	sp,sp,-16
   101ac:	00812423          	sw	s0,8(sp)
   101b0:	00001797          	auipc	a5,0x1
   101b4:	3dc78793          	addi	a5,a5,988 # 1158c <__init_array_end>
   101b8:	00001417          	auipc	s0,0x1
   101bc:	3d840413          	addi	s0,s0,984 # 11590 <__fini_array_end>
   101c0:	40f40433          	sub	s0,s0,a5
   101c4:	00112623          	sw	ra,12(sp)
   101c8:	00912223          	sw	s1,4(sp)
   101cc:	40245413          	srai	s0,s0,0x2
   101d0:	02040263          	beqz	s0,101f4 <__libc_fini_array+0x4c>
   101d4:	00241493          	slli	s1,s0,0x2
   101d8:	ffc48493          	addi	s1,s1,-4
   101dc:	00f484b3          	add	s1,s1,a5
   101e0:	0004a783          	lw	a5,0(s1)
   101e4:	fff40413          	addi	s0,s0,-1
   101e8:	ffc48493          	addi	s1,s1,-4
   101ec:	000780e7          	jalr	a5
   101f0:	fe0418e3          	bnez	s0,101e0 <__libc_fini_array+0x38>
   101f4:	00c12083          	lw	ra,12(sp)
   101f8:	00812403          	lw	s0,8(sp)
   101fc:	00412483          	lw	s1,4(sp)
   10200:	01010113          	addi	sp,sp,16
   10204:	00008067          	ret

00010208 <__libc_init_array>:
   10208:	ff010113          	addi	sp,sp,-16
   1020c:	00812423          	sw	s0,8(sp)
   10210:	01212023          	sw	s2,0(sp)
   10214:	00001417          	auipc	s0,0x1
   10218:	37040413          	addi	s0,s0,880 # 11584 <__init_array_start>
   1021c:	00001917          	auipc	s2,0x1
   10220:	36890913          	addi	s2,s2,872 # 11584 <__init_array_start>
   10224:	40890933          	sub	s2,s2,s0
   10228:	00112623          	sw	ra,12(sp)
   1022c:	00912223          	sw	s1,4(sp)
   10230:	40295913          	srai	s2,s2,0x2
   10234:	00090e63          	beqz	s2,10250 <__libc_init_array+0x48>
   10238:	00000493          	li	s1,0
   1023c:	00042783          	lw	a5,0(s0)
   10240:	00148493          	addi	s1,s1,1
   10244:	00440413          	addi	s0,s0,4
   10248:	000780e7          	jalr	a5
   1024c:	fe9918e3          	bne	s2,s1,1023c <__libc_init_array+0x34>
   10250:	00001417          	auipc	s0,0x1
   10254:	33440413          	addi	s0,s0,820 # 11584 <__init_array_start>
   10258:	00001917          	auipc	s2,0x1
   1025c:	33490913          	addi	s2,s2,820 # 1158c <__init_array_end>
   10260:	40890933          	sub	s2,s2,s0
   10264:	40295913          	srai	s2,s2,0x2
   10268:	00090e63          	beqz	s2,10284 <__libc_init_array+0x7c>
   1026c:	00000493          	li	s1,0
   10270:	00042783          	lw	a5,0(s0)
   10274:	00148493          	addi	s1,s1,1
   10278:	00440413          	addi	s0,s0,4
   1027c:	000780e7          	jalr	a5
   10280:	fe9918e3          	bne	s2,s1,10270 <__libc_init_array+0x68>
   10284:	00c12083          	lw	ra,12(sp)
   10288:	00812403          	lw	s0,8(sp)
   1028c:	00412483          	lw	s1,4(sp)
   10290:	00012903          	lw	s2,0(sp)
   10294:	01010113          	addi	sp,sp,16
   10298:	00008067          	ret

0001029c <memset>:
   1029c:	00f00313          	li	t1,15
   102a0:	00050713          	mv	a4,a0
   102a4:	02c37e63          	bgeu	t1,a2,102e0 <memset+0x44>
   102a8:	00f77793          	andi	a5,a4,15
   102ac:	0a079063          	bnez	a5,1034c <memset+0xb0>
   102b0:	08059263          	bnez	a1,10334 <memset+0x98>
   102b4:	ff067693          	andi	a3,a2,-16
   102b8:	00f67613          	andi	a2,a2,15
   102bc:	00e686b3          	add	a3,a3,a4
   102c0:	00b72023          	sw	a1,0(a4)
   102c4:	00b72223          	sw	a1,4(a4)
   102c8:	00b72423          	sw	a1,8(a4)
   102cc:	00b72623          	sw	a1,12(a4)
   102d0:	01070713          	addi	a4,a4,16
   102d4:	fed766e3          	bltu	a4,a3,102c0 <memset+0x24>
   102d8:	00061463          	bnez	a2,102e0 <memset+0x44>
   102dc:	00008067          	ret
   102e0:	40c306b3          	sub	a3,t1,a2
   102e4:	00269693          	slli	a3,a3,0x2
   102e8:	00000297          	auipc	t0,0x0
   102ec:	005686b3          	add	a3,a3,t0
   102f0:	00c68067          	jr	12(a3)
   102f4:	00b70723          	sb	a1,14(a4)
   102f8:	00b706a3          	sb	a1,13(a4)
   102fc:	00b70623          	sb	a1,12(a4)
   10300:	00b705a3          	sb	a1,11(a4)
   10304:	00b70523          	sb	a1,10(a4)
   10308:	00b704a3          	sb	a1,9(a4)
   1030c:	00b70423          	sb	a1,8(a4)
   10310:	00b703a3          	sb	a1,7(a4)
   10314:	00b70323          	sb	a1,6(a4)
   10318:	00b702a3          	sb	a1,5(a4)
   1031c:	00b70223          	sb	a1,4(a4)
   10320:	00b701a3          	sb	a1,3(a4)
   10324:	00b70123          	sb	a1,2(a4)
   10328:	00b700a3          	sb	a1,1(a4)
   1032c:	00b70023          	sb	a1,0(a4)
   10330:	00008067          	ret
   10334:	0ff5f593          	andi	a1,a1,255
   10338:	00859693          	slli	a3,a1,0x8
   1033c:	00d5e5b3          	or	a1,a1,a3
   10340:	01059693          	slli	a3,a1,0x10
   10344:	00d5e5b3          	or	a1,a1,a3
   10348:	f6dff06f          	j	102b4 <memset+0x18>
   1034c:	00279693          	slli	a3,a5,0x2
   10350:	00000297          	auipc	t0,0x0
   10354:	005686b3          	add	a3,a3,t0
   10358:	00008293          	mv	t0,ra
   1035c:	fa0680e7          	jalr	-96(a3)
   10360:	00028093          	mv	ra,t0
   10364:	ff078793          	addi	a5,a5,-16
   10368:	40f70733          	sub	a4,a4,a5
   1036c:	00f60633          	add	a2,a2,a5
   10370:	f6c378e3          	bgeu	t1,a2,102e0 <memset+0x44>
   10374:	f3dff06f          	j	102b0 <memset+0x14>

00010378 <__register_exitproc>:
   10378:	c2818793          	addi	a5,gp,-984 # 119b8 <_global_impure_ptr>
   1037c:	0007a703          	lw	a4,0(a5)
   10380:	14872783          	lw	a5,328(a4)
   10384:	04078c63          	beqz	a5,103dc <__register_exitproc+0x64>
   10388:	0047a703          	lw	a4,4(a5)
   1038c:	01f00813          	li	a6,31
   10390:	06e84e63          	blt	a6,a4,1040c <__register_exitproc+0x94>
   10394:	00271813          	slli	a6,a4,0x2
   10398:	02050663          	beqz	a0,103c4 <__register_exitproc+0x4c>
   1039c:	01078333          	add	t1,a5,a6
   103a0:	08c32423          	sw	a2,136(t1) # 101c0 <__libc_fini_array+0x18>
   103a4:	1887a883          	lw	a7,392(a5)
   103a8:	00100613          	li	a2,1
   103ac:	00e61633          	sll	a2,a2,a4
   103b0:	00c8e8b3          	or	a7,a7,a2
   103b4:	1917a423          	sw	a7,392(a5)
   103b8:	10d32423          	sw	a3,264(t1)
   103bc:	00200693          	li	a3,2
   103c0:	02d50463          	beq	a0,a3,103e8 <__register_exitproc+0x70>
   103c4:	00170713          	addi	a4,a4,1
   103c8:	00e7a223          	sw	a4,4(a5)
   103cc:	010787b3          	add	a5,a5,a6
   103d0:	00b7a423          	sw	a1,8(a5)
   103d4:	00000513          	li	a0,0
   103d8:	00008067          	ret
   103dc:	14c70793          	addi	a5,a4,332
   103e0:	14f72423          	sw	a5,328(a4)
   103e4:	fa5ff06f          	j	10388 <__register_exitproc+0x10>
   103e8:	18c7a683          	lw	a3,396(a5)
   103ec:	00170713          	addi	a4,a4,1
   103f0:	00e7a223          	sw	a4,4(a5)
   103f4:	00c6e633          	or	a2,a3,a2
   103f8:	18c7a623          	sw	a2,396(a5)
   103fc:	010787b3          	add	a5,a5,a6
   10400:	00b7a423          	sw	a1,8(a5)
   10404:	00000513          	li	a0,0
   10408:	00008067          	ret
   1040c:	fff00513          	li	a0,-1
   10410:	00008067          	ret

00010414 <__call_exitprocs>:
   10414:	fd010113          	addi	sp,sp,-48
   10418:	c2818793          	addi	a5,gp,-984 # 119b8 <_global_impure_ptr>
   1041c:	01812423          	sw	s8,8(sp)
   10420:	0007ac03          	lw	s8,0(a5)
   10424:	01312e23          	sw	s3,28(sp)
   10428:	01412c23          	sw	s4,24(sp)
   1042c:	01512a23          	sw	s5,20(sp)
   10430:	01612823          	sw	s6,16(sp)
   10434:	02112623          	sw	ra,44(sp)
   10438:	02812423          	sw	s0,40(sp)
   1043c:	02912223          	sw	s1,36(sp)
   10440:	03212023          	sw	s2,32(sp)
   10444:	01712623          	sw	s7,12(sp)
   10448:	00050a93          	mv	s5,a0
   1044c:	00058b13          	mv	s6,a1
   10450:	00100a13          	li	s4,1
   10454:	fff00993          	li	s3,-1
   10458:	148c2903          	lw	s2,328(s8)
   1045c:	02090863          	beqz	s2,1048c <__call_exitprocs+0x78>
   10460:	00492483          	lw	s1,4(s2)
   10464:	fff48413          	addi	s0,s1,-1
   10468:	02044263          	bltz	s0,1048c <__call_exitprocs+0x78>
   1046c:	00249493          	slli	s1,s1,0x2
   10470:	009904b3          	add	s1,s2,s1
   10474:	040b0463          	beqz	s6,104bc <__call_exitprocs+0xa8>
   10478:	1044a783          	lw	a5,260(s1)
   1047c:	05678063          	beq	a5,s6,104bc <__call_exitprocs+0xa8>
   10480:	fff40413          	addi	s0,s0,-1
   10484:	ffc48493          	addi	s1,s1,-4
   10488:	ff3416e3          	bne	s0,s3,10474 <__call_exitprocs+0x60>
   1048c:	02c12083          	lw	ra,44(sp)
   10490:	02812403          	lw	s0,40(sp)
   10494:	02412483          	lw	s1,36(sp)
   10498:	02012903          	lw	s2,32(sp)
   1049c:	01c12983          	lw	s3,28(sp)
   104a0:	01812a03          	lw	s4,24(sp)
   104a4:	01412a83          	lw	s5,20(sp)
   104a8:	01012b03          	lw	s6,16(sp)
   104ac:	00c12b83          	lw	s7,12(sp)
   104b0:	00812c03          	lw	s8,8(sp)
   104b4:	03010113          	addi	sp,sp,48
   104b8:	00008067          	ret
   104bc:	00492783          	lw	a5,4(s2)
   104c0:	0044a683          	lw	a3,4(s1)
   104c4:	fff78793          	addi	a5,a5,-1
   104c8:	04878a63          	beq	a5,s0,1051c <__call_exitprocs+0x108>
   104cc:	0004a223          	sw	zero,4(s1)
   104d0:	fa0688e3          	beqz	a3,10480 <__call_exitprocs+0x6c>
   104d4:	18892783          	lw	a5,392(s2)
   104d8:	008a1733          	sll	a4,s4,s0
   104dc:	00492b83          	lw	s7,4(s2)
   104e0:	00f777b3          	and	a5,a4,a5
   104e4:	00079e63          	bnez	a5,10500 <__call_exitprocs+0xec>
   104e8:	000680e7          	jalr	a3
   104ec:	00492783          	lw	a5,4(s2)
   104f0:	f77794e3          	bne	a5,s7,10458 <__call_exitprocs+0x44>
   104f4:	148c2783          	lw	a5,328(s8)
   104f8:	f92784e3          	beq	a5,s2,10480 <__call_exitprocs+0x6c>
   104fc:	f5dff06f          	j	10458 <__call_exitprocs+0x44>
   10500:	18c92783          	lw	a5,396(s2)
   10504:	0844a583          	lw	a1,132(s1)
   10508:	00f77733          	and	a4,a4,a5
   1050c:	00071c63          	bnez	a4,10524 <__call_exitprocs+0x110>
   10510:	000a8513          	mv	a0,s5
   10514:	000680e7          	jalr	a3
   10518:	fd5ff06f          	j	104ec <__call_exitprocs+0xd8>
   1051c:	00892223          	sw	s0,4(s2)
   10520:	fb1ff06f          	j	104d0 <__call_exitprocs+0xbc>
   10524:	00058513          	mv	a0,a1
   10528:	000680e7          	jalr	a3
   1052c:	fc1ff06f          	j	104ec <__call_exitprocs+0xd8>

00010530 <_exit>:
   10530:	00000593          	li	a1,0
   10534:	00000613          	li	a2,0
   10538:	00000693          	li	a3,0
   1053c:	00000713          	li	a4,0
   10540:	00000793          	li	a5,0
   10544:	05d00893          	li	a7,93
   10548:	00000073          	ecall
   1054c:	00054463          	bltz	a0,10554 <_exit+0x24>
   10550:	0000006f          	j	10550 <_exit+0x20>
   10554:	ff010113          	addi	sp,sp,-16
   10558:	00812423          	sw	s0,8(sp)
   1055c:	00050413          	mv	s0,a0
   10560:	00112623          	sw	ra,12(sp)
   10564:	40800433          	neg	s0,s0
   10568:	00c000ef          	jal	ra,10574 <__errno>
   1056c:	00852023          	sw	s0,0(a0)
   10570:	0000006f          	j	10570 <_exit+0x40>

00010574 <__errno>:
   10574:	c3018793          	addi	a5,gp,-976 # 119c0 <_impure_ptr>
   10578:	0007a503          	lw	a0,0(a5)
   1057c:	00008067          	ret

```
My assembly code contains instructions like addi, srai, sw, and so on. Running the sample.py on this water_level_assembly.txt would yield:

```
Number of different instructions: 35
List of unique instructions:
beq
lw
mv
addiw
add
bgeu
or
ecall
j
jal
sllw
beqz
ld
srai
sd
auipc
bne
bltz
negw
lbu
sext.w
bltu
jr
sw
sub
li
jalr
sb
and
slli
bnez
addi
andi
blt
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
  
## Reference 


- https://github.com/The-OpenROAD-Project/OpenSTA.git
- https://github.com/kunalg123
- https://www.vsdiat.com
- https://github.com/SakethGajawada/RISCV-GNU

.text
.global _start
.global INT_DIRECTOR
_start:
		
		LDR R13,=STACK1 		@ Point to base of STACK for SVC mode
		ADD R13, R13,#0x1000		@ Point to top of STACK
		CPS #0x12			@ Switch to IRQ mode
		LDR R13,=STACK2			@ Point to IRQ stack
		ADD R13, R13,#0x1000		@ Point to top of STACK
		CPS #0x13 			@ Back to SVC mode
		
		LDR R0,=#0x02			@ Value to enable clock for a GPIO module
		LDR R1 ,=0x44E000AC		@ Address o f CM_PER_GP!01_CLKCTRL Register
		STR R0, [R1]			@ Write #02 to 
			
		LDR R0,=0x4804C000		@ Base address for GPIOl registers
		ADD R4, R0,#0x190		@ Address of GPI01_CLEARDATAOUT register
		MOV R7, #0x01E00000		@ Load value to turn off LED on GPI01_21-24
		STR R7,[R4]			@ Write to GPI01_CLEARDATAOUT register
					
		ADD R1,R0,#0x0134		@ Make GPI01_0E register address
		LDR R6,[R1]			@ READ current GPIOl Output Enable register
		LDR R7,=0xFE1FFFFF		@ Word to enable GPI01_21-24 as outputs (0 enables)
		AND R6,R7,R6			@ Clear bit 12 (MODIFY)
		STR R6, [R1]			@ WRITE to GPIOl Output Enable register
		
		ADD R1, R0, #0x14C		@ R1 = address of GPIO1_FALLINGDETECT register
		MOV R2, #0x00004000		@ LOAD VALUE FOR BIT 14
		LDR R3, [R1] 			@ READ GPI01_FALLINGDETECT register
		ORR R3, R3, R2			@ Modify (set bit 14) 
		STR R3, [R1]			@ Write back
		ADD R1, R0, #0x34		@ Address of GPIO1_IRQSTATUS_SET_0 register
		STR R2, [R1]			@ Enable GPI01_14 request on POINTRPENDl
			
		LDR R1,= 0x482000E8		@ Address of INTC_MIR_CLEAR3 register
		MOV R2,#0x04			@ Value to unmask INTC INT 98, GPI0INT1A
		STR R2,[R1]			@ Write to INTC_MIR_CLEAR3 register
			
		MRS R3, CPSR			@ Copy CPSR to R3
		BIC R3,#0x80			@ Clear bit 7
		MSR CPSR_c, R3			@ Write back to CPSR
			
		
LOOP: NOP						
	BL POLL						@ Poll the flag
	
	@ Turn on LED0&LED1 (GPI01_22,23)
	MOV R4, #0x00600000			
	BL LED		
	@ Turn off					
	MOV R4, #0x00000000			
	BL LED
	@-------------------------------
		
    
	@ Turn on LED1&LED2 (GPI01_23,24)
	MOV R4, #0x00C00000			
	BL LED						
	@ Turn off					
	MOV R4, #0x00000000			
	BL LED	
    @-------------------------------
    
    
	@ Turn on LED2&LED3 (GPI01_21,22)
	MOV R4, #0x01800000			
	BL LED						
	@ Turn off 	
	MOV R4, #0x00000000			
	BL LED
	@-------------------------------
		
    
	B LOOP
		
	LED:
		STMFD SP!, {R0-R3, LR}	@ Save used registers on the stack
		BL POLL					@ Poll the flag
		LDR R1, =0x4804C194		@ Load address of GPIO1_SETDATAOUT register
		STR R4, [R1]			@ Write to GPI01_SETDATAOUT register
		LDR R2,=0x00100000		@ Load delay for 1 second
	DELAY:
		SUBS R2,#1				@ Delay for 1 second 
		BNE DELAY 				@ Delay for 1 second
		
		BL POLL					@ Poll the flag again
		LDR R1,=0x4804C190		@ Load GPIO1_CLEARDATA
		STR R4, [R1]			@ Write to GPIO1_CLEARDATA register
		LDMFD SP!, {R0-R3, PC}	@ Restore saved registers and return from procedure
		

POLL:	STMFD SP!, {R0-R3, LR}	@ Save used registers on the stack
LOOP2:	NOP
		LDR R3, =FLAG			@ Load flag address
		LDR R2, [R3]			@ Load flag value
		TST R2, #0x1			@ Check if flag is set
		BEQ LOOP2				@ If not, repeat
		LDMFD SP!, {R0-R3, PC}	@ Restore saved registers and return from procedure
		
		
INT_DIRECTOR:
		STMFD SP!, {R0-R3, LR}		@ Push registers on stack
		LDR R0,=0x482000F8			@ Address of INTC-PENDING_IRQ3 register
		LDR R1,[R0]					@ Read INTC-PENDING_IRQ3 register
		TST R1,#0x00000004			@ TEST BIT 2
		BEQ PASS_ON					@ Not from GPIOINT1A, go to back to wait loop, Else
		LDR R0, =0x4804C02C			@ Load GPIO1_IRQSTATUS_0 register address
		LDR R1, [R0]				@ Read STATUS register
		TST R1,#0x00004000			@ Check if bit 14 =1
		BNE BUTTON_SVC				@ If bit 14 =1, then button pushed
		BEQ PASS_ON					@ If bit 14 =0, then go to back to wait loop
		
PASS_ON:
		LDMFD SP!, {R0-R3,LR}		@ Restore registers
		SUBS PC, LR, #4				@ Pass execution on to wait LOOP for now
		
BUTTON_SVC:
		MOV R1,#0x00004000			@ Value turns off GPI01_14 Interrupt request
		STR R1,[R0]					@ Write to GPIO1_IRQSTATUS_0 register
		
		LDR R0,=0x48200048			@ Address of INTC__CONTROL register
		MOV R1, #01					@ Value to clear bit 0
		STR R1,[R0]					@ Write to INTC__CONTROL register
		
		LDR R0,=0x4804C194			@ Load address of GPI01_SETDATA0UT register
		MOV R1,#0x00001000			@ Load value to turn on GPI01_12
		STR R1,[R0]					@ Write to GPI01_SETDATA0UT register
		
		LDR R3, =FLAG				@ Load flag address
		LDR R2, [R3]				@ Load flag value
		TST R2, #0x1				@ Check flag value
		MOVEQ R2, #0x1				@ Flip flag
		MOVNE R2, #0x0				@ Flip flag
		STR R2, [R3]				@ Store flipped flag value

		LDR R0,=0x4804C190			@ Load address of GP101_CLEARDATAOUT register
		STR R1, [R0]				@ Write 0x00001000 to GPI01_CLEARDATA0UT register

		LDMFD SP!, {R0-R3,LR}		@ Restore registers
		SUBS PC, LR, #4				@ Return from IRQ interrupt procedure
		
.align 2
SYS_IRQ:	 .WORD 0				@ Location to store systems IRQ address
.data
.align 2
STACK1:		.rept 1024
			.word 0x0000
			.endr
STACK2:		.rept 1024
			.word 0x0000
			.endr
.align 2
FLAG:		.byte 0x1

.END

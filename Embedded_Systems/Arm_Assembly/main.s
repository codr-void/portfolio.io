.text
.global _start
.global INTERRUPT_HANDLER
_start:
.equ CONSTANT_NUMBER, 15000

		LDR R13,=STACK1 		// Load base address of SVC mode stack into R13
		ADD R13, R13,#0x1000	// Adjust R13 to point to the top of the stack
		CPS #0x12				// Switch to IRQ mode
		LDR R13,=STACK2			// Load base address of IRQ stack into R13
		ADD R13, R13,#0x1000	// Adjust R13 to point to the top of the IRQ stack
		CPS #0x13 				// Switch back to SVC mode
		
		LDR R0,=#0x02			// Load the enable value for a GPIO module clock
		LDR R1 ,=0x44E000AC		// Load address of the CM_PER_GPIO1_CLKCTRL register
		STR R0, [R1]			// Write enable value to the clock control register
			
		LDR R0,=0x4804C000		// Base address of GPIO1
		ADD R4, R0,#0x190		// Address of GPIO1_CLEARDATAOUT register
		MOV R7, #0x01E00000		// Value to turn off LEDs connected to GPIO1_21 to GPIO1_24
		STR R7,[R4]				// Clear data out register, turning off the LEDs
					
		ADD R1,R0,#0x0134		// Address of GPIO1 output enable register
		LDR R6,[R1]				// Read current value of output enable register
		LDR R7,=0xFE1FFFFF		// Mask to set GPIO1_21 to GPIO1_24 as outputs
		AND R6,R7,R6			// Modify output enable register to set specified GPIO pins as outputs
		STR R6, [R1]			// Write new value back to output enable register
		
		ADD R1, R0, #0x14C		// Address of GPIO1_FALLINGDETECT register
		MOV R2, #0x00004000		// Value to enable falling edge detection for GPIO1_14
		LDR R3, [R1] 			// Read current falling edge detection settings
		ORR R3, R3, R2			// Set the falling edge detection for GPIO1_14
		STR R3, [R1]			// Write updated settings back
		ADD R1, R0, #0x34		// Address of GPIO1_IRQSTATUS_SET_0 register
		STR R2, [R1]			// Enable interrupt request for GPIO1_14
		
		LDR R1,= 0x482000E8		// Address of INTC_MIR_CLEAR3 register
		MOV R2,#0x04			// Value to unmask interrupt 98 (GPIOINT1A)
		STR R2,[R1]				// Unmask the interrupt in the interrupt controller
			
		MRS R3, CPSR			// Copy current program status register to R3
		BIC R3,#0x80			// Clear bit 7 to enable IRQs
		MSR CPSR_c, R3			// Update CPSR with the new value
		
LOOP: NOP						// No operation, placeholder for loop start
		BL POLL					// Call the poll function to check for flag status
		MOV R4, #0x00600000		// Load value to set GPIO1_22 and GPIO1_23 to high
		BL LED					// Call LED subroutine to update LEDs
		MOV R4, #0x01800000		// Load value to set GPIO1_23 and GPIO1_24 to high
		BL LED					// Call LED subroutine to update LEDs
		MOV R4, #0x00C00000		// Load value to set GPIO1_21 and GPIO1_22 to high
		BL LED					// Call LED subroutine to update LEDs
		B LOOP					// Jump back to start of loop
		
	LED:
		STMFD SP!, {R0-R3, LR}	// Save R0-R3 and LR on stack
		BL POLL					// Call poll function
		LDR R1, =0x4804C194		// Address of GPIO1_SETDATAOUT register
		STR R4, [R1]			// Set data out register, turning on specified LEDs
		LDR R2,=0x00200000		// Load delay value for approx. 1 second
	DELAY:
		SUBS R2,#1				// Decrement delay counter
		BNE DELAY 				// Continue delay loop if counter not zero
		BL POLL					// Poll the flag again
		LDR R1,=0x4804C190		// Address of GPIO1_CLEARDATAOUT register
		STR R4, [R1]			// Clear specified bits, turning off LEDs
		LDMFD SP!, {R0-R3, PC}	// Restore R0-R3, PC from stack, return from subroutine
		

POLL:	STMFD SP!, {R0-R3, LR}	// Save R0-R3, LR on stack
LOOP2:	NOP
		LDR R3, =FLAG			// Load address of the flag variable
		LDR R2, [R3]			// Read flag value
		TST R2, #0x1			// Test if flag is set (bit 0)
		BEQ LOOP2				// If flag not set, loop
		LDMFD SP!, {R0-R3, PC}	// Restore registers, return from subroutine
		
INTERRUPT_HANDLER:
		STMFD SP!, {R0-R3, LR}		// Save registers on stack
		LDR R0,=0x482000F8			// Address of INTC_PENDING_IRQ3 register
		LDR R1,[R0]					// Read IRQ pending register
		TST R1,#0x00000004			// Check if interrupt from GPIOINT1A (bit 2)
		BEQ PASS_ON				// If not, skip handling
		LDR R0, =0x4804C02C			// Address of GPIO1_IRQSTATUS_0 register
		LDR R1, [R0]				// Read interrupt status
		TST R1,#0x00004000			// Check if GPIO1_14 triggered the interrupt
		BNE BUTTON_SVC				// If yes, handle button service
		BEQ PASS_ON				// If no, pass on
		
PASS_ON:
		LDMFD SP!, {R0-R3,LR}		// Restore registers
		SUBS PC, LR, #4				// Return to previous state
		
BUTTON_SVC:
		MOV R1,#0x00004000			// Mask to clear interrupt for GPIO1_14
		STR R1,[R0]					// Clear interrupt status
		LDR R0,=0x48200048			// Address of INTC_CONTROL register
		MOV R1, #01					// Value to acknowledge interrupt
		STR R1,[R0]					// Write to control register to acknowledge
		LDR R0,=0x4804C194			// Address of GPIO1_SETDATAOUT register
		MOV R1,#0x00001000			// Value to turn on LED connected to GPIO1_12
		STR R1,[R0]					// Write to set data out register, turning on LED
		LDR R3, =FLAG				// Load address of the flag variable
		LDR R2, [R3]				// Read current flag value
		TST R2, #0x1				// Test flag
		MOVEQ R2, #0x1				// If flag is 0, set to 1
		MOVNE R2, #0x0				// If flag is 1, set to 0
		STR R2, [R3]				// Update flag value
		LDR R0,=0x4804C190			// Address of GPIO1_CLEARDATAOUT register
		STR R1, [R0]				// Clear data out register, turning off LED
		LDMFD SP!, {R0-R3,LR}		// Restore registers
		SUBS PC, LR, #4				// Return from interrupt handler
.align 2
SYS_IRQ:	 .WORD 0				// Reserve word for system IRQ address
.data
.align 2
STACK1:		.rept 1024
			.word 0x0000
			.endr
STACK2:		.rept 1024
			.word 0x0000
			.endr
.align 2
FLAG:		.byte 0x1				// Initialize flag variable with value 1

.END

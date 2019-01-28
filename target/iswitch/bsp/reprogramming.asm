; -----------------------------------------------------------------------------------------
; Execute SPM instruction (FLASH erase, buffer fill, page write...)
; param		r13:r12		FLASH address
; param		r15:r14		word to be written to r1:r0
; param		r9			SPMSCR content
; -----------------------------------------------------------------------------------------
execute_spm:
			movw	zl, r12		; setup the FLASH address in the Z-pointer
			movw	r0, r14		; setup the data to be written to r1:r0
			out		spmcsr, r9
			spm
			ret

; -----------------------------------------------------------------------------------------
; Enter programming mode 
; -----------------------------------------------------------------------------------------
enter_reprogramming_mode:			
			; enable only interrupt from CAN controller and disable all other interrupts
			; (NB! assume nobody else uses this Pin Change interrupt!)
			ldi		r16, (1<<CAN_PCICR_BIT)
			sts		pcicr, r16	

			ldi		r16, 0
			out		eimsk, r16	; disable external interrupts
			sts		timsk0, r16 ; disable interrupts from timer 0
			sts		timsk1, r16 ; disable interrupts from timer 0
			sts		timsk2, r16 ; disable interrupts from timer 0
			; TODO: if watchdog is enabled, take care of it
			; TODO: SPI interrupt not affected (we use SPI to communicate with CAN controller)
			; TODO: UART/ADC/EE/ANA/TWI/SPM interrupt not affected (we don't use all this)
			; TODO: 
			ret

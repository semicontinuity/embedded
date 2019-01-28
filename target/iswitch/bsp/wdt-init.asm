; DO NOT CHANGE THIS FILE
; IT HAS TO BE exactly 6 words long!

			; Set the watchdog timeout to 8 seconds
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~			
			; Must be done ASAP because on power-up the timer might be set to 16msec by default
			; NB if WDTON fuse is programmed, watchdog is always enabled.
						
			; Writing 1s to WDE and WDCE enables changes for next 4 cycles
			ldi		r16, (1<<WDCE)|(1<<WDE)	
			sts		WDTCSR, r16
			; WDCE must be 0 (as per spec). WDP=1001 means 1024K cycles, ~8sec.
			ldi		r16, (0<<WDCE)|(1<<WDE)|(1<<WDP3)|(0<<WDP2)|(0<<WDP1)|(1<<WDP0)
			sts		WDTCSR, r16
			; ~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~

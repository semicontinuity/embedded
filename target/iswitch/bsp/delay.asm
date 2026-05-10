; -----------------------------------------------------------------------------------------
delay:

; Delay ~1 sec
; NB: count1, count 2 are not initialized => delay is only approximate
.def		count1	= r16
.def		count2	= r17
.def		count3	= r18
; -----------------------------------------------------------------------------------------
			ldi		count3,2	; см. на формирование задержки
_wait:
			dec		count1
			brne	_wait		; это даст 256*3 такта = 96 мкс паузу. маловато!
			dec		count2
			brne	_wait		; грубо это умножит на 256, 25 мс - тоже мало...
								; нам бы 0,4сек=100 мс - еще на 16 умножить.
			dec		count3
			brne	_wait
			ret

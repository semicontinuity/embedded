; -----------------------------------------------------------------------------------------
delay:

; Delay ~1 sec
; NB: count1, count 2 are not initialized => delay is only approximate
.def		count1	= r16
.def		count2	= r17
.def		count3	= r18
; -----------------------------------------------------------------------------------------
			ldi		count3,2	; ��. �� ������������ ��������
_wait:
			dec		count1
			brne	_wait		; ��� ���� 256*3 ����� = 96 ��� �����. ��������!
			dec		count2
			brne	_wait		; ����� ��� ������� �� 256, 25 �� - ���� ����...
								; ��� �� 0,4���=100 �� - ��� �� 16 ��������.
			dec		count3
			brne	_wait
			ret

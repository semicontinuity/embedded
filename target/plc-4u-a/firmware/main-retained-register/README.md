# Water leakage control module firmware

#### I/O allocation for Arduino Nano V3

```
PB0     IN      IN6 (Valve limit switch C) >>> OUT     EXTRA_OUTPUT__A
PB1     IN      IN7 (Valve limit switch D) >>> OUT     EXTRA_OUTPUT__B
PB2     IN      IN8 (Extra Input A)
PB3     IN      IN9 (Extra Input B)
PB4     OUT     BUTTON_LED__E (Contactor)
PB5     OUT     BUTTON_LED__F (Failure) (On-Board LED); Buzzer

PC0     IN      INA (Button A)
PC1     IN      INB (Button B)
PC2     IN      INC (Button C) >>> OUT     BUTTON_LED__A, BUTTON_LED__C
PC3     IN      IND (Button D) >>> OUT     BUTTON_LED__B, BUTTON_LED__D
PC4     IN      INE (Button E)
PC5     IN      INF (Button F)

PD0
PD1
PD2     IN      IN0 (Water leak sensor A)
PD3     IN      IN1 (Water leak sensor B)
PD4     IN      IN2 (Water leak sensor C) >>> OUT     VALVE_CONTROL__A__PWR, VALVE_CONTROL__B__PWR,
PD5     IN      IN3 (Water leak sensor D) >>> OUT     VALVE_CONTROL__A__DIR, VALVE_CONTROL__B__DIR
PD6     IN      IN4 (Valve limit switch A)
PD7     IN      IN5 (Valve limit switch B)

```


#### Controlling long-running processes

* Coil for starting/stopping a process: PROCESS__REQUEST
  * Write 1 to start long-running process
  * Write 0 to cancel long-running process, if it is running
  * Coil is reset to 0 when the process has finished
* Coil, indicating that the process is running: PROCESS__RUNNING
  * User should not write to the coil
  * If the process was requested to start, the coil becomes 1, when the process has been orderly started
  * If the process has orderly finished, the coil becomes 0
* Coil, indicating the result of the process: PROCESS__FAILURE

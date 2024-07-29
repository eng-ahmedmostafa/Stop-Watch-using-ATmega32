# Stop-Watch-using-ATmega32
Designed and implemented a Stop Watch system using an ATmega32 microcontroller operating at 1MHz. Configured Timer1 in CTC mode for precise time counting. Utilized six common anode 7-segment displays connected through multiplexing with a 7447 decoder and controlled via NPN BJT transistors linked to the microcontroller pins. The 7447 decoder was connected to PORTC, while PORTA managed the enable/disable functionality of each 7-segment.

Stopwatch functionalities included:

Counting Start: Automatic start upon power connection to the MCU.
Reset: Configured External Interrupt INT0 with a falling edge to reset time, using an internal pull-up resistor push button.
Pause: Configured External Interrupt INT1 with a rising edge to pause time, using an external pull-down resistor push button.
Resume: Configured External Interrupt INT2 with a falling edge to resume time, using an internal pull-up resistor push button.
![image](https://github.com/user-attachments/assets/458272d5-10e1-4ec5-985b-56dfa46d9728)

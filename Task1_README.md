# R3_SoftwareTask1_Nidhish_Subramanian
Task 1.

------------------------------------------------------------

To simulate the circuit shown in kieran_diagram.JPG
Please visit :  https://www.tinkercad.com/things/6UqNCWUMi81 

------------------------------------------------------------

Wiring guide for circuit.

Red: 5V supply.

Black: Ground.

Pink and Purple: BCD input.

Yellow: Topside input from BCD to 7-segment display.

Green: Bottomside input from BCD to 7-segment display.

------------------------------------------------------------

Components list.

2x 220 Ohms resistors.

2x 1K Ohms resistors.

2x CD4511 display driver chip.

2x 7-segment displays.

1x 10K potentiometer.

1x 830 tie points breadboard.

Jumper wires.

1x Arduino Uno R3.

USB cable.

------------------------------------------------------------

Code guide.

- Map potentiometer input value range to 7-segment display output value range. 0-1023 to 0-99.

- Use formula - Resultant value = Potentiometer input reading x (maximum output limit/maximum input limit).

- Resultant value = Potentiometer input reading x (99/1023).

- Shed decimals in resultant value by converting from double to integer.

- Pass resultant value through logic gate. If value is lesser than 9, use only display 1. If not, use display 2 as well.

- Take 55 for example. 55 is greater than 9. So both displays are required.

- Divide 55 by 10. Pass remainder to display 1. Pass quotient to display 2.

- If number changes to 56, only display 1 is updated. 

- Number changes to 7. Condition 1 is validated and integer is less than 9. Send number directly to display 1. Set display 2 to 0.


A deeper look.

- When value is sent to display 1 or 2, it is made to pass through a display function.

- Take 7 for example. 7 is passed to display 1 based on the conditional logic described above. Display 1 is controlled by display function 1.

- 7 is 1110 in binary. Display function 1 converts 7 to binary. BCD has 4 input lines connected to 4 digital pins on board. 

- Display function tells the board which pins to route voltage to. Input lines on BCD are energized accordingly. 

- BCD then converts and routes voltage to its output pins ranging from A-G. 

- Output pins A-G are connected to input pins A-G on 7-segment display.

- Based on that, certain LEDs are either turned on or off. 

An even deeper look.

- When 7 is passed to display function 1, it is divided by 2.

- A  quotient and remainder is acquired.

- If a remainder is present, the first bit in a boolean array is set to 1 --> {1,0,0,0}. Array was originally --> {0,0,0,0}.

- The quotient is 3. 3 (or any input value) is divided again and again till a quotient of 0 remains.

- The divisions are performed through a loop. So based on when a remainder is acquired, an element on the boolean array is altered. 

- 3 is acquired at second pass. So element 2 is now set to 1. Array --> {1,1,0,0}.

- Once 1 is divided by 2, we get a quotient of 0. The pass during which this occurs is accounted for and the element on the array is changed accordingly.

- Array is now --> {1,1,1,0}.

Final step.

- Input pin 1 on BCD is set to element 1. Pin 2 to element 2, etc.

- Voltage is routed to the input pins based on the array.

- Pins 1, 2, and 3 recieve 5 Volts. Pin 4 is set to 0. 

- We see the number 7 on display 1.

- Exact same logic applies when sending a number to display 2. We only have to work with numbers ranging from 0-9. So none of the conditions or rules are violated.

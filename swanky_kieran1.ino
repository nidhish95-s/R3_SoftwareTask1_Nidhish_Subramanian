// Initialize input lines.
int a1 = 2, b1 = 3, c1 = 4, d1 = 5;
int a2 = 8, b2 = 9, c2 = 10, d2 = 11;

// Initialize potentiometer pin and the input value variable.
int poten_in = A1;
int potenval = 0;

// Initialize display variable.
double disp_conv = 0;

void setup()
{
// Activate pins and set default display.  
  	pinMode((a1,b1,c1,d1,a2,b2,c2,d2), OUTPUT);
  	pinMode (poten_in, INPUT); 
  
// Activate serial monitor to readings.  
  	Serial.begin(9600);
}

// Input Functions declarations and definitions.
	
void display_1(int value)
{
  bool on_off[] = {0,0,0,0}; // Input array.
  for(int x = 0; x < 4;) // Input array is a 4-bit array.
  {
    if (value == 0){break;}
  	int div = value/2; // Take 7 for example.
  	int rem = value%2; // Quotient  = 3. Remainder = 1
    value = div; // To divide quotient till it's 0.
    if(rem == 0 && x == 0){on_off[0] = 0;} // This is easy to understand.
    if(rem != 0 && x>0){on_off[x] = 1;} // After first pass, the given element is set to 1 if a remainder is still present. For 7 we have {1,1,0,0} after the step below.
    if(rem != 0 && x == 0) // If we have a remainder on first pass, set first bit to 1. For 7, we have {1,0,0,0} so far.
    {
      on_off[0] = 1;
    }
    if (div == 0) // When we reach the end, add a 1 to whatever element we stop at. After the first two steps, for 7, we are now at {1,1,1,0}.
    {
      on_off[x] = 1;
      break; 
    }
    x++;
  }
  digitalWrite(a1, on_off[0]); // Send the array values to the pins.
  digitalWrite(b1, on_off[1]); // The binary number is decoded.
  digitalWrite(c1, on_off[2]); // Corresponding LEDs light up on the display.
  digitalWrite(d1, on_off[3]); // For 7, the last pin stays off according to {1,1,1,0}.
}

void display_2(int value)// Follows the exact same logic.
{
  bool on_off[] = {0,0,0,0};
  for(int x = 0; x < 4;)
  {
    if (value == 0){break;}
  	int div = value/2;
  	int rem = value%2;
    value = div;
    if(rem == 0 && x == 0){on_off[0] = 0;}
    if(rem != 0 && x>0){on_off[x] = 1;}
    if(rem != 0 && x == 0)
    {
      on_off[0] = 1;
    }
    if (div == 0)
    {
      on_off[x] = 1;
      break;
    }
    x++;
  }
  digitalWrite(a2, on_off[0]);
  digitalWrite(b2, on_off[1]);
  digitalWrite(c2, on_off[2]);
  digitalWrite(d2, on_off[3]);
}

// Output function declaration and definition.

void potentiometervalueconverter ()
{
  // What is my potentiometer saying?
  potenval = analogRead(poten_in); 
    
  // Convert potentiometer values to usable values.
  disp_conv = potenval*(99.00/1023.00); // 99/10243 = limit of display/limit of potentiometer.
  int con_val = disp_conv; // Trim the double down. Get rid of decimals.
  Serial.println(con_val); // This is just to check if we're doing okay.
  if (con_val <= 9)
  {   	
    display_1(con_val); // We only need 1 display for numbers below 10.
    display_2(0); // So set display 2 to 0.
  }
  if(con_val >= 10) // Take 55 for example.
  {
    int div = con_val/10; // 55/10 = 5.
    int rem = con_val%10; // 55%10 = 5.
    display_1(rem); // Send the remainder 5 to display 1.
    display_2(div); // Send the quotient 5 to display 2.
    delay(10); // Because it's clunky.
  }
}


// Output loop.

void loop()
{
  potentiometervalueconverter(); // Call your function.    
}
  		     
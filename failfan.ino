int NbTopsFan; 
int Calc;
 
int fan1_pin = 2;
int fan2_pin = 3;
int led_pin = 4;
int relay_pin = 5;
int buzzer_pin = 6;


typedef struct{
  char fantype;
  unsigned int fandiv;
  }fanspec;
 
//Definitions of the fans
//This is the varible used to select the fan and it's divider,
//set 1 for unipole hall effect sensor
//and 2 for bipole hall effect sensor
fanspec fanspace[3]={{0,1},{1,2},{2,8}}; char fan = 2;
 
void rpm ()
//This is the function that the interupt calls
{ NbTopsFan++; }
 
//This is the setup function where the serial port is initialised,
//and the interrupt is attached
void setup()
{ 
  pinMode(fan1_pin, INPUT);
  pinMode(fan2_pin, INPUT);
  pinMode(led_pin, OUTPUT);
  pinMode(buzzer_pin, OUTPUT);
  pinMode(relay_pin, OUTPUT);
  Serial.begin(115200);
  attachInterrupt(0, rpm, RISING);
  delay (1000);
}
 
void loop ()
//Set NbTops to 0 ready for calculations
{ NbTopsFan = 0;
 
//Enables interrupts
sei();
 
//Wait 1 second
delay (100);
 
//Disable interrupts
cli();
 
//Times NbTopsFan (which is apprioxiamately the fequency the fan 
//is spinning at) by 60 seconds before dividing by the fan's divider
Calc = ((NbTopsFan * 600)/fanspace[fan].fandiv);

if (Calc>600){
   digitalWrite(led_pin, LOW);
   digitalWrite(buzzer_pin, LOW);
   digitalWrite(relay_pin, LOW);
}else{
   digitalWrite(led_pin, HIGH);
   digitalWrite(buzzer_pin, HIGH);
   digitalWrite(relay_pin, HIGH);
}
//Prints the number calculated above
Serial.print (Calc, DEC);
 
//Prints " rpm" and a new line
Serial.print (" rpm\r\n");
} 

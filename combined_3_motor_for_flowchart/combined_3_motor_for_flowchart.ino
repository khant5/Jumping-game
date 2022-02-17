#include <LiquidCrystal.h>
#include <Servo.h>
Servo myServo;
// init the lcd display according to the circuit

LiquidCrystal lcd(12, 11, 6, 5, 4, 3);

int const potPin =A0;

int potVal; 
int angle;
 
void setup()  {
myServo.attach(9);
  lcd.begin(16, 2);

}

void loop() {
  potVal = analogRead(potPin);
  angle = map(potVal, 0, 1023, 0, 179);
  myServo.write(angle);
  long previousMillis = 0;
  unsigned long currentMillis = millis();
  long interval = 1000;
  static uint32_t last_arrow_move;  // last time the arrow moved
  static int arrow_x, arrow_y;
  const int player_x = 5;
  static int player_y;
  int count = 0;
  // Update the arrow position every 100 ms.
  int speed=(angle/1.8);
  if(currentMillis - previousMillis > interval) {
    // save the last time you blinked the LED 
    previousMillis = currentMillis;   
      lcd.setCursor(0,0);
      lcd.print(currentMillis/1000);
      lcd.setCursor(0,2);
      lcd.print(" ");
     
  
  }
 
  


       
    lcd.setCursor(0,1);
    lcd.print(speed);
          // speed=speed/4;
  if (millis() - last_arrow_move >= (speed)) {
    
   
   
    last_arrow_move += speed;
   
   
    
  
    //  last_arrow_move=last_arrow_move-50;
    // Erase the arrow at its old position.
    lcd.setCursor(arrow_x, arrow_y);
    lcd.print("  ");

  
    // Move one cell to the left.
    arrow_x--;
    
    // If too far left, then send a brand new arrow.
    if (arrow_x < 2) {
      arrow_x = 15;
      arrow_y = random(0, 2);


    }

    // Draw the arrow at its new position.
    lcd.setCursor(arrow_x, arrow_y);
    lcd.print("<-");

  }

  // Get the updated player position.
  int new_player_y;
  if (digitalRead(7) == HIGH) {  // "jump" button pressed
    new_player_y = 0;
     lcd.setCursor(0,0);
    
    
  }
  else {
    new_player_y = 1;
  }

  // Update the player if he moved.
  if (new_player_y != player_y) {

    // Erase the player at its old position.
    lcd.setCursor(player_x, player_y);
    lcd.print(" ");
    

    // Move.
    player_y = new_player_y;

    // Redraw at the updated position.
    lcd.setCursor(player_x, player_y);
    lcd.print("x");
     
  }
if ((player_x == arrow_x) && (player_y == arrow_y)){
int score=currentMillis/1000;
lcd.clear(); 
lcd.setCursor (12,1);
lcd.print(score);
lcd.setCursor (0,1);
lcd.print ("Press Reset");
lcd.setCursor (0,0);
lcd.print ("Game Over!Score:");
//myServo.write(angle);
  
 exit(0);
}
 
}

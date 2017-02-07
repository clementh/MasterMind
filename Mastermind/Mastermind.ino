#include <LiquidCrystal.h>

LiquidCrystal lcd(12, 11, 5, 4, 3, 2);

const int button_1 = 8;
const int button_2 = 9;


void setup() {
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);
  srand(analogRead(0));
  
  // set up the LCD's number of columns and rows:
  lcd.begin(16, 2);
  lcd.clear();

}


//##################################################littles function##################################################
void ResetPlayerAnswer(char *playerAnswer){
      for(int i = 0; i<4; i++){
      playerAnswer[i] = 'A';
    }
}


void ScrollText(char *text){
  int len = strlen(text);
  
  // set the cursor to (16,0):
  lcd.setCursor(16,0);
  // set the display to automatically scroll:
  lcd.autoscroll();
  for (int i = 0; i < len; i ++) {
    lcd.print(text[i]);
    delay(350);
  }
  lcd.noAutoscroll();
  lcd.clear();  
}


void BlinkLcd(char *text){
  lcd.write(text);
  for(int i = 0; i<4 ; i++){
    // Turn off the display:
    lcd.noDisplay();
    delay(300);
    // Turn on the display:
    lcd.display();
    delay(200);
  }
  //lcd.clear();
}



//##################################################Importants functions ##################################################
void DisplayBegin(){
  // Print a message to the LCD.
  lcd.setCursor(3,0);
  lcd.print("MasterMind");
  lcd.setCursor(6, 1);
  lcd.print("v1.0");
  delay(2000);
  lcd.clear();
}



void DisplayEnd(int win, char *secretAnswer){
  //define if we won or loss and display a correct sentence
  if(win) {
    char *text = "CONGRATULATIONS YOU WIN!";
    char *text2 = "CONGRATULATIONS!";
    ScrollText(text);
    BlinkLcd(text2);
  }
  else{
    lcd.clear();
    lcd.setCursor(3,0);
    lcd.print("GAME  OVER");
  }
  //print the answer on the lcd screen
  lcd.setCursor(0,1);
  lcd.print("Answer was: ");
  lcd.write(secretAnswer);
  delay(4000);
}


void RandomAnswer(char *secretAnswer){
  for (int i = 0; i < 4; i++){
     secretAnswer[i] = (rand()%6)+65;
  }
  secretAnswer[4]='\0';

}


int GetButtons(){
  while((digitalRead(button_1) != HIGH) && (digitalRead(button_2) != HIGH) ){}
  if (digitalRead(button_1) == HIGH)
    return 1; 
    
  if (digitalRead(button_2) == HIGH)
    return 2;
    
  else 
    return 0;
}



void InputLetters (char *playerAnswer, int *dx, int *dy){
  int input = 0;
  int letter = 0;
  ResetPlayerAnswer(playerAnswer);
  
  for(;letter <= 3;){
    lcd.setCursor(*dx,*dy);
    //lcd.blink();
    //lcd.cursor();
    lcd.write(input+65);
    
    if(GetButtons()==1){    
      input = (input+=1)%6;
    }
    if(GetButtons()==2){
      playerAnswer[letter] = input + 65;
      input = 0;
      letter ++;
      *dx +=1;
    }
    delay(200);
  }

}


void Printer(int *results, int *dx, int *dy, int nbTry) {
  byte figure[8] = {B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00000};
  
  if((results[0] != 0) || ( results[1]!=0)){
    int p =0;
    for(int i = 0; i<results[0]&& p<=9; i++){
      figure[p]=B11000;
      p+=2;
    }
    p=1;
    
    for(int i = 0; i<results[1] && p<=9; i++){
      figure[p]=B000011;
      p+=2;
    }
  }
  lcd.createChar(nbTry+1, figure);
  lcd.setCursor(*dx,*dy);
  lcd.write(nbTry+1);
  
  if((*dx+1)==15){
    *dy=(*dy+1);
  }
  *dx=(*dx+1)%15;
  
  delay(600);
  
}



int *GetResults(char *secretAnswer, char *playerAnswer){
    int i, j;

    int *result = (int *)malloc(sizeof(int)*2);
    result[0] = 0; result[1] = 0;

    for (i = 0; i < 4; ++i)
    {
        if (playerAnswer[i] == secretAnswer[i])
        {
            result[0] += 1;
            secretAnswer[i] += 32;
            playerAnswer[i] = '1';
        }
    }

    if (result[0] != 4)
    {
        for (i = 0; i < 4; i++)
        {
            for (j = 0; j < 4; j++)
            {
                if (playerAnswer[i] == secretAnswer[j])
                {   
                    result[1] += 1;
                    secretAnswer[j] += 32;
                    playerAnswer[i] = '2';
                }
            }     
        }
    }
    for (int i = 0; i < 4; ++i)
    {
        if (secretAnswer[i] > 96)
        {
            secretAnswer[i] = secretAnswer[i] -= 32;
        }    
    }
    return result;  
}




int GameLoop(char *secretAnswer, char *playerAnswer, int dx, int dy){
  int nbTry;
  int *result;
  
  for(nbTry = 0; nbTry<6; nbTry++){
    InputLetters(playerAnswer, &dx, &dy);
    result = GetResults(secretAnswer, playerAnswer);
    Printer(result, &dx,&dy, nbTry);
    if(result[0] == 4)
      return 0;
  }
  return 1;
}


/*Function 
    DisplayBegin();
    DisplayEnd(1, secretAnswer);
    RandomAnswer(secretAnswer);
    InputLetters(playerAnswer, &dx, &dy);
    ScrollText(text);
    
*/

void loop() {
  lcd.clear();
  lcd.home();
  char secretAnswer[4];
  char playerAnswer[4];
  int dx = 0;
  int dy = 0;
  
  DisplayBegin();
  
  RandomAnswer(secretAnswer);
  //lcd.write(secretAnswer);
  
  delay(500);
  lcd.clear();
  

  int gameStatus = GameLoop(secretAnswer,playerAnswer, dx, dy);
  
  if(gameStatus == 0)
    DisplayEnd(1, secretAnswer);
  else
    DisplayEnd(0, secretAnswer);


    
  delay(1000);
}



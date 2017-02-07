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

void ResetAnswer(char *Answer){
      for(int i = 0; i<4; i++){
      Answer[i] = '\0';
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
  lcd.print("v1.1");
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

int CheckTwins(char *secretAnswer, char tmp){
  for (int i =0; i<4; i++)
    if(tmp == secretAnswer[i])
      return 0;
  return 1;
}


int MenuDisplay(void){
  char *levels[5]={"BEGINNER","NORMAL","TEACHER","HARD","42"};
  
  int input = 0;
  lcd.clear();
  lcd.home();
  lcd.write("SELECT LEVEL :");
  lcd.setCursor(0,1);
  lcd.print(levels[input]);

  for(;;){
    if(GetButtons()==1){
      lcd.clear();
      lcd.home();
      lcd.write("SELECT LEVEL :");
      lcd.setCursor(0,1);

      input = (input+=1)%5;
      lcd.print(levels[input]);
    }
    if(GetButtons()==2){
      return input;
    }
    delay(200);
  }
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


//##################################################LEVELS functions ##################################################


void RandomAnswer_0(char *secretAnswer){
  char tmp;
  ResetAnswer(secretAnswer);
  
  for (int i = 0; i < 4;){
    tmp = (rand()%5)+65;
    
    if(CheckTwins(secretAnswer, tmp) ==1){
      secretAnswer[i] = tmp;
      i++;
    }
  }
  secretAnswer[4]='\0';
}


void RandomAnswer_1(char *secretAnswer){
  char tmp;
  ResetAnswer(secretAnswer);
  
  for (int i = 0; i < 4;){
    tmp = (rand()%6)+65;
    
    if(CheckTwins(secretAnswer, tmp) ==1){
      secretAnswer[i] = tmp;
      i++;
    }
  }
  secretAnswer[4]='\0';
}


void RandomAnswer(char *secretAnswer){
  ResetPlayerAnswer(secretAnswer);

  
  for (int i = 0; i < 4; i++){
     secretAnswer[i] = (rand()%6)+65;
  }
  secretAnswer[4]='\0';
}


void RandomAnswer_3(char *secretAnswer){
  ResetPlayerAnswer(secretAnswer);

  
  for (int i = 0; i < 4; i++){
     secretAnswer[i] = (rand()%7)+65;
  }
  secretAnswer[4]='\0';

}

void RandomAnswer_4(char *secretAnswer){
  ResetPlayerAnswer(secretAnswer);

  
  for (int i = 0; i < 4; i++){
     secretAnswer[i] = (rand()%26)+65;
  }
  secretAnswer[4]='\0';

}


void InputLetters_0(char *playerAnswer, int *dx, int *dy){
  int input = 0;
  int letter = 0;
  ResetAnswer(playerAnswer);
  
  for(;letter < 4;){
    lcd.setCursor(*dx,*dy);
    lcd.write(input+65);
    
    if(GetButtons()==1){ 
      do
      {
        input = (input+=1)%5;
        
      }while(CheckTwins(playerAnswer,(input)%5+65)!=1);  
    }
    if(GetButtons()==2){
      playerAnswer[letter] = input + 65;
      for(input = 0;CheckTwins(playerAnswer,input+65)!=1;input ++){}
      
      letter ++;
      *dx +=1;
    }
    delay(200);
  }
}


void InputLetters_1(char *playerAnswer, int *dx, int *dy){
  int input = 0;
  int letter = 0;
  ResetAnswer(playerAnswer);
  
  for(;letter < 4;){
    lcd.setCursor(*dx,*dy);
    lcd.write(input+65);
    
    if(GetButtons()==1){ 
      do
      {
        input = (input+=1)%6;
        
      }while(CheckTwins(playerAnswer,(input)%5+65)!=1);  
    }
    if(GetButtons()==2){
      playerAnswer[letter] = input + 65;
      for(input = 0;CheckTwins(playerAnswer,input+65)!=1;input ++){}
      
      letter ++;
      *dx +=1;
    }
    delay(200);
  }
}



void InputLetters(char *playerAnswer, int *dx, int *dy){
  int input = 0;
  int letter = 0;
  ResetPlayerAnswer(playerAnswer);
  
  for(;letter <= 3;){
    lcd.setCursor(*dx,*dy);
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


void InputLetters_3(char *playerAnswer, int *dx, int *dy){
  int input = 0;
  int letter = 0;
  ResetPlayerAnswer(playerAnswer);
  
  for(;letter <= 3;){
    lcd.setCursor(*dx,*dy);
    lcd.write(input+65);
    
    if(GetButtons()==1){    
      input = (input+=1)%7;
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


void InputLetters_4(char *playerAnswer, int *dx, int *dy){
  int input = 0;
  int letter = 0;
  ResetPlayerAnswer(playerAnswer);
  
  for(;letter <= 3;){
    lcd.setCursor(*dx,*dy);
    lcd.write(input+65);
    
    if(GetButtons()==1){    
      input = (input+=1)%26;
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

int GameLoop_0(char *secretAnswer, char *playerAnswer, int dx, int dy){
  int nbTry;
  int *result;
  
  RandomAnswer_0(secretAnswer);

  for(nbTry = 0; nbTry<6; nbTry++){
    InputLetters_0(playerAnswer, &dx, &dy);
    result = GetResults(secretAnswer, playerAnswer);
    Printer(result, &dx,&dy, nbTry);
    
    if(result[0] == 4)
      return 0;
  }
  return 1;
}


int GameLoop_1(char *secretAnswer, char *playerAnswer, int dx, int dy){
  int nbTry;
  int *result;
  
  RandomAnswer_1(secretAnswer);

  for(nbTry = 0; nbTry<6; nbTry++){
    InputLetters_1(playerAnswer, &dx, &dy);
    result = GetResults(secretAnswer, playerAnswer);
    Printer(result, &dx,&dy, nbTry);
    
    if(result[0] == 4)
      return 0;
  }
  return 1;
}


int GameLoop(char *secretAnswer, char *playerAnswer, int dx, int dy){
  int nbTry;
  int *result;
  
  RandomAnswer(secretAnswer);

  
  for(nbTry = 0; nbTry<6; nbTry++){
    InputLetters(playerAnswer, &dx, &dy);
    result = GetResults(secretAnswer, playerAnswer);
    Printer(result, &dx,&dy, nbTry);
    if(result[0] == 4)
      return 0;
  }
  return 1;
}


int GameLoop_3(char *secretAnswer, char *playerAnswer, int dx, int dy){
  int nbTry;
  int *result;
  
  RandomAnswer_3(secretAnswer);

  
  for(nbTry = 0; nbTry<6; nbTry++){
    InputLetters_3(playerAnswer, &dx, &dy);
    result = GetResults(secretAnswer, playerAnswer);
    Printer(result, &dx,&dy, nbTry);
    if(result[0] == 4)
      return 0;
  }
  return 1;
}


int GameLoop_4(char *secretAnswer, char *playerAnswer, int dx, int dy){
  int nbTry;
  int *result;
  
  RandomAnswer_4(secretAnswer);

  
  for(nbTry = 0; nbTry<6; nbTry++){
    InputLetters_4(playerAnswer, &dx, &dy);
    result = GetResults(secretAnswer, playerAnswer);
    Printer(result, &dx,&dy, nbTry);
    if(result[0] == 4)
      return 0;
  }
  return 1;
}




//################################################## Main ##################################################


void loop() {
  lcd.clear();
  lcd.home();
  char secretAnswer[4];
  char playerAnswer[4];
  int dx = 0;
  int dy = 0;
  int gameStatus = 0;
  int level = 4;
  
  DisplayBegin();
    
  delay(500);
  lcd.clear();
  
  level = MenuDisplay();
  lcd.clear();
  delay(300);
  

  switch(level){
  case 0:
    gameStatus = GameLoop_0(secretAnswer, playerAnswer, dx, dy);
    break;
  
  
  case 1:
     gameStatus = GameLoop_1(secretAnswer, playerAnswer, dx, dy);
     break;
     
  case 2:
     gameStatus = GameLoop(secretAnswer, playerAnswer, dx, dy);
     break;

   case 3:
    gameStatus = GameLoop_3(secretAnswer,playerAnswer, dx, dy);
    break;
    
  case 4:
    gameStatus = GameLoop_4(secretAnswer,playerAnswer, dx, dy);
    break;
  
  }
  if(gameStatus == 0)
    DisplayEnd(1, secretAnswer);
  else
    DisplayEnd(0, secretAnswer);

    
  delay(1000);
}



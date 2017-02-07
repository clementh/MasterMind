/**********************************************************
 * ***********************MASTERMIND***********************
 * ********************************************************
 * **                                                    **
 * ###################### Version 2.1 #####################
 * **                                                    **
 * ** Authors:       C.HERAT && P-M.MAGNI                **
 * **                                                    **
 * ** last edit: 07/02/2017                              **
 * *******************************************************/


#include <LiquidCrystal.h>


/**
 * Initialisation de la librairie avec les sorties de l'Arduino utilisées pour l'écran
 * Et declaration des entrées de l'Arduino pour les boutons ainsi que les leds
 */
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int button_1 = 8;
const int button_2 = 9;
const int led_r = 6;
const int led_v = 7;


/**
 * Initialisation de l'Arduino :
 * indiquer a la librairie les "dimensions" de l'écran
 * indiquer le mode de fonctionnement des pins pour les boutons
 * Indiquer le mode de fonctionnement des pins pour les leds   
 */
void setup() {
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);
  pinMode(led_r, OUTPUT);
  pinMode(led_v, OUTPUT);

  srand(analogRead(0));
  
  lcd.begin(16, 2);
  lcd.clear();
  
  DisplayBegin();
}


/**
 * Fonction de réinitialisation du tableau de stockage pour la réponse du joueur
 * 
 * @param playerAnswer [ tableau contenant la réponse du joueur]
 */
void ResetPlayerAnswer(char *playerAnswer){
      for(int i = 0; i<4; i++){
      playerAnswer[i] = 'A';
    }
}


/**
 * Fonction pour réinitialiser le tableau de stockage de la réponse secrète
 * 
 * @param Answer [tableau contenant la réponse secrète]
 */
void ResetAnswer(char *Answer){
      for(int i = 0; i<4; i++){
      Answer[i] = '\0';
    }
}



/**
 * Pour faire les différents affichages avec un texte qui défile du programme,
 * nous avons créé cette fonction qui prend un texte en entrée et l'affiche
 * sur l'écran en le faisant se décaler vers la gauche 
 * 
 * @param text [le texte à afficher]
 */
void ScrollText(char *text){
  int len = strlen(text);
  
  // set the cursor to (16,0):
  lcd.setCursor(16,0);
  // set the display to automatically scroll:
  lcd.autoscroll();
  for (int i = 0; i < len; i ++) {
    lcd.print(text[i]);
    delay(200);
  }
  lcd.noAutoscroll();
  lcd.clear();  
}



/**
 * Permet de faire clignoter un texte sur l'écran lcd.
 *  
 * @param text [chaine de caractère à faire clignoter]
 */
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


/**
 * Permet de faire clignoter les leds au lancement du jeu
 * 
 * @param flash_num   [int] indique le nombre de clignotement
 * @param flash_speed [int] indique la vitesse de clignotement
 */
void BlinkLed(int flash_num, int flash_speed){
  for(int i = 0; i<flash_num; i++){
    digitalWrite(led_r, HIGH); 
    digitalWrite(led_v, HIGH);
    delay(flash_speed);
    digitalWrite(led_r, LOW); 
    digitalWrite(led_v, LOW); 
    delay(flash_speed);
  }
}


/**
 * Permet de faire clignoter de façon particulière les leds lors des défaites ou
 * des victoires
 * 
 * @param led         [int] définit la led a faire clignoter 
 * @param flash_speed [int] définit la vitesse de clignotement
 * @param flash_num   [int] définit le nombre de clignotement
 */
void LedAnswer(int led, int flash_speed, int flash_num){
    for(int i=0; i<flash_num; i++){
      digitalWrite(led,HIGH);
      delay(flash_speed);
      digitalWrite(led,LOW);
      delay(flash_speed);
      digitalWrite(led,HIGH);

    }
}


/**
 * Affichage de présentation du jeu
 */
void DisplayBegin(){
  // Print a message to the LCD.
  lcd.setCursor(3,0);
  lcd.print("MasterMind");
  lcd.setCursor(6, 1);
  lcd.print("v2.1");
  BlinkLed(10, 100);
  lcd.clear();
}


/**
 * Affiche un ecran avec la réponse et si on a gagné ou perdu
 * 
 * @param win          [si gagné ou perdu]
 * @param secretAnswer [Réponse secrète]
 */
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
  //delay(4000);
}


/**
 * affichage du menu de choix de niveau
 * 
 * @return  [numero du niveau]
 */
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
    delay(300);
  }
}


/**
 * Fonction d'acquisition de l'état des boutons
 * On attend que l'utilisateur appuie sur un bouton et lorsqu'il le fait on 
 * retourne le chiffre correspondant
 * 
 * @switchState [une variable qui nous sert a stocker le numero du bouton allumé]
 * @return       [entier qui correspond au bouton qui est allumé]
 */
int GetButtons(){
  while((digitalRead(button_1) != HIGH) && (digitalRead(button_2) != HIGH) ){}
  if (digitalRead(button_1) == HIGH)
    return 1; 
    
  if (digitalRead(button_2) == HIGH)
    return 2;
    
  else 
    return 0;
}


/**
 * Fonction de l'affichage des résultat
 *
 * Le but de cette fonction est de réaliser le caractère spécial correspondant 
 * aux résultats de la réponses précédente du joueur.
 * 
 * Nous commençons par créer un tableau de bytes éteint pour le cas ou il n'y a aucune
 * bonnes réponses
 *
 * Ensuite nous modifions ce tableau de byte éteint en y remplacant un élément par
 * B11000 (ligne gauche, bien placés) ou B00011 (ligne droite, mal placés) en fonction
 * des résultats
 *
 * Puis nous créons le caractère spécial désiré avec ce tableau de byte
 *
 * enfin nous plaçons le curseur de l'écran lcd à la bonne position et on affiche 
 * le caractère créé en veillant à ce qu'il ne sorte pas de la zone d'affichage
 * 
 * 
 * @param results [tableau de résultats avec results[0] le nombre d'éléments bien placés]
 * @param dx      [Pointeur qui contient la position en x du curseur sur l'écran]
 * @param dy      [Pointeur qui contient la position en y du curseur sur l'écran]
 * @param nbTry   [numéro de la tentative de réponse, permet d'incrémenter un nom]
 */
void Printer(int *results, int *dx, int *dy, int nbTry) {
  
  byte figure[8] = {B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00000};   /**Déclaration caractère vide */
  
  if((results[0] != 0) || ( results[1]!=0)){                                    /**On va modifier ce tableau afin qu'il corresponde aux resultats s'il y a des éléments bien ou mal placés */

    int p =0;                                                                   /**p est une variable qui va nous permettre de nous déplacer dans le tableau de bytes créé précédement*/
    for(int i = 0; i<results[0]&& p<=9; i++){                                   /**on va s'occuper de créer les lignes correspondante au nombre d'éléments bien placés*/

      figure[p]=B11000;
      p+=2;
    }

    p=1;                                                                        /**on définit p à 1 afin d'avoir le décalage entre les lignes de bien placés et les lignes de mal placés */

    for(int i = 0; i<results[1] && p<=9; i++){                                  /**Et ici on va créer les lignes correspondant au nombre d'éléments mal placés*/
      figure[p]=B000011;
      p+=2;
    }
  }

  lcd.createChar(nbTry+1, figure);                                              /**On s'occupe de créer le caractère spécial à partir du tableau figure modifié (ou pas) précédemment et de réaliser l'affichage au bon endroit sur l'écran LCD */
  lcd.setCursor(*dx,*dy);
  lcd.write(nbTry+1);

  if((*dx+1)==15){                                                               /**on veille ici a ne pas sortir de la zone d'affichage de l'écran LCD*/
    *dy=(*dy+1);
  }
  *dx=(*dx+1)%15;
  
  delay(600);
}


/**
 * Le calcul du résultat s'effectue en deux temps 
 * 
 * 1. Détermination des lettres bien placées
 *    Pour cela nous comparons les lettres situées aux même positions (user[i] 
 *    avec secret[i]) et en cas d'égalité 
 *        - on incrémente la case du tableau result correspondant au lettres 
 *          bien placée
 *        - afin d'éviter un doublon dans les recherche suivantes on met la 
 *          lettre du tableau secret en minuscule cela nous permettant également 
 *          de ne pas perde le mot secret
 *        - toujours dans le but d'éviter une double occurrence pour les 
 *          prochaine recherche on met la lettre du tableau user a la valeur 1 
 *          (nous pouvons écraser cette donnée car nous ne la réutiliserons plus) 
 * 
 * 2. Détermination des lettres mal placées
 *    Pour cela nous procédons de la même manière que précédemment mais cette fois 
 *    ci en comparant chaque lettre du tableau user a chaque lettre du tableau secret
 * Nous remettons ensuite les lettre du tableau secret en majuscule
 * 
 * @param  secretAnswer [tableau contenant la réponse secrète]
 * @param  playerAnswer [tableau contenant la réponse du joueur]
 * @return result       [tableau contenant le nombre de bien placés et le nombre de mal placé]                    
 */
int *GetResults(char *secretAnswer, char *playerAnswer){
    int i, j;

    /**
     * Tableau de Résultat la première(0) case correspond au éléments bien 
     * placés et la deuxième(1) aux éléments mal placés
     */
    int *result = (int *)malloc(sizeof(int)*2);
    result[0] = 0; result[1] = 0;

    for (i = 0; i < 4; ++i)                                                     /**Détermination des lettres bien placées*/

    {
        if (playerAnswer[i] == secretAnswer[i])
        {
            result[0] += 1;                                                     /*Incrémentation du nombre de lettres bien placées*/
            secretAnswer[i] += 32;                                              /*Mise en minuscule de la lettre*/
            playerAnswer[i] = '1';                                              /*Mise a 1 de la lettre*/
        }
    }
    if (result[0] != 4)                                                         /**Si toutes les lettres sont bien placées on ne vérifie pas si il y en a des mal placées*/
    {
        for (i = 0; i < 4; i++)                                                 /*Détermination des lettres bien placées*/
        {
            for (j = 0; j < 4; j++)
            {
                if (playerAnswer[i] == secretAnswer[j])
                {   
                    result[1] += 1;                                             /*Incrémentation du nombre de lettres bien placées*/
                    secretAnswer[j] += 32;                                      /*Mise en minuscule de la lettre*/
                    playerAnswer[i] = '2';                                      /*Mise a 2 de la lettre*/
                }
            }     
        }
    }
    for (int i = 0; i < 4; ++i)                                                 /*mise en majuscule des lettre ayant été mise en minuscule*/
    {
        if (secretAnswer[i] > 96)
        {
            secretAnswer[i] = secretAnswer[i] -= 32;
        }    
    }
  return result;  
}


/**
 * Fonction qui a pour objectif d'informer s'il y a deja la nouvelle lettre dans
 * le tableau en entrée
 * 
 * @param  secretAnswer [tableau a verifier]
 * @param  tmp          [lettre a comparer]
 * @return              [1 s'il n'y a pas de jumeau, 0 sinon]
 */
int CheckTwins(char *secretAnswer, char tmp){
  for (int i =0; i<4; i++)
    if(tmp == secretAnswer[i])
      return 0;
  return 1;
}


/**
 * Fonction qui créé la réponse secrète en fonction du niveau du jeu.
 * en effet ce dernier influe sur la plage de lettres possible pour chaque choix.
 * On utilise le code ASCII pour les manipulations.
 *
 * - On regarde tout d'abord si on a le droit d'avoir plusieur fois la même lettre
 *   en fonction du niveau
 *   - Si on a droit à plusieurs fois la même lettre :
 *     - On choisi les 4 éléments de la réponse secrète indépendamment. Pour chacun d'entre eux
 *       on utilise une valeur aléatoire modulé par la quantitée de lettre possible
 *       et on additionne ça à 65 afin d'avoir la lettre correspondante.
 *   - Sinon on fait la même chose mais avant stocker la lettre trouvée, 
 *     on vérifie qu'elle n'a pas déjà été utilisé dans cette réponse
 *     et si elle l'a été on incrémente de 1 et on revérifie 
 * 
 * @param secretAnswer [Tableau de char contenant la réponse secrète]
 * @param interval     [Entier donnant le nombre de lettre disponible ne fonction du niveau]
 * @param twins        [Entier indiquant si avoir plusieurs fois la même lettre est autorisé ou non]
 */
void RandomAnswer(char *secretAnswer, int interval, int twins){
  char tmp;
  ResetAnswer(secretAnswer);
  if(twins!=1){
    for (int i = 0; i < 4;){
      tmp = (rand()%interval)+65;
      if(CheckTwins(secretAnswer, tmp) ==1){
        secretAnswer[i] = tmp;
        i++;
      }
    }
  }
  else
   for (int i = 0; i < 4; i++){
     secretAnswer[i] = (rand()%interval)+65;
   }
  secretAnswer[4]='\0';
}


/**
 * Fonction d'acquisition de la réponse du joueur
 *
 * Nous faisons appel a la fonction GetButtons(...) pour obtenir les infor,afin de 
 * récupérer l'information des boutons.
 * 
 * Pour chacun des 4 éléments de sa réponse le joueur va faire défiler les 
 * lettres possibles avec le bouton 1. 
 * 
 * A chaque fois qu'il appuie sur le bouton 1, on va afficher la lettre 
 * actuellement choisie.
 * 
 * Il va ensuite valider la lettre choisie avec le bouton 2. Et le curseur
 * va se déplacer d'une case sur l'écran.
 *
 * Chaque lettre choisie sera stockée à la place correspondante dans le 
 * tableau "playerAnswer"
 *
 * Nous utilison la table ASCII pour les lettres. Ce qui permet une manipulation
 * plus simple. En effet pour passer a la lettre suivante il suffit d'incrémenter
 * sa valeur de 1 et de faire un modulo afin de ne pas sortir de l'ensemble de 
 * lettre possible (de A à F ici en l'occurence).
 * 
 * @param playerAnswer [Tableau de 4 char contenant la réponse du joueur]
 * @param dx           [Pointeur qui contient la position en x du curseur sur l'écran]
 * @param dy           [Pointeur qui contient la position en y du curseur sur l'écran]
 */
void InputLetters(char *playerAnswer, int *dx, int *dy, int interval, int twins){
  int input = 0;
  int letter = 0;
  ResetAnswer(playerAnswer);
  
  if(twins!=1){
    for(;letter < 4;){
      lcd.setCursor(*dx,*dy);
      lcd.write(input+65);
      
      if(GetButtons()==1){ 
        do
        {
          input = (input+=1)%5;
          
        }while(CheckTwins(playerAnswer,(input)%interval+65)!=1);  
      }
      if(GetButtons()==2){
        playerAnswer[letter] = input + 65;
        for(input = 0;CheckTwins(playerAnswer,input+65)!=1;input ++){}
        
        letter ++;
        *dx +=1;
      }
    delay(300);
    }
  }
  else{
    for(;letter < 4;){
      lcd.setCursor(*dx,*dy);
      lcd.write(input+65);
      
      if(GetButtons()==1){    
        input = (input+=1)%interval;
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
}


/**
 * Boucle de jeu principale.
 *
 * elle depend directement du choix de niveau effectué dans le menu.
 *
 * en fonction du niveau choisi elle va autoriser ou non d'avoir plusieurs
 * fois la même lettres et la quantitée de lettre disponible 
 * 
 * @param  secretAnswer [réponse secrète]
 * @param  playerAnswer [réponse du joueur]
 * @param  dx           [position du curseur sur l'écran en x]
 * @param  dy           [position du curseur sur l'écran en y]
 * @param  interval     [quantitée de lettres disponible]
 * @param  twins        [si avoir plusieurs fois la même lettre est autorisé ou non]
 * @return              [0 si victoire, 1 sinon]
 */
int GameLoop(char *secretAnswer, char *playerAnswer, int dx, int dy, int interval, int twins){
  int nbTry;
  int *result;
  
  RandomAnswer(secretAnswer, interval, twins);

  for(nbTry = 0; nbTry<6; nbTry++){
    InputLetters(playerAnswer, &dx, &dy, interval, twins);
    result = GetResults(secretAnswer, playerAnswer);
    Printer(result, &dx,&dy, nbTry);
    
    if(result[0] == 4)
      return 0;
  }
  return 1;
}


/**
 * Boucle principale du programme
 *
 * Dans cette version nous avons implémenté des niveaux, il y en a 5:
 *   - Beginner : niveau débutant, "finger in the nose"
 *       - Pas le droit à plusieurs fois la même lettre
 *       - Les lettres possible sont de A à E
 *       
 *   - Normal   : règles officielle du Mastermind
 *       - Pas le droit à plusieurs fois la même lettre
 *       - Les lettres possible sont de A à F
 *       
 *   - Teacher  : règles demandées dans le sujet du projet
 *       - Plusieurs même lettres possible
 *       - Les lettres possible sont de A à F
 *
 *   - Hard     : niveau difficile, "Good Luck !"
 *       - Plusieurs même lettres possible
 *       - Les lettres possible sont de A à G
 *       
 *   - 42       : niveau solution 404 "Fuyez Pauvres Fous!"
 *       - Plusieurs même lettres possible
 *        Les lettres possible sont tout l'alphabet 
 *
 *
 *  Et nous avons également des Leds qui s'allument en fonction des évenement du jeu. ;)
 *
 * Enjoy the game !
 */
void loop() {
  char secretAnswer[4];
  char playerAnswer[4];
  int dx = 0;
  int dy = 0;
  int gameStatus = 0;
  int level = 4;
      
  lcd.clear();
  
  level = MenuDisplay();
  
  lcd.clear();
  delay(300);
  

  switch(level){
  case 0:
    gameStatus = GameLoop(secretAnswer, playerAnswer, dx, dy, 5, 0);
    break;
  
  
  case 1:
     gameStatus = GameLoop(secretAnswer, playerAnswer, dx, dy, 6, 0);
     break;
     
  case 2:
     gameStatus = GameLoop(secretAnswer, playerAnswer, dx, dy, 6, 1);
     break;

   case 3:
    gameStatus = GameLoop(secretAnswer,playerAnswer, dx, dy, 7, 1);
    break;

  case 4:
    gameStatus = GameLoop(secretAnswer,playerAnswer, dx, dy, 26, 1);
    break;
  
  }
  if(gameStatus == 0){
    DisplayEnd(1, secretAnswer);
    LedAnswer(led_v,100,10);
    delay(1000);
  }
  else{
    DisplayEnd(0, secretAnswer);
    LedAnswer(led_r,100,5);
    delay(1000);

  }
  delay(1000);
  
  digitalWrite(led_v,LOW);
  digitalWrite(led_r,LOW);

}
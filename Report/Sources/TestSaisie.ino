/**
 * **************************
 * ***********TEST***********
 * **************************
 * Programme de test pour la fonction de saisie des réponses
 */

#include <LiquidCrystal.h>


/**
 * Initialisation de la librairie avec les sorties de l'Arduino utilisées pour l'écran
 * Et declaration des entrées de l'Arduino pour les boutons
 */
LiquidCrystal lcd(12, 11, 5, 4, 3, 2);
const int button_1 = 8;
const int button_2 = 9;


/**
 * Initialisation de l'Arduino :
 * indiquer a la librairie les "dimensions" de l'écran
 * indiquer le mode de fonctionnement des pins pour les boutons     
 */
void setup() {
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);

  lcd.begin(16, 2);
}


/**
 * Fonction d'acquisition de l'état des boutons
 * On attend que l'utilisateur appuie sur un bouton et lorsqu'il le fait on retourne le chiffre correspondant
 * 
 * @switchState [int] est une variable qui nous sert a stocker le numero du bouton allumé. 
 * @return un entier qui correspond au bouton qui est allumé
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
 * @param playerAnswer [char *] Tableau de 4 char contenant la réponse du joueur
 * @param dx           [int *] Pointeur qui contient la position en x du curseur 
 *                             sur l'écran
 * @param dy           [int *] Pointeur qui contient la position en y du curseur
 *                             sur l'écran
 */
void InputLetters (char *playerAnswer, int *dx, int *dy){
  int input = 0;
  int letter = 0;
  
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


/**
 * Boucle principale du programme
 *
 * Nous allons effacer l'écran en 1er lieu afin d'éviter tout reste d'affichage
 *
 * Ensuite nous plaçons le curseur à l'origine de l'écran (home = position(0,0))
 *
 * Nous laissons 6 tentatives de réponse au joueur. 
 * A chaque tentative nous faisons appel à la fonction InputLetters(...) pour
 * l'acquisition de la réponse.
 *
 * Lorsqu'une tentative de réponse a été faite nous faisons 2 choses :
 *   - on regarde si le curseur est proche du bord droit de l'écran 
 *     (position en x supérieur à 13) et si oui on passe à la ligne en 
 *     incrémentant la position en y de 1 en vérifiant qu'on ne sort pas non 
 *     plus de l'écran.
 *   - on incrémente la position du curseur en x de 1 afin de sauter une case 
 *     d'affichage qui nous servira plus tard pour afficher les résultats de la 
 *     tentative.
 *
 */
void loop() {
  lcd.clear();
  lcd.home();
  char playerAnswer[4];
  int dx = 0;
  int dy = 0;
  int nbTry;
  for(nbTry = 0; nbTry<6; nbTry++){
    InputLetters(playerAnswer, &dx, &dy);
    if(dx>=13)
      dy=(dy+1)%2;
    
    dx=(dx+1)%15;
  }
  delay(1000);
}
/**
 * **************************
 * ***********TEST***********
 * **************************
 * Programme de test pour la saisie avec les 2 boutons
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
  lcd.begin(16, 2);
  pinMode(button_1, INPUT);
  pinMode(button_2, INPUT);

}



/**
 * Fonction d'acquisition de l'état des boutons
 * On attend que l'utilisateur appuie sur un bouton et lorsqu'il le fait on retourne le chiffre correspondant
 * 
 * @switchState [int] est une variable qui nous sert a stocker le numero du bouton allumé. 
 * @return un entier qui correspond au bouton qui est allumé
 */
int GetButtons(){
  int switchState = 0;  
  while((digitalRead(button_1) != HIGH) && (digitalRead(button_2) != HIGH) ){}
  
  if (digitalRead(button_1) == HIGH)
    switchState = 1; 
    
  if (digitalRead(button_2) == HIGH)
    switchState = 2;
   
  return switchState; 
}



/**
 * Boucle principale du programme
 * 
 * on va en permanence afficher "James"
 * et lorsqu'on appuyera sur un des boutons on affichera "Bond" a la suite de "James"
 */
void loop() {
  lcd.clear();
  
  lcd.print("James");
  
  delay(200);
  
  
  if(GetButtons()){
    lcd.print("Bond");
    delay(200);
  }
  
  lcd.clear(); 

}

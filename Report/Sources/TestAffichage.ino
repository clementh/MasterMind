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
 * @param results [tableau de int] results[0] est le nombre d'éléments bien placés
 * @param dx      [int *] Pointeur qui contient la position en x du curseur 
 *                        sur l'écran
 * @param dy      [int *] Pointeur qui contient la position en y du curseur
 *                        sur l'écran
 * @param nbTry   [int] numéro de la tentative qui sert a definir un nouveau 
 *                      caractère spécial correspondant a la réponse que nous 
 *                      voulons afficher.
 */
void Printer(int *results, int *dx, int *dy, int nbTry) {
  /** Déclaration caractère vide */
  byte figure[8] = {B00000,B00000,B00000,B00000,B00000,B00000,B00000,B00000};
  
  /**
   * On va modifier ce tableau afin qu'il corresponde aux resultats s'il y a des
   * éléments bien ou mal placés
   */
  if((results[0] != 0) || (results[1]!=0)){
    /**
     * p est une variable qui va nous permettre de nous déplacer dans le tableau
     * de bytes créé précédement
     */
    int p =0; 

    /**
     * on va s'occuper de créer les lignes correspondante au nombre d'éléments 
     * bien placés
     */
    for(int i = 0; i<results[0]&& p<=9; i++){
      figure[p]=B11000;
      p+=2;
    }
    /** 
     * on définit p à 1 afin d'avoir le décalage entre les lignes de bien placés 
     * et les lignes de mal placés 
     */
    p=1;
    
    /**
     * Et ici on va créer les lignes correspondant au nombre d'éléments mal placés
     */
    for(int i = 0; i<results[1] && p<=9; i++){
      figure[p]=B000011;
      p+=2;
    }
  }

  /**
   * On s'occupe de créer le caractère spécial à partir du tableau figure
   * modifié (ou pas) précédemment et de réaliser l'affichage au bon endroit sur
   * l'écran LCD
   */
  lcd.createChar(nbTry+1, figure);
  lcd.setCursor(*dx,*dy);
  lcd.write(nbTry+1);
  

  /**
   * on veille ici a ne pas sortir de la zone d'affichage de l'écran LCD
   */
  if((*dx+1)==15){
    *dy=(*dy+1);
  }
  *dx=(*dx+1)%15;
  
  delay(600);
  
}


/**
 * Boucle principale du jeu
 *
 * Nous allons déclarer en dur le tableau results qui contient le nombre de 
 * bien placés et le nombre de mal placés afin de tester la fonction 
 * d'affichage des résultats
 */
void loop() {
  int result[2]={1;2};
  int dx = 0;
  int dy = 0;

  Printer(results, &dx, &dy, 1)

  delay(10000);
}

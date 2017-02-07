#include stdio.h
#include stdlib.h


/*Fonction de calcul du résultat.*/


/*
Le calcul du résultat s'effectue en deux temps 
1. Détermination des lettres bien placées
    Pour cela nous comparons les lettres situées aux même positions (user[i] avec secret[i]) et en cas d'égalité 
        - on incrémente la case du tableau result correspondant au lettres bien placée
        - afin d'éviter un doublon dans les recherche suivantes on met la lettre du tableau secret en minuscule cela nous permettant également de ne pas perde le mot secret
        - toujours dans le but d'éviter une double occurrence pour les prochaine recherche on met la lettre du tableau user a la valeur 1 (nous pouvons écraser cette donnée car nous ne la réutiliserons plus) 
2. Détermination des lettres mal placées
    Pour cela nous procédons de la même manière que précédemment mais cette fois ci en comparant chaque lettre du tableau user a chaque lettre du tableau secret
nous remettons ensuite les lettre du tableau secret en majuscule
*/
int GetAnswer(char secret, char user){

    int i, j; /** Variable pour le parcours des tableaux */
    
    int result = (int )malloc(sizeof(int)2); /*Tableau de Résultat la première(0) case correspond au éléments bien placés et la deuxième(1) aux éléments mal placés*/
    result[0] = 0; result[1] = 0;

    for (i = 0; i  4; ++i)/*Détermination des lettres bien placées*/
    {
        if (user[i] == secret[i])
        {
            result[0] += 1;/*Incrémentation du nombre de lettres bien placées*/
            secret[i] += 32;/*Mise en minuscule de la lettre*/
            user[i] = '1';/*Mise a 1 de la lettre*/
        }
    }

    if (result[0] != 4)/*Si toutes les lettres sont bien placées on ne vérifie pas si il y en a des mal placées*/
    {
        for (i = 0; i  4; i++)/*Détermination des lettres bien placées*/
        {
            for (j = 0; j  4; j++)
            {
                if (user[i] == secret[j])
                {   
                    result[1] += 1;/*Incrémentation du nombre de lettres bien placées*/
                    secret[j] += 32;/*Mise en minuscule de la lettre*/
                    user[i] = '2';/*Mise a 2 de la lettre*/
                }

            }     
        }
    }

    for (int i = 0; i  4; ++i)/*mise en majuscule des lettre ayant été mise en minuscule*/
    {
        if (secret[i]  96)
        {
            secret[i] = secret[i] -= 32;
        }
        
    }
return result;
    
}

int main(int argc, char const argv[])
{
    char secret[4] = ABBA;
    char user[4] = ACDC;
    int i;

    int tab = GetAnswer(secret, user);
    
    for (i = 0; i  4; ++i)/*Test du résultat*/
    {
        printf(%cn, secret[i]);
    }
    printf(n);

    for (i = 0; i  4; ++i)/*Test du résultat*/
    {
        printf(%cn, user[i]);
    }
    printf(n);


    for (int i = 0; i  2; ++i)/*Test du résultat*/
    {
        printf(%dn, tab[i]);
    }

    return 0;
}


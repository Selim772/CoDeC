#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

int dechiffre(int* tmp)
{
  int tab[8];
  int stockbin[8];
  int k = 0;
  int y=0;
  for(int k=0; k<2; k++)
    {
      int c = tmp[k];
      int x=0;
      while(x < 8)
	{
	  tab[x] = c%2;
	  c = c/2;
	  x++;
	}

      stockbin[y] = tab[3];
      y++;
      stockbin[y] = tab[6];
      y++;
      stockbin[y] = tab[5];
      y++;
      stockbin[y] = tab[4];
      y++;
    }

  int res=0;
  for(int i=0; i<8; i++)
    {
      res = res*2 + stockbin[i];
    }
  return res;
}

int chiffre(int tmp, FILE*fp){
    //printf("%d", tmp);
    int tab[8]={0};
    //int tab1[8];
    int stockbin[8] = {0};
    int stockend[8] = {0};
            int c = tmp;
            //printf("%d ", c);
            int x=0;
            int i = 0;
            //printf("%d ", c);
        while(c > 0) // On obtient le nombre binaire de tab_decimal[i] decimal(c) = binaire(10110001)
        {
            tab[7-x] = c%2;
            //printf("%d", tab[7-x]);
            c = c/2;
            //printf("%d", tab[7-x]);
            x++;// là c'est la conversion du caractère decimal en binaire
            //printf("%d", tab[7-x]);
        }//printf("\n");
            //printf("%d ", c);
            /*for(int i = 0; i<8; i++){
                printf("%d", tab[7-i]);
            }*/
            //printf(" | ");
        stockbin[0] = 1;
        stockbin[1] = tab[1];
        stockbin[2] = tab[2];
        stockbin[3] = tab[3];
        stockbin[4] = tab[0];//là je met les 4premiers bits tab[0] à tab[3] dans stockbin (dans un ordre particulier)
        stockbin[5] = 1;
        stockbin[6] = 1;
        stockbin[7] = 0;// je rempli stockbin de 0, 5, 6, et 7 de bits randoms

        for(int i = 0; i<8; i++){
                //printf("%d", stockbin[i]);
            }
            //printf(" | ");

        stockend[0] = 0;
        stockend[1] = tab[5];
        stockend[2] = tab[6];
        stockend[3] = tab[7];
        stockend[4] = tab[4];// là les 4 derniers bits tab[4] à tab[7] dnas stockend dans un ordre particulier aussi
        stockend[5] = 1;
        stockend[6] = 0;
        stockend[7] = 1;// je rempli stockbin de 0, 5, 6, et 7 de bits randoms


    int res=0;
    for(int i=0; i<8; i++)
    {
      res = res*2 + stockbin[i];
      //printf("%d ", stockbin[i]);//ici je converti le tableau de 8 bits stockbin en decimal dans la variable res
    }
    //printf("|");
    //printf("%d ", res);

    int res1=0;
    for(int j=0; j<8; j++)
    {
      res1 = res1*2 + stockend[j];//ici je converti le tableau de 8 bits stockend en decimal dans la variable res1
    }
    fputc(res, fp);
    fputc(res1, fp);//ici j'insère res et res1 dans le fichier fp decléré dans le main
}


/*void stocke(int valeur,FILE* cible)
{
  fputc(valeur, cible);

}*/

int main(int argc, char const *argv[]) {

  int caractere_actuel = 0;
  FILE *fichier = NULL;
  FILE *fp = NULL;

  int tmp;
  char nomfichierachiffrer[100] = "";

  printf("Quel fichier voulez vous chiffrer ? -> ");
  fgets(nomfichierachiffrer, 100, stdin);
  if(nomfichierachiffrer[strlen(nomfichierachiffrer) - 1] == '\n')
  {
    nomfichierachiffrer[strlen(nomfichierachiffrer) - 1 ] = '\0';
  }
  fichier = fopen(nomfichierachiffrer, "rb");//c'est le fichier où je recupèrerai mes caractères
  if (fichier == NULL) {
    printf("impossible de lire %s, désolé\n", nomfichierachiffrer);
    exit(0);
  }

  strcat(nomfichierachiffrer, "c");
  fp = fopen(nomfichierachiffrer, "wb");//c'est le fichier que je créerai à la fin pour rentrer mes caractères chiffré
  if (fp == NULL) {
    printf("impossible d'ecrire dans %s\n", nomfichierachiffrer);
    exit(0);
  }

  int counter=0;
  while((caractere_actuel = fgetc(fichier)) != EOF) // je recupère un caractère, je ferai tant qu'il y aura un caractères
    {
      counter++;
      tmp = caractere_actuel;//j'affecte mon caractère à tmp pour le mettre en decimal
      //printf("%d ", tmp[k]); jusque là, c ok
	  chiffre(tmp, fp);//je met mon caractère (decimal) dans la fonction
	//stocke(chiffre(tmp),fp);
    }

  printf("\nIl y a %d caractères dans le fichier\n", counter);

  fclose(fp);
  fclose(fichier);
  return 0;
}

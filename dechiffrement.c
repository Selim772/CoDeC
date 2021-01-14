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
      while(x < 8) // On obtient le nombre binaire de tab_decimal[i]
	{
	  tab[x] = c%2;
	  c = c/2;
	  x++;
	}           // On obtient le nombre binaire de tab_decimal[i]5234 = 3654

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

int chiffre(int *tmp){
    int tab[8];
    int stockbin[8];
    int k = 0;
    int y=0;
        for(int k=0; k<2; k++)
        {
            int c = tmp[k];
            int x=0;
        while(x < 8) // On obtient le nombre binaire de tab_decimal[i]
        {
            tab[x] = c%2;
            c = c/2;
            x++;
        }
    }
}

void stocke(int valeur, FILE* cible)
{
  //printf("%d=>%c ", valeur, valeur);
  fputc(valeur, cible);
}

int main(int argc, char const *argv[]) {

  int caractere_actuel = 0;
  FILE *fichier = NULL;
  FILE *fp = NULL;

  int tmp[2];
  int k=0;
  char nomfichieradechiffrer[100] = "";
  printf("Quel fichier voulez vous dechiffrer ? -> ");
  fgets(nomfichieradechiffrer, 100, stdin);
  if(nomfichieradechiffrer[strlen(nomfichieradechiffrer) - 1] == '\n')
  {
    nomfichieradechiffrer[strlen(nomfichieradechiffrer) - 1 ] = '\0';
  }
  fichier = fopen(nomfichieradechiffrer, "rb");
  if (fichier == NULL) {
    printf("impossible de lire epreuve2.mp3c, désolé\n");
    exit(0);
  }

  strcat(nomfichieradechiffrer, "d");
  fp = fopen(nomfichieradechiffrer, "wb");
  if (fp == NULL)
    {
    printf("impossible d'ecrire epreuve2.mp3\n");
    exit(0);
    }

  int counter=0;
  while((caractere_actuel = fgetc(fichier)) != EOF) // Tant qu'il y a encore des caractères...
    {
      counter++;
      tmp[k] = caractere_actuel;
      k++;
      if(k==2){
	int octet = dechiffre(tmp);
	stocke(octet,fp);
	k=0;
      }
    }

  printf("\nIl y a %d caractères dans le fichier\n", counter);

  fclose(fp);
  fclose(fichier);
  return 0;
}

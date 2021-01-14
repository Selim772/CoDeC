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
    int tab[8]={0};
    int stockbin[8] = {0};
    int stockend[8] = {0};
            int c = tmp;
            int x=0;
            int i = 0;

        while(c > 0)
        {
            tab[7-x] = c%2;

            c = c/2;

            x++;
        }
        stockbin[0] = 1;
        stockbin[1] = tab[1];
        stockbin[2] = tab[2];
        stockbin[3] = tab[3];
        stockbin[4] = tab[0];
        stockbin[5] = 1;
        stockbin[6] = 1;
        stockbin[7] = 0;


        stockend[0] = 0;
        stockend[1] = tab[5];
        stockend[2] = tab[6];
        stockend[3] = tab[7];
        stockend[4] = tab[4];
        stockend[5] = 1;
        stockend[6] = 0;
        stockend[7] = 1;


    int res=0;
    for(int i=0; i<8; i++)
    {
      res = res*2 + stockbin[i];
    }
    int res1=0;
    for(int j=0; j<8; j++)
    {
      res1 = res1*2 + stockend[j];
    }
    fputc(res, fp);
    fputc(res1, fp);
}

void stocke(int valeur,FILE* cible)
{
  fputc(valeur, cible);
}

int main(int argc, char const *argv[]) {

    int caractere_actuel = 0;
    FILE *fichier;
    FILE *fp;
    int tmp1 = 0;
    char firstbit[9], secondbit[9], thirdbit[9], fourthbit[9];

    FILE *matrice = fopen("key.txt", "rb");
    if (matrice == NULL) {
      "Impossible d'ouvrir le fichier contenant la clé !";
      return 1;
    }
    if (fscanf(matrice, "G4C=[%[01] %[01] %[01] %[01]]", firstbit, secondbit, thirdbit, fourthbit) != 4) {
        printf("Clé incorrect !");
        fclose(matrice);
        return 1;
    }
    if (strlen(firstbit) != 8 || strlen(secondbit) != 8 || strlen(thirdbit) != 8 || strlen(fourthbit) != 8) {
        printf("Clé incorrect !");
        fclose(matrice);
        return 1;
    }




  printf("Voulez vous chiffrer(0) ou dechiffrer(1) : ");
  scanf("%d", &tmp1);

  if(tmp1 == 0){

  int tmp;
  char nomfichierachiffrer[100] = "";

  printf("Quel fichier voulez vous chiffrer ? -> ");
  fflush(stdin);
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
    printf("impossible d'ecrire %s\n", nomfichierachiffrer);
    exit(0);
  }

  int counter=0;
  while((caractere_actuel = fgetc(fichier)) != EOF) // je recupère un caractère, je ferai tant qu'il y aura un caractères
    {
      counter++;
      tmp = caractere_actuel;
      chiffre(tmp, fp);
    }
    printf("\nIl y a %d caractères dans le fichier\n", counter);
    fclose(fp);
  fclose(fichier);
  } else if(tmp1 == 1){
       int tmp[2];
       int k=0;
  char nomfichieradechiffrer[100] = "";
  printf("Quel fichier voulez vous dechiffrer ? -> ");
  fflush(stdin);
  fgets(nomfichieradechiffrer, 100, stdin);
  if(nomfichieradechiffrer[strlen(nomfichieradechiffrer) - 1] == '\n')
  {
    nomfichieradechiffrer[strlen(nomfichieradechiffrer) - 1 ] = '\0';
  }

  fichier = fopen(nomfichieradechiffrer, "rb");
  if (fichier == NULL) {
    printf("impossible de lire %s, désolé\n", nomfichieradechiffrer);
    exit(0);
  }

  strcat(nomfichieradechiffrer, "d");
  fp = fopen(nomfichieradechiffrer, "wb");
  if (fp == NULL)
    {
    printf("impossible d'ecrire dans %s\n", nomfichieradechiffrer);
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

  fclose(fp);
  fclose(fichier);
  }else{
    printf("Votre réponse ne correspond pas, veuillez choisir entre le chiffrage(0) et le dechiffrage(1)");
    scanf("%d", &tmp1);
  }

  return 0;
}

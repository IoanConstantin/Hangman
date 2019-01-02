/* Citeste de la tastatura cifra pentru meniu in loc de SAGETI */
/*  aleg=4 trec mai departe la joc nou */
/*  aleg=5 resume joc */
#include <stdio.h>
afis( char *num)
{
    printf("%c", *num);
}

int citire_meniu() {
     int aleg=0;
     char tasta;
     char maideparte;
     char arr1[]="New Game    ";
     char arr2[]="Resume Game ";
     char arr3[]="Quit        ";

      do {
        system("cls");
        //sageti_meniu(int paleg)
        if (aleg==1) printf("*");
        int i;
        for (i=0; i<12; i++)
        {
         afis (&arr1[i]);
        }
        printf("\n");

        if (aleg==2) printf("*");
        for (i=0; i<12; i++)
        {
         afis (&arr2[i]);
        }
        printf("\n");

        for (i=0; i<12; i++)
        {
         afis (&arr3[i]);
        }
        printf("\n");
        //scanf("%d",&aleg);
        //printf("aleg_before=%d",aleg);
        aleg=sageti_meniu(aleg);
        //printf("aleg_after=%d",aleg);


        /*if (aleg==1){
            maideparte=getch();
            if (maideparte==13)
                printf("Am UNU");
        }
        if (aleg==2){
            maideparte=getch();
            if (maideparte==13)
                printf("Am DOI");
        }
        */

      }
     while (aleg<3);

     system("cls");
        int i;
        for (i=0; i<12; i++)
        {
         /* passing element’s address*/
         afis (&arr1[i]);
        }
        printf("\n");

        for (i=0; i<12; i++)
        {
         /* passing element’s address*/
         afis (&arr2[i]);
        }
        printf("\n");

     printf("*");
        for (i=0; i<12; i++)
        {
         /* passing element’s address*/
         afis (&arr3[i]);
        }
        printf("\n");

  return aleg;

}

int sageti_meniu(int paleg)
{
  int iesire=0;
  //int apasenter=0;
  while(iesire==0)
  {
  //int m;
  char usrchar;
  int contor;
  contor=0;
  //char ch;
  //ch = getch();
  usrchar=getch();
    if (usrchar==13)
      if (paleg==1) {
        paleg=4;
        return paleg;
      }

    if (usrchar==13)
      if (paleg==2) {
        paleg=5;
        return paleg;
      }

    if(usrchar == -32)
        usrchar=getch();
        //printf("usrcharENTER=%d",usrchar);



    switch(usrchar)
    {
    case 72:
        contor--;
        if (contor==0)
            contor=4;
        printf("up");
        paleg=--paleg;
        if (paleg<0) paleg=0;
        iesire=1;
        //return maleg;
        break;
    case 80:
        contor++;
        if(contor==5)
            contor=1;
        printf("down");
        paleg=++paleg;
        if (paleg>3) paleg=0;
        iesire=1;
        //return maleg;
        break;
    //case 13:

    //case 13:
     //   if (iesire==1) apasenter=1;
    default :
       //if (apasenter!=1) break;
            printf("Apasati sagetile pentru navigare!");

    }
  //printf("%c - %d", ch, ch);    // prints out the char and it's int code
   }
   //printf("paleg procedure=%d",paleg);
   //return paleg;
   return paleg;
}

int main()
{
     int m_aleg;
     m_aleg=citire_meniu();
     printf("****  Plec mai departe cu **** %d",m_aleg);
     return 0;
}

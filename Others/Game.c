#include <stdio.h>
#include <string.h>

char *remove_newline(char *s)
{
    int len = strlen(s);

    if (len > 0 && s[len-1] == '\n')  // if there's a newline
        s[len-1] = '\0';          // truncate the string

    return s;
}

char* citire_cuvant() {
   int cc_i, cc_n, cc_k;
   time_t t;

   /* Intializes random number generator */
   srand((unsigned) time(&t));

   cc_n=rand() % 12;

   //printf("cc_n=%d",cc_n);

   FILE *fp;
   char scuvant[20]  ="00000000000000000000";
   //char retcuvant[20]="00000000000000000000";

   fp = fopen("cuvinte.txt" , "r");

   for (cc_k=0;cc_k<cc_n+1;cc_k++)
     fgets (scuvant, 19, fp);

   fclose(fp);
   /*printf("Proc scuvant %s",scuvant);
   printf(".");*/
   //return scuvant;

   return remove_newline(&scuvant);

}


int main() {
   int sfarsit_joc,greseli_adm,gresite,lit_nimerite,nrchar_cuv,tip_joc;
   tip_joc=2; //joc nou     2 - resume     3 - quit
   sfarsit_joc=0;
   char ghici[2];
   greseli_adm=6;
   gresite=0;
   lit_nimerite=2;
   //char cuv[]="visiniu";
   char cuv[20]  ="00000000000000000000";
   char afisate[]="....................";
    int k1=0;


  if (tip_joc==1) {
   strcpy(cuv,citire_cuvant());
   /*printf("CUV=%s",cuv);
   printf(".");
   printf("lungime cuvant:%d",strlen(cuv));*/
   /*
   char cuv[20];
   strncpy(cuv, cuv0, strlen(cuv0)-1);
   printf("Lungime:%d",strlen(cuv));
   */
   printf("\n");
   nrchar_cuv=strlen(cuv);


   afisate[0]=cuv[0];
   afisate[nrchar_cuv-1]=cuv[nrchar_cuv-1];
   // for(k1=1;k1<nrchar_cuv-1;k1++) afisate[k1]="_";

  }

  if (tip_joc==2) {
    FILE *fp2;
    fp2 = fopen("salvare.txt" , "r");

    char l_n[20];
    for (k1=0;k1<4;k1++)
    {
     fgets (l_n, 20, fp2);
     if (k1==0) {
        //fgets (l_n, 19, fp2);
        strcpy(cuv,remove_newline(&l_n));
        printf("CUV_2=%s",cuv);
        printf(".");
     }
   printf("\n");
   nrchar_cuv=strlen(cuv);

     if (k1==1) {
        //fgets (l_n, 19, fp2);
        strcpy(afisate,remove_newline(&l_n));
        printf("AFIS_2=%s",afisate);
        printf(".");
     }

     if (k1==2) {
        //fgets (l_n, 19, fp2);
        /*switch (l_n[0])
        {
            case '0': lit_nimerite=0;
            case '1': lit_nimerite=1;
            case '2': lit_nimerite=2;
            case '3': lit_nimerite=3;
            case '4': lit_nimerite=4;
            case '5': lit_nimerite=5;
            case '6': lit_nimerite=6;
            case '7': lit_nimerite=7;
            case '8': lit_nimerite=8;
            case '9': lit_nimerite=9;
        }*/

        lit_nimerite=atoi(remove_newline(&l_n));
        printf("lit_nimerite2=%d",lit_nimerite+1);
     }

     if (k1==3) {
        //fgets (l_n, 19, fp2);

        /*switch (l_n[0])
        {
            case '0': gresite=0;
            case '1': gresite=1;
            case '2': gresite=2;
            case '3': gresite=3;
            case '4': gresite=4;
            case '5': gresite=5;
            case '6': gresite=6;
            case '7': gresite=7;
            case '8': gresite=8;
            case '9': gresite=9;
        }*/

        gresite=atoi(remove_newline(&l_n));
        printf("gresite2=%d",gresite+1);
     }
    }

   fclose(fp2);

  }
    printf("Afisate:%s",afisate);

    do
    {
        printf("Introduceti o litera:\n");
        //ghici=getche();
        scanf("%s",&ghici);
        printf("ghici=%c\n",ghici[0]);
        int incer_reusita=0;

        for(k1=1;k1<nrchar_cuv-1;k1++)
        {
            /*printf("cuv[k1]=%c",cuv[k1]);
            printf("afisate[k1]=%c",afisate[k1]);

            printf("ghici[0]=%c",ghici[0]);*/

            if (cuv[k1]==ghici[0]) {
              if (afisate[k1]=='.') {
                 incer_reusita=1;
                 //printf("*********");
                 ++lit_nimerite;
                 afisate[k1]=ghici[0];
                 printf("Nimerite:%s",afisate);
              }
            }
        }

        if (incer_reusita==0)
              {
                  ++gresite;
                  printf("Greseli:%d ",gresite);

                  if (gresite==greseli_adm) {
                    printf("AI PIERDUT - 6 greseli");
                    sfarsit_joc=2;
                  }
              }

         if (lit_nimerite==nrchar_cuv) {
              printf("AI CASTIGAT, FELICITARI !!!");
              sfarsit_joc=1;
              }


     }
    while (sfarsit_joc==0);



   return 1;
}

#include <stdio.h>
#include <string.h>
int main()
{
int cuv=0,car=0,nr=0,i;
char line[300];
do
{
   gets(line);
   printf("%s",line);
   if((strlen(line)==1)&&line[0]!='1'&&line[0]!='2'&&line[0]!='3'&&line[0]!='4'&&line[0]!='5'&&line[0]!='6'&&line[0]!='7'&&line[0]!='8'&&line[0]!='9')   car++;
   else
   {
       int oknr=1;
       for(i=0;i<strlen(line);i++)
       {
              if (!(line[0]=='-'||line[i]=='1'||line[i]=='2'||line[i]=='3'||line[i]=='4'||line[i]=='5'||line[i]=='6'||line[i]=='7'||line[i]=='8'||line[i]=='9')) oknr=0;
        }
       if(oknr==0) cuv++;
       if(oknr==1) nr++;
   }
} while(!(strlen(line)==3&&line[0]=='E'&&line[1]=='N'&&line[2]=='D'));
printf("%d ",cuv-1); //cuvinte
printf("%d ",car); //caractere
printf("%d ",nr); //numere
return 0;
}


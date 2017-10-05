#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"fonction.h"
#include <time.h>
#define max 100
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sauvgarder_info_chauffeur(info_chauffeur *tete)
{
info_chauffeur *p=tete;

FILE*fc=ouvrir_fichier("info_chauffeur.txt","wb");
if(p==NULL)
printf("\nil n'y'a aucun chauffeur\n");
while(p!=NULL)
{
fwrite(p,sizeof(info_chauffeur),1,fc);
p=p->next;
}
fclose(fc);
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
info_chauffeur*charger_info_chauffeur(date dt,trans_pro*debut)
{
info_chauffeur*p,*tete=NULL;
FILE*fc=ouvrir_fichier("info_chauffeur.txt","rb");
p=(info_chauffeur*)malloc(sizeof(info_chauffeur));
fread(p,sizeof(info_chauffeur),1,fc);
while(!feof(fc))
{
tete=ajouter_chauffeur(debut,tete,p,dt);
p=(info_chauffeur*)malloc(sizeof(info_chauffeur));
fread(p,sizeof(info_chauffeur),1,fc);
}
fclose(fc);
return tete;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
info_chauffeur*inserer_donnees_chauffeur(info_chauffeur*tete)
{
info_chauffeur *d,*p=tete;
char c;
int i=0,k=0,n1,n2;
d=(info_chauffeur*)malloc(sizeof(info_chauffeur));

printf("\n\tinformation du chauffeur\n\n");
printf("Entrer le nom\n");                                       
scanf("%s",d->nom);
do
{
printf("Entrer le matricule\n");
scanf("%s",d->matricule);
k=0;
p=tete;
while(p!=NULL&&k==0)
{
if(strcmp(d->matricule,p->matricule)==0)
{
k=1;
}
p=p->next;
}
if(k==1)
printf("\n\t\tMatricule existe deja veuillez ressayer \n");
}
while(k==1);
printf("Entrer l'adresse\n");
c=getchar();
gets(d->adresse);
do
{
i=0;n1=0;n2=0;
printf("Entrer le numero du telephone\n");
scanf("%s",d->numero);
if((strlen(d->numero)!=10)||(d->numero[0]!='0')||((d->numero[1]!='5')&&(d->numero[1]!='6')))    
n1=1;
while(i<strlen(d->numero)&&n1==0&&n2==0)
{  
 if(d->numero[i]!='0'&&d->numero[i]!='1'&&d->numero[i]!='2'&&d->numero[i]!='3'&&d->numero[i]!='4'&&d->numero[i]!='5'&&d->numero[i]!='6'&&d->numero[i]!='7'&&d->numero[i]!='8'&&d->numero[i]!='9')
{
n2=1;
}
i++;
}
if(n1==1||n2==1)
printf("\n\t\tNumero incorrect veuillez ressayer\n\n");
}
while(n1==1||n2==1);
return d;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

info_chauffeur*ajouter_chauffeur(trans_pro*debut,info_chauffeur*tete,info_chauffeur*ic,date dt)
{
trans_pro *t;
info_chauffeur *p,*d,*a;
t=debut;
p=tete;
int test=test_chauffeur(debut,ic,dt);

if(debut==NULL||test==0)
{
if(tete==NULL)
{
tete=ic;
tete->next=NULL;
return tete;
}
else
{
d=tete;
tete=ic;
ic->next=d;
return tete;
}
}
if(tete==NULL)
{
tete=ic;
tete->next=NULL;
return tete;
}

if(test==1&&test_chauffeur(debut,tete,dt)==1)
{
if(cmp_date(date_prog(debut,ic,dt),date_prog(debut,tete,dt))>0)
{
a=tete;
tete=ic;
tete->next=a;
return tete;
}
}
while(p->next!=NULL)
{
if(test_chauffeur(debut,p->next,dt)==1&&cmp_date(date_prog(debut,ic,dt),date_prog(debut,p->next,dt))>0)
{
d=p->next;
p->next=ic;
ic->next=d;
return tete;
}
else
p=p->next;
}
if(p->next==NULL)
{
p->next=ic;
ic->next=NULL;
return tete;
}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int test_chauffeur(trans_pro*debut,info_chauffeur*ic,date dt)
{
trans_pro*p=debut;
if(debut==NULL)
return 0;
while(p!=NULL)
{
if(strcmp(p->chauffeur.matricule,ic->matricule)==0&&cmp_date(p->dt_trans,dt)>0)
return 1;
p=p->next;
}
if(p==NULL)
return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
date date_prog(trans_pro*debut,info_chauffeur*ic,date dt)
{
trans_pro *p=debut;
while(p!=NULL)
{
if(strcmp(p->chauffeur.matricule,ic->matricule)==0&&cmp_date(p->dt_trans,dt)>0)          
return(p->dt_trans);
p=p->next;
}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void afficher_info_chauffeur(info_chauffeur*tete)
{
int i;
info_chauffeur *p;
p=tete;
if(tete==NULL)
{
printf("La liste est vide\n");
}
else
{
i=1;
while(p!=NULL)
{
printf("\tles information du chauffeur:%d\n\t\t______________________________\n",i);
printf("\t\tNom : %s\n\t\tMatricule : %s\n\t\tAdresse: %s\n\t\tNumero de telephone: %s\n",p->nom,p->matricule,p->adresse,p->numero);    //a modifier
printf("\t\t______________________________\n");
p=p->next;
i++;
}
}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
info_chauffeur*supprimer_chauffeur(info_chauffeur*tete)
{
char matricule[14];
info_chauffeur *p,*a;
p=tete;
printf("Donner le matricule du chauffeur\n");
scanf("%s",matricule);
if(tete==NULL)
{
printf("La liste est vide\n");
return tete;
}
if(strcmp(p->matricule,matricule)==0)
{
a=tete;
tete=a->next;
free(a);
return tete;
}
while(p->next!=NULL&&strcmp(p->next->matricule,matricule)!=0)
p=p->next;
if(strcmp(p->next->matricule,matricule)==0)
{
a=p->next;
p->next=p->next->next;
free(a);
return tete;
}
if(p->next==NULL)
{
printf("\nCe matricule n'existe pas \n\n");
return tete;
}
}

///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void afficher_info_chauffeur_disponible(info_chauffeur*tete,trans_pro*debut)
{
int i=1,k;
info_chauffeur *p;
date *dt1;
printf("\n\tEntrer la date dont vous voulez voir les chauffeurs disponibles\n\n");
dt1=saisir_dat();
trans_pro *t=debut;
p=tete;
if(tete==NULL)
{
printf("La liste est vide\n");
}printf("\n\t\t********************************************************\n\t\tInformations des chauffeur disponible à la date : %d-%d-%d\n\t\t********************************************************\n\n",dt1->jour,dt1->mois,dt1->annee);
while(p!=NULL)
{
k=1;
t=debut;
while(t!=NULL&&k==1)
{
if(strcmp(p->matricule,t->chauffeur.matricule)==0&&cmp_date(t->dt_trans,*dt1)==0)
k=0;
t=t->next;
if(t==NULL&&k==1)
{
printf("\tles information du chauffeur:%d\n\t\t______________________________\n",i);
printf("\t\tNom : %s\n\t\tMatricule : %s\n\t\tAdresse: %s\n\t\tNumero de telephone: %s\n",p->nom,p->matricule,p->adresse,p->numero);            //a modifier
printf("\t\t______________________________\n");
i++;
}
}
p=p->next;
}
if(i==1)
printf("\n\nIl n'y'a pas de chauffeur disponible\n\n");
}

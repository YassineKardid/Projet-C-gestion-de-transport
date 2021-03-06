#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"fonction.h"
#include <time.h>
#define max 100

date date_aujourdhuit(date dt)
{
    time_t secondes;
    struct tm instant;

    time(&secondes);
    instant=*localtime(&secondes);
    dt.jour=instant.tm_mday;
    dt.mois=instant.tm_mon+1;
    dt.annee=instant.tm_year+1900;
    printf("\t\t%d-%d-%d\n", instant.tm_mday, instant.tm_mon+1, instant.tm_year+1900);
    return dt;
}
////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
date*saisir_dat()
{
int t;
date*dt;
dt=(date*)malloc(sizeof(date));
do
{
printf("Enter le jours\n");
scanf("%d",&dt->jour);
printf("Enter le mois\n");
scanf("%d",&dt->mois);
printf("Enter l'annee\n");
scanf("%d",&dt->annee);
t=test_date(*dt);
if(t<0)
printf("\n\t\tDate non correcte veuillez ressayer \n"); 
}
while(t<0);
return dt;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int cmp_date(date dt1,date dt2)   //si dt1<dt2 return -1;si dt1>dt2 return 1; si dt1=dt2 return 0;
{
if(dt1.annee>dt2.annee)
return 1;
if(dt1.annee<dt2.annee)
return(-1);
if((dt1.annee==dt2.annee)&&(dt1.mois>dt2.mois))
return 1;
if((dt1.annee==dt2.annee)&&(dt1.mois<dt2.mois))
return(-1);
if((dt1.annee==dt2.annee)&&(dt1.mois==dt2.mois)&&(dt1.jour>dt2.jour))
return 1;
if((dt1.annee==dt2.annee)&&(dt1.mois==dt2.mois)&&(dt1.jour<dt2.jour))
return(-1);
if((dt1.annee==dt2.annee)&&(dt1.mois==dt2.mois)&&(dt1.jour==dt2.jour))
return 0;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
int test_date(date dt1)
{
if(dt1.mois<0||dt1.mois>12||dt1.jour<0||dt1.annee<0||dt1.jour>31)
return -1;
if(dt1.annee/4!=0&&dt1.mois==2&&dt1.jour>28)
return -1;
if(dt1.annee/4==0&&dt1.mois==2&&dt1.jour>29)
return -1;
if((dt1.mois==4||dt1.mois==6||dt1.mois==9||dt1.mois==11)&&dt1.jour>30)
return -1;
else
return 1;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
FILE*ouvrir_fichier(char*nom,char*mode)
{
FILE*fv=fopen(nom,mode);
if(fv==NULL)
{
printf("\nimpossible d'ouvrir le fichier");
exit(0);
}
return fv;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void sauvgarder_trans_prog(trans_pro *debut)
{int i;
trans_pro *p=debut;

FILE*fg=ouvrir_fichier("trans_programme.txt","wb");
if(p==NULL)
printf("\nil n'y'a aucun transport programme\n");
while(p!=NULL)
{
fwrite(p,sizeof(trans_pro),1,fg);
p=p->next;
}
fclose(fg);
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
trans_pro*charger_trans_pro()
{int j=0;
trans_pro*p,*debut=NULL;
FILE*fg=ouvrir_fichier("trans_programme.txt","rb");
p=(trans_pro*)malloc(sizeof(trans_pro));
fread(p,sizeof(trans_pro),1,fg);
while(!feof(fg))
{
debut=inserer_trans_pro(debut,p);
p=(trans_pro*)malloc(sizeof(trans_pro));
fread(p,sizeof(trans_pro),1,fg);
}
fclose(fg);
return debut;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
info_trajet*saisir_trajet()
{info_trajet *t;
t=(info_trajet*)malloc(sizeof(info_trajet));
printf("\n\t***Entrer les information  de trajet***\n\n");
printf("Entrer le code du trajet\n");
scanf("%s",t->code);
printf("Entrer la ville de depart\n");
scanf("%s",t->ville_depart);
printf("Entrer la ville d'arrive\n");
scanf("%s",t->ville_arrive);
printf("Entrer la distance en (km)\n");
scanf("%d",&t->distance);
return t;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
info_vehicule*affecte_voiture(info_vehicule*ve,trans_pro*debut,int i,date dt1)
{
trans_pro *p;
info_vehicule *w=(info_vehicule*)malloc(sizeof(info_vehicule));
int j,k,l;
if(debut==NULL)
return ve;
j=0;
k=1;
while(j<i)
{
k=1;
p=debut;
while(p!=NULL&&k==1)
{
if(strcmp((ve+j)->numero,p->voiture.numero)==0&&cmp_date(p->dt_trans,dt1)==0)
 k=0;
p=p->next;
if(p==NULL&&k==1)
{
*w=*(ve+j);
while(j<i-1)
{
*(ve+j)=*(ve+j+1);
j++;
}
*(ve+i-1)=*w;
return(w);
}
}
j++;
}
if(j>=i)
{
printf("\nIl n'y'a pas de voiture disponible\n\n");
return NULL;
}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
info_chauffeur*affecte_chauffeur(info_chauffeur*tete,trans_pro*debut,date dt1)
{
int k,l; 
info_chauffeur *p;
trans_pro *t;
p=tete;
if(debut==NULL)
{
return  tete;
}
while(p!=NULL)
{
k=1;
t=debut;
while(t!=NULL&&k==1)
{
if(strcmp(p->matricule,t->chauffeur.matricule)==0&&cmp_date(t->dt_trans,dt1)==0)
k=0;
t=t->next;
if(t==NULL&&k==1)
return p;
}
p=p->next;
}
if(p==NULL)
{
printf("\n\nIl n'y'a pas de chauffeur disponible\n\n");
return NULL;
}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
trans_pro*inserer_trans_pro(trans_pro*debut,trans_pro*TP)
{
trans_pro *p,*d;
p=debut;
if(debut==NULL)
{
debut=TP;                               
debut->next=NULL;
return debut;
}
if(cmp_date(TP->dt_trans,debut->dt_trans)>=0)
{
d=debut;
debut=TP;
TP->next=d;
return debut;
}
while(p->next!=NULL)
{
if(cmp_date(TP->dt_trans,p->next->dt_trans)>=0)
{
d=p->next;
p->next=TP;
TP->next=d;
return debut;
}
p=p->next;
}
if(p->next==NULL)
{
p->next=TP;
TP->next=NULL;
return debut;
}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
trans_pro*programmer_transport(info_chauffeur*tete,info_vehicule*ve,int i,trans_pro*debut)
{
int l;
trans_pro *tp;
date dt;

info_vehicule*v=(info_vehicule*)malloc(sizeof(info_vehicule));
info_chauffeur*c=(info_chauffeur*)malloc(sizeof(info_chauffeur));
tp=(trans_pro*)malloc(sizeof(trans_pro));

printf("\n\tDonner les information du trajet que vous voulez programmer\n\n");
tp->trajet=*(saisir_trajet());
printf("\n\tDonner la date du transport que vous voulez programmer\n\n");
dt=*(saisir_dat());
tp->dt_trans=dt;
v=affecte_voiture(ve,debut,i,dt);
c=affecte_chauffeur(tete,debut,dt);
if(v==NULL)
{
printf("\n\nIl n'y'a pas de voiture disponible\n\n");
return debut;                                        
}
tp->voiture=*v;
if(c==NULL)
{
printf("\n\nIl n'y'a pas de chauffeur disponible\n\n");
return debut;
}
tp->chauffeur=*c;
debut=inserer_trans_pro(debut,tp);
return debut;
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void afficher_trans_dt_donnee(trans_pro*debut)
{
int k=1;
trans_pro*p;
date*dt;
p=debut;
if(p==NULL)
printf("\nil n'y'a aucun transport programme\n");
printf("\tEntrer la date dont vous voulez voir les details des tansports\n");
dt=saisir_dat();
printf("\n\t\t******************************\n\t\tDate de transport : %d-%d-%d\n\t\t******************************\n",dt->jour,dt->mois,dt->annee);
while(p!=NULL)
{
if(cmp_date(p->dt_trans,*dt)==0)
{
printf("\n\t\t=Information du transport:%d=\n\n",k);


printf("\t\tNom du chauffeur: %s\n",p->chauffeur.nom);
printf("\t\tMatricule du vehicule: %s\n\n",p->voiture.numero);
printf("\t\t****Information du trajet****\n\t\t______________________________\n\n");
printf("\t\tCode du trajet : %s\n\t\tVille de depart: %s\n\t\tVille d'arrive: %s\n\t\tDistance:%d km\n",p->trajet.code,p->trajet.ville_depart,p->trajet.ville_arrive,p->trajet.distance);
printf("\t\t______________________________\n\n");
k++;
}
p=p->next;
}
if(k==1)
printf("\n\n\tIl n'y' aucun transport programme dans cette date\n\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void afficher_trans_effectue(trans_pro*debut,date dt)
{
trans_pro*p;
int k=1;
p=debut;
while(p!=NULL)
{
if(cmp_date(p->dt_trans,dt)<0)
{
printf("\n================Information du transport effectue n°:%d===================\n\n",k);
printf("\t\tDate de transport : %d-%d-%d\n",p->dt_trans.jour,p->dt_trans.mois,p->dt_trans.annee);
printf("\t\t============================\n\n");
printf("\t\t****Informations du chauffeur****\n\t\t______________________________\n");
printf("\t\tNom: %s\n\t\tMatricule : %s\n\t\tAdresse: %s\n\t\tNumero de telephone: %s\n",p->chauffeur.nom,p->chauffeur.matricule,p->chauffeur.adresse,p->chauffeur.numero);
printf("\t\t______________________________\n\n");
printf("\t\t****Information du vehicule****\n\t\t______________________________\n");
printf("\t\tNumero de vehicule : %s\n\t\tMarque du vehicule: %s\n\t\tNombre de passagers: %d\n",p->voiture.numero,p->voiture.marque,p->voiture.nbr_passagers);
printf("\t\tDate d'achat : %d-%d-%d\n",p->voiture.dat_achat.jour,p->voiture.dat_achat.mois,p->voiture.dat_achat.annee);
printf("\t\t______________________________\n\n");
printf("\t\t****Information du trajet****\n\t\t______________________________\n");
printf("\t\tCode du trajet : %s\n\t\tVille de depart: %s\n\t\tVille d'arrive: %s\n\t\tDistance:%d km\n",p->trajet.code,p->trajet.ville_depart,p->trajet.ville_arrive,p->trajet.distance);
printf("\t\t______________________________\n\n");
k++;
}
p=p->next;
}
if(k==1)
printf("\n\tIl n'y' aucun transport effectue\n\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void afficher_trans_courant(trans_pro*debut,date dt)
{
trans_pro*p;
int k=1;
p=debut;
while(p!=NULL)
{
if(cmp_date(p->dt_trans,dt)==0)
{
printf("\n================Information du transport courant n°:%d===================\n\n",k);
printf("\t\tDate de transport : %d-%d-%d\n",p->dt_trans.jour,p->dt_trans.mois,p->dt_trans.annee);
printf("\t\t============================\n\n");
printf("\t\t****Informations du chauffeur****\n\t\t______________________________\n");
printf("\t\tNom: %s\n\t\tMatricule : %s\n\t\tAdresse: %s\n\t\tNumero de telephone: %s\n",p->chauffeur.nom,p->chauffeur.matricule,p->chauffeur.adresse,p->chauffeur.numero);
printf("\t\t______________________________\n\n");
printf("\t\t****Information du vehicule****\n\t\t______________________________\n");
printf("\t\tNumero de vehicule : %s\n\t\tMarque du vehicule: %s\n\t\tNombre de passagers: %d\n",p->voiture.numero,p->voiture.marque,p->voiture.nbr_passagers);
printf("\t\tDate d'achat : %d-%d-%d\n",p->voiture.dat_achat.jour,p->voiture.dat_achat.mois,p->voiture.dat_achat.annee);
printf("\t\t______________________________\n\n");
printf("\t\t****Information du trajet****\n\t\t______________________________\n");
printf("\t\tCode du trajet : %s\n\t\tVille de depart: %s\n\t\tVille d'arrive: %s\n\t\tDistance:%d km\n",p->trajet.code,p->trajet.ville_depart,p->trajet.ville_arrive,p->trajet.distance);
printf("\t\t______________________________\n\n");
k++;
}
p=p->next;
}
if(k==1)
printf("\n\tIl n'y' aucun transport en courant\n\n");
}
//////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void afficher_tarns_prevu(trans_pro*debut,date dt)
{
trans_pro*p;
int k=1;
p=debut;
while(p!=NULL)
{
if(cmp_date(p->dt_trans,dt)>0)
{
printf("\n================Information du transport prevu n°:%d===================\n\n",k);
printf("\t\tDate de transport : %d-%d-%d\n",p->dt_trans.jour,p->dt_trans.mois,p->dt_trans.annee);
printf("\t\t============================\n\n");
printf("\t\t****Informations du chauffeur****\n\t\t______________________________\n");
printf("\t\tNom: %s\n\t\tMatricule : %s\n\t\tAdresse: %s\n\t\tNumero de telephone: %s\n",p->chauffeur.nom,p->chauffeur.matricule,p->chauffeur.adresse,p->chauffeur.numero);
printf("\t\t______________________________\n\n");
printf("\t\t****Information du vehicule****\n\t\t______________________________\n");
printf("\t\tNumero de vehicule : %s\n\t\tMarque du vehicule: %s\n\t\tNombre de passagers: %d\n",p->voiture.numero,p->voiture.marque,p->voiture.nbr_passagers);
printf("\t\tDate d'achat : %d-%d-%d\n",p->voiture.dat_achat.jour,p->voiture.dat_achat.mois,p->voiture.dat_achat.annee);
printf("\t\t______________________________\n\n");
printf("\t\t****Information du trajet****\n\t\t______________________________\n");
printf("\t\tCode du trajet : %s\n\t\tVille de depart: %s\n\t\tVille d'arrive: %s\n\t\tDistance:%d km\n",p->trajet.code,p->trajet.ville_depart,p->trajet.ville_arrive,p->trajet.distance);
printf("\t\t______________________________\n\n");
k++;
}
p=p->next;
}
if(k==1)
printf("\n\til n'y' aucun transport prevu\n\n");
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
trans_pro*annuler_trans(trans_pro*debut,date dt)    // dt: date d'aujourd'huit
{
char matricule[14],code[16];
int i,k=0;
date dt1;
trans_pro *p=debut,*a;
printf("\nDonner le matricule du chauffeur\n");
scanf("%s",matricule);
printf("Entrer la date du tranport\n");
dt1=*saisir_dat();
if(debut==NULL)
{
printf("La liste est vide\n");
return debut;
}
if((strcmp(p->chauffeur.matricule,matricule)==0)&&(cmp_date(p->dt_trans,dt1)==0))
{
a=debut;
debut=a->next;
free(a);
return debut;
}
while((p->next!=NULL)&&(k==0))
{

if(strcmp(p->next->chauffeur.matricule,matricule)==0&&cmp_date(p->next->dt_trans,dt1)==0)
{
k=1;
}
else
p=p->next;
}
if(p->next==NULL&&k==0)
{
printf("\n\n\tles informations que vous avez entree sont incorrects\n\n");
return debut;
}
if(k==1)
{
a=p->next;
p->next=p->next->next;
free(a);
return debut;
}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void afficher_tous_trans(trans_pro*debut)
{
int k=1;
trans_pro*p;
p=debut;
if(p==NULL)
printf("\nil n'y'a aucun transport programme\n");
while(p!=NULL)
{
printf("\n================Information du transport:%d===================\n\n",k);
printf("\t\tDate de transport : %d-%d-%d\n",p->dt_trans.jour,p->dt_trans.mois,p->dt_trans.annee);
printf("\t\t============================\n\n");
printf("\t\t****Informations du chauffeur****\n\t\t______________________________\n");
printf("\t\tMatricule : %s\n\t\tAdresse: %s\n\t\tNumero de telephone: %s\n",p->chauffeur.matricule,p->chauffeur.adresse,p->chauffeur.numero);
printf("\t\t______________________________\n\n");
printf("\t\t****Information du vehicule****\n\t\t______________________________\n");
printf("\t\tNumero de vehicule : %s\n\t\tMarque du vehicule: %s\n\t\tNombre de passagers: %d\n",p->voiture.numero,p->voiture.marque,p->voiture.nbr_passagers);
printf("\t\tDate d'achat : %d-%d-%d\n",p->voiture.dat_achat.jour,p->voiture.dat_achat.mois,p->voiture.dat_achat.annee);
printf("\t\t______________________________\n\n");
printf("\t\t****Information du trajet****\n\t\t______________________________\n");
printf("\t\tCode du trajet : %s\n\t\tVille de depart: %s\n\t\tVille d'arrive: %s\n\t\tDistance:%d km\n",p->trajet.code,p->trajet.ville_depart,p->trajet.ville_arrive,p->trajet.distance);
printf("\t\t______________________________\n\n");
k++;
p=p->next;
}
}
///////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
void detaille_trans(trans_pro*debut)  //pour connaitre le transport il faut entrer le matricule du chauffeur et la date du voyage
{
char matricule[14];
int k=1;
trans_pro*p;
date*dt;
p=debut;
if(p==NULL)
printf("\nil n'y'a aucun transport programme\n\n");
printf("\t¤¤Entrer le matricule du chauffeur qui fait le voyage dont vous voulez voir les detaills¤¤\n");
scanf("%s",matricule);
printf("\tentrer la date de ce transport\n");
dt=saisir_dat();
while(p!=NULL&&k!=2)
{
if(cmp_date(p->dt_trans,*dt)==0&&strcmp(matricule,p->chauffeur.matricule)==0)
{
printf("\n\t=============Detailles du transport==============\n\n");
printf("\t\tDate de transport : %d-%d-%d\n",p->dt_trans.jour,p->dt_trans.mois,p->dt_trans.annee);
printf("\t\t============================\n\n");
printf("\t\t****Informations du chauffeur****\n\t\t______________________________\n");
printf("\t\tNom : %s\n\t\tMatricule : %s\n\t\tAdresse: %s\n\t\tNumero de telephone: %s\n",p->chauffeur.nom,p->chauffeur.matricule,p->chauffeur.adresse,p->chauffeur.numero);
printf("\t\t______________________________\n\n");
printf("\t\t****Information du vehicule****\n\t\t______________________________\n");
printf("\t\tNumero de vehicule : %s\n\t\tMarque du vehicule: %s\n\t\tNombre de passagers: %d\n",p->voiture.numero,p->voiture.marque,p->voiture.nbr_passagers);
printf("\t\tDate d'achat : %d-%d-%d\n",p->voiture.dat_achat.jour,p->voiture.dat_achat.mois,p->voiture.dat_achat.annee);
printf("\t\t______________________________\n\n");
printf("\t\t****Information du trajet****\n\t\t______________________________\n");
printf("\t\tCode du trajet : %s\n\t\tVille de depart: %s\n\t\tVille d'arrive: %s\n\t\tDistance:%d km\n",p->trajet.code,p->trajet.ville_depart,p->trajet.ville_arrive,p->trajet.distance);
printf("\t\t______________________________\n\n");
k++;
}
p=p->next;
}
if(k==1)
printf("\n\n\tIl n'y' aucun transport a les memes donnees\n\n");
}



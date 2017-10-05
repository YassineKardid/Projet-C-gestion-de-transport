#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"fonction.h"
#include <time.h>
#define max 100
main()
{
int i=0,c,z=0;
info_vehicule *ve;
info_chauffeur *tete;
date dt;
printf("\n\t\t**Date d'aujourd'hui**\n");
dt=date_aujourdhuit(dt);
trans_pro *debut;
tete=NULL;
debut=NULL;
ve=(info_vehicule*)malloc(max*sizeof(info_vehicule));
debut=charger_trans_pro();
tete=charger_info_chauffeur(dt,debut);
i=charger_info_vehicule(ve); 
do
{

printf("\n\t\t¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤ MENU ¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤\n\t\t-Entrer '1'  pour ajouter un nouveau chauffeur\n\n\t\t-Entrer '2'  pour ajouter un nouveau vehicule\n\n\t\t-Entrer '3'  pour supprimer un chauffeur\n\n\t\t-Entrer '4'  pour programmer un transport\n\n\t\t-Entrer '5'  pour afficher les voitures\n\t\t             disponibles a une date donnee\n\n\t\t-Entrer '6'  pour afficher tous les vehicules\n\n\t\t-Entrer '7'  pour afficher les chauffeurs\n\t\t\t     disponibles a une date donnee\n\n\t\t-Entrer '8'  pour afficher tous les chauffeurs\n\n\t\t-Entrer '9'  pour afficher les transports\n\t\t\t     effectues a une date donnee\n\n\t\t-Entrer '10' pour afficher les transports effectues\n\n\t\t-Entrer '11' pour afficher les transports courants\n\n\t\t-Entrer '12' pour afficher les transports prevus\n\n\t\t-Entrer '13' pour annuler un transport\n\n\t\t-entrer '14' pour voir les details d'un voyage\n\n\t\t-Entrer '15' pour sortir \n\t\t¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤¤\n");
do
{
scanf("%d",&c);
if(c<1||c>16)
printf("\n\tEntrer seulement les nombres compris entre  '1' et '16'\n\n");
}
while(c<1||c>16);
switch(c)
{
case 1 :tete=ajouter_chauffeur(debut,tete,inserer_donnees_chauffeur(tete),dt);break;
case 2 :i=ajouter_vehicule(i,ve);break;
case 3 :{
        tete=supprimer_chauffeur(tete);
        sauvgarder_info_chauffeur(tete);
        tete=charger_info_chauffeur(dt,debut);break;
        }
case 4 :{
         debut=programmer_transport(tete,ve,i,debut);
         sauvgarder_info_chauffeur(tete);
         tete=charger_info_chauffeur(dt,debut);break;
        } 
case 5  :afficher_vehicule_disponible(i,ve,debut);break; 
case 6  :afficher_vehicule(i,ve);break;
case 7  :afficher_info_chauffeur_disponible(tete,debut);break;
case 8  :afficher_info_chauffeur(tete);break;
case 9  :afficher_trans_dt_donnee(debut);break;
case 10 :afficher_trans_effectue(debut,dt);break;
case 11 :afficher_trans_courant(debut,dt);break;
case 12 :afficher_tarns_prevu(debut,dt);break;
case 13 :debut=annuler_trans(debut,dt); break;
case 14 :detaille_trans(debut);break;
case 15 :z=1;break;
case 16 :afficher_tous_trans(debut);break;
} 
}
while(z==0);
sauvgarder_trans_prog(debut);
sauvgarder_info_vehicule(ve,i);
sauvgarder_info_chauffeur(tete);
}


typedef struct date
{
int annee;
int mois;
int jour;
}date;
typedef struct information_du_vehicule
{
char numero[12];
char marque[12];
date dat_achat;
int nbr_passagers;
}info_vehicule;

typedef struct information_du_chauffeur
{
char nom[20];
char matricule[14];
char adresse[60];
char numero[14];
struct information_du_chauffeur*next;
}info_chauffeur;

typedef struct information_du_trajet
{
char code[14];
char ville_depart[14];
char ville_arrive[14];
int distance;
}info_trajet;

typedef struct transport_programmee
{
info_vehicule voiture;
info_chauffeur chauffeur; 
info_trajet trajet;
date dt_trans;
struct transport_programmee*next;
}trans_pro;
//////////////////////////////////////////////////
date*saisir_dat();
date date_aujourdhuit(date);
int test_date(date);
int ajouter_vehicule(int,info_vehicule*);
void afficher_vehicule(int,info_vehicule*);
info_chauffeur*inserer_donnees_chauffeur(info_chauffeur*tete);
void afficher_info_chauffeur(info_chauffeur*);
info_chauffeur*supprimer_chauffeur(info_chauffeur*);
info_trajet*saisir_trajet();
trans_pro*programmer_transport(info_chauffeur*,info_vehicule*,int,trans_pro*);
info_chauffeur*affecte_chauffeur(info_chauffeur*,trans_pro*,date);
info_vehicule*affecte_voiture(info_vehicule*,trans_pro*,int,date);
trans_pro*inserer_trans_pro(trans_pro*,trans_pro*);
void afficher_tous_trans(trans_pro*);
int cmp_date(date,date);
void afficher_trans_effectue(trans_pro*,date);
void afficher_trans_courant(trans_pro*,date);
void afficher_tarns_prevu(trans_pro*,date);
trans_pro*annuler_trans(trans_pro*,date);
void afficher_info_chauffeur_disponible(info_chauffeur*,trans_pro*);
void afficher_vehicule_disponible(int,info_vehicule *,trans_pro*);
void sauvgarder_info_vehicule(info_vehicule*,int);
int charger_info_vehicule(info_vehicule*);
FILE*ouvrir_fichier(char*,char*);
info_chauffeur*charger_info_chauffeur(date,trans_pro*);
void sauvgarder_trans_prog(trans_pro*);
trans_pro*charger_trans_pro();
date date_prog(trans_pro*,info_chauffeur*,date);
int test_chauffeur(trans_pro*,info_chauffeur*,date);
info_chauffeur*ajouter_chauffeur(trans_pro*debut,info_chauffeur*tete,info_chauffeur*ic,date);
void afficher_trans_dt_donnee(trans_pro*);
void detaille_trans(trans_pro*);


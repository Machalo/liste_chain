#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>
#include "liste_stack.c"


char noms[10][20] = {"Frostfall","Hammercloak","Goldenstone","Oakenshield","Bloodrock","Ambershaper","Magmabrew","Blessedfoot","Granitebasher","Copperhood"};
char prenom_m[10][20] = {"Valen  ","Yumol  ","Brandrur","Dedrak ","Botdrok","Hakunli","Sirdur ","Kissem ","Dhormeth","Nonur  "};
char prenom_f[10][20] = {"Lofrurika","Vondroula","Hukhisli","Hubolda","Honwiserd","Thurbirgit","Azeda  ","Lonotryd","Mastigit","Lokhuna"};
char sexe[2][3] = {"M","F"};
char classe[5][20] = {"Guerrier","Prêtre  ","Paladin ","Voleur  ","Chasseur"};
int guerrier[3] = {6,1,3};
int pretre[3] = {2,6,2};
int paladin[3] = {5,3,2};
int voleur[3] = {2,2,6};
int chasseur[3] = {3,2,5};


char *creationNom();

typedef struct SexeEtPrenom
{
    char sexe[4];
    char prenom[13];
}SexeEtPrenom;

struct SexeEtPrenom creaSexePrenom()
{
    struct SexeEtPrenom sexePrenomPerso;

    char y = rand() %2;
    char *sexe_perso;

    sexe_perso = sexe[y];

    strcpy(sexePrenomPerso.sexe, sexe_perso);

    int x = rand() %10;
    int z = rand() %10;    
    char *prenom_perso = "";


    if (sexe_perso == sexe[0])
    {
        prenom_perso = prenom_m[x];
    }
    if (sexe_perso == sexe[1])
    {
        prenom_perso = prenom_f[z];
    }

    strcpy(sexePrenomPerso.prenom, prenom_perso);

    return sexePrenomPerso;
}

char *creationNom()
{
    char *nom_perso ="";
    int w = rand() %10;

    nom_perso = noms[w];

    return nom_perso;
}

typedef struct ClasseEtStats 
{
    char classe[20];
    int niveau;
    int intel;
    int force;
    int agi;
    int pv;
    int pm;
}ClasseEtStats;

struct ClasseEtStats creaStats()
{
    struct ClasseEtStats statsPerso;

    int c = rand() %5;
    char *classe_perso = classe[c];

    strcpy(statsPerso.classe, classe_perso);

    int niv = (rand() %9) +1;


    statsPerso.niveau = niv;
    

    if (classe_perso == classe[0])
    {
        statsPerso.intel = guerrier[1]*niv;
        statsPerso.force = guerrier[0]*niv;
        statsPerso.agi = guerrier[2]*niv;
    }

    if (classe_perso == classe[1])
    {
        statsPerso.intel = pretre[1]*niv;
        statsPerso.force = pretre[0]*niv;
        statsPerso.agi = pretre[2]*niv;
    }

    if (classe_perso == classe[2])
    {
        statsPerso.intel = paladin[1]*niv;
        statsPerso.force = paladin[0]*niv;
        statsPerso.agi = paladin[2]*niv;
    }

    if (classe_perso == classe[3])
    {
        statsPerso.intel = voleur[1]*niv;
        statsPerso.force = voleur[0]*niv;
        statsPerso.agi = voleur[2]*niv;
    }

    if (classe_perso == classe[4])
    {
        statsPerso.intel = chasseur[1]*niv;
        statsPerso.force = chasseur[0]*niv;
        statsPerso.agi = chasseur[2]*niv;
    }

    int pvPerso = niv*10 + statsPerso.force*2;
    int pmPerso = niv*5 + statsPerso.intel*2;

    statsPerso.pv = pvPerso;
    statsPerso.pm = pmPerso;
    
    
    return statsPerso;
}

int main(int argc, char *argv[])
{
    srand(time(0));
    int num;
    char *p;

    errno = 0;
    long conv = 0;

    if (argv[1] != NULL )
    {
        conv = strtol(argv[1], &p, 10);
    }
    else 
    {
        printf("Erreur : entrez un nombre entier compris entre 1 et 20 s'il vous plaît.\n");
        return 0;

    }
 

    if (errno != 0 || *p != '\0' || conv > 20 || conv <= 0 )
    {
        printf("Erreur : entrez un nombre entier compris entre 1 et 20 s'il vous plaît.\n");
        return 0;
    }
    else
        num = conv;

    int rCode=0;
    ListPerso_T *listHead = NULL;

        for (size_t i = 0; i < num; i++)
    {
        struct ClasseEtStats statsFinal = creaStats();
        struct SexeEtPrenom sEtPFinal = creaSexePrenom();
        rCode=LIST_InsertHeadNode(&listHead, sEtPFinal.sexe, creationNom(), sEtPFinal.prenom, statsFinal.classe, statsFinal.niveau, statsFinal.intel, statsFinal.force, statsFinal.agi, statsFinal.pv, statsFinal.pm);
        if(rCode)
        {
            fprintf(stderr, "LIST_InsertHeadNode() reports: %d\n", rCode);
            goto CLEANUP;
        }

    }

    rCode=PrintListPayloads(listHead);
    if(rCode)
      {
      fprintf(stderr, "PrintListPayloads() reports: %d\n", rCode);
      goto CLEANUP;
      }

    CLEANUP:

    if(listHead)
    {
        int rc=LIST_Destroy(&listHead);
        if(rc)
        {
            fprintf(stderr, "LIST_Destroy() reports: %d\n", rc);
            if(!rCode)
            rCode=rc;
        }
    }

   return(rCode);

}
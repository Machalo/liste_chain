#include <stdio.h>
#include <errno.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>

typedef struct Personnage
{
    char sexe[5];
    char nom[15];
    char prenom[15];
    char classe[10];
    int niveau;
    int intel;
    int force;
    int agi;
    int pv;
    int pm;
} Personnage_T;

typedef struct ListPerso
{
    /* Next-node pointer */
    struct ListPerso *next;     /* pointer to the next node in the list. */
    Personnage_T      payload;  /* Data Payload (defined by coder) */
} ListPerso_T;

int LIST_InsertHeadNode(
    ListPerso_T **IO_head,
    char *I_sexe,
    char *I_nom,
    char *I_prenom,
    char *I_classe,
    int I_niveau,
    int I_intel,
    int I_force,
    int I_agi,
    int I_pv,
    int I_pm
    )
{
   int rCode=0;
   ListPerso_T *newNode = NULL;

   /* Allocate memory for new node (with its payload). */
   newNode=malloc(sizeof(*newNode));
   if(NULL == newNode)
      {
      rCode=ENOMEM;   /* ENOMEM is defined in errno.h */
      fprintf(stderr, "malloc() failed.\n");
      goto CLEANUP;                        
      }

   /* Initialize the new node's payload. */
   snprintf(newNode->payload.sexe, sizeof(newNode->payload.sexe), "%s", I_sexe);
   snprintf(newNode->payload.nom, sizeof(newNode->payload.nom), "%s", I_nom);
   snprintf(newNode->payload.prenom, sizeof(newNode->payload.prenom), "%s", I_prenom);
   snprintf(newNode->payload.classe, sizeof(newNode->payload.classe), "%s", I_classe);
   newNode->payload.niveau = I_niveau;
   newNode->payload.intel = I_intel;
   newNode->payload.force = I_force;
   newNode->payload.agi = I_agi;
   newNode->payload.pv = I_pv;
   newNode->payload.pm = I_pm;

   /* Link this node into the list as the new head node. */
   newNode->next = *IO_head;
   *IO_head = newNode;

CLEANUP:

   return(rCode);
}

int PrintListPayloads(
    ListPerso_T *head
    )
{
   int rCode=0;
   ListPerso_T *cur = head;
   int nodeCnt=0;
   printf("Sexe Nom\t \tPrenom\t\tClasse Niveau\tIntel Force Agi PV PM\n");

   while(cur)
    {
      ++nodeCnt;
      printf("%s    %s  \t%s \t%s %d\t %d\t %d\t %d\t %d\t %d\n",
            cur->payload.sexe,
            cur->payload.nom,
            cur->payload.prenom,
            cur->payload.classe,
            cur->payload.niveau,
            cur->payload.intel,
            cur->payload.force,
            cur->payload.agi,
            cur->payload.pv,
            cur->payload.pm
            );
       cur=cur->next;
    }


   return(rCode);
}

int LIST_Destroy(
      ListPerso_T **IO_head
      )
   {
   int rCode=0;

   while(*IO_head)
      {
      ListPerso_T *delNode = *IO_head;
   
      *IO_head = (*IO_head)->next;   
      free(delNode);
      }
   
   return(rCode);
   }
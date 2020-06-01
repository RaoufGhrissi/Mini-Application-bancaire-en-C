#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define CMAX 10

int x,y,z;
typedef struct SClient
{
  int Code_cli;
  char Nom[CMAX];
  char Prenom[CMAX];
}SClient;

typedef struct Date
{
    int Jour;
    int Mois;
    int Annee;
}Date;

typedef struct SCompte
{
    int Code_cpt;
    int Code_cli;
    struct Date d_compte;
}SCompte;

int cmpstr(const void* a, const void* b)
{
    const SClient *c1 = a;
    const SClient *c2 = b;
    return strcmp(c1->Nom, c2->Nom);
}

SClient clients[20];
SCompte comptes[20];

void menu()
{
    printf("1- Gestion des clients\n");
    printf("2- Gestion des comptes\n");
    printf("3- Gestion des operations\n");
    printf("4- Quitter le programme\n");
    printf("Veuillez choisir un numero : ");
    scanf("%d",&x);
    sous_menu(x);
}
void sous_menu(int a)
{
    if (a==1)
    {
        printf("1- Ajouter client\n");
        printf("2- Modifier client\n");
        printf("3- supprimer client\n");
        printf("4- Afficher la liste des clients par order alphabetique\n");
        printf("Veuillez choisir un numero : ");
        scanf("%d",&y);
        gerer_client(y);
    }
    else if (a==2)
    {
        printf("1- Creer un compte\n");
        printf("2- Rechercher un compte\n");
        printf("3- Afficher la liste des comptes\n");
        printf("4- Supprimer un compte\n");
        printf("Veuillez choisir un numero : ");
        scanf("%d",&y);
        gerer_compte(y);
    }
    else if (a==3)
    {
        printf("1- Retrait d'argent\n");
        printf("2- Afficher le compte apr�s l'operation\n");
        printf("Veuillez choisir un numero : ");
        scanf("%d",&y);
        //operation(y);
    }
    else
        return 0 ;
}

void gerer_client(int a)
{
    if (a==1)
    {
        struct SClient client;
        FILE *outfile;

        printf("Code Client : ");
        scanf("%d", &client.Code_cli);
        printf("Nom : ");
        scanf("%s", &client.Nom);
        printf("Prenom : ");
        scanf("%s", &client.Prenom);

        outfile = fopen("client.txt", "a");
        fwrite (&client, sizeof(client), 1, outfile);
        if(fwrite != 0)
            printf("client ajoute avec succes !\n");
        else
            printf("erreur! veuillez ajouter le client de nouveau !\n");

        fclose(outfile);
    }
    else if (a==2)
    {
        struct SClient client;
        struct SClient nvClient;
        FILE *infile;

        printf("Code Client a modifier: ");
        scanf("%d", &nvClient.Code_cli);
        printf("Nouveau Nom : ");
        scanf("%s", &nvClient.Nom);
        printf("Nouveau Prenom : ");
        scanf("%s", &nvClient.Prenom);

        infile = fopen("client.txt", "r");
        int start = 0 ;
        while(fread(&client, sizeof(struct SClient), 1, infile)){
            clients[start] = client;
            start ++ ;
        }
        fclose(infile);
        remove("client.txt");
        FILE *outfile;
        outfile = fopen("modifier.txt", "a");
        for (int i=0 ; i<start ; i++)
        {
            if (clients[i].Code_cli == nvClient.Code_cli)
                fwrite(&nvClient, sizeof(nvClient), 1, outfile);
            else
                fwrite (&clients[i], sizeof(clients[i]), 1, outfile);
        }
        fclose(outfile);
        rename("modifier.txt","client.txt");
    }
    else if (a==3)
    {
        FILE *infile;
        printf("Code Client a modifier : ");
        int code;
        scanf("%d", &code);
        struct SClient client;
        infile = fopen ("client.txt", "r");
        int start = 0 ;
        while(fread(&client, sizeof(struct SClient), 1, infile)){
            clients[start] = client;
            start ++ ;
        }
        fclose(infile);
        remove("client.txt");
        FILE *outfile;
        outfile = fopen("modifier.txt", "a");
        for (int i=0 ; i<start ; i++)
        {
            if (clients[i].Code_cli != code)
                fwrite (&clients[i], sizeof(clients[i]), 1, outfile);
        }
        fclose(outfile);
        rename("modifier.txt","client.txt");
    }
    else if (a==4)
    {
        FILE *infile;
        struct SClient client;
        infile = fopen ("client.txt", "r");
        int start = 0 ;
        while(fread(&client, sizeof(struct SClient), 1, infile)){
            clients[start] = client;
            start ++ ;
        }
        fclose (infile);
        qsort(clients, start, sizeof(SClient), cmpstr);
        for (int i=0 ; i<start ; i++)
        {
            printf("\nCode Client: %d", clients[i].Code_cli);
            printf("\nNom: %s %s", clients[i].Nom, clients[i].Prenom);
            printf("\n");
        }
    }
}

void gerer_compte(int a)
{
    if (a==1)
    {
        struct SCompte compte;
        FILE *outfile;

        printf("Code Compte : ");
        scanf("%d", &compte.Code_cpt);
        printf("Code Client: ");
        scanf("%d", &compte.Code_cli);
        printf("Date de creation du compte | ");
        printf("Jour : ");
        scanf("%d", &compte.d_compte.Jour);
        printf("Mois : ");
        scanf("%d", &compte.d_compte.Mois);
        printf("Annee : ");
        scanf("%d", &compte.d_compte.Annee);

        outfile = fopen("compte.txt", "a");
        fwrite (&compte, sizeof(compte), 1, outfile);
        if(fwrite != 0)
            printf("compte ajoute avec succes !\n");
        else
            printf("erreur! veuillez ajouter le client de nouveau !\n");

        fclose(outfile);
    }
    else if (a==2)
    {
        struct SCompte compte;
        FILE *infile;
        int code;
        printf("Code compte a rechercher: ");
        scanf("%d", &code);

        infile = fopen("compte.txt", "r");
        while(fread(&compte, sizeof(struct SCompte), 1, infile)){
            if (compte.Code_cpt == code)
            {
                printf("\nCode compte: %d", compte.Code_cpt);
                printf("\nCode client: %d", compte.Code_cli);
                printf("\nDate : %d/%d/%d", compte.d_compte.Jour, compte.d_compte.Mois, compte.d_compte.Annee);
            }
        }
        fclose(infile);
    }
    else if (a==3)
    {
        struct SCompte compte;
        FILE *infile;
        infile = fopen("compte.txt", "r");
        while(fread(&compte, sizeof(struct SCompte), 1, infile))
            {
                printf("\nCode compte: %d", compte.Code_cpt);
                printf("\nCode client: %d", compte.Code_cli);
                printf("\nDate : %d/%d/%d", compte.d_compte.Jour, compte.d_compte.Mois, compte.d_compte.Annee);
                printf("\n");
            }
        fclose(infile);
    }
    else if (a==4)
    {
        FILE *infile;
        printf("Code compte a supprimer : ");
        int code;
        scanf("%d", &code);
        struct SCompte compte;
        infile = fopen ("compte.txt", "r");
        int start = 0 ;
        while(fread(&compte, sizeof(struct SCompte), 1, infile)){
            comptes[start] = compte;
            start ++ ;
        }
        fclose(infile);
        remove("compte.txt");
        FILE *outfile;
        outfile = fopen("modifier.txt", "a");
        for (int i=0 ; i<start ; i++)
        {
            if (comptes[i].Code_cpt != code)
                fwrite (&comptes[i], sizeof(comptes[i]), 1, outfile);
        }
        fclose(outfile);
        rename("modifier.txt","compte.txt");
    }
}
int main()
{
    menu();
    return 0;
}

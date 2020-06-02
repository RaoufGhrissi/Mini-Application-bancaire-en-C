#include <stdio.h>
#include <stdlib.h>
#define CMAX 10

int solde,choix,x;
typedef struct SClient
{
    int Code_cli;
    char Nom[CMAX];
    char Prenom[CMAX];
}SClient;

int comparer (const void* a, const void* b)
{
    const SClient *c1 = a ;
    const SClient *c2 = b ;
    return strcmp(c1->Nom, c2->Nom);
}

typedef struct Date
{
    int Jour;
    int Mois;
    int Annee;
}Date;

typedef struct SCompte
{
    int code_cpt;
    int Code_cli;
    int somme;
    struct Date d_compte;
}SCompte;

SClient clients[20];
SCompte comptes[20];

void menu()
{
    printf("1- Gestion des clients\n");
    printf("2- Gestion des comptes\n");
    printf("3- Gestion des operations\n");
    printf("4- Quitter le programme\n");
    printf("Choisir le menu : ");
    scanf("%d", &choix);
    sous_menu(choix);
}

void sous_menu(int a)
{
    if (a==1)
    {
        printf("1- Ajouter\n");
        printf("2- Modifier\n");
        printf("3- Supprimer\n");
        printf("4- Afficher\n");
        printf("5- Retour\n");
        printf("Choisir un sous menu : ");
        scanf("%d", &x);
        gerer_client(x);
    }
    else if (a==2)
    {
        printf("1- Ajouter\n");
        printf("2- Rechercher\n");
        printf("3- Afficher la liste\n");
        printf("4- Supprimer\n");
        printf("5- Retour\n");
        printf("Choisir un sous menu : ");
        scanf("%d", &x);
        gerer_compte(x);
    }
    else if (a==3)
    {
        printf("1- Retrait\n");
        printf("2- Versement d'argent\n");
        printf("Choisir un sous menu : ");
        scanf("%d", &x);
        gerer_operation(x);
    }
    else if (a==4)
        return 0;
    else
    {
        printf("mauvaix choix");
        return 0;
    }
}

void gerer_client(int a)
{
    if (a==1)
    {
        struct SClient client;
        FILE *file;

        printf("Code Client : ");
        scanf("%d", &client.Code_cli);
        printf("Nom : ");
        scanf("%s", &client.Nom);
        printf("Prenom : ");
        scanf("%s", &client.Prenom);

        file = fopen("client.txt", "a");
        fwrite(&client, sizeof(client), 1, file);

        if(fwrite != 0)
            printf("client ajoute avec succes");
        else
            printf("erreur");
        fclose(file);
    }
    else if (a==2)
    {
        struct SClient client;
        struct SClient nvClient;
        FILE *file;

        printf("Code Client a modifier : ");
        scanf("%d", &nvClient.Code_cli);
        printf("nv nom : ");
        scanf("%s", &nvClient.Nom);
        printf("nv prenom : ");
        scanf("%s", &nvClient.Prenom);

        file = fopen("client.txt", "r");

        int nbClients = 0;

        while(fread(&client, sizeof(struct SClient), 1, file)) {
            clients[nbClients] = client;
            nbClients++;
        }
        fclose(file);
        remove("client.txt");

        FILE *nf;
        nf = fopen("nv.txt", "a");
        for ( int i=0 ; i<nbClients ; i++)
        {
            if (clients[i].Code_cli == nvClient.Code_cli)
                fwrite(&nvClient, sizeof(clients[i]), 1, nf);
            else
                fwrite(&clients[i], sizeof(clients[i]), 1, nf);
        }
        fclose(nf);
        rename("nv.txt", "client.txt");
    }
    else if (a==3)
    {
        struct SClient client;
        int code;
        FILE *file;

        printf("Code Client a supprimer : ");
        scanf("%d", &code);

        file = fopen("client.txt", "r");

        int nbClients = 0;

        while(fread(&client, sizeof(struct SClient), 1, file)) {
            clients[nbClients] = client;
            nbClients++;
        }
        fclose(file);
        remove("client.txt");

        FILE *nf;
        nf = fopen("nv.txt", "a");
        for ( int i=0 ; i<nbClients ; i++)
        {
            if (clients[i].Code_cli != code)
                fwrite(&clients[i], sizeof(clients[i]), 1, nf);
        }
        fclose(nf);
        rename("nv.txt", "client.txt");
    }
    else if (a==4)
    {
        FILE *file;
        struct SClient client;
        file = fopen("client.txt", "r");
        int nbClients = 0;
        while(fread(&client, sizeof(struct SClient), 1, file)) {
            clients[nbClients] = client;
            nbClients++;
        }
        fclose(file);
        qsort(clients, nbClients, sizeof(SClient), comparer);
        for (int c=0 ; c<nbClients ; c++)
        {
            printf("\nCode client : %d", clients[c].Code_cli);
            printf("\nNom: %s | %s", clients[c].Nom, clients[c].Prenom);
            printf("\n");
        }

    }
    else if (a==5)
        menu();
}

void gerer_compte(int a)
{
    if (a==1)
    {
        struct SCompte compte;
        struct SCompte compte0;
        FILE *file;
        FILE *fl;

        printf("Code Compte : ");
        scanf("%d", &compte.code_cpt);

        fl = fopen("compte.txt", "r");
        int found = 0;
        while(fread(&compte0, sizeof(struct SCompte), 1, fl) && found == 0) {
            if (compte0.code_cpt == compte.code_cpt)
                found = 1;
        }

        if(found == 1)
        {
            printf("code existant\n");
            return 0;
        }

        printf("Code Client : ");
        scanf("%d", &compte.Code_cli);
        printf("Date de creation du compte | ");
        printf("Jour : ");
        scanf("%d", &compte.d_compte.Jour);
        printf("Mois : ");
        scanf("%d", &compte.d_compte.Mois);
        printf("Annee : ");
        scanf("%d", &compte.d_compte.Annee);
        printf("Somme : ");
        scanf("%d", &compte.somme);
        file = fopen("compte.txt", "a");
        fwrite(&compte, sizeof(compte), 1, file);

        if(fwrite != 0)
            printf("compte ajoute avec succes");
        else
            printf("erreur");
    }
    else if (a==2)
    {
        struct SCompte compte;
        int code;
        FILE *file;

        printf("Code compte : ");
        scanf("%d", &code);

        file = fopen("compte.txt", "r");
        int found = 0;
        while(fread(&compte, sizeof(struct SCompte), 1, file) && found == 0) {
            if (compte.code_cpt == code)
               {
                    printf("\n Code compte : %d", compte.code_cpt);
                    printf("\n Code client : %d", compte.Code_cli);
                    printf("\n Date creation %d / %d / %d", compte.d_compte.Jour, compte.d_compte.Mois, compte.d_compte.Annee);
                    printf("\n Somme %d", compte.somme);
                    found = 1 ;
               }
        }
        if(found == 0)
            printf("code non existant\n");
        fclose(file);
    }
    else if (a==3)
    {
        struct SCompte compte;
        FILE *file;

        file = fopen("compte.txt", "r");

        while(fread(&compte, sizeof(struct SCompte), 1, file)) {
                    printf("\n Code compte : %d", compte.code_cpt);
                    printf("\n Code client : %d", compte.Code_cli);
                    printf("\n Date creation %d / %d / %d", compte.d_compte.Jour, compte.d_compte.Mois, compte.d_compte.Annee);
                    printf("\n Somme %d", compte.somme);
                    printf("\n-----------------------------------------");
        }
        fclose(file);
    }
    else if (a==4)
    {
        struct SCompte compte;
        int code;
        FILE *file;

        printf("Code Compte a supprimer : ");
        scanf("%d", &code);

        file = fopen("compte.txt", "r");

        int nb = 0;

        while(fread(&compte, sizeof(struct SCompte), 1, file)) {
            comptes[nb] = compte;
            nb++;
        }
        fclose(file);
        remove("compte.txt");

        FILE *nf;
        nf = fopen("nv.txt", "a");
        for ( int i=0 ; i<nb ; i++)
        {
            if (comptes[i].code_cpt != code)
                fwrite(&comptes[i], sizeof(comptes[i]), 1, nf);
        }
        fclose(nf);
        rename("nv.txt", "compte.txt");
    }
    else if (a==5)
        menu();
}

void gerer_operation(int a)
{
    if (a==1)
    {
        struct SCompte compte;
        int code,m;
        FILE *file;

        printf("Code Compte : ");
        scanf("%d", &code);

        file = fopen("compte.txt", "r");

        int nb = 0;

        while(fread(&compte, sizeof(struct SCompte), 1, file)) {
            comptes[nb] = compte;
            nb++;
        }
        fclose(file);
        remove("compte.txt");

        FILE *nf;
        nf = fopen("nv.txt", "a");
        for ( int i=0 ; i<nb ; i++)
        {
            if (comptes[i].code_cpt == code)
            {
                        do{
                            printf("\n montant : ");
                            scanf("%d", &m);
                            if (m>500)
                                printf("\n le montant ne doit pas depasser 500 DT");
                            solde = comptes[i].somme - m;
                            if (solde<250)
                                printf("\n le solde ne doit pas etre inferieur a 250 DT");
                        }while(m>500 || solde<250);
                comptes[i].somme = comptes[i].somme - m;
                printf("\n code compte %d", comptes[i].code_cpt);
                printf("\n code client %d", comptes[i].Code_cli);
                printf("\n nv somme : %d", comptes[i].somme);
                printf("\n Date creation %d / %d / %d", compte.d_compte.Jour, compte.d_compte.Mois, compte.d_compte.Annee);
                printf("\n-----------------------------------------");
            }
            fwrite(&comptes[i], sizeof(comptes[i]), 1, nf);
        }
        fclose(nf);
        rename("nv.txt", "compte.txt");
    }
    else if (a==2)
    {
        struct SCompte compte;
        int code1,code2,m;
        FILE *file;

        printf("Code Compte de depart : ");
        scanf("%d", &code1);

        printf("Code compte d'arrivee : ");
        scanf("%d", &code2);

        file = fopen("compte.txt", "r");

        int nb = 0;

        while(fread(&compte, sizeof(struct SCompte), 1, file)) {
            comptes[nb] = compte;
            nb++;
        }
        fclose(file);
        remove("compte.txt");

        FILE *nf;
        nf = fopen("nv.txt", "a");
        for ( int i=0 ; i<nb ; i++)
        {
            if (comptes[i].code_cpt == code1)
            {
                        do{
                            printf("\n montant : ");
                            scanf("%d", &m);
                            if (m>500)
                                printf("\n le montant ne doit pas depasser 500 DT");
                            solde = comptes[i].somme - m;
                            if (solde<250)
                                printf("\n le solde ne doit pas etre inferieur a 250 DT");
                        }while(m>500 || solde<250);
                comptes[i].somme = comptes[i].somme - m;
                printf(" compte depart : ");
                printf("\n code compte %d", comptes[i].code_cpt);
                printf("\n code client %d", comptes[i].Code_cli);
                printf("\n nv somme : %d", comptes[i].somme);
                printf("\n Date creation %d / %d / %d", compte.d_compte.Jour, compte.d_compte.Mois, compte.d_compte.Annee);
                printf("\n-----------------------------------------");
            }
            else if (comptes[i].code_cpt == code2)
            {
                comptes[i].somme = comptes[i].somme + m;
                printf(" compte d'arrivée :");
                printf("\n code compte %d", comptes[i].code_cpt);
                printf("\n code client %d", comptes[i].Code_cli);
                printf("\n nv somme : %d", comptes[i].somme);
                printf("\n Date creation %d / %d / %d", compte.d_compte.Jour, compte.d_compte.Mois, compte.d_compte.Annee);
                printf("\n-----------------------------------------");
            }
            fwrite(&comptes[i], sizeof(comptes[i]), 1, nf);
        }
        fclose(nf);
        rename("nv.txt", "compte.txt");
    }
}

int main()
{
    menu();
    return 0;
}


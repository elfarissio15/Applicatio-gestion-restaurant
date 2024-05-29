#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <errno.h>
#include <ctype.h>
#include <conio.h>
#include<time.h>

#define ELEMENT_SIZE 100

// Information globale sur les restaurant

// Structure pour la gestion des employes.
typedef struct Employe {
    char nom[ELEMENT_SIZE];
    char prenom[ELEMENT_SIZE];
    int E_ID ;
    char CNI[10];
    char ph_number[12];
    char Departement[ELEMENT_SIZE];
    //int Dep_ID;
    float salaire;
} Employe;
typedef struct EmpListe {
    Employe data;
    struct EmpListe* next;
} EmpListe;

// Structure pour la gestion des Repas.
typedef struct Repass {
    char name[ELEMENT_SIZE];
    float prix;
    char consomation_par_temps[ELEMENT_SIZE]; //lors de l'ajout d'un Repas en specifier combien de temp il prend
    int R_ID ;
} Repass;
typedef struct RepasListe {
    Repass data ;
    struct RepasListe* next ;
} RepasListe;

// Structure pour la gestion des clients.
typedef struct Client {
    int C_ID ;
    char name[ELEMENT_SIZE];
    char first_name[ELEMENT_SIZE];
    char ph_number[11];
    //Repas ordre;
    float paiment;
} Client;
typedef struct client_Liste {
    Client data;
    struct client_Liste* next;
} client_Liste;

// Structure pour la gestion des commandes.
typedef struct Commande {
    char** plats;
    char* string_plat ;
    int Cm_ID ;
    Client Client;
    float consomation;
    int nbr_plat ;
    char* etat ;// completer 1 ou non 0 ,quand tout les Repas dans la commande ont des pret egaux a 1 alors etat = 1
} Commande;
typedef struct commande_liste {
    Commande data ;
    struct commande_liste* next ;
}commande_liste;

//login
char Chef[] = "Chef",emploir[] = "emploier" ;
char pass_chef[] = "1111",pass_emploier[] = "2222";

int login_Bibliotheque(){
    char nomdu[20];
    char mdp[10];
    int retries = 3;
    int choix;
    system("cls");
    printf("\n\n\n");
    printf("\t                           /          BIENVENUE DANS LE PROGRAMME          \\\n");
    printf("\t                           \\           DE GESTION DU  RESTAURANT           /\n");

    printf("\n\n");
    printf("\t                          ___________________                  ______________\n");
    printf("\t                         |                   |                |              |\n");
    printf("\t                         |  1. Se connecter  |                |  2. Quitter  |\n");
    printf("\t                         |___________________|                |______________|\n\n");

    printf("\nEntrer votre choix (1/2): ");
    scanf("%d", &choix);

    while (choix < 1 || choix > 2) {
        printf("\n\a\033[31mOperation introuvable! Continue pour re-choisir l'operation.\033[0m\n");
        printf("\nEntrer votre choix (1/2): ");
        scanf("%d", &choix);
    }
    getchar();

    printf("\n\n");
    if (choix == 1) {
        while (retries != 0){
            printf("\tSe connecter:");
            printf("\n\n");
            printf("\t\t[Nom d'utilisateur]: ");
            fgets(nomdu ,sizeof(nomdu),stdin);
            nomdu[strcspn(nomdu, "\n")] = '\0';
            printf("\n\t\t[Mot de passe]: ");
            fgets(mdp, sizeof(mdp), stdin);
            mdp[strcspn(mdp, "\n")] = '\0';
            if(strcmp(nomdu,Chef)==0){
                if(strcmp(mdp,pass_chef)==0){
                    printf("\n\t\033[3;32mConnexion reussie...\033[0m\n\n");
                    printf("\t\t\033[3;32mSous Nom Chef \033[0m\n\n");
                    return 1;
                }else{
                    printf("\n\t\033[3;31mMot de passe Chef incorrect Reessayez ...\033[0m\n\n");
                }
            }else if(strcmp(nomdu,emploir)==0){
                if(strcmp(mdp,pass_emploier)==0){
                    printf("\n\t\033[3;32mConnexion reussie...\033[0m\n\n");
                    printf("\t\t\033[3;32mSous Nom Emploier \033[0m\n\n");
                    return 2;
                }else{
                    printf("\n\t\033[3;31mMot de passe Emploier incorrect Reessayez ...\033[0m\n\n");
                }
            }else{
                printf("\n\t\033[3;31mNom d'utilisateur ou Mot de passe incorrect!\033[0m");
                printf("\n\t\033[3;31mReessayez de vous connecter.\033[0m\n\n");
                retries--;
            }
        }
        if (retries == 0) {
            printf("\n\t\033[3;31mEchec de connection! Reessayez apres quelques minutes...\033[0m\n\n");
            exit(3);
        }

    } else if (choix == 2) {
        printf("\t\tProgramme fermer!\n\n");
        return 0 ;
    }
    system("pause");
}
//DEFINITIONS

// Fonctions pour la gestion des employes.
EmpListe* insert_Emploier_Liste(EmpListe* Emploiers); //verifie si il existe dans la liste
void aff_Emploier_Liste(EmpListe* Emploiers); //par tableau de base de donnees
EmpListe* supp_Emploier_Liste(EmpListe* Emploiers);
EmpListe* modifier_Emploier_liste(EmpListe* Emploiers);
EmpListe* chercher_Emploier_liste(EmpListe* Emploiers);
EmpListe* Trier_Emploier_liste(EmpListe* Emploiers);

// Fonctions pour la gestion des clients.
client_Liste* insert_client_Liste(client_Liste* Clients);//verifie si il existe dans la liste
void aff_client_Liste(client_Liste* Clients);
client_Liste* supp_client_Liste(client_Liste* Clients);
client_Liste* modifier_client_liste(client_Liste* Clients);
client_Liste* chercher_client_liste(client_Liste* Client);
client_Liste* Trier_client_liste(client_Liste* Clients);

// Fonctions pour la gestion des Repas.
RepasListe* insert_Repas_Liste(RepasListe* Repas);//verifie si il existe dans la liste
void aff_Repas_Liste(RepasListe* Repas);
RepasListe* supp_Repas_Liste(RepasListe* Repas);
RepasListe* modifier_Repas_liste(RepasListe* Repas);
RepasListe* chercher_Repas_liste(RepasListe* Repas);
RepasListe* Trier_Repas_liste(RepasListe* Repas);

// Fonctions pour la gestion des commandes.
commande_liste* insert_commande_Liste(commande_liste* Commandes,RepasListe* Repas_valables,client_Liste* Clients_valables);
void aff_commande_Liste(commande_liste* Commandes);
commande_liste* supp_commande_Liste(commande_liste* Commandes);
commande_liste* modifier_commande_liste(commande_liste* Commandes,RepasListe* Repas_valables,client_Liste* Clients_valables );
commande_liste* chercher_commande_liste(commande_liste* Commandes);
commande_liste* Trier_commande_liste(commande_liste* Commandes);

//fonctions for l'aprend de data_bases
EmpListe* get_Emploier_base( FILE* Empfile,EmpListe* Emploiers);
client_Liste* get_Client_base( FILE* Clifile,client_Liste* Clients);
RepasListe* get_Repas_base( FILE* Repfile ,Repass* Repas);

//fonctions for le donne de  data_bases
FILE* give_Emploier_base(FILE* Empfile , EmpListe* Emploiers );
FILE* give_Client_base( FILE* Clifile ,client_Liste* Clients);
FILE* give_Repas_base( FILE* Repfile ,RepasListe* Repas);
FILE* give_Commande_base( FILE* Comfile ,commande_liste* Commandes);


//DECLARATION
int E_ID ,C_ID ,R_ID,Cm_ID ;

EmpListe* dupliquer_Emploiers_liste(EmpListe* Liste ,Employe Element){
    EmpListe* Nouv = malloc(sizeof(EmpListe)) ;
    Nouv->next = NULL;
    Nouv->data = Element;
    if(Liste ==NULL){
        return Nouv;
    }
    else{
        EmpListe* tmp = Liste;
        while(tmp->next!=NULL){
            tmp = tmp->next;
        }
        tmp->next = Nouv;
        return Liste;
    }
}
EmpListe* get_Emploier_base( FILE* Empfile , EmpListe* Emploiers){
    Empfile = fopen("EmployeData.txt", "r");
    Employe emp_data;
        if (Empfile == NULL) {
            printf("\033[31mError opening file Emploier for reading.\033[0m\n");
            exit(10);
        }
        while (fscanf(Empfile, "%[^,],%[^,],%d,%[^,],%[^,],%[^,],%f\n", emp_data.nom,
                                                    emp_data.prenom,
                                                    &emp_data.E_ID,
                                                    emp_data.CNI,
                                                    emp_data.ph_number,
                                                    emp_data.Departement,
                                                &emp_data.salaire) != EOF) {
            Emploiers = dupliquer_Emploiers_liste(Emploiers, emp_data);
        }
    return Emploiers ;
}
client_Liste* dupliquer_Clients_liste(client_Liste* Liste ,Client Element){
    client_Liste* Nouv = malloc(sizeof(client_Liste));
    Nouv->next = NULL ;
    Nouv->data = Element;
    if(Liste == NULL){
        return Nouv ;
    }else{
        client_Liste* tmp  = Liste ;
        while(tmp->next != NULL){
            tmp = tmp->next ;
        }
        tmp->next = Nouv ;
        return Liste ;
    }
}
client_Liste* get_Client_base(FILE* Clifile ,client_Liste* Clients){
    Clifile = fopen("ClientData.txt", "r");
    Client cli_data ;
        if (Clifile == NULL) {
                printf("\033[31mError opening file Client for reading.\033[0m\n");
                exit(20);
        }
        while (fscanf(Clifile, "%[^,],%[^,],%d,%[^,],%f\n", cli_data.name,
                                                    cli_data.first_name,
                                                    &cli_data.C_ID,
                                                    cli_data.ph_number,
                                                &cli_data.paiment) != EOF) {
            Clients = dupliquer_Clients_liste(Clients, cli_data);
        }
    return Clients ;
}
RepasListe* dupliquer_repas_liste(RepasListe* Liste , Repass Element){
    RepasListe* Nouv = malloc(sizeof(RepasListe));
    Nouv->next = NULL;
    Nouv->data = Element ;
    if(Liste == NULL){
        return Nouv ;
    }
    else{
        RepasListe* tmp = Liste ;
        while(tmp->next != NULL){
            tmp = tmp->next;
        }
        tmp->next = Nouv ;
        return Liste;
    }
}
RepasListe* get_Repas_base( FILE* Repfile ,Repass* Repas){
    Repfile = fopen("RepasData.txt", "r");
    Repass Rep_data ;
        if (Repfile == NULL) {
            printf("\033[31mError opening file Repas for writing.\033[0m\n");
            exit(30);
        }
        while (fscanf(Repfile, "%[^,],%d,%f,%s\n", Rep_data.name,
                                                    &Rep_data.R_ID,
                                                    &Rep_data.prix,
                                                Rep_data.consomation_par_temps) != EOF) {
            Repas = dupliquer_repas_liste(Repas, Rep_data);
        }
    return Repas ;
}
commande_liste* dupliquer_Commandes_liste(commande_liste* Liste,Commande Element){
    commande_liste* Nouv = malloc(sizeof(commande_liste));
    Nouv->next = NULL ;
    Nouv->data = Element;
    if(Liste == NULL){
        return Nouv ;
    }else{
        commande_liste* tmp = Liste ;
        while(tmp->next != NULL){
            tmp = tmp->next ;
        }
        tmp->next = Nouv ;
        return Liste ;
    }
}

FILE* give_Client_base( FILE* Clifile ,client_Liste* Clients){
    Clifile = fopen("ClientData.txt", "w");
    client_Liste* tmp = Clients ;
    if (Clifile == NULL) {
                printf("\033[31mError opening file Client for updating.\n");
                exit(20);
        }
        while (tmp != NULL){
            fprintf(Clifile, "%s,%s,%d,%s,%.2f\n", tmp->data.name,tmp->data.first_name,tmp->data.C_ID,tmp->data.ph_number,tmp->data.paiment);
            tmp =tmp->next;
        }
        fclose(Clifile);
    return Clifile ;
}
FILE* give_Commande_base( FILE* Comfile ,commande_liste* Commandes){
    Comfile = fopen("CommandeData.txt", "w");
    commande_liste* tmp = Commandes ;
    if (Comfile == NULL) {
                printf("\033[31mError opening file Commande for updating.\n");
                exit(20);
        }
        while (tmp != NULL){
            fprintf(Comfile, "%s,%s,%d,%s,%.2f,%s\n", tmp->data.string_plat,tmp->data.Client.name,tmp->data.Cm_ID,tmp->data.Client.ph_number,tmp->data.consomation,tmp->data.etat);
            tmp =tmp->next;
        }
        fclose(Comfile);
    return Comfile ;
}
FILE* give_Emploier_base( FILE* Empfile ,EmpListe* Emploiers ){
    Empfile = fopen("EmployeData.txt","w");
    EmpListe* tmp = Emploiers;
    if(Empfile ==NULL){
        printf("\033[31mError opening file Emploier for updating.\n");
        exit(20);
    }while(tmp!=NULL){
        fprintf(Empfile,"%s,%s,%d,%s,%s,%s,%.2f\n",tmp->data.nom,
                                                    tmp->data.prenom,
                                                    tmp->data.E_ID,
                                                    tmp->data.CNI,
                                                    tmp->data.ph_number,
                                                    tmp->data.Departement,
                                                tmp->data.salaire);
        tmp =tmp->next;
    }
    fclose(Empfile);
    return Empfile;
}
FILE* give_Repas_base( FILE* Repfile ,RepasListe* Repas){
    Repfile = fopen("RepasData.txt","w");
    RepasListe* tmp = Repas ;
    if(Repfile == NULL){
        printf("\033[31mError opening file Repas for updating.\n");
        exit(20);
    }while(tmp != NULL){
        fprintf(Repfile,"%s,%d,%f,%s\n",tmp->data.name,
                                                    tmp->data.R_ID,
                                                    tmp->data.prix,
                                                tmp->data.consomation_par_temps);
        tmp = tmp->next ;
    }
    fclose(Repfile);
    return Repfile ;
}
// Fonctions pour la gestion des employes.

int existe_client_test(client_Liste* Clients , char * name,char* phone_number){
    client_Liste* tmp = Clients;
    if(tmp == NULL){
        printf("\t\t\033[31mLA LISTE DE CLIENTS EST VIDE :\033[0m\n");
        return 0;
    }
    else{
        while(tmp != NULL){
            if(strcmp(tmp->data.name,name)==0 && strcmp(tmp->data.ph_number,phone_number)==0){
                return 1;
            }
            tmp =tmp->next;
        }
        return 0;
    }
}

int isvalid_CNI(EmpListe *Head, char *CNI) {
    EmpListe *Emp = Head;

    while (Emp != NULL) {
        if (strcmp(Emp->data.CNI, CNI) == 0) {
            return -1;
        }
        Emp = Emp->next;
    }
    // Si l'element n'est pas trouver.
    return 1;
}
int isvalid_Ph_number(EmpListe *Head, char *tele) {
    EmpListe *Emp = Head;

    while (Emp != NULL) {
        if (strcmp(Emp->data.ph_number, tele) == 0) {
            return -1;
        }
        Emp = Emp->next;
    }
    // Si l'element n'est pas trouver.
    return 1;
}

EmpListe* insert_Emploier_Liste(EmpListe* Emploiers) {
    EmpListe * nouv = (EmpListe*) malloc (sizeof(EmpListe));
    E_ID++;
    int m ;
    // Open the file in append mode.
    FILE *Empfile;

    printf("\n\t\t [ENTRER LE NOM DE L'EMPLOYE]: ");
    fgets(nouv->data.nom,sizeof(nouv->data.nom),stdin);
    nouv->data.nom[strcspn(nouv->data.nom, "\n")] = '\0';
    printf("\n\t\t [ENTRER LE PRENOM DE L'EMPLOYE]: ");
    fgets(nouv->data.prenom,sizeof(nouv->data.prenom),stdin);
    nouv->data.prenom[strcspn(nouv->data.prenom, "\n")] = '\0';
    do{
        m =0;
        printf("\n\t\t [ENTRER LE CNI DE L'EMPLOYE]: ");
        fgets(nouv->data.CNI,sizeof(nouv->data.CNI),stdin);
        nouv->data.CNI[strcspn(nouv->data.CNI, "\n")] = '\0';
        if(isvalid_CNI(Emploiers,nouv->data.CNI)==-1){
            printf("\n\t\t\033[31m RESSAYER AVEC UN AUTRE CNI: \033[0m\n");
            m=1;
        }
    }while(m==1);
    do{
        m =0;
        printf("\n\t\t [ENTRER LE NUMERO DE TELEPHONE DE L'EMPLOYE]: ");
        fgets(nouv->data.ph_number,sizeof(nouv->data.ph_number),stdin);
        nouv->data.ph_number[strcspn(nouv->data.ph_number, "\n")] = '\0';
        if(isvalid_Ph_number(Emploiers,nouv->data.ph_number)==-1){
            printf("\n\t\t\033[31m [RESSAYER AVEC UN AUTRE NUMERO DE TELEPHONE]...... \033[0m\n");
            m=1;
        }
    }while(m==1);
    printf("\n\t\t [ENTRER LE DEPARTEMENT DE L'EMPLOYE]: ");
    fgets(nouv->data.Departement,sizeof(nouv->data.Departement),stdin);
    nouv->data.Departement[strcspn(nouv->data.Departement, "\n")] = '\0';
    printf("\n\t\t [ENTRER LE SALAIR DE L'EMPLOYE]: ");
    scanf("%f", &nouv->data.salaire);
    while (getchar() != '\n');
    nouv->data.E_ID = E_ID;
    nouv->next = Emploiers;
    Emploiers = nouv;
    Empfile = fopen("EmployeData.txt","a");
    if (Empfile == NULL) {
        perror("Error opening file for updating.\n");
        exit(-1);
    }
    // Write the employee data to the file.
    fprintf(Empfile, "%s,%s,%d,%s,%s,%s,%.2f\n", nouv->data.nom, nouv->data.prenom, nouv->data.E_ID,
            nouv->data.CNI, nouv->data.ph_number, nouv->data.Departement, nouv->data.salaire);
    // Close the file
    fclose(Empfile);

    return nouv;
}
void aff_Emploier_Liste(EmpListe* Emp){
EmpListe* tmp = NULL;

printf("\n|\033[44m----------------------------------------------------------------------------------------------------------------------------------------------\033[0m|");
printf("\n|\033[44m      ID       | NOM                  | PRENOM               | CNI              | N.TELEPHON  | DEPARTEMENT                      | SALAIRE    \033[0m|\n");
printf("|\033[44m----------------------------------------------------------------------------------------------------------------------------------------------\033[0m|\n");
tmp = Emp;

while(tmp != NULL) {
    printf("| %d\t\t| %-20s | %-20s | %s\t | %-10s  | %-30s   | %-11.2f|\n", tmp->data.E_ID,
                                                                                tmp->data.nom,
                                                                                tmp->data.prenom,
                                                                                tmp->data.CNI,
                                                                                tmp->data.ph_number,
                                                                                tmp->data.Departement,
                                                                                tmp->data.salaire);
    printf("------------------------------------------------------------------------------------------------------------------------------------------------\n");
    tmp = tmp->next;
}
}
EmpListe* supp_Emploier_Liste(EmpListe* Emploiers){
        int m ,ID;
        EmpListe* tmp = Emploiers;
        EmpListe* ptmp = NULL;
        FILE* Empfile ;
        if (tmp == NULL) {
            printf("\t\tLA LISTE EST VIDE:\n");
            return NULL;
        }
        do {
            m=0;
            system("cls");
            aff_Emploier_Liste(Emploiers);
            printf("\t\tENTRER L'ID QUE TU VEUX SUPPRIMER DE LA LISTE(-1 -> exit) : ");
            scanf("%d",&ID);
            if(ID != -1){
                while (tmp != NULL) {
                if ( tmp->data.E_ID == ID) {
                    if (ptmp == NULL) {
                        Emploiers = tmp->next;
                        free(tmp);
                        tmp = Emploiers;
                    } else {
                        ptmp->next = tmp->next;
                        free(tmp);
                        tmp = ptmp->next;
                    }
                    // After deleting, exit the function
                    Empfile = give_Emploier_base(Empfile,Emploiers);
                    Emploiers = get_Emploier_base(Empfile,Emploiers);
                    return Emploiers ;
                } else {
                    ptmp = tmp;
                    tmp = tmp->next;
                }
            }
            // If we reach here, it means no match was found
            printf("\033[31mNo employee with the given ID found.\033[30m\n");
            m=1;
            system("pause");
            }else{
                return Emploiers;
            }
        }while(m==1);
    }
EmpListe* modifier_Emploier_liste(EmpListe* Emploiers){
    int m, p,k;
    EmpListe* tmp = Emploiers;
    FILE* Empfile ;
    char choix[ELEMENT_SIZE];
    char inser[ELEMENT_SIZE]; // Use array instead of malloc
    if (tmp == NULL) {
        printf("\t\t\033[31mLA LISTE D'EMPLOIERS EST VIDE:\033[0m\n");
        return NULL;
    }
    do {
        m = 0;
        aff_Emploier_Liste(Emploiers);
        printf("\t\tENTRER N'IMPORTE INFORMATION QUE TU VEUT MODIFIER DE LA LISTE EN SPECIFIANT L'ID D'EMPLOIER SUIVI D'ELEMENT QUI SERA MODIFIER(4:NOM->morad):");
        fgets(choix, sizeof(choix), stdin);
        choix[strcspn(choix, "\n")] = '\0';
        char* token = strtok(choix, ":");

        EmpListe* current = tmp; // Create a separate pointer for traversal

        while (current != NULL) {
            if (current->data.E_ID == atof(token)) {
                tmp = current; // Update tmp to the current position
                break;
            }
            current = current->next;
        }
        if (current == NULL) {
            printf("\n\t\t\033[31mWE DIDN'T FIND ANY ELEMENT WITH THIS ID\033[0m");
            m = 1;
            break;
        }

        token = strtok(NULL, ":");
        char* String = strtok(token, "->");
        char ELEMENT[ELEMENT_SIZE];
        strcpy(ELEMENT, String);
        String = strtok(NULL, "->");
        char Modifier[ELEMENT_SIZE];
        strcpy(Modifier, String);

        if (strcmp(ELEMENT, "NOM") == 0) {
            k=1;
            do {
                if(k>1){
                    printf("\n\t\tENTRER A NOUVEAU LE NOM EXISTANT QUE TU VEUX CHANGER :");
                    fgets(Modifier,sizeof(Modifier),stdin);
                    Modifier[strcspn(Modifier, "\n")] = '\0';
                }
                p = 0;
                if (strcmp(Modifier, tmp->data.nom) == 0) {
                    printf("\t\tDONNER LE NOUVEAU NOM D'EMPLOIER #%d:", tmp->data.E_ID);
                    fgets(inser, sizeof(inser), stdin);
                    inser[strcspn(inser, "\n")] = '\0'; // Remove newline character
                    strcpy(tmp->data.nom, inser);
                } else {
                    printf("\n\t\t\033[31mLE NOM ENTRER COMME UN NOM DEJA EXIST EST PAS VALIDE VERIFIER LA LIGNE D'ID #%d ET RESSAYER\033[0m", tmp->data.E_ID);
                    k++;
                    p = 1;
                }
            } while (p == 1);
        }else if(strcmp(ELEMENT,"PRENOM")==0){
            k=1;
            do{
                if(k>1){
                    printf("\n\t\tENTRER A NOUVEAU LE PRENOM EXISTANT QUE TU VEUX CHANGER :");
                    fgets(Modifier,sizeof(Modifier),stdin);
                    Modifier[strcspn(Modifier, "\n")] = '\0';
                }
                p=0;
                if(strcmp(Modifier,tmp->data.prenom)==0){
                    printf("\t\tDONNER LE NOUVEAU PRENOM D'EMPLOIER #%d:",tmp->data.E_ID);
                    fgets(inser,sizeof(inser),stdin);
                    inser[strcspn(inser, "\n")] = '\0'; // Remove newline character
                    strcpy(tmp->data.prenom,inser);
                }
                else{
                    printf("\n\t\t\033[31mLE PRENOM ENTRER COMME UN PRENOM DEJA EXIST EST PAS VALID VERIFIER LA LIGNE D'ID #%d ET RESSAYER\033[0m",tmp->data.E_ID);
                    k++;
                    p=1;
                }
            }while(p==1);
        }else if(strcmp(ELEMENT,"CNI")==0){
            k=1;
            do{
                if(k>1){
                    printf("\n\t\tENTRER A NOUVEAU LE CNI EXISTANT QUE TU VEUX CHANGER :");
                    fgets(Modifier,sizeof(Modifier),stdin);
                    Modifier[strcspn(Modifier, "\n")] = '\0';
                }
                p=0;
                if(strcmp(Modifier,tmp->data.CNI)==0){
                    printf("\t\tDONNER LE NOUVEAU CNI D'EMPLOIER #%d:",tmp->data.E_ID);
                    fgets(inser,sizeof(inser),stdin);
                    inser[strcspn(inser, "\n")] = '\0'; // Remove newline character
                    strcpy(tmp->data.CNI,inser);
                }
                else{
                    printf("\n\t\t\033[31mLE CNI ENTRER COMME UN PRENOM DEJA EXIST EST PAS VALID VERIFIER LA LIGNE D'ID #%d ET RESSAYER\033[0m",tmp->data.E_ID);
                    k++;
                    p=1;
                }
            }while(p==1);
        }else if(strcmp(ELEMENT,"N.TELEPHON")==0){
            k=1;
            do{
                if(k>1){
                    printf("\n\t\tENTRER A NOUVEAU LE PHONE NUMBER EXISTANT QUE TU VEUX CHANGER :");
                    fgets(Modifier,sizeof(Modifier),stdin);
                    Modifier[strcspn(Modifier, "\n")] = '\0';
                }
                p=0;
                if(strcmp(Modifier,tmp->data.ph_number)==0){
                    printf("\t\tDONNER LE NOUVEAU PHONE NUMBER D'EMPLOIER #%d:",tmp->data.E_ID);
                    fgets(inser,sizeof(inser),stdin);
                    inser[strcspn(inser, "\n")] = '\0'; // Remove newline character
                    strcpy(tmp->data.CNI,inser);
                }
                else{
                    printf("\n\t\t\033[31mLE PHONE NUMBER ENTRER COMME UN DEJA EXIST EST PAS VALID VERIFIER LA LIGNE D'ID #%d ET RESSAYER\033[0m",tmp->data.E_ID);
                    k++;
                    p=1;
                }
            } while (p == 1);
        } else if (strcmp(ELEMENT,"DEPARTEMENT") == 0){
            k=1;
            do{
                if(k>1){
                    printf("\n\t\tENTRER A NOUVEAU LE DEPARTEMENT EXISTANT QUE TU VEUX CHANGER :");
                    fgets(Modifier,sizeof(Modifier),stdin);
                    Modifier[strcspn(Modifier, "\n")] = '\0';
                }
                p = 0;
                if (strcmp(Modifier,tmp->data.Departement) == 0) {
                    printf("\t\tDONNER LE NOUVEAU DEPARTEMENT D'EMPLOIER #%d:",tmp->data.E_ID);
                    fgets(inser,sizeof(inser),stdin);
                    inser[strcspn(inser, "\n")] = '\0'; // Remove newline character
                    strcpy(tmp->data.Departement,inser);
                }
                else {
                    printf("\n\t\t\033[31mLE DEPARTEMENT ENTRER COMME UN DEJA EXIST EST PAS VALID VERIFIER LA LIGNE D'ID #%d ET RESSAYER\033[0m",tmp->data.E_ID);
                    k++;
                    p = 1;
                }
            } while (p == 1);
        } else if (strcmp(ELEMENT,"SALAIRE") == 0) {
            k=1;
            do {
                if(k>1){
                    printf("\n\t\tENTRER A NOUVEAU LE SALAIRE EXISTANT QUE TU VEUX CHANGER :");
                    fgets(Modifier,sizeof(Modifier),stdin);
                    Modifier[strcspn(Modifier, "\n")] = '\0';
                }
                p = 0;
                if (tmp->data.salaire== atof(Modifier)) {
                    printf("\t\tDONNER LE NOUVEAU SALAIRE D'EMPLOIER #%d:",tmp->data.E_ID);
                    fgets(inser,sizeof(inser),stdin);
                    inser[strcspn(inser, "\n")] = '\0'; // Remove newline character
                    tmp->data.salaire = atof(inser);
                } else {
                    printf("\n\t\t\033[31mLE SALAIRE ENTRER COMME UN DEJA EXIST EST PAS VALID VERIFIER LA LIGNE D'ID #%d ET RESSAYER\033[0m",tmp->data.E_ID);
                    k++;
                    p = 1;
                }
            } while (p == 1);
        } else {
            system("cls");
            m=1;
        }
    } while (m == 1);
    system("cls");
    aff_Emploier_Liste(Emploiers);
    Empfile = give_Emploier_base(Empfile,Emploiers);
    Emploiers = get_Emploier_base(Empfile,Emploiers);
    return Emploiers;
}
EmpListe* chercher_Emploier_liste(EmpListe* Emploiers){
    int m ;
    EmpListe* tmp = Emploiers ;
    EmpListe* nouv = NULL;
    char choix[ELEMENT_SIZE];
    if(tmp ==NULL ){
        printf("\t\t\033[31mLA LISTE D'EMPLOIERS EST VIDE\033[0m");
        return nouv ;
    }
    do{
        m =0 ;
        aff_Emploier_Liste(Emploiers);
        printf("\t\tENTRER N'IMPORTE INFORMATION QUE TU VEUT CHERCHER DANS LA LISTE (EXEMPLE=>NOM:samir):");
        fgets(choix,sizeof(choix),stdin);
        choix[strcspn(choix, "\n")] = '\0';
        char* token = strtok(choix,":");
        char* Categorie = strdup(token);
        token = strtok(NULL,":");
        char* Chercher = strdup(token);
        if(strcmp(Categorie,"ID")==0){
            while(tmp!= NULL){
                if (tmp->data.E_ID == atof(Chercher)) {
                    nouv = dupliquer_Emploiers_liste(nouv,tmp->data);
                }
                tmp=tmp->next;
            }
        }else if(strcmp(Categorie,"NOM")==0){
            while(tmp!= NULL){
                if(strcmp(Chercher,tmp->data.nom) ==0){
                    nouv = dupliquer_Emploiers_liste(nouv,tmp->data);
                }
                tmp = tmp->next;
            }
        }else if(strcmp(Categorie,"PRENOM")==0){
            while(tmp!= NULL){
                if(strcmp(Chercher,tmp->data.prenom) ==0){
                    nouv = dupliquer_Emploiers_liste(nouv,tmp->data);
                }
                tmp = tmp->next;
            }
        }else if(strcmp(Categorie,"CNI")==0){
            while(tmp!= NULL){
                if(strcmp(Chercher,tmp->data.CNI) ==0){
                    nouv = dupliquer_Emploiers_liste(nouv,tmp->data);
                }
                tmp = tmp->next;
            }
        }else if(strcmp(Categorie,"N.TELEPHON")==0){
            while(tmp!= NULL){
                if(strcmp(Chercher,tmp->data.ph_number) ==0){
                    nouv = dupliquer_Emploiers_liste(nouv,tmp->data);
                }
                tmp = tmp->next;
            }
        }else if(strcmp(Categorie,"DEPARTEMENT")==0){
            while(tmp!= NULL){
                if(strcmp(Chercher,tmp->data.Departement) ==0){
                    nouv = dupliquer_Emploiers_liste(nouv,tmp->data);
                }
                tmp = tmp->next;
            }
        }else if(strcmp(Categorie,"SALAIRE")==0){
            while(tmp!= NULL){
                if(tmp->data.salaire == atof(Chercher)){
                    nouv = dupliquer_Emploiers_liste(nouv,tmp->data);
                }
                tmp = tmp->next;
            }
        }else{
            system("cls");
            m=1;
        }
    }while (m==1);
    system("cls");
    aff_Emploier_Liste(nouv);
    return nouv ;

}
EmpListe* Trier_Emploier_liste(EmpListe* Emploiers){
    int m ,type,save;
    char choix[ELEMENT_SIZE];
    FILE* Empfile;
    Employe tri;
    EmpListe* tmp1 = Emploiers;
    EmpListe* tmp2 = Emploiers;
    EmpListe* result = Emploiers ;
    if (tmp1 == NULL){
        printf("\t\t\033[31mLA LISTE D'EMPLOIER EST VIDE:\033[0m\n");
        return NULL ;
    }
    if (tmp1->next == NULL){
        printf("\t\t\033[32mLA LISTE DES EMPLOIER EST TRIER:\033[0m\n");
        return Emploiers ;
    }
    do{
        m=0;
        aff_Emploier_Liste(Emploiers);
        printf("\t\tENTRER LE NOM DE LA CASE QUE TU VEUT TRIER AVEC EN SPECIFIANT LE TYPE DE TRIYAGE (EXEMPLE=>EMPLOIER ID:DESC) : ");
        fgets(choix,sizeof(choix),stdin);
        choix[strcspn(choix, "\n")] = '\0';
        char* token = strtok(choix,":");
        char* Categorie = strdup(token);
        token = strtok(NULL,":");
        char* Trier =strdup(token);
        if(strcmp(Trier,"DESC")==0){
            type = -1 ;
        }else if(strcmp(Trier,"INSC")==0){
            type = 1 ;
        }else{
            printf("\t\t\033[31mINVALID INPUT RESSAYER SOIT AVEC \"DESC\" OU \"INSC\":\033[0m");
            continue;
        }
        if(strcmp(Categorie,"ID")==0){
            while (tmp1->next != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && tmp2->data.E_ID <tmp1->data.E_ID){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && tmp2->data.E_ID >tmp1->data.E_ID){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
                tmp1 =tmp1->next;
            }
        }else if(strcmp(Categorie,"NOM")==0){
            while (tmp1->next != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && strcmp(tmp2->data.nom,tmp1->data.nom) < 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && strcmp(tmp2->data.nom,tmp1->data.nom) > 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
                tmp1 =tmp1->next;
            }
        }else if(strcmp(Categorie,"PRENOM")==0){
            while (tmp1->next != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && strcmp(tmp2->data.prenom,tmp1->data.prenom) < 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && strcmp(tmp2->data.prenom,tmp1->data.prenom) > 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
                tmp1 =tmp1->next;
            }
        }else if(strcmp(Categorie,"CNI")==0){
            while (tmp1->next != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && strcmp(tmp2->data.CNI,tmp1->data.CNI) < 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && strcmp(tmp2->data.CNI,tmp1->data.CNI) > 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
                tmp1 =tmp1->next;
            }
        }else if(strcmp(Categorie,"N.TELEPHON")==0){
            while (tmp1->next != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && strcmp(tmp2->data.ph_number,tmp1->data.ph_number) < 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && strcmp(tmp2->data.ph_number,tmp1->data.ph_number) > 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
                tmp1 =tmp1->next;
            }
        }else if(strcmp(Categorie,"DEPARTEMENT")==0){
             while (tmp1->next != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && strcmp(tmp2->data.Departement,tmp1->data.Departement) < 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && strcmp(tmp2->data.Departement,tmp1->data.Departement) > 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
                tmp1 =tmp1->next;
            }
        }else if(strcmp(Categorie,"SALAIRE")==0){
            while (tmp1 != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && tmp2->data.salaire <tmp1->data.salaire){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && tmp2->data.salaire >tmp1->data.salaire){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
            tmp1 =tmp1->next;
            }
        }else  {
            system("cls");
            m=1;
        }
    }while(m==1);
    system("cls");
    aff_Emploier_Liste(Emploiers);
    printf("\t\t\033[32mVOULLEZ SAUVGARDER LE NOUVEAU TRIAGE OU NON ,SI OUI TAPER 1 SINON N'IMPORTE NOMBRE :\033[0m");
    scanf("%d",&save);
    if(save ==1){
        Empfile = give_Emploier_base(Empfile,Emploiers);
        Emploiers = get_Emploier_base(Empfile,Emploiers);
        return Emploiers ;
    }
    else{
        return result;
    }
}

// Fonction pour chercher l'employe avec le plus grand salaire.
    Employe SalrSearch(EmpListe *Head) {
        EmpListe *Emp = Head;
        float HighSalr = Emp->data.salaire;
        Employe empHighSalr = Emp->data;

        if (Head == NULL) {
            printf("Liste d'employes vide.\n");
            return;
        }
        while (Emp != NULL) {
            if (Emp->data.salaire > HighSalr) {
                HighSalr = Emp->data.salaire;
                empHighSalr = Emp->data;
            }
            Emp = Emp->next;
        }
        return (empHighSalr);
    }
//fonction pour chercher le client qui a le plus grand paiment ou sold
Client  PaimSearch(client_Liste* Head){
    client_Liste * Cli = Head ;
    float HighPaim = Cli->data.paiment;
    Client ClihighPaim = Cli->data;
    if(Head == NULL){
        printf("Liste de Clients vide.\n");
        return;
    }
    while(Cli != NULL){
        if (Cli->data.paiment > HighPaim)
        {
            HighPaim = Cli->data.paiment;
            ClihighPaim = Cli->data;
        }
        Cli = Cli->next;
    }
    return (ClihighPaim);
}
//fonctions pour la gestion des clients.
int isCliValid(client_Liste* Clients, char *tele) {
    client_Liste *tmp = Clients;
    while (tmp != NULL) {
        if (strcmp(tmp->data.ph_number, tele) == 0) {
            return -1;
        }
        tmp = tmp->next;
    }
    // Si l'element n'est pas trouver.
    return 1;
}
client_Liste* insert_client_Liste(client_Liste* Clients){
    client_Liste * nouv = malloc(sizeof(client_Liste)) ;
    int m ;
    C_ID++;
    // Open the file in append mode.
    FILE *Clifile ;
    FILE *Resfile;

    printf("\t\t\t [NOM CLIENT]: ");
    fgets(nouv->data.name,sizeof(nouv->data.name),stdin);
    nouv->data.name[strcspn(nouv->data.name, "\n")] = '\0';
    printf("\t\t\t [PRENOM CLIENT]: ");
    fgets(nouv->data.first_name,sizeof(nouv->data.first_name),stdin);
    nouv->data.first_name[strcspn(nouv->data.first_name, "\n")] = '\0';
    do{
        m =0;
        printf("\t\t\t [NUMERO DE TELEPHONE CLIENT]: ");
        fgets(nouv->data.ph_number,sizeof(nouv->data.ph_number),stdin);
        nouv->data.ph_number[strcspn(nouv->data.ph_number, "\n")] = '\0';
        if(isCliValid(Clients,nouv->data.ph_number)==-1){
            printf("\n\t\t\033[31m RESSAYER AVEC UN AUTRE NUMERO DE TELEPHONE: \033[0m\n");
            m=1;
        }
    }while(m==1);
    printf("\t\t\t [PAIMENT CLIENT]: ");
    scanf("%f", &nouv->data.paiment);
    while (getchar() != '\n');
    nouv->data.C_ID = C_ID ;
    nouv->next = Clients ;
    Clients = nouv ;
    Clifile = fopen("ClientData.txt", "a");
    if (Clifile == NULL) {
        perror("\033[31mError opening file for updating.\n");
        exit(-1);
    }
    // Write the employee data to the file.

    fprintf(Clifile, "%s,%s,%d,%s,%.2f\n", nouv->data.name, nouv->data.first_name, nouv->data.C_ID,
            nouv->data.ph_number, nouv->data.paiment);
    // Close the file
    fclose(Clifile);
    return(nouv);
}
void aff_client_Liste(client_Liste* Clients) {
    client_Liste* tmp = NULL;

    printf("\n|\033[44m-----------------------------------------------------------------------------------------------\033[0m|");
    printf("\n|\033[44m  ID           | NOM                  | PRENOM               | N.TELEPHON  | PAIMENT           \033[0m|\n");
    printf("|\033[44m-----------------------------------------------------------------------------------------------\033[0m|\n");
    tmp = Clients;

    while(tmp != NULL) {
        printf("| %d\t\t| %-20s | %-20s | %-10s  | %-18.2f|\n", tmp->data.C_ID,
                                                            tmp->data.name,
                                                            tmp->data.first_name,
                                                            tmp->data.ph_number,
                                                            tmp->data.paiment);
        printf("-------------------------------------------------------------------------------------------------\n");
        tmp = tmp->next;
    }
}
client_Liste* supp_client_Liste(client_Liste* Clients){
    int m ,ID;
    client_Liste* tmp = Clients;
    client_Liste* ptmp =NULL;
    FILE* Clifile ;
    if(tmp==NULL){
        printf("\t\t\033[31mLA LISTE DES CLIENTS EST VIDE:\033[0m\n");
        return NULL;
    }
    do {
        m=0;
        aff_client_Liste(Clients);
        printf("\t\tENTRER L'ID QUE TU VEUX SUPPRIMER DE LA LISTE (-1 -> exit) :");
        scanf("%d",&ID);
            if(ID != -1){
                while (tmp != NULL) {
                if ( tmp->data.C_ID == ID) {
                    if (ptmp == NULL) {
                        Clients = tmp->next;
                        free(tmp);
                        tmp = Clients;
                    } else {
                        ptmp->next = tmp->next;
                        free(tmp);
                        tmp = ptmp->next;
                    }
                    // After deleting, exit the function
                    Clifile = give_Client_base(Clifile,Clients);
                    Clients = get_Client_base(Clifile,Clients);
                    return Clients ;
                } else {
                    ptmp = tmp;
                    tmp = tmp->next;
                }
            }
            // If we reach here, it means no match was found
            printf("\033[31mNo employee with the given ID found.\033[0m\n");
            m=1;
            system("pause");
            }else{
                return Clients;
            }
        }while(m==1);
    }
client_Liste* modifier_client_liste(client_Liste* Clients){
    int m , p , k;
    client_Liste* tmp  = Clients;
    FILE* Clifile;
    char choix[ELEMENT_SIZE];
    char inser[ELEMENT_SIZE];
    if(tmp ==NULL){
        printf("\t\t\033[31mLA LISTE DE CLIENTS EST VIDE:\033[0m\n");
        return NULL;
    }
    do{
        m =0;
        aff_client_Liste(Clients);
        printf("\t\tENTRER N'IMPORTE INFORMATION QUE TU VEUX MODIFIER DE LA LISTE EN SPECIFIANT L'ID DE CLIENT SUIVI D'ELEMENT QUI SERA MODIFIER(4:NOM->morad):");
        fgets(choix ,sizeof(choix),stdin);
        choix[strcspn(choix, "\n")] = '\0';
        char* token = strtok(choix, ":");

        client_Liste* current = tmp; // Create a separate pointer for traversal

        while (current != NULL) {
            if (current->data.C_ID == atof(token)) {
                tmp = current; // Update tmp to the current position
                break;
            }
            current = current->next;
        }
        if (current == NULL) {
            printf("\n\t\t\033[31mWE DIDN'T FIND ANY ELEMENT WITH THIS ID\033[0m");
            m = 1;
            break;
        }
        token = strtok(NULL, ":");
        char* String = strtok(token, "->");
        char ELEMENT[ELEMENT_SIZE];
        strcpy(ELEMENT, String);
        String = strtok(NULL, "->");
        char Modifier[ELEMENT_SIZE];
        strcpy(Modifier, String);

        if(strcmp(ELEMENT,"NOM")==0){
            k=1;
            do{
                if(k>1){
                    printf("\n\t\tENTRER A NOUVEAU LE NOM EXISTANT QUE TU VEUX CHANGER :");
                    fgets(Modifier,sizeof(Modifier),stdin);
                    Modifier[strcspn(Modifier, "\n")] = '\0';
                }
                p=0;
                if(strcmp(Modifier,tmp->data.name)==0){
                    printf("\t\tDONNER LE NOUVEAU NOM DE CLIENT #%d:",tmp->data.C_ID);
                    fgets(inser,sizeof(inser),stdin);
                    inser[strcspn(inser, "\n")] = '\0';
                    strcpy(tmp->data.name,inser);
                }
                else{
                    printf("\n\t\t\033[31mLE NOM ENTRER COMME UN NOM DEJA EXIST EST PAS VALID VERIFIER LA LIGNE D'ID #%d ET RESSAYER\033[0m",tmp->data.C_ID);
                    k++;
                    p=1;
                }
            }while(p==1);
        }else if(strcmp(ELEMENT,"PRENOM")==0){
            k=1;
            do{
                if(k>1){
                    printf("\n\t\tENTRER A NOUVEAU LE PRENOM EXISTANT QUE TU VEUX CHANGER :");
                    fgets(Modifier,sizeof(Modifier),stdin);
                    Modifier[strcspn(Modifier, "\n")] = '\0';
                }
                p=0;
                if(strcmp(Modifier,tmp->data.first_name)==0){
                    printf("\t\tDONNER LE NOUVEAU PRENOM DE CLIENT #%d:",tmp->data.C_ID);
                    fgets(inser,sizeof(inser),stdin);
                    inser[strcspn(inser, "\n")] = '\0';
                    strcpy(tmp->data.first_name,inser);
                }
                else{
                    printf("\t\t\033[31mLE PRENOM ENTRER COMME UN PRENOM DEJA EXIST EST PAS VALID VERIFIER LA LIGNE D'ID #%d ET RESSAYER\033[0m",tmp->data.C_ID);
                    k++;
                    p=1;
                }
            }while(p==1);
        }else if(strcmp(ELEMENT,"N.TELEPHON")==0){
            k=1;
            do{
                if(k>1){
                    printf("\n\t\tENTRER A NOUVEAU LE PHONE NUMBER EXISTANT QUE TU VEUX CHANGER :");
                    fgets(Modifier,sizeof(Modifier),stdin);
                    Modifier[strcspn(Modifier, "\n")] = '\0';
                }
                p=0;
                if(strcmp(Modifier,tmp->data.ph_number)==0){
                    printf("\t\tDONNER LE NOUVEAU PHONE NUMBER DE CLIENT #%d:",tmp->data.C_ID);
                    fgets(inser,sizeof(inser),stdin);
                    inser[strcspn(inser, "\n")] = '\0';
                    strcpy(tmp->data.ph_number,inser);
                }
                else{
                    printf("\t\t\033[31mLE PHONE NUMBER ENTRER COMME UN DEJA EXIST EST PAS VALID VERIFIER LA LIGNE D'ID #%d ET RESSAYER\033[0m",tmp->data.C_ID);
                    k++;
                    p=1;
                }
            }while(p==1);
        }else if(strcmp(ELEMENT,"PAIEMENT")==0){
            k=1;
            do{
                if(k>1){
                    printf("\n\t\tENTRER A NOUVEAU LE PAIEMENT EXISTANT QUE TU VEUX CHANGER :");
                    fgets(Modifier,sizeof(Modifier),stdin);
                    Modifier[strcspn(Modifier, "\n")] = '\0';
                }
                p=0;
                if(tmp->data.paiment== atof(Modifier)){
                    printf("\t\tDONNER LE NOUVEAU PAIEMENT D'EMPLOIER #%d:",tmp->data.C_ID);
                    fgets(inser,sizeof(inser),stdin);
                    inser[strcspn(inser, "\n")] = '\0';
                    tmp->data.paiment = atof(inser);
                }
                else{
                    printf("\t\t\033[31mLE PAIEMENT ENTRER COMME UN DEJA EXIST EST PAS VALID VERIFIER LA LIGNE D'ID #%d ET RESSAYER\033[0m",tmp->data.C_ID);
                    k++;
                    p=1;
                }
            }while(p==1);
        }else  {
            system("cls");
            m=1;
        }
    }while(m==1);
    system("cls");
    aff_client_Liste(Clients);
    Clifile = give_Client_base(Clifile,Clients);
    Clients = get_Client_base(Clifile,Clients);
    return Clients;
}

client_Liste* chercher_client_liste(client_Liste* Clients){
    int m ;
    client_Liste* tmp = Clients ;
    client_Liste* nouv = NULL ;
    char choix[ELEMENT_SIZE];
    if(tmp ==NULL ){
        printf("\t\t\033[31mLA LISTE DES CLIENTS EST VIDE\033[0m");
        return nouv ;
    }
    do{
        m =0 ;
        aff_client_Liste(Clients);
        printf("\t\tENTRER N'IMPORTE INFORMATION QUE TU VEUT CHERCHER DANS LA LISTE (EXEMPLE=>NOM:samir):");
        fgets(choix,sizeof(choix),stdin);
        choix[strcspn(choix, "\n")] = '\0';
        char* token = strtok(choix,":");
        char* Categorie = strdup(token);
        token = strtok(NULL,":");
        char* Chercher = strdup(token);
        if(strcmp(Categorie,"ID")==0){
            while(tmp!= NULL){
                if(tmp->data.C_ID == atof(Chercher)){
                    nouv = dupliquer_Clients_liste(nouv,tmp->data);
                }
                tmp=tmp->next;
            }
        }else if(strcmp(Categorie,"NOM")==0){
            while(tmp!= NULL){
                if(strcmp(Chercher,tmp->data.name) ==0){
                    nouv = dupliquer_Clients_liste(nouv,tmp->data);
                }
                tmp = tmp->next;
            }
        }else if(strcmp(Categorie,"PRENOM")==0){
            while(tmp!= NULL){
                if(strcmp(Chercher,tmp->data.first_name) ==0){
                    nouv = dupliquer_Clients_liste(nouv,tmp->data);
                }
                tmp = tmp->next;
            }
        }else if(strcmp(Categorie,"N.TELEPHON")==0){
            while(tmp!= NULL){
                if(strcmp(Chercher,tmp->data.ph_number) ==0){
                    nouv = dupliquer_Clients_liste(nouv,tmp->data);
                }
                tmp = tmp->next;
            }
        }else if(strcmp(Categorie,"PAIEMENT")==0){
            while(tmp!= NULL){
                if(tmp->data.paiment == atof(Chercher)){
                    nouv = dupliquer_Clients_liste(nouv,tmp->data);
                }
                tmp = tmp->next;
            }
        }else{
            system("cls");
            m=1;
        }
    }while (m==1);
    system("cls");
    aff_client_Liste(nouv);
    return nouv ;

}
client_Liste* Trier_client_liste(client_Liste* Clients){
    int m ,type,save;
    char choix[ELEMENT_SIZE];
    FILE* Clifile ;
    Client tri  ;
    client_Liste* tmp1 = Clients;
    client_Liste* tmp2 = Clients;
    client_Liste* result = Clients ;
    if (tmp1 == NULL){
        printf("\t\t\033[31mLA LISTE DES CLIENTS EST VIDE:\033[0m\n");
        return NULL ;
    }
    if (tmp1->next == NULL){
        printf("\t\t\033[32mLA LISTE DES CLIENTS EST TRIER:\033[0m\n");
        return Clients ;
    }
    do{
        m=0;
        aff_client_Liste(Clients);
        printf("\t\tENTRER LE NOM DE LA CASE QUE TU VEUT TRIER AVEC, EN SPECIFIANT LE TYPE DE TRIYAGE (EXEMPLE=>EMPLOIER ID:DESC) : ");
        fgets(choix,sizeof(choix),stdin);
        choix[strcspn(choix, "\n")] = '\0';
        char* token = strtok(choix,":");
        char* Categorie = strdup(token);
        token = strtok(NULL,":");
        char* Trier =strdup(token);
        if(strcmp(Trier,"DESC")==0){
            type = -1 ;
            break;
        }else if(strcmp(Trier,"INSC")==0){
            type = 1 ;
        }else{
            printf("\t\t\033[31mINVALID INPUT RESSAYER SOIT AVEC \"DESC\" OU \"INSC\":\033[0m");
            continue;
        }
        if(strcmp(Categorie,"ID")==0){
            while (tmp1->next != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && tmp2->data.C_ID <tmp1->data.C_ID){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && tmp2->data.C_ID >tmp1->data.C_ID){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
                tmp1 =tmp1->next;
            }
        }else if(strcmp(Categorie,"NOM")==0){
            while (tmp1->next != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && strcmp(tmp2->data.name,tmp1->data.name) < 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && strcmp(tmp2->data.name,tmp1->data.name) > 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
                tmp1 =tmp1->next;
            }
        }else if(strcmp(Categorie,"PRENOM")==0){
            while (tmp1->next != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && strcmp(tmp2->data.first_name,tmp1->data.first_name) < 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && strcmp(tmp2->data.first_name,tmp1->data.first_name) > 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
                tmp1 =tmp1->next;
            }
        }else if(strcmp(Categorie,"N.TELEPHON")==0){
            while (tmp1->next != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && strcmp(tmp2->data.ph_number,tmp1->data.ph_number) < 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && strcmp(tmp2->data.ph_number,tmp1->data.ph_number) > 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
                tmp1 =tmp1->next;
            }
        }else if(strcmp(Categorie,"PAIMENT")==0){
            while (tmp1 != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && tmp2->data.paiment <tmp1->data.paiment){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && tmp2->data.paiment >tmp1->data.paiment){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
            tmp1 =tmp1->next;
            }
        }else  {
            system("cls");
            m=1;
        }
    }while(m==1);
    system("cls");
    aff_client_Liste(result);
    printf("\t\t\033[32mVOULLEZ SAUVGARDER LE NOUVEAU TRIAGE OU NON ,SI OUI TAPER 1 SINON N'IMPORTE NOMBRE :\033[0m");
    scanf("%d",&save);
    if(save ==1){
        Clifile = give_Client_base(Clifile,Clients);
        Clients = get_Client_base(Clifile,Clients);
        return Clients ;
    }
    else{
        return result;
    }

}

// Fonction pour chercher le plus cher plat.
Repass PriceSearch(RepasListe *Head) {
        RepasListe *Plat = Head;
        float HighPrice = Plat->data.prix;
        Repass platHighPrice = Plat->data;

        if (Head == NULL) {
            printf("Liste d'employes vide.\n");
            return;
        }
        while (Plat != NULL) {
            if (Plat->data.prix > HighPrice) {
                HighPrice = Plat->data.prix;
                platHighPrice = Plat->data;
            }
            Plat = Plat->next;
        }
        return platHighPrice;
    }

//fonction pour la gestion de repas
RepasListe* insert_Repas_Liste(RepasListe* Repas){
    RepasListe* nouv = malloc(sizeof(RepasListe));
    R_ID++ ;
    // Open the file in append mode.
    FILE *Repfile ;

    printf("\t\t\t[NOM REPAS] :");
    fgets(nouv->data.name,sizeof(nouv->data.name),stdin);
    nouv->data.name[strcspn(nouv->data.name, "\n")] = '\0';
    printf("\t\t\t[PRIX Repas]:");
    scanf("%f",&nouv->data.prix);
    getchar();
    printf("\t\t\t[CONSOMATION DU TEMPS]:");
    fgets(nouv->data.consomation_par_temps,sizeof(nouv->data.consomation_par_temps),stdin);
    nouv->data.consomation_par_temps[strcspn(nouv->data.consomation_par_temps, "\n")] = '\0';
    nouv->data.R_ID = R_ID ;
    nouv->next = Repas ;
    Repas = nouv ;
    Repfile = fopen("RepasData.txt", "a");
    if (Repfile == NULL) {
        perror("Error opening file for updating.\n");
        exit(-1);
    }
    // Write the employee data to the file.
    fprintf(Repfile, "%s,%d,%.2f,%s\n", nouv->data.name, nouv->data.R_ID,
            nouv->data.prix,nouv->data.consomation_par_temps);
    // Close the file
    fclose(Repfile);

    return(nouv);
}
void aff_Repas_Liste(RepasListe* Repas) {
    RepasListe* tmp = Repas ;

    printf("\n|\033[44m----------------------------------------------------------------------------\033[0m|");
    printf("\n|\033[44m ID            | NOM                  | PRIX  (DHS)   | TEMPS               \033[0m|\n");
    printf("|\033[44m----------------------------------------------------------------------------\033[0m|\n");

    while(tmp != NULL) {
        printf("| %d\t\t| %-20s | %-14.2f| %-20s|\n", tmp->data.R_ID,
                                                        tmp->data.name,
                                                        tmp->data.prix,
                                                        tmp->data.consomation_par_temps);
        printf("------------------------------------------------------------------------------\n");
        tmp = tmp->next;
    }
}
RepasListe* supp_Repas_Liste(RepasListe* Repas){
    int m ,ID;
    RepasListe* tmp =Repas;
    RepasListe* ptmp =NULL;
    FILE* Repfile ;
    if(tmp==NULL){
        printf("\t\t\033[31mLA LISTE EST VIDE:\033[0m\n");
        return NULL;
    }
    do{
        m=0;
        system("cls");
        aff_Repas_Liste(Repas);
        printf("\t\tENTRER L'ID QUE TU VEUX SUPPRIMER DE LA LISTE (-1 -> exit) :");
        scanf("%d",&ID);
        if(ID != -1){
            while (tmp != NULL) {
            if ( tmp->data.R_ID == ID) {
                if (ptmp == NULL) {
                    Repas = tmp->next;
                    free(tmp);
                    tmp = Repas;
                } else {
                    ptmp->next = tmp->next;
                    free(tmp);
                    tmp = ptmp->next;
                }
                // After deleting, exit the function
                Repfile = give_Repas_base(Repfile , Repas);
                Repas = get_Repas_base(Repfile,Repas);
                return Repas ;
            } else {
                ptmp = tmp;
                tmp = tmp->next;
            }
        }
        // If we reach here, it means no match was found
        printf("\033[31mNo Repas with the given ID found.\033[0m\n");
        m=1;
        system("pause");
        }else{
            return Repas;
        }
    }while(m==1);
}
RepasListe* modifier_Repas_liste(RepasListe* Repas){
    int m , p ,k ;
    RepasListe* tmp  = Repas;
    FILE* Repfile ;
    char choix[ELEMENT_SIZE];
    char inser[ELEMENT_SIZE]; // Use array instead of malloc
    if(tmp ==NULL){
        printf("\t\t\033[31mLA LISTE DE REPAS EST VIDE:\033[0m\n");
        return NULL;
    }
    do{
        m =0;
        aff_Repas_Liste(Repas);
        printf("\t\tENTRER N'IMPORTE INFORMATION QUE TU VEUX MODIFIER DE LA LISTE EN SPECIFIANT L'ID DE Repas SUIVI D'ELEMENT QUI SERA MODIFIER(4:NOM->morad):");
        fgets(choix ,sizeof(choix),stdin);
        choix[strcspn(choix, "\n")] = '\0';
        char* token = strtok(choix, ":");

        RepasListe* current = tmp ; // Create a separate pointer for traversal

        while (current != NULL) {
            if (current->data.R_ID == atof(token)) {
                tmp = current; // Update tmp to the current position
                break;
            }
            current = current->next;
        }
        if (current == NULL) {
            printf("\n\t\tv\033[31mWE DIDN'T FIND ANY ELEMENT WITH THIS ID\033[0m");
            m = 1;
            break;
        }

        token = strtok(NULL, ":");
        char* String = strtok(token, "->");
        char ELEMENT[ELEMENT_SIZE];
        strcpy(ELEMENT, String);
        String = strtok(NULL, "->");
        char Modifier[ELEMENT_SIZE];
        strcpy(Modifier, String);
        if(strcmp(ELEMENT,"NOM")==0){
            k=1;
            do{
                if(k>1){
                    printf("\n\t\tENTRER A NOUVEAU LE NOM EXISTANT QUE TU VEUX CHANGER :");
                    fgets(Modifier,sizeof(Modifier),stdin);
                    Modifier[strcspn(Modifier, "\n")] = '\0';
                }
                p=0;
                if(strcmp(Modifier,tmp->data.name)==0){
                    printf("\t\tDONNER LE NOUVEAU NOM DE REPAS #%d:",tmp->data.R_ID);
                    fgets(inser, sizeof(inser), stdin);
                    inser[strcspn(inser, "\n")] = '\0'; // Remove newline character
                    strcpy(tmp->data.name, inser);
                }
                else{
                    printf("\t\t\033[31mLE NOM ENTRER COMME UN NOM DEJA EXIST EST PAS VALID VERIFIER LA LIGNE D'ID #%d ET RESSAYER\033[0m",tmp->data.R_ID);
                    k++;
                    p=1;
                }
            }while(p==1);

        }else if(strcmp(ELEMENT,"PRIX")==0){
            k=1;
            do{
                if(k>1){
                    printf("\n\t\tENTRER A NOUVEAU LE PRIX EXISTANT QUE TU VEUX CHANGER :");
                    fgets(Modifier,sizeof(Modifier),stdin);
                    Modifier[strcspn(Modifier, "\n")] = '\0';
                }
                p=0;
                if(tmp->data.prix==atof(Modifier)){
                    printf("\t\tDONNER LE NOUVEAU PRIX DE REPAS #%d:",tmp->data.R_ID);
                    fgets(inser,sizeof(inser),stdin);
                    inser[strcspn(inser, "\n")] = '\0'; // Remove newline character
                    tmp->data.prix = atof(inser);
                }
                else{
                    printf("\t\t\033[31mLE PRIX ENTRER COMME UN PRIX DEJA EXIST EST PAS VALID VERIFIER LA LIGNE D'ID #%d ET RESSAYER\033[0m",tmp->data.R_ID);
                    k++;
                    p=1;
                }
            }while(p==1);
        }else if(strcmp(ELEMENT,"TEMPS")==0){
            k=1;
            do{
                if(k>1){
                    printf("\n\t\tENTRER A NOUVEAU LE TEMPS EXISTANT QUE TU VEUX CHANGER :");
                    fgets(Modifier,sizeof(Modifier),stdin);
                    Modifier[strcspn(Modifier, "\n")] = '\0';
                }
                p=0;
                if(strcmp(Modifier,tmp->data.consomation_par_temps)==0){
                    printf("\t\tDONNER LA NOUVELLE DUREE DE TEMPS DE Repas #%d:",tmp->data.R_ID);
                    fgets(inser,sizeof(inser),stdin);
                    inser[strcspn(inser, "\n")] = '\0'; // Remove newline character
                    strcpy(tmp->data.consomation_par_temps,inser);
                }
                else{
                    printf("\t\t\033[31mLA DUREE DE TMPS ENTRER COMME UNE DEJA EXISTE EST PAS VALID VERIFIER LA LIGNE D'ID #%d ET RESSAYER\033[0m",tmp->data.R_ID);
                    k++;
                    p=1;
                }
            }while(p==1);
        }else  {
            system("cls");
            m=1;
        }
    }while(m==1);
    system("cls");
    aff_Repas_Liste(Repas);
    Repfile = give_Repas_base(Repfile , Repas);
    Repas = get_Repas_base(Repfile,Repas);
    return Repas;

}

RepasListe* chercher_Repas_liste(RepasListe* Repas){
    int m ;
    RepasListe* tmp = Repas ;
    RepasListe* nouv = NULL ;
    char  choix[ELEMENT_SIZE];
    if(tmp ==NULL ){
        printf("\t\tLA LISTE DES Repas EST VIDE");
        return nouv ;
    }
    do{
        m =0 ;
        aff_Repas_Liste(Repas);
        printf("\t\tENTRER N'IMPORTE INFORMATION QUE TU VEUT CHERCHER DANS LA LISTE (EXEMPLE=>NOM Repas:PIZZA):");
        fgets(choix,sizeof(choix),stdin);
        choix[strcspn(choix, "\n")] = '\0';
        char* token = strtok(choix,":");
        char* Categorie = strdup(token);
        token = strtok(NULL,":");
        char* Chercher =strdup(token);
        if(strcmp(Categorie,"ID")==0){
            while(tmp!= NULL){
                if(tmp->data.R_ID == atof(Chercher)){
                    nouv = dupliquer_repas_liste(nouv,tmp->data);
                }
                tmp=tmp->next;
            }
        }else if(strcmp(Categorie,"NOM")==0){
            while(tmp!= NULL){
                if(strcmp(Chercher,tmp->data.name) ==0){
                    nouv = dupliquer_repas_liste(nouv,tmp->data);
                }
                tmp = tmp->next;
            }
        }else if(strcmp(Categorie,"PRIX")==0){
            while(tmp!= NULL){
                if(atof(Chercher)==tmp->data.prix){
                    nouv = dupliquer_repas_liste(nouv,tmp->data);
                }
                tmp = tmp->next;
            }
        }else if(strcmp(Categorie,"TEMPS")==0){
            while(tmp!= NULL){
                if(strcmp(tmp->data.consomation_par_temps, Chercher)==0){
                    nouv = dupliquer_repas_liste(nouv,tmp->data);
                }
                tmp = tmp->next;
            }
        }else{
            system("cls");
            m=1;
        }
    }while (m==1);
    system("cls");
    aff_Repas_Liste(nouv);
    return nouv ;

}
RepasListe* Trier_Repas_liste(RepasListe* Repas){
    int m, type, save;
    char choix[ELEMENT_SIZE];
    FILE* Repfile;
    Repass tri;
    RepasListe* tmp1 = Repas ;
    RepasListe* tmp2 = Repas ;
    RepasListe* result = Repas ;
    if (tmp1 == NULL){
        printf("\t\t\033[31mLA LISTE DES REPAS EST VIDE:\033[0m\n");
        return NULL;
    }
    if (tmp1->next == NULL){
        printf("\t\t\033[32mLA LISTE DES REPAS EST TRIER:\033[0m\n");
        return Repas ;
    }
    do {
        m = 0;
        aff_Repas_Liste(Repas);
        printf("\t\tENTRER LE NOM DE LA CASE QUE TU VEUT TRIER AVEC EN SPECIFIANT LE TYPE DE TRIYAGE (EXEMPLE=>ID:DESC)");
        fgets(choix, sizeof(choix), stdin);
        choix[strcspn(choix, "\n")] = '\0';
        char* token = strtok(choix,":");
        char* Categorie = strdup(token);
        token = strtok(NULL,":");
        char* Trier =strdup(token);
        if(strcmp(Trier,"DESC")==0){
            type = -1 ;
            break;
        }else if(strcmp(Trier,"INSC")==0){
            type = 1 ;
        }else{
            printf("\t\t\033[31mINVALID INPUT RESSAYER SOIT AVEC \"DESC\" OU \"INSC\":\033[0m");
            continue ;
        }
        if (strcmp(Categorie,"ID") == 0) {
            while (tmp1->next != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && tmp2->data.R_ID <tmp1->data.R_ID){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && tmp2->data.R_ID >tmp1->data.R_ID){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
                tmp1 =tmp1->next;
            }
        }else if(strcmp(Categorie,"NOM")==0){
            while (tmp1->next != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && strcmp(tmp2->data.name,tmp1->data.name) < 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && strcmp(tmp2->data.name,tmp1->data.name) > 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
                tmp1 =tmp1->next;
            }
        }else if(strcmp(Categorie,"PRIX")==0){
            while (tmp1 != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && tmp2->data.prix <tmp1->data.prix){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && tmp2->data.prix >tmp1->data.prix){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
            tmp1 =tmp1->next;
            }
        }else if(strcmp(Categorie,"TEMPS")==0){
            while (tmp1->next != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && strcmp(tmp2->data.consomation_par_temps,tmp1->data.consomation_par_temps) < 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && strcmp(tmp2->data.consomation_par_temps,tmp1->data.consomation_par_temps) > 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
                tmp1 =tmp1->next;
            }
        }else  {
            system("cls");
            m=1;
        }
    }while(m==1);
    system("cls");
    aff_Repas_Liste(result);
    printf("\t\t\033[32mVOULLEZ SAUVGARDER LE NOUVEAU TRIAGE OU NON ,SI OUI TAPER 1 SINON N'IMPORTE NOMBRE :\033[0m");
    scanf("%d",&save);
    if(save ==1){
        Repfile = give_Repas_base(Repfile , Repas);
        Repas = get_Repas_base(Repfile,Repas);
        return Repas ;
    }
    else{
        return result;
    }
}

//fonctions pour la gestion de commande
int existe_plat_test(RepasListe* Repas_valables ,char* string){
    RepasListe* tmp =Repas_valables ;
    while(tmp!= NULL){
        if(strcmp(tmp->data.name,string)==0){
            return 1 ;
        }
        tmp = tmp->next;
    }
    return 0;
}
float get_prix_total(char** plats , int nbr_plat,RepasListe* Repas_valables){
    float prix =0;
    for(int i =0 ;i<nbr_plat ;i++){
        RepasListe * tmp = Repas_valables ;
        while(tmp !=NULL){
            if(strcmp(tmp->data.name,plats[i])==0){
                prix += tmp->data.prix;
                break;
            }
            tmp=tmp->next;
        }
    }
    return prix ;
}
int verify_tab(char** tab , int dim , char* string ){
    for(int i =0 ;i<dim;i++){
        if(strcmp(tab[i],string)==0){
            return 0;
        }
    }
    return 1 ;
}

char* max_group_time(char** plats, int nbr_plat, RepasListe* Repas_valables) {
char* max_time = NULL;  // Pointer to the maximum time string
    int max_minutes = -1;    // Maximum number of minutes

    // Iterate over the list of meals
    RepasListe* tmp = Repas_valables;
    while (tmp != NULL) {
        for (int i = 0; i < nbr_plat; i++) {
            if (strcmp(tmp->data.name, plats[i]) == 0) {
                // Parse the time string to extract the number of minutes
                char* min_str = strtok(tmp->data.consomation_par_temps, "min");
                if (min_str != NULL) {
                    int minutes = atoi(min_str);
                    if (minutes > max_minutes) {
                        max_minutes = minutes;
                        max_time = tmp->data.consomation_par_temps;
                    }
                }
                break;
            }
        }
        tmp = tmp->next;
    }

    // Return the maximum time string found
    return max_time;
}
char* String_plates_exist(Commande data) {
    char* plats = malloc(sizeof(char) * ELEMENT_SIZE); // Allocate memory for the string
    if (plats == NULL) {
        // Handle memory allocation failure
        return NULL;
    }
    plats[0] = '\0'; // Initialize the string
    int n = data.nbr_plat;
    for (int i = 0; i < n; i++) {
        strcat(plats, data.plats[i]); // Concatenate each plat
        strcat(plats, "-"); // Add comma separator
    }
    // Remove the last comma if it exists
    if (n > 0) {
        plats[strlen(plats) - 1] = '\0';
    }
    return plats;
}
Commande  GrandeSearch(commande_liste* Head){
    commande_liste* tmp =Head;
    float HighCom = tmp->data.consomation;
    Commande HighComPrix = tmp->data ;
    if (Head == NULL) {
            printf("Liste de commande vide.\n");
            return;
        }
        while (tmp != NULL) {
            if (tmp->data.consomation > HighCom) {
                HighCom = tmp->data.consomation;
                HighComPrix = tmp->data;
            }
            tmp = tmp->next;
        }
        return HighComPrix;
}
commande_liste* insert_commande_Liste(commande_liste* Commandes,RepasListe* Repas_valables,client_Liste* Clients_valables){
    int  choix , cas,m,t,o,inser,n=0;
    float prix_total= 0;
    char commande_test[ELEMENT_SIZE];
    commande_liste *nouv = malloc(sizeof(commande_liste));
    FILE *Clifile ;
    FILE * Comfile ;
    Cm_ID++;
    nouv->data.Cm_ID = Cm_ID;
    if(Repas_valables == NULL ){
        printf("\t\t\033[31m[IL N'YA PAS AUCUN REPAS AU MEMENT] :\033[0m\n");
        printf("\t\t\t\033[31m[DEMANDER AU CHEF D'AJOUTER DES REPAS]\033[0m\n");
        return Commandes ;
    }
    printf("\t\t[LA COMMENDE CONTIENNE COMBIENE DE REPAS]:");
    scanf("%d",&choix);
    while (getchar() != '\n');
    nouv->data.plats = malloc(sizeof(char*)*choix);
    nouv->data.etat = malloc(sizeof(char)*ELEMENT_SIZE);
    for(int i=0;i<choix;i++){
        nouv->data.plats[i]=malloc(sizeof(char)*ELEMENT_SIZE);
    }
    nouv->data.nbr_plat = choix;
    for(int i= 0 ; i<choix ; i++ ) {
        t=1;
        printf("\t\t\t\t[LE PLAT #%d] :\n",i+1);
        do {
            m=0;
            printf("\t\t\t\t\t\t[LE NOM PLAT]:");
            fgets(commande_test,sizeof(commande_test),stdin);
            commande_test[strcspn(commande_test, "\n")] = '\0';
            cas = existe_plat_test(Repas_valables,commande_test);
            if(cas ==1 && verify_tab(nouv->data.plats,i,commande_test)==1){
                strcpy(nouv->data.plats[i], commande_test);
                RepasListe* tmp = Repas_valables ;
                while (tmp!=NULL)
                {
                    if(strcmp(nouv->data.plats[i],tmp->data.name)==0){
                        prix_total += tmp->data.prix ;
                    }
                    tmp=tmp->next;
                }

            }
            else if(cas == 0){
                printf("\t\t\033[31mCE PLAT N'EXISTE PAS MERCI D'ENTRER UN PLAT VALID:\033[0m\n");
                aff_Repas_Liste(Repas_valables);
                system("pause");
                m=1;
            }
        }while(m==1);
    }
    printf("\t\tLE PRIX DE CETTE COMMANDE EST %.2fDHS\n",prix_total);
    nouv->data.consomation = prix_total;
    do {
        while (getchar() != '\n');
        m=0;
        char Client_name [ELEMENT_SIZE];
        char Client_ph_number [ELEMENT_SIZE];
        float paiment ;
        printf("\t\t[LE NOM DU CLIENT QUI A COMMENDER]:");
        fgets(Client_name,sizeof(Client_name),stdin);
        Client_name[strcspn(Client_name, "\n")] = '\0';
        while (getchar() != '\n');
        printf("\t\t[SON NUMERO DE TELEPHONE]:");
        fgets(Client_ph_number,sizeof(Client_ph_number),stdin);
        Client_ph_number[strcspn(Client_ph_number, "\n")] = '\0';
        cas = existe_client_test(Clients_valables,Client_name,Client_ph_number);
        if(cas==0 ){/*Must heve think more in this */
            printf("\t\t\033[31m[LE CLIENT SAISIE N'EXISTE PAS].......\033[0m\n");
            while (getchar() != '\n');
            do{
                o=0;
                printf("\t\tVOULEZ VOUS L'INSERER UN NOUVEAU CLIENT (1=Oui)(0=Non):");
                scanf("%d",&choix);
                    if(choix ==1){
                        while (getchar() != '\n');
                        Clients_valables = insert_client_Liste(Clients_valables);
                        client_Liste* tmp = Clients_valables ;
                        nouv->data.Client=tmp->data;
                        strcpy(nouv->data.etat, "attente");
                        nouv->data.string_plat = malloc(sizeof(char)*ELEMENT_SIZE);
                        strcpy(nouv->data.string_plat,String_plates_exist(nouv->data));
                        nouv->data.string_plat[strcspn(nouv->data.string_plat, "\n")] = '\0';
                        nouv->next=Commandes ;
                        Commandes = nouv ;
                        Comfile = give_Commande_base(Comfile ,Commandes);
                        do{
                            t=0;
                            if(tmp->data.paiment < nouv->data.consomation){
                                printf("\n\t\t\033[31mLE PAIMENT DE CLIENT N'EST PAS SUFFISANT AU PRIX DE CETTE COMANDE:\033[0m\n");
                                printf("\t\tDEMANDER AU CLIENT D'AJOUTER %.2fDHS OU PLUS POUR SATISFAIRE L'ACHAT\n",nouv->data.consomation-tmp->data.paiment);
                                printf("\t\tENTRER ICI COMBIEN LE CLIENT A PAYER PLUS :");
                                scanf("%f",&paiment);
                                tmp->data.paiment += paiment;
                                nouv->data.Client = tmp->data ;
                                Clifile = give_Client_base(  Clifile ,Clients_valables);
                                Clients_valables = get_Client_base(Clifile,Clients_valables);
                                t=1;
                            }
                            else{
                                tmp->data.paiment -= nouv->data.consomation;
                                printf("\n\t\t\033[32mMERCI POUR VOTRE ACHAT LE RETENU EST %.2fDHS\033[0m\n",tmp->data.paiment);
                                printf("\t\t\033[32mMERCI D'ATTENDRE %s MINUTES POUR QUE VOTRE COMANDE SOIT PRETE\033[0m\n",max_group_time(nouv->data.plats,nouv->data.nbr_plat,Repas_valables));
                                nouv->data.Client = tmp->data ;
                                Clifile = give_Client_base(  Clifile ,Clients_valables);
                                Clients_valables = get_Client_base(Clifile,Clients_valables);
                                strcpy(nouv->data.etat, "preparation");
                                Comfile = give_Commande_base(Comfile ,Commandes);
                            }
                        }while(t==1);
                    }else if(choix ==0){
                        m=1;
                        break;
                    }
                    else{
                        printf("\t\t\033[31mINVALID INPUT\033[0m\n");
                        o=1;
                    }
            }while(o==1);
        }else {
            client_Liste* tmp = Clients_valables ;
                while(tmp->next!=NULL){
                    if(strcmp(tmp->data.name , Client_name)==0 && strcmp(Client_ph_number,tmp->data.ph_number)==0){
                        nouv->data.Client=tmp->data;
                        break;
                    }
                    tmp = tmp->next;
                }
            strcpy(nouv->data.etat, "attente");
            nouv->data.string_plat = malloc(sizeof(char)*ELEMENT_SIZE);
            strcpy(nouv->data.string_plat,String_plates_exist(nouv->data));
            nouv->data.string_plat[strcspn(nouv->data.string_plat, "\n")] = '\0';
            nouv->next=Commandes ;
            Commandes = nouv ;
            Comfile = give_Commande_base(Comfile ,Commandes);
            do{
                t=0;
                if(tmp->data.paiment < nouv->data.consomation){
                    printf("\n\t\t\033[31mLE PAIMENT DE CLIENT N'EST PAS SUFFISANT AU PRIX DE CETTE COMANDE:\033[0m\n");
                            printf("\t\tDEMANDER AU CLIENT D'AJOUTER %.2f DIRHAMS OU PLUS POUR SATISFAIRE L'ACHAT\n",nouv->data.consomation-tmp->data.paiment);
                            printf("\t\tENTRER ICI COMBIEN LE CLIENT A PAYER PLUS :");
                            scanf("%f",&paiment);
                            nouv->data.Client.paiment += paiment;
                            tmp->data.paiment += paiment;
                            nouv->data.Client = tmp->data ;
                            Clifile = give_Client_base(  Clifile ,Clients_valables);
                            Clients_valables = get_Client_base(Clifile,Clients_valables);
                            t=1;
                }else{
                        tmp->data.paiment -= prix_total;
                        printf("\n\t\t\033[32mMERCI POUR VOTRE ACHAT LE RETENU EST %.2fDHS\033[0m\n",tmp->data.paiment);
                        printf("\t\t\033[32mMERCI D'ATTENDRE %s MINUTES POUR QUE VOTRE COMANDE SOIT PRETE\033[0m\n",max_group_time(nouv->data.plats,nouv->data.nbr_plat,Repas_valables));
                        nouv->data.Client = tmp->data ;
                        Clifile = give_Client_base(  Clifile ,Clients_valables);
                        Clients_valables = get_Client_base(Clifile,Clients_valables);
                        strcpy(nouv->data.etat, "preparation");
                        Comfile = give_Commande_base(Comfile ,Commandes);
                    }
            }while(t==1);
        }
    }while(m==1);

    return (nouv);
}

void aff_commande_Liste(commande_liste* Commandes){
    commande_liste* tmp = Commandes;
    printf("\n|\033[44m---------------------------------------------------------------------------------------------------------------------------------------\033[0m|");
    printf("\n|\033[44m  ID           | PLATES                                   | CLIENT               | N.TELEPHON  | PRIX              |    ETAT           \033[0m|\n");
    printf("|\033[44m---------------------------------------------------------------------------------------------------------------------------------------\033[0m|\n");

    while(tmp != NULL) {
        printf("| %d\t\t| %-40s | %-20s | %-11s | %-17.2f |%-19s|\n", tmp->data.Cm_ID,
                                                            tmp->data.string_plat,
                                                            tmp->data.Client.name,
                                                            tmp->data.Client.ph_number,
                                                            tmp->data.consomation,
                                                            tmp->data.etat);
        printf("-----------------------------------------------------------------------------------------------------------------------------------------\n");
        tmp = tmp->next;
    }
}
commande_liste* supp_commande_Liste(commande_liste* Commandes){
    int m ,ID;
    FILE* Comfile ;
    commande_liste* tmp =Commandes;
    commande_liste* ptmp =NULL;
    if (tmp == NULL) {
        printf("\t\t\033[31mLA LISTE DE COMMANDES EST VIDE:\033[0m\n");
        return NULL;
    }
    do {
        m=0;
        aff_commande_Liste(Commandes);
        printf("\t\tENTRER L'ID QUE TU VEUX SUPPRIMER DE LA LISTE (-1 -> exit):");
        scanf("%d",&ID);
        if(ID != -1){
            while (tmp != NULL) {
            if ( tmp->data.Cm_ID == ID) {
                if (ptmp == NULL) {
                    Commandes = tmp->next;
                    free(tmp);
                    tmp = Commandes;
                } else {
                    ptmp->next = tmp->next;
                    free(tmp);
                    tmp = ptmp->next;
                }
                // After deleting, exit the function
                Comfile = give_Commande_base(Comfile ,Commandes);
                return Commandes ;
            } else {
                ptmp = tmp;
                tmp = tmp->next;
            }
        }
        // If we reach here, it means no match was found
        printf("\033[31mNo Commandes with the given ID found.\033[0m\n");
        m=1;
        system("pause");
        }else{
            return Commandes;
        }
    }while(m==1);
}
int exist_repas_test(RepasListe* Repas_valables , char * string ){
    RepasListe* tmp = Repas_valables ;
    while(tmp != NULL){
        if(strcmp(tmp->data.name,string)==0){
            return 1;
        }
        tmp = tmp->next;
    }
    return 0 ;
}
commande_liste* modifier_commande_liste(commande_liste* Commandes,RepasListe* Repas_valables,client_Liste* Clients_valables ){
    int m , p ,i,k,cas,l;
    commande_liste* tmp =Commandes;
    FILE* Comfile ;
    char choix[ELEMENT_SIZE];
    char inser[ELEMENT_SIZE]; // Use array instead of malloc
    if (tmp == NULL) {
    printf("\t\t\033[31mLA LISTE DE COMMANDES EST VIDE:\033[0m\n");
    return NULL;
    }
    do {
        m=0;
        aff_commande_Liste(Commandes);
        printf("\t\tENTRER N'IMPORTE INFORMATION QUE TU VEUX MODIFIER DE LA LISTE EN SPECIFIANT L'ID DU CLIENT SUIVI D'ELEMENT QUI SERA MODIFIER(4:NOM->morad):");
        fgets(choix ,sizeof(choix),stdin);
        choix[strcspn(choix, "\n")] = '\0';
        char* token = strtok(choix, ":");

        commande_liste* current = tmp ;

        while (current != NULL) {
            if (current->data.Cm_ID == atof(token)) {
                tmp = current; // Update tmp to the current position
                break;
            }
            current = current->next;
        }
        if (current == NULL) {
            printf("\n\t\t\033[31mWE DIDN'T FIND ANY ELEMENT WITH THIS ID\033[0m");
            m = 1;
            break;
        }

        token = strtok(NULL, ":");
        char* String = strtok(token, "->");
        char ELEMENT[ELEMENT_SIZE];
        strcpy(ELEMENT, String);
        String = strtok(NULL, "->");
        char Modifier[ELEMENT_SIZE];
        strcpy(Modifier, String);

        if(strcmp(ELEMENT,"PLATES")==0){
            k=1;
            do{
                if(k>1){
                    printf("\n\t\tENTRER A NOUVEAU LE NOM EXISTANT QUE TU VEUX CHANGER :");
                    fgets(Modifier,sizeof(Modifier),stdin);
                    Modifier[strcspn(Modifier, "\n")] = '\0';
                }
                for(i=0;i<tmp->data.nbr_plat;i++)
                    {
                        if (strcmp(Modifier, tmp->data.plats[i]) == 0 ) {
                        do{
                            l=0;
                            printf("\t\tDONNER LA NOUVELLE VALEUR QUI VA ETRE DANS CETTE PLACE :");
                            fgets(inser,sizeof(inser),stdin);
                            inser[strcspn(inser, "\n")] = '\0';
                            cas = exist_repas_test(Repas_valables,inser);
                            if(cas == 1){
                                strcpy(tmp->data.plats[i], inser);
                            }
                            else{
                                printf("\t\t\033[31mCE NOUVAUX REPAS ENTRER N'EXITSE PAS RESSAYER\033[0m\n");
                                l=1;
                            }
                        }while(l==1);
                        }
                    }
                    if(i == tmp->data.nbr_plat){
                        printf("\t\t\033[31mLE PRODUIT ENTRER COMME DEJA EXISTE EST PAS VALID VERIFIER LA LIGNE D'ID #%d ET RESSAYER\033[0m",tmp->data.Cm_ID);
                        k++;
                        p=1 ;
                    }
            }while(p==1);
        }
        else if(strcmp(ELEMENT,"CLIENT")==0)
        {
            k=1;
            do{
                if(k>1){
                    printf("\n\t\tENTRER A NOUVEAU LE NOM EXISTANT QUE TU VEUX CHANGER :");
                    fgets(Modifier,sizeof(Modifier),stdin);
                    Modifier[strcspn(Modifier, "\n")] = '\0';
                }
                p=0;
                if(strcmp(tmp->data.Client.name,Modifier) == 0)
                {
                    printf("\t\tDONNER LE NOUVEAU NOM DU CLIENT :");
                    fgets(inser,sizeof(inser),stdin);
                    inser[strcspn(inser, "\n")] = '\0';
                    client_Liste* cltmp = Clients_valables;
                    while (cltmp != NULL )
                    {
                        if(strcmp(cltmp->data.name,inser)==0 )
                            {
                                tmp->data.Client = cltmp->data;
                                break ;
                            }
                        cltmp = cltmp->next;
                    }
                    if(cltmp ==NULL )
                    {
                        do{
                            l =0 ;
                            int a ;
                            printf("\t\tCE NOUVEAU CLIENT N'EXISTE PAS VOULLEZ VOUS DE LE CREE (1/0):");
                            scanf("%d",&a);
                            switch (a)
                            {
                            case 1:
                                Clients_valables =  insert_client_Liste(Clients_valables);
                                strcpy(tmp->data.Client.name, Clients_valables->data.name) ;
                                strcpy(tmp->data.Client.ph_number, Clients_valables->data.ph_number) ;
                                break;
                            case 0:
                                break;
                            default:
                                l=1;
                                break;
                            }
                            break;
                    }while(l==1);
                    }


                }
                else{
                    printf("\t\t\033[31mLE NOM ENTRER COMME UN NOM DEJA EXIST EST PAS VALID VERIFIER LA LIGNE D'ID #%d ET RESSAYER\033[0m",tmp->data.Cm_ID);
                    k++;
                    p=1;
                }
        }while(p==1);
        }else if(strcmp(ELEMENT,"PRIX")==0){
            printf("\n\t\tTU N'A PAS LA PERMISSION DE CHANGER UN PRIX FIX :\n");
            m=1;
        }
        else if(strcmp(ELEMENT,"N.TELEPHON")==0){
            k=1;
            do{
                if(k>1){
                    printf("\n\t\tENTRER A NOUVEAU LE N.TELEPHON EXISTANT QUE TU VEUX CHANGER :");
                    fgets(Modifier,sizeof(Modifier),stdin);
                    Modifier[strcspn(Modifier, "\n")] = '\0';
                }
                p=0;
                if(strcmp(Modifier,tmp->data.Client.ph_number)==0){
                    client_Liste* cltmp = Clients_valables;
                    printf("\t\tDONNER LE NOUVEAU PHONE NUMBER DU CLIENT :");
                    fgets(inser,sizeof(inser),stdin);
                    inser[strcspn(inser, "\n")] = '\0';
                    while (cltmp != NULL) {
                        if(isvalid_Ph_number(cltmp,inser) == 1)
                        {
                            strcpy(cltmp->data.ph_number,inser);
                            strcpy(tmp->data.Client.ph_number, inser);
                            break;
                        }
                        cltmp =cltmp->next ;
                    }
                    if(cltmp == NULL )
                    {
                        printf("\t\t\033[31mID N'EXISTE PAS ENTRER UN AUTRE ID\033[0m:");
                        m=1;
                    }
                }
                else{
                    printf("\n\t\t\033[31mLE N.TELEPHON ENTRER COMME UN NUMERO DEJA EXIST EST PAS VALID VERIFIER LA LIGNE D'ID #%d ET RESSAYER\033[0m",tmp->data.Cm_ID);
                    k++;
                    p=1;
                }
            }while (p==1);
        }
        else{
            system("cls");
            m=1;
        }
    }while (m==1);
    system("cls");
    aff_commande_Liste(Commandes);
    Comfile = give_Commande_base(Comfile ,Commandes);
    return (Commandes);
}

commande_liste* chercher_commande_liste(commande_liste* Commandes){
    int m ,i;
    commande_liste* tmp =Commandes;
    commande_liste* nouv =NULL;
    char choix[ELEMENT_SIZE];
    if (tmp == NULL) {
        printf("\t\t\033[31mLA LISTE DE COMMANDES EST VIDE:\033[0m\n");
        return nouv;
    }
    do {
        m=0;
        aff_commande_Liste(Commandes);
        printf("\t\tENTRER N'IMPORTE INFORMATION QUE TU VEUX CHERCHER DE LA LISTE (EXEMPLE=>ID:8):");
        fgets(choix,sizeof(choix),stdin);
        choix[strcspn(choix, "\n")] = '\0';
        char* token = strtok(choix,":");
        char* Categorie = strdup(token);
        token = strtok(NULL,":");
        char* Chercher = strdup(token);
        if(strcmp(Categorie,"ID")==0){
            while (tmp != NULL) {
                if(tmp->data.Cm_ID == atof(Chercher)){
                    nouv = dupliquer_Commandes_liste(nouv,tmp->data);
                }
                tmp =tmp->next;
            }
        }else if(strcmp(Categorie,"PLATES")==0){
            while (tmp != NULL) {
                for(i=0;i<tmp->data.nbr_plat;i++){
                    if(strcmp(Chercher,tmp->data.plats[i])==0){
                        nouv = dupliquer_Commandes_liste(nouv,tmp->data);
                        break;
                    }
                }
                tmp =tmp->next;
            }
        }else if(strcmp(Categorie,"CLIENT")==0){
            while (tmp != NULL) {
                if(strcmp(Chercher,tmp->data.Client.name)==0){
                    nouv = dupliquer_Commandes_liste(nouv,tmp->data);
                }
                tmp =tmp->next;
            }
        }else if(strcmp(Categorie,"N.TELEPHON")==0){
            while (tmp != NULL) {
                if(strcmp(Chercher,tmp->data.Client.ph_number)==0){
                    nouv = dupliquer_Commandes_liste(nouv,tmp->data);
                }
                tmp =tmp->next;
            }
        }else if(strcmp(Categorie,"ETAT")==0){
            while (tmp != NULL) {
                if(strcmp(Chercher,tmp->data.etat)==0){
                    nouv = dupliquer_Commandes_liste(nouv,tmp->data);
                }
                tmp =tmp->next;
            }
        }else {
            system("cls");
            m=1;
        }
    }while (m==1);
    system("cls");
    aff_commande_Liste(nouv);
    return nouv;
}
commande_liste* Trier_commande_liste(commande_liste* Commandes){
    int m , type , save ,i,j;
    char choix[ELEMENT_SIZE];
    char Categorie[ELEMENT_SIZE];
    FILE* Comfile ;
    Commande tri  ;
    commande_liste* tmp1 = Commandes ;
    commande_liste* tmp2 = Commandes ;
    commande_liste* result =Commandes ;
    if (tmp1 == NULL){
        printf("\t\t\033[31mLA LISTE DES COMANDES EST VIDE:\033[0m\n");
        return NULL ;
    }
    if (tmp1->next == NULL){
        printf("\t\t\033[32mLA LISTE DES COMANDES EST TRIER:\033[0m\n");
        return Commandes ;
    }
    do{
        m=0;
        aff_commande_Liste(Commandes);
        printf("\t\tENTRER LE NOM DE LA CASE QUE TU VEUT TRIER AVEC EN SPECIFIANT LE TYPE DE TRIYAGE (EXEMPLE=>COMMANDE ID:DESC)");
        fgets(choix,sizeof(choix),stdin);
        choix[strcspn(choix, "\n")] = '\0';
        char* token = strtok(choix,":");
        char* Categorie = strdup(token);
        token = strtok(NULL,":");
        char* Trier =strdup(token);
        if(strcmp(Trier,"DESC")==0){
            type = -1 ;
            break;
        }else if(strcmp(Trier,"INSC")==0){
            type = 1 ;
        }else{
            printf("\t\t\033[0mINVALID INPUT RESSAYER SOIT AVEC \"DESC\" OU \"INSC\":\033[0m");
            continue;
        }
        if(strcmp(Categorie,"ID")==0){
            while (tmp1->next != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && tmp2->data.Cm_ID <= tmp1->data.Cm_ID){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && tmp2->data.Cm_ID >= tmp1->data.Cm_ID){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
                tmp1 =tmp1->next;
            }
        }else if(strcmp(Categorie,"PLATES")==0){
            while (tmp1->next != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    for(i=0;i<tmp1->data.nbr_plat;i++){
                            for(j=0;j<tmp2->data.nbr_plat;j++){
                                if(type == 1 && strcmp(tmp2->data.plats[j], tmp1->data.plats[i]) <= 0){
                                    tri = tmp2->data;
                                    tmp2->data = tmp1->data;
                                    tmp1->data = tri;
                                }
                                if(type == -1 && strcmp(tmp2->data.plats[j], tmp1->data.plats[i]) >= 0){
                                    tri = tmp2->data;
                                    tmp2->data = tmp1->data;
                                    tmp1->data = tri;
                                }
                            }
                            if(j<tmp2->data.nbr_plat){
                                break;
                            }
                    }
                    tmp2 =tmp2->next;
                }
                tmp1 =tmp1->next;
            }
        }else if(strcmp(Categorie,"CLIENT")==0){
            while (tmp1->next != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && strcmp(tmp2->data.Client.name,tmp1->data.Client.name) <= 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && strcmp(tmp2->data.Client.name,tmp1->data.Client.name) >= 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
                tmp1 =tmp1->next;
            }
        }else if(strcmp(Categorie,"N.TELEPHON")==0){
            while (tmp1->next != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && strcmp(tmp2->data.Client.ph_number,tmp1->data.Client.ph_number) <= 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && strcmp(tmp2->data.Client.ph_number,tmp1->data.Client.ph_number) >= 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
                tmp1 =tmp1->next;
            }
        }else if(strcmp(Categorie,"PRIX")==0){
            while (tmp1->next != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && tmp2->data.consomation <= tmp1->data.consomation){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && tmp2->data.consomation >= tmp1->data.consomation){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
                tmp1 =tmp1->next;
            }
        }else if(strcmp(Categorie,"ETAT")==0){
            while (tmp1->next != NULL) {
                tmp2 = tmp1->next ;
                while (tmp2 != NULL) {
                    if(type == 1 && strcmp(tmp2->data.etat,tmp1->data.etat) <= 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    if(type == -1 && strcmp(tmp2->data.etat,tmp1->data.etat) >= 0){
                        tri = tmp2->data;
                        tmp2->data = tmp1->data;
                        tmp1->data = tri;
                    }
                    tmp2 =tmp2->next;
                }
                tmp1 =tmp1->next;
            }
        }else  {
            system("cls");
            m=1;
        }
    }while(m==1);
    system("cls");
    aff_commande_Liste(result);
    printf("\t\tVOULLEZ SAUVGARDER LE NOUVEAU TRIAGE OU NON ,SI OUI TAPER 1 SINON N'IMPORTE NOMBRE :");
    scanf("%d",&save);
    if(save ==1){
        Comfile = give_Commande_base(Comfile ,Commandes);
        return Commandes ;
    }
    else{
        return result;
    }
}


//fonction principale
int main() {

    FILE *Empfile ;
    FILE *Clifile  ;
    FILE * Repfile;
    FILE* Comfile ;

    EmpListe* Emploiers = NULL;
    client_Liste* Clients= NULL;
    RepasListe* Repas= NULL;
    commande_liste* Commandes= NULL;

    Emploiers =  get_Emploier_base(Empfile,Emploiers);
    Clients = get_Client_base(Clifile,Clients);
    Repas = get_Repas_base(Repfile,Repas);

    //int  O = 0, mc = 0, tc = 0;
    int m=0 , fd ;;
    int option, gest_client, gest_emploier, gest_Repas, gest_Comande,InfOption;
    Employe EmpSal;
    Client Clientpay ;
    Repass Plat;
    Commande  ComGrande ;

    do{
        system("cls");
        int login = login_Bibliotheque();
        system("pause");
        switch (login){
            case 0:
                exit(3);
            break ;
            case 1:
            do {
                    system("cls");
                    printf("\n\n");
                    printf("\t                             -++++++++++++++++++++++++++++++++++++++++++++-                           \n");
                    printf("\t                           /             PROGRAMME DE GESTION DU            \\                           \n");
                    printf("\t                           \\                    RESTAURANT                  /                           \n");
                    printf("\t                             -++++++++++++++++++++++++++++++++++++++++++++-                           \n");

                    printf("\n\n\t|\033[100m                                                 MENU:                                                  \033[0m|\n");

                    printf("\n\t           ______________________________________________________________________________________________");
                    printf("\n\t|\033[48;2;168;240;100m         ||                                  ||                                                          \033[0m|");
                    printf("\n\t|\033[48;2;168;240;100m         ||      Operation                   ||      Description                                         \033[0m|");
                    printf("\n\t|\033[48;2;168;240;100m         ||                                  ||                                                          \033[0m|");
                    printf("\n\t|\033[48;2;168;240;100m         ||----------------------------------||----------------------------------------------------------\033[0m|");
                    printf("\n\t|\033[100m   [1]        Donnes des employes                 Gerer les donnees coresspondantes aux                  \033[0m|");
                    printf("\n\t|\033[100m                                                  employes du restaurant.                                \033[0m|");
                    printf("\n\t|\033[100m         ||----------------------------------||----------------------------------------------------------\033[0m|");
                    printf("\n\t|\033[100m   [2]        Donnes des clients                  Gerer les donnees coresspondantes aux clients.         \033[0m|");
                    printf("\n\t|\033[100m         ||----------------------------------||----------------------------------------------------------\033[0m|");
                    printf("\n\t|\033[100m   [3]        Donnes des Repas                    Gerer les donnees coresspondantes aux Repas du         \033[0m|");
                    printf("\n\t|\033[100m                                                  restaurant (menu, prix, ingredients, disponibilite).   \033[0m|");
                    printf("\n\t|\033[100m         ||----------------------------------||----------------------------------------------------------\033[0m|");
                    printf("\n\t|\033[100m   [4]        Donnes des commandes                Gerer les commandes des clients, y compris la prise    \033[0m|");
                    printf("\n\t|\033[100m                                                  de commandes, la facturation et la livraison.          \033[0m|");
                    printf("\n\t|\033[100m         ||----------------------------------||----------------------------------------------------------\033[0m|");
                    printf("\n\t|\033[100m   [5]        Supprimer                           Supprimer la base de donne des clients ,des emploier   \033[0m|");
                    printf("\n\t|\033[100m                                                        des repas,generalement de restaurant             \033[0m|");
                    printf("\n\t|\033[100m         ||----------------------------------||----------------------------------------------------------\033[0m|");
                    printf("\n\t|\033[100m   [6]        Restaurant Info                    Les Nouvoutee du restaurant a savoir meilleure client   \033[0m|");
                    printf("\n\t|\033[100m                                                                ,emploier,commande,repas                 \033[0m|");
                    printf("\n\t|\033[100m         ||----------------------------------||----------------------------------------------------------\033[0m|");
                    printf("\n\t|\033[100m   [7]   ||   Quitter                        ||   Quitter le programme.                                  \033[0m|");
                    printf("\n\t|\033[100m_________||__________________________________||__________________________________________________________\033[0m|\n");
                    printf("\n\nQuelle operation a choisir? \033[3m(Entrer un nombre du menu)\033[0m: ");
                    scanf("%d", &option);
                    printf("\n");

                    while (option < 1 || option > 7) {
                        printf("\n\aOperation introuvable! Continue pour re-choisir l'operation.\n");
                        printf("\n\nQuelle operation a choisir? \033[3m(Entrer un nombre du menu)\033[0m: ");
                        scanf("%d", &option);
                        printf("\n");
                    }
                    while (getchar() != '\n');
                    switch (option) {
                        // Gestion des employes.
                        case (1):
                        printf("\nOperation choisie: [1]  -  \033[3;35m'Gestion des employes'\033[0m\n");
                        do{
                            printf("\t\t\t       ----------------------------------------------------------\n");
                            printf("\t\t\t      |                   Gestion des employes                   |\n");
                            printf("\t\t\t      |----------------------------------------------------------|\n");
                            printf("\t\t\t      |             [1]   |   Ajouter un employe                 |\n");
                            printf("\t\t\t      |             [2]   |   Afficher les employes              |\n");
                            printf("\t\t\t      |             [3]   |   Supprimer un employe               |\n");
                            printf("\t\t\t      |             [4]   |   Modifier un employe                |\n");
                            printf("\t\t\t      |             [5]   |   Chercher un employe                |\n");
                            printf("\t\t\t      |             [6]   |   Trier les employes                 |\n");
                            printf("\t\t\t      |             [7]   |   Retourner                          |\n");
                            printf("\t\t\t      |__________________________________________________________|\n");
                            do{
                                EmpListe* rechercheEmploier ;
                                m=0;
                                printf("\n\nQuelle operation a choisir? \033[3m(Entrer un nombre du menu)\033[0m: ");
                                scanf("%d", &gest_emploier);
                                printf("\n");
                                switch(gest_emploier){
                                    // Ajouter un employe
                                    case 1:

                                            printf("\n\t\tGIVE ME HOW MUCH EMPLOIER DO YOU WANT TO INSERT:");
                                            scanf("%d",&fd);
                                            for(int i = 0;i<fd;i++){
                                                printf("\n\t\tEMPLOIER #%d\n",i+1);
                                                getchar();
                                                Emploiers = insert_Emploier_Liste(Emploiers);
                                            }

                                        break;
                                    // Afficher les employes
                                    case 2:
                                            aff_Emploier_Liste(Emploiers);
                                        break;
                                    // Supprimer un employe
                                    case 3:
                                            getchar();
                                            Emploiers = supp_Emploier_Liste(Emploiers);
                                            system("cls");
                                            aff_Emploier_Liste(Emploiers);
                                        break;
                                    // Modifier un employe
                                    case 4:
                                            getchar();
                                            Emploiers = modifier_Emploier_liste(Emploiers);
                                        break;
                                    // Chercher un employe
                                    case 5:
                                            getchar();
                                            rechercheEmploier = chercher_Emploier_liste(Emploiers);
                                        break;
                                    // Trier les employes
                                    case 6:
                                            getchar();
                                            Emploiers = Trier_Emploier_liste(Emploiers);
                                        break;
                                    // Retourner
                                    case 7:
                                        m=0;
                                        break;
                                    //echec de choisir
                                    default:
                                        printf("\n\t\033[3;31mEchec de choisir! Reessayez ...\033[0m\n\n");
                                        m=1;
                                }
                            }while (m==1);
                            system("pause");
                        }while(gest_emploier != 7 );
                            break;
                        //Gestion des clients.
                        case (2):
                        printf("\nOperation choisie: [2]  - \033[3;35m'Gestion des clients'\033[0m\n");
                        do{
                            do{
                                client_Liste* rechercheclient ;
                                m=0;
                                printf("\t\t\t       ----------------------------------------------------------\n");
                                printf("\t\t\t      |                   Gestion des clients                    |\n");
                                printf("\t\t\t      |----------------------------------------------------------|\n");
                                printf("\t\t\t      |             [1]   |   Ajouter un client                  |\n");
                                printf("\t\t\t      |             [2]   |   Afficher les client                |\n");
                                printf("\t\t\t      |             [3]   |   Supprimer un client                |\n");
                                printf("\t\t\t      |             [4]   |   Modifier un client                 |\n");
                                printf("\t\t\t      |             [5]   |   Chercher un client                 |\n");
                                printf("\t\t\t      |             [6]   |   Trier les clients                  |\n");
                                printf("\t\t\t      |             [7]   |   Retourner                          |\n");
                                printf("\t\t\t      |__________________________________________________________|\n");
                                printf("\n\nQuelle operation a choisir? \033[3m(Entrer un nombre du menu)\033[0m: ");
                                scanf("%d", &gest_client);
                                printf("\n");
                                switch(gest_client){
                                    // Ajouter un client
                                    case 1:

                                            printf("\n\t\tGIVE ME HOW MUCH CLIENT DO YOU WANT TO INSERT:");
                                            scanf("%d",&fd);
                                            for(int i = 0;i<fd;i++){
                                                printf("\n\t\tCLIENT #%d\n",i+1);
                                                getchar();
                                                Clients = insert_client_Liste(Clients);
                                            }
                                        break;
                                    // Afficher les clients
                                    case 2:
                                            aff_client_Liste(Clients);
                                        break;
                                    // Supprimer un client
                                    case 3:
                                            getchar();
                                            Clients = supp_client_Liste(Clients);
                                        break;
                                    // Modifier un client
                                    case 4:
                                            getchar();
                                            Clients = modifier_client_liste(Clients);
                                        break;
                                    // Chercher un client
                                    case 5:
                                            getchar();
                                            rechercheclient = chercher_client_liste(Clients);
                                        break;
                                    // Trier les clients
                                    case 6:
                                            getchar();
                                            Clients = Trier_client_liste(Clients);
                                        break;
                                    // Retourner
                                    case 7:
                                        m=0;
                                        break;
                                    //echec de choisir
                                    default:
                                        printf("\n\t\033[3;31mEchec de choisir! Reessayez ...\033[0m\n\n");
                                        m=1;
                                }
                            }while (m==1);
                            system("pause");
                            system("cls");
                        }while(gest_client != 7 );
                            break;

                        //Gestion des Repas
                        case (3):
                        printf("\nOperation choisie: [3]  -  \033[3;35m'Gestion des Repas'\033[0m\n");
                        do{
                            do{
                                RepasListe* cherchererepas ;
                                m=0;
                                printf("\t\t\t       ----------------------------------------------------------\n");
                                printf("\t\t\t      |                   Gestion des Repas                      |\n");
                                printf("\t\t\t      |----------------------------------------------------------|\n");
                                printf("\t\t\t      |             [1]   |   Ajouter un Repas                   |\n");           //il faut que chaque Repas ajouter doit avoir tout les produit nessaicaire valable dans le stock
                                printf("\t\t\t      |             [2]   |   Afficher les Repas                 |\n");           //sinon il n'a pas la permission d'ajouter un Repas tant qu'il n'a pas citer cet produit dans le stock
                                printf("\t\t\t      |             [3]   |   Supprimer un Repas                 |\n");
                                printf("\t\t\t      |             [4]   |   Modifier un Repas                  |\n");//meme lorsqu'on modifie un Repas
                                printf("\t\t\t      |             [5]   |   Chercher un Repas                  |\n");
                                printf("\t\t\t      |             [6]   |   Trier les Repas                    |\n");//par prix /ID
                                printf("\t\t\t      |             [7]   |   Retourner                          |\n");
                                printf("\t\t\t      |__________________________________________________________|\n");
                                printf("\n\nQuelle operation a choisir? \033[3m(Entrer un nombre du menu)\033[0m: ");
                                scanf("%d", &gest_Repas);
                                printf("\n");
                                switch(gest_Repas){
                                    // Ajouter un Repas
                                    case 1:
                                            getchar();
                                            Repas = insert_Repas_Liste(Repas);
                                        break;
                                    // Afficher les Repas
                                    case 2:
                                            aff_Repas_Liste(Repas);
                                        break;
                                    // Supprimer un Repas
                                    case 3:
                                            getchar();
                                            Repas = supp_Repas_Liste(Repas);
                                        break;
                                    // Modifier un Repas
                                    case 4:
                                            getchar();
                                            Repas = modifier_Repas_liste(Repas);
                                        break;
                                    // Chercher un Repas
                                    case 5:
                                            getchar();
                                            cherchererepas = chercher_Repas_liste(Repas);
                                        break;
                                    // Trier les Repas
                                    case 6:
                                            getchar();
                                            Repas = Trier_Repas_liste(Repas);
                                        break;
                                    // Retourner
                                    case 7:
                                        m=0;
                                        break;
                                    //echec de choisir
                                    default:
                                        printf("\n\t\033[3;31mEchec de choisir! Reessayez ...\033[0m\n\n");
                                        m=1;
                                }
                            }while (m==1);
                            system("pause");
                        }while(gest_Repas != 7 );
                            break;
                        //Gestion de stock
                        case (4):
                        printf("\nOperation choisie: [4]  -  \033[3;35m'Gestion de Commandes'\033[0m\n");
                        do{
                            do{
                                commande_liste* Chercher ;
                                commande_liste* trier ;
                                m=0;
                                printf("\t\t\t       ----------------------------------------------------------\n");
                                printf("\t\t\t      |                   Gestion des Commandes                  |\n");
                                printf("\t\t\t      |----------------------------------------------------------|\n");//ajout depond des Repas valable
                                printf("\t\t\t      |             [1]   |   Ajouter une Commande               |\n");                                                                             //apres l'ajout de comande en fait la mis a jour des produit si le poid courant des produit est egal ou inferieure
                                printf("\t\t\t      |             [2]   |   Afficher les Commende              |\n");           //afficher les comande valable en attente d'etre completer                               // a inferieure en fait derectement le mssg de warning aux emploier qu'il faut domander des autres emploier de stock
                                printf("\t\t\t      |             [3]   |   Supprimer une Commende             |\n");//supprimer une commande qui a rencontrer une eureur            // c-A-d les comandes qui ont une consomation_par_temps non nul                                                                             // de demander un arrivage du produit
                                printf("\t\t\t      |             [4]   |   Modifier une Commende              |\n");//
                                printf("\t\t\t      |             [5]   |   Chercher une Commende              |\n");
                                printf("\t\t\t      |             [6]   |   Trier les Commende                 |\n");
                                printf("\t\t\t      |             [7]   |   Retourner                          |\n");
                                printf("\t\t\t      |__________________________________________________________|\n");
                                printf("\n\nQuelle operation a choisir? \033[3m(Entrer un nombre du menu)\033[0m: ");
                                scanf("%d", &gest_Comande);
                                printf("\n");
                                switch(gest_Comande){
                                    // Ajouter un Repas
                                    case 1:
                                            getchar();
                                            Commandes = insert_commande_Liste(Commandes,Repas,Clients);
                                        break;
                                    // Afficher les Repas
                                    case 2:
                                            aff_commande_Liste(Commandes);
                                        break;
                                    // Supprimer un Repas
                                    case 3:
                                            getchar();
                                            Commandes = supp_commande_Liste(Commandes);
                                        break;
                                    // Modifier un Repas
                                    case 4:
                                            getchar();
                                            Commandes = modifier_commande_liste(Commandes,Repas,Clients);
                                        break;
                                    // Chercher un Repas
                                    case 5:
                                            getchar();
                                            Chercher = chercher_commande_liste(Commandes);
                                        break;
                                    // Trier les Repas
                                    case 6:
                                            getchar();
                                            Commandes = Trier_commande_liste(Commandes);
                                        break;
                                    // Retourner
                                    case 7:
                                        m=0;
                                        break;
                                    //echec de choisir
                                    default:
                                        printf("\n\t\033[3;31mEchec de choisir! Reessayez ...\033[0m\n\n");
                                        m=1;
                                }
                            } while (m == 1);
                            system("pause");
                            system("cls");
                        } while (gest_Comande != 7 );
                            break;
                        case 5 :
                        printf("\nOperation choisie: [5]  -  \033[3;35m'Base de donnees'\033[0m\n");
                            int choix , assure ;
                            do{
                                printf("\t\t\033[31mEst ce que tu est sure que tu veut supprimer les donnes (1=Oui)(0=Non):\033[0m");
                                scanf("%d",&choix);
                                if(choix == 1){
                                    do{
                                        m=0;
                                        printf("\t\tQuelle base de donnes tu veut supprimer :\n");
                                        printf("\t\t\t1- [Emploiers]\n\t\t\t");
                                        printf("2-  [Clients]\n\t\t\t");
                                        printf("3-   [Repas]\n\t\t\t");
                                        printf("4- [Commandes]\n\t\t\t");
                                        printf("Votre choix ici :");
                                        scanf("%d",&assure);
                                        switch(assure){
                                            case 1 :
                                                Empfile = fopen("EmployeData.txt", "w");
                                                fclose(Empfile);
                                            break;
                                            case 2 :
                                                Clifile = fopen("ClientData.txt", "w");
                                                fclose(Clifile);
                                            break;
                                            case 3 :
                                                Repfile = fopen("RepasData.txt", "w");
                                                fclose(Repfile);
                                            break;
                                            case 4 :
                                                Comfile = fopen("CommandeData.txt", "w");
                                                fclose(Comfile);
                                            break;
                                            default:
                                                m=1;
                                        }
                                    }while (m==1);
                                }
                                else{
                                    break;
                                }
                            }while(choix!=1 || choix !=0);
                            break;

                        case 6:
                        printf("\nOperation choisie: [6]  -  \033[3;35m'Restaurant info'\033[0m\n");
                        do{
                            do{
                                system("cls");
                                printf("\t\t\t       ----------------------------------------------------------\n");
                                printf("\t\t\t      |                      Restaurant Info                     |\n");
                                printf("\t\t\t      |----------------------------------------------------------|\n");
                                printf("\t\t\t      |             [1]   |        Meilleur emploier             |\n");
                                printf("\t\t\t      |             [2]   |        Meilleur client               |\n");
                                printf("\t\t\t      |             [3]   |        Meilleur repas                |\n");
                                printf("\t\t\t      |             [4]   |        Meilleur Commande             |\n");
                                printf("\t\t\t      |             [5]   |        Retourner                     |\n");
                                printf("\t\t\t      |__________________________________________________________|\n");
                                printf("\n\nQuelle operation a choisir? \033[3m(Entrer un nombre du menu)\033[0m: ");
                                scanf("%d", &InfOption);
                                printf("\n");
                                switch (InfOption) {
                                    case 1:
                                        EmpSal = SalrSearch(Emploiers);
                                        printf(" [Nom]: %s\n", EmpSal.nom);
                                        printf(" [Prenom]: %s\n", EmpSal.prenom);
                                        printf(" [CNI]: %10s\n", EmpSal.CNI);
                                        printf(" [Numero de telephone]: %10s\n", EmpSal.ph_number);
                                        printf(" [Departement de l'employe]: %s\n", EmpSal.Departement);
                                        printf(" [Salaire de l'employe]: %.2f\n", EmpSal.salaire);
                                        printf("\n");
                                        break;
                                    case 2:
                                        Clientpay = PaimSearch(Clients);
                                        printf("\033[5;206;120;34m");
                                        printf("\t\t______________________________________________\n");
                                        printf("\t\t|     [Nom]: %-20s            |\n",Clientpay.name);
                                        printf("\t\t| [Prenom]: %-20s             |\n", Clientpay.first_name);
                                        printf("\t\t| [Numero de telephone]: %-18s  |\n", Clientpay.ph_number);
                                        printf("\t\t| [Paiment du client]: %-10.2f            |\n", Clientpay.paiment);
                                        printf("\t\t|____________________________________________|");printf("\033[0m\n");
                                        printf("\n");
                                        break;
                                    case 3:
                                        Plat = PriceSearch(Repas);
                                        printf("\t\t______________________________________________\n");
                                        printf("\t\t|     [Nom]: %-20s            |\n", Plat.name);
                                        printf("\t\t|     [Prix]: %.2f                |\n", Plat.prix);
                                        printf("\t\t|    [Consomation par temps]: %-18s|\n", Plat.consomation_par_temps);
                                        printf("\t\t|____________________________________________|");printf("\033[0m\n");
                                        printf("\n");
                                        break;
                                    case 4:
                                        ComGrande = GrandeSearch(Commandes);
                                        printf(" [Nom Du Client qui a commander]: %s\n",ComGrande.Client.name);
                                        printf(" [Son Numero de telephone]: %10s\n",ComGrande.Client.ph_number);
                                        printf(" [Commande Prix]: %.2f\n",ComGrande.consomation);
                                        printf(" [Nombre Des plats]: %d\n",ComGrande.nbr_plat);
                                        printf(" [L'ensemble Des plats]: %s\n",ComGrande.string_plat);
                                        printf(" [L'etat de la Commande]: %s\n",ComGrande.etat);
                                        printf("\n");
                                        break;
                                    case 5:
                                        m=0;
                                        break;
                                    default:
                                        printf("\n\t\033[3;31mEchec de choisir! Reessayez ...\033[0m\n\n");
                                        m=1;
                                }
                                system("pause");
                            }while(m==1);
                        }while(InfOption != 5);
                        default:
                        printf("\n\n\t\tProgramme fermer\n\n");
                        //exit(10);
                    }
            }while (option != 7) ;
            break ;
            case 2:
            do{
                system("cls");

                printf("\n\n");
                printf("\t                             -++++++++++++++++++++++++++++++++++++++++++++-                           \n");
                printf("\t                           /             PROGRAMME DE GESTION DU            \\                           \n");
                printf("\t                           \\                    RESTAURANT                  /                           \n");
                printf("\t                             -++++++++++++++++++++++++++++++++++++++++++++-                           \n");

                printf("\n\n\t|\033[100m                                                MENU:                                                   \033[0m|\n");

                printf("\n\t           ______________________________________________________________________________________________");
                printf("\n\t|\033[48;2;168;240;100m         ||                                  ||                                                          \033[0m|");
                printf("\n\t|\033[48;2;168;240;100m         ||      Operation                   ||      Description                                         \033[0m|");
                printf("\n\t|\033[48;2;168;240;100m         ||                                  ||                                                          \033[0m|");
                printf("\n\t|\033[48;2;168;240;100m         ||----------------------------------||----------------------------------------------------------\033[0m|");
                printf("\n\t|\033[100m   [1]        Donnes des clients                  Gerer les donnees coresspondantes aux clients.         \033[0m|");
                printf("\n\t|\033[100m         ||----------------------------------||----------------------------------------------------------\033[0m|");
                printf("\n\t|\033[100m   [2]        Gestion des commandes               Gerer les commandes des clients, y compris la prise    \033[0m|");
                printf("\n\t|\033[100m                                                  de commandes, la facturation et la livraison.          \033[0m|");
                printf("\n\t|\033[100m         ||----------------------------------||----------------------------------------------------------\033[0m|");
                printf("\n\t|\033[100m   [3]   ||   Quitter                        ||   Quitter le programme.                                  \033[0m|");
                printf("\n\t|\033[100m_________||__________________________________||__________________________________________________________\033[0m|\n");
                printf("\n\nQuelle operation a choisir? \033[3m(Entrer un nombre du menu)\033[0m: ");
                scanf("%d", &option);
                printf("\n");

                while (option < 1 || option > 3) {
                    printf("\n\aOperation introuvable! Continue pour re-choisir l'operation.\n");
                    printf("\n\nQuelle operation a choisir? \033[3m(Entrer un nombre du menu)\033[0m: ");
                    scanf("%d", &option);
                    printf("\n");
                }
                while (getchar() != '\n');
                switch (option) {
                    case (1):
                        printf("\nOperation choisie: [1]  - \033[3;35m'Gestion des clients'\033[0m\n");
                        do{
                            do{
                                client_Liste* rechercheclient ;
                                m=0;
                                printf("\t\t\t       ----------------------------------------------------------\n");
                                printf("\t\t\t      |                   Gestion des clients                    |\n");
                                printf("\t\t\t      |----------------------------------------------------------|\n");
                                printf("\t\t\t      |             [1]   |   Ajouter un client                  |\n");
                                printf("\t\t\t      |             [2]   |   Afficher les client                |\n");
                                printf("\t\t\t      |             [3]   |   Supprimer un client                |\n");
                                printf("\t\t\t      |             [4]   |   Modifier un client                 |\n");
                                printf("\t\t\t      |             [5]   |   Chercher un client                 |\n");
                                printf("\t\t\t      |             [6]   |   Trier les clients                  |\n");
                                printf("\t\t\t      |             [7]   |   Retourner                          |\n");
                                printf("\t\t\t      |__________________________________________________________|\n");
                                printf("\n\nQuelle operation a choisir? \033[3m(Entrer un nombre du menu)\033[0m: ");
                                scanf("%d", &gest_client);
                                printf("\n");
                                switch(gest_client){
                                    // Ajouter un client
                                    case 1:

                                            printf("\n\t\tGIVE ME HOW MUCH CLIENT DO YOU WANT TO INSERT:");
                                            scanf("%d",&fd);
                                            for(int i = 0;i<fd;i++){
                                                printf("\n\t\tCLIENT #%d\n",i+1);
                                                getchar();
                                                Clients = insert_client_Liste(Clients);
                                            }
                                        break;
                                    // Afficher les clients
                                    case 2:
                                            aff_client_Liste(Clients);
                                        break;
                                    // Supprimer un client
                                    case 3:
                                            getchar();
                                            Clients = supp_client_Liste(Clients);
                                        break;
                                    // Modifier un client
                                    case 4:
                                            getchar();
                                            Clients = modifier_client_liste(Clients);
                                        break;
                                    // Chercher un client
                                    case 5:
                                            getchar();
                                            rechercheclient = chercher_client_liste(Clients);
                                        break;
                                    // Trier les clients
                                    case 6:
                                            getchar();
                                            Clients = Trier_client_liste(Clients);
                                        break;
                                    // Retourner
                                    case 7:
                                        m=0;
                                        break;
                                    //echec de choisir
                                    default:
                                        printf("\n\t\033[3;31mEchec de choisir! Reessayez ...\033[0m\n\n");
                                        m=1;
                                }
                            }while (m==1);
                            system("pause");
                            system("cls");
                        }while(gest_client != 7 );
                            break;
                    case (2):
                    printf("\nOperation choisie: [2]  -  \033[3;35m'Gestion des commandes'\033[0m\n");
                        do{
                            do{
                                commande_liste* Chercher ;
                                commande_liste* trier ;
                                m=0;
                                printf("\t\t\t       ----------------------------------------------------------\n");
                                printf("\t\t\t      |                   Gestion des Commandes                  |\n");
                                printf("\t\t\t      |----------------------------------------------------------|\n");//ajout depond des Repas valable
                                printf("\t\t\t      |             [1]   |   Ajouter une Commande               |\n");                                                                             //apres l'ajout de comande en fait la mis a jour des produit si le poid courant des produit est egal ou inferieure
                                printf("\t\t\t      |             [2]   |   Afficher les Commende              |\n");           //afficher les comande valable en attente d'etre completer                               // a inferieure en fait derectement le mssg de warning aux emploier qu'il faut domander des autres emploier de stock
                                printf("\t\t\t      |             [3]   |   Supprimer une Commende             |\n");//supprimer une commande qui a rencontrer une eureur            // c-A-d les comandes qui ont une consomation_par_temps non nul                                                                             // de demander un arrivage du produit
                                printf("\t\t\t      |             [4]   |   Modifier une Commende              |\n");//
                                printf("\t\t\t      |             [5]   |   Chercher une Commende              |\n");
                                printf("\t\t\t      |             [6]   |   Trier les Commende                 |\n");
                                printf("\t\t\t      |             [7]   |   Retourner                          |\n");
                                printf("\t\t\t      |__________________________________________________________|\n");
                                printf("\n\nQuelle operation a choisir? \033[3m(Entrer un nombre du menu)\033[0m: ");
                                scanf("%d", &gest_Comande);
                                printf("\n");
                                switch(gest_Comande){
                                    // Ajouter un Repas
                                    case 1:
                                            getchar();
                                            Commandes = insert_commande_Liste(Commandes,Repas,Clients);
                                        break;
                                    // Afficher les Repas
                                    case 2:
                                            aff_commande_Liste(Commandes);
                                        break;
                                    // Supprimer un Repas
                                    case 3:
                                            getchar();
                                            Commandes = supp_commande_Liste(Commandes);
                                        break;
                                    // Modifier un Repas
                                    case 4:
                                            getchar();
                                            Commandes = modifier_commande_liste(Commandes,Repas,Clients);
                                        break;
                                    // Chercher un Repas
                                    case 5:
                                            getchar();
                                            Chercher = chercher_commande_liste(Commandes);
                                        break;
                                    // Trier les Repas
                                    case 6:
                                            getchar();
                                            Commandes = Trier_commande_liste(Commandes);
                                        break;
                                    // Retourner
                                    case 7:
                                        m=0;
                                        break;
                                    //echec de choisir
                                    default:
                                        printf("\n\t\033[3;31mEchec de choisir! Reessayez ...\033[0m\n\n");
                                        m=1;
                                }
                            } while (m == 1);
                            system("pause");
                        } while (gest_Comande != 7 );
                    break ;
                    default:
                        printf("\n\n\t\tProgramme fermer\n\n");
                    }
            }while(option != 3);
            break ;
        }
    }while(1);

return 0;
}

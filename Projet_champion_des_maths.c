#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>

#define FILENAME "scores.txt"
#define MAX_NAME_LEN 50

void accueil(int *points, const char *nom, const char *pnom);
void addition(int *points);
void soustraction(int *points);
void multiplication(int *points);
void table_mult(int *points);
void division(int *points);
int load_user(const char *nom, const char *pnom);
void save_user(const char *nom, const char *pnom, int points);

int load_user(const char *nom, const char *pnom) {
    FILE *file = fopen(FILENAME, "r");
    int points = 0;
    char current_nom[MAX_NAME_LEN], current_pnom[MAX_NAME_LEN];
    int found = 0;

    if (file) {
        while (fscanf(file, "%s %s %d", current_nom, current_pnom, &points) == 3) {
            if (strcmp(nom, current_nom) == 0 && strcmp(pnom, current_pnom) == 0) {
                found = 1;
                break;
            }
        }
        fclose(file);
        if (!found) points = 0;
    }
    return points;
}

void save_user(const char *nom, const char *pnom, int new_points) {
    FILE *old_file = fopen(FILENAME, "r");
    FILE *new_file = fopen("temp.txt", "w");
    char current_nom[MAX_NAME_LEN], current_pnom[MAX_NAME_LEN];
    int current_points, found = 0;

    if (old_file) {
        while (fscanf(old_file, "%s %s %d", current_nom, current_pnom, &current_points) == 3) {
            if (strcmp(nom, current_nom) == 0 && strcmp(pnom, current_pnom) == 0) {
                fprintf(new_file, "%s %s %d\n", nom, pnom, new_points);
                found = 1;
            } else {
                fprintf(new_file, "%s %s %d\n", current_nom, current_pnom, current_points);
            }
        }
        fclose(old_file);
    }

    if (!found) {
        fprintf(new_file, "%s %s %d\n", nom, pnom, new_points);
    }

    fclose(new_file);
    remove(FILENAME);
    rename("temp.txt", FILENAME);
}

void addition(int *points) {
    int a = rand() % 100, b = rand() % 100;
    int res, essais = 0;

    printf("\nAddition\n%d + %d = ?\n", a, b);
    do {
        if (essais++ > 0) printf("Réessayez...\n");
        scanf("%d", &res);
    } while (res != a + b);

    *points += (essais == 1) ? 10 : (essais == 2) ? 5 : 1;
    printf("Bien joué ! Points actuels: %d\n\n", *points);
}

void soustraction(int *points) {
    int a = rand() % 100, b = rand() % 100;
    if (b > a) { int temp = a; a = b; b = temp; }
    int res, essais = 0;

    printf("\nSoustraction\n%d - %d = ?\n", a, b);
    do {
        if (essais++ > 0) printf("Réessayez...\n");
        scanf("%d", &res);
    } while (res != a - b);

    *points += (essais == 1) ? 10 : (essais == 2) ? 5 : 1;
    printf("Bravo ! Points actuels: %d\n\n", *points);
}

void multiplication(int *points) {
    int a = rand() % 10, b = rand() % 10;
    int res, essais = 0;

    printf("\nMultiplication\n%d × %d = ?\n", a, b);
    do {
        if (essais++ > 0) printf("Réessayez...\n");
        scanf("%d", &res);
    } while (res != a * b);

    *points += (essais == 1) ? 10 : (essais == 2) ? 5 : 1;
    printf("Excellent ! Points actuels: %d\n\n", *points);
}

void table_mult(int *points) {
    int table, mode, sum_essais = 0;
    printf("\nTable de multiplication\nChoisir une table (1-10) : ");
    scanf("%d", &table);

    printf("Mode (0: Apprendre, 1: S'entraîner) : ");
    scanf("%d", &mode);

    if (mode == 0) {
        for (int i = 1; i <= 10; i++)
            printf("%d × %d = %d\n", i, table, i * table);
    } else {
        for (int i = 1; i <= 10; i++) {
            int res, essais = 0;
            printf("%d × %d = ?\n", i, table);

            do {
                if (essais++ > 0) printf("Réessayez...\n");
                scanf("%d", &res);
            } while (res != i * table);

            sum_essais += essais;
        }
        *points += (sum_essais <= 10) ? 10 : (sum_essais <= 20) ? 5 : 1;
        printf("Table maîtrisée ! Points +%d\n\n", (sum_essais <= 10) ? 10 : (sum_essais <= 20) ? 5 : 1);
    }
}

void division(int *points) {
    int a = rand() % 100, b = rand() % 99 + 1;
    int q, r, essais = 0;

    printf("\nDivision\n%d ÷ %d = ?\n", a, b);
    do {
        if (essais++ > 0) printf("Réessayez...\n");
        printf("Quotient : ");
        scanf("%d", &q);
        printf("Reste : ");
        scanf("%d", &r);
    } while (q != a / b || r != a % b);

    *points += (essais == 1) ? 10 : (essais == 2) ? 5 : 1;
    printf("Parfait ! Points actuels: %d\n\n", *points);
}

void accueil(int *points, const char *nom, const char *pnom) {
    int choix;
    do {
        printf("\n+--- Menu ------------------------+\n"
               "|1 : Addition                     |\n"
               "|2 : Soustraction                 |\n"
               "|3 : Multiplication               |\n"
               "|4 : Tables de multiplication     |\n"
               "|5 : Division                     |\n"
               "|0 : Quitter                      |\n"
               "+---------------------------------+\n"
               "Joueur : %s %s\n"
               "Points : %d\n"
               "Votre choix : ", nom, pnom, *points);

        scanf("%d", &choix);

        switch(choix) {
            case 1: addition(points); break;
            case 2: soustraction(points); break;
            case 3: multiplication(points); break;
            case 4: table_mult(points); break;
            case 5: division(points); break;
            case 0:
                save_user(nom, pnom, *points);
                printf("\nSauvegarde réussie ! Au revoir %s %s !\n", nom, pnom);
                return;
            default: printf("Choix invalide !\n");
        }
    } while (choix != 0);
}

int main() {
    srand(time(NULL));
    char nom[MAX_NAME_LEN], pnom[MAX_NAME_LEN];
    int points;

    printf("Nom : ");
    scanf("%49s", nom);
    printf("Prénom : ");
    scanf("%49s", pnom);

    points = load_user(nom, pnom);
    printf("Bienvenue %s %s ! Vous démarrez avec %d points.\n", nom, pnom, points);
    accueil(&points, nom, pnom);

    return 0;
}
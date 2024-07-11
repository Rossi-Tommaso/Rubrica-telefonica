#include <stdio.h>
#include <stdbool.h>
#include <string.h>
#include <ctype.h>
#define TEL 11
#define LEN 20

typedef struct {
    char nome[LEN], cognome[LEN], n_telefono[TEL];
} Contatto;

bool aggiungiContatto();
bool visualizzaContatti();
bool cercaContatto();
bool svuotaRubrica();
bool eliminaContatto();
bool menu();

int main() {
    while (true) {
        if (!menu())
            return 0;
    }
    return 0;
}

bool menu() {
    int scelta;

    printf("1. Aggiungere un contatto alla rubrica.\n");
    printf("2. Visualizzare tutti i contatti della rubrica.\n");
    printf("3. Cercare un contatto per nome.\n");
    printf("4. Svuota rubrica.\n");
    printf("5. Elimina un contatto specifico.\n");
    printf("6. Uscire dal programma.\n\n");
    printf("Scelta: ");
    
    if (scanf("%d", &scelta) != 1) {
        printf("Input non valido\n");
        while (getchar() != '\n');  // clear the input buffer
        return true;
    }

    switch (scelta) {
        case 1:
            if (!aggiungiContatto())
                return true;
            break;

        case 2:
            if (!visualizzaContatti())
                return true;
            break;

        case 3:
            if (!cercaContatto())
                return true;
            break;

        case 4:
            if (!svuotaRubrica())
                return true;
            break;

        case 5:
            if (!eliminaContatto())
                return true;
            break;

        case 6:
            return false;

        default:
            printf("Scelta non valida\n");
            break;
    }
    return true;
}

bool aggiungiContatto() {
    Contatto contatto;
    FILE *fp = fopen("strutture_rubricatelefonica.txt", "a");

    if (fp == NULL) {
        printf("Errore nell'apertura del file\n");
        return false;
    }

    printf("Inserisci dati per aggiungere contatto:\n\n");

    do {
        printf("Numero di telefono: ");
        scanf("%s", contatto.n_telefono);
    } while (strlen(contatto.n_telefono) < 10 && strlen(contatto.n_telefono) > 14);

    printf("Nome: ");
    scanf("%s", contatto.nome);
    contatto.nome[0] = toupper(contatto.nome[0]);
    for (int i = 1; i < strlen(contatto.nome); i++) {
        contatto.nome[i] = tolower(contatto.nome[i]);
    }

    printf("Cognome: ");
    scanf("%s", contatto.cognome);
    contatto.cognome[0] = toupper(contatto.cognome[0]);
    for (int i = 1; i < strlen(contatto.cognome); i++) {
        contatto.cognome[i] = tolower(contatto.cognome[i]);
    }

    fprintf(fp, "%s %s %s\n", contatto.n_telefono, contatto.nome, contatto.cognome);
    fclose(fp);
    return true;
}

bool visualizzaContatti() {
    char tel[TEL], nome[LEN], cognome[LEN];
    FILE *fp = fopen("strutture_rubricatelefonica.txt", "r");

    if (fp == NULL) {
        printf("Errore nell'apertura del file\n");
        return false;
    }

    while (fscanf(fp, "%s %s %s", tel, nome, cognome) != EOF) {
        printf("Nome: %s\tCognome: %s\tNumero di telefono: %s\n", nome, cognome, tel);
    }

    fclose(fp);
    return true;
}

bool cercaContatto() {
    char tel[TEL], nome[LEN], cognome[LEN], n[LEN], c[LEN];
    FILE *fp = fopen("strutture_rubricatelefonica.txt", "r");

    if (fp == NULL) {
        printf("Errore nell'apertura del file\n");
        return false;
    }

    printf("Inserisci nome e cognome della persona da cercare:\nNome: ");
    scanf("%s", n);
    n[0] = toupper(n[0]);
    for (int i = 1; i < strlen(n); i++) {
        n[i] = tolower(n[i]);
    }
    printf("Cognome: ");
    scanf("%s", c);
    c[0] = toupper(c[0]);
    for (int i = 1; i < strlen(c); i++) {
        c[i] = tolower(c[i]);
    }

    bool trovato = false;
    while (fscanf(fp, "%s %s %s", tel, nome, cognome) != EOF) {
        if (strcmp(nome, n) == 0 && strcmp(cognome, c) == 0) {
            printf("\nNumero di telefono: %s\n", tel);
            trovato = true;
        }
    }
    if (!trovato) {
        printf("\nATTENZIONE: numero non in rubrica.\nSOLUZIONE: aggiungi il numero nella rubrica selezionando la prima voce del menu.\n");
    }

    fclose(fp);
    return true;
}

bool svuotaRubrica() {
    int scelta;

    printf("Vuoi veramente svuotare la rubrica?\nATTENZIONE: azione irreversibile.\n(1) SI\t\t(2) NO\n");
    if (scanf("%d", &scelta) != 1) {
        printf("Scelta non valida. Operazione annullata.\n\n");
        while (getchar() != '\n');  // clear the input buffer
        return true;
    }

    if (scelta == 1) {
        FILE *fp = fopen("strutture_rubricatelefonica.txt", "w");
        if (fp == NULL) {
            printf("Errore nell'apertura del file\n");
            return false;
        }
        fclose(fp);
        printf("Rubrica svuotata.\n\n");
    } else if (scelta == 2) {
        printf("Operazione annullata.\n\n");
    } else {
        printf("Scelta non valida. Operazione annullata.\n\n");
    }

    return true;
}

bool eliminaContatto() {
    char tel[TEL], nome[LEN], cognome[LEN], n[LEN], c[LEN];
    bool trovato = false;

    FILE *fp = fopen("strutture_rubricatelefonica.txt", "r");
    if (fp == NULL) {
        printf("Errore nell'apertura del file\n");
        return false;
    }

    FILE *tmp_fp = fopen("temp.txt", "w");
    if (tmp_fp == NULL) {
        printf("Errore nella creazione del file temporaneo\n");
        fclose(fp);
        return false;
    }

    printf("Inserisci nome e cognome della persona da eliminare:\nNome: ");
    scanf("%s", n);
    n[0] = toupper(n[0]);
    for (int i = 1; i < strlen(n); i++) {
        n[i] = tolower(n[i]);
    }
    printf("Cognome: ");
    scanf("%s", c);
    c[0] = toupper(c[0]);
    for (int i = 1; i < strlen(c); i++) {
        c[i] = tolower(c[i]);
    }

    while (fscanf(fp, "%s %s %s", tel, nome, cognome) == 3) {
        if (strcmp(nome, n) == 0 && strcmp(cognome, c) == 0) {
            trovato = true;
            printf("\nContatto trovato e eliminato: %s %s %s\n", tel, nome, cognome);
        } else {
            fprintf(tmp_fp, "%s %s %s\n", tel, nome, cognome);
        }
    }

    fclose(fp);
    fclose(tmp_fp);

    if (!trovato) {
        printf("Contatto non trovato.\n");
        remove("temp.txt");
        return false;
    }

    if (remove("strutture_rubricatelefonica.txt") != 0) {
        printf("Errore nella rimozione del file originale\n");
        return false;
    }
    if (rename("temp.txt", "strutture_rubricatelefonica.txt") != 0) {
        printf("Errore nel rinominare il file temporaneo\n");
        return false;
    }

    printf("Contatto eliminato con successo.\n");
    return true;
}

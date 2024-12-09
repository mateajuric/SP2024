#define _CRT_SECURE_NO_WARNINGS
#define MAX 50
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Article* position;
typedef struct Article {
    char naziv[MAX];
    int kolicina;
    float cijena;
    position next;
} Article;

typedef struct Reciept {
    char date[11];
    position Articles;
    struct Reciept* next;
} Reciept;

Reciept* CreateReciept(char* date);
int AddArticleSorted(position p, char* naziv, int kolicina, float cijena);
int AddRecieptSorted(Reciept* head, Reciept* newReciept);
int CompareDates(const char* date1, const char* date2);
int ReadReciepts(Reciept* head);
int Potrosnja(Reciept* head, const char* artikl, const char* startDate, const char* endDate);
int PrintReciepts(Reciept* head);
int FreeArticles(position p);
int FreeReciepts(Reciept* head);

int main() {
    Reciept head;
    strcpy(head.date, "");
    head.Articles = NULL;
    head.next = NULL;
    int izbor = 0;
    char artikl[MAX];
    char startDate[11];
    char endDate[11];

    if (ReadReciepts(&head) != 0) {
        printf("Greska pri citanju racuna.\n");
        return -1;
    }

    do {
        printf("\nOdaberite opciju:\n");
        printf("1. Prikazi sve racune\n");
        printf("2. Pretraga potrosnje za artikl u vremenskom periodu\n");
        printf("3. Izlaz\n");
        printf("Vas izbor: ");
        scanf("%d", &izbor);

        switch (izbor) {
        case 1:
            PrintReciepts(&head);
            break;

        case 2:
            printf("Unesite naziv artikla: ");
            scanf(" %s", artikl);
            printf("Unesite pocetni datum (YYYY-MM-DD): ");
            scanf(" %10s", startDate);
            printf("Unesite krajnji datum (YYYY-MM-DD): ");
            scanf(" %10s", endDate);
            Potrosnja(&head, artikl, startDate, endDate);
            break;

        case 3:
            printf("Izlaz iz programa.\n");
            break;

        default:
            printf("Neispravan izbor, pokusajte ponovo.\n");
            break;
        }
    } while (izbor != 3);

    FreeReciepts(&head);
    return 0;
}

Reciept* CreateReciept(char* date) {
    Reciept* q = (Reciept*)malloc(sizeof(Reciept));
    if (q == NULL) {
        printf("Greska pri alokaciji memorije za racun!\n");
        return NULL;
    }
    strcpy(q->date, date);

    q->Articles = (position)malloc(sizeof(Article));
    if (q->Articles == NULL) {
        printf("Greska pri alokaciji memorije za artikle!\n");
        free(q);
        return NULL;
    }
    q->Articles->next = NULL; 
    q->Articles->kolicina = 0;
    q->Articles->cijena = 0.0;
    strcpy(q->Articles->naziv, "");

    q->next = NULL;
    return q;
}

int AddArticleSorted(position p, char* naziv, int kolicina, float cijena) {
    if (p == NULL) {
        printf("Lista artikala nije inicijalizirana!\n");
        return -1;
    }

    position q = NULL;
    q = (position)malloc(sizeof(Article));
    if (q == NULL) {
        printf("Greska pri alokaciji memorije za artikl!\n");
        return -1;
    }
    strcpy(q->naziv, naziv);
    q->kolicina = kolicina;
    q->cijena = cijena;
    q->next = NULL;

    position prev = p;
    position curr = p->next;

    while (curr != NULL && strcmp(curr->naziv, q->naziv) < 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != NULL && strcmp(curr->naziv, q->naziv) == 0) {
        curr->kolicina += q->kolicina;
        free(q);
    }
    else {
        q->next = curr;
        prev->next = q;
    }
    return 0;
}


int AddRecieptSorted(Reciept* p, Reciept* newReciept) {
    Reciept* prev = p;
    Reciept* curr = p->next;

    while (curr != NULL && CompareDates(curr->date, newReciept->date) < 0) {
        prev = curr;
        curr = curr->next;
    }

    if (curr != NULL && CompareDates(curr->date, newReciept->date) == 0) {
        position article = newReciept->Articles;
        while (article != NULL) {
            AddArticleSorted(curr->Articles, article->naziv, article->kolicina, article->cijena);
            article = article->next;
        }
        FreeArticles(newReciept->Articles);
        free(newReciept);
    }
    else {
        newReciept->next = curr;
        prev->next = newReciept;
    }
    return 0;
}

int CompareDates(const char* date1, const char* date2) {
    int year1, month1, day1;
    int year2, month2, day2;

    sscanf(date1, "%d-%d-%d", &year1, &month1, &day1);
    sscanf(date2, "%d-%d-%d", &year2, &month2, &day2);

    if (year1 < year2) return -1;
    if (year1 > year2) return 1;
    if (month1 < month2) return -1;
    if (month1 > month2) return 1;
    if (day1 < day2) return -1;
    if (day1 > day2) return 1;

    return 0;
}
int ReadReciepts(Reciept* p) {
    FILE* fp = NULL;
    fp=fopen("racuni.txt", "r");
    if (fp == NULL) {
        printf("Greska pri otvaranju datoteke racuni.txt!\n");
        return -1;
    }

    char recieptFile[MAX];
    while (fscanf(fp, " %s", recieptFile) == 1) {
        FILE* reciept = NULL;
        reciept= fopen(recieptFile, "r");
        if (reciept==NULL) 
        {
            printf("Greska pri otvaranju datoteke %s!\n", recieptFile);
            return -1;
        }

        char date[11];
        fscanf(reciept, " %10s", date);

        Reciept* newReciept = CreateReciept(date);
        if (!newReciept) {
            fclose(reciept);
            return -1;
        }

        char naziv[MAX];
        int kolicina;
        float cijena;

        while (fscanf(reciept, " %s %d %f", naziv, &kolicina, &cijena) == 3) {
            AddArticleSorted(newReciept->Articles, naziv, kolicina, cijena);
        }

        AddRecieptSorted(p, newReciept);
        fclose(reciept);
    }

    fclose(fp);
    return 0;
}

int Potrosnja(Reciept* p, const char* artikl, const char* startDate, const char* endDate) {
    Reciept* current = p->next;
    int totalQuantity = 0;
    float totalSpent = 0;

    while (current != NULL) {
        if (CompareDates(current->date, startDate) >= 0 && CompareDates(current->date, endDate) <= 0) {
            position article = current->Articles->next;
            while (article != NULL) {
                if (strcmp(article->naziv, artikl) == 0) {
                    totalQuantity += article->kolicina;
                    totalSpent += article->kolicina * article->cijena;
                }
                article = article->next;
            }
        }
        current = current->next;
    }

    printf("Ukupno potroseno na %s: %.2f, ukupna kolicina: %d\n", artikl, totalSpent, totalQuantity);
    return 0;
}

int PrintReciepts(Reciept* p) {
    Reciept* current = p->next;
    while (current != NULL) {
        printf("Racun - Datum: %s\n", current->date);
        position article = current->Articles->next; 
        while (article != NULL) {
            printf("\tArtikl: %s, Kolicina: %d, Cijena: %.2f\n",
                article->naziv, article->kolicina, article->cijena);
            article = article->next;
        }
        current = current->next;
    }
    return 0;
}


int FreeArticles(position p) {
    position current = p;
    while (current != NULL) {
        position temp = current;
        current = current->next;
        free(temp);
    }
    return 0;
}

int FreeReciepts(Reciept* p) {
    Reciept* current = p->next;
    while (current != NULL) {
        Reciept* temp = current;
        FreeArticles(current->Articles);
        current = current->next;
        free(temp);
    }
    return 0;
}

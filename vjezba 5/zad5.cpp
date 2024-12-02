//Napisati program koji iz datoteke èita postfiks izraz i zatim korištenjem stoga raèuna
// rezultat.Stog je potrebno realizirati preko vezane liste.

#define _CRT_SECURE_NO_WARNINGS
#define ERROR_OF -1
#define ERROR_ALLOCATION -1
#define MAX_LINE 1024
#include<stdio.h>
#include<string.h>
#include<stdlib.h>

typedef struct stog* position;
typedef struct stog
{
    int el;
	position next;
}stog;
int push(position p, int br);
int pop(position p);
int razlika(position p);
int zbroj(position p);
int umnozak(position p);
int kvocijent(position p);

int main()
{
	stog head;
	head.next = NULL;
    int numBytes;
    int br;
    char buffer[MAX_LINE];
    char* temp = buffer;
    FILE* fp = NULL;
	fp = fopen("Text.txt", "r");
        if (fp == NULL)
        {
            printf("Datoteka nije otvorena.\n");
            return ERROR_OF;
        }
        char operacija[15];
        while (fgets(buffer, MAX_LINE, fp) != NULL) {
            temp = buffer; 
            while (sscanf(temp, "%s %n", operacija, &numBytes) == 1) {

                if (sscanf(operacija, "%d", &br) == 1) {
                    push(&head, br);
                }
                else if (strcmp(operacija, "+") == 0) {
                    zbroj(&head);
                }
                else if (strcmp(operacija, "-") == 0) {
                    razlika(&head);
                }
                else if (strcmp(operacija, "*") == 0) {
                    umnozak(&head);
                }
                else if (strcmp(operacija, "/") == 0) {
                    kvocijent(&head);
                }
                else {
                    printf("Nepoznata operacija: %s\n", operacija);
                    return -1;
                }
                temp += numBytes;
            }
        }

        if (head.next != NULL) {
            int rezultat = pop(&head);
            printf("Rezultat je %d.\n", rezultat);
        }
        else {
            printf("Stog je prazan, nema rezultata.\n");
        }
		return 0;
}
int razlika(position p)
{
    int rezultat;
    int broj1 = pop(p);
    int broj2 = pop(p);
    rezultat = broj2 - broj1;
    push(p, rezultat);

    return 0;
}
int zbroj(position p)
{
    int rezultat;
    int broj1 = pop(p);
    int broj2 = pop(p);
    rezultat = broj1 + broj2;
    push(p, rezultat);

    return 0;
}
int umnozak(position p)
{
    int rezultat;
    int broj1 = pop(p);
    int broj2 = pop(p);
    rezultat = broj1 * broj2;
    push(p, rezultat);

    return 0;
}
int kvocijent(position p)
{
    int rezultat;
    int broj1 = pop(p);
    int broj2 = pop(p);
    rezultat = broj2 / broj1;
    push(p, rezultat);

    return 0;
}
int push(position p, int br)
{
    position q=NULL;
    q = (position)malloc(sizeof(stog));
    if (q == NULL)
    {
        printf("Neuspjesna alokacija.\n");
        return ERROR_ALLOCATION;
    }
    q->el = br;

    q->next = p -> next;
    p->next = q;

    return 0;
}
int pop(position p)
{
    if (p->next == NULL) {
        printf("Greška: stog je prazan.\n");
        return ERROR_OF;
    }
    position temp;
    temp= p->next;
    int broj = temp->el;
    p->next = temp->next;
    free(temp);
    return broj;
}


#define _CRT_SECURE_NO_WARNINGS
#define ERROR_OF 1
#define ERROR_ALLOCATION 1
#define MAX_LINE 1024
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

typedef struct Polinom* position;
typedef struct Polinom {
    int coeff;
    int exp;
    position next;
} Polinom;

int  FileRead(position p, const char* File);
int CreateElement(position* q, int coeff, int exp);
int InsertAfter(position p, position n);
int DeleteAfter(position temp);
int Print(position p);
int Multiply(position rezultat, position p1, position p2);
int Sum(position result, position p1, position p2);
int InsertSorted(position head, position newEl);

int main()
{
    Polinom head1 = { 0, 0, NULL };
    Polinom head2 = { 0, 0, NULL };
    Polinom sum = { 0, 0, NULL };
    Polinom multi = { 0, 0, NULL };

    FileRead(&head1, "polinom1.txt");
    FileRead(&head2, "polinom2.txt");

    Sum(&sum, &head1, &head2);
    Multiply(&multi, &head1, &head2);

    printf("Zbroj polinoma: ");
    Print(sum.next);
    printf("\nUmnozak polinoma: ");
    Print(multi.next);
    return 0;
}

int FileRead(position p, const char* File)
{
    int c, e, numBytes;
    char buffer[MAX_LINE];
    char* temp = buffer;

    FILE* fp = fopen(File, "r");
    if (fp == NULL)
    {
        printf("Greska pri otvaranju datoteke.\n");
        return ERROR_OF;
    }
    while (fgets(buffer, MAX_LINE, fp) != NULL) {
        temp = buffer;
        while (strlen(temp) > 0) {
            int status = sscanf(temp, " %d %d %n", &c, &e, &numBytes);
            if (status == 2) {
                position n;
                if (CreateElement(&n, c, e) == 0) {
                    InsertSorted(p, n);
                }
            }
            else {
                printf("Datoteka nije valjana.\n");
                fclose(fp);
                return ERROR_OF;
            }
            temp += numBytes;
        }
    }
    fclose(fp);
    return 0;
}

int CreateElement(position*q, int coeff, int exp)
{
    *q = (position)malloc(sizeof(Polinom));
    if (*q == NULL)
    {
        printf("Pogresna alokacija memorije!\n");
        return ERROR_ALLOCATION;
    }
    (*q)->coeff = coeff;
    (*q)->exp = exp;
    (*q)->next = NULL;
    return 0;
}

int DeleteAfter(position temp)
{
    if (temp == NULL || temp->next == NULL) {
        return 1;
    }
    position todelete;
    todelete = temp->next;
    temp->next = todelete->next;
    free(todelete);
    return 0;
}

int InsertAfter(position p, position n)
{
    n->next = p->next;
    p->next = n;
    return 0;
}

int InsertSorted(position head, position newEl)
{
    position temp = head;

    while (temp->next && (temp->next->exp < newEl->exp)) {
        temp = temp->next;
    }

    if (temp->next == NULL || temp->next->exp != newEl->exp) {
        InsertAfter(temp, newEl);
    }
    else {
        int resultCoeff = temp->next->coeff + newEl->coeff;
        if (resultCoeff == 0) {
            DeleteAfter(temp);
            free(newEl);
        }
        else {
            temp->next->coeff = resultCoeff;
            free(newEl);
        }
    }
    return 0;
}

int Sum(position result, position p1, position p2)
{
    position temp1 = p1->next;
    position temp2 = p2->next;

    while (temp1) {
        position novi;
        CreateElement(&novi, temp1->coeff, temp1->exp);
        InsertSorted(result, novi);
        temp1 = temp1->next;
    }

    while (temp2) {
        position novi;
        CreateElement(&novi, temp2->coeff, temp2->exp);
        InsertSorted(result, novi);
        temp2 = temp2->next;
    }

    return 0;
}

int Multiply(position rezultat, position p1, position p2)
{
    position temp1 = p1->next;

    while (temp1) {
        position temp2 = p2->next;
        while (temp2) {
            position novi;
            CreateElement(&novi, temp1->coeff * temp2->coeff, temp1->exp + temp2->exp);
            InsertSorted(rezultat, novi);
            temp2 = temp2->next;
        }
        temp1 = temp1->next;
    }

    return 0;
}

int Print(position p)
{
    if (p == NULL) return 0;
    while (p) {
        printf("%dx^%d ", p->coeff, p->exp);
        if (p->next != NULL && p->next->coeff > 0)
            printf("+ ");
        p = p->next;
    }
    return 0;
}
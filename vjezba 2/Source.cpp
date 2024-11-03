
#define _CRT_SECURE_NO_WARNINGS
#define ERROR_ALLOCATION -1
#define ERROR_OF -1

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

//Definirati strukturu osoba (ime, prezime, godina roðenja) 
typedef struct person* position;
typedef struct person
{
	char name[30];
	char surname[30];
	int birthYear;
	position next;
}person;


int InsertStart(position p);
int Print(position p);
int InsertEnd(position p);
int FindBySurname(position p);
int Delete(position p);
int InsertAfter(position p);
int InsertBefore(position p);
void SortBySurname(position p);
int FileWrite(position p);
int FileRead(position p);

//dinamièki dodaje novi element na poèetak liste
int InsertStart(position p)
{
	position q = NULL;
	q = (position)malloc(sizeof(person));
	if (q == NULL)
	{
		printf("Pogresna alokacija memorije!\n");
		return ERROR_ALLOCATION;
	}
	printf("Unesi ime osobe:");
	scanf(" %s", q->name);
	printf("Unesi prezime osobe:");
	scanf(" %s", q->surname);
	printf("Unesi godinu rodenja osobe:");
	scanf(" %d", &q->birthYear);

	q->next = p->next;
	p->next = q;
	return 0;
}

//ispisuje listu
int Print(position p)
{
	if (p == NULL)
	{
		printf("Lista je prazna.\n");
		return 0;
	}
	while (p != NULL)
	{
		
		printf("%s %s %d\n", p->name, p->surname, p->birthYear);
		p = p->next;
	}
	
	return 0;
}

//dinamièki dodaje novi element na kraj liste
int InsertEnd(position p)
{
	while (p->next != NULL)
	{
		p = p->next;
	}
	position q = NULL;
	q = (position)malloc(sizeof(person));
	if (q == NULL)
	{
		printf("Pogresna alokacija memorije!\n");
		return ERROR_ALLOCATION;
	}
	printf("Unesi ime osobe:");
	scanf(" %s", q->name);
	printf("Unesi prezime osobe:");
	scanf(" %s", q->surname);
	printf("Unesi godinu rodenja osobe:");
	scanf(" %d", &q->birthYear);

	
	q->next = p->next;
	p->next = q;
	return 0;
}

//pronalazi element u listi(po prezimenu)
int FindBySurname(position p)
{
	char sur[30];
	printf("Unesi prezime osobe koju zelis pronaci:");
	scanf(" %s", sur);
	while (p != NULL && strcmp(sur, p->surname) != 0)
	{
		p = p->next;
	}
	if (p == NULL)
	{
		printf("Ne postoji uneseno prezime unutar liste,\n");
	}
	else
	{
		printf("Adresa unesene osobe je %p.\n", p);

	}
	return 0;

}
//briše odreðeni element iz liste
int Delete(position p)
{
	position prev = NULL;
	char sur[30];
	printf("Unesi prezime osobe koju zelis izbrisati:");
	scanf(" %s", sur);
	while (p->next != NULL && strcmp(p->surname, sur) != 0)
	{
		prev = p;
		p = p->next;

	}
	if (prev != NULL && strcmp(p->surname, sur) == 0)
	{
		prev->next = p->next;
		free(p);
		printf("Osoba s prezimenom %s je obrisana iz liste.\n", sur);

	}
	else { printf("Osoba nije pronadena.\n"); }
	return 0;

}
//dinamièki dodaje novi element iza odreðenog elementa
int InsertAfter(position p)
{
	char sur[30];
	printf("Unesi prezime osobe iza koje zelis dodati novu:");
	scanf(" %s", sur);
	position q = NULL;
	q = (position)malloc(sizeof(person));
	if (q == NULL)
	{
		printf("Pogresna alokacija memorije!\n");
		return ERROR_ALLOCATION;
	}
	printf("Unesi ime osobe:");
	scanf(" %s", q->name);
	printf("Unesi prezime osobe:");
	scanf(" %s", q->surname);
	printf("Unesi godinu rodenja osobe:");
	scanf(" %d", &q->birthYear);

	while (p->next != NULL && strcmp(sur, p->surname) != 0)
	{
		p = p->next;
	}
	if (strcmp(sur, p->surname) == 0)
	{
		q->next = p->next;
		p->next = q;

	}
	else
	{
		printf("Krivo uneseno prezime.\n");
	}
	return 0;
}

//dinamièki dodaje novi element ispred odreðenog elementa
int InsertBefore(position p)
{
	char sur[30];
	printf("Unesi prezime osobe ispred koje zelis dodati novu:");
	scanf(" %s", sur);
	position q = NULL;
	q = (position)malloc(sizeof(person));
	if (q == NULL)
	{
		printf("Pogresna alokacija memorije!\n");
		return ERROR_ALLOCATION;
	}
	printf("Unesi ime osobe:");
	scanf(" %s", q->name);
	printf("Unesi prezime osobe:");
	scanf(" %s", q->surname);
	printf("Unesi godinu rodenja osobe:");
	scanf(" %d", &q->birthYear);
	position prev = NULL;
	while (p->next != NULL && strcmp(sur, p->surname) != 0)
	{

		prev = p;
		p = p->next;
	}
	if (prev != NULL && strcmp(sur, p->surname) == 0)
	{
		q->next = p;
		prev->next = q;

	}
	else
	{
		printf("Krivo uneseno prezime.\n");
	}

	return 0;
}
//sortira listu po prezimenima osoba
void SortBySurname(position p) {
	position j, prev_j, temp, end = NULL;

	while (p->next != end) {
		prev_j = p;
		j = p->next;

		while (j->next != end) {

			if (strcmp(j->surname, j->next->surname) > 0) {

				temp = j->next;
				prev_j->next = temp;
				j->next = temp->next;
				temp->next = j;


				j = temp;
			}
			prev_j = j;
			j = j->next;
		}
		end = j;
	}
}
//upisuje listu u datoteku
int FileWrite(position p)
{
	FILE* fp = NULL;
	fp = fopen("osobe.txt", "w");
	if (fp == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		return ERROR_OF;
	}
	while (p != NULL)
	{
		fprintf(fp, "%s %s %d\n", p->name, p->surname, p->birthYear);
		p = p->next;
	}
	fclose(fp);

	return 0;
}

//èita listu iz datoteke
int FileRead(position p)
{
	FILE* fp = NULL;
	fp = fopen("osobe.txt", "r");
	if (fp == NULL)
	{
		printf("Greska pri otvaranju datoteke.\n");
		return ERROR_OF;
	}
	char name[30];
	char surname[30];
	int birthYear;
	while (fscanf(fp, "%s %s %d", name, surname, &birthYear) == 3)
	{
		position NewPerson=NULL;
		NewPerson = (position)malloc(sizeof(person));
		if(NewPerson==NULL)
			{
			printf("Pogresna alokacija memorije.\n");
			fclose(fp);
			return ERROR_ALLOCATION;
			}

		strcpy(NewPerson->name,name);
		strcpy(NewPerson->surname,surname);
		NewPerson->birthYear = birthYear;
		NewPerson->next = NULL;
		while (p->next != NULL)
		{
			p = p->next;
		}
		p->next = NewPerson;
	}



	fclose(fp);

	return 0;
}

int main()
{
	person head;
	head.next = NULL;
	char option;




	while (1) {
		printf("A-dodaj novi element na pocetak liste\nB-ispisi listu\nC-dodaj novi element na kraj liste\nD - pronadi adresu elementa po prezimenu\nE - obrisi element iz liste\n");
		printf("F - dodaj element iza izabranog elementa\nG - dodaj element ispred izabranog elementa\nH-sortiraj listu po prezimenima\nI-lista se zapisuje u datoteci\n");
		printf("J - citaj listu iz datoteke\nQ-izlaz\n\n");
		scanf(" %c", &option);
		if (option == 'A')
			InsertStart(&head);
		else if (option == 'B')
			Print(head.next);
		else if (option == 'C')
			InsertEnd(&head);
		else if (option == 'D')
			FindBySurname(head.next);
		else if (option == 'E')
			Delete(&head);
		else if (option == 'F')
			InsertAfter(&head);
		else if (option == 'G')
			InsertBefore(&head);
		else if (option == 'H')
			SortBySurname(&head);
		else if (option == 'I')
			FileWrite(head.next);
		else if (option == 'J')
			FileRead(head.next);
		else if (option == 'Q')
			break;
		else
			printf("Neispravan unos.");







	}
	return 0;
}
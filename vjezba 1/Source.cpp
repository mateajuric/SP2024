#include <stdio.h>
#include <stdlib.h>
#define _CRT_SECURE_NO_WARNINGS
#define ERROR_OP 1
#define MAX 1024

int brojredaka(const char*);

int main()
{
	int brredaka=0;
	brredaka = brojredaka("imedatoteke.txt");
	return 0;
}
int brojredaka(const char*fileName)
{
	FILE *fp = NULL;
	char buffer[MAX] = {};
	int broj = 0;
	fp = fopen(fileName,"r");
	if (fp==NULL)
	{
		printf("Greska pri otvaranju datoteke.");
		return ERROR_OP;
	}
	while (!feof(fp))
	{
		fgets(buffer, MAX, fp);
		broj++;
	}
	fclose(fp);

}
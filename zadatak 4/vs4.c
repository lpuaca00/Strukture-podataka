#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <math.h>

#define MAX_LINE (1024)
#define MAX_SIZE (50)

struct _Number;
typedef struct _Number* Position;
typedef struct _Number {
	int koeficijent;
	int eksponent;
	Position next;
} Number;

Position CreateElement(int koeficijent, int eksponent);
int EnterFileName(char* fileName);
int ReadFile(Position head1, Position head2, char* fileName);
int ReadingNumbersAndSpaces(Position head, char* buffer);
int DeleteAfter(Position before);
int InsertSorted(Position head, Position new);
int Addition(Position a, Position b, Position c);
int FreeMemory(Position head);
int PrintNumbers(Position head);
int Multiplication(Position c, Position a, Position b);
int CreateAndInsertAfter(int koeficijent, int eksponent, Position position);


int main()
{
    Number head1 = { .next = NULL, .koeficijent = 0, .eksponent = 0 };
    Number head2 = { .next = NULL, .koeficijent = 0, .eksponent = 0 };
    Number ResultAdd = { .next = NULL, .koeficijent = 0, .eksponent = 0 };
    Number ResultMult = { .next = NULL, .koeficijent = 0, .eksponent = 0 };
    char filename[MAX_SIZE] = {0};    

    EnterFileName(filename);

    if(ReadFile(&head1, &head2, filename) == EXIT_SUCCESS) 
    {
        PrintNumbers(&head1);
        PrintNumbers(&head2);

        Addition(&head1, &head2, &ResultAdd);
        Multiplication(&ResultMult, &head1, &head2);

        PrintNumbers(&ResultAdd);
        PrintNumbers(&ResultMult);

        FreeMemory(&head1);
        FreeMemory(&head2);
        FreeMemory(&ResultMult);
        FreeMemory(&ResultAdd);
    }

    return EXIT_SUCCESS;
}

int EnterFileName(char* filename)
{
    printf("Unesite ime datoteke: ");
    scanf(" %s", filename);

    return EXIT_SUCCESS;
}

int ReadFile(Position head1, Position head2, char* fileName)
{
	FILE* datoteka = NULL;
	char buffer[MAX_LINE] = { 0 };

	datoteka = fopen(fileName, "r");
	if (!datoteka)
	{
		perror("Greska pri otvaranju datoteke!\n");
		return -1;
	}

	fgets(buffer, MAX_LINE, datoteka);
    if(!ReadingNumbersAndSpaces(head1, buffer)) {
        return EXIT_FAILURE;
    }

    fgets(buffer, MAX_LINE, datoteka);
    if(!ReadingNumbersAndSpaces(head2, buffer)) {
        return EXIT_FAILURE;
    }
	
    fclose(datoteka);

    return EXIT_SUCCESS;
}

int ReadingNumbersAndSpaces(Position head, char* buffer)
{
    Position newNumber = NULL;
    char* buffer2 = buffer;
    int koeficijent = 0, eksponent = 0, space = 0;

    while(strlen(buffer2) > 0) {
        sscanf(buffer2, " %d %d %n", &koeficijent, &eksponent, &space);

        newNumber = CreateElement(koeficijent, eksponent);
        if(!newNumber) {
            return EXIT_FAILURE;
        }

        InsertSorted(head, newNumber);

        buffer2 += space; 
    }
    
    return EXIT_SUCCESS;
}

Position CreateElement(int koeficijent, int eksponent)
{
	Position new = NULL;

	new = (Position)malloc(sizeof(Number));
	if (!new)
	{
		perror("Can't allocate memory!\n");
		return NULL;
	}

	new->koeficijent = koeficijent;
    new->eksponent = eksponent;
    new->next = NULL;

	return new;
}

int CreateAndInsertAfter(int koeficijent, int eksponent, Position position)
{
	Position new = CreateElement(koeficijent, eksponent);
	if (!new)
	{
		return EXIT_FAILURE;
	}

	new->next = position->next;
	position->next = new;

	position = position->next;

	return EXIT_SUCCESS;

}

int DeleteAfter(Position before)
{
	Position toDelete = NULL;

	toDelete = before->next;
	before->next = toDelete->next;
	free(toDelete);

	return EXIT_SUCCESS;
}

int Addition(Position a, Position b, Position c)
{
    Position temp1 = NULL, temp2 = NULL, temp3 = NULL;
    temp1 = a->next;
    temp2 = b->next;

    while(temp1 != NULL && temp2 != NULL) 
    {
        //new = (Position)malloc(sizeof(Number));

        if(temp1->eksponent == temp2->eksponent) {
            CreateAndInsertAfter(temp1->koeficijent + temp2->koeficijent, temp1->eksponent, c);
            temp1 = temp1->next;
            temp2 = temp2->next;
        }
        else if (temp1->eksponent < temp2->eksponent) {
			CreateAndInsertAfter(temp1->koeficijent, temp1->eksponent, c);
			temp1 = temp1->next;
		}
		else {
			CreateAndInsertAfter(temp2->koeficijent, temp2->eksponent, c);
			temp2 = temp2->next;
		}
    }

    if (temp1 == NULL) {
		temp3 = temp2;
	}
	else {
		temp3 = temp1;
	}

	while (temp3 != NULL) {
		CreateAndInsertAfter(temp3->koeficijent, temp3->eksponent, c);
		temp3 = temp3->next;
	}

	return EXIT_SUCCESS;
}

int Multiplication(Position c, Position a, Position b)
{
	Position temp1 = NULL, temp2 = NULL, new = NULL;

	for (temp1 = a->next; temp1 != NULL; temp1 = temp1->next)
	{
		for (temp2 = b->next; temp2 != NULL; temp2 = temp2->next)
		{
			new = CreateElement(temp1->koeficijent * temp2->koeficijent, temp1->eksponent + temp2->eksponent);
			if (!new) {
				return EXIT_FAILURE;
			}

			InsertSorted(c, new);
		}
	}

	return EXIT_SUCCESS;
}

int InsertSorted(Position head, Position new)
{
    Position temp = head;

    while(temp->next != NULL && temp->next->eksponent < new->eksponent) {
        temp = temp->next;
    }

    if(temp->next == NULL || temp->next->eksponent != new->eksponent) {
        new->next = temp->next;
	    temp->next = new;
    }
    else {
        int zbrojKoeficijenata = temp->next->koeficijent + new->eksponent;
        if(zbrojKoeficijenata == 0) {
            DeleteAfter(temp);
        } 
        else {
            temp->next->koeficijent = zbrojKoeficijenata;
        }
        free(new);
    }

    return EXIT_SUCCESS;
}

int PrintNumbers(Position head) {
    while (head->next != NULL) {
        printf("%dx^%d ", head->next->koeficijent, head->next->eksponent);
        head->next = head->next->next;
    }
    printf("\n");

    return EXIT_SUCCESS;
}

int FreeMemory(Position head)
{
	Position temp = head;

	while (temp->next)
	{
		DeleteAfter(temp);
	}
	
	return EXIT_SUCCESS;
}
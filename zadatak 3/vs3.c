#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)
 
struct _Person;
typedef struct _Person* Position;
typedef struct _Person {
	char name[MAX_SIZE];
	char surname[MAX_SIZE];
	int birthYear;
	Position next;
} Person;
 

int PrependList(Position head, char* name, char* surname, int birthYear);
int AppendList(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position after, Position position);
int InsertBefore(Position position);
Position FindLast(Position head);
Position FindPerson(Position first, char* surname);
Position FindBefore(Position head, char* surname);
int DeleteAfter(Position head, char* surname);
int SortList(Position head);
int WriteInFile(char* ime, Position head);
int ReadFromFile(char* ime, Position head);
int InsertAfter1(Position position, Position newPerson);
int menu(Position position);
int DeleteAll(Position head);


int main(int argc, char** argv) 
{ 
	Person head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position p = &head;

	int odabir = 0;
    
	menu(p);

	DeleteAll(p);

	return EXIT_SUCCESS;
}

int DeleteAll(Position head)
{
    Position temp=NULL;
    
    while (head->next!=NULL)
    {
        temp=head->next;
        head->next=temp->next;
        free(temp);
    }
    
    return 0;
}
 
int PrependList(Position head, char* name, char* surname, int birthYear) {
 
	Position newPerson = NULL;
 
	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		return -1;
	}
 
	InsertAfter1(head, newPerson);
 
	return EXIT_SUCCESS;
}
 
int AppendList(Position head, char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
	Position last = NULL;
 
	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		return -1;
	}
 
	last = FindLast(head);
	InsertAfter1(last, newPerson);
 
	return EXIT_SUCCESS;
}

int InsertAfter1 (Position position, Position newPerson)
{
	newPerson->next = position->next;
	position->next = newPerson;
 
	return EXIT_SUCCESS;
}

int PrintList(Position first)
{
	Position temp = first;
 
	while (temp) {
		printf("Name: %s, surname: %s, birthyear: %d\n", temp->name, temp->surname, temp->birthYear);
		temp = temp->next;
	}
 
	return EXIT_SUCCESS;
}
 
Position CreatePerson(char* name, char* surname, int birthYear)
{
	Position newPerson = NULL;
 
	newPerson = (Position)malloc(sizeof(Person));
	if (!newPerson) {
		perror("Can't allocate memory!\n");
		return NULL;
	}
 
	strcpy(newPerson->name, name);
	strcpy(newPerson->surname, surname);
	newPerson->birthYear = birthYear;
	newPerson->next = NULL;
 
	return newPerson;
}
 
int InsertAfter(Position after, Position position)
{
	Position newPerson = NULL;
	char surname[20] = {0}, name[20] = {0};
	int birthYear;

	printf("Unesite ime, prezime i godiste osobe.");
	scanf(" %s %s %d", name, surname, &birthYear);

	newPerson = CreatePerson(name, surname, birthYear);

	if(!after && !newPerson) {
        return -1;
    }

	newPerson->next = after->next;
	after->next = newPerson;
 
	return EXIT_SUCCESS;
}

int InsertBefore(Position position)
{
	Position newPerson = NULL;
    Position ispred = NULL;
	char osoba[20] = {0};
	char surname[20] = {0}, name[20] = {0};
	int birthYear;

	printf("Unesite prezime osobe ispred koje zelite unijeti novu osobu");
	scanf(" %s", osoba);

	ispred = FindBefore(position->next, osoba);

	printf("Unesite ime, prezime i godiste osobe.");
	scanf(" %s %s %d", name, surname, &birthYear);

	newPerson = CreatePerson(name, surname, birthYear);

	if(!ispred && !newPerson) {
        return -1;
    }

	InsertAfter(ispred, position);

	return EXIT_SUCCESS;
}
 
Position FindLast(Position head)
{
	Position temp = head;
 
	while (temp->next) {
        temp = temp->next;
	}
 
	return temp;
}
 
Position FindPerson(Position first, char* surname)
{
	Position temp = first;
	while (temp) {
		if (strcmp(temp->surname, surname) == 0) {
			return temp;
		}
        temp = temp->next;
	}

	return temp;
}

Position FindBefore(Position head, char* surname)
{
    Position temp = head;

    while (temp->next != NULL && strcmp(temp->next->surname, surname) != 0) {
		    temp = temp->next;       
	    }

    return temp;
}

int DeleteAfter(Position head, char* surname)
{
    Position before = NULL;
    Position ToDelete = NULL;

    before = FindBefore(head, surname);

    ToDelete = before->next;

	if (!ToDelete) 
		return EXIT_SUCCESS;
	
	
    before->next = ToDelete->next;
    free(ToDelete);

    return EXIT_SUCCESS;
}

int SortList(Position head)
{

    Position temp1 = NULL, temp2 = NULL, temp3 = NULL, end = NULL;

    while(head->next!=end){
        temp1 = head;
        temp2 = head->next;
        while(temp2->next!=end){
            if(strcmp(temp2->surname, temp2->next->surname)>0){
                temp3 = temp2->next;
                temp1->next = temp3;
                temp2->next = temp3->next;
                temp3->next = temp2;
                temp2 = temp3;
            }
            temp1 = temp2;
            temp2 = temp2->next;
        }
        end = temp2;
    }

    return 0;
}

int WriteInFile(char* ime, Position head)
{
	FILE* datoteka = NULL;
    Position temp = head->next;

    datoteka = fopen(ime, "w");
	if(!datoteka) {
		printf("Neuspjesno otvaranje datoteke!");
		return -1;
	}

    while(temp) {
        fprintf(datoteka, " %s\t%s\t%d\n", temp->name, temp->surname, temp->birthYear);
        temp = temp->next;
    }
    
    fclose(datoteka);

    return EXIT_SUCCESS;
}

int ReadFromFile(char* ime, Position head)
{
    Position temp=head;
    FILE* datoteka = NULL;
    char buffer[MAX_SIZE]={0}, name[20]={0}, surname[20]={0};
    int birthYear=0;
    
    datoteka = fopen(ime, "r");
    if(!datoteka) {
        printf("Neuspjesno otvaranje datoteke.");
        return -1;
    }
    
    while(!feof(datoteka))
    {
        fgets(buffer, MAX_SIZE, datoteka);
        fgets(buffer, MAX_SIZE, datoteka);
    }
    
    fclose(datoteka);

    return EXIT_SUCCESS;
}

int menu(Position position) 
{
	char ime = {0};
    char odabir = {0};
	int birthYear = 0;
    char name[20] = {0}, surname[20] = {0};
    char odabir2[20] = {0};
	Position after = NULL;
	char osoba[20] = {0};

	printf("Odaberite sto zelite napraviti u listi: \n"
		   "1 - Dodati novu osobu u listu na pocetak\n"
		   "2 - Dodati novu osobu u listu na kraj\n"
		   "3 - Isprintati listu\n"
		   "4 - Izbrisati nekoga s liste\n"
		   "5 - Sortirati listu\n"
		   "6 - Napisati listu u datoteku\n"
		   "7 - Ispisati listu iz datoteke\n"
		   "8 - Dodati novu osobu nakon nekoga\n"
		   "9 - Dodati novu osobu ispred nekoga\n\n");

	scanf(" %s", &odabir);

	switch(odabir) {
		case 1:
		{
			while(1) {
				printf("Unesite ime, prezime i godiste osobe.");
				scanf(" %s %s %d", name, surname, &birthYear);

				PrependList(position, name, surname, birthYear);
			}

			break;
		}
		case 2:
		{
			while(1) {
				printf("Unesite ime, prezime i godiste osobe.");
				scanf(" %s %s %d", name, surname, &birthYear);
			
				AppendList(position, name, surname, birthYear);
			}

			break;
		}
		case 3:
        {
        	PrintList(position->next);

        	break;
        }
		case 4:
        {
            printf("Unesite prezime osobe koju zelite izbrisati: \n");
            scanf(" %s", odabir2);
           
		    DeleteAfter(position, odabir2);
           
		    break;
        }
		case 5:
		{
			SortList(position);
			
			break;
		}
		case 6:
		{
			printf("Unesite ime datoteke u koju zelite unijeti listu: \n");
            scanf(" %s", odabir2);

			strcat(odabir2, ".txt");

            WriteInFile(odabir2, position);

            break;
		}
		case 7:
		{
			printf("Unesite ime datoteke iz koje zelite procitati listu: \n");
            scanf(" %s", odabir2);
			
			strcat(odabir2, ".txt");
            
			ReadFromFile(odabir2, position);
            
			break;
		}
		case 8:
		{
			printf("Unesite prezime osobe iza koje zelite unijeti novu osobu");
			scanf(" %s", osoba);

			after = FindPerson(position->next, osoba);

			InsertAfter(after,position);

			break;
		}
		case 9:
		{
			InsertBefore(position);

			break;
		}
		default:
		{
			printf("Krivo ste unijeli odabir. ");
			
			break;
		}
	}

	return 0;
}
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
}Person;
 
int PrependList(Position head, char* name, char* surname, int birthYear);
int AppendList(Position head, char* name, char* surname, int birthYear);
int PrintList(Position first);
Position CreatePerson(char* name, char* surname, int birthYear);
int InsertAfter(Position position, Position newPerson);
int InsertBefore(Position position, Position newPerson);
Position FindLast(Position head);
Position FindPerson(Position first, char* surname);
Position FindBefore(Position head, char* surname);
int DeleteAfter(Position head, char* surname);
int SortList(Position head);
int WriteInFile(FILE *datoteka, Position head);
int ReadFromFile(FILE *datoteka);

int main(int argc, char** argv) {
 
	Person head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position p = &head;
    Position newPerson1 = NULL;
    Position newPerson2 = NULL;
    Position after = NULL;
    Position ispred = NULL;

    PrependList(&head, "Lucijana", "Puaca", 2001);
	AppendList(&head, "Karla", "Pupacic", 2002);
	PrependList(&head, "Ivo", "Ivic", 1997);
	
	PrintList(p->next);
	printf("\n");

	after = FindPerson(head.next, "Puaca");
    ispred = FindBefore(&head, "Pupacic");
	//DeleteAfter(&head, "Pupacic");

    newPerson1 = CreatePerson("Katarina", "Novakovic", 2000);
    newPerson2 = CreatePerson("Ivona", "Pavela", 2001);

    if(!after && !newPerson1) {
        return -1;
    }

    InsertAfter(after, newPerson1);
	
    if(!ispred && !newPerson2) {
        return -1;
    }

    InsertBefore(ispred, newPerson2);

    PrintList(p->next);
	printf("\n");

    SortList(&head);

    PrintList(p->next);
	printf("\n");

	return EXIT_SUCCESS;
}
 
int PrependList(Position head, char* name, char* surname, int birthYear) {
 
	Position newPerson = NULL;
 
	newPerson = CreatePerson(name, surname, birthYear);
	if (!newPerson) {
		return -1;
	}
 
	InsertAfter(head, newPerson);
 
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
	InsertAfter(last, newPerson);
 
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
 
int InsertAfter(Position position, Position newPerson)
{
	newPerson->next = position->next;
	position->next = newPerson;
 
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

int InsertBefore(Position position, Position newPerson) 
{
    InsertAfter(position, newPerson);

    return EXIT_SUCCESS;
}

int SortList(Position head){

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

int WriteInFile(FILE *datoteka, Position head)
{
    Position temp = head->next;

    datoteka = fopen("lista.txt", "w");

    while(temp) {
        fprintf(datoteka, " %s\t%s\t%d\n", temp->name, temp->surname, temp->birthYear);
        temp = temp->next;
    }
    
    fclose(datoteka);

    return EXIT_SUCCESS;
}

int ReadFromFile(FILE *datoteka)
{
    //ne razumijem kako se koristi buffer ali znam da treba s njim rijesiti
    //pa cu ovo nadopuniti naknadno

    return EXIT_SUCCESS;
}
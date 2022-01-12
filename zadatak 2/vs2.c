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
Position FindLast(Position head);
Position FindPerson(Position first, char* surname);
Position FindBefore(Position head, char* surname);
int DeleteAfter(Position head, char* surname);
 
int main(int argc, char** argv) {
 
	Person head = { .next = NULL, .name = {0}, .surname = {0}, .birthYear = 0 };
	Position p = &head;
 
    PrependList(&head, "Lucijana", "Puaca", 2001);
	AppendList(&head, "Karla", "Pupacic", 2002);
	PrependList(&head, "Ivo", "Ivic", 1997);
	
	PrintList(p->next);
	printf("\n");

	FindPerson(head.next, "Puaca");

	DeleteAfter(&head, "Pupacic");

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

	if (!ToDelete) {
		return EXIT_SUCCESS;
	}
	
    before->next = ToDelete->next;
    free(ToDelete);

    return EXIT_SUCCESS;
}
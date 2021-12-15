#include<stdio.h>
#include<stdlib.h>
#include<string.h>

#define MAX (50)

struct direktorij;
typedef struct direktorij* Position;
typedef struct direktorij {
	char name[MAX];
	Position child;
	Position sibling;

} Direktorij;

struct stog;
typedef struct stog* SPosition;
typedef struct stog {
	Position directory;
	SPosition next;

} Stog;

Position CreateDirectory(char* name);
int Izbornik(Position current);
Position Insert(Position current, Position q); //md
int PrintContent(Position current); //dir
Position ChangeDirectory(Position current); //cd dir
int Exit(Position current); //exit
Position ReturnToPrevious(Position current, Stog head); //cd..


int main()
{
	Direktorij root = { .child = NULL, .sibling = NULL, .name = {0} };
    Stog head = { .directory = NULL, .next = NULL };
	int brojac = 0;

    Izbornik(&root);

	return 0;
}

Position Insert(Position current, Position q) 
{
    char name[MAX] = {0};

    printf("Enter name of new directory: \n");
    scanf(" %s", name);

    q = CreateDirectory(&name);

    if(current == NULL) {
        return q;
    }

    if(strcmp(current -> name, q -> name) > 0) {
        q -> sibling = current;
        return q;
    }
    else if(strcmp(current -> name, q -> name) < 0) {
        current -> sibling = insert(current -> sibling, q);
    }
    else {
        printf("The directory already exists!\n");
        free(q);
    }

    return current;
}

int PrintContent(Position current)
{
	if (current -> child == NULL)
	{
		printf("The directory is empty!\n");
		return 0;
	}

	current = current -> child;

	printf("Direktoriji: \n");
	printf("\t%s\n", current -> name);

	while (current -> sibling != NULL)
	{
		printf("\t%s\n", current -> sibling -> name);
		current = current -> sibling;
	}

	return 0;
}

int Izbornik(Position current)
{
	char choice[MAX] = { 0 };
	
	printf("----------------------------------------------------------\n");
	printf("Menu\n");
	printf("md <filename> - Add new directory\n");
	printf("cd dir <filename> - Open directory\n");
	printf("cd.. - Return to previous directory\n");
	printf("dir - Print current directory's content\n");
    printf("exit - Leave the program\n");
	printf("----------------------------------------------------------\n");

	while (1)
	{
		scanf(" %s", choice);

		if (!strcmp(choice, "md"))  {
			Insert(current, current);
        }
		else if (!strcmp(choice, "cd dir")) {
			current = cd(current);
        }
		else if (!strcmp(choice, "cd..")) {
			//current = nazad(current, head);
        }
		else if (!strcmp(choice, "dir")) {
			direktorij(current);
        }
		else if (!strcmp(choice, "exit")) {
			Exit(current);
        }
		else if(!strcmp(choice,"Menu")) {
			return 0;
        }
		else {
			printf("Command does not exist!\n");
        }
	}

	return 0;
}

Position ReturnToPrevious(Position current, SPosition head)
{
	SPosition first = NULL;
	first = head -> next;

	Position temp = NULL;

	if (!first)
	{
		printf("This directory does not have a parent!\n");
		return current;
	}
	temp = first->directory;

	head -> next = first -> next;
	free(first);

	return temp;
}

Position ChangeDirectory(Position current)
{
	char name[MAX] = { 0 };
	Position temp = current -> child;

	printf("Which directory do you want to enter: ");
	scanf(" %s", name);

	while (temp != NULL && strcmp(name, temp -> name) != 0)
	{
		temp = temp -> sibling;
	}

	if (!temp)
	{
		printf("The directory does not exist!\n");
		return NULL;
	}

	return temp;
}

int Exit(Position current)
{

	if (current == NULL)
	{
		return 0;
	}

	Exit(current->sibling);
	Exit(current->child);
	Exit(current->sibling);

	free(current);

	return 0;
}

Position CreateDirectory(char* name)
{
	Position newDirectory = NULL;
 
	newDirectory = (Position)malloc(sizeof(Direktorij));
	if (!newDirectory) {
		perror("Can't allocate memory!\n");
		return NULL;
	}
 
	strcpy(newDirectory->name, name);
	newDirectory -> child = NULL;
    newDirectory -> sibling = NULL;
 
	return newDirectory;
}
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAX_SIZE (50)

struct _StackElement;
typedef struct _StackElement* Position;
typedef struct _StackElement {
	double number;
	Position next;
} StackElement;

int EnterFileName(char* filename);
Position CreateElement(double number);
int InsertAfter(Position position, Position newElement);
int Push(Position head, double number);
int DeleteAfter(Position position);
int Pop(double* result, Position head);
char* ReadFile(char* filename);
int PerformOperation(Position head, char operation);
int CalculatePostfix(double* result, char* filename);
int DeleteAll(Position head);

int main()
{
	double result = 0;
    char filename[MAX_SIZE] = {0};    

    EnterFileName(filename);

	if (CalculatePostfix(&result, filename) == EXIT_SUCCESS) {
		printf("Result is: %0.1lf\n", result);
	}

	return EXIT_SUCCESS;
}

int EnterFileName(char* filename)
{
    printf("Unesite ime datoteke: ");
    scanf(" %s", filename);

    return EXIT_SUCCESS;
}

Position CreateElement(double number)
{
	Position newElement = NULL;

	newElement = (Position)malloc(sizeof(StackElement));
	if (!newElement) {
		perror("Can't allocate memory!\n");
		return NULL;
	}

	newElement->number = number;
	newElement->next = NULL;

	return newElement;
}

int InsertAfter(Position position, Position newElement)
{
	newElement->next = position->next;
	position->next = newElement;

	return EXIT_SUCCESS;
}

int Push(Position head, double number)
{
	Position newElement = NULL;

	newElement = CreateElement(number);
	if (!newElement) {
		return -1;
	}

	InsertAfter(head, newElement);

	return EXIT_SUCCESS;
}

int DeleteAfter(Position position)
{
	Position temp = position->next;

	if (!temp) {
		return EXIT_SUCCESS;
	}

	position->next = temp->next;
	free(temp);

	return EXIT_SUCCESS;
}

int Pop(double* result, Position head)
{
	Position first = head->next;

	if (!first) {
		perror("Postfix not valid! Please check your file!\n");
		return -1;
	}

	*result = first->number;
	DeleteAfter(head);

	return EXIT_SUCCESS;
}

int DeleteAll(Position head)
{
	while (head->next) {
		DeleteAfter(head);
	}

	return EXIT_SUCCESS;
}

int PerformOperation(Position head, char operation)
{
	double operand1 = 0;
	double operand2 = 0;
	double result = 0;
	int status1 = EXIT_SUCCESS;
	int status2 = EXIT_SUCCESS;

	status2 = Pop(&operand2, head);
	if (status2 != EXIT_SUCCESS) {
		return -1;
	}

	status1 = Pop(&operand1, head);
	if (status1 != EXIT_SUCCESS) {
		return -2;
	}

	switch (operation)
	{
	case '+':
		result = operand1 + operand2;
		break;
	case '-':
		result = operand1 - operand2;
		break;
	case '*':
		result = operand1 * operand2;
		break;
	case '/':
		if (operand2 == 0) {
			perror("Cannot divide with zero!\n");
			return -3;
		}
		result = operand1 / operand2;
		break;
	default:
		printf("Does not exist.\n");
		return -4;
	}

	return Push(head, result);
}

char* ReadFile(char* filename)
{
    FILE* file = NULL;
    int fileLength = 0;
    char* buffer = NULL;

    file = fopen(filename, "rb");
    if (!file) {
        perror("Can't open file!\n");
        return NULL;
    }

    fseek(file, 0, SEEK_END);
    fileLength = ftell(file);

    buffer = (char*)calloc(fileLength + 1, sizeof(char));
    if (!buffer) {
        perror("Can't allocate memory!\n");
        return NULL;
    }

    rewind(file);
    fread(buffer, sizeof(char), fileLength, file);
    printf("|%s|\n", buffer);
    fclose(file);

    return buffer;
}

int CalculatePostfix(double* result, char* filename)
{
	char* buffer = NULL;
	char* currentBuffer = NULL;
	int numBytes = 0;
	double number = 0;
	int status = 0;
	char operation = 0;
	StackElement head = { .next = NULL, .number = 0 };

	buffer = ReadFile(filename);
    currentBuffer = buffer;

	while (strlen(currentBuffer) > 0) {
		status = sscanf(currentBuffer, " %lf %n", &number, &numBytes);
		if (status == 1) {
			status = Push(&head, number);
			if (status != EXIT_SUCCESS) {
				free(buffer);
				DeleteAll(&head);
				return -3;
			}
			currentBuffer += numBytes;
		}
		else {
			sscanf(currentBuffer, " %c %n", &operation, &numBytes);
			status = PerformOperation(&head, operation);
			if (status != EXIT_SUCCESS) {
				free(buffer);
				DeleteAll(&head);
				return -4;
			}
			currentBuffer += numBytes;
		}
	}

	free(buffer);

	status = Pop(result, &head);
	if (status != EXIT_SUCCESS) {
		DeleteAll(&head);
		return -5;
	}

	if (head.next) {
		printf("Postfix not valid! Please check your file!\n");
		DeleteAll(&head);
		return -6;
	}

	return EXIT_SUCCESS;
}


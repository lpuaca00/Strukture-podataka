#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct _tree;
typedef struct _tree* Position;
typedef struct _tree {
    int number;
    Position left;
    Position right;

} tree;

Position CreateNew(int num);
int PrintPostorder(Position root);
int PrintInorder(Position root);
int PrintPreorder(Position root);
Position Insert(Position q, int num);
Position Minimum(Position root);
Position Delete(Position root, int num);
Position Search(Position root, int num);
int Menu(Position current);
Position PrintLevel(Position root, int brojac);
Position PrintLevelorder(Position root);

int main() 
{
    tree root = { .left = NULL, .right = NULL, .number = 0 };
    int brojac = 0;

    do {
		brojac = Menu(&root);
	} 
    while (brojac >= 0);

    return EXIT_SUCCESS;
}

int Menu(Position current) 
{
    char choice[50] = { 0 };
    int num = 0;
    Position found = NULL;
	
	printf("----------------------------------------------------------\n");
	printf("Menu: \n");
	printf("A - insert new element\n");
	printf("B - print postorder\n");
	printf("C - print inorder\n");
	printf("D - print preorder\n");
    printf("G - print level order\n");
    printf("E - delete element\n");
    printf("F - search element\n");
	printf("----------------------------------------------------------\n");

	while (1)
	{
		scanf(" %s", choice);

		if (!strcmp(choice, "A"))  {
            printf("Enter the number you want inserted to tree: \n");
            scanf("%d ", &num);
			Insert(current, num);
        }
		else if (!strcmp(choice, "B")) {
			PrintPostorder(current);
        }
		else if (!strcmp(choice, "C")) {
			PrintInorder(current);
        }
		else if (!strcmp(choice, "D")) {
			PrintPreorder(current);
        }
        else if (!strcmp(choice, "G")) {
			PrintLevelorder(current);
        }
		else if (!strcmp(choice, "E")) {
			printf("Enter the number you want to delete: \n");
            scanf("%d ", &num);
			Delete(current, num);
        }
        else if (!strcmp(choice, "F")) {
			printf("Enter the number you want to find: \n");
            scanf("%d ", &num);
			found = Search(current, num);
            printf("Number: %d\nLeft: %d\nRight: %d\n", found -> number, found -> left, found -> right);
        }
		else if(!strcmp(choice,"Menu")) {
			return 0;
        }
		else {
			printf("Command does not exist!\n");
        }
	}

	return EXIT_SUCCESS;
}

Position CreateNew(int num)
{
    Position new = (Position)malloc(sizeof(tree));

    if (!new)
    {
        printf("Couldn't allocate memory!\n");
        return EXIT_FAILURE;
    }

    new -> number = num;
    new -> left = new -> right = NULL;

    return new;
}

int PrintPostorder(Position root)
{
    if (root != NULL) {
        PrintPostorder(root -> left);
        PrintPostorder(root -> right);
        printf("%d ", root -> number);
    }

    return EXIT_SUCCESS;
}

int PrintInorder(Position root)
{
    if (root != NULL) {
        PrintInorder(root -> left);
        printf("%d ", root -> number);
        PrintInorder(root -> right);
    }

    return EXIT_SUCCESS;
}

int PrintPreorder(Position root)
{
    if (root != NULL) {
        printf("%d ", root -> number);
        PrintPreorder(root -> left);
        PrintPreorder(root -> right);
    }

    return EXIT_SUCCESS;
}

//ispis level ordera
Position PrintLevel(Position root, int brojac)
{
    Position current1 = NULL, current2 = NULL;

    if (root == NULL) {
        return EXIT_FAILURE;
    }
 
    if (brojac == 1)
    {
        printf("%d ", root -> number);
        return 0;
    }
    
    current1 = PrintLevel(root -> left, brojac - 1);
    current2 = PrintLevel(root -> right, brojac - 1);

    if(current1 || current2) {
        return EXIT_SUCCESS;
    }

}
Position PrintLevelorder(Position root)
{
    int brojac = 1;

    if(root == NULL) {
        printf("There is nothing to print!\n");
    }

    while(PrintLevel(root, brojac)) {
        brojac++;
    }

    return EXIT_SUCCESS;
}

Position Insert(Position q, int num)
{
    if (q == NULL) {
        return CreateNew(num);
    }
    if (num < q -> number) {
        q -> left = Insert(q -> left, num);
    }
    else {
        q -> right = Insert(q -> right, num);
    }

    return q;
}

Position Minimum(Position root)
{
    Position temp = root;

    while (temp && temp -> left != NULL)
        temp = temp -> left;

    return temp;
}

Position Delete(Position root, int num)
{
    Position temp = NULL;

    if (root == NULL) {
        return root;
    }

    if (num < root -> number) {
        root -> left = Delete(root -> left, num);
    }
    else if (num > root -> number) {
        root -> right = Delete(root -> right, num);
    }
    else {
        if (root -> left == NULL) {
            temp = root -> right;
            free(root);
            return temp;
        }
        else if (root -> right == NULL) {
            temp = root -> left;
            free(root);
            return temp;
        }
        
        temp = Minimum(root -> right);
        root -> number = temp -> number;
        root -> right = Delete(root -> right, temp -> number);
    }

    return root;
}

Position Search(Position root, int num)
{
    Position found = NULL;

    if (root == NULL || root  -> number == num) {
        return root;
    }
   
    if (root -> number < num) {
        found = Search(root -> right, num);
        return found;
    }
    else {
        found = Search(root -> left, num);
        return found;
    }
 
}

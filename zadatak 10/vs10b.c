#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>

struct gradovi;
typedef struct gradovi* Position;
struct gradovi {
    char ime[20];
    int stanovnici;
    Position next;
};

struct drzave;
typedef struct drzave* CouPosition;
struct drzave {
    char ime[20];
    Position grad;
    CouPosition d;
    CouPosition l;
};

CouPosition dodajDrzavu(CouPosition p, char* imeDrzave, char* datGrad);
int dodajGradove(CouPosition p, char* datGrad);
int printDrzaveInorder(CouPosition p);
int printGradove(Position p);
int usporediGradove(Position p, Position q);
int trazi(CouPosition p, char* imeDrzave, int stanovnici);
CouPosition traziDrzavu(CouPosition p, char* imeDrzave);

int main()
{
    CouPosition root = NULL;
    FILE* f = NULL;
    char imeDrzave[20] = {0};
    char datGrad[20] = {0};
    int stanovnici = 0;

    f = fopen("drzave.txt", "r");
    if(f == NULL) {
        perror("Greska pri otvaranju datoteke!\n");
        return 0;
    }

    while(!feof(f)) {
        fscanf(f, "%s %s", imeDrzave, datGrad);
        root = dodajDrzavu(root, imeDrzave, datGrad);
    }
    fclose(f);
    printDrzaveInorder(root);

    printf("Unesite drzavu koju zelite pregledati: ");
    scanf("%s", imeDrzave);
    printf("Minimalan broj stanovnika po gradu: ");
    scanf("%d", &stanovnici);
    trazi(root, imeDrzave, stanovnici);

    return EXIT_SUCCESS;
}

int printDrzaveInorder(CouPosition p) {
    if(p == NULL) {
        return 0;
    }

    printDrzaveInorder(p->l);
    printf("%s\n", p->ime);
    printGradove(p->grad->next);
    printDrzaveInorder(p->d);
    
    return 0;
}

int printGradove(Position p) {
    while(p != NULL) {
        printf("\t%s %d\n", p->ime, p->stanovnici);
        p = p->next;
    }

    return EXIT_SUCCESS;
}

CouPosition dodajDrzavu(CouPosition p, char* imeDrzave, char* datGrad) {
    CouPosition q = NULL;
    Position h = NULL;
    if(p == NULL) {
        q = (CouPosition)malloc(sizeof(struct drzave));
        
        if(q == NULL) {
            perror("Greska pri alokaciji!\n");
            return NULL;
        }
        strcpy(q->ime, imeDrzave);

        h = (Position)malloc(sizeof(struct gradovi));
        
        if(q == NULL) {
            perror("Greska pri alokaciji!\n");
            return NULL;
        }
        
        strcpy(h->ime, "");
        h->stanovnici = 0;
        h->next = NULL;
        q->grad = h;

        dodajGradove(q->grad, datGrad);
        q->l = NULL;
        q->d = NULL;

        return q;
    }

    else if(strcmp(p->ime, imeDrzave) > 0) {
        p->l = dodajDrzavu(p->l, imeDrzave, datGrad);
    }
    else if(strcmp(p->ime, imeDrzave) < 0) {
        p->d = dodajDrzavu(p->d, imeDrzave, datGrad);
    }

    return p;
}

int dodajGradove(Position p, char* datGrad) {
    Position q = NULL;
    FILE* f = NULL;
    char ime[20];
    int stan = 0;
    Position prev = p;
    Position poc = p;

    f = fopen(datGrad, "r");
    if(f == NULL) {
        perror("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    while(!feof(f)) {
        prev = poc;
        p = poc;
        
        fscanf(f, "%s %d", ime, &stan);
        
        q = (Position)malloc(sizeof(struct gradovi));
        
        if(q == NULL) {
            perror("Greska pri alokaciji!\n");
            return -1;
        }
        strcpy(q->ime, ime);
        q->stanovnici = stan;
        
        while(p != NULL) {
            if(p->next == NULL) {
                q->next = p->next;
                p->next = q;
                break;
            }
            if(usporediGradove(q, prev->next) == 1) {
                q->next = prev->next;
                prev->next = q;
                break;
            }
            prev = p;
            p = p->next;
        }
    }
    fclose(f);
    
    return EXIT_SUCCESS;
}

int usporediGradove(Position p, Position q) {
    if(p->stanovnici > q->stanovnici)
        return 1;
    else if(p->stanovnici < q->stanovnici)
        return -1;
    else {
        if(strcmp(p->ime, q->ime) > 0)
            return 1;
        else if(strcmp(p->ime, q->ime) < 0)
            return -1;
    }

    return EXIT_SUCCESS;
}

int trazi(CouPosition p, char* imeDrzave, int stanovnici) {
    CouPosition drzava = NULL;
    Position h = NULL;
    int x = 0;

    drzava = traziDrzavu(p, imeDrzave);
    if(drzava == NULL) {
        printf("Nema te drzave!\n");
        return 0;
    }
    h = drzava->grad;

    if(h == NULL) {
        printf("Nema nijedan grad u toj drzavi!\n");
        return 0;
    }
    h = h->next;
    
    while(h != NULL) {
        if(h->stanovnici >= stanovnici) {
            printf("\t%s\n", h->ime);
            x = 1;
        }
        else break;
        h = h->next;
    }
    
    if(x == 0)
        printf("Nema nijedan takav grad!\n");

    return EXIT_SUCCESS;
}

CouPosition traziDrzavu(CouPosition p, char* imeDrzave) {
    if(p == NULL)
        return NULL;
    if(strcmp(imeDrzave, p->ime) == 0)
        return p;
    if(strcmp(imeDrzave, p->ime) < 0)
        return traziDrzavu(p->l, imeDrzave);
    if(strcmp(imeDrzave, p->ime) > 0)
        return traziDrzavu(p->d, imeDrzave);
}
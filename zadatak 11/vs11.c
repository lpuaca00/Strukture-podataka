#include<stdio.h>
#include<stdlib.h>
#include<malloc.h>
#include<string.h>
#define N 11

struct gradovi;
typedef struct gradovi* Position;
struct gradovi {
    char ime[20];
    int stanovnici;
    Position d;
    Position l;
};

struct drzave;
typedef struct drzave* CouPosition;
struct drzave {
    char ime[20];
    Position grad;
    CouPosition next;
};

int dodajDrzavu(CouPosition p, char* ime, char* dat);
int dodajGrad(Position p, char* dat);
Position unosGrada(Position p, char* ime, int stan);
int printDrzave(CouPosition p);
int printGradove(Position p);
CouPosition traziDrzavu(CouPosition p, char* ime);
int traziGrad(Position p, int broj);
int kljucZaDrzavu(char* imeDrzave);

int main()
{
    struct drzave head = {.ime = "", .grad = NULL, .next = NULL};
    struct drzave hash[N];
    FILE* f = NULL;
    char imeDrzave[20] = {0};
    char datGrad[20] = {0};
    CouPosition p = NULL;
    int broj = 0;
    Position h = NULL;
    int kljuc = 0;
    int i = 0;

    for(i = 0; i < N; i++) {
        hash[i].grad = NULL;
        hash[i].next = NULL;
        strcpy(hash[i].ime, "");
    }

    f = fopen("drzave.txt", "r");
    if(f == NULL) {
        perror("Greska pri otvaranju datoteke!\n");
        return -1;
    }
    
    while(!feof(f)) {
        fscanf(f, "%s %s", imeDrzave, datGrad);
        kljuc = kljucZaDrzavu(imeDrzave);
        dodajDrzavu(&head, imeDrzave, datGrad);
    }
    fclose(f);

    printf("Lista drzava:\n");
    for(i = 0; i < N; i++)
    {
        printf("Hash[%d]:\n", i);
        printDrzave(hash[i].next);
    }
    printf("\n\n");

    printf("\nUnesite ime države koju zelite pregledati: ");
    scanf("%s", imeDrzave);
    kljuc = kljucZaDrzavu(imeDrzave);
    p = traziDrzavu(&hash[kljuc], imeDrzave);
    if(p == NULL) {
        printf("Ta država ne postoji!\n");
        return 0;
    }
    printf("Minimalan broj stanovnika: ");
    scanf("%d", &broj);
    printf("\nGradovi te države (%s) sa vise od %d stanovnika:\n", p->ime, broj);
    traziGrad(p->grad, broj);

    return EXIT_SUCCESS;
}

int dodajDrzavu(CouPosition p, char* ime, char* dat) {
    CouPosition q = NULL;
    CouPosition prev = NULL;
    Position h = NULL;
    
    q = (CouPosition)malloc(sizeof(struct drzave));
    
    if(q == NULL) {
        perror("Greska pri alokaciji!\n");
        return -1;
    }
    
    strcpy(q->ime, ime);
    q->grad = h;

    h = (Position)malloc(sizeof(struct gradovi));
    
    if(h == NULL) {
        perror("Greska pri alokaciji!\n");
        return -1;
    }
    
    strcpy(h->ime, "");
    h->stanovnici = 0;
    h->d = NULL;
    h->l = NULL;
    q->grad = h;
    dodajGrad(q->grad, dat);

    prev = p;
    while(p != NULL) {
        if(p->next == NULL) {
            p->next = q;
            q->next = NULL;
            break;
        }
        if(strcmp(q->ime, prev->next->ime) < 0) {
            q->next = prev->next;
            prev->next = q;
            break;
        }
        prev = p;
        p = p->next;
    }
    
    return EXIT_SUCCESS;
}

int dodajGrad(Position p, char* dat) {
    FILE* f = NULL;
    char ime[20];
    int stan = 0;

    f = fopen(dat, "r");
    if(f == NULL) {
        perror("Greska pri otvaranju datoteke!\n");
        return -1;
    }

    while(!feof(f)) {
        fscanf(f, "%s %d", ime, &stan);
        p = unosGrada(p, ime, stan);
    }
    fclose(f);
    
    return EXIT_SUCCESS;
}

Position unosGrada(Position p, char* ime, int stan)
{
    Position q = NULL;
    if(p == NULL) {
        q = (Position)malloc(sizeof(struct gradovi));
        
        if(q == NULL) {
            perror("Greska pri alociranju!\n");
            return NULL;
        }
        
        strcpy(q->ime, ime);
        q->stanovnici = stan;
        q->l = NULL;
        q->d = NULL;
        
        return q;
    }
    
    if(stan > p->stanovnici) {
        p->d = unosGrada(p->d, ime, stan);
    }
    if(stan < p->stanovnici) {
        p->l = unosGrada(p->l, ime, stan);
    }
    if(stan == p->stanovnici) {
        if(strcmp(ime, p->ime) >= 0) {
            p->d = unosGrada(p->d, ime, stan);
        }
        else {
            p->l = unosGrada(p->l, ime, stan);
        }
    }

    return p;
}

int printDrzave(CouPosition p) {
    while(p != NULL) {
        printf("\t%s\n", p->ime);
        printGradove(p->grad->d);
        p = p->next;
    }

    return EXIT_SUCCESS;
}

int printGradove(Position p) {
    if(p == NULL) {
        return 0;
    }

    printGradove(p->l);
    printf("\t\t%s\n", p->ime);
    printGradove(p->d);
    
    return EXIT_SUCCESS;
}

CouPosition traziDrzavu(CouPosition p, char* ime)
{
    while(p != NULL) {
        if(strcmp(p->ime, ime) == 0) {
            return p;
        }
        p = p->next;
    }

    return p;
}

int traziGrad(Position p, int broj)
{
    if(p == NULL) {
        return 0;
    }
    traziGrad(p->l, broj);
    if(p->stanovnici >= broj) {
        printf("\t%s %d\n", p->ime, p->stanovnici);
    }
    traziGrad(p->d, broj);

    return EXIT_SUCCESS;
}

int kljucZaDrzavu(char* imeDrzave)
{
    int kljuc = 0;
    int i = 0;

    for(i = 0; i < 5; i++)
        kljuc += (int)imeDrzave[i];

    return kljuc % N;
}

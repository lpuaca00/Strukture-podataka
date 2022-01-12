#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX_SIZE (128)
#define MAX_LINE (1024)

typedef struct _student {
	char ime[MAX_SIZE];
	char prezime[MAX_SIZE];
	double bodovi;
} student;

int ProcitajBrojRedakaIzDatoteke(char* );
student* AlocirajMemorijuIProcitajStudente(int , char* );
double PronalazenjeNajvecegBrBodova(int , student* );
void RacunanjeIIspisStudenata(int, double, student*);

int main()
{
	int n = 0, maxbodovi = 0;
	char ime[20] = {0};
	student *studenti = NULL;

	printf("Unesite ime datoteke: \n");
	scanf(" %s", &ime);

	n = ProcitajBrojRedakaIzDatoteke(ime);
	//printf("%d", n);

	studenti = AlocirajMemorijuIProcitajStudente(n, ime);

	maxbodovi = PronalazenjeNajvecegBrBodova(n, studenti);

	printf("IME\tPREZIME\tAPSOLUTNI\tRELATIVNI \n");
	RacunanjeIIspisStudenata(n, maxbodovi, studenti);

	return 0; //znaci da je uspjesno izvrseno
}

int ProcitajBrojRedakaIzDatoteke(char* ime)
{
	int brojac = 0;
	FILE* datoteka = NULL;
	char buffer[MAX_LINE] = {0};
	
	datoteka = fopen(ime, "r"); //otvaranje datoteke
	if(!datoteka) {
		printf("Greska (otvaranje datoteke)!");
		return -1;
	}

	//racunanje broja redaka
	while(!feof(datoteka)) {
		fgets(buffer, MAX_LINE, datoteka);
		brojac++;
	}
	
	fclose(datoteka);
	
	return brojac;
}

student* AlocirajMemorijuIProcitajStudente(int n, char* ime)
{
	int brojac = 0;
	FILE* datoteka = NULL;
	student* studenti = NULL;
	
	//alociranje memorije 
	studenti = (student*)malloc(n * sizeof(student));
	if(!studenti) {
		printf("Greska (alokacija memorije)!");
		return NULL;
	}

	datoteka = fopen(ime, "r"); //otvaranje datoteke
	if(!datoteka) {
		printf("Greska!");
		free(studenti);
		return NULL;
	}

	//ucitavanje podataka
	while(!feof(datoteka)) {
		fscanf(datoteka, " %s %s %lf", studenti[brojac].ime, studenti[brojac].prezime, &studenti[brojac].bodovi);
		brojac++;
	}
	
	fclose(datoteka);
	
	return studenti;
}

double PronalazenjeNajvecegBrBodova(int n, student* studenti)
{
	double najveci = 0;
	int i;

	for(i=0; i<n; i++) {
		if(studenti[i].bodovi > najveci)
			najveci = studenti[i].bodovi;
	}

	return najveci;
}

void RacunanjeIIspisStudenata(int n, double maxbodovi, student* studenti)
{
	int i;
	double relativni = 0.0;

	for(i=0; i<n; i++) {
		relativni = (studenti[i].bodovi/maxbodovi)*100;

		//ispis svega
		printf(" %s\t %s\t %lf\t%lf\n", studenti[i].ime, studenti[i].prezime, studenti[i].bodovi, relativni);
	}
	
}

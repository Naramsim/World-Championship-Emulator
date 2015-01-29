/*
*Autori : Alessandro Pezzè 158629, Norbert Paissan 157610
*Progetto : 2
*Anno : 2013/2014
*Corso : Informatica
*/

#ifndef LIB_H
#define LIB_H
#include <stdio.h>//FILE
short golA;
short golB;
short _skillA;
short _skillB;
short _girone;
short _squadraA;
short _squadraB;
int interval;//intervallo fra ogni azione
volatile int breakflag;//variabile che determina il numero di azioni rimanenti di una partita
FILE *f;//file su cui scrivere il file

void dupPrint(FILE *fp,char *fmt,  ...);//funzione che stampa su stdout e su file

int* PlayMatch();//funzione che esegue le partite
int comp(const void*, const void*);//funzione di supporto per la qsort di sistema
void dochildStuff(int[]);//funzione che identifica tutto il lavoro di un figlio

struct squadra {
	char nome_squadra[240];
	int numero_squadra; //ID squadra
	int skill; //potenza di una squadra
	int stop; //0-> gironi ; 1-> ottavi ; 2->quarti ; 3-> semifinali ; 4->finale ; 5->Campionessa
};

struct squadra* iscritte[32];//squadre iscritte al torneo

struct girone {
	struct  squadra* interne[4];//sempre nello stesso ordine
	int punteggio[4];
	int gol_fatti[4];
	int gol_subiti[4];
	int vinte[4];
	int perse[4];
	int pareggiate[4];
	struct squadra* attive[4];//sortabile
};

void sortGironi(struct girone* ,int ); //funzione che si occupa di sortare le squadre interne al girone in modo che non giochino mai contro la stessa squadra
void sortPunteggio(struct girone*); //funzione che sorta ogni gironi secondo punteggio e differenza reti
#endif
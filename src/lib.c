/*
*Autori : Alessandro Pezzè 158629, Norbert Paissan 157610
*Progetto : 2
*Anno : 2013/2014
*Corso : Informatica
*/

#include "lib.h"
#include <stdio.h>
#include <signal.h>
#include <time.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <stdarg.h>//va
#include <sys/time.h>

/*funzione che printa in stdout e su file*/
void dupPrint(FILE *fp,char *fmt,  ...) //fmt e' il format
{
    va_list ap;

    va_start(ap, fmt);
    vprintf(fmt, ap);
    va_end(ap);

    va_start(ap, fmt);
    vfprintf(fp, fmt, ap);
    fflush(fp);
    va_end(ap);
}

/*supporto a ChildStuff, genera i gol secondo delle regole*/
void handle(int sig) {
    int skillA=_skillA;
    int skillB=_skillB;
    
	short sum = skillA+skillB;
	
	srand(time(NULL)^ (getpid()<<16)); //lo srand deve essere in funzione del getpid(diverso per ogni figlio), altrimenti il seme è lo stesso per tutti
	short r = rand() % sum +1;//rand per la differenza di skill
	short rr = rand() % 100 +1;//rand per la probabilità di successo delle azioni
	if(r<skillA){
		if(rr>50){ 
		  golA++;
		}
	}else if(r>=skillA){
		if(rr>50){
		  golB++;
		}
	}
    --breakflag;
}


/*genera i gol della partita*/
int* playMatch() {

	golA=0;
	golB=0;
    breakflag=6;//3 azioni per tempo, una ogni 15 minuti
	
    struct itimerval it_val;//di sistema importata a time.h

    if (signal(SIGALRM, (void (*)(int)) handle) == SIG_ERR) { //fa partire l'handle
        perror("non sono riuscito a catchare SIGALRM");
        exit(1);
    }

    it_val.it_value.tv_sec =     interval/1000; 
    it_val.it_value.tv_usec =    (interval*1000) % 1000000;   
    it_val.it_interval = it_val.it_value;

    if (setitimer(ITIMER_REAL, &it_val, NULL) == -1) { //setitimer usato per timer
        perror("errore setitimer()");
        exit(1);
    }
    
    while (breakflag){ //partita
        pause();//catcha i SIG
        if(breakflag==3){
           dupPrint(f,"1° finito %15.15s contro %s \n",
                                     iscritte[_squadraA]->nome_squadra,
                                     iscritte[_squadraB]->nome_squadra);
            int recupero = rand() % 5 +1; //recupero
            int possibilitaAzione=0;
            if(recupero==5){
                short sum = _skillA+_skillB;
                short r = rand() % sum +1;
                if(r<_skillA){
                    golA++;
                }else if(r>=_skillA){
                    golB++;
                }
            }
            nanosleep((struct timespec[]){{0, recupero*1000000000}}, NULL); //1 secondo per minuto

        }
    }

    int recupero = rand() % 5 +1; //recupero
    int possibilitaAzione=0;
    if(recupero==5){
        short sum = _skillA+_skillB;
        short r = rand() % sum +1;
        if(r<_skillA){
            golA++;
        }else if(r>=_skillA){
            golB++;
        }
    }
    nanosleep((struct timespec[]){{0, recupero*1000000000}}, NULL); //1 secondo per minuto



    if(_girone==-1 && golA==golB){  //supplementari
        dupPrint(f,"2° finito %15.15s contro %s \n",
                                     iscritte[_squadraA]->nome_squadra,
                                     iscritte[_squadraB]->nome_squadra);

        breakflag=2; //15 minuti per tempo supplementare
        while (breakflag){ 
            pause();//catcha i SIG
            if(breakflag==1){
                dupPrint(f,"1° suppl finito %9.9s contro %s \n",
                                     iscritte[_squadraA]->nome_squadra,
                                     iscritte[_squadraB]->nome_squadra);
                int recupero = rand() % 3 +1; //recupero
                nanosleep((struct timespec[]){{0, recupero*1000000000}}, NULL); //1 secondo per minuto
            }
        }
        
    }

    recupero = rand() % 3 +1; //recupero
    possibilitaAzione=0;
    if(recupero==5){
        short sum = _skillA+_skillB;
        short r = rand() % sum +1;
        if(r<_skillA){
            golA++;
        }else if(r>=_skillA){
            golB++;
        }
    }
    nanosleep((struct timespec[]){{0, recupero*1000000000}}, NULL); //1 secondo per minuto


    
    if(_girone==-1 && golA==golB){//rigori
        dupPrint(f,"2° suppl finito %9.9s contro %s \n",
                                     iscritte[_squadraA]->nome_squadra,
                                     iscritte[_squadraB]->nome_squadra);
        dupPrint(f,"Rigori %18.18s contro %s \n",
                                     iscritte[_squadraA]->nome_squadra,
                                     iscritte[_squadraB]->nome_squadra);
        short n;
       
        short rA;
        short rB;

        for(n=0;n<5;n++){
            rA= rand()%100;
            rB= rand()%100; 
            if(rA<75){
                ++golA;
                dupPrint(f,"%25.24s segna\n", iscritte[_squadraA]->nome_squadra);
            }else{
                dupPrint(f,"%25.24s para!\n", iscritte[_squadraB]->nome_squadra);
            }
            if(rB<75){
                ++golB;
                dupPrint(f,"%26ssegna  %s\n", " ", iscritte[_squadraB]->nome_squadra);
            }else{
                dupPrint(f,"%26spara!  %s\n", " ", iscritte[_squadraA]->nome_squadra);
            }
            
        }
        
        while(golA==golB){
            rA= rand()%100;
            rB= rand()%100; 
            if(rA<75){
                ++golA;
                dupPrint(f,"%25.24s segna\n", iscritte[_squadraA]->nome_squadra);
            }else{
                dupPrint(f,"%25.24s para!\n", iscritte[_squadraB]->nome_squadra);
            }
            if(rB<75){
                ++golB;
                dupPrint(f,"%26ssegna  %s\n", " ", iscritte[_squadraB]->nome_squadra);
            }else{
                dupPrint(f,"%26spara!  %s\n", " ", iscritte[_squadraA]->nome_squadra);
            }
        }
    }
    
    int* ret=malloc(2);
    ret[0]=golA;
    ret[1]=golB;
    return ret;
    
}


/*comparazione per la qsort di sistema*/
int comp (const void * A, const void * B){ 
    int f = *((int*)A);
    int s = *((int*)B);
    if (f > s) return  1;
    if (f < s) return -1;
    return 0;
}


/* esegue la partita, prende i gol e li scrive nella pipe*/
void dochildStuff(int pfd[2]){
    close(pfd[0]);//chiude la pipe in lettura
    FILE *datiEntranti = fopen("data/dati.txt","r");
    int girone;
    int squadraA; //ID A
    int squardaB; //ID B 
    int skillA;
    int skillB;
    fscanf(datiEntranti, "%d %d %d %d %d", &girone,
                                        &squadraA,
                                        &squardaB,
                                        &skillA,
                                        &skillB);
    fclose(datiEntranti);
    _skillA=skillA;//_skill sono globali, mi servono a causa dei signal
    _skillB=skillB;
    _squadraA=squadraA;
    _squadraB=squardaB;
    _girone=girone;
                    //TODO mettere globali le squadre così posso dire che primi tempi sono finiti
    dupPrint(f,"In campo: %15.15s contro %s \n",
                                     iscritte[squadraA]->nome_squadra,
                                     iscritte[squardaB]->nome_squadra);
    
    int* gol=playMatch();
    
    /*processo di conversione da int* a char**/
    short gol1=gol[0]; //gol in int
    //dupPrint(f,"%d ",gol1);
    short gol2=gol[1];
    //dupPrint(f,"%d\n",gol2);
    /*creo la stringa da writare in pipe */
    char cgol1[32]; //stringhe in cui copiare gli int
    char cgol2[32];
    char csquadraA[32]; //stringhe in cui copiare le squadre
    char csquadraB[32];
    char cgirone[32];//stringa per il girone
    char str[165]; //stringa da writare
    /*conversione int in char* */
    sprintf(cgol1,"%d",gol1); 
    sprintf(cgol2,"%d",gol2);
    sprintf(csquadraA,"%d",squadraA);
    sprintf(csquadraB,"%d",squardaB);
    sprintf(cgirone,"%d",girone);
    /*concatenazione*/
    strcpy(str,cgirone);
    strcat(str,",");    
    strcat(str,csquadraA);
    strcat(str,",");
    strcat(str,csquadraB);
    strcat(str,",");
    strcat(str,cgol1);
    strcat(str,",");
    strcat(str,cgol2);
    strcat(str,",");
    
    write(pfd[1], str, strlen(str));//scrive nella pipe

    dupPrint(f,"Postpartita %13.13s contro %-25s  %1d a %1d\n", iscritte[squadraA]->nome_squadra
                ,iscritte[squardaB]->nome_squadra
                ,gol1
                ,gol2);
    free(gol);//dealloca gol
    exit(0);//fa uscire questo figlio
}


void sortGironi(struct girone* gironi,int modo){
    //modo=0 -> 0-1 2-3
    //modo=1 -> 0-2 1-3
    //modo=2 -> 0-3 1-2
    short i;
    if(modo==0){
        for(i=0;i<8;i++){
            gironi[i].attive[0]=gironi[i].interne[0];
            gironi[i].attive[1]=gironi[i].interne[1];
            gironi[i].attive[2]=gironi[i].interne[2];
            gironi[i].attive[3]=gironi[i].interne[3];
        }
    }else if(modo==1){
        for(i=0;i<8;i++){
            gironi[i].attive[0]=gironi[i].interne[0];
            gironi[i].attive[1]=gironi[i].interne[2];
            gironi[i].attive[2]=gironi[i].interne[1];
            gironi[i].attive[3]=gironi[i].interne[3];
        }
    }else if(modo==2){
        for(i=0;i<8;i++){
            gironi[i].attive[0]=gironi[i].interne[0];
            gironi[i].attive[1]=gironi[i].interne[3];
            gironi[i].attive[2]=gironi[i].interne[1];
            gironi[i].attive[3]=gironi[i].interne[2];
        }
    }
}



void sortPunteggio(struct girone* gironi) {
    short j,i,f;
    for(f=0;f<8;f++){//cicla su tutti ed 8 i gironi
        for(i=1;i<4;i++){
            for(j=0;j<4-i;j++){
                if(gironi[f].punteggio[j] > gironi[f].punteggio[j+1]){
                    int temp = gironi[f].punteggio[j];
                    gironi[f].punteggio[j] =gironi[f].punteggio[j+1];
                    gironi[f].punteggio[j+1] = temp;

                    temp = gironi[f].gol_fatti[j];
                    gironi[f].gol_fatti[j] =gironi[f].gol_fatti[j+1];
                    gironi[f].gol_fatti[j+1] = temp;

                    temp = gironi[f].gol_subiti[j];
                    gironi[f].gol_subiti[j] =gironi[f].gol_subiti[j+1];
                    gironi[f].gol_subiti[j+1] = temp;

                    temp = gironi[f].vinte[j];
                    gironi[f].vinte[j] =gironi[f].vinte[j+1];
                    gironi[f].vinte[j+1] = temp;

                    temp = gironi[f].pareggiate[j];
                    gironi[f].pareggiate[j] =gironi[f].pareggiate[j+1];
                    gironi[f].pareggiate[j+1] = temp;

                    temp = gironi[f].perse[j];
                    gironi[f].perse[j] =gironi[f].perse[j+1];
                    gironi[f].perse[j+1] = temp;

                    struct squadra* temp_= malloc(sizeof(*temp_)); //per scambiare l'array di struct squadre interne devo istanziarne uno uguale ma temporaneo
                    temp_ = gironi[f].interne[j];
                    gironi[f].interne[j] =gironi[f].interne[j+1];
                    gironi[f].interne[j+1] = temp_;

                }else if(gironi[f].punteggio[j] == gironi[f].punteggio[j+1]){ //caso in cui i punti siano uguali ma non la differenza reti
                    
                    if( gironi[f].gol_fatti[j]-gironi[f].gol_subiti[j] > gironi[f].gol_fatti[j+1]-gironi[f].gol_subiti[j+1]){
                        int temp = gironi[f].punteggio[j];
                        gironi[f].punteggio[j] =gironi[f].punteggio[j+1];
                        gironi[f].punteggio[j+1] = temp;

                        temp = gironi[f].gol_fatti[j];
                        gironi[f].gol_fatti[j] =gironi[f].gol_fatti[j+1];
                        gironi[f].gol_fatti[j+1] = temp;

                        temp = gironi[f].gol_subiti[j];
                        gironi[f].gol_subiti[j] =gironi[f].gol_subiti[j+1];
                        gironi[f].gol_subiti[j+1] = temp;

                        temp = gironi[f].vinte[j];
                        gironi[f].vinte[j] =gironi[f].vinte[j+1];
                        gironi[f].vinte[j+1] = temp;

                        temp = gironi[f].pareggiate[j];
                        gironi[f].pareggiate[j] =gironi[f].pareggiate[j+1];
                        gironi[f].pareggiate[j+1] = temp;

                        temp = gironi[f].perse[j];
                        gironi[f].perse[j] =gironi[f].perse[j+1];
                        gironi[f].perse[j+1] = temp;

                        struct squadra* temp_= malloc(sizeof(*temp_));
                        temp_ = gironi[f].interne[j];
                        gironi[f].interne[j] =gironi[f].interne[j+1];
                        gironi[f].interne[j+1] = temp_;
                    }
                }
            }
        }
    }
}
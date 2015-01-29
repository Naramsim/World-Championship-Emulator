/*
*Autori : Alessandro Pezzè 158629, Norbert Paissan 157610
*Progetto : 2
*Anno : 2013/2014
*Corso : Informatica
*/

#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <errno.h>
#include <string.h>
#include <time.h>
#include <ctype.h>
#include <unistd.h>
#include <stddef.h>//size_t
#include "lib.h"



int main(int argc, char*argv[]){
	interval=1660;//default, fra ogni azione passa 1,6s, un tempo ha 3 azioni, un tempo dura 5s
	int opt = 0;
	char *inputFile=NULL;//crea a NULL il nome file da leggere per le squadre
	char *logfile=NULL;//crea a NULL il nome del file dove salvare i log
	int realta=0; //se 0, i gironi venono sortati casualmente, se 1 no.
	while((opt = getopt(argc, argv, "t:i:vl:")) != -1){//opzioni t,i,l con paramentri 
		switch(opt){
			case 't':{
				interval=atoi(optarg);//ASCII to int
				if(interval<=0){
					interval=1;
				}
				interval=interval*1000; //millisecondi
				//dupPrint(f,"\nOgni tempo durera':%d millisecondi\n", interval); 
				interval=interval/3;//il tempo interno al programma si scandisce in azioni, 3 azioni per tempo		
				break;
			}
			case 'i':{
				inputFile=optarg;//salva il nome dell'input
				break;
			}
			case 'v':{
				realta=1;//se si vuol giocare con i veri gironi
				break;
			}
			case 'l':{
				logfile=optarg;//salva il nome del log
				break;
			}
		}
	}
	if(logfile==NULL){
		f=fopen("log.txt","w");//nome di default
	}else{
		f=fopen(logfile,"w");
	}

	dupPrint(f,"Benvenuti, oggi qui a Rio de Janerio fa caldo\nma il sottoscritto Alessandro Pezze' \nassieme al suo fidato Norbert Paissan vi faranno sudare freddo oggi,\nvi racconteremo in esclusiva 2 mesi prima (anche di SKY) la strada per la coppa del mondo!");
	//sleep(3);
	
	/*preleva le squadre*/

	FILE *fp;//puntatore al file da leggere
	short q=0;
	short posval=0;
	
	char *subDir="assets/";

	if(inputFile==NULL){ //se non viene dato l'input uso il mio file
		
		/*genero indici casuali delle squadre*/
		int val[32]; //indici delle squadre da prelevare
		short j;
		srand(time(NULL));
		for(j=0;j<32;j++){
				val[j]=rand()%245 +1; 
		}

		/*sort dell'array*/
		qsort (val, sizeof(val)/sizeof(*val), sizeof(*val), comp);
		short k;
		for (k = 0 ; k < 32 ; k++){
			if(val[k]==val[k+1]){//se sono stati generati due numeri uguali, prendilo ma aggiungigli 1, così al torneo non potranno partecipare due squadre uguali
					++val[k+1]; //non si rischia di sforare l'array, esiste infatti una squadra in posizione 246 delle 245 selezionabili. essa è: RAPPRESENTANZA UNITN
			}
		}
		
		if((fp = fopen("assets/squadre.dat", "r"))==NULL) { //apro in read
	        dupPrint(f,"Cannot open file.\n");
	        exit(1);
	    }

		while(!feof(fp)) {//finche trovi da leggere
	        char s[100];
	        int nn;
	        fscanf(fp,"%s %d",s,&(nn)); //scanna il file, prima prende la stringa, poi l'intero corrispondente alla skill
	        if(q==val[posval]){//quando arrivo agli indici prestabiliti, estraggo
				struct squadra* temp= malloc(sizeof(*temp));
				strcpy(temp->nome_squadra,s); 	//assegno il nome
				temp->skill=nn;					//assegno la skilla
				temp->stop=0;					//assegno che è arrivata al massimo alla fase a gironi
				iscritte[posval]=temp;
				posval++;
	        }
			q++;
		}

	}else{
		char path[100];
		strcpy(path,subDir);
		strcat(path,inputFile);
		//dupPrint(f,"%s\n", path);
		if((fp = fopen(path, "r"))==NULL) { //apro in read
	        dupPrint(f,"Cannot open file.\n");
	        exit(1);
	    }

		while(!feof(fp)) {//finche trovi da leggere
	        char s[100];
	        int nn;
	        fscanf(fp,"%s %d",s,&(nn)); //scanna il file, prima prende la stringa, poi l'intero corrispondente alla skill
			struct squadra* temp= malloc(sizeof(*temp));
			strcpy(temp->nome_squadra,s); 	//assegno il nome
			temp->skill=nn;					//assegno la skilla
			temp->stop=0;					//assegno che è arrivata al massimo alla fase a gironi
			iscritte[posval]=temp;
			posval++;
			printf("%s %d\n", s,nn);
        }
	}

    
	fclose(fp);

	/*shuffle squadre iscritte*/
	int sh;
	if(realta==0){ //se realta==1 lascia i gironi veri nel caso di mondiale2014.dat
		for(sh=0;sh<32;sh++){
			int random= rand()%32; 
			struct squadra* temp= malloc(sizeof(*temp)); //serve una struct temporanea
			temp= iscritte[random];
			iscritte[random]=iscritte[sh];
			iscritte[sh]=temp;
		}
	}
	for(sh=0;sh<32;sh++){//inizializza ID squadre
		iscritte[sh]->numero_squadra=sh;
	}
	
	dupPrint(f,"\n");
	
	/*creazione gironi*/
	struct girone* gironi =(struct girone*) malloc(8*sizeof(struct girone)); //alloco per 8 gironi //con calloc va in segfaul a volte
	int c;
	for(c=0;c<4;c++){
		gironi[0].interne[c%4]= iscritte[c];//inserisco tutte le squadre nei gironi
	}
	for(c=4;c<8;c++){
		gironi[1].interne[c%4]= iscritte[c];
	}
	for(c=8;c<12;c++){
		gironi[2].interne[c%4]= iscritte[c];
	}
	for(c=12;c<16;c++){
		gironi[3].interne[c%4]= iscritte[c];
	}
	for(c=16;c<20;c++){
		gironi[4].interne[c%4]= iscritte[c];
	}
	for(c=20;c<24;c++){
		gironi[5].interne[c%4]= iscritte[c];
	}
	for(c=24;c<28;c++){
		gironi[6].interne[c%4]= iscritte[c];
	}
	for(c=28;c<32;c++){
		gironi[7].interne[c%4]= iscritte[c];
	}
	
	int z;
	for(c=0;c<8;c++){
		dupPrint(f,"Girone %d \n",c+1);
		for(z=0;z<4;z++){
			dupPrint(f,"Con skill %2d ->",gironi[c].interne[z]->skill);
			//dupPrint(f," e con ID: %d",gironi[c].interne[z]->numero_squadra);
			dupPrint(f," %4s\n",gironi[c].interne[z]->nome_squadra);
		}
		dupPrint(f,"\n");
	}

	printf("Premi INVIO per iniziare il campionato");
	while( getchar() != '\n' );

	/*fase a gironi*/
	int h=0;
	if(1){
		for(h=0;h<3;h++){	//ogni squadra gioca 3 partite 
							//le partite saranno:
							// 1-2 e 3-4
							// 1-3 e 2-4
							// 1-4 e 2-3

			/* creazione della pipe*/
			int nread; //numero byte letti dalla pipe 
			int pfd[2];//file descriptor
			char s[1024];//dove mettere i dati letti
			pid_t pids[16];//ID dei figli
			short n = 16;//numero partite
			
			sleep(1);
			if(pipe(pfd) == -1){//pipe per il ritono dei risultati
				perror("pipe");
				return 0;
			}

			/* crea i figli */
			short i;
			short ngironi=0;
			sortGironi(gironi,h);
			for (i = 0; i < 32; i++) {
				nanosleep((struct timespec[]){{0, 100000000}}, NULL); //0.2 secondi
				
				if ((pids[i] = fork()) < 0) {
					perror("fork");
					abort();
				} else if (pids[i] == 0) {//qui entrano i figli
					FILE *daitUscenti=fopen("data/dati.txt","w");											//passo tante cose per semplificare i calcoli al padre che li processerà
					fprintf(daitUscenti,"%d %d %d %d %d",ngironi,										//Girone appartenenza
													gironi[ngironi].attive[(i%4)]->numero_squadra,		//ID A
													gironi[ngironi].attive[(i+1)%4]->numero_squadra,	//ID B
													gironi[ngironi].attive[(i%4)]->skill,				//Skill A
													gironi[ngironi].attive[(i+1)%4]->skill ); 			//Skill B
					fclose(daitUscenti);
					dochildStuff(pfd);// funzione figli, fa la partita
				}
				i=i+1;
				if((i%4)==3){
					++ngironi;//aumenta i gironi ogni 4 partite

				}
			}

			/* padre */
			int status;
			pid_t pid;
			while (n > 0) {//aspetta che i figli finiscano
					pid = wait(&status);
			  --n;
			}
			
			close(pfd[1]);//chiude in scrittura
			nread=read(pfd[0], s, sizeof(s));//legge cosa hanno scritto i figli

			int tabellino[80]; //16partite*5  //girone
												//sqA
												//sqB
												//golA
												//golB
			n=0;//riuso
			int nn=0;
			char *ds=strdup(s);//alloca e duplica
		 	dupPrint(f,"\n");
			tabellino[n]= atoi( strtok(ds, ",") );//atoi-> ASCII to Int

			while(n<79) {//riempie tabellino
				tabellino[++n]=atoi( strtok(NULL, ",") );//strtok, tokenizza

			}

		 	short gir; 
			short pos1;
			short pos2;
			short golA;
			short golB;
			while(nn<=79){ //scrive i risultati del tabellino
				
				gir = tabellino[nn];//dupPrint(f,"gir:%d ", gir); // 0
				nn++;
				//dupPrint(f,"IDa:%d ", tabellino[nn]);
				pos1= tabellino[nn]%4;//dupPrint(f,"pos1:%d ", pos1); // 1
				nn++;
				//dupPrint(f,"IDb:%d ", tabellino[nn]);
				pos2= tabellino[nn]%4;//dupPrint(f,"pos2:%d ", pos2); // 2
				nn++;
				golA= tabellino[nn];//dupPrint(f,"golA:%d ", golA); // 3
				nn++;
				golB= tabellino[nn];//dupPrint(f,"golB:%d\n", golB); // 4
				nn++;

				gironi[gir].gol_fatti[pos1]+=golA;
				gironi[gir].gol_fatti[pos2]+=golB;
				gironi[gir].gol_subiti[pos1]+=golB;
				gironi[gir].gol_subiti[pos2]+=golA;
				if(golA>golB){
					gironi[gir].punteggio[pos1]+=3;
					gironi[gir].vinte[pos1]++;
					gironi[gir].perse[pos2]++;
				}else if(golA==golB){
					gironi[gir].punteggio[pos1]+=1;
					gironi[gir].punteggio[pos2]+=1;
					gironi[gir].pareggiate[pos1]++;
					gironi[gir].pareggiate[pos2]++;
				}else if(golA<golB){
					gironi[gir].punteggio[pos2]+=3;
					gironi[gir].vinte[pos2]++;
					gironi[gir].perse[pos1]++;
				}
			}
			free(ds);//libera
			dupPrint(f,"\n");


			/*estrae i dati finali dai gironi*/
			for(c=0;c<8;c++){
				dupPrint(f,"Girone %d \n",c+1);
				for(z=0;z<4;z++){
					dupPrint(f,"%20.19s | punti: %2d, gol: %2d, subiti: %2d |v:%d  p:%d  p:%d\n",
																gironi[c].interne[z]->nome_squadra,
																gironi[c].punteggio[z],
																gironi[c].gol_fatti[z],
																gironi[c].gol_subiti[z],
																gironi[c].vinte[z],
																gironi[c].pareggiate[z],
																gironi[c].perse[z]
																);
				}
				dupPrint(f,"\n");
			}
			printf("Premi INVIO per continuare");
			while( getchar() != '\n' );
		}
	}
	

	struct squadra* primeGironi[8]; //le prime qulificate di ogni girone
	struct squadra* secondeGironi[8]; //le seconde classificate di ogni girone
	int n;
	//sort dei gironi, sort crescente basato solo su punteggio e gol_fatti
	sortPunteggio(gironi); //TODO sort per gol_fatti
	for(n=0;n<8;n++){
		gironi[n].interne[3]->stop=1;
		gironi[n].interne[2]->stop=1;
		primeGironi[n]=gironi[n].interne[3];
		secondeGironi[n]=gironi[n].interne[2];
	}

	dupPrint(f,"Le squadre che accedono alla fase finale sono:\n");
	for(n=0;n<8;n++){
		dupPrint(f,"prima:%25s \tseconda:%s\n", primeGironi[n]->nome_squadra,
										secondeGironi[n]->nome_squadra);
	}


	/*ottavi*/

	struct squadra* quarti[8];//otto squadre ai quarti, qui verranno inserite le squadre vincenti agli ottavi

	if(1){ //le variabili restano solo nell'if, poi vengono distrutte
		int nread; //numero byte letti dalla pipe 
		int pfd[2];//file descriptor
		char s[1024];//dove mettere i dati letti
		pid_t pids[16];//ID dei figli
		n = 8;//numero partite, otto partite agli ottavi
		short i;
		
		sleep(1);
		if(pipe(pfd) == -1){//pipe per il ritono dei risultati
			perror("pipe");
			return 0;
		}
		
		//shuffle
		for(sh=0;sh<8;sh++){
			int random= rand()%8; 
			struct squadra* temp= malloc(sizeof(*temp));
			temp= primeGironi[random];
			primeGironi[random]=primeGironi[sh];
			primeGironi[sh]=temp;
		}
		for(sh=0;sh<8;sh++){
			int random= rand()%8; 
			struct squadra* temp= malloc(sizeof(*temp));
			temp= secondeGironi[random];
			secondeGironi[random]=secondeGironi[sh];
			secondeGironi[sh]=temp;
		}
		
		dupPrint(f,"\nEcco gli accoppiamenti degli ottavi:\n");
		for(n=0;n<8;n++){
			dupPrint(f,"%25s contro: %s\n", primeGironi[n]->nome_squadra,
									 secondeGironi[n]->nome_squadra);
		}
		dupPrint(f,"\n");
		
		for (i = 0; i < 8; i++) {
			nanosleep((struct timespec[]){{0, 100000000}}, NULL); //0.1 secondi fra una partita e la successiva
			
			srand(time(NULL));//genera il seme random
			
			if ((pids[i] = fork()) < 0) {
				perror("fork");
				abort();
			} else if (pids[i] == 0) {//qui entrano i figli
				FILE *daitUscenti=fopen("data/dati.txt","w");//passo tante cose per semplificare i calcoli al padre che li processerà
				fprintf(daitUscenti,"%d %d %d %d %d", -1,							//-1, non ci sono gironi			
												primeGironi[i]->numero_squadra,		//ID A
												secondeGironi[i]->numero_squadra,	//ID B
												primeGironi[i]->skill,				//Skill A
												secondeGironi[i]->skill ); 			//Skill B
				fclose(daitUscenti);
				dochildStuff(pfd);
			}
		}

		/* padre */
		int status;
		pid_t pid;
		while (n > 0) {
			pid = wait(&status);//aspetta che i figli finiscano
		  --n;
		}
		
		close(pfd[1]);//chiude in scrittura
		nread=read(pfd[0], s, sizeof(s));//legge cosa hanno scritto i figli
		int tabellino[40]; //8partite*5 	//girone
											//sqA
											//sqB
											//golA
											//golB
		n=0;
		int nn=0;
		char *ds=strdup(s);//alloca e duplica
	 	dupPrint(f,"\n");
		tabellino[n]= atoi( strtok(ds, ",") );//atoi-> ASCII to Int

		while(n<39) {//riempie tabellino
			tabellino[++n]=atoi( strtok(NULL, ",") );//strtok, tokenizza
		}

	 	short gir; 
		short pos1;
		short pos2;
		short golA;
		short golB;
		//struct squadra* quarti[4];
		
		while(nn<=39){ 
			gir = tabellino[nn];
			nn++;
			pos1= tabellino[nn];
			nn++;
			pos2= tabellino[nn];
			nn++;
			golA= tabellino[nn];
			nn++;
			golB= tabellino[nn];
			nn++;
			
			

			if(golA>golB){
				for(n=0;n<8;n++){
					if(pos1==primeGironi[n]->numero_squadra){
						primeGironi[n]->stop=2;
					}
				}
			}else if(golA==golB){
				dupPrint(f,"Pareggio? qualcosa è andato storto..\n");
			}else if(golA<golB){
				for(n=0;n<8;n++){
					if(pos2==secondeGironi[n]->numero_squadra){
						secondeGironi[n]->stop=2;
					}
				}
			}
			;
		}
		free(ds);//libera


		
		int quartiSupporto=0;
		for(n=0;n<8;n++){
			if(secondeGironi[n]->stop==2){
				quarti[quartiSupporto]=secondeGironi[n];
				++quartiSupporto;
			}
		}
		for(n=0;n<8;n++){
			if(primeGironi[n]->stop==2){
				quarti[quartiSupporto]=primeGironi[n];		
				++quartiSupporto;
			}
		}
	}	



	/*quarti*/
	dupPrint(f,"Le squadre che accedono ai quarti sono:\n");
	for(n=0;n<8;n++){
		dupPrint(f,"%25s\n", quarti[n]->nome_squadra);
	}

	printf("Premi INVIO per continuare");
	while( getchar() != '\n' );

	struct squadra* semiFinali[4];//quattro squadre alle semifinali, qui verranno inserite le squadre vincenti dei quarti
	if(1){
		int nread; //numero byte letti dalla pipe 
		int pfd[2];//file descriptor
		char s[1024];//dove mettere i dati letti
		pid_t pids[8];//ID dei figli
		n = 4;//numero partite
		short i;
		
		sleep(1);
		if(pipe(pfd) == -1){//pipe per il ritono dei risultati
			perror("pipe");
			return 0;
		}
		
		//shuffle
		for(sh=0;sh<8;sh++){
			int random= rand()%8; 
			struct squadra* temp= malloc(sizeof(*temp));
			temp= quarti[random];
			quarti[random]=quarti[sh];
			quarti[sh]=temp;
		}
		
		dupPrint(f,"\nEcco gli accoppiamenti dei quarti:\n");
		for(n=0;n<8;n++){
			dupPrint(f,"%25s contro: ", quarti[n]->nome_squadra);
			n++;
			dupPrint(f,"%s\n", quarti[n]->nome_squadra);
		}
		dupPrint(f,"\n");
		
		for (i = 0; i < 8; i++) {
			nanosleep((struct timespec[]){{0, 100000000}}, NULL); //0.1 secondi
			
			srand(time(NULL));
			
			if ((pids[i] = fork()) < 0) {
				perror("fork");
				abort();
			} else if (pids[i] == 0) {//qui entrano i figli
				FILE *daitUscenti=fopen("data/dati.txt","w");//passo tante cose per semplificare i calcoli al padre che li processerà
				fprintf(daitUscenti,"%d %d %d %d %d", -1,						//non ci sono gironi di appartenenza				
												quarti[i]->numero_squadra,		//ID A
												quarti[i+1]->numero_squadra,	//ID B
												quarti[i]->skill,				//Skill A
												quarti[i+1]->skill ); 			//Skill B
				
				fclose(daitUscenti);
				dochildStuff(pfd);
			}
			i=i+1;
		}

		/* padre */ 
		int status;
		pid_t pid;
		while (n > 0) {
			pid = wait(&status);//aspetta che i figli finiscano
		  --n;
		}
		
		close(pfd[1]);//chiude in scrittura
		nread=read(pfd[0], s, sizeof(s));//legge cosa hanno scritto i figli
		int tabellino[20]; //4partite*5 	//girone
											//sqA
											//sqB
											//golA
											//golB
		n=0;
		int nn=0;
		char *ds=strdup(s);//alloca e duplica
	 	dupPrint(f,"\n");
		tabellino[n]= atoi( strtok(ds, ",") );//atoi-> ASCII to Int

		while(n<19) {//riempie tabellino
			tabellino[++n]=atoi( strtok(NULL, ",") );//strtok, tokenizza
		}

	 	short gir; 
		short pos1;
		short pos2;
		short golA;
		short golB;
		
		while(nn<=19){ 
			gir = tabellino[nn];
			nn++;
			pos1= tabellino[nn];
			nn++;
			pos2= tabellino[nn];
			nn++;
			golA= tabellino[nn];
			nn++;
			golB= tabellino[nn];
			nn++;

			
			if(golA>golB){
				for(n=0;n<8;n++){
					if(pos1==quarti[n]->numero_squadra){
						quarti[n]->stop=3;
					}
				}
			}else if(golA==golB){
				dupPrint(f,"Pareggio? Si consiglia di aumentare la durata delle partite\n");
			}else if(golA<golB){
				for(n=0;n<8;n++){
					if(pos2==quarti[n]->numero_squadra){
						quarti[n]->stop=3;
					}
				}
			}
		}
		free(ds);//libera

		int semiSupporto=0;//semifinaliSupporto;
		for(n=0;n<8;n++){
			if(quarti[n]->stop==3){
				semiFinali[semiSupporto]=quarti[n];
				++semiSupporto;
			}
		}
	}	

	/*Semifinali*/
	dupPrint(f,"Le squadre che accedono alle semifinali sono:\n");
	for(n=0;n<4;n++){
		dupPrint(f,"%25s\n", semiFinali[n]->nome_squadra);
	}

	printf("Premi INVIO per continuare");
	while( getchar() != '\n' );

	struct squadra* finaliste[2];//le due finaliste; in questo array verranno inserite della semifinali le due aspiranti campionesse

	if(1){
		int nread; //numero byte letti dalla pipe 
		int pfd[2];//file descriptor
		char s[1024];//dove mettere i dati letti
		pid_t pids[4];//ID dei figli
		n = 2;//numero partite
		short i;
		
		sleep(1);
		if(pipe(pfd) == -1){//pipe per il ritono dei risultati
			perror("pipe");
			return 0;
		}
		
		//shuffle
		for(sh=0;sh<4;sh++){
			int random= rand()%4; 
			struct squadra* temp= malloc(sizeof(*temp));
			temp= semiFinali[random];
			semiFinali[random]=semiFinali[sh];
			semiFinali[sh]=temp;
		}
		
		dupPrint(f,"\nEcco gli accoppiamenti delle semifinali:\n");
		for(n=0;n<4;n++){
			dupPrint(f,"%25s contro:", semiFinali[n]->nome_squadra);
			n++;
			dupPrint(f,"%s\n", semiFinali[n]->nome_squadra);
		}
		dupPrint(f,"\n");
		
		for (i = 0; i < 4; i++) {
			nanosleep((struct timespec[]){{0, 100000000}}, NULL); //0.1 secondi
			
			srand(time(NULL));
			
			if ((pids[i] = fork()) < 0) {
				perror("fork");
				abort();
			} else if (pids[i] == 0) {//qui entrano i figli
				FILE *daitUscenti=fopen("data/dati.txt","w");//passo tante cose per semplificare i calcoli al padre che li processerà
				fprintf(daitUscenti,"%d %d %d %d %d", -1,						//non ci sono gironi di appartenenza				
												semiFinali[i]->numero_squadra,		//ID A
												semiFinali[i+1]->numero_squadra,	//ID B
												semiFinali[i]->skill,				//Skill A
												semiFinali[i+1]->skill ); 			//Skill B
				
				fclose(daitUscenti);
				dochildStuff(pfd);
			}
			i=i+1;
		}

		/* padre */ 
		int status;
		pid_t pid;
		while (n > 0) {
			pid = wait(&status);//aspetta che i figli finiscano
		  --n;
		}
		
		close(pfd[1]);//chiude in scrittura
		nread=read(pfd[0], s, sizeof(s));//legge cosa hanno scritto i figli
		int tabellino[10]; //2partite*5 	//girone
											//sqA
											//sqB
											//golA
											//golB
		n=0;
		int nn=0;
		char *ds=strdup(s);//alloca e duplica
	 	dupPrint(f,"\n");
		tabellino[n]= atoi( strtok(ds, ",") );//atoi-> ASCII to Int

		while(n<9) {//riempie tabellino
			tabellino[++n]=atoi( strtok(NULL, ",") );//strtok, tokenizza
		}

	 	short gir; 
		short pos1;
		short pos2;
		short golA;
		short golB;
		
		while(nn<=9){ 
			gir = tabellino[nn];
			nn++;
			pos1= tabellino[nn];
			nn++;
			pos2= tabellino[nn];
			nn++;
			golA= tabellino[nn];
			nn++;
			golB= tabellino[nn];
			nn++;

			

			if(golA>golB){
				for(n=0;n<4;n++){
					if(pos1==semiFinali[n]->numero_squadra){
						semiFinali[n]->stop=4;
					}
				}
			}else if(golA==golB){
				dupPrint(f,"Pareggio? Si consiglia di aumentare la durata delle partite\n");
			}else if(golA<golB){
				for(n=0;n<4;n++){
					if(pos2==semiFinali[n]->numero_squadra){
						semiFinali[n]->stop=4;
					}
				}
			}
		}
		free(ds);//libera

		int finaleSupporto=0;//semifinaliSupporto;
		for(n=0;n<4;n++){
			if(semiFinali[n]->stop==4){
				finaliste[finaleSupporto]=semiFinali[n];
				++finaleSupporto;
			}
		}
	}

	printf("Premi INVIO per continuare");
	while( getchar() != '\n' );

	/*Finale*/
	dupPrint(f,"Le squadre che accedono alla finale sono:\n");
	for(n=0;n<2;n++){
		dupPrint(f,"%25s\n", finaliste[n]->nome_squadra);
	}

	if(1){
		int nread; //numero byte letti dalla pipe 
		int pfd[2];//file descriptor
		char s[1024];//dove mettere i dati letti
		pid_t pids[2];//ID dei figli
		n = 1;//numero partite
		short i=0;
		
		sleep(1);
		if(pipe(pfd) == -1){//pipe per il ritono dei risultati
			perror("pipe");
			return 0;
		}


		int nF=0;
		dupPrint(f,"Chi diventerà campione del mondo? \n");
		dupPrint(f,"%25s o ", finaliste[nF]->nome_squadra);
		nF++;
		dupPrint(f,"%s ?\n", finaliste[nF]->nome_squadra);
		
		
		
		srand(time(NULL));
		
		if ((pids[i] = fork()) < 0) {
			perror("fork");
			abort();
		} else if (pids[i] == 0) {//qui entrano i figli
			FILE *daitUscenti=fopen("data/dati.txt","w");//passo tante cose per semplificare i calcoli al padre che li processerà
			fprintf(daitUscenti,"%d %d %d %d %d", -1,							//non ci sono gironi di appartenenza				
											finaliste[i]->numero_squadra,		//ID A
											finaliste[i+1]->numero_squadra,		//ID B
											finaliste[i]->skill,				//Skill A
											finaliste[i+1]->skill ); 			//Skill B
			
			fclose(daitUscenti);
			dochildStuff(pfd);
		}
		
		

		/* padre */ 
		int status;
		pid_t pid;
		while (n > 0) {
			pid = wait(&status);//aspetta che i figli finiscano
		  --n;
		}
		
		close(pfd[1]);//chiude in scrittura
		nread=read(pfd[0], s, sizeof(s));//legge cosa hanno scritto i figli
		int tabellino[5]; //1partita*5 		//girone
											//sqA
											//sqB
											//golA
											//golB
		n=0;
		int nn=0;
		char *ds=strdup(s);//alloca e duplica
	 	dupPrint(f,"\n");
		tabellino[n]= atoi( strtok(ds, ",") );//atoi-> ASCII to Int

		while(n<4) {//riempie tabellino
			tabellino[++n]=atoi( strtok(NULL, ",") );//strtok, tokenizza
		}

	 	short gir; 
		short pos1;
		short pos2;
		short golA;
		short golB;
		
		gir = tabellino[nn];
		nn++;
		pos1= tabellino[nn];
		nn++;
		pos2= tabellino[nn];
		nn++;
		golA= tabellino[nn];
		nn++;
		golB= tabellino[nn];
		nn++;

		if(golA>golB){
			for(n=0;n<2;n++){
				if(pos1==finaliste[n]->numero_squadra){
					finaliste[n]->stop=5;
					dupPrint(f,"Campione! Campione del mondo! Si %s e' Campione del mondo!\n", finaliste[n]->nome_squadra);
				}
			}
		}else if(golA==golB){
			dupPrint(f,"Pareggio? Si consiglia di aumentare la durata delle partite\n");
		}else if(golA<golB){
			for(n=0;n<2;n++){
				if(pos2==finaliste[n]->numero_squadra){
					finaliste[n]->stop=5;
					dupPrint(f,"Incredibile! contro ogni pronostico e' %s che vince la coppa!\n", finaliste[n]->nome_squadra );
				}
			}
		}
		free(ds);//libera
	}

	fclose(f);
	return 0;
}


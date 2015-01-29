#
#Autori : Alessandro Pezzè 158629, Norbert Paissan 157610
#Progetto : 2
#Anno : 2013/2014
#Corso : Informatica
#

CC=gcc 
#compilatore che si vuole usare

all: 
	@echo "\nCampionato del mondo 2014 Brazil"
	@echo "make bin-> genera binari"
	@echo "make asset -> genera file di test"
	@echo "make test -> genera file di test e li testa"
	@echo "make clean ->pulisce gli eseguibili e i supporti, non i file di testo delle squadre, così si possono riprovare"
	@echo "per eseguire il programma dare da linea di comando:"
	@echo "./bin/calcio.out -v -i[nomeFileInput] -l[nomeFileDiLog] -t[durataTempo]"
	@echo "-v non mescola i gironi, da accoppiare con -i modiali2014.dat così si eseguira' l'eseguibile con i veri gironi"
	@echo "-i[] nome dell'input da passare all'eseguibile, "
	@echo "-l[] nome con cui si vuole che il log venga salvato"
	@echo "-t[] durata in secondi di un tempo di 45 minuti"
	@echo "tutte le opzioni possono essere scelte, nessuna e' obbligatoria"

bin: bindir calcio.o lib.o res
	$(CC) bin/calcio.o bin/lib.o -o bin/calcio.out 
#compila i file file oggetto per fare gli eseguibili

bindir:
	mkdir -p bin 
#mkdir crea le cartelle
	mkdir -p data
#-p previene errore se cartella esiste
calcio.o:
	$(CC) -c src/calcio.c -o bin/calcio.o 
#compila la main

lib.o:
	$(CC) -c src/lib.c -o bin/lib.o 
#compila le funzioni

res: 
	$(CC) src/squadre.c -o bin/squadre.out 
#compila il programma che genera le squadre e le skill

asset:
#asset al posto di assets, assets e' di sistema
	mkdir -p assets
#crea cartella assets
	$(CC) src/squadre.c -o bin/squadre.out 
	./bin/squadre.out

test: bin asset
#esegue le label indicate sopra 
#poi esegue senza opzioni la main
	./bin/calcio.out 

clean:
	rm -rf bin/*o bin/*out *txt data/*txt
#rimuove ricorsivamenre tutti i .o .out .txt

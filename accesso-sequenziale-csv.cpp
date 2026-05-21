#include <iostream>
#include <string>
//lettura/scrittura
#include <fstream>
//maiuscolo
#include <algorithm>
#include <cctype>
//rename/remove
#include <cstdio>
using namespace std;

bool Aggiungi(string classe, string descrizione, string numero, string subalterno, string cap, string istat, double longit, double lat){
	ifstream leggi("Comune_Bergamo_-_Numerazione_civica.csv");
	//aggiungo in coda
	ofstream scrivi("file2.csv", ios::app);
	string riga;
	if(!scrivi.is_open()){
		return false;
	}
	//copio tutte le righe
	if(leggi.is_open()){
		while(getline(leggi, riga)){
			scrivi<<riga<<"\n";
		}
	}
	//aggiungo l'elemento
	scrivi<<classe<<","<<descrizione<<","<<numero<<","<<subalterno<<","<<cap<<","<<istat<<","<<longit<<","<<lat<<",\"("<<longit<<","<<lat<<")\""<<"\n";
	//chiudo
	leggi.close();
	scrivi.close();
	return true;
}

int Cerca(string descrizione, string numero){
	ifstream leggi("Comune_Bergamo_-_Numerazione_civica.csv");
	string riga, classe, desc, num, resto;
	//salto le prima riga di intestazione
	getline(leggi, riga);
	int i=0;
	while(!leggi.eof()){
		//legge la classe (il primo campo) ma non lo usa
		getline(leggi, classe, ','); 
		//legge la descrizione
		getline(leggi, desc, ','); 
		//legge numero
		getline(leggi, num, ',');  
		//legge ma non usa il resto della riga
		getline(leggi, resto, '\n');  
		if(desc==descrizione&&num==numero){
			return i;
		}
		i++;
	}
	return -1;
}

bool Modifica(int posiz, string classe, string descrizione, string numero, string subalterno, string cap, string istat, double longit, double lat){
	ifstream leggi("Comune_Bergamo_-_Numerazione_civica.csv");
	ofstream scrivi("file2.csv");
	string riga;
	//salto l'intestazione
	getline(leggi, riga);
	scrivi<<riga<<"\n";
	int i=0;
	if(!scrivi.is_open()){
		return false;
	}
	if(leggi.is_open()){
		while(getline(leggi,riga)){
			if(i!=posiz){
				//se non trovo quello che voglio modificare continuo a copiare
				scrivi<<riga<<"\n";
			}
			else{
				//quando lo trovo scrivo le riga modificata
				scrivi<<classe<<","<<descrizione<<","<<numero<<","<<subalterno<<","<<cap<<","<<istat<<","<<longit<<","<<lat<<",\"("<<longit<<","<<lat<<")\""<<"\n";
			}
			i++;
		}
	}
	return true;
}

bool Cancella(int posiz){
	ifstream leggi("Comune_Bergamo_-_Numerazione_civica.csv");
	ofstream scrivi("file2.csv");
	string riga;
	//salto intestazione
	getline(leggi, riga);
	scrivi<<riga<<"\n";
	int i=0;
	if(!scrivi.is_open()){
		return false;
	}
	if(leggi.is_open()){
		while(getline(leggi,riga)){
			//finchè non trovo quello che sto cercando lo copio e quello da eliminare lo salto e non faccio nulla
			if(i!=posiz){
				scrivi<<riga<<"\n";
			}
			i++;
		}
	}
	return true;
}

int main(){
	int opzione;
	string classe, descrizione, numero, subalterno, cap, istat;
	double latitudine, longitudine;

	do{
		cout<<"APPLICAZIONE CSV\n1 - inserisci\n2 - modifica\n3 - cancella\n0 - stop";
		cout<<"\nopzione: ";
		cin>>opzione;

		switch(opzione){

			case 1:{
				//inserisco i campi del nuovo elemento
				cout<<"\ninserisci i dati della via che vuoi aggiungere:\n";
				fflush(stdin);
				cout<<"classe: ";
				getline(cin, classe);
				cout<<"descrizione: ";
				getline(cin, descrizione);
				cout<<"numero: ";
				getline(cin, numero);
				cout<<"subalterno: ";
				getline(cin, subalterno);
				cout<<"cap: ";
				getline(cin, cap);
				cout<<"istat: ";
				getline(cin, istat);
				cout<<"latitudine: ";
				cin>>latitudine;
				cout<<"longitudine: ";
				cin>>longitudine;
				fflush(stdin);
				//chiamo la funzione
				bool inserisci=Aggiungi(classe, descrizione, numero, subalterno, cap, istat, longitudine, latitudine);
				if(inserisci){
					//cancello il vecchio file e rinomino il nuovo
					remove("Comune_Bergamo_-_Numerazione_civica.csv");
					rename("file2.csv", "Comune_Bergamo_-_Numerazione_civica.csv");
					cout<<"\nelemento aggiunto\n\n";
				}
				else{
					cout<<"\nerrore nell'inserimento\n\n";
				}
				break;
			}

			case 2:{
				fflush(stdin);
				cout<<"\ninserisci i dati della via da modificare:\n";
				cout<<"descrizione: ";
				getline(cin, descrizione);
				//maiuscolo
				transform(descrizione.begin(), descrizione.end(), descrizione.begin(), [](unsigned char c){
					return toupper(c);
				});
				cout<<"numero: ";
				getline(cin, numero);
				//maiuscolo
				transform(numero.begin(), numero.end(), numero.begin(), [](unsigned char c){
					return toupper(c);
				});
				//cerco nel file se la via è presente
				int posiz=Cerca(descrizione, numero);
				if(posiz!=-1){
					cout<<"\ninserisci i dati modificati:\n";
					fflush(stdin);
					cout<<"classe: ";
					getline(cin, classe);
					cout<<"descrizione: ";
					getline(cin, descrizione);
					cout<<"numero: ";
					getline(cin, numero);
					cout<<"subalterno: ";
					getline(cin, subalterno);
					cout<<"cap: ";
					getline(cin, cap);
					cout<<"istat: ";
					getline(cin, istat);
					cout<<"latitudine: ";
					cin>>latitudine;
					cout<<"longitudine: ";
					cin>>longitudine;
					fflush(stdin);
					bool mod=Modifica(posiz, classe, descrizione, numero, subalterno, cap, istat, longitudine, latitudine);
					if(mod){
						//se va a buon fine cancello il vecchio file e rinomino il nuovo
						remove("Comune_Bergamo_-_Numerazione_civica.csv");
						rename("file2.csv", "Comune_Bergamo_-_Numerazione_civica.csv");
						cout<<"\nmodifica avvenuta\n\n";
					}
					else{
						cout<<"\nerrore nella modifica\n\n";
					}
				}
				else{
					cout<<"\nelemento non trovato\n\n";
				}
				break;
			}

			case 3:{
				fflush(stdin);
				cout<<"\ninserisci i dati della via da cancellare:\n";
				cout<<"descrizione: ";
				getline(cin, descrizione);
				//maiuscolo
				transform(descrizione.begin(), descrizione.end(), descrizione.begin(), [](unsigned char c){
					return toupper(c);
				});
				cout<<"numero: ";
				getline(cin, numero);
				//maiuscolo
				transform(numero.begin(), numero.end(), numero.begin(), [](unsigned char c){
					return toupper(c);
				});
				int posiz=Cerca(descrizione, numero);
				//se lo trovo cancello
				if(posiz!=-1){
					bool canc=Cancella(posiz);
					if(canc){
						//se va tutto a buon fine cancello il file vecchio e rinomino il nuovo
						remove("Comune_Bergamo_-_Numerazione_civica.csv");
						rename("file2.csv", "Comune_Bergamo_-_Numerazione_civica.csv");
						cout<<"\ncancellazione avvenuta\n\n";
					}
					else{
						cout<<"\nerrore nella cancellazione\n\n";
					}
				}
				else{
					cout<<"\nelemento non trovato\n\n";
				}
				break;
			}
		}
	}
	while(opzione!=0);

	return 0;
}

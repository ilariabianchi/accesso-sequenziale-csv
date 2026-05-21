#include <iostream>
#include <string>
#include <fstream>
//per convertire in maiuscolo
#include <algorithm>
#include <cctype>
using namespace std;

struct Location {
    double latitudine1;
    double longitudine1;
};

struct NumerazioneCivica {
    string classe;
    string descrizione;
    string numero;
    string subalterno;
    string cap;
    string istat;
    double latitudine;
    double longitudine;
    Location posto;
};

bool CaricaDati(NumerazioneCivica v[], int righe_tot){
	//apro il file
    ifstream leggi("Comune_Bergamo_-_Numerazione_civica.csv");
    //se il file non è aperto, ritorno falso
    if(!leggi.is_open()) {
        return false;
    }
    string riga, dati;
    //salto la prima riga di intestazione
    getline(leggi, riga);
    int i=0;
    //controllo che il ciclo si ripeta per il numero delle righe e che non sia alla fine del file
    while (i<righe_tot && !leggi.eof()){
    	//leggo il primo campo della riga e se siamo già alal fine del file esco dal ciclo
        getline(leggi, v[i].classe, ',');
        if(leggi.eof()){
        	break;	
		}
		//leggo gli altri campi separati dalla virgola
        getline(leggi, v[i].descrizione, ',');
        getline(leggi, v[i].numero, ',');
        getline(leggi, v[i].subalterno, ',');
        getline(leggi, v[i].cap, ',');
        getline(leggi, v[i].istat, ',');
		//converto da stringa a double
        getline(leggi, dati, ',');
        v[i].latitudine=stod(dati);
		//alla fine della riga si va a capo e la virgola non c'è più
        getline(leggi, dati, '\n');
        v[i].longitudine=stod(dati);
		//copio gli stessi valori latitudine e longitudine in Location
        v[i].posto.latitudine1=v[i].latitudine;
        v[i].posto.longitudine1=v[i].longitudine;
        i++;
    }
	//chiudo il file
    leggi.close();
    return true;
}

bool Aggiungi(string classe, string descrizione, string numero, string subalterno, string cap, string istat, double longit, double lat){
	ifstream leggi("Comune_Bergamo_-_Numerazione_civica.csv");
	ofstream scrivi("file2.csv", ios::app);
	//copio nel nuovo file
	string riga;
	if(!scrivi.is_open()){
		return false;
	}
	if(leggi.is_open()){
		while(!leggi.eof()){
			getline(leggi, riga);
			scrivi<<riga<<endl;
		}
    }
    scrivi<<classe<<","<<descrizione<<","<<numero<<","<<subalterno<<","<<cap<<","<<istat<<","<<longit<<","<<lat<<",\"("<<longit<<","<<lat<<")\""<<endl;
	leggi.close();
	scrivi.close();
	return true;
}
int Cerca(NumerazioneCivica v[], string descrizione, string numero, int d){
	for(int i=0; i<d; i++){
		if(v[i].descrizione==descrizione&&v[i].numero==numero){
			return i;
		}
	}
	return -1;
}
bool Modifica(int posiz, string classe, string descrizione, string numero, string subalterno, string cap, string istat, double longit, double lat){
	ifstream leggi("Comune_Bergamo_-_Numerazione_civica.csv");
	ofstream scrivi("file2.csv");
	string riga;
	getline(leggi, riga);
    scrivi<<riga<<endl;
	int i=0;
	//copio nel nuovo file
	
	if(!scrivi.is_open()){
		return false;
	}
	if(leggi.is_open()){
		while(getline(leggi,riga)){
			if(i!=posiz){
				scrivi<<riga<<endl;		
			}
			else{
		    scrivi<<classe<<","<<descrizione<<","<<numero<<","<<subalterno<<","<<cap<<","<<istat<<","<<longit<<","<<lat<<",\"("<<longit<<","<<lat<<")\""<<endl;
			}
			i++;
		}
    }
	return true;
	
}

//bool Cancella(){
	
//}

int main() {
	int opzione;
	NumerazioneCivica dati[10];
	NumerazioneCivica via, nuovo, cerca;
	int d=sizeof(dati)/sizeof(dati[0]);
	
    do{
        cout<<"APPLICAZIONE CSV\n1 - carica dati\n2 - inserisci\n3 - modifica\n4 - cancella\n5 - visualizza\n0 - stop";
        cout<<"\nopzione: ";
        cin>>opzione;
        
        switch(opzione){
        	
        	case 1:{
        		//carico i dati
        		if(CaricaDati(dati, d)){
                    cout<<"\ndati caricati\n\n";
                }
                //se i dati non vengono caricati si viene avvertiti
                else{
                    cout<<"\nfile non aperto\n\n";
                }
        		
				break;
			}
			
			case 2:{
				//inserisco un nuovo elemnto
				cout<<"\ninserisci i dati della via che vuoi aggiungere:\n";
				fflush(stdin);
				cout<<"classe: ";
				getline(cin, via.classe);
				cout<<"descrizione: ";
				getline(cin, via.descrizione);
				cout<<"numero: ";
				getline(cin, via.numero);
				cout<<"subalterno: ";
				getline(cin, via.subalterno);
				cout<<"cap: ";
				getline(cin, via.cap);
				cout<<"istat: ";
				getline(cin, via.istat);
				cout<<"latitudine: ";
				cin>>via.latitudine;
				cout<<"longitudine: ";
				cin>>via.longitudine;
				fflush(stdin);
				bool inserisci=Aggiungi(via.classe, via.descrizione, via.numero, via.subalterno, via.cap, via.istat, via.longitudine, via.latitudine);
				if(inserisci){
					cout<<"\nelemento aggiunto\n\n";
				}
				else{
					cout<<"\nerrore nell'inserimento\n\n";
				}
				break;
			}
			
			case 3:{
				//modifico un elemento
				fflush(stdin);
				cout<<"\ninserisci i dati della via da cercare:\n";
				cout<<"descrizione: ";
				getline(cin, via.descrizione);
				transform(via.descrizione.begin(), via.descrizione.end(), via.descrizione.begin(), [](unsigned char c){
        			return toupper(c);
    			});
				cout<<"numero: ";
				getline(cin, via.numero);
				transform(via.numero.begin(), via.numero.end(), via.numero.begin(), [](unsigned char c){
        			return toupper(c);
    			});
				int posiz=Cerca(dati, via.descrizione, via.numero, d);
				if(posiz!=-1){
					cout<<"\ninserisci i dati modificati:\n";
					fflush(stdin);
					cout<<"classe: ";
					getline(cin, via.classe);
					cout<<"descrizione: ";
					getline(cin, via.descrizione);
					cout<<"numero: ";
					getline(cin, via.numero);
					cout<<"subalterno: ";
					getline(cin, via.subalterno);
					cout<<"cap: ";
					getline(cin, via.cap);
					cout<<"istat: ";
					getline(cin, via.istat);
					cout<<"latitudine: ";
					cin>>via.latitudine;
					cout<<"longitudine: ";
					cin>>via.longitudine;
					fflush(stdin);
					bool mod=Modifica(posiz, via.classe, via.descrizione, via.numero, via.subalterno, via.cap, via.istat, via.longitudine, via.latitudine);
				}
				if(Modifica){
					cout<<"\nmodifica avvenuta\n\n";
				}
				else{
					cout<<"\nerrore nella modifica\n\n";
				}
				
				
				break;
			}
			
			case 4:{
				
				break;
			}
		}
    }
    while(opzione!=0);
	
	return 0;
}

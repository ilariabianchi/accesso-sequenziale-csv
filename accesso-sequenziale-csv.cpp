#include <iostream>
#include <string>
#include <fstream>
using namespace std;

bool Aggiungi(){
	ifstream leggi("Comune_Bergamo_-_Numerazione_civica.csv");
	ofstream scrivi("file2.csv");
	//copio nel nuovo file
	string riga;
	if(leggi.is_open()){
		while(!leggi.eof()){
			getline(leggi, riga);
			scrivi<<riga<<endl;
		}
    }
    else{
    	return false;
	}
	return true;
}

//bool Modifica(){
	
//}

//bool Cancella(){
	
//}

int main() {
	int opzione;

    do{
        cout<<"APPLICAZIONE CSV\n1 - inserisci\n2 - visualizza\n3 - modifica\n4 - cancella\n0 - stop";
        cout<<"\nopzione: ";
        cin>>opzione;
        
        switch(opzione){
        	
        	case 1:{
        		
				break;
			}
			
			case 2:{
				
				break;
			}
			
			case 3:{
				
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

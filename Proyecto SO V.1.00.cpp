#include <bits/stdc++.h>
#include <windows.h>
#include "termcolor.hpp"
#define MAX 1000
#include <SFML/Audio.hpp>
int MAX2=1000;
using namespace sf;
using namespace std;
void barra_uso(int);
class TNodo{
	public:
		int id;
		string name;
		char moments[1000];
		TNodo *sig;
		float tam;
		float tempo;
		float newTempo;
		string estado;
		TNodo(string nombre,int _id){
			this->sig=NULL;
				id=_id;
				srand(time(NULL));
				this->tempo=5+rand()%20;
				this->newTempo=this->tempo;
				this->tam=0;
				strcpy(moments,"______");
				this->name=nombre;
				this->estado="Listo";
		}	
};
int condicion(int x)
{
	int cont=0;
	bool continuar;
	do
	{
		continuar=false;
		cin.clear();
		if(cont>0) cin.ignore(1024,'\n');
		cin>>x;
		cont++;
		if(cin.fail()&&cin.rdstate())
		{
			continuar=true;
			cout<<termcolor::red<<"Por favor, ingresa un N�mero decimal: "<<termcolor::reset<<endl;
		}
	}while(continuar);
	return x;
}
struct TNombre{
	string name;
};
class TProceso{ 
	private:
		int cantelem;
	public:
		TNodo *lista;
		TNodo *tail;
		TProceso();
		void ligaProceso(string,int); //Llenar Lista
		void processID(); //Mostrar Lista de Procesos
		int iniciarProcesos(); 
		void kill(string);
		void mejorAjuste(string,int);
		void primerAjuste(string,int);
		void peorAjuste(string,int);
		void bloquear(string);
		TNodo* eliminar();
		TNodo* mayor();
		TNodo* postbloqueo(TNodo*);
		void ordernarLista();
		inline int size(){
			return this->cantelem;
		}	
};
TProceso::TProceso(){
	lista=NULL;
	cantelem=0;
}
void TProceso::ligaProceso(string name,int id){
	TNodo *nuevo=new TNodo(name,id);
	int x;
	struct tm *hora;
	time_t tiempo;
	time(&tiempo);
    hora=localtime(&tiempo);
	strcpy(nuevo->moments,asctime(hora));
	cout<<"Ingrese el Tama�o del Proceso "<<nuevo->name<<"en MBs"<<endl; 
	nuevo->tam=condicion(x);
	if(nuevo->tam>MAX2){ 
	do{ 
		cout<<"El Tama�o del Proceso es demasiado grande para la memoria Actual"<<endl;  
		cout<<"Elija un tama�o m�s peque�o para el proceso "<<nuevo->name<<"en MBs"<<endl;
		nuevo->tam=condicion(nuevo->tam); 
	}while(nuevo->tam>MAX2); 
	} 
	if(lista==NULL){
		MAX2-=nuevo->tam;
		lista=nuevo;
		cantelem++;
	}else{
		tail=lista;
		while(tail->sig!=NULL){
			tail=tail->sig;
		}
		MAX2-=nuevo->tam;
		tail->sig=nuevo;
		cantelem++;
	} 
}
TNodo* TProceso::eliminar(){
	if(lista==NULL){
		return NULL;
	}
	TNodo *pop=lista;
	if(lista->sig==NULL){
		lista=NULL;
		tail=NULL;
		cantelem--;
		return lista;
	}else{
		lista=lista->sig;
		MAX2+=lista->tam;
		cantelem--;
		return lista;
	}
	delete pop;
	cantelem--;
}
void TProceso::processID(){
	TNodo *show=lista;
	int cantele=0,memFull=0,memLibre=0;
	system("cls");
	cout<<"Listado de los Procesos:"<<endl;
	while(show!=NULL){
		//pop->name.compare(nombre)!=0
		if(show->estado.compare("Bloqueado")==0){
			cout<<termcolor::on_yellow<<"ID "<<show->id<<":"<<" Nombre del Proceso: "<<show->name<<" Tama�o del Proceso: "<<show->tam<<"mbs"<<" Tiempo Total del Proceso: "<<show->tempo<<" Segundos"<<endl<<" Tiempo Actual del Proceso: "<<show->newTempo<<" Segundos"<<" Estado Actual del Proceso: "<<show->estado<<" Tiempo Exacto de Inicializaci�n: "<<show->moments;//<<endl;
		}else{
		cout<<termcolor::on_red<<"ID "<<show->id<<":"<<" Nombre del Proceso: "<<show->name<<" Tama�o del Proceso: "<<show->tam<<"mbs"<<" Tiempo Total del Proceso: "<<show->tempo<<" Segundos"<<endl<<" Tiempo Actual del Proceso: "<<show->newTempo<<" Segundos"<<" Estado Actual del Proceso: "<<show->estado<<" Tiempo Exacto de Inicializaci�n: "<<show->moments; //<<endl;
		}cantele++;
		memFull+=show->tam;
		show=show->sig;
		//cout<<endl;
		cout<<"__________________________________________________________________________________________________"<<endl;
	}
	cout<<termcolor::reset<<endl;
	memLibre=MAX-memFull;
	cout<<"Existen un Total de "<<cantele<<" Procesos actuales "<<endl;
	cout<<"Se tiene un Total de "<<memFull<<"MB Memoria Ocupada"<<endl;
	cout<<"Se tiene un Total de "<<memLibre<<"MB Memoria Libre"<<endl;
		if(memFull>0&&memFull<200){
				cout<<endl;
				barra_uso(1);
			}else if(memFull>=200&&memFull<400){
				cout<<endl;
				barra_uso(2);
			}else if(memFull>=400&&memFull<600){
				cout<<endl;
				barra_uso(3);
			}else if(memFull>=600&&memFull<800){
				cout<<endl;
				barra_uso(4);
			}else if(memFull>=800&&memFull<1000){
				cout<<endl;
				barra_uso(5);
			}else if(memFull==1000){
				cout<<endl;
				barra_uso(6);
			}else if(memFull==0){
				cout<<endl;
				barra_uso(7);
			}
			cout<<termcolor::reset;
}
int TProceso::iniciarProcesos(){
	int x,y,i,z,a;
	bool band=false;
	TNodo *pop=lista;
	TNodo *aux;
	for(;;){
		if(pop==NULL){
			system("cls");
			cout<<termcolor::red<<"No hay Procesos disponibles. A�ada procesos antes de continuar"<<termcolor::reset<<endl;
			system("pause");
			return 0;
		}
		//system("cls");
		cout<<termcolor::yellow<<"I N F O R M A C I O N  I M P O R T A N T E"<<endl;
		cout<<"Para Bloquear el proceso actual presione Shift, Presione Enter para Reanudar y Q para Salir del Simulador. Presione cuando este listo"<<termcolor::reset<<endl;
		if(GetAsyncKeyState(VK_SHIFT)){
			//setbuf(stdin,NULL);
			aux=pop;
			TProceso::bloquear(aux->name);
			pop=TProceso::postbloqueo(aux);
			setbuf(stdin,NULL);
			band=true;
			//pop=lista;
			getchar();
		}
		if(GetAsyncKeyState(0x51)){
			system("cls");
			cout<<termcolor::green<<"Salida Exitosa"<<termcolor::reset<<endl;
			system("pause");
			return 0;
		}	
		pop->newTempo--;
		Sleep(1000);
		if(pop->newTempo==0){
			pop=TProceso::eliminar();
			if(pop==NULL){
				break;
			}
			if(pop->estado.compare("Bloqueado")==0){
				pop->estado="Listo";
			}
		}
		   system("cls");
			cout<<termcolor::green<<"Proceso Actual "<<pop->name<<" Tiempo Restante "<<pop->newTempo<<termcolor::reset<<endl;
	}
}
void TProceso::kill(string nombre){
	if(lista!=NULL){
		TNodo *pop=lista;
		TNodo *anterior=NULL;
		while((pop!=NULL)&&(pop->name.compare(nombre)!=0)){
			anterior=pop;
			pop=pop->sig;
		}
			if(pop==NULL){
				cout<<"No se ha Encontrado el Proceso "<<nombre<<endl;
			}else if(anterior==NULL){
				cout<<"Proceso "<<nombre<<" Eliminado con �xito"<<endl;
				lista=lista->sig;
				MAX2+=lista->tam;
				cantelem--;
			}else{
				cout<<"Proceso "<<nombre<<" Eliminado con �xito"<<endl;
				anterior->sig=pop->sig;
				MAX2+=pop->tam;
				cantelem--;
				delete pop;
			}
	}else{
		cout<<"Lista Vac�a"<<endl;
	}
}
TNodo* TProceso::postbloqueo(TNodo *actual){
	if(lista==NULL){
		actual->estado="Bloqueado";
		actual->sig=NULL;
		lista=actual;
		return lista;
	}else{
		tail=lista;
		while(tail->sig!=NULL){
			tail=tail->sig;
		}
		actual->sig=NULL;
		actual->estado="Bloqueado";
		tail->sig=actual;
		return lista;
	}
}
void TProceso::bloquear(string nombre){
		if(lista!=NULL){
		TNodo *pop=lista;
		TNodo *anterior=NULL;
		while((pop!=NULL)&&(pop->name.compare(nombre)!=0)){
			anterior=pop;
			pop=pop->sig;
		}
			if(anterior==NULL){
				cout<<"Proceso "<<nombre<<" Bloqueado con �xito"<<endl;
				lista=lista->sig;
			}else{
				cout<<"Proceso "<<nombre<<" Bloqueado con �xito"<<endl;
				anterior->sig=pop->sig;
				delete pop;
			}
	}
}
void TProceso::primerAjuste(string name,int _id){
	TNodo *nuevo=new TNodo(name,_id);
	int x,suma;
	struct tm *hora;
	time_t tiempo;
	time(&tiempo);
    hora=localtime(&tiempo);
	strcpy(nuevo->moments,asctime(hora));
	cout<<"Ingrese el Tama�o del Proceso "<<nuevo->name<<"en MBs"<<endl; 
	nuevo->tam=condicion(x);
	if(nuevo->tam>MAX2){
		do{ 
		cout<<"El Tama�o del Proceso es demasiado grande para la memoria Actual"<<endl;  
		cout<<"Elija un tama�o m�s peque�o para el proceso "<<nuevo->name<<"en MBs"<<endl;
		nuevo->tam=condicion(nuevo->tam); 
	}while(nuevo->tam>MAX2);
	}
	
	if(lista==NULL){
		lista=nuevo;
		cantelem++;
	}else{
		if(nuevo->tam<lista->tam){
			nuevo->sig=lista;
			lista=nuevo;
			MAX2-=nuevo->tam;
			cantelem++;
		}else{
			TNodo *aux=lista;
			TNodo *final=lista;
			while(nuevo->tam>=aux->tam && aux->sig!=NULL){
				final=aux;
				aux=aux->sig;
			}
			if(aux->sig==NULL){
				tail=aux; 
				tail->sig=nuevo;
 				MAX2-=nuevo->tam;
				cantelem++;
			}else{
				MAX2-=nuevo->tam;
				nuevo->sig=aux;
				final->sig=nuevo;
				cantelem++;
			}
		}
	}
}
void TProceso::ordernarLista(){
	if(lista!=NULL){
	TNodo *pivote=NULL,*actual=NULL;
	int aux=0;
	pivote=lista;
	while(pivote!=tail->sig){
		actual=pivote->sig;
			while(actual!=NULL){
				if(pivote->tam>actual->tam){
					aux=pivote->tam;
					pivote->tam=actual->tam;
					actual->tam=aux;
				}
				actual=actual->sig;
			}
		pivote=pivote->sig;	
	}
	}else{
		cout<<"Lista Vac�a"<<endl;
	}
}
void TProceso::mejorAjuste(string name, int id){
	int tam;
	struct tm *hora;
	time_t tiempo;
	time(&tiempo);
    hora=localtime(&tiempo);
	TNodo *nuevo=new TNodo(name,id);
	strcpy(nuevo->moments,asctime(hora));
	cout<<"Ingrese el Tama�o del Proceso "<<nuevo->name<<"en MBs"<<endl; 
	nuevo->tam=condicion(tam);
	if(nuevo->tam>MAX2){
	do{
		cout<<"El Tama�o del Proceso es demasiado grande para la memoria Actual"<<endl; 
		cout<<"Elija un tama�o m�s peque�o para el proceso "<<nuevo->name<<"en MBs"<<endl;
		nuevo->tam=condicion(tam);
	}while(nuevo->tam>MAX2);
	}
	if(lista==NULL){
		lista=nuevo;
		MAX2-=nuevo->tam;
		cantelem++;
	}else{
		TProceso::ordernarLista();
			if(nuevo->tam<lista->tam){
			nuevo->sig=lista;
			lista=nuevo;
			MAX2-=nuevo->tam;
			cantelem++;
		}else{
			TNodo *aux=lista;
			TNodo *final=lista;
			while(nuevo->tam>=aux->tam && aux->sig!=NULL){
				final=aux;
				aux=aux->sig;
			}
			if(aux->sig==NULL){
				tail=aux;
				tail->sig=nuevo;
				MAX2-=nuevo->tam;
				cantelem++;
			}else{
				MAX2-=nuevo->tam;
				nuevo->sig=aux;
				final->sig=nuevo;
				cantelem++;
			}
		}
	}
}
TNodo* TProceso::mayor(){ 
	TNodo *aux=lista; 
	TNodo *max; 
	int mayor=0; 
	while(aux->sig!=NULL){ 
		if(aux->tam>mayor){ 
			mayor=aux->tam; 
			max=aux; 
		} 
		aux=aux->sig; 
	} 
	return max;  
} 
void TProceso::peorAjuste(string name,int id){
	int pos,x;
	TNodo *nuevo=new TNodo(name,id);
	TNodo *max;
	struct tm *hora;
	time_t tiempo;
	time(&tiempo);
    hora=localtime(&tiempo);
	strcpy(nuevo->moments,asctime(hora));
	cout<<"Ingrese el Tama�o del Proceso "<<nuevo->name<<"en MBs"<<endl; 
	nuevo->tam=condicion(x); 
	if(nuevo->tam>MAX2){ 
	do{ 
		cout<<"El Tama�o del Proceso es demasiado grande para la memoria Actual"<<endl;  
		cout<<"Elija un tama�o m�s peque�o para el proceso "<<nuevo->name<<"en MBs"<<endl;
		nuevo->tam=condicion(x); 
	}while(nuevo->tam>MAX2); 
	} 
	if(lista==NULL){
		lista=nuevo;
		MAX2-=nuevo->tam;
		cantelem++;
	}else{
		max=TProceso::mayor();
		if(nuevo->tam>max->tam){ 
			tail=lista; 
			while(tail->sig!=NULL){ 
				tail=tail->sig; 
			} 
			tail->sig=nuevo; 
			MAX2-=nuevo->tam; 
			cantelem++; 
		}else{ 
		TNodo *temp=lista;
		TNodo *final=lista;
		while(temp->tam!=max->tam){
			final=temp;
			temp=temp->sig;
		}
		MAX2-=nuevo->tam;
		nuevo->sig=temp;
		final->sig=nuevo;
		cantelem++;
	}
}
}
string generaNombre(int);
void welcome(int);
int menu2();
void salir();
int main(){
	setlocale(LC_ALL,"Spanish");
	TProceso *lista=new TProceso();
	string name;
	int op,id,stat;
	srand((time(NULL)));
	struct tm *hora;
	time_t tiempo;
	time(&tiempo);
    hora=localtime(&tiempo);
    sf::Music music;
    music.openFromFile("MiiChannelMusic.ogg");
    music.play();
    music.setLoop(true);
    //if(!music.openFromFile("MiiChannelMusic.ogg"))
	//welcome(1);
	do{
		system("cls");
		welcome(0);
		cout<<"Tiempo Actual: "<<asctime(hora);
		cout<<termcolor::cyan<<"Seleccione una de las siguientes opciones:"<<termcolor::reset<<endl;
		cout<<"1.- Insertar un nuevo proceso"<<endl;
		//cout<<"1.- Insertar nuevo Proceso sin Ningun Ajuste"<<endl;
		cout<<"2.- Informaci�n de los Procesos Actuales"<<endl;
		cout<<"3.- Iniciar Procesos "<<endl;
		cout<<"4.- Eliminar un Proceso"<<endl;
		//cout<<"5.- Primer Ajuste"<<endl;
		//cout<<"6.- Mejor Ajuste"<<endl;
		//cout<<"7.- Peor Ajuste"<<endl;
		cout<<"5.- Salir"<<endl; 
		op=condicion(op);
		switch(op){
			case 1: switch(menu2()){
						case 1: id=1+rand()%100;
								name=generaNombre(id);
								lista->ligaProceso(name,id);
								break;
						case 2: id=1+rand()%100;
								name=generaNombre(id);
								lista->primerAjuste(name,id);
								system("pause");
								break;
						case 3:	id=1+rand()%100;
								name=generaNombre(id);
								lista->mejorAjuste(name,id);
								system("pause");
								break;
						case 4: id=1+rand()%100;
								name=generaNombre(id);
								lista->peorAjuste(name,id);
								system("pause");
								break;
						default:cout<<termcolor::red<<"Opci�n Inv�lida. Ser� retornado al men� principal"<<termcolor::reset<<endl;
								system("pause");
								break; 
					}
					break;
			case 2: lista->processID();
					system("pause");
					break;
			case 3: system("cls");
					stat=lista->iniciarProcesos();
					if(stat!=0){
					system("cls");
					cout<<termcolor::green<<"Ha finalizado el procesamiento con �xito"<<termcolor::reset<<endl;
					system("pause");	
					}
					break;
			case 4: cout<<"Ingresa el Nombre del Proceso a Eliminar"<<endl;
					fflush(stdin);
					getline(cin,name);
					lista->kill(name);
					system("pause");
					break; 
			case 5: music.setLoop(false);
					music.stop();
					salir();		
					break; 
			default: cout<<termcolor::red<<"Introduce una Opci�n V�lida"<<termcolor::reset<<endl;
					system("pause");
					break; 
		}
	}while(0!=9); //Ese bugaso lo hizo Javier Nagore :v 
}

int menu2(){
	system("cls");
	welcome(0);
	cout<<termcolor::on_green<<"Insertar un nuevo Proceso:"<<termcolor::reset<<endl;
	cout<<termcolor::cyan<<"Seleccione una de las siguientes opciones:"<<termcolor::reset<<endl;
	cout<<"1.- Insertar sin ajuste"<<endl;
	cout<<"2.- Insertar con primer ajuste"<<endl;
	cout<<"3.- Insertar con mejor ajuste"<<endl;
	cout<<"4.- Insertar con peor ajuste"<<endl;
	return condicion(1);	
}

string generaNombre(int id){
	TNombre nombres[101];
	nombres[1].name="Kokun";
	nombres[2].name="Bebote";
	nombres[3].name="VirusLetal100%RealNofeik";
	nombres[4].name="FlipFlop";
	nombres[5].name="Hardwar";
	nombres[6].name="Softwar";
	nombres[7].name="El de M�todos";
	nombres[8].name="Virus Windows";
	nombres[9].name="UaaBuntu";
	nombres[10].name="Nagobuntu";
	nombres[11].name="El Babitas";
	nombres[12].name="JuanGa";
	nombres[13].name="Guido";
	nombres[14].name="Juliett";
	nombres[15].name="Pabe";
	nombres[16].name="El Berns";
	nombres[17].name="Campana de Gauss";
	nombres[18].name="Horacio";
	nombres[19].name=":v";
	nombres[20].name="Mr.Bean";
	nombres[21].name="Karol";
	nombres[22].name="Monciloco";
	nombres[23].name="El de Redacci�n";
	nombres[24].name="Sendos Procesos";
	nombres[25].name="Happy Lunch";
	nombres[26].name="Geogebra";
	nombres[27].name="Firefox";
	nombres[28].name="La Chulis";
	nombres[29].name="Guon";
	nombres[30].name="Carlitos Palitos Pinalitos";
	nombres[31].name="Troyano";
	nombres[32].name="Midtown Madness";
	nombres[33].name="El Saucedo";
	nombres[34].name="El Serna";
	nombres[35].name="Bluetooth";
	nombres[36].name="Dev-C++";
	nombres[37].name="Chrome";
	nombres[38].name="Edgar Cortes";
	nombres[39].name="Ballenato";
	nombres[40].name="Code::Blocks";
	nombres[41].name="Issac Eli Ramos M�rquez";
	nombres[42].name="Euzeus";
	nombres[43].name="VLC";
	nombres[44].name="Just Another Process";
	nombres[45].name="Pebble";
	nombres[46].name="GuidoSon";
	nombres[47].name="GENuINE993";
	nombres[48].name="S0 3er Parcial.pdf";
	nombres[49].name="CCleaner";
	nombres[50].name="RIUAA";
	nombres[51].name="Sendas Faltas";
	nombres[52].name="Blackberry";
	nombres[53].name="Inclusivo";
	nombres[54].name="Panchito";
	nombres[55].name="El Checo";
	nombres[56].name="Micr�fonos";
	nombres[57].name="Pabeyork";
	nombres[58].name="Tlatoani Avelar";
	nombres[59].name="RitmoSon";
	nombres[60].name="iPod";
	nombres[61].name="Polic�a Cibern�tica";
	nombres[62].name="Molly";
	nombres[63].name="Winamp";
	nombres[64].name="Opera";
	nombres[65].name="Microsoft Store";
	nombres[66].name="ESET Smart Security";
	nombres[67].name="Cortana";
	nombres[68].name="Salas P�rez";
	nombres[69].name="Leds Quemados";
	nombres[70].name="Tom";
	nombres[71].name="Homero Simpson";
	nombres[72].name="Cuphead";
	nombres[73].name="Proceses";
	nombres[74].name="Compras Compulsivas";
	nombres[75].name="Problemas de Primer Mundo";
	nombres[76].name="Benjam�n";
	nombres[77].name="Mariana";
	nombres[78].name="Rodolfo";
	nombres[79].name="Word";
	nombres[80].name="Power Point";
	nombres[81].name="Keil uVision 5";
	nombres[82].name="Amazon";
	nombres[83].name="Zegucom";
	nombres[84].name="Aud�fonos";
	nombres[85].name="academia.uaa.mx";
	nombres[86].name="Windows Defender";
	nombres[87].name="Steam";
	nombres[88].name="MATLAB";
	nombres[89].name="Explota Compuertas L�gicas";
	nombres[90].name="Costco";
	nombres[91].name="System32";
	nombres[92].name="Microsoft Edge";
	nombres[93].name="Friday The 13th The Game";
	nombres[94].name="Proteus 8 Professional";
	nombres[95].name="Multisim";
	nombres[96].name="WMware WorkStation Pro";
	nombres[97].name="qBittorrent";
	nombres[98].name="Photoshop";
	nombres[99].name="Sumatra PDF";
	nombres[100].name="Malware";
	return nombres[id].name;
}

void welcome(int pos){
	FILE *fp;
	char ch,x;
	fp = fopen("welcome.txt", "r"); // read mode
	if (fp == NULL)
   {
      perror("Error while opening the file.\n");
      exit(EXIT_FAILURE);
   }
   while((ch = fgetc(fp)) != EOF)
   		cout<<termcolor::green<<ch;
      //printf("%c", ch);
   fclose(fp);
   cout<<termcolor::reset<<endl;
   cout<<endl;
   if(pos==1){
   system("pause");
	}else{
		
	}
}

void salir(){
	system("cls");
	welcome(0);
	//sf::Music music;
	cout<<termcolor::yellow<<"�Esta seguro que desea salir? Todo lo realizado en esta ejecuci�n se perder�."<<endl<< "Presione 1 para confirmar"<<endl<<"Presione cualquier numero para cancelar"<<termcolor::reset<<endl;
	if(condicion(1)==1){
		cout<<termcolor::green<<"Gracias por haber utilizado el simulador de procesos. �Hasta la pr�xima!"<<termcolor::reset<<endl;
		//music.setLoop(false);
		system("pause");
		exit(0);
	}
}
void barra_uso(int escal){
		char mat[5][3];
	switch(escal){
			case 1: //0-20 aprox
				cout<<"\n\tUso de memoria 0-20%"<<endl;
				for(int i=0;i<4;i++){
		for(int j=0;j<3;j++){
			mat[i][j]=char (NULL);
		}
	}
		for(int i=4;i<=5;i++){
			for(int j=0;j<3;j++){
				mat[i][j]=char(61);
			}
		}
			for(int i=0;i<5;i++){
				cout<<"\t\t";
		for(int j=0;j<3;j++){
			//cout<<"["<<mat[i][j]<<"]";
			cout<<termcolor::green<<"["<<mat[i][j]<<"]";
		}
		cout<<endl;
	}
			break;
			
	case 2: //20-40 aprox
			cout<<"\n\tUso de memoria 20-40%"<<endl;
				for(int i=0;i<3;i++){
		for(int j=0;j<3;j++){
			mat[i][j]=char (NULL);
		}
	}
		for(int i=3;i<=5;i++){
			for(int j=0;j<3;j++){
				mat[i][j]=char(61);
			}
		}
			for(int i=0;i<5;i++){
				cout<<"\t\t";
		for(int j=0;j<3;j++){
			//cout<<"["<<mat[i][j]<<"]";
			cout<<termcolor::green<<"["<<mat[i][j]<<"]";
		}
		cout<<endl;
	}
			break;
			
		case 3: //40-60 aprox
			cout<<"\n\tUso de memoria 40-60%"<<endl;
				for(int i=0;i<2;i++){
		for(int j=0;j<3;j++){
			mat[i][j]=char (NULL);
		}
	}
		for(int i=2;i<=5;i++){
			for(int j=0;j<3;j++){
				mat[i][j]=char(61);
			}
		}
			for(int i=0;i<5;i++){
				cout<<"\t\t";
		for(int j=0;j<3;j++){
			//cout<<"["<<mat[i][j]<<"]";
			cout<<termcolor::green<<"["<<mat[i][j]<<"]";
		}
		cout<<endl;
	}
			break;
			
		case 4: //60-80 aprox
			cout<<"\n\tUso de memoria 60-80%"<<endl;
				for(int i=0;i<1;i++){
		for(int j=0;j<3;j++){
			mat[i][j]=char (NULL);
		}
	}
		for(int i=1;i<=5;i++){
			for(int j=0;j<3;j++){
				mat[i][j]=char(61);
			}
		}
			for(int i=0;i<5;i++){
				cout<<"\t\t";
		for(int j=0;j<3;j++){
			//cout<<"["<<mat[i][j]<<"]";
			cout<<termcolor::green<<"["<<mat[i][j]<<"]";
		}
		cout<<endl;
	}
			break;
	
		case 5: // 80-100 aprox
			cout<<"\n\tUso de memoria 80-100%"<<endl;
				for(int i=0;i<=0;i++){
		for(int j=0;j<3;j++){
			mat[i][j]=char (177);
		}
	}
		for(int i=1;i<=5;i++){
			for(int j=0;j<3;j++){
				mat[i][j]=char(61);
			}
		}
			for(int i=0;i<5;i++){
				cout<<"\t\t";
		for(int j=0;j<3;j++){
			//cout<<"["<<mat[i][j]<<"]";
			cout<<termcolor::green<<"["<<mat[i][j]<<"]";
		}
		cout<<endl;
	}
			break;
		
		case 6: //totalmente llena
				cout<<"\n\tUso de memoria 100% - Memoria llena"<<endl;
				for(int i=0;i<5;i++){
		for(int j=0;j<3;j++){
			mat[i][j]=char(61);
		}
	}
		
			for(int i=0;i<5;i++){
				cout<<"\t\t";
		for(int j=0;j<3;j++){
			//cout<<"["<<mat[i][j]<<"]";
			cout<<termcolor::green<<"["<<mat[i][j]<<"]";
		}
		cout<<endl;
	}
			break;
			
		case 7: 
				cout<<"\n\tUso de memoria 0% - Memoria Vacia"<<endl;
					for(int i=0;i<5;i++){
		for(int j=0;j<3;j++){
			mat[i][j]=char (NULL);
		}
	}
		
			for(int i=0;i<5;i++){
				cout<<"\t\t";
		for(int j=0;j<3;j++){
			//cout<<"["<<mat[i][j]<<"]";
			cout<<termcolor::green<<"["<<mat[i][j]<<"]";
		}
		cout<<endl;
	}
			
			
			
	}
		
}


/*class TProceso{
public:
float tempo;
char name[100];
float tam;
*/
#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
class TNodo{
	public:
		string name;
		TNodo *sig;
		float tam;
		float tempo;
		float newTempo;
		TNodo(string nombre){
			this->sig=NULL;
				srand(time(NULL));
				this->tempo=1+rand()%10;
				this->newTempo=this->tempo;
				this->tam=0;
				this->name=nombre;
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
			cout<<"Por favor, ingresa un Número: "<<endl;
		}
	}while(continuar);
	return x;
}
struct TNombre{
	string name;
	int id;
};
string generaNombre(int id){
	TNombre nombres[100];
	int cont;
	nombres[0].name="GuidoSon";
	nombres[0].id=0;
	nombres[1].name="Kokun";
	nombres[1].id=1;
	nombres[2].name="Bebote";
	nombres[2].id=2;
	nombres[3].name="VirusLetal100%RealNofeik";
	nombres[3].id=3;
	nombres[4].name="FlipFlop";
	nombres[4].id=4;
	nombres[5].name="Hardwar";
	nombres[5].id=5;
	nombres[6].name="Softwar";
	nombres[6].id=6;
	nombres[7].name="El de Métodos";
	nombres[7].id=7;
	nombres[8].name="Virus Windows";
	nombres[8].id=8;
	nombres[9].name="UaaBuntu";
	nombres[9].id=9;
	nombres[10].name="Nagobuntu";
	nombres[10].id=10;
	nombres[11].name="El Babitas";
	nombres[11].id=11;
	nombres[12].name="JuanGa";
	nombres[12].id=12;
	nombres[13].name="Guido";
	nombres[13].id=13;
	nombres[14].name="Juliett";
	nombres[14].id=14;
	nombres[15].name="Pabe";
	nombres[15].id=15;
	nombres[16].name="El Berns";
	nombres[16].id=16;
	nombres[17].name="Campana de Gauss";
	nombres[17].id=17;
	nombres[18].name="Horacio";
	nombres[18].id=18;
	nombres[19].name=":v";
	nombres[19].id=19;
	nombres[20].name="Mr.Bean";
	nombres[20].id=20;
	nombres[21].name="Karol";
	nombres[21].id=21;
	nombres[22].name="Monciloco";
	nombres[22].id=22;
	nombres[77].name="Mariana";
	nombres[77].id=77;
	return nombres[id].name;
}
class TProceso{
	public:
		TNodo *lista;
		TNodo *tail;
		TProceso();
		void ligaProceso(string); //Llenar Lista
		void processID(); //Mostrar Lista de Procesos
		void iniciarProcesos(); 
		string kill();
		void mejorAjuste();
		void primerAjuste();
		void peorAjuste();
		TNodo* eliminar();		
};
TProceso::TProceso(){
	lista=NULL;
}
void TProceso::ligaProceso(string name){
	TNodo *nuevo=new TNodo(name);
	int x;
	cout<<"Ingrese el Tamaño del Proceso"<<endl;
	nuevo->tam=condicion(x);
	if(lista==NULL){
		lista=nuevo;
	}else{
		tail=lista;
		while(tail->sig!=NULL){
			tail=tail->sig;
		}
		tail->sig=nuevo;
	} 
}
TNodo* TProceso::eliminar(){
	if(lista==NULL){
		return NULL;
	}
	TNodo *pop=lista;
	if(lista==tail){
		tail=NULL;
		lista=NULL;
		return NULL;
	}else{
		lista=lista->sig;
		return lista;
	}
	delete pop;
}
void TProceso::processID(){
	TNodo *show=lista;
	int cantelem=0;
	cout<<"Listado de los Procesos"<<endl;
	while(show!=NULL){
		cout<<"ID "<<cantelem+1<<":"<<" Nombre del Proceso: "<<show->name<<" Tamaño del Proceso: "<<show->tam<<"mbs"<<" Tiempo Total del Proceso: "<<show->tempo<<" Segundos"<<" Tiempo Actual del Proceso: "<<show->newTempo<<" Segundos";
		cantelem++;
		show=show->sig;
		cout<<endl;
		cout<<"_______________________________________________________________________________________________________________"<<endl;
	}
	cout<<"Existen un Total de "<<cantelem<<" Procesos actuales "<<endl;
}
void TProceso::iniciarProcesos(){
	TNodo *pop=lista;
	for(;;){
		if(pop==NULL){
			cout<<"No hay Procesos disponibles"<<endl;
			break;
		}
		cout<<"Para pausar presione Shift, Presione Enter para Reanudar y Escape para Salir"<<endl;
		if(GetAsyncKeyState(VK_LSHIFT)){
			setbuf(stdin,NULL);
		}
		if(GetAsyncKeyState(VK_ESCAPE)){
			break;
		}	
		pop->newTempo--;
		Sleep(1000);
		if(pop->newTempo==0){
			pop=TProceso::eliminar();
			//pop=pop->sig;
			if(pop==NULL){
				break;
			}
		}
		   system("cls");
			cout<<"Proceso Actual "<<pop->name<<" Tiempo Restante "<<pop->newTempo<<endl; }
	}
int main(){
	setlocale(LC_ALL,"Spanish");
	TProceso *lista=new TProceso();
	string name;
	int op,id;
	srand((time(NULL)));
	do{
		system("cls");
		cout<<"1.- Nuevo Proceso"<<endl; //Beta
		cout<<"2.- Mostrar Datos de Todos los Procesos Actuales"<<endl;
		cout<<"3.- Iniciar Procesos "<<endl; //Alpha3
		cin>>op;
		switch(op){
			case 1: id=0+rand()%22;
					name=generaNombre(id);
					lista->ligaProceso(name);
					break;
			case 2: lista->processID();
					system("pause");
					break;
			case 3: lista->iniciarProcesos();
					system("pause");
					break; 
		}
	}while(op!=4);
}

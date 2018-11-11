#include <bits/stdc++.h>
#include <windows.h>
using namespace std;
class TNodo{
	public:
		int id;
		string name;
		TNodo *sig;
		float tam;
		float tempo;
		float newTempo;
		TNodo(string nombre,int _id){
			this->sig=NULL;
				id=_id;
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
};
string generaNombre(int id){
	TNombre nombres[100];
	int cont;
	nombres[0].name="GuidoSon";
	nombres[1].name="Kokun";
	nombres[2].name="Bebote";
	nombres[3].name="VirusLetal100%RealNofeik";
	nombres[4].name="FlipFlop";
	nombres[5].name="Hardwar";
	nombres[6].name="Softwar";
	nombres[7].name="El de Métodos";
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
	nombres[23].name="El de Redacción";
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
	nombres[41].name="Issac Eli Ramos Márquez";
	nombres[42].name="Euzeus";
	nombres[43].name="VLC";
	nombres[44].name="Just Another Process";
	nombres[45].name="Pebble";
	nombres[77].name="Mariana";
	return nombres[id].name;
}
class TProceso{
	public:
		TNodo *lista;
		TNodo *tail;
		TProceso();
		void ligaProceso(string,int); //Llenar Lista
		void processID(); //Mostrar Lista de Procesos
		void iniciarProcesos(); 
		void kill(string);
		void mejorAjuste();
		void primerAjuste();
		void peorAjuste();
		TNodo* eliminar();		
};
TProceso::TProceso(){
	lista=NULL;
}
void TProceso::ligaProceso(string name,int id){
	TNodo *nuevo=new TNodo(name,id);
	int x;
	cout<<"Ingrese el Tamaño del Proceso "<<nuevo->name<<endl;
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
		cout<<"ID "<<show->id<<":"<<" Nombre del Proceso: "<<show->name<<" Tamaño del Proceso: "<<show->tam<<"mbs"<<" Tiempo Total del Proceso: "<<show->tempo<<" Segundos"<<" Tiempo Actual del Proceso: "<<show->newTempo<<" Segundos";
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
		cout<<"Para Pausar el proceso actual presione Space, Presione Enter para Reanudar y Escape para Salir"<<endl;
		if(GetAsyncKeyState(VK_SHIFT)){
			setbuf(stdin,NULL);
			getchar();
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
				cout<<"Proceso "<<nombre<<" Eliminado con Éxito"<<endl;
				lista=lista->sig;
			}else{
				cout<<"Proceso "<<nombre<<" Eliminado con Éxito"<<endl;
				anterior->sig=pop->sig;
				delete pop;
			}
	}else{
		cout<<"Lista Vacía"<<endl;
	}
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
		cout<<"4.- Eliminar un Proceso"<<endl;
		cout<<"5.- Salir"<<endl; 
		op=condicion(op);
		switch(op){
			case 1: id=0+rand()%45;
					name=generaNombre(id);
					lista->ligaProceso(name,id);
					break;
			case 2: lista->processID();
					system("pause");
					break;
			case 3: lista->iniciarProcesos();
					system("pause");
					break;
			case 4: cout<<"Ingresa el Nombre del Proceso a Eliminar"<<endl;
					fflush(stdin);
					getline(cin,name);
					lista->kill(name);
					system("pause");
					break;
			case 5: break;
			default: cout<<"Introduce una Opción Válida"<<endl;
					system("pause");
					break; 
		}
	}while(op!=5);
}

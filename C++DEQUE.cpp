//////////////////////////////////PRACTICA 1. INFORMÁTICA INDUSTRIAL
/////////////////////////////////// OSCAR EMILIO APONTE RENGIFO
//////////////////////////////////-----------SISTEMA DE REFRIGERACIÓN INDUSTRIAL--SENSOR DE TEMPERATURA
#include <iostream>
#include <fstream> // Apertura del fichero
#include <deque> // DECLARACIÓN DE LA CLASE DEQUE
#include <stdlib.h> // Para el uso del "system('cls')"

#include <algorithm> // Iterador

using namespace std;

class lecturatemp // Declaración de clase que contiene dos tipos de datos
{
    public:
    double lectura;
     long int timestamp;

}milectura;
//////////////////////////--------DECLARACIÓN DE DEQUE e Iterador como variable global
deque <lecturatemp> cola;
deque <lecturatemp>:: const_iterator it;
//////////////////////////--------DECLARACIÓN DE FUNCIONES.
void menu(); // Control de las opciones que realiza el programa
void imprimir(); // Imprime los datos presentes en la cola
void volver_al_menu(); //
void borrar(); // Borra datos del deque
bool comparatempmin (lecturatemp elem1, lecturatemp elem2);  // función que compara dos elementos
bool comparatempmax (lecturatemp elem1, lecturatemp elem2);  // función que compara dos elementos
///////////////////////////////////////////////--FUNCIONES------------------

int main()
{
    //////////////////
    int contador=0;
    /////////////////////////// LECTURA DEL FICHERO

     ifstream fich("datos.txt");//Abrimos fichero de daros.
    if (!fich)
    {
        cout <<"error en la lectura del fichero" << endl;//Mensaje de error por si fichero se abre mal.
        return 0;
    }
    while(!fich.eof())
    {
    contador++;
     fich>>milectura.lectura;//Introducimos el primer dato de fichero en el objeto de la clase
     fich>>milectura.timestamp;//Introducimos el segunfo dato del fichero en el segundo objeto
    cola.push_back(milectura);// Introducimos al final de la cola la clase.
    }fich.close();//cerramos fichero.
    ////////////////////////////Fin de lectura de fichero

    /////////////Selección de los 10 ultimos valores ingresados y descarte de las más antiguos
   do
   {
       contador--;
    cola.pop_front();//Sacamos los datos de la cola por su parte delantera.
   }while(contador>10); // "cola.pop_front" elimina los datos hasta que llega a los 10 ultimos
   /////////////////////////////////////// Llamada a la función menu
    menu();

}



///////////////--FUNCIÓN: MENÚ------
void menu()
{
int opcion;
long int tiempo_m;
double temperatura_m;
cout<<endl<<endl;
cout<<"|--------------------------------------------------------------------------|"<<endl;
cout<<"|--SISTEMA DE REFRIGERACION DE PLANTA IDUSTRIAL-----Sensor de temperatura--|"<<endl;
cout<<"|---------------------------Menú de opciones-------------------------------|"<<endl;
cout<<"|           0.- Salir                                                      |"<<endl;
cout<<"|           1.- Visualizar datos ///temperatura(Cº)-tiempo(seg)///         |"<<endl;
cout<<"|           2.- Ingresar nueva lectura                                     |"<<endl;
cout<<"|           3.- Visualizar máxima y mínima temperatura                     |"<<endl;
cout<<"|--------------------------------------------------------------------------|"<<endl;
cout<<endl<<endl;
cin>>opcion;


/////////----ERROR ANTE SELECCIÓN DE OPCIÓN INCORRECTA----

if (opcion!=0 && opcion!=1 && opcion!=2 && opcion!=3)
    {
    system("cls"); // Limpia pantalla
    cout<<endl;
    cout<<"ERROR--  "<< "!"<<opcion<<"!"<< " OPCION INCORRECTA"<< endl;
    menu();
    }

/////////----OPCIONES A ELEGIR--------------------

switch (opcion)
{
    ///////////-------SALIR DEL PROGRAMA----------
    case (0):
    break;
    ///////////-------VISUALIZAR DATOS------------
    case (1):
       system("cls");
       cout<<"----------------------------------"<<endl;
       cout<<"opcion.-1.-Visualizacion de datos:"<<endl;
       imprimir();
       volver_al_menu();
    break;
    //////////--------INGRESAR NUEVO DATO----------
    case (2):
        system("cls"); // limpia pantalla
        /////---BORRADO DE DATO ANTES DE INGRESAR EL NUEVO VALOR---
        borrar(); // borra el dato más antiguo antes del ingreso del nuevo dato
        ////---INGRESAR NUEVO VALOR--------
        cout<<"-------------------------------------"<<endl;
        cout<<" opcion.-2.- Ingresar nueva lectura  "<<endl;
        cout<<"-------------------------------------"<<endl;
        cout<<"Ingrese tiempo:"<<endl;
        cin>> milectura.timestamp;
        cout<<"Ingrese temperatura:"<<endl;
        cin >> milectura.lectura;
        cola.push_back(milectura); // Agrega dato al final de la cola
       imprimir();
       volver_al_menu();
    break;
    //////////-------MÁXIMA Y MÍNIMA TEMPERATURA---
    case (3):
        system("cls");
        cout<<"--------------------------------------------------"<<endl;
        cout<<"opcion.-3.- Visualizar temperatura máxima y mínima"<<endl;
       imprimir();
       //////////////////////////// Selección de máximo y mínimo - se emplea iterador
       it= max_element(cola.begin(),cola.end(),comparatempmax);
       cout<<"La temperatura máxima es:"<<endl;
       cout << it->lectura << " grados Centigrados"<<endl;
       it = min_element(cola.begin(),cola.end(),comparatempmin);
       cout<<"La temperatura mínima es:"<<endl;
       cout << it->lectura << " grados Centigrados"<<endl;
       volver_al_menu();
        break;
}

}



void imprimir() // FUNCIÓN QUE IMPRIME LOS ELEMENTOS DEL DEQUE - emplea iterador que recorre la cola
{
    deque <lecturatemp>:: iterator it;
    cout<<endl;
    cout<<"   |-----Lecturas del sensor-----|"<<endl;
    cout<<"   |--Temperatura(C)-Tiempo(sg)--|"<<endl;
    cout<<"   |-----------------------------|"<<endl;
    for (it=cola.begin() ; it!=cola.end(); it++)
    cout<<"   |   "<<it->lectura<<"     |  "<<it->timestamp<<"   |"<<  "         "  << endl;

}


void volver_al_menu() // FUNCIÓN QUE DA LA OPCIÓN DE VOLVER AL MENU LUEGO DE REALIZADO UN PROCESO
{
    int cont;
    cout<<"  >>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>>"<<endl<<endl;
    cout<<"Presione 1 para volver al menú- En Caso contrario sale del sistema"<<endl;
    cin>>cont;
    if (cont==1)
      {system("cls");
    menu();}
}

void borrar() // FUNCIÓN QUE BORRA ELEMENTO MÁS ANTIGUO
{
 cola.pop_front();
}
///////////////////// FUNCIONES BOOLEANAS EMPLEADAS PARA LA COMPARACIÓN DE DOS ELEMENTOS - se recorre a través del iterator

bool comparatempmin (lecturatemp elem1, lecturatemp elem2)
{
return (elem1.lectura < elem2.lectura);
}

bool comparatempmax (lecturatemp elem1 ,lecturatemp elem2)
{
return (elem2.lectura > elem1.lectura);
}

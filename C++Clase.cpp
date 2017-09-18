///////////////////////////////////PR�CTICA 1. INFORM�TICA INDUSTRIAL ----------------------------------------------
/////////////////////////////////// OSCAR EMILIO APONTE RENGIFO  ----------------------------
//////////////////////////////////-----------SISTEMA DE REFRIGERACI�N INDUSTRIAL--SENSOR DE TEMPERATURA-------------

#include <iostream>
#include <fstream> // Para conseguir la apertura del fichero.
#include <stdlib.h>//Permite el empleo del system("cls"):limpia pantalla.
///////////////////////
#include <conio.h>// Manejo de la excepci�n.
#include <ctype.h>// Manejo de la excepci�n
///////////////////////
using namespace std;

//////////////////////////////////---------DECLARACI�N DE CLASE NODO- LISTA ENLAZADA
class nodo
{
    public:// Declaramos las variables como p�blicas para acceder a ellas sin restriciones.
    double temperatura;
     int  tiempo;
    nodo *sig; //Puntero a nodo
};
///////////////////////////////////-------VARIABLES GLOBALES
int contador=0;
double cola_temperatura[10];//En esta variable se vuelca la cola para utilizar en las funciones de m�ximo y m�nimo.
///////////////////////////////////------VARIABLE GLOBAL DE LA LISTA ENLAZADA-NODO
nodo *cabeza=NULL;
///////////////////////////////////------DECLARACI�N DE FUNCIONES
void menu();//Crea un menu para elegir la acci�n a llevar a cabo.
void insertar(nodo *   &cab , double temperatura ,int tiempo);//Inserta un elemento al fina de la cola.
int borrar(nodo* &cab,double temperatura, int tiempo);// borra el primer dato introducido, desplaza los demas hacia la izquierda y deja el �ltimo hueco del dato vacio.
void imprimir (nodo * cab); // Imprime toda la cola.
void mayor_menor ();//Determina la temperatura mayor y menor de la cola.
void volver_al_menu ();//Una vez acabadas las funciones de la opci�n elgida, esta funci�n devuelve al sistema al men�.
void excepcion(int numero);// Crea una excepcion con el objetivo de que se introduzcan datos num�ricos en el apartado de tiempo cuando se introducen datos por teclado.

//////////////////////////////////////////////////////////////////////------FUNCIONES

////////////////////-------------FUNCI�N MAIN--- LECTURA DEL FICHERO Y POSTERIOR SELECCI�N DE 10 DATOS---------
int main()
{
     int time;
    double temp;
//////////////////----LECTURA DEL FICHERO------------
        ifstream entrada_aux;
    entrada_aux.open("datos.txt",ios::in);// Se produce la apertura del fichero.

    if (entrada_aux.good())// Si la apaertura se realiza correctamente mientras no se llegue al final del fichero introducir los datos del fichero en las variables y llama a la funcion insertar para introducirlos en la cola.
    {
       contador=0;
        while (!entrada_aux.eof())
        {
           contador++;
           entrada_aux >> temp;
           entrada_aux >> time;
 ////////////////----SE INSERTAN LOS VALORES LEIDOS EN LA LISTA ENLAZADA---------
           insertar(cabeza,temp ,time);
        }
        entrada_aux.close();// Cerrar fichero.
    }
    else
        {
            cerr << "error de apertura de fichero" << endl;// Si el fichero no se abre correctamente aparece mensaje de error.
        }
////////////////----FIN DE LECTURA DE FICHERO----
///////////////-----SE IMPLEMENTA UN CONTADOR PARA LA SELECCI�N DE LOS 10 �LTIMOS VALORES--------
do
    {
    contador--;
    borrar(cabeza,temp,time);
    }while (contador>10);
///////////////----LLAMADA DE LA FUNCI�N MEN� DE OPCIONES------
menu();

}

/////////////////////------------FUNCI�N DE ACCESO AL MEN� DE OPCIONES
void menu()
{
int opcion;
int tiempo_m;
double temperatura_m;
cout<<endl<<endl;
cout<<"  |--------------------------------------------------------------------------|"<<endl;
cout<<"  |--SISTEMA DE REFRIGERACION DE PLANTA IDUSTRIAL-----Sensor de temperatura--|"<<endl;
cout<<"  |---------------------------Men� de opciones-------------------------------|"<<endl;
cout<<"  |           0.- Salir                                                      |"<<endl;
cout<<"  |           1.- Visualizar datos    temperatura(C)- tiempo(seg)            |"<<endl;
cout<<"  |           2.- Ingresar nueva lectura                                     |"<<endl;
cout<<"  |           3.- Visualizar m�xima y m�nima temperatura                     |"<<endl;
cout<<"  |--------------------------------------------------------------------------|"<<endl;
cout<<endl<<endl;
cin>>opcion;
/////////----ERROR ANTE SELECCI�N DE OPCI�N INCORRECTA----
if (opcion!=0 && opcion!=1 && opcion!=2 && opcion!=3)
    {
    system("cls");// para limpiar pantalla.
    cout<<endl;
    cout<<"ERROR-- OPCION INCORRECTA"<< endl;
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
       cout<<"  |---------------------------------------|"<<endl;
       cout<<"  |--opcion.-1.-Visualizacion de datos:---|"<<endl;
       imprimir(cabeza);
       volver_al_menu();
    break;
    //////////--------INGRESAR NUEVO DATO----------
    case (2):
        system("cls");
        cout<<"  |---------------------------------------|"<<endl;
        cout<<"  |  opcion.-2.- Ingresar nueva lectura   |"<<endl;
        cout<<"  |---------------------------------------|"<<endl;
        /////---BORRADO DE DATO ANTES DE INGRESAR EL NUEVO VALOR---
        borrar(cabeza , temperatura_m , tiempo_m);
        ////---INGRESAR NUEVO VALOR--------
        excepcion(tiempo_m); // Llamada a funci�n excepci�n
        cout<<"     Ingrese temperatura:  "<<endl;
        cin >>     temperatura_m;
       insertar(cabeza,temperatura_m ,tiempo_m);
       imprimir(cabeza);
       volver_al_menu();
    break;
    //////////-------M�XIMA Y M�NIMA TEMPERATURA---
    case (3):
        system("cls");
        cout<<"  |-------------------------------------------------|"<<endl;
        cout<<"  |     opcion.-3.temperatura m�xima y m�nima       |"<<endl;
        cout<<"  |-------------------------------------------------|"<<endl;
       imprimir(cabeza);
       mayor_menor ();
       volver_al_menu();
    break;
}
}

///////////////////--------------FUNCI�N IMPRIMIR - Lista enlazada
void imprimir (nodo *cab)

{
    int i=0;
    cout <<"  |---------------------------------------|"<< endl;
    cout <<"  |  temperatura (C)  ||   tiempo (seg)   |" <<endl;
    while(cab!=NULL)//Mientras el puntero que apunta a la cabeza de la cola sea distinto del que apunta al final.
    {
    cola_temperatura[i]=cab->temperatura;//Se introduce los valores de temperatura en el vector.
    cout <<"  |      "<<cab->temperatura << "        ||    " << cab->tiempo <<"    |"<< endl;//Se sacan por pantalla cada valor en cada iteracion.
    cab=cab->sig;//El puntero cabeza pasa a apuntar al siguiente objeto
    i++;
    }
}
//////////////////---------------FUNCI�N: SELECCI�N DE MAYOR Y MENOR VALOR DE T�
void mayor_menor ()
{
double mayor=0;
double menor=10000000000000;
for(int i1=0;i1<10;i1++)//recorremos vector y comparamos valores
     {
        if(cola_temperatura[i1]>mayor)
        {
            mayor=cola_temperatura[i1];
        }
        if(cola_temperatura[i1]<menor)
        {
            menor=cola_temperatura[i1];
        }
     }
    cout<<"  |---------------------------------------|"<<endl;
    cout<<"     La mayor temperatura es de: "<< mayor << endl<<endl;
    cout<<"     La menor temperatura es de: "<< menor << endl;
}

/////////////////----------------FUNCI�N: INSERTA VALORES EN LISTA ENLAZADA:NODO
void insertar(nodo* &cab, double temperatura ,int tiempo)
{
    nodo *nuevo;
    nodo *actual;
    nodo *anterior;

    nuevo =new nodo;//Se reserva memoria din�mica para nuevo.
    nuevo->temperatura=temperatura;//nuevo nodo
    nuevo->tiempo=tiempo;// Nuevo nodo
    actual=cab;
    anterior=NULL;
    if (cab==NULL)// En el caso de que la lista este vacia
    {
        cab=nuevo;
        nuevo->sig=NULL;
    }
    else //Navegamos hasta que lleguemos al lugar donde insertar el nuevo dato
        {
            while (actual!=NULL  )
            {
                anterior=actual;
                actual=actual->sig;
            }
            if(anterior==NULL)
            {
                cab=nuevo;
                nuevo->sig=actual;
            }
            else
            {
                anterior->sig=nuevo;
            }
}
            nuevo->sig=actual;
}
/////////////////----------------FUNCI�N:BORRA DATO
int borrar(nodo* &cab,double temperatura, int tiempo)
{
    nodo *actual;
    nodo *anterior;
    if (cab==NULL)//Si la lista esta vac�a no se hace nada
    {
        cout<<"la lista esta vacia"<<endl;
        return 0;
    }
    if (cab->tiempo=tiempo)// como se debe borrar el primer elemento que el puntero cabeza apunte al siguiente dato.
    {
        actual=cab;
        cab=cab->sig;
        delete actual;
        return 1;
    }
    anterior=cab;
    actual=cab->sig;
   while(actual!=NULL && actual->tiempo< tiempo)//se navega hasta encontrar el dato que se quiere borrar.
        {
        anterior=actual;
        actual=actual->sig;
        }
     if(actual==NULL)
            return 0;
     else
        {
        if(actual->tiempo==tiempo)
        {
            anterior->sig=actual->sig;
            delete actual;
            return 1;
        }else
        return 0;
     }
}
////////////////----------------FUNCI�N: VOLVER AL MEN�
void volver_al_menu()
{
    int cont;
    cout<<"  |---------------------------------------|"<<endl;
    cout<<"Presione 1 para volver al men�- En Caso contrario sale del sistema"<<endl;
    cin>>cont;
    if (cont==1)
      {system("cls");
        menu();}
}
////////////////---------------FUNCI�N : EXCEPCI�N- MANEJO DE NUEVO VALOR TIEMPO- Solo permite ingresar n�meros
void excepcion( int numero_aux)
{
char Cadena[20];/// Declarar un Char para capturar los datos
int iex;  /// iex para contador
bool Error=false;
do{
iex=0;
    try{
        cout<<"     Ingresar tiempo:"<<endl;
         cin>>     Cadena;///pedir datos por teclado
    while (Cadena[iex])///recorre desde la primera posici�n hasta la �ltima
        {
     if (isalpha(Cadena[iex]))///isalpha funci�n que analiza si el car�cter es alfab�tico
     {throw Cadena[iex];}///si existe un car�cter alfab�tico, controlamos el error
            iex++;            /// Contador incrementa en 1
        }
      Error=false; // si no hay caracteres alfab�ticos entonces el error es falso
       }
    catch (char)
    {
    Error=true;
    cout<<"El tiempo Ingresado no es correcto, por favor ingresa otro numero: "<<endl;
    }
}while(Error==true);
numero_aux= atoi(Cadena); ///atoi  funci�n que convierte una cadena a numero
}

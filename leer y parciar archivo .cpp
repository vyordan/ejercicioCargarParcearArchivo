#include <iostream>
#include <fstream>  //para manipular archivos
#include <string.h> //para operar las cadenas de caracteres
#include <stdexcept> //para manejar los errores
using namespace std;

struct vendedor
{
    int idVendedor;
    string nombreVendedor;
    int mesVenta;
    int anioVenta;
    double montoVenta; 
};

//procedimientos y funciones para leer el archivo y llenar el arreglo
void cargarDatos(vendedor[], int);           //recibe el vector para llenarlo, tambien recibe el tama;o de este
void parcearDatos(string, vendedor[], int&);  //va recibir un estring que va parcear y cada token se lo va asignar a campo que le corresponde
string bloques(string, int&);                //este recibe el string y va retornar un token (el toquen que retorne es el que parcearDatos asigna)

//funciones para operar los datos del arreglo
void imprimirVendedor(vendedor);
void imprimirDatosVendedor(vendedor[], int, int, string);
double sumaVentas(vendedor[], int, int, int);
float promedioVentas(vendedor[], int, int, int);
vendedor vendedorMayorVentas(vendedor[], int, int);
vendedor vendedorMenorVentas(vendedor[], int, int);

int main(){
    const int vendedoresTotales= 5000;
    vendedor vendedores[vendedoresTotales];
    
    cargarDatos(vendedores, vendedoresTotales);
    cout<<fixed; //para que apartir de aqui no imprima en notacion cientifica
    //MENU
    imprimirVendedor(vendedorMayorVentas(vendedores, vendedoresTotales, 0));
    imprimirDatosVendedor(vendedores, vendedoresTotales, 66, "Marta Díaz");

    return(0);
}

void cargarDatos(vendedor vendedores[], int vendedoresTotales){
    ifstream archivo; 
    string direccionArchivo = "datos2025.csv";
    archivo.open(direccionArchivo, ios::in);
    
    if (archivo.fail())
    {
        cout<<"--ERROR-- No se pudo abrir el archivo."<<endl;
        exit(1);
    }
    
    int indiceVendedor = 0;
    string texto;
    
    while (!archivo.eof() && indiceVendedor < vendedoresTotales)
    {
        getline(archivo, texto);
        parcearDatos(texto, vendedores, indiceVendedor);
    }
    archivo.close();
    cout<<"Datos cargados"<<endl;
}
void parcearDatos(string datos, vendedor vendedores[], int &indiceVendedor){
    int indice = 0; 
    try  //para menejar excepciones y errores
    {
        vendedores[indiceVendedor].idVendedor = stoi(bloques(datos, indice));
        vendedores[indiceVendedor].nombreVendedor = bloques(datos, indice);
        vendedores[indiceVendedor].mesVenta = stoi(bloques(datos, indice));
        vendedores[indiceVendedor].anioVenta = stoi(bloques(datos, indice));
        vendedores[indiceVendedor].montoVenta = stod(bloques(datos, indice)); 
        indiceVendedor++;
    }
    catch(...)
    {
        cout<<"--ERROR--\nNo se pueden asignar los datos: "<<datos<<endl<<endl;
    }
}
string bloques(string datos, int& indice){
    string bloque;
    while ((datos[indice] != ',') && (datos[indice] != '\0'))
    {
        bloque += datos[indice];
        indice++;
    }
    indice++;
    return bloque;
}

double sumaVentas(vendedor vendedores[] ,int totalVendedores, int id, int anio){
    double totalVentas = 0;
    for (int i = 0; i < totalVendedores; i++)
    {
        if ((vendedores[i].anioVenta == anio) || (anio == 0))
        {
            if ((vendedores[i].idVendedor == id) || (id == 0))
            {
                totalVentas += vendedores[i].montoVenta;
            }
        }
    }
    return totalVentas;
}
vendedor vendedorMayorVentas(vendedor vendedores[], int totalVendedores, int anio){
    vendedor mayoresVentas = vendedores[0];
    for (int i = 0; i < totalVendedores; i++)
    {
        if ((vendedores[i].anioVenta == anio) || (anio == 0))
        {
            if (mayoresVentas.montoVenta < vendedores[i].montoVenta)
            {
                mayoresVentas = vendedores[i];
            }
        }
    }
    return mayoresVentas;
}
vendedor vendedorMenorVentas(vendedor vendedores[], int totalVendedores, int anio){
    vendedor menoresVentas = vendedores[0];
    for (int i = 0; i < totalVendedores; i++)
    {
        if ((vendedores[i].anioVenta == anio) || (anio == 0))
        {
            if (menoresVentas.montoVenta > vendedores[i].montoVenta)
            {
                menoresVentas = vendedores[i];
            }
        }
    }
    return menoresVentas;
}
float promedioVentas(vendedor vendedores[], int totalVendedores, int id, int anio){
    double totalVentas = 0;
    int divisor = 0;
    for (int i = 0; i < totalVendedores; i++)
    {
        if ((vendedores[i].anioVenta == anio) || (anio == 0))
        {
            if ((vendedores[i].idVendedor == id) || (id == 0))
            {
                totalVentas += vendedores[i].montoVenta;
                divisor++;
            }
        }
    }
    return (totalVentas / divisor);
}
void imprimirDatosVendedor(vendedor vendedores[], int totalVendedores, int id, string nombre){
    int indicePrimero = -1;
    for (int i = 0; i < totalVendedores; i++)
    {
        if ((vendedores[i].idVendedor == id) && (vendedores[i].nombreVendedor == nombre))
        {
            indicePrimero = i;
            break;
        }
    }
    cout<<"-----------Datos-----------"<<endl;
    cout<<"ID:      "<<vendedores[indicePrimero].idVendedor<<endl;
    cout<<"Nombre:  "<<vendedores[indicePrimero].nombreVendedor<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"Mes\t|Anio\t|Total_Venta"<<endl;
    cout<<"----------------------------"<<endl;
    for (int i = indicePrimero; i < totalVendedores; i++)
    {
        if ((vendedores[i].idVendedor == id) && (vendedores[i].nombreVendedor == nombre))
        {
            cout<<vendedores[i].mesVenta<<"\t|"<<vendedores[i].anioVenta<<"\t|"<<vendedores[i].montoVenta<<endl;
            cout<<"----------------------------"<<endl;
        }
    }
    cout<<"El total de sus ventas es: "<<sumaVentas(vendedores, totalVendedores, id, 0)<<endl;
    cout<<"----------------------------"<<endl;
    if (indicePrimero == (-1))
    {
        cout<<"El usuario no fue encontrado\nNota: recuerde que el id y el nombre deben de coincidir ambos."<<endl;
    }
}

void imprimirVendedor(vendedor vendedores){
    cout<<"-----------Datos-----------"<<endl;
    cout<<"ID:      "<<vendedores.idVendedor<<endl;
    cout<<"Nombre:  "<<vendedores.nombreVendedor<<endl;
    cout<<"----------------------------"<<endl;
    cout<<"Mes\t|Anio\t|Total_Venta"<<endl;
    cout<<vendedores.mesVenta<<"\t|"<<vendedores.anioVenta<<"\t|"<<vendedores.montoVenta<<endl;
    cout<<"----------------------------"<<endl;
}

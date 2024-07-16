#include<cstdlib>
#include<fstream>
#include<string>
#include <iostream>
#include<cmath>
#include<iomanip>

using namespace std;

const int MAX_SUB = 24;

typedef struct {

    int mili_i=0;
    int mili_f=0;
    string texto;
    int desajuste=0;
} tSub;

typedef tSub tArray[MAX_SUB];

typedef struct {

    string duracion_i;
    string duracion_f;
    string texto;
} tSubI;

typedef tSubI tArrayI[MAX_SUB];

//prototipos
void cargar(tArrayI& lista_subi);
void toMilisegundos(tArrayI& lista_subi, tArray& lista_sub);
void desajuste(tArray& lista_sub);
void mostrar(tArray& lista_sub);
void cambiar(tArray& lista_sub);
bool buscarmili(tArray& lista_sub, int& mili);
void buscar(tArray& lista_sub);
void guardar(tArray& lista_sub);
int menu();

int main()
{
    system("chcp 1252");
    ifstream archivo;
    tSub sub;
    tArray lista_sub;
    tArrayI lista_subi;
    int op;
    toMilisegundos(lista_subi, lista_sub);
    desajuste(lista_sub);
    op = menu();
    while (op != 5)
    {
        switch (op)
        {

        case 1:
        {
            mostrar(lista_sub);
            system("pause");
            system("cls");
        }
        break;

        case 2:
        {
            cambiar(lista_sub);
            system("pause");
            system("cls");
        }
        break;

        case 3:
        {   buscar(lista_sub);
            system("pause");
            system("cls");


        }
        break;

        case 4:
        {   
            guardar(lista_sub);
            system("pause");
            system("cls");
            return 0;
        }
        break;
        }
        op = menu();
    }
   
}



void cargar(tArrayI& lista_subi)
{
    ifstream archivo_1;
    tSubI sub1;
    int i = 0;
    archivo_1.open("n.txt");
    if (archivo_1.is_open())
    {
        while(i<MAX_SUB && !archivo_1.eof())
        {
            archivo_1 >> lista_subi[i].duracion_i;
            archivo_1 >> lista_subi[i].duracion_f;
            getline(archivo_1, lista_subi[i].texto);
            i++;
        }
    }
    else
    {
        cout << "el archivo no se encontro";
    }
}

void toMilisegundos(tArrayI& lista_subi,tArray& lista_sub)
{ 
    ifstream archivo_1;
    short int horai, mini, segi, milii,horaf,minf,segf,milif,i=0;
    cargar(lista_subi);
    archivo_1.open("n.txt");
    if (archivo_1.is_open())
    {
        while (i < MAX_SUB && lista_subi[i].duracion_i!="Fin")
        {
           
            horai = stoi(lista_subi[i].duracion_i.substr(0, 2));
            mini = stoi(lista_subi[i].duracion_i.substr(3, 2));
            segi = stoi(lista_subi[i].duracion_i.substr(6, 2));
            milii = stoi(lista_subi[i].duracion_i.substr(9, 3));
            lista_sub[i].mili_i = (horai * 3600000) + (mini * 60000) + (segi * 1000) + milii;
          
            horaf = stoi(lista_subi[i].duracion_f.substr(0, 2));
            minf = stoi(lista_subi[i].duracion_f.substr(3, 2));
            segf = stoi(lista_subi[i].duracion_f.substr(6, 2));
            milif = stoi(lista_subi[i].duracion_f.substr(9, 3));
            lista_sub[i].mili_f = (horaf * 3600000) + (minf * 60000) + (segf * 1000) + milif;
            lista_sub[i].texto = lista_subi[i].texto;
           
            i++;
           
        }

    }
    else
    {
        cout << "el archivo no se encontro";
    }

}

void desajuste(tArray& lista_sub)
{
    int desajuste,tamaño;
    
    for (int i = 0; i < MAX_SUB; i++)
    {
        desajuste = (lista_sub[i].mili_f - lista_sub[i].mili_i) / 50;
        tamaño = lista_sub[i].texto.size();
        lista_sub[i].desajuste = tamaño - desajuste;
        
    }
}

void mostrar(tArray& lista_sub)
{
    int i = 0;
    while (i < MAX_SUB && lista_sub[i].mili_i != 0)
    {
        cout << "intervalo: " << lista_sub[i].mili_i << " -->" << lista_sub[i].mili_f << endl;
        cout << "texto: " << lista_sub[i].texto << endl;
        i++;
    }

}
void cambiar(tArray& lista_sub)
{
    int pocision;
    string nuevo;
    cout<<"¿en cual posicion quisiseras cambiar en texto? " << endl;
    cin >> pocision;
    if (lista_sub[pocision].mili_i == 0|| pocision>23)
    {
        cout<<"la posicion no es valida " << endl;
        system("pause");
        system("cls");
    }
    else
    {
        cout << "escriba el nuevo texto: " << endl;
        cin.ignore();
        getline(cin, nuevo);
        lista_sub[pocision].texto = nuevo;
        cout << "se cambio correctamente" << endl;
    }

}
void buscar(tArray& lista_sub)
{
    int mili=0,i=0;
    bool encontrado;
    cout << "¿cual instante quisieras ver?" << endl;
    cin >> mili;
    cout << endl;
    encontrado = buscarmili(lista_sub, mili);
    if (encontrado == true)
    {
        while (i < MAX_SUB && lista_sub[i].mili_i != 0)
        {
            if (mili >= lista_sub[i].mili_i && mili <= lista_sub[i].mili_f)
            {
                cout << "Milisegundos: " << mili << endl;
                cout << "encontrado en la pocision: " << i << endl;
                cout << "Intervalo: " << lista_sub[i].mili_i << "-->" << lista_sub[i].mili_f << endl;
                cout << "Texto: " << lista_sub[i].texto << endl;
                if (lista_sub[i].desajuste <= 0)
                {
                    cout << "Desajuste: 0"<<endl;
                }
                else
                {
                    cout << "Desajuste: " << lista_sub[i].desajuste << endl;
                }
            }
            i++;
        }
 
    }
    else
    {
        cout << "Milisegundos: " << mili << endl;
        cout << "No encontrado" << endl;
   
    }



}
bool buscarmili(tArray& lista_sub,int& mili)
{
    int i=0;
    bool encontrado=false;
    while (i < MAX_SUB && lista_sub[i].mili_i != 0 && encontrado !=true)
    {
        if (mili >= lista_sub[i].mili_i && mili <= lista_sub[i].mili_f)
        {
            encontrado = true;
        }
        else
        {
            encontrado = false;
        }

        i++;
    }

    return encontrado;
}

void guardar(tArray& lista_sub)
{
    ofstream archivo;
    int  i = 0;
    archivo.open("subtitulosEX.txt");
    if (archivo.is_open())
    {
        while (i < MAX_SUB && lista_sub[i].mili_i != 0)
        {
            archivo << lista_sub[i].mili_i << " " << lista_sub[i].mili_f << " " << lista_sub[i].texto << endl;
            i++;
        }
        archivo.close();
        cout << "se ha guardado correctamente" << endl;
    }
    else
    {
        cout << "no se pudo abrir el archivo" << endl;
    }
}

int menu()
{
    int op=-1;
    while ((op < 0) || (op > 5))
    {
        cout << "1-mostrar lista"<<endl;
        cout << "2-cambiar texto" << endl;
        cout << "3-buscar subtitulo" << endl;
        cout << "4-salir" << endl;
        cout << "Opcion  " << endl;
        cin >> op;
        if ((op < 0) || (op > 5))
        {
            cout << "opcion no valida";
        }
    }

    return op;
}


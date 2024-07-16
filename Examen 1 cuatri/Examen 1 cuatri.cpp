#include <iostream>
#include <fstream>
#include <iomanip>
#include <string>
using namespace std;

typedef enum {
    Fis, Mat, Inf
}tArea;
typedef struct {
    tArea area;
    int numpag;
    string titulo;
}tLibro;
typedef struct {
    tLibro libros[100];
    int cont;
}tListaLibros;
typedef struct {
    tArea areaEst;
    tListaLibros lista;
    int cap;
    int numpagEst;
}tEstanteria;
typedef struct {
    tEstanteria est[15];
    int cont;
}tBiblioteca;

tArea strToArea(string str);
bool cargarEstanterias(tBiblioteca& biblioteca);
bool cargarLibros(tListaLibros& listaLibros);
void borrarLibro(tListaLibros& listaLibros, int indice);
tLibro mayor(tListaLibros& listaLibros);
int buscarEstanteria(const tBiblioteca& biblioteca, tLibro libro);
void asignar(tBiblioteca& biblioteca, tListaLibros listaLibros, tListaLibros& sinColocar);
string areaToStr(tArea area);
void mostrarLibros(const tListaLibros& listaLibros);
void mostrarBiblioteca(const tBiblioteca& biblioteca);

int main(){
    tBiblioteca biblioteca;
    tListaLibros listaLibros, sinColocar;
    char aux;
    if (!cargarEstanterias(biblioteca)) {
        cout << "No se ha podido cargar la biblioteca." << endl;
        system("PAUSE");
        return 0;
    }
    else if (!cargarLibros(listaLibros)) {
        cout << "No se ha podido cargar la lista de libros." << endl;
        system("PAUSE");
        return 0;
    }
    else {
        cout << "Biblioteca y lista de libros cargada con exito." << endl;
        cout << "A continuacion se van a ordenar los libros. Pulse cualquier tecla para continuar:";
        cin >> aux;
        system("cls");
    }
    asignar(biblioteca, listaLibros, sinColocar);
    mostrarBiblioteca(biblioteca);


}

tArea strToArea(string str) {
    if (str == "Fis") {
        return Fis;
    }
    else if (str == "Mat") {
        return Mat;
    }
    else if (str == "Inf") {
        return Inf;
    }
}

bool cargarEstanterias(tBiblioteca &biblioteca) {
    ifstream archivo;
    archivo.open("biblioteca.txt");
    if (archivo.is_open()) {
        archivo >> biblioteca.cont;
        int n = 0, p = biblioteca.cont;
        string area;
        while (p != 0) {
            archivo >> area;
            biblioteca.est[n].areaEst = strToArea(area);
            archivo >> biblioteca.est[n].cap;
            biblioteca.est[n].numpagEst = biblioteca.est[n].cap;
            n++;
            p--;
        }
        archivo.close();
        return true;
    }
    else {
        return false;
    }
}
bool cargarLibros(tListaLibros &listaLibros) {
    ifstream archivo;
    listaLibros.cont = 0;
    archivo.open("libros.txt");
    if (archivo.is_open()) {
        string area;
        archivo >> area;
        while (area != "XXX"){
            listaLibros.libros[listaLibros.cont].area = strToArea(area);
            archivo >> listaLibros.libros[listaLibros.cont].numpag;
            getline(archivo, listaLibros.libros[listaLibros.cont].titulo);
            listaLibros.cont++;
            archivo >> area;
        }
        archivo.close();
        return true;
    }
    else {
        return false;
    }
}
void borrarLibro(tListaLibros &listaLibros, int indice) { 
    for (int i = indice ; i <= listaLibros.cont; i++) {
        listaLibros.libros[i].area = listaLibros.libros[i + 1].area;
        listaLibros.libros[i].numpag = listaLibros.libros[i + 1].numpag;
        listaLibros.libros[i].titulo = listaLibros.libros[i + 1].titulo;
    }
    listaLibros.cont--;
}
tLibro mayor(tListaLibros &listaLibros) {
    tLibro mayor;
    int indice = 0;
    int mayorn = 0;
    for (int i = 0; i <= listaLibros.cont; i++) {
        if (mayorn <= listaLibros.libros[i + 1].numpag){
            mayorn = listaLibros.libros[i + 1].numpag;
            mayor = listaLibros.libros[i + 1];
            indice = i + 1;
        }
    }
    borrarLibro(listaLibros, indice);
    return mayor;
}
int buscarEstanteria(const tBiblioteca &biblioteca, tLibro libro) {
    for (int i = 0; i < biblioteca.cont; i++) {
        if (biblioteca.est[i].areaEst == libro.area && biblioteca.est[i].numpagEst >= libro.numpag){
            return i;
        }
    }
    return -1;
}
void asignar(tBiblioteca &biblioteca, tListaLibros listaLibros, tListaLibros &sinColocar) {
    tLibro libro;
    int pos = -1;
    sinColocar.cont = 0;
    for (int i = 0; i < biblioteca.cont; i++) {
        biblioteca.est[i].lista.cont = 0;
    }
    for (int i = listaLibros.cont; i > 0; i--) {
        libro = mayor(listaLibros);
        pos = buscarEstanteria(biblioteca, libro);
        if (pos == -1) {
            sinColocar.libros[sinColocar.cont] = libro;
            sinColocar.cont++;
        }
        else if (pos > -1) {
            biblioteca.est[pos].lista.libros[biblioteca.est[pos].lista.cont] = libro;
            biblioteca.est[pos].numpagEst -= libro.numpag;
            biblioteca.est[pos].lista.cont++;
        }
    }
}
string areaToStr(tArea area) {
    if (area == Fis) {
        return "Fisica";
    }
    else if (area == Mat) {
        return "Matematicas";
    }
    else if (area == Inf) {
        return "Informatica";
    }
}
void mostrarLibros(const tListaLibros &listaLibros) {
    int i = 0;
    while ( i < listaLibros.cont) {
        cout << listaLibros.libros[i].titulo << " (" << listaLibros.libros[i].numpag << " paginas)" << endl;
        i++;
    }
}
void mostrarBiblioteca(const tBiblioteca& biblioteca) {
    int i = 0, a = 1;
    while ( i < biblioteca.cont) {
        if (biblioteca.est[i].areaEst == Mat) {
            cout << areaToStr(biblioteca.est[i].areaEst) << " - " << a << " (" << biblioteca.est[i].cap << "/" << biblioteca.est[i].numpagEst << ")" << endl;
            mostrarLibros(biblioteca.est[i].lista);
            a++;
        }
        i++;
    }
    int j = 0;
    a = 1;
    while (j < biblioteca.cont) {
        if (biblioteca.est[j].areaEst == Inf) {
            cout << areaToStr(biblioteca.est[j].areaEst) << " - " << a << " (" << biblioteca.est[j].cap << "/" << biblioteca.est[j].numpagEst << ")" << endl;
            mostrarLibros(biblioteca.est[j].lista);
            a++;
        }
        j++;
    }
    int x = 0;
    a = 1;
    while (x < biblioteca.cont) {
        if (biblioteca.est[x].areaEst == Fis) {
            cout << areaToStr(biblioteca.est[x].areaEst) << " - " << a << " (" << biblioteca.est[x].cap << "/" << biblioteca.est[x].numpagEst << ")" << endl;
            mostrarLibros(biblioteca.est[x].lista);
            a++;
        }
        x++;
    }
}
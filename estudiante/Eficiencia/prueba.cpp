// Fichero: test.cpp
// Baraja o desbaraja varias imagenes PGM
//

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main(int argc, char *argv[]){
    clock_t ti, tf;
    char *origen, *destino; // nombres de los ficheros
    Image image;

    // Comprobar validez de la llamada
    if (argc != 3){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: subimagen <FichImagenOriginal> <FichImagenDestino> \n";
        exit(1);
    }

    // Obtener argumentos
    origen = argv[1];
    destino = argv[2];

    // Leer la imagen del fichero de entrada
    if (!image.Load(origen)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Barajamos las imagenes
    ti = clock();
    image.ShuffleRows();
    tf = clock();
    cout << (tf - ti)/(double)CLOCKS_PER_SEC  << "\t" << image.size() << endl;
    // Guardar la imagen resultado en el fichero
    image.Save(destino);

    return 0;
}

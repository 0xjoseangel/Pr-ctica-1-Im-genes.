#include <iostream>
#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main(int argc, char *argv[]){

    char *origen, *destino; // nombres de los ficheros
    int factor;
    Image image, icono;

    // Comprobar validez de la llamada
    if (argc != 4){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: icono <FichImagenOriginal> <FichImagenDestino> <Factor de Reducción>\n";
        cerr << "Siendo el factor menor que el ancho y el alto que el tamaño de la imagen original \n";
        cerr << "y mayor que 0. \n";
    }

    // Obtener argumentos
    origen = argv[1];
    destino = argv[2];
    factor = atoi(argv[3]);

    // Leer la imagen del fichero de entrada
    if (!image.Load(origen)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << origen << endl;
    cout << "Fichero resultado: " << destino << endl;
    cout << "Factor de reducción de la imagen original con respecto al icono: ";
    cout << factor << endl;

    // Mostrar los parametros de la Imagen
    cout << endl;
    cout << "Dimensiones de " << origen << ":" << endl;
    cout << "   Imagen   = " << image.get_rows() << " filas x " << image.get_cols() << " columnas " << endl;

    // Generamos el icono
    icono = image.Subsample(factor);
    
    // Guardar la imagen resultado en el fichero
    if (icono.Save(destino))
        cout << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    return 0;
}
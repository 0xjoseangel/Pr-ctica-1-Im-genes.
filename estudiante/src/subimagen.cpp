/**
 * @file subimagen.cpp
 * @author your name (you@domain.com)
 * @brief 
 * @version 0.1
 * @date 2023-10-21
 * 
 * @copyright Copyright (c) 2023
 * 
 */

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main(int argc, char *argv[]){

    char *origen, *destino; // nombres de los ficheros
    int nrow, ncol, height, width;
    Image image, imageRecortada;

    // Comprobar validez de la llamada
    if (argc != 7){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: subimagen <FichImagenOriginal> <FichImagenDestino> <fila> <col> <filas_sub> <cols_sub>\n";
        exit(1);
    }

    // Obtener argumentos
    origen = argv[1];
    destino = argv[2];
    nrow = atoi(argv[3]);
    ncol = atoi(argv[4]);
    height = atoi(argv[5]);
    width = atoi(argv[6]);

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << origen << endl;
    cout << "Fichero resultado: " << destino << endl;
    cout << "Fila inicial para recortar: " << nrow << endl;
    cout << "Columna inicial para recortar: " << ncol << endl;
    cout << "Numero de filas de la subimagen: " << height << endl;
    cout << "Numero de columnas de la subimagen: " << width << endl;

    // Leer la imagen del fichero de entrada
    if (!image.Load(origen)){
        cerr << "Error: No pudo leerse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    // Mostrar los parametros de la Imagen
    cout << endl;
    cout << "Dimensiones de " << origen << ":" << endl;
    cout << "   Imagen   = " << image.get_rows() << " filas x " << image.get_cols() << " columnas " << endl;

    // Generamos la imagen recortada
    imageRecortada = image.Crop(nrow, ncol, height, width);
    
    // Guardar la imagen resultado en el fichero
    if (imageRecortada.Save(destino))
        cout << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    return 0;
}

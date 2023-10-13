// Fichero: contraste.cpp
// Modifica el contraste de una imagen PGM
//

#include <iostream>
#include <cstring>
#include <cstdlib>

#include <image.h>

using namespace std;

int main(int argc, char *argv[]){

    char *origen, *destino; // nombres de los ficheros
    byte in1, in2, out1, out2;
    Image image;

    // Comprobar validez de la llamada
    if (argc != 7){
        cerr << "Error: Numero incorrecto de parametros.\n";
        cerr << "Uso: contraste <FichImagenOriginal> <FichImagenDestino> <e1> <e2> <s1> <s2>\n";
        exit(1);
    }

    // Obtener argumentos
    origen = argv[1];
    destino = argv[2];
    in1 = atoi(argv[3]);
    in2 = atoi(argv[4]);
    out1 = atoi(argv[5]);
    out2 = atoi(argv[6]);

    // Mostramos argumentos
    cout << endl;
    cout << "Fichero origen: " << origen << endl;
    cout << "Fichero resultado: " << destino << endl;
    cout << "Umbral inferior entrada: " << in1 << endl;
    cout << "Umbral superior entrada: " << in2 << endl;
    cout << "Umbral inferior salida: " << out1 << endl;
    cout << "Umbral salida entrada: " << out2 << endl;

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

    // Cambiamos el contraste a la imagen
    image.AdjustContrast (in1, in2, out1, out2);
    
    // Guardar la imagen resultado en el fichero
    if (image.Save(destino))
        cout << "La imagen se guardo en " << destino << endl;
    else{
        cerr << "Error: No pudo guardarse la imagen." << endl;
        cerr << "Terminando la ejecucion del programa." << endl;
        return 1;
    }

    return 0;
}

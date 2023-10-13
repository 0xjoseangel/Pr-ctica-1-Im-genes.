/**
 * @file imageop.cpp
 * @brief Fichero con definiciones para el resto de métodos de la clase Image
 */

#include <iostream>
#include <cmath>
#include <image.h>

#include <cassert>

void Image::Invert()
{
    for (int i = 0; i < this->get_rows(); i++)
        for (int j = 0; j < this->get_cols(); j++)
            this->set_pixel(i, j, 255 - this->get_pixel(i, j));
}

void Image::AdjustContrast(byte in1, byte in2, byte out1, byte out2) {
    if (!this->Empty()) {
        byte invariante = (out2 - out1) / (in2 - in1);
        for (int i = 0; i < this->size(); i++)
            this->set_pixel(i, out1 + (invariante * (this->get_pixel(i))));
    }
}

Image Image::Crop(int nrow, int ncol, int height, int width) const {
    Image imagenRecortada(height, width);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Ajusrtamos los valores de i y j
            int originalRow = i + nrow;
            int originalCol = j + ncol;

            if (originalRow < this->get_rows() && originalCol < this->get_cols()) {
                int kRecortada = i * width + j;
                imagenRecortada.set_pixel(kRecortada, this->get_pixel(originalRow, originalCol));
            }
        }
    }

    return imagenRecortada;
}
// Revisar
Image Image::Zoom2X(int fil, int col, int lado) const {
    assert(fil+lado<this->get_rows() && col+lado<this->get_cols());

    Image SubImagen(this->Crop(fil, col, lado, lado));
    Image ImagenZoom(2*lado-1, 2*lado-1);

    // Se interpola sobre las columnas
    for (int i=0; i<ImagenZoom.get_rows(); i+=2) {
        for (int j=0; j<=ImagenZoom.get_cols(); j++) {
            if (j%2)
                ImagenZoom.set_pixel(i, j, SubImagen.get_pixel(i,j));
            else
                // Comprobamos que no sea el ultimo pixel de la columna
                if (j!=get_cols()-1)
                    ImagenZoom.set_pixel(i, j, (SubImagen.get_pixel(i,j-1) + SubImagen.get_pixel(i,j+1))/2);
                else
                    ImagenZoom.set_pixel(i, j, SubImagen.get_pixel(i,j));
            
        }
    }
    // Se interpola sobre las filas
    for (int i=0; i<ImagenZoom.get_rows(); i+=2) {
        for (int j=0; j<=ImagenZoom.get_cols(); j++) {
            if (j%2)
                ImagenZoom.set_pixel(j, i, SubImagen.get_pixel(j,i));
            else
                // Comprobamos que no sea el ultimo pixel de la fila
                if (j!=get_rows()-1)
                    ImagenZoom.set_pixel(j, i, (SubImagen.get_pixel(j,i-1) + SubImagen.get_pixel(j,i+1))/2);
                else
                    ImagenZoom.set_pixel(j, i, SubImagen.get_pixel(j,i));
            
        }
    }

    return ImagenZoom;
}
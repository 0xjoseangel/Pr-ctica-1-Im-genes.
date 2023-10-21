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

    int ladoNuevaImagen = 2*lado-1;
    Image ImagenZoom(ladoNuevaImagen, ladoNuevaImagen);
    
    int n = 0;
    for (int i = 0; i < ladoNuevaImagen; i++) {
        for (int j = 0; j < ladoNuevaImagen; j++) {    
            if (i%2 == 0 && j%2 == 0) 
                ImagenZoom.set_pixel(i,j,SubImagen.get_pixel(n++));
        }
    }
    for (int i = 0; i < ladoNuevaImagen; i++) {
        for (int j = 0; j < ladoNuevaImagen; j++) {    
            if (i%2 == 0 && j%2 != 0)
                ImagenZoom.set_pixel(i,j, (ImagenZoom.get_pixel(i,j-1) + ImagenZoom.get_pixel(i,j+1)) / 2);
            else if (i%2 != 0)
                ImagenZoom.set_pixel(i,j, (ImagenZoom.get_pixel(i-1,j) + ImagenZoom.get_pixel(i+1,j)) / 2);
        }
    }
    return ImagenZoom;
}

double Image::Mean(int i, int j, int height, int width) const {
    assert(i>height || j>width);
    Image SubImagen = this->Crop(i, j, height, width);

    int sum = 0;
    for (int i=0; i<SubImagen.get_rows()*SubImagen.get_cols(); i++) {
        sum += SubImagen.get_pixel(i);
    }
    return sum/(i<SubImagen.get_rows()*SubImagen.get_cols());
}

void Image::ShuffleRows() {
    const int p = 9973;
    Image temp(rows,cols);
    int newr;
    for (int r=0; r<rows; r++){
        newr = r*p % rows;
        for (int c=0; c<cols;c++)
            temp.set_pixel(r,c,get_pixel(newr,c));
    }
    Copy(temp);
}
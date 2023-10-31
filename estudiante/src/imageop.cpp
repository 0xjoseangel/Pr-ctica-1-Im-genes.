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
    for (int i = 0; i < this->size(); i++)
        this->set_pixel(i, 255 - this->get_pixel(i));
}

void Image::AdjustContrast(byte in1, byte in2, byte out1, byte out2) {
    double en1=in1, en2=in2, sa1=out1, sa2=out2;
    if (!this->Empty()) {
        double invariante = (sa2 - sa1) / (en2 - en1);
        for (int i = 0; i < this->size(); i++) {
            if (this->get_pixel(i) >= in1 && this->get_pixel(i) <= in2)
                this->set_pixel(i, round(sa1 + (invariante * (this->get_pixel(i)-en1))));
        }
    }
}

Image Image::Crop(int nrow, int ncol, int height, int width) const {
    assert((nrow + height) < this->get_rows() && (ncol + width) < this->get_cols());
    Image imagenRecortada(height, width);

    for (int i = 0; i < height; i++) {
        for (int j = 0; j < width; j++) {
            // Ajustamos los valores de i y j
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
    // Interpolacion horizontal
    for (int i = 0; i < ladoNuevaImagen; i+=2) {
        for (int j = 1; j < ladoNuevaImagen; j+=2) {    
            ImagenZoom.set_pixel(i,j, (ImagenZoom.get_pixel(i,j-1) + ImagenZoom.get_pixel(i,j+1)) / 2);
        }
    }
    // Interpolacion vertical
    for (int i = 1; i < ladoNuevaImagen; i+=2) {
        for (int j = 0; j < ladoNuevaImagen; j++) {    
            ImagenZoom.set_pixel(i,j, (ImagenZoom.get_pixel(i-1,j) + ImagenZoom.get_pixel(i+1,j)) / 2);
        }
    }

    return ImagenZoom;
}

double Image::Mean(int i, int j, int height, int width) const {
    assert((i + height) < this->get_rows() && (j + width) < this->get_cols());

    Image SubImagen = this->Crop(i, j, height, width);

    double sum = 0;
    for (int i=0; i<SubImagen.get_rows()*SubImagen.get_cols(); i++) {
        sum += SubImagen.get_pixel(i);
    }
    return sum/(SubImagen.get_rows()*SubImagen.get_cols());
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

Image Image::Subsample(int factor) const{
    assert(factor>0 && factor<=this->get_cols() && factor<=this->get_rows());
    
    int num_cols=this->get_cols()/factor;
    int num_filas=this->get_rows()/factor;
    Image icono(num_filas, num_cols);
    
    for (int i=0; i<num_filas; i++){
        for (int j=0; j<num_cols; j++){
            byte media=round(this->Mean(i*factor, j*factor, factor, factor));
            icono.set_pixel(i, j, media);
        }
    }
    return icono;
}
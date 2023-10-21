# Introducción
Practica realizada por Jesus Rodriguez y Jose Angel Carretero para la asignatura de Estructura de computadores del doble grado
en igenieria informatica y administracion y direccion de empresas.

# Ejecutables

## Negativo:

Calcula el negativo de una imagen

```
__negativo__ <FichImagenOriginal> <FichImagenDestino>
```

`FichImagenOriginal` Imagen PGM a la que se va a calcular

`FichImagenDestino` Imagen PGM resultado de calcular el negativo

## Contraste:

Cambia el contraste de una imagen

```
__contraste__ <FichImagenOriginal> <FichImagenDestino> <e1> <e2> <s1> <s2>
```

`FichImagenOriginal` Imagen PGM a la que se va a cambiar el contraste

`FichImagenDestino` Imagen PGM resultado de cambiar el contraste

`e1` Umbral inferior de la imagen de entrada

`e2` Umbral superior de la imagen de entrada

`s1` Umbral inferior de la imagen de salida

`s2` Umbral superior de la imagen de salida

## Subimagen:

Genera una subimagen a partir de otra

```
__submagen__ <FichImagenOriginal> <FichImagenDestino> <fila> <col> <filas_sub> \<cols_sub>
```

`FichImagenOriginal` Imagen PGM que se quiere recortar

`FichImagenDestino` Imagen PGM ya recortada

`fila` Fila inicial para recortar

`col` Columna inicial para recortar 

`filas_sub` Numero de filas

`cols_sub` Numero de columnas

## Barajar:

Baraja o desbaraja una imagen PGM

```
__barajar__ <FichImagenOriginal> <FichImagenDestino>
```

`<FichImagenOriginal>` Imagen PGM a ser barajada

`<FichImagenDestino>` Imagen PGM ya barajada

## Zoom:

Genera una imagen ampliada de otra

```
__suimagen__ <FichImagenOriginal> <FichImagenDestino> <fila> <col> <lado>
```

`<FichImagenOriginal>` Imagen PGM que se quiere recortar

`FichImagenDestino` Imagen PGM ya recortada

`fila` Fila de la subimagen que se va a ampliar

`col`  Fila de la subimagen que se va a ampliar 

`lado` Tamano del cuadrado

> :notebook: Para compilar el proyecto se debe de generar el makefile con el       comando`cmake CMakeLists.txt`. Tras esto, se habra generado el makefile para compilar todos los ejecutables de la practica ademas de el Doxyfile para poder generar la documentacion.




#include <iostream>
using namespace std;
#include "ProductosArchivo.h"
#include "Producto.h"
#include <string>

Producto ProductosArchivo::leer(int nroRegistro) {
    Producto prod{};// VER POR QUE PIDE LAS LLAVES PARA CORREGIR EL ERROR
    FILE* p;
    p = fopen("productos.dat", "rb");
    if (p == NULL) {
        return prod;
    }
    fseek(p, nroRegistro * sizeof(Producto), SEEK_SET);
    fread(&prod, sizeof(Producto), 1, p);
    fclose(p);
    return prod;
}

bool ProductosArchivo::leerTodos(Producto productos[], int cantidad) {
    FILE* p;
    p = fopen("productos.dat", "rb");
    if (p == NULL) {
        return false;
    }
    fread(productos, sizeof(Producto), cantidad, p);
    fclose(p);
    return true;
}

bool ProductosArchivo::guardar(Producto prod) {
    FILE* p = fopen("productos.dat", "ab");
    if (p == NULL) {
        return false;
    }
    bool ok = fwrite(&prod, sizeof(Producto), 1, p);
    fclose(p);
    return ok;
}

bool ProductosArchivo::guardar(Producto prod, int nroRegistro) {
    FILE* p = fopen("productos.dat", "rb+");
    if (p == NULL) {
        return false;
    }
    fseek(p, nroRegistro * sizeof(Producto), SEEK_SET);
    bool ok = fwrite(&prod, sizeof(Producto), 1, p);
    fclose(p);
    return ok;
}

int ProductosArchivo::getCantidad() {
    FILE* p = fopen("productos.dat", "rb");
    if (p == NULL) {
        return 0;
    }
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Producto);
    fclose(p);
    return cant;
}

int ProductosArchivo::buscar(int codProd) {
    int cant = getCantidad();
    Producto prod;
    for (int i = 0; i < cant; i++) {
        prod = leer(i);
        if (prod.getIdProd() == codProd) {
            return i;
        }
    }
    return -1;
}

void ProductosArchivo::mostrarArchivo()
{
    ProductosArchivo prodArc;
    int cantArchivos = prodArc.getCantidad();
    Producto* prod = new Producto[cantArchivos];
    prodArc.leerTodos(prod, cantArchivos);
    for (int x = 0; x < cantArchivos; x++)
    {
        prod[x].mostrar();
        cout << endl;
    }
}

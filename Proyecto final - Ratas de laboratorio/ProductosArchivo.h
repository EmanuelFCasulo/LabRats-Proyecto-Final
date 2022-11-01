#pragma once
#include "Producto.h"


class ProductosArchivo
{
public:
	Producto leer(int nroRegistro);
	bool leerTodos(Producto empleados[], int cantidad);
	bool guardar(Producto producto);
	bool guardar(Producto prod, int nroRegistro);//Edita un registro
	int getCantidad();
	int buscar(int cod);
	void mostrarArchivo();
};


#pragma once
#include "Empleado.h"


class EmpleadosArchivo
{
public:
	Empleado leer(int nroRegistro);
	bool leerTodos(Empleado empleados[], int cantidad);
	bool guardar(Empleado empleado);
	bool guardar(Empleado emp, int nroRegistro);
	int getCantidad();
	int buscar(int legajo);

	void mostrarArchivo();
	
};

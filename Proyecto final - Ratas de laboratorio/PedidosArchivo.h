#pragma once
#include "Pedido.h"

class PedidosArchivo
{
public:
	Pedido leer(int nroRegistro);
	bool leerTodos(Pedido pedidos[], int cantidad);
	bool guardar(Pedido pedido);
	bool guardar(Pedido ped, int nroRegistro);
	int getCantidad();
	int buscar(int legajo);

	void mostrarArchivo();
	
};


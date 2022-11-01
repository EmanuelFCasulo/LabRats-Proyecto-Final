#pragma once
#include "Empleado.h"
#include "Fecha.h"
#include <iostream>
using namespace std;
#include "Producto.h"

class Pedido
{
private:
	
	int _idPedido;
	int _legajo;
	int _idProducto;
	int _cantidadProducto;//Cantidad total de productos
	Fecha _fechaPedido;
	bool _cargado = false;
	char _tipoPedido[2];// I = INGRESO STOCK E= EGRESO STOCK C= CANCELADO

public:
	void cargar(int legajo);
	void mostrar();

	void setIdPedido(int idPedido);
	void setLegajo(int legajo);
	void setIdProducto(int idProducto);
	void setCantidadProducto(int cantidadProducto);
	void setFechaPedido(Fecha fechaPedido);
	void setEstadoPedido(bool cargado);//PARA VER SI EL PEDIDO FUE CARGADO EN EL SISTEMA O NO
	void setTipoPedido(const char* tipoPedido);

	int getIdPedido();
	int getLegajo();
	int getIdProducto();
	int getCantidadProducto();
	Fecha getFechaPedido();
	bool getEstadoPedido();//PARA VER SI EL PEDIDO FUE CARGADO EN EL SISTEMA O NO
	const char* getTipoPedido();
	
};


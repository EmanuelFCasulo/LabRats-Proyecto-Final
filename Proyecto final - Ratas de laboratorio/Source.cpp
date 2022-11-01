#include <iostream>
using namespace std;
#include "Producto.h"
#include "ProductosArchivo.h"
#include "Funciones.h"
#include "Empleado.h"
#include "EmpleadosArchivo.h"
#include "Domicilio.h"
#include "Pedido.h"
#include "PedidosArchivo.h"
#include "rlutil.h"



int main() {
	///Color de fondo y letra (SON COLORES DE PRUEBA, DESPUES ELEGIMOS CUAL DEJAMOS)
	rlutil::setColor(rlutil::CYAN);
	rlutil::setBackgroundColor(rlutil::BLACK);//PUSE BLACK POR QUE SI ES CYAN NO SE DISTINGUEN LOS OTROS COLORES
	
	menuPrincipal();
	
	//PedidosArchivo pedArc;
	//pedArc.mostrarArchivo();//Muestra el archivo de pedidos

	//Pedido pedido;
	//pedido.cargar(123);

	//EmpleadosArchivo empArc;
	//empArc.mostrarArchivo();//Muestra el archivo de empleados

	//ProductosArchivo prodArc;
	//prodArc.mostrarArchivo();//Muestra el archivo de productos

	//Producto prod;
	//prod.cargar();

	//EmpleadosArchivo ea;
	//Empleado e;
	//e.cargar();
	/*for (int x = 0; x < ea.getCantidad(); x++)
	{
		e = ea.leer(x);
		e.mostrar();
		cout << endl << endl;
	}*/

	//Domicilio e;
	//e.cargar();

	/*Producto prod;
	ProductosArchivo prodArc;
	prod.cargar();*/

  return 0;
}
//TODO: FALTA Como cargar muchos productos en un solo pedido y Como funciona el cin.ignore()
//TODO: ERROR AL MOSTRAR DE VEZ EN CUANDO ARCHIVO EMPPLEADO VER


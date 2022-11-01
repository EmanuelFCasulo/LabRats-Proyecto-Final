#include "Pedido.h"
#include "PedidosArchivo.h"
#include "rlutil.h"
#include "Funciones.h"
#include "Fecha.h"
#include "ProductosArchivo.h"
#include "Pedido.h"

enum opciones
{
	Opcion1 = 0,
	Opcion2 = 1,
	Opcion3 = 2,
	Opcion4 = 3,
	Opcion5 = 4,
	Opcion6 = 5,
	Opcion7 = 6,
	Opcion8 = 7,
	Opcion9 = 8
};

void Pedido::cargar(int legajo)
{
	bool repite = true;

	do
	{
		int cantidad = 50;
		PedidosArchivo parc;
		Pedido* p = new Pedido[cantidad];
		int pos = 0;
		int idPedido = 666;
		int idProducto;
		int cantidadProducto;
		Fecha fechaPedido;
		bool cargado;
		char tipoPedido[2];// I = INGRESO STOCK E= EGRESO STOCK C= CANCELADO
		bool repite = true;

		rlutil::cls();
		rlutil::setColor(rlutil::YELLOW);
		cout << "CARGA DE PEDIDOS - LAB RATS" << endl;
		cout << "=======================================================" << endl;
		rlutil::setColor(rlutil::CYAN);

		cargado = false;
		do
		{
			cin.ignore();
			rlutil::setColor(rlutil::CYAN);
			cout << endl << "Ingrese el tipo de pedido: ";
			rlutil::setColor(rlutil::WHITE);
			cin.getline(tipoPedido, 2, '\n');
			if (strcmp(tipoPedido, "e") != 0 && strcmp(tipoPedido, "i") != 0)
			{
				rlutil::setColor(rlutil::RED);
				cout << "Tipo de pedido invalido" << endl;
				rlutil::setColor(rlutil::CYAN);
				presioneUnaTecla();
				limpiarConsola();
			}
		} while (strcmp(tipoPedido, "e") != 0 && strcmp(tipoPedido, "i") != 0);

		rlutil::setColor(rlutil::CYAN);
		cout << endl << "Fecha del pedido :" << endl;
		rlutil::setColor(rlutil::WHITE);
		fechaPedido.cargar();

		int cargarOtro;

		
		do
		{
			bool existe = false;
			do {
				
				ProductosArchivo pArchAux;
				Producto prodAux;

				rlutil::setColor(rlutil::CYAN);
				cout << endl << "Ingrese ID producto: ";
				rlutil::setColor(rlutil::WHITE);
				cin >> idProducto;

				for (int x = 0; x < pArchAux.getCantidad(); x++)
				{
					prodAux = pArchAux.leer(x);

					if (prodAux.getIdProd() == idProducto)
					{
						existe = true;
					}
				}
				if (existe == false) {
					cout << "El ID de producto no existe, por favos ingrese un ID válido" << endl;
					presioneUnaTecla();
				}
			} while (existe != true);
			rlutil::setColor(rlutil::CYAN);
			cout << endl << "Unidades solicitadas: ";
			rlutil::setColor(rlutil::WHITE);
			cin >> cantidadProducto;
			//cin.ignore();

			/*cout << "Desea agregar otro producto al pedido? " << endl;
			cout << "1. SI" << endl;
			cout << "2. NO" << endl;
			cin >> cargarOtro;
			while (cargarOtro != 1 && cargarOtro != 2)
			{
				cout << "Opcion invalida, por favor seleccione una opcion valida: ";
				cin >> cargarOtro;
			}*/
			int op = 1;
			int y = 0;
			do
			{
				rlutil::setBackgroundColor(rlutil::BLACK);
				rlutil::setColor(rlutil::WHITE);
				rlutil::hidecursor();
				limpiarConsola();
				showItemEgreso("Desea agregar otro producto al pedido?", 30, 8, 0);
				showItemEgreso("==============================================", 30, 9, 0);
				showItemEgreso("- SI          ", 38, 11, y == Opcion1);
				showItemEgreso("- Cancelar    ", 38, 12, y == Opcion2);

				switch (rlutil::getkey())
				{
				case 14: // UP
					rlutil::locate(28, 10 + y);
					std::cout << " " << std::endl;
					y--;
					if (y < 0) {
						y = 0;
					}
					break;
				case 15: // DOWN
					rlutil::locate(28, 10 + y);
					std::cout << " " << std::endl;
					y++;
					if (y > 1) {
						y = 1;
					}
					break;
				case 1: // ENTER

					switch (y)
					{
					case 0:
						op = 0;
						break;
					case 1:
						op = 0;
						repite = false;
						break;
					}
				}

			} while (op != 0);

			p[pos].setIdPedido(idPedido);
			p[pos].setIdProducto(idProducto);
			p[pos].setCantidadProducto(cantidadProducto);
			p[pos].setFechaPedido(fechaPedido);
			p[pos].setEstadoPedido(cargado);
			p[pos].setTipoPedido(tipoPedido);
			p[pos].setLegajo(legajo);

			if (y == 0) {
				pos++;
			}
		} while (repite);

	

		//cout << "----------------------------------" << endl;

		//for (int i = 0; i <= pos; i++) {
		//	PedidosArchivo aux;
		//	Pedido pAux = aux.leer(i);
		//	pAux.mostrar();
		//}

		int op = 1;
		int y = 0;
		do
		{
			rlutil::setBackgroundColor(rlutil::BLACK);
			rlutil::setColor(rlutil::WHITE);
			rlutil::hidecursor();
			limpiarConsola();
			showItemEgreso("Desea guardar el pedido ingresado?", 30, 9, 0);
			showItemEgreso("- OK       ", 30, 11, y == Opcion1);
			showItemEgreso("- Cancelar ", 30, 12, y == Opcion2);

			switch (rlutil::getkey())
			{
			case 14: // UP
				rlutil::locate(28, 10 + y);
				std::cout << " " << std::endl;
				y--;
				if (y < 0) {
					y = 0;
				}
				break;
			case 15: // DOWN
				rlutil::locate(28, 10 + y);
				std::cout << " " << std::endl;
				y++;
				if (y > 1) {
					y = 1;
				}
				break;
			case 1: // ENTER

				switch (y)
				{
				case 0:
					op = 0;
					PedidosArchivo pedArc;
					for (int j = 0; j <= pos; j++) {
						pedArc.guardar(p[j]);
					}
					limpiarConsola();
					ubicar(27, 10);
					rlutil::setColor(rlutil::GREEN);
					cout << "Pedido cargado con exito" << endl;
					ubicar(27, 11);
					cout << "Tu ID de pedido es: " << p[0].getIdPedido();// falta agregar el id de pedido
					rlutil::setColor(rlutil::CYAN);
					presioneUnaTecla();
					limpiarConsola();
					delete[] p;
					break;
				case 1:
					op = 0;
					limpiarConsola();
					break;
				}
			}

		} while (op != 0);

		op = 1;
		y = 0;
		do
		{
			rlutil::setBackgroundColor(rlutil::BLACK);
			rlutil::setColor(rlutil::WHITE);
			rlutil::hidecursor();
			limpiarConsola();
			showItemEgreso("Desea CARGAR otro pedido?", 30, 9, 0);
			showItemEgreso("- OK       ", 38, 11, y == Opcion1);
			showItemEgreso("- Cancelar ", 38, 12, y == Opcion2);

			switch (rlutil::getkey())
			{
			case 14: // UP
				rlutil::locate(28, 10 + y);
				std::cout << " " << std::endl;
				y--;
				if (y < 0) {
					y = 0;
				}
				break;
			case 15: // DOWN
				rlutil::locate(28, 10 + y);
				std::cout << " " << std::endl;
				y++;
				if (y > 1) {
					y = 1;
				}
				break;
			case 1: // ENTER
				switch (y)
				{
				case 0:
					op = 0;
					break;
				case 1:
					op = 0;
					break;
				}
				break;
			}

		} while (op != 0);

		switch (y)
		{
		case 0:
			repite = true;
			break;
		case 1:
			repite = false;
			break;
		}
	}
	while (repite);

	presioneUnaTecla();
}


void Pedido::mostrar()
{
	cout << getIdPedido() << endl;
	cout << getLegajo() << endl;
	cout << getIdProducto() << endl;
	cout << getCantidadProducto() << endl;//Cantidad total de un producto
	_fechaPedido.mostrar();
}


void Pedido::setIdPedido(int idPedido)
{
	_idPedido = idPedido;
}



void Pedido::setLegajo(int legajo)
{
	_legajo = legajo;
}

void Pedido::setIdProducto(int idProducto)
{
	_idProducto = idProducto;
}

void Pedido::setFechaPedido(Fecha fechaPedido)
{
	_fechaPedido = fechaPedido;
}

void Pedido::setCantidadProducto(int cantidadProducto)
{
	_cantidadProducto = cantidadProducto;
}

int Pedido::getIdPedido()
{
	return _idPedido;
}

int Pedido::getLegajo()
{
	return _legajo;
}

int Pedido::getIdProducto()
{
	return _idProducto;
}

int Pedido::getCantidadProducto()
{
	return _cantidadProducto;
}

Fecha Pedido::getFechaPedido()
{
	return _fechaPedido;
}

bool Pedido::getEstadoPedido()
{
	return _cargado;
}

const char* Pedido::getTipoPedido()
{
	return _tipoPedido;
}

void Pedido::setEstadoPedido(bool cargado)
{
	_cargado = cargado;
}

void Pedido::setTipoPedido(const char* tipoPedido)
{
	strcpy(_tipoPedido, tipoPedido);
}

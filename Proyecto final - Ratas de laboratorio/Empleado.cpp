#include <iostream>
#include <string.h>
#include "rlutil.h"
#include "Empleado.h"
#include "EmpleadosArchivo.h"
#include "Domicilio.h"
#include "Funciones.h"

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

void Empleado::cargar()//TODO: CARGAR EMPLEADOS
{
	Empleado e;
	char nombre[30];
	char apellido[30];
	int dni;
	Domicilio domicilio;
	char email[40];
	int telefono;
	int legajo; 
	int password;
	int categoria;
	bool repite = true;
	bool estado;
	int opcion;

	do
	{
		Empleado empVerificacion;
		EmpleadosArchivo empVerificacionArc;
		bool repetido = false;

		rlutil::cls();
		ubicar(27, 8);
		rlutil::setColor(rlutil::YELLOW);
		cout << "CARGA DE EMPLEADOS - LAB RATS" << endl;
		ubicar(27, 9);
		cout << "=======================================================" << endl;
		ubicar(27, 10);
		rlutil::setColor(rlutil::CYAN);
		cout << "Ingrese su nombre: " ;
		rlutil::setColor(rlutil::WHITE);
		cin.getline(nombre, 30, '\n');

		ubicar(27, 11);
		rlutil::setColor(rlutil::CYAN);
		cout  << "Apellido: " ;
		rlutil::setColor(rlutil::WHITE);
		cin.getline(apellido, 30, '\n');

		ubicar(27, 12);
		rlutil::setColor(rlutil::CYAN);
		cout << "Numero de DNI: " ;
		rlutil::setColor(rlutil::WHITE);
		cin >> dni;
		cin.ignore();

		ubicar(27, 13);
		rlutil::setColor(rlutil::CYAN);
		cout << "EMAIL: " ;
		rlutil::setColor(rlutil::WHITE);
		cin.getline(email, 30, '\n');
		
		ubicar(27, 14);
		rlutil::setColor(rlutil::CYAN);
		cout << "Numero de telefono: " ;
		rlutil::setColor(rlutil::WHITE);
		cin >> telefono;
		
		ubicar(27, 15);
		rlutil::setColor(rlutil::CYAN);
		cout << "Numero de legajo: " ;
		rlutil::setColor(rlutil::WHITE);
		cin >> legajo;

		estado = true;

		ubicar(27, 16);
		rlutil::setColor(rlutil::CYAN);
		cout << "Categoria: " ;//1- ingreso 2-egreso
		rlutil::setColor(rlutil::WHITE);
		cin >> categoria;

		ubicar(27, 17);
		rlutil::setColor(rlutil::CYAN);
		cout <<  "Password (numerica): " ;
		rlutil::setColor(rlutil::WHITE);
		cin >> password;
		rlutil::setColor(rlutil::CYAN);
		cin.ignore();

		domicilio.cargar();

		//VALIDO QUE EL EMPLEADO NO TENGA EL MISMO LEGAJO O DNI QUE OTRO DEL ARCHIVO
		for (int x = 0; x < empVerificacionArc.getCantidad(); x++)
		{
			empVerificacion = empVerificacionArc.leer(x);
			if (empVerificacion.getLegajo() == legajo || empVerificacion.getDni() == dni)
			{
				repetido = true;
			}
		}
		if (repetido == true)
		{
			limpiarConsola();
			rlutil::setColor(rlutil::RED);
			ubicar(27, 10);//TDOO:ERROR NO detecta el ubicar --> Ya hay un usuario con el mismo DNI / LEGAJO cargado
			cout <<endl<< "                           Ya hay un usuario con el mismo DNI / LEGAJO cargado" << endl;//Dejar con estos espacios
			rlutil::setColor(rlutil::WHITE);
			presioneUnaTecla();
			return ;
		}

		//SETEO LOS VALORES DE LAS VARIABLES LOCALES
		e.setNombre(nombre);
		e.setApellido(apellido);
		e.setDni(dni);
		e.setEmail(email);
		e.setTelefono(telefono);
		e.setLegajo(legajo);
		e.setPassword(password);
		e.setCategoria(categoria);
		e.setDomicilio(domicilio);
		e.setEstado(estado);


		int op = 1;
		int y = 0;
		do
		{
			rlutil::setBackgroundColor(rlutil::BLACK);
			rlutil::setColor(rlutil::WHITE);
			rlutil::hidecursor();
			limpiarConsola();
			showItemEgreso("Desea guardar los datos ingresados?", 30, 9, 0);
			showItemEgreso("- OK       ", 40, 11, y == Opcion1);
			showItemEgreso("- Cancelar ", 40, 12, y == Opcion2);

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
			}

		} while (op != 0);

		switch (y)
		{
		case 0:
			EmpleadosArchivo ea;
			ea.guardar(e);
			limpiarConsola();
			ubicar(27, 10);
			rlutil::setColor(rlutil::GREEN);
			cout << "Usuario cargado con exito" << endl;
			rlutil::setColor(rlutil::CYAN);
			presioneUnaTecla();
			limpiarConsola();
			break;
		case 1:
			limpiarConsola();
			break;
		}
		op = 1;
		y = 0;
		do
		{
			rlutil::setBackgroundColor(rlutil::BLACK);
			rlutil::setColor(rlutil::WHITE);
			rlutil::hidecursor();
			limpiarConsola();
			showItemEgreso("Desea CARGAR otro empleado?", 30, 9, 0);
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
		//cin.ignore();
	}
	while (repite);

}

void Empleado::mostrar()
{
	rlutil::setColor(rlutil::CYAN);
	cout << "Nombre: " << getNombre() << endl;
	cout << "Apellido: " << getApellido() << endl;
	cout << "DNI: " << getDni()<<endl;
	_domicilio.mostrar();
	cout << "Email: " << getEmail() << endl;
	cout << "Telefono: " << getTelefono() << endl;
	cout << "Legajo: "<< getLegajo() << endl;
	cout << "Categoria: " << getCategoria() << endl;

}

//SETS

void Empleado::setNombre(const char* nombre)
{
	strcpy(_nombre, nombre);
}

void Empleado::setApellido(const char* apellido)
{
	strcpy(_apellido, apellido);
}

void Empleado::setDni(int dni)
{
	_dni = dni;
}

void Empleado::setDomicilio(Domicilio domicilio)
{
	_domicilio = domicilio;
}

void Empleado::setEmail(const char* email)
{
	strcpy(_email, email);
}

void Empleado::setTelefono(int telefono)
{
	if (telefono > 0) {
		_telefono = telefono;
	}
}

void Empleado::setLegajo(int legajo)
{
	if (legajo > 0) {
		_legajo = legajo;
	}
}

void Empleado::setEstado(bool estado)
{
	_estado = estado;
}

void Empleado::setCategoria(int categoria)
{
	_categoria = categoria;
}

void Empleado::setPassword(int password)
{
	_password = password;

}

//GETS

const char* Empleado::getNombre()
{
	return _nombre;
}

const char* Empleado::getApellido()
{
	return _apellido;
}

int Empleado::getDni()
{
	return _dni;
}

const char* Empleado::getEmail()
{
	return _email;
}

int Empleado::getTelefono()
{
	return _telefono;
}

int Empleado::getLegajo()
{
	return _legajo;
}

bool Empleado::getEstado()
{
	return _estado;
}

int Empleado::getCategoria()
{
	return _categoria;
}

int Empleado::getPassword()
{
	return _password;
}





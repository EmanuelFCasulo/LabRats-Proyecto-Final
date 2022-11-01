#include "Domicilio.h"
#include "Funciones.h"
#include <string.h>
#include <iostream>
#include "rlutil.h"

using namespace std;



Domicilio::Domicilio()
{
}

void Domicilio::cargar()
{
	char calle[30]; 
	int altura;
	char localidad[30];
	char provincia[30];

	ubicar(27, 18);
	rlutil::setColor(rlutil::WHITE);
	cout << "Datos del domicilio" << endl;
	rlutil::setColor(rlutil::CYAN);

	ubicar(27, 19);
	cout << "Ingrese la calle: " ;
	rlutil::setColor(rlutil::WHITE);
	cin.getline(calle, 30, '\n');
	rlutil::setColor(rlutil::CYAN);

	do
	{
		ubicar(27, 20);
		cout << "Altura (Numero): " ;
		rlutil::setColor(rlutil::WHITE);
		cin >> altura;	
		if (altura <= 0 && altura < 99999)
		{
			cout << "Ingrese una altura valida";
		}
	} while (altura <= 0);

	rlutil::setColor(rlutil::CYAN);

	ubicar(27, 21);
	cout  << "Localidad: ";
	cin.ignore();
	rlutil::setColor(rlutil::WHITE);
	cin.getline(localidad, 30, '\n');
	rlutil::setColor(rlutil::CYAN);

	ubicar(27, 22);
	cout << "Provincia: " ;
	rlutil::setColor(rlutil::WHITE);
	cin.getline(provincia, 30, '\n');

	setCalle(calle);
	setAltura(altura);
	setLocalidad(localidad);
	setProvincia(provincia);
	
}

void Domicilio::mostrar()
{
	
	rlutil::setColor(rlutil::CYAN);
	cout << "Calle: " << getCalle()<<endl;
	cout << "Altura: " << getAltura()<<endl;
	cout << "Localidad: " << getLocalidad()<<endl;
	cout << "Provincia: " << getProvincia()<<endl;
}

//SETS

void Domicilio::setCalle(const char* calle)
{
	strcpy(_calle, calle);
}


void Domicilio::setAltura(int altura)
{
	_altura = altura;
}

void Domicilio::setLocalidad(const char* localidad)
{
	strcpy(_localidad, localidad);
}

void Domicilio::setProvincia(const char* provincia)
{
	strcpy(_provincia, provincia);
}

//GETS

const char *Domicilio::getCalle()
{
	return _calle;
}

int Domicilio::getAltura()
{
	return _altura;
}

const char *Domicilio::getLocalidad()
{
	return _localidad;
}

const char *Domicilio::getProvincia()
{
	return _provincia;
}

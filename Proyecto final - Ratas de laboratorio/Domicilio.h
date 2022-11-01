#pragma once
#include <string.h>
using namespace std;

class Domicilio
{
protected:
	char _calle[30];
	int _altura;
	char _localidad[30];
	char _provincia[30];

public:
	Domicilio();
	
	void cargar();
	void mostrar();
	void setCalle(const char *calle);
	void setAltura(int altura);
	void setLocalidad(const char *localidad);
	void setProvincia(const char *provincia);

	const char* getCalle();
	int getAltura();
	const char* getLocalidad();
	const char* getProvincia();

};


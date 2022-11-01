#pragma once
#include "Domicilio.h"

class Empleado
{
private:
	char _nombre[30];
	char _apellido[30];
	int _dni;
	Domicilio _domicilio;
	char _email[40];
	int _telefono;
	int _legajo;
	bool _estado;
	int _password;
	int _categoria;//LA CATEGORIA DE ADMINISTRADOR ES LA 999

public:
	void cargar();
	void mostrar();

	void setNombre(const char* nombre);
	void setApellido(const char* apellido);
	void setDni(int dni);
	void setDomicilio(Domicilio dom);
	void setEmail(const char* email);
	void setTelefono(int telefono);
	void setLegajo(int legajo);
	void setEstado(bool estado = true);
	void setCategoria(int categoria);
	void setPassword(int password);

	const char* getNombre();
	const char* getApellido();
	int getDni();
	const char* getEmail();
	int getTelefono();
	int getLegajo();
	bool getEstado();///MODIFICAR PORQUE EL EMPLEADO NO DEBERIA CARGAR SU ESTADO(estado por defecto es true)
	int getCategoria();
	int getPassword();

};


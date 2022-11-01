#pragma once
#include <string>
using namespace std;

class Producto
{
private:
	int _idProd;
	char _nombre[30];
	char _marca[30];
	int _categoriaProd;
	float _precio;
	int _stock;
	bool _estado;//por defecto esta en true, el administrador solo podria cambiar el estado

public:

	void cargar();
	void mostrar();

	void setIdProd(int idProd);
	void setNombre(const char *nombre);
	void setMarca(const char *marca);
	void setCategoriaProd(int categoriaProd);
	void setPrecio(float precio);
	void setStock(int stock);
	void setEstado(bool estado);
	void aumentarStock(int cant);
	void descontarStock(int cant);

	int getIdProd();
	const char *getNombre();
	const char *getMarca();
	int getCategoriaProd();
	float getPrecio();
	int getStock();
	bool getEstado();

};


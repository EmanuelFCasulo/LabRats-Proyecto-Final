#pragma once


class Fecha
{
private:
    int _dia;
    int _mes;
    int _anio;

public:
    void cargar();
    void mostrar();

    void setDia(int dia);
    void setMes(int mes);
    void setAnio(int anio);

    int getDia();
    int getMes();
    int getAnio();

    Fecha();
};


#include <iostream>
using namespace std;
#include "Fecha.h"
#include "rlutil.h"
#include "Funciones.h"

void Fecha::cargar()
{
    do
    {
        rlutil::setColor(rlutil::CYAN);
        cout << endl << "Dia: " ;
        cin >> _dia;
        if (_dia < 1 || _dia > 31)
        {
            rlutil::setColor(rlutil::RED);
            cout << "Ingrese un dia valido" << endl;
            rlutil::setColor(rlutil::CYAN);
            presioneUnaTecla();
            limpiarConsola();
        }
    } while (_dia < 1 || _dia > 31);
    do
    {
        rlutil::setColor(rlutil::CYAN);
        cout << endl<< "Mes: " ;
        cin >> _mes;
        if (_mes < 1 || _mes > 12)
        {
            rlutil::setColor(rlutil::RED);
            cout << "Ingrese un mes valido" << endl;
            rlutil::setColor(rlutil::CYAN);
            presioneUnaTecla();
            limpiarConsola();
        }
    } while (_mes < 1 || _mes > 12);

    do
    {
        rlutil::setColor(rlutil::CYAN);
        cout << endl << "Anio: " ;
        cin >> _anio;
        if (_anio < 2021 )
        {
            rlutil::setColor(rlutil::RED);
            cout << "Ingrese un anio valido" << endl;
            rlutil::setColor(rlutil::CYAN);
            presioneUnaTecla();
            limpiarConsola();
        }
    } while (_anio < 2021 );
}

void Fecha::mostrar()
{
    rlutil::setColor(rlutil::CYAN);
    cout << _dia << "/" << _mes << "/" << _anio << endl;
}

//SETS

void Fecha::setDia(int dia)
{
    _dia = dia;
}

void Fecha::setMes(int mes)
{
    _mes = mes;
}

void Fecha::setAnio(int anio)
{
    _anio = anio;
}

//GETS

int Fecha::getDia()
{
    return _dia;
}

int Fecha::getMes()
{
    return _mes;
}

int Fecha::getAnio()
{
    return _anio;
}

Fecha::Fecha() {
    time_t rawtime;
    struct tm timeinfo;

    time(&rawtime);
    timeinfo = *(localtime(&rawtime));

    _dia = timeinfo.tm_mday;
    _mes = timeinfo.tm_mon + 1;
    _anio = timeinfo.tm_year + 1900;
}


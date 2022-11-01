#include "EmpleadosArchivo.h"
#include "Empleado.h"
#include <iostream>
using namespace std;

Empleado EmpleadosArchivo::leer(int nroRegistro) {
    Empleado emp;
    FILE* p;
    p = fopen("empleados.dat", "rb");
    if (p == NULL) {
        return emp;
    }
    fseek(p, nroRegistro * sizeof(Empleado), SEEK_SET);
    fread(&emp, sizeof(Empleado), 1, p);
    fclose(p);
    return emp;
}

bool EmpleadosArchivo::leerTodos(Empleado estudiantes[], int cantidad) {
    FILE* p;
    p = fopen("empleados.dat", "rb");
    if (p == NULL) {
        return false;
    }
    fread(estudiantes, sizeof(Empleado), cantidad, p);
    fclose(p);
    return true;
}

bool EmpleadosArchivo::guardar(Empleado est) {
    FILE* p = fopen("empleados.dat", "ab");
    if (p == NULL) {
        return false;
    }
    bool ok = fwrite(&est, sizeof(Empleado), 1, p);
    fclose(p);
    return ok;
}

bool EmpleadosArchivo::guardar(Empleado emp, int nroRegistro) {
    FILE* p = fopen("empleados.dat", "rb+");
    if (p == NULL) {
        return false;
    }
    fseek(p, nroRegistro * sizeof(Empleado), SEEK_SET);
    bool ok = fwrite(&emp, sizeof(Empleado), 1, p);
    fclose(p);
    return ok;
}

int EmpleadosArchivo::getCantidad() {
    FILE* p = fopen("empleados.dat", "rb");
    if (p == NULL) {
        return 0;
    }
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Empleado);
    fclose(p);
    return cant;
}

int EmpleadosArchivo::buscar(int legajo) {
    int cant = getCantidad();
    Empleado emp;
    for (int i = 0; i < cant; i++) {
        emp = leer(i);
        if (emp.getLegajo() == legajo) {
            return i;
        }
    }
    return -1;
}

void EmpleadosArchivo::mostrarArchivo()
{
        EmpleadosArchivo empArc;
        int cantArchivos = empArc.getCantidad();
        Empleado* emp = new Empleado[cantArchivos];
        empArc.leerTodos(emp, cantArchivos);
        for (int x = 0; x < cantArchivos; x++)
        {
            emp[x].mostrar();
            cout << endl;
        }
}

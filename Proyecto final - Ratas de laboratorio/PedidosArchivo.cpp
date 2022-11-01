#include "PedidosArchivo.h"
#include <iostream>
using namespace std;

Pedido PedidosArchivo::leer(int nroRegistro) {
    Pedido ped;
    FILE* p;
    p = fopen("pedidos.dat", "rb");
    if (p == NULL) {
        return ped;
    }
    fseek(p, nroRegistro * sizeof(Pedido), SEEK_SET);
    fread(&ped, sizeof(Pedido), 1, p);
    fclose(p);
    return ped;
}

bool PedidosArchivo::leerTodos(Pedido pedidos[], int cantidad) {
    FILE* p;
    p = fopen("pedidos.dat", "rb");
    if (p == NULL) {
        return false;
    }
    fread(pedidos, sizeof(Pedido), cantidad, p);
    fclose(p);
    return true;
}

bool PedidosArchivo::guardar(Pedido ped) {
    FILE* p = fopen("pedidos.dat", "ab");
    if (p == NULL) {
        return false;
    }
    bool ok = fwrite(&ped, sizeof(Pedido), 1, p);
    fclose(p);
    return ok;
}

bool PedidosArchivo::guardar(Pedido ped, int nroRegistro) {
    FILE* p = fopen("pedidos.dat", "rb+");
    if (p == NULL) {
        return false;
    }
    fseek(p, nroRegistro * sizeof(Pedido), SEEK_SET);
    bool ok = fwrite(&ped, sizeof(Pedido), 1, p);
    fclose(p);
    return ok;
}

int PedidosArchivo::getCantidad() {
    FILE* p = fopen("pedidos.dat", "rb");
    if (p == NULL) {
        return 0;
    }
    fseek(p, 0, SEEK_END);
    int cant = ftell(p) / sizeof(Pedido);
    fclose(p);
    return cant;
}

int PedidosArchivo::buscar(int idPedido) {
    int cant = getCantidad();
    Pedido ped;
    for (int i = 0; i < cant; i++) {
        ped = leer(i);
        if (ped.getIdPedido() == idPedido) {
            return i;
        }
    }
    return -1;
}

void PedidosArchivo::mostrarArchivo()
{
        PedidosArchivo pedArc;
        int cantArchivos = pedArc.getCantidad();
        Pedido* ped = new Pedido[cantArchivos];
        pedArc.leerTodos(ped, cantArchivos);
        for (int x = 0; x < cantArchivos; x++)
        {
            ped[x].mostrar();
            cout << endl;
        }
}

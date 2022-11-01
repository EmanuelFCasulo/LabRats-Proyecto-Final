#include <iostream>
using namespace std;
#include "rlutil.h"
#include "Funciones.h"
#include "Domicilio.h"
#include "Fecha.h"
#include "Pedido.h"
#include "PedidosArchivo.h"
#include "Empleado.h"
#include "EmpleadosArchivo.h"
#include "Producto.h"
#include "ProductosArchivo.h"



void limpiarConsola()
{
    rlutil::cls();
}

void presioneUnaTecla()
{
    rlutil::anykey();
}

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

//TODO: MENU PRINCIPAL DEL PROGRAMA
void menuPrincipal()
{
    int y = 0;
    int op = 1;
    do
    {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
        rlutil::hidecursor();
        showItem("Bienvenido/a a LAB/RATS", 29, 8, 0);
        showItem("-------------------------------", 26, 9, 0);
        showItem("- Acceder como empleado  ", 30, 10, y == Opcion1);
        showItem("- Acceder como admin     ", 30, 11, y == Opcion2);

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

            if (y == 0)
            {
                menuEmpleado();
            }
            else
            {
                menuAdmin();
            }
        } 
    } while (op != 0);
}

//TODO: Login empleados
void menuEmpleado()
{
    int legajo;
    int password;
    int intentos=0;
    Empleado e, emp;
    EmpleadosArchivo ea;
    bool ingreso = false;
    bool repite = true;
    limpiarConsola();

    do
    {
        //TODO: Ingreso Empleados (funciona bien el do while)
        rlutil::setColor(rlutil::YELLOW);
        ubicar(27 , 8);
        cout << "                 INGRESO EMPLEADOS" << endl;
        ubicar(27, 9);
        cout << "=======================================================" << endl;
        //cout << endl << endl;
        ubicar(30 - 3, 10);
        rlutil::setColor(rlutil::WHITE);
        cout << "Ingrese nro de legajo: " ;
        rlutil::setColor(rlutil::CYAN);
        cin >> legajo;//validarlo del archivo de empleados
    

        rlutil::setColor(rlutil::WHITE);
        ubicar(27, 11);
        cout << "Ingrese su clave de ingreso: ";
        rlutil::setColor(rlutil::CYAN);
        cin >> password;
        rlutil::setColor(rlutil::CYAN);
        cout << endl;
        limpiarConsola();

        for (int x = 0; x < ea.getCantidad(); x++)
        {
            e = ea.leer(x);

            if (e.getLegajo() == legajo && e.getPassword() == password && e.getEstado() == true)
            {

                emp = e;
                if (emp.getCategoria() == 999)
                {
                    limpiarConsola();
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::RED);
                    cout << "El usuario ADMIN no puede acceder al menu de empleados" << endl;
                    rlutil::setColor(rlutil::WHITE);
                    presioneUnaTecla();
                    limpiarConsola();
                    return menuPrincipal();
                }
                else
                {
                    if (emp.getEstado() == false)
                    {
                        ubicar(27, 10);
                        rlutil::setColor(rlutil::RED);
                        cout << "El usuario ha sido dado de baja" << endl;
                        rlutil::setColor(rlutil::WHITE);
                        presioneUnaTecla();
                    }
                }

                ubicar(27, 10);
                rlutil::setColor(rlutil::GREEN);
                cout << "Ingreso exitoso! Bienvenido " << emp.getNombre() << " " << emp.getApellido();
                rlutil::setColor(rlutil::WHITE);
                ingreso = true;
                repite = false;
                presioneUnaTecla();
                limpiarConsola();
            }
        
            
        }

        if(ingreso == false)
        {
        intentos++;
            if (intentos < 3 && intentos > 0)
            {
                ubicar(27, 10);
                rlutil::setColor(rlutil::RED);
                cout << "Legajo o clave invalida, vuelva a intentar" << endl;
                rlutil::setColor(rlutil::WHITE);
                presioneUnaTecla();
                limpiarConsola();
            }
        }
        
        if (intentos == 3)
        {
            ubicar(27, 10);
            rlutil::setColor(rlutil::RED);
            cout << "Muchos ingresos fallidos, se cerrara el programa" << endl;
            rlutil::setColor(rlutil::WHITE);
            presioneUnaTecla();
            return;
        }
    }
    while (repite);

    menuPrincipalEmpleado(emp);
}

//TODO: Menu donde se filtra que menu mostrar segun la categoria
void menuPrincipalEmpleado(Empleado emp)
{
    int legajoEmp = emp.getLegajo();
    if (emp.getCategoria() == 1)
    {
        menuEmpleadoIngreso(legajoEmp);
    }
    else
    {
        if (emp.getCategoria() == 2 )
        {
            menuEmpleadoEgreso(legajoEmp);
        }
    }

}

//TODO: Menu empleado para ingreso de productos
void menuEmpleadoIngreso(int legajo)//Si tiene categoria 1 se encarga del ingreso de productos
{
    //int opcion;
    int y = 0;
    int op = 1;
    do
    {
        rlutil::setBackgroundColor(rlutil::RED);
        rlutil::setColor(rlutil::WHITE);
        rlutil::hidecursor();

        showItemIngreso("                 INGRESO DE STOCK", 30, 8, 0);
        showItemIngreso("=======================================================", 30, 9, 0);
        showItemIngreso("- Registrar nuevo pedido      ", 30, 10, y == Opcion1);
        showItemIngreso("- Cargar pedido pendiente     ", 30, 11, y == Opcion2);
        showItemIngreso("- Cancelar pedido             ", 30, 12, y == Opcion3);
        showItemIngreso("- Volver al inicio de sesion  ", 30, 13, y == Opcion4);
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
            if (y > 3) {
                y = 3;
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
            case 2:
                op = 0;
                break;
            case 3:
                op = 0;
                break;
            }
        }

    } while (op != 0);

    switch (y)
    {
    case 0:
    {
        int opcion;
        bool repite = true;
        do
        {
            Pedido ped;
            PedidosArchivo pedArc;
            ped.cargar(legajo);
            if (ped.getTipoPedido() == "e")
            {
                ubicar(27, 10);
                rlutil::setColor(rlutil::RED);
                cout << "Usted no esta habilitado para registrar pedidos de EGRESO de productos" << endl;
                rlutil::setColor(rlutil::CYAN);
                presioneUnaTecla();
                limpiarConsola();
                return menuEmpleadoIngreso(legajo);
            }
            else
            {
                if (ped.getTipoPedido() == "c")
                {
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::RED);
                    cout << "No se pueden registrar pedidos cancelados!" << endl;
                    rlutil::setColor(rlutil::CYAN);
                    presioneUnaTecla();
                    limpiarConsola();
                    return menuEmpleadoIngreso(legajo);
                }
            }
            limpiarConsola();
            
            rlutil::setColor(rlutil::CYAN);
            ubicar(27, 10);
            cout << "Desea guardar el pedido ingresado?" << endl;
            ubicar(27, 11);
            cout << "1- OK" << endl;
            ubicar(27, 12);
            cout << "2- Cancelar" << endl;
            ubicar(27, 13);
            rlutil::setColor(rlutil::WHITE);
            cout << "Elija una opcion" << endl;
            ubicar(27, 14);
            rlutil::setColor(rlutil::WHITE);
            cin >> opcion;

            if (opcion != 1 && opcion != 2)
            {
                ubicar(27, 10);
                rlutil::setColor(rlutil::RED);
                cout << endl << "Opcion inexistente" << endl;
                rlutil::setColor(rlutil::CYAN);
                presioneUnaTecla();
                limpiarConsola();
            }
            switch (opcion)
            {
            case 1:
            {
                limpiarConsola();
                pedArc.guardar(ped);

                ubicar(27, 10);
                rlutil::setColor(rlutil::GREEN);
                cout << "Pedido cargado con exito" << endl;
                rlutil::setColor(rlutil::CYAN);
                presioneUnaTecla();
                limpiarConsola();
                do
                {
                    ubicar(27, 10);
                    cout << "Desea cargar otro pedido?" << endl;
                    ubicar(27, 11);
                    cout << "1- OK" << endl;
                    ubicar(27, 12);
                    cout << "2- Cancelar" << endl;
                    ubicar(27, 13);
                    cin >> opcion;
                    
                    if (opcion != 1 && opcion != 2)
                    {
                        ubicar(27, 10);
                        rlutil::setColor(rlutil::RED);
                        cout << "Opcion inexistente" << endl;
                        rlutil::setColor(rlutil::CYAN);
                        presioneUnaTecla();
                        limpiarConsola();
                    }
                } while (opcion != 1 && opcion != 2);

                switch (opcion)
                {
                case 1:
                    repite = true;
                    break;
                case 2:
                    repite = false;
                    return menuEmpleadoIngreso(legajo);
                    break;
                }
            }
            case 2:
                return menuEmpleadoIngreso(legajo);
                break;
            }
        } while (repite);
    }
    case 1:
    {
        bool repite = true;
        bool cancelado = false;
        bool cargado = false;
        do
        {
            Pedido ped1, pedAux1;
            PedidosArchivo pedArc1;
            int idPedido;
            int opcion;
            bool encontro = false;


            limpiarConsola();
            ubicar(27, 10);
            rlutil::setColor(rlutil::YELLOW);
            cout << "EJECUTAR PEDIDO PENDIENTE" << endl;
            ubicar(27, 11);
            cout << "=======================================================" << endl;
            ubicar(27, 12);
            rlutil::setColor(rlutil::WHITE);
            cout << "Ingrese ID de pedido";
            ubicar(27, 13);
            rlutil::setColor(rlutil::CYAN);
            cin >> idPedido;
            limpiarConsola();

            for (int x = 0; x < pedArc1.getCantidad(); x++)
            {
                ped1 = pedArc1.leer(x);
                if (ped1.getIdPedido() == idPedido && ped1.getTipoPedido() == "i")
                {
                    encontro = true;
                    repite = false;
                }
                else
                {
                    if (ped1.getIdPedido() == idPedido && ped1.getTipoPedido() == "c")
                    {
                        ubicar(27, 10);
                        rlutil::setColor(rlutil::RED);
                        cout << "El pedido fue cancelado con anterioridad." << endl;
                        rlutil::setColor(rlutil::CYAN);
                        presioneUnaTecla();
                        limpiarConsola();
                        cancelado = true;
                        encontro = true;
                        repite = false;
                        return menuEmpleadoIngreso(legajo);
                    }
                    else
                    {
                        if (ped1.getIdPedido() == idPedido && ped1.getTipoPedido() == "e")
                        {
                            ubicar(27, 10);
                            rlutil::setColor(rlutil::RED);
                            cout << "No tiene permiso para ejecutar pedidos de egreso de stock" << endl;
                            rlutil::setColor(rlutil::CYAN);
                            presioneUnaTecla();
                            limpiarConsola();
                            return menuEmpleadoIngreso(legajo);
                        }
                    }
                }
            }
            if (encontro == true && cancelado == false)
            {
                int opcion;

                limpiarConsola();
                ubicar(27, 10);
                rlutil::setColor(rlutil::GREEN);
                cout << "Pedido encontrado!" << endl;
                rlutil::setColor(rlutil::CYAN);
                presioneUnaTecla();
                limpiarConsola();
                do
                {
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::CYAN);
                    cout << "Desea cargarlo al sistema?" << endl;
                    ubicar(27, 11);
                    cout << "1- SI" << endl;
                    ubicar(27, 12);
                    cout << "2- Cancelar" << endl << endl;
                    rlutil::setColor(rlutil::WHITE);
                    ubicar(27, 13);
                    cout << "Elija una opcion" << endl;
                    ubicar(27, 14);
                    rlutil::setColor(rlutil::CYAN);
                    cin >> opcion;
                    limpiarConsola();

                    if (opcion != 1 && opcion != 2)
                    {
                        ubicar(27, 10);
                        rlutil::setColor(rlutil::RED);
                        cout << "Opcion invalida" << endl;
                        rlutil::setColor(rlutil::CYAN);
                        presioneUnaTecla();
                        limpiarConsola();
                    }

                } while (opcion != 1 && opcion != 2);

                switch (opcion)
                {
                case 1:
                {
                    Producto prod;
                    ProductosArchivo prodArc;
                    int reg = 0, regPed = 0;

                    for (int x = 0; x < pedArc1.getCantidad(); x++)
                    {
                        ped1 = pedArc1.leer(x);

                        for (int j = 0; j < prodArc.getCantidad(); j++)
                        {
                            prod = prodArc.leer(j);

                            if (ped1.getIdPedido() == idPedido && ped1.getIdProducto() == prod.getIdProd())
                            {
                                prod.aumentarStock(ped1.getCantidadProducto());
                                reg = j;
                                regPed = x;
                                prodArc.guardar(prod, reg);
                                ubicar(27, 10);
                                rlutil::setColor(rlutil::GREEN);
                                cout << "Pedido cargado con exito!" << endl;
                                rlutil::setColor(rlutil::CYAN);

                                cargado = true;
                                ped1.setEstadoPedido(cargado);
                                pedArc1.guardar(ped1, regPed);
                                presioneUnaTecla();
                                limpiarConsola();
                            }
                        }
                    }
                    return menuEmpleadoIngreso(legajo);
                    break;
                }
                case 2:
                    return menuEmpleadoIngreso(legajo);
                    break;
                }
            }
            else
            {
                ubicar(27, 10);
                rlutil::setColor(rlutil::RED);
                cout << "Pedido no encontrado/incorrecto" << endl;
                rlutil::setColor(rlutil::CYAN);
                presioneUnaTecla();
                limpiarConsola();
                return menuEmpleadoIngreso(legajo);
            }
        } while (repite);
        return menuEmpleadoIngreso(legajo);
        break;
    }
    case 2:
    {
        int opcion1;
        Pedido ped1, ped1Aux;
        PedidosArchivo pedArc1;
        int idPedido;
        int reg;
        bool encontro = false;
        bool cancelado = false;
        
        ubicar(27, 10);
        rlutil::setColor(rlutil::YELLOW);
        cout << "CANCELAR PEDIDO DE INGRESO" << endl;
        ubicar(27, 11);
        cout << "=======================================================" << endl;
        ubicar(27, 12);
        rlutil::setColor(rlutil::WHITE);
        cout << "Ingrese ID de pedido";
        ubicar(27, 13);
        rlutil::setColor(rlutil::CYAN);
        cin >> idPedido;

        for (int x = 0; x < pedArc1.getCantidad(); x++)
        {
            ped1 = pedArc1.leer(x);
            if (ped1.getIdPedido() == idPedido && ped1.getTipoPedido() == "i")
            {
                encontro = true;
                reg = x;
                ped1Aux = ped1;
            }
            else
            {
                if (ped1.getIdPedido() == idPedido && ped1.getTipoPedido() == "c")
                {
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::RED);
                    cout << "El pedido fue cancelado con anterioridad." << endl;
                    rlutil::setColor(rlutil::CYAN);
                    presioneUnaTecla();
                    limpiarConsola();
                    return menuEmpleadoIngreso(legajo);
                }
                else
                {
                    if (ped1.getIdPedido() == idPedido && ped1.getTipoPedido() == "e")
                    {
                        ubicar(27, 10);
                        rlutil::setColor(rlutil::RED);
                        cout << "Usted no esta habilitado para cancelar pedidos de EGRESO de productos" << endl;
                        rlutil::setColor(rlutil::CYAN);
                        presioneUnaTecla();
                        limpiarConsola();
                        return menuEmpleadoIngreso(legajo);
                    }
                }
            }
        }
        if (encontro == false)
        {
            ubicar(27, 10);
            rlutil::setColor(rlutil::RED);
            cout << "No se encontro ningun pedido" << endl;
            rlutil::setColor(rlutil::CYAN);
            presioneUnaTecla();
            limpiarConsola();
            return menuEmpleadoIngreso(legajo);
        }
        else
        {
            ubicar(27, 10);
            rlutil::setColor(rlutil::GREEN);
            cout << "Pedido encontrado!" << endl;
            rlutil::setColor(rlutil::CYAN);
            presioneUnaTecla();
            limpiarConsola();
            do
            {
                int opcion;
                ubicar(27, 10);
                rlutil::setColor(rlutil::CYAN);
                ubicar(27, 11);
                cout << "=======================================================" << endl;
                ubicar(27, 12);
                cout << "CANCELAR PEDIDOS" << endl;
                ubicar(27, 13);
                cout << "=======================================================" << endl;
                ubicar(27, 14);
                cout << "1- Cancelar el pedido: " << ped1Aux.getIdPedido() << endl;
                ubicar(27, 15);
                cout << "2- Volver" << endl << endl;;
                ubicar(27, 16);
                rlutil::setColor(rlutil::WHITE);
                cout << "Ingrese una opcion: ";
                rlutil::setColor(rlutil::CYAN);
                ubicar(27, 17);
                cin >> opcion1;
                limpiarConsola();

                if (opcion1 < 1 && opcion1 > 2)
                {
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::RED);
                    cout << "Opcion Incorrecta" << endl;
                    rlutil::setColor(rlutil::CYAN);
                    presioneUnaTecla();
                    limpiarConsola();
                }
            } while (opcion1 < 1 && opcion1 > 2);
           
            if (opcion1 == 1)
            {
                ped1Aux.setTipoPedido("c");
                pedArc1.guardar(ped1Aux, reg);
                ubicar(27, 10);
                rlutil::setColor(rlutil::GREEN);
                cout << "Pedido " << ped1Aux.getIdPedido() << " cancelado con exito!" << endl;
                rlutil::setColor(rlutil::CYAN);
                presioneUnaTecla();
                limpiarConsola();
                return menuEmpleadoIngreso(legajo);
            }
            else
            {
                return menuEmpleadoIngreso(legajo);
                limpiarConsola();
            }
        }
        return menuEmpleadoIngreso(legajo);
        break;
    }
    case 3:
        return menuEmpleado();
        break;
    }


    }

//TODO: Menu empleado para egreso de productos
void menuEmpleadoEgreso(int legajo)//si tiene categoria 2 se encaga del egreso de productos por pedido
{
    int opcion;
    int y = 0;
    int op = 1;
    do
    {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
        rlutil::hidecursor();

        showItemEgreso("                  EGRESO DE STOCK", 30, 8, 0);
        showItemEgreso("=======================================================", 30, 9, 0);
        showItemEgreso("- Registrar nuevo pedido      ", 30, 10, y == Opcion1);
        showItemEgreso("- Cargar pedido pendiente     ", 30, 11, y == Opcion2);
        showItemEgreso("- Cancelar pedido             ", 30, 12, y == Opcion3);
        showItemEgreso("- Volver al inicio de sesion  ", 30, 13, y == Opcion4);
        
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
            if (y > 3) {
                y = 3;
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
            case 3:
                op = 0;
                break;
            case 4:
                op = 0;
                break;
            default:
                break;
            }
        }
    } while (op != 0);

    switch (y)
    {
    case 1:
    {
        bool repite = true;
        do
        {
            Pedido ped;
            PedidosArchivo pedArc;
            ped.cargar(legajo);
            if (ped.getTipoPedido() == "i")
            {
                ubicar(27, 10);
                rlutil::setColor(rlutil::RED);
                cout << "Usted no esta habilitado para registrar pedidos de INGRESO de productos" << endl;
                rlutil::setColor(rlutil::CYAN);
                presioneUnaTecla();
                limpiarConsola();
                return menuEmpleadoEgreso(legajo);
            }
            else
            {
                if (ped.getTipoPedido() == "c")
                {
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::RED);
                    cout << "No se pueden registrar pedidos cancelados!" << endl;
                    rlutil::setColor(rlutil::CYAN);
                    presioneUnaTecla();
                    limpiarConsola();
                    return menuEmpleadoEgreso(legajo);
                }
            }
            limpiarConsola();
            do
            {
                ubicar(27, 10);
                rlutil::setColor(rlutil::CYAN);
                cout << "Desea guardar el pedido ingresado?" << endl;
                ubicar(27, 11);
                cout << "1- OK" << endl;
                ubicar(27, 12);
                cout << "2- Cancelar" << endl;
                ubicar(27, 13);
                rlutil::setColor(rlutil::WHITE);
                cin >> opcion;
                limpiarConsola();

                if (opcion != 1 && opcion != 2)
                {
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::RED);
                    cout << endl << "Opcion inexistente" << endl;
                    rlutil::setColor(rlutil::CYAN);
                    presioneUnaTecla();
                    limpiarConsola();
                }
            } while (opcion != 1 && opcion != 2);

            switch (opcion)
            {
            case 1:
                limpiarConsola();
                pedArc.guardar(ped);
                ubicar(27, 10);
                rlutil::setColor(rlutil::GREEN);
                cout << "Pedido cargado con exito" << endl;
                rlutil::setColor(rlutil::CYAN);
                presioneUnaTecla();
                limpiarConsola();
                do
                {
                    ubicar(27, 10);
                    cout << "Desea cargar otro pedido?" << endl;
                    ubicar(27, 11);
                    cout << "1- OK" << endl;
                    ubicar(27, 12);
                    cout << "2- Cancelar" << endl;
                    ubicar(27, 13);
                    cin >> opcion;
                    limpiarConsola();
                    
                    if (opcion != 1 && opcion != 2)
                    {
                        ubicar(27, 10);
                        rlutil::setColor(rlutil::RED);
                        cout << "Opcion inexistente" << endl;
                        rlutil::setColor(rlutil::CYAN);
                        presioneUnaTecla();
                        limpiarConsola();
                    }
                } while (opcion != 1 && opcion != 2);

                switch (opcion)
                {
                case 1:
                    repite = true;
                    break;
                case 2:
                    return menuEmpleadoEgreso(legajo);
                    break;
                }
            case 2:
                return menuEmpleadoEgreso(legajo);
                break;
            }
        } while (repite);
    }
    case 2:
    {
        bool repite = true;
        bool cancelado = false;
        bool cargado = false;
        do
        {
            Pedido ped1, pedAux1;
            PedidosArchivo pedArc1;
            int idPedido;
            int opcion;
            bool encontro = false;
            ubicar(27, 10);
            rlutil::setColor(rlutil::YELLOW);
            cout << "CARGAR PEDIDO PENDIENTE" << endl;
            ubicar(27, 11);
            cout << "=======================================================" << endl;
            ubicar(27, 12);
            rlutil::setColor(rlutil::WHITE);
            cout << "Ingrese ID de pedido";
            ubicar(27, 13);
            rlutil::setColor(rlutil::CYAN);
            cin >> idPedido;
            limpiarConsola();

            for (int x = 0; x < pedArc1.getCantidad(); x++)
            {
                ped1 = pedArc1.leer(x);
                if (ped1.getIdPedido() == idPedido && ped1.getTipoPedido() == "e")
                {
                    encontro = true;
                    repite = false;
                }
                else
                {
                    if (ped1.getIdPedido() == idPedido && ped1.getTipoPedido() == "c")
                    {
                        ubicar(27, 10);
                        rlutil::setColor(rlutil::RED);
                        cout << "El pedido fue cancelado con anterioridad." << endl;
                        rlutil::setColor(rlutil::CYAN);
                        presioneUnaTecla();
                        limpiarConsola();
                        cancelado = true;
                        encontro = true;
                        repite = false;
                        return menuEmpleado();
                    }
                    else
                    {
                        if (ped1.getIdPedido() == idPedido && ped1.getTipoPedido() == "i")
                        {
                            encontro = true;
                            repite = false;
                            ubicar(27, 10);
                            rlutil::setColor(rlutil::RED);
                            cout << "No tiene permitido cargar pedidos de ingreso de stock" << endl;
                            rlutil::setColor(rlutil::CYAN);
                            presioneUnaTecla();
                            limpiarConsola();
                            return menuEmpleadoEgreso(legajo);
                        }
                    }
                }
            }
            if (encontro == true && cancelado == false)
            {
                int opcion;

                limpiarConsola();
                ubicar(27, 10);
                rlutil::setColor(rlutil::GREEN);
                cout << "Pedido encontrado!" << endl;
                rlutil::setColor(rlutil::CYAN);
                presioneUnaTecla();
                limpiarConsola();
                do
                {
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::CYAN);
                    cout << "Desea cargarlo al sistema?" << endl;
                    ubicar(27, 11);
                    cout << "1- SI" << endl;
                    ubicar(27, 12);
                    cout << "2- Cancelar" << endl << endl;
                    ubicar(27, 13);
                    rlutil::setColor(rlutil::WHITE);
                    cout << "Elija una opcion" << endl;
                    ubicar(27, 14);
                    rlutil::setColor(rlutil::CYAN);
                    cin >> opcion;
                    limpiarConsola();

                    if (opcion != 1 && opcion != 2)
                    {
                        ubicar(27, 10);
                        rlutil::setColor(rlutil::RED);
                        cout << "Opcion invalida" << endl;
                        rlutil::setColor(rlutil::CYAN);
                        presioneUnaTecla();
                        limpiarConsola();
                    }

                } while (opcion != 1 && opcion != 2);

                switch (opcion)
                {
                case 1:
                {
                    Producto prod;
                    ProductosArchivo prodArc;
                    int reg = 0, regPed = 0;

                    for (int x = 0; x < pedArc1.getCantidad(); x++)
                    {
                        ped1 = pedArc1.leer(x);

                        for (int j = 0; j < prodArc.getCantidad(); j++)
                        {
                            prod = prodArc.leer(j);

                            if (ped1.getIdPedido() == idPedido && ped1.getIdProducto() == prod.getIdProd())
                            {
                                prod.descontarStock(ped1.getCantidadProducto());//TODO: Hacer validacion de descontar stock desde aca o dentro del metodo descontarStock?
                                reg = j;
                                regPed = x;
                                prodArc.guardar(prod, reg);
                                ubicar(27, 10);
                                rlutil::setColor(rlutil::GREEN);
                                cout << "Pedido ejecutado con exito!" << endl;
                                rlutil::setColor(rlutil::CYAN);

                                cargado = true;
                                ped1.setEstadoPedido(cargado);
                                pedArc1.guardar(ped1, regPed);
                                presioneUnaTecla();
                                limpiarConsola();
                            }
                        }
                    }
                    return menuEmpleadoEgreso(legajo);
                    break;
                }
                case 2:
                    return menuEmpleadoEgreso(legajo);
                    break;
                }
            }
            else
            {
                ubicar(27, 10);
                rlutil::setColor(rlutil::RED);
                cout << "Pedido no encontrado/incorrecto" << endl;
                rlutil::setColor(rlutil::CYAN);
                presioneUnaTecla();
                limpiarConsola();
                return menuEmpleadoIngreso(legajo);
            }
        } while (repite);
        return menuEmpleadoEgreso(legajo);
        break;
    }
    case 3:
    {
        Pedido ped1,ped1Aux;
        PedidosArchivo pedArc1;
        int idPedido;
        int reg;
        bool encontro = false;
        bool cancelado = false;

        ubicar(27, 10);
        rlutil::setColor(rlutil::YELLOW);
        cout << "CANCELAR PEDIDO DE EGRESO" << endl;
        ubicar(27, 11);
        cout << "=======================================================" << endl;
        ubicar(27, 12);
        rlutil::setColor(rlutil::WHITE);
        cout << "Ingrese ID de pedido";
        ubicar(27, 13);
        rlutil::setColor(rlutil::CYAN);
        cin >> idPedido;
        limpiarConsola();

        for (int x = 0; x < pedArc1.getCantidad(); x++)
        {
            ped1 = pedArc1.leer(x);
            if (ped1.getIdPedido() == idPedido && ped1.getTipoPedido() == "e")
            {
                encontro = true;
                reg = x;
                ped1Aux = ped1;
            }
            else
            {
                if (ped1.getIdPedido() == idPedido && ped1.getTipoPedido() == "c")
                {
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::RED);
                    cout << "El pedido fue cancelado con anterioridad." << endl;
                    rlutil::setColor(rlutil::CYAN);
                    presioneUnaTecla();
                    limpiarConsola();
                    return menuEmpleadoEgreso(legajo);
                }
                else
                {
                    if (ped1.getIdPedido() == idPedido && ped1.getTipoPedido() == "i")
                    {
                        ubicar(27, 10);
                        rlutil::setColor(rlutil::RED);
                        cout << "Usted no esta habilitado para cancelar pedidos de INGRESO de productos" << endl;
                        rlutil::setColor(rlutil::CYAN);
                        return menuEmpleadoEgreso(legajo);
                        presioneUnaTecla();
                        limpiarConsola();
                    }
                }
            }
        }
        if (encontro == false)
        {
            ubicar(27, 10);
            rlutil::setColor(rlutil::RED);
            cout << "No se encontro ningun pedido" << endl;
            rlutil::setColor(rlutil::CYAN);
            presioneUnaTecla();
            limpiarConsola();
            return menuEmpleadoEgreso(legajo);
        }
        else
        {
            ubicar(27, 10);
            rlutil::setColor(rlutil::GREEN);
            cout << "Pedido encontrado!" << endl;
            rlutil::setColor(rlutil::CYAN);
            presioneUnaTecla();
            limpiarConsola();
            do
            {
                int opcion;
                ubicar(27, 10);
                rlutil::setColor(rlutil::CYAN);
                cout << "=======================================================" << endl;
                ubicar(27, 11);
                cout << "CANCELAR PEDIDOS" << endl;
                ubicar(27, 12);
                cout << "=======================================================" << endl;
                ubicar(27, 13);
                cout << "1- Cancelar el pedido: "<<ped1Aux.getIdPedido()<< endl;
                ubicar(27, 14);
                cout << "2- Volver" << endl << endl;;

                ubicar(27, 15);
                rlutil::setColor(rlutil::WHITE);
                cout << "Ingrese una opcion: ";
                ubicar(27, 16);
                rlutil::setColor(rlutil::CYAN);
                cin >> opcion;
                limpiarConsola();

                if (opcion != 1 && opcion != 2)
                {
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::RED);
                    cout << "Opcion Incorrecta" << endl;
                    rlutil::setColor(rlutil::CYAN);
                    presioneUnaTecla();
                    limpiarConsola();
                }
            } while (opcion != 1 && opcion != 2);

            if (opcion == 1)
            {
                ped1Aux.setTipoPedido("c");
                pedArc1.guardar(ped1Aux, reg);
                ubicar(27, 10);
                rlutil::setColor(rlutil::GREEN);
                cout << "Pedido " << ped1Aux.getIdPedido() << " cancelado con exito!" << endl;
                rlutil::setColor(rlutil::CYAN);
                presioneUnaTecla();
                limpiarConsola();
                return menuEmpleadoEgreso(legajo);
            }
            else
            {
                return menuEmpleadoEgreso(legajo);
                limpiarConsola();
            }
        }
        return menuEmpleadoEgreso(legajo);
        break;
    }
    case 4:
        return menuEmpleado();
        break;
    }
    
    

}   

//TODO: Login administrador
void menuAdmin()
{
    int legajo;
    int password;
    int intentos = 0;
    Empleado e, admin;
    EmpleadosArchivo ea;
    bool ingreso = false;
    bool repite = true;
    
    
    /*char caracter;// clave asterisco
    string pasword;*/
    limpiarConsola();

    do
    {
        //TODO: Ingreso Administrador
        ubicar(27, 10);
        rlutil::setColor(rlutil::YELLOW);
        cout << "                INGRESO ADMINISTRADOR" << endl;
        ubicar(27, 11);
        cout << "=======================================================" << endl;
        ubicar(27, 12);
        rlutil::setColor(rlutil::WHITE);
        cout << "Ingrese nro de legajo: ";
        rlutil::setColor(rlutil::CYAN);
        cin >> legajo;
        ubicar(27, 13);
        rlutil::setColor(rlutil::WHITE);
        cout  << "Ingrese su clave de ingreso: ";
        rlutil::setColor(rlutil::CYAN);
        cin >> password;
         
        //TODO: CLave asterisco
        // cout<<"Ingrese su clave de ingreso: "<<endl<<endl;
        //caracter = getch();
        //while (caracter != 13)
        //{
        //    pasword.push_back(caracter);
        //    cout << "*";
        //    caracter = getch();
        //}




        limpiarConsola();

        for (int x = 0; x < ea.getCantidad(); x++)
        {
            e = ea.leer(x);
            if (e.getLegajo() == legajo && e.getPassword() == password && e.getCategoria()== 999)
            {
                admin = e;
                ubicar(27, 10);
                rlutil::setColor(rlutil::GREEN);
                cout << "Ingreso exitoso! Bienvenido " << admin.getNombre() << " " << admin.getApellido();
                rlutil::setColor(rlutil::CYAN);
                ingreso = true;
                repite = false;
                presioneUnaTecla();
                limpiarConsola();
            }
            else
            {
                if (e.getLegajo() == legajo && e.getPassword() == password && e.getCategoria() != 999)
                {
                    ubicar(27, 10);
                    rlutil::setColor(rlutil::RED);
                    cout << "Solamente se permite ingresos con cuenta ADMIN";
                    rlutil::setColor(rlutil::CYAN);
                    presioneUnaTecla();
                    limpiarConsola();
                    return menuAdmin();
                    
                }
            }
        }
        if (ingreso == false)
        {
            intentos++;
            if (intentos < 3 && intentos > 0)
            {
                limpiarConsola();   
                ubicar(27, 10);
                rlutil::setColor(rlutil::RED);
                cout << "Legajo o clave invalida, vuelva a intentar" << endl;
                rlutil::setColor(rlutil::CYAN);
                presioneUnaTecla();
                limpiarConsola();
            }
        }
        if (intentos == 3)
        {
            limpiarConsola();
            ubicar(27, 10);
            rlutil::setColor(rlutil::RED);
            cout << "Muchos ingresos fallidos, se cerrara el programa" << endl;
            rlutil::setColor(rlutil::CYAN);
            presioneUnaTecla();
            return;
        }
    }
    while (repite);

    menuPrincipalAdmin(admin);

}

//TODO: Menu de informes
void menuInformes()
{
    limpiarConsola();
    int opcion;
    int y = 0;
    int op = 1;
    do
    {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::setColor(rlutil::WHITE);
        rlutil::hidecursor();

        showItem("           Seleccione el informe requerido", 30, 8, 0);
        showItem("=======================================================", 30, 9, 0);
        showItem("         - Cantidad de pedidos por empleado            ", 30, 10, y == Opcion1);
        showItem("         - Cantidad de egresos por producto            ", 30, 11, y == Opcion2);
        showItem("         - Cantidad de ingresos por producto           ", 30, 12, y == Opcion3);
        showItem("         - Stock de productos por categoria            ", 30, 13, y == Opcion4);
        showItem("         - Productos mas vendidos en el mes            ", 30, 14, y == Opcion5);
        showItem("         - Historial productos menos vendidos          ", 30, 15, y == Opcion6);
        showItem("         - Resumen semanal de pedidos                  ", 30, 16 ,y == Opcion7);
        showItem("         - Volver al inicio de sesion                  ", 30, 17, y == Opcion8);
        showItem("=======================================================", 30, 18, 0);
        showItem("                     - Volver                          ", 30, 19 ,y == Opcion9);

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
            if (y > 8) {
                y = 8;
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
            case 3:
                op = 0;
                break;
            case 4:
                op = 0;
                break;
            case 5:
                op = 0;
                break;
            case 6:
                op = 0;
                break;
            case 7:
                op = 0;
                break;
            case 8:
                op = 0;
                break;
            }
        }
       
    }while (op != 0);

    //TODO: FALTA HACER 
    switch (y)
    {
    case 0:
    {
        //mostrar informe Cantidad de pedidos por empleado
    }
        break;
    case 1:
    {
        //mostrar informe Cantidad de egresos por producto
    }
        break;
    case 2:
    {
        //mostrar informe Cantidad de ingresos por producto
    }
        break;
    case 3:
    {
        //mostrar informe Stock de productos por categoria
    }
        break;
    case 4:
        //mostrar informe Productos más vendidos en el mes
        break;
    case 5:
    {
        //mostrar informe Historial productos menos vendidos
    }
        break;
    case 6:
    {
        //mostrar informe Resumen semanal de pedidos
    }
        break;
    case 7:
        return menuAdmin();
        break;
    }
}

//TODO: Menu principal del administrador
void menuPrincipalAdmin(Empleado admin)
{
    int op=1;
    int y = 0;
    limpiarConsola();
    do
    {
    rlutil::setBackgroundColor(rlutil::BLACK);
    rlutil::setColor(rlutil::WHITE);
    rlutil::hidecursor();

    showItemEgreso("                  MENU ADMINISTRADOR", 30, 8, 0);
    showItemEgreso("=======================================================", 30, 9, 0);
    showItemEgreso("- Solicitar informes            ", 30, 10, y == Opcion1);
    showItemEgreso("- Alta empleado                 ", 30, 11, y == Opcion2);
    showItemEgreso("- Baja a empleado               ", 30, 12, y == Opcion3);
    showItemEgreso("- Modificar datos empleado      ", 30, 13, y == Opcion4);
    showItemEgreso("- Alta productos                ", 30, 14, y == Opcion5);
    showItemEgreso("- Baja de productos             ", 30, 15, y == Opcion6);
    showItemEgreso("- Modificar productos           ", 30, 16, y == Opcion7);
    showItemEgreso("=======================================================", 30, 18, 0);
    showItemEgreso("- Volver a inicio de sesion     ", 30, 17, y == Opcion8);
    showItemEgreso("- Menu principal                ", 30, 19, y == Opcion9);

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
        if (y > 8) {
            y =8;
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
        case 2:
            op = 0;
            break;
        case 3:
            op = 0;
            break;
        case 4:
            op = 0;
            break;
        case 5:
            op = 0;
            break;
        case 6:
            op = 0;
            break;
        case 7:
            op = 0;
            break;
        case 8:
            op = 0;
            break;

        }
    }

} while (op != 0);

    switch (y)
    {
    case 0:
        menuInformes();
        return menuPrincipalAdmin(admin);
        break;
    case 1:
    {
        Empleado e;
        EmpleadosArchivo ea;
        cin.ignore();
        e.cargar();
        ea.guardar(e);
        return menuPrincipalAdmin(admin);
        break;
    }
    case 2:
        menuBajaEmpleado(admin);
        return menuPrincipalAdmin(admin);
        break;
    case 3:
        rlutil::setColor(rlutil::CYAN);
        rlutil::setBackgroundColor(rlutil::BLACK);
        menuEditarEmpleado(admin);
        return menuPrincipalAdmin(admin);
        break;
    case 4:
        Producto prod;
        ProductosArchivo prodArc;
        cin.ignore();
        prod.cargar();
        prodArc.guardar(prod);
        return menuPrincipalAdmin(admin);
        break;

    case 5:
        limpiarConsola();
        menuBajaProducto();
        return menuPrincipalAdmin(admin);
        break;
    case 6:
        limpiarConsola();
        menuEditarProducto();
        return menuPrincipalAdmin(admin);
        break;
    case 7:
        limpiarConsola();
        return menuAdmin();
        break;
    case 8:
        limpiarConsola();
        return menuPrincipal();
        break;
    }
}

//TODO: Menu baja de empleados
void menuBajaEmpleado(Empleado admin)
{
    Empleado e, eAux;
    EmpleadosArchivo ea;
    int legajo;
    int opcion;
    bool encontro = false;
    int password;
    int intentos = 0;
    int reg;
    bool dadoDeBaja = false;
    int op = 1;
    int y = 0;

    limpiarConsola();
    rlutil::setColor(rlutil::YELLOW);
    ubicar(27, 10);
    cout << "BAJA DE EMPLEADO" << endl;
    ubicar(27, 11);
    cout << "=======================================================" << endl;
    ubicar(27, 12);
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingrese el legajo del empleado: ";
    ubicar(27, 13);
    rlutil::setColor(rlutil::CYAN);
    cin >> legajo;
    limpiarConsola();
    //pedirle la clave para volver a validar que sea el admin

    for (int x = 0; x < ea.getCantidad(); x++)
    {
        e = ea.leer(x);

        if (e.getLegajo() == legajo && e.getEstado() == true && e.getCategoria() == 999)
        {
            ubicar(27, 10);
            rlutil::setColor(rlutil::RED);
            cout << "No se permite dar de baja a otro ADMIN" << endl;
            presioneUnaTecla();
            limpiarConsola();
            return menuPrincipalAdmin(admin);
        }
        if (e.getLegajo() == legajo && e.getEstado() == false)
        {
            limpiarConsola();
            ubicar(27, 10);
            rlutil::setColor(rlutil::RED);
            cout << "El empleado ya fue dado de baja anteriormente" << endl;
            dadoDeBaja = true;
            presioneUnaTecla();
            limpiarConsola();
            return menuPrincipalAdmin(admin);
            
        }
        else
        {
            if (e.getLegajo() == legajo && e.getEstado() == true && admin.getLegajo()== legajo)
            {
                limpiarConsola();
                ubicar(27, 10);
                rlutil::setColor(rlutil::RED);
                cout << "Sin permiso a darse de baja como ADMIN";
                presioneUnaTecla();
                limpiarConsola();
                return menuPrincipalAdmin(admin);
            }
            else
            {
                if (e.getLegajo() == legajo && e.getEstado() == true)
                {
                    eAux = e;
                    encontro = true;
                    reg = x;
                }

            }


        }
    }
    if (encontro == true && dadoDeBaja == false)
    {
        rlutil::setColor(rlutil::GREEN);
        limpiarConsola();
        ubicar(27, 10);
        cout << "Empleado encontrado!" << endl;
        ubicar(27, 12);
        rlutil::setColor(rlutil::WHITE);
        cout << "Presione una tecla para continuar.." << endl;
        rlutil::setColor(rlutil::CYAN);
        presioneUnaTecla();
        limpiarConsola();

        rlutil::setColor(rlutil::YELLOW);
        ubicar(27, 10);
        cout << "               Solicitud Baja de empleado" << endl;
        ubicar(27, 11);
        cout << "=======================================================" << endl;
        ubicar(27, 12);
        rlutil::setColor(rlutil::CYAN);
        cout << "Nombre: ";
        rlutil::setColor(rlutil::WHITE);
        cout << eAux.getNombre();
        rlutil::setColor(rlutil::CYAN);
        ubicar(27, 13);
        cout << "Apellido: ";
        rlutil::setColor(rlutil::WHITE);
        cout << eAux.getApellido();
        ubicar(27, 14);
        cout << "Legajo: ";
        rlutil::setColor(rlutil::WHITE);
        cout << eAux.getLegajo();


        do
        {
            rlutil::setBackgroundColor(rlutil::BLACK);
            rlutil::setColor(rlutil::WHITE);
            rlutil::hidecursor();
            showItemEgreso("               Desea darlo de baja?", 27, 16, 0);
            showItemEgreso("=======================================================", 27, 17, 0);
            showItemEgreso("                - Si, dar de baja                      ", 27, 18, y == Opcion1);
            showItemEgreso("                - Cancelar                             ", 27, 19, y == Opcion2);

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


    if (y == 0)
    {
        ubicar(27, 10);
        rlutil::setColor(rlutil::WHITE);
        cout << "Ingrese su clave personal" << endl;
        ubicar(27, 11);
        rlutil::setColor(rlutil::CYAN);
        cin >> password;
        limpiarConsola();

        while (admin.getPassword() != password)
        {
            ubicar(27, 10);
            rlutil::setColor(rlutil::RED);
            cout << "Clave invalida, Intente nuevamente" << endl;
            ubicar(27, 11);
            rlutil::setColor(rlutil::WHITE);
            cout <<endl<< "Ingrese su clave personal" << endl;
            ubicar(27, 12);
            rlutil::setColor(rlutil::CYAN);
            cin >> password;

            intentos++;
            if (intentos == 3)
            {
                ubicar(27, 10);
                rlutil::setColor(rlutil::RED);
                cout << "Demaciados intentos fallidos, se cerrara el programa" << endl;
                rlutil::setColor(rlutil::CYAN);
                presioneUnaTecla();
                return;
            }
        }
        limpiarConsola();
        eAux.setEstado(false);
        ea.guardar(eAux, reg);
        ubicar(27, 10);
        rlutil::setColor(rlutil::GREEN);
        cout << "El empleado a sido dado de baja con exito!" << endl;
        rlutil::setColor(rlutil::CYAN);
        presioneUnaTecla();
        limpiarConsola();
        return menuPrincipalAdmin(admin);
    }

    }
    else
    {
        ubicar(27, 10);
        rlutil::setColor(rlutil::RED);
        cout << "No se encontro el empleado solicitado" << endl;
        rlutil::setColor(rlutil::CYAN);
        return menuPrincipalAdmin(admin);
    }
}

//TODO: Menu editar empleados
void menuEditarEmpleado(Empleado admin)
{
    Empleado e, eAux;
    EmpleadosArchivo ea; 
    int legajo;
    bool encontro = false;
    int reg;
    int op = 1;
    int y = 0;

    limpiarConsola();
    ubicar(27, 10);
    rlutil::setColor(rlutil::YELLOW);
    cout << "                   EDITAR EMPLEADO" << endl;
    ubicar(27, 11);
    cout << "=======================================================" << endl;
    ubicar(27, 12);
    rlutil::setColor(rlutil::WHITE);
    cout << "Ingrese el legajo del empleado: ";//Validar que el legajo este en el sistema antes de pedir la opcion a modificar
    rlutil::setColor(rlutil::CYAN);
    cin >> legajo;
    limpiarConsola();


    for (int x = 0; x < ea.getCantidad(); x++)
    {
        e = ea.leer(x);

        if (e.getLegajo() == legajo && e.getCategoria() == 999 && admin.getLegajo() != legajo)
        {
            ubicar(27, 10);
            cout << "No tiene permitido modificar los datos de otro ADMIN";
            presioneUnaTecla();
            return menuEditarEmpleado(admin);

        }
        else
        {

            if (e.getLegajo() == legajo)
            {
                limpiarConsola();
                encontro = true;
                ubicar(27, 10);
                rlutil::setColor(rlutil::GREEN);
                cout << "Empleado encontrado!" << endl;
                ubicar(27, 11);
                cout << "Nombre: " << e.getNombre()<<endl;
                ubicar(27, 12);
                cout << "Apellido: " << e.getApellido()<<endl;
                ubicar(27, 13);
                cout << "Legajo: " << e.getLegajo()<<endl;
                rlutil::setColor(rlutil::CYAN);

                eAux = e;
                reg = x;
                presioneUnaTecla();
                limpiarConsola();

            }
        }
    }
    if (encontro == true)
    {

        do
        {
            rlutil::setBackgroundColor(rlutil::BLACK);
            rlutil::setColor(rlutil::WHITE);
            rlutil::hidecursor();
            //limpiarConsola();
            showItemEgreso("              SELECCIONAR DATO A MODIFICAR", 30, 8, 0);
            showItemEgreso("=======================================================", 30, 10, 0);
            showItemEgreso("                    - Nombre                           ", 30, 11, y == Opcion1);
            showItemEgreso("                    - Apellido                         ", 30, 12, y == Opcion2);
            showItemEgreso("                    - DNI                              ", 30, 13, y == Opcion3);
            showItemEgreso("                    - Domicilio                        ", 30, 14, y == Opcion4);
            showItemEgreso("                    - Email                            ", 30, 15, y == Opcion5);
            showItemEgreso("                    - Telefono                         ", 30, 16, y == Opcion6);
            showItemEgreso("                    - Categoria                        ", 30, 17, y == Opcion7);
            showItemEgreso("                    - Clave                            ", 30, 18, y == Opcion8);
            showItemEgreso("=======================================================", 30, 19, 0);
            showItemEgreso("                        VOLVER                         ", 30, 20, y == Opcion9);

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
                if (y > 8) {
                    y = 8;
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
                case 2:
                    op = 0;
                    break;
                case 3:
                    op = 0;
                    break;
                case 4:
                    op = 0;
                    break;
                case 5:
                    op = 0;
                    break;
                case 6:
                    op = 0;
                    break;
                case 7:
                    op = 0;
                    break;
                case 8:
                    op = 0;
                    break;
                }

            }

        } while (op != 0);

        cin.ignore();
    }
    else
    {
        limpiarConsola();
        ubicar(27, 10);
        rlutil::setColor(rlutil::RED);
        cout << "No se encontro el empleado solicitado" << endl;
        rlutil::setColor(rlutil::CYAN);
        limpiarConsola();
    }

    
    switch (y)
    {
    case 0:
        limpiarConsola();
        char nombre[30];
        ubicar(27, 10);
        rlutil::setColor(rlutil::YELLOW);
        cout<<"Ingrese nuevo nombre: ";
        rlutil::setColor(rlutil::CYAN);
        cin.getline(nombre, 30, '\n');
        eAux.setNombre(nombre);
        ea.guardar(eAux, reg);
        ubicar(27, 12);
        rlutil::setColor(rlutil::GREEN);
        cout << "Nombre actualizado con exito!" << endl;
        presioneUnaTecla();
        limpiarConsola();
        break;
    case 1:
        limpiarConsola();
        char apellido[30];
        ubicar(27, 10);
        rlutil::setColor(rlutil::YELLOW);
        cout << "Ingrese nuevo apellido: ";
        rlutil::setColor(rlutil::CYAN);
        cin.getline(apellido, 30, '\n');
        eAux.setApellido(apellido);
        ea.guardar(eAux, reg);
        ubicar(27, 12);
        rlutil::setColor(rlutil::GREEN);
        cout << "Apellido actualizado con exito!" << endl;
        presioneUnaTecla();
        limpiarConsola();
        break;
    case 2:
        limpiarConsola();
        int dni;
        rlutil::setColor(rlutil::YELLOW);
        ubicar(27, 10);
        cout << "Ingrese nuevo numero de dni: ";
        rlutil::setColor(rlutil::CYAN);
        cin >> dni;
        eAux.setDni(dni);
        ea.guardar(eAux, reg);
        ubicar(27, 12);
        rlutil::setColor(rlutil::GREEN);
        cout << "DNI actualizado con exito!" << endl;
        presioneUnaTecla();
        limpiarConsola();
        break;
    case 3:
    {
        limpiarConsola();
        Domicilio dom;
        ubicar(27, 10);
        rlutil::setColor(rlutil::YELLOW);
        cout << "Actualizacion de domicilio" << endl;
        rlutil::setColor(rlutil::CYAN);
        dom.cargar();
        eAux.setDomicilio(dom);
        ea.guardar(eAux, reg);
        ubicar(27, 12);
        rlutil::setColor(rlutil::GREEN);
        cout << "Domicilio actualizado con exito!" << endl;
        presioneUnaTecla();
        limpiarConsola();
        break;
    }
    case 4:
        limpiarConsola();
        char email[30];
        ubicar(27, 10);
        rlutil::setColor(rlutil::YELLOW);
        cout << "Ingrese nuevo email: ";
        rlutil::setColor(rlutil::CYAN);
        cin.getline(email, 30, '\n');
        ea.guardar(eAux, reg);
        ubicar(27, 12);
        rlutil::setColor(rlutil::GREEN);
        cout << "Email actualizado con exito!" << endl;
        presioneUnaTecla();
        break;

    case 5:
        limpiarConsola();
        int telefono;
        ubicar(27, 10);
        rlutil::setColor(rlutil::YELLOW);
        cout << "Ingrese nuevo nro de telefono: ";
        rlutil::setColor(rlutil::CYAN);
        cin >> telefono;
        eAux.setTelefono(telefono);
        ea.guardar(eAux, reg);
        ubicar(27, 12);
        rlutil::setColor(rlutil::GREEN);
        cout << "Telefono actualizado con exito!" << endl;
        presioneUnaTecla();
        break;
    case 6:
        limpiarConsola();
        int categoria;
        do
        {

            ubicar(27, 10);
            rlutil::setColor(rlutil::YELLOW);
            cout << "Ingrese nueva categoria: ";
            rlutil::setColor(rlutil::CYAN);
            cin >> categoria;

            if (categoria != 1 && categoria != 2 && categoria != 999)
            {
                ubicar(27, 12);//No lo detecta el ubicar()
                rlutil::setColor(rlutil::RED);
                cout << endl<<"                           Ingrese una categoria valida ";
                rlutil::setColor(rlutil::CYAN);
                presioneUnaTecla();
                limpiarConsola();
            }


        } while (categoria!= 1 && categoria!= 2 && categoria !=999);

        eAux.setCategoria(categoria);
        ea.guardar(eAux, reg);
        ubicar(27, 12);
        rlutil::setColor(rlutil::GREEN);
        cout << "Categoria actualizada con exito!" << endl;
        presioneUnaTecla();
        break;
    case 7:
        limpiarConsola();
        int password;
        ubicar(27, 10);
        rlutil::setColor(rlutil::YELLOW);
        cout << "Ingrese nueva contraseña: ";
        rlutil::setColor(rlutil::CYAN);
        cin >> password;
        eAux.setPassword(password);
        ea.guardar(eAux, reg);
        ubicar(27, 12);
        
        rlutil::setColor(rlutil::GREEN);
        cout << "Contraseña actualizada con exito!" << endl;
        presioneUnaTecla();
        break;
    case 8:
        break;
    }
    

}

//TODO: Menu baja de productos
void menuBajaProducto()
{
}

//TODO:Menu editar productos
void menuEditarProducto()
{
    //rlutil::setBackgroundColor(rlutil::BLACK);
    //rlutil::setColor(rlutil::WHITE);
    //rlutil::hidecursor();
    //limpiarConsola();
    //showItemEgreso("            SELECCIONAR DATO A MODIFICAR", 30, 8, 0);
    //showItemEgreso("=======================================================", 30, 10, 0);
    //showItemEgreso("- Nombre         ", 38, 11, y == Opcion1);
    //showItemEgreso("- Marca          ", 38, 12, y == Opcion2);
    //showItemEgreso("- Cod Categoria  ", 38, 13, y == Opcion3);
    //showItemEgreso("- Precio         ", 38, 14, y == Opcion4);
    //showItemEgreso("- Stock          ", 38, 15, y == Opcion5);
    //showItemEgreso("=======================================================", 30, 16, 0);
    //showItemEgreso("-                      VOLVER                         ", 38, 17, y == Opcion6);
}

//TODO: MOSTRAR ITEMS DE LOS MENU
void showItem(const char* text, int posx, int posy, bool selected) {

    if (selected) {
        rlutil::setBackgroundColor(rlutil::MAGENTA);
        rlutil::locate(posx - 3, posy);
        std::cout << " " << (char)175 << " " << text << " " << (char)174 << " " << std::endl;

    }
    else {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::locate(posx - 3, posy);
        std::cout << "   " << text << "   " << std::endl;
    }

    rlutil::setBackgroundColor(rlutil::BLACK);
}
void showItemIngreso(const char* text, int posx, int posy, bool selected) {

    if (selected) {
        rlutil::setBackgroundColor(rlutil::LIGHTBLUE);
        rlutil::locate(posx - 3, posy);
        std::cout << " " << (char)175 << " " << text << " " << (char)174 << " " << std::endl;

    }
    else {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::locate(posx - 3, posy);
        std::cout << "   " << text << "   " << std::endl;
    }

    rlutil::setBackgroundColor(rlutil::BLACK);
}
void showItemEgreso(const char* text, int posx, int posy, bool selected) {

    if (selected) {
        rlutil::setBackgroundColor(rlutil::LIGHTRED);
        rlutil::locate(posx - 3, posy);
        std::cout << " " << (char)175 << " " << text << " " << (char)174 << " " << std::endl;

    }
    else {
        rlutil::setBackgroundColor(rlutil::BLACK);
        rlutil::locate(posx - 3, posy);
        std::cout << "   " << text << "   " << std::endl;
    }

    rlutil::setBackgroundColor(rlutil::BLACK);
}
void ubicar(int posx, int posy)
{
    rlutil::locate(posx, posy);
}
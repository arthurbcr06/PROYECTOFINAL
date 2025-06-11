#include <iostream>
#include <vector>
#include <fstream>
#include <cstdlib>
#include <ctime>
#include <stdexcept>
#include <sstream>
#include <locale.h>
#include "Vuelo.h"

//g++ main.cpp Vuelo.cpp -o proyecto_final

// eso verifica si la fecha es valida calculando el dia y mes
bool esFechaValida(const std::string& fecha) {
    int dia, mes;
    char sep;
    std::istringstream iss(fecha);
    if (!(iss >> dia >> sep >> mes) || sep != '/' || dia < 1 || mes < 1 || mes > 12) return false;

    int diasEnMes[] = { 31,28,31,30,31,30,31,31,30,31,30,31 };
    return dia <= diasEnMes[mes - 1];
}

// eso verifica si la hora es valida calculando la hora y minuto
bool esHoraValida(const std::string& hora) {
    int h, m;
    char sep;
    std::istringstream iss(hora);
    if (!(iss >> h >> sep >> m) || sep != ':' || h < 0 || h > 23 || m < 0 || m > 59)
        return false;
    return true;
}

// nos permite obtener la duracion del vuelo en minutos
int obtenerDuracion(const std::string& salida, const std::string& llegada) {
    if ((salida == "Paris" && llegada == "Tokyo") || (salida == "Tokyo" && llegada == "Paris"))
        return 720;
    if ((salida == "Paris" && llegada == "Londres") || (salida == "Londres" && llegada == "Paris"))
        return 60;
    if ((salida == "NewYork" && llegada == "Londres") || (salida == "Londres" && llegada == "NewYork"))
        return 420;
    return 120;
}

// para agregar un vuelo al vector y guardarlo en el archivo
void agregarVuelo(std::vector<Vuelo>& vuelos, const std::string& nombreArchivo) {
    try {
        std::string dia, hora, salida, llegada;

        do {
            std::cout << "Dia del vuelo (dd/mm): ";
            std::cin >> dia;
            if (!esFechaValida(dia)) std::cout << "Fecha invalida. Reintente.\n";
        } while (!esFechaValida(dia));

        do {
            std::cout << "Hora del vuelo (hh:mm): ";
            std::cin >> hora;
            if (!esHoraValida(hora)) std::cout << "Hora invalida. Reintente.\n";
        } while (!esHoraValida(hora));

        std::cout << "Ciudad de salida: ";
        std::cin >> salida;
        std::cout << "Ciudad de llegada: ";
        std::cin >> llegada;

        int duracion = obtenerDuracion(salida, llegada);
        int ocupacion = std::rand() % 101;

        Vuelo v(dia, hora, duracion, salida, llegada, ocupacion);
        vuelos.push_back(v);

        std::ofstream archivo(nombreArchivo, std::ios::app);
        if (!archivo) throw std::runtime_error("No se pudo abrir el archivo.");
        v.guardarEnArchivo(archivo);

        std::cout << "Vuelo agregado exitosamente.\n";
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
        std::cin.clear(); std::cin.ignore(10000, '\n');
    }
}

// nos permite consultar los vuelos guardados en el archivo
void consultarVuelos(const std::string& nombreArchivo) {
    try {
        std::ifstream archivo(nombreArchivo);
        if (!archivo) throw std::runtime_error("No se pudo abrir el archivo.");
        std::cout << "Lista de vuelos:\n";
        while (archivo.peek() != EOF) {
            Vuelo v; v.cargarDesdeArchivo(archivo);
            if (archivo) v.mostrar();
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

// eso mostra las emisiones de carbono por vuelo
void mostrarEmisiones(const std::string& nombreArchivo) {
    try {
        std::ifstream archivo(nombreArchivo);
        if (!archivo) throw std::runtime_error("No se pudo abrir el archivo.");
        std::cout << "Emisiones de carbono por vuelo:\n";
        while (archivo.peek() != EOF) {
            Vuelo v; v.cargarDesdeArchivo(archivo);
            if (archivo) {
                v.mostrar();
                std::cout << "Emision estimada: " << v.calcularEmisionCarbono() << " kg CO2\n";
            }
        }
    } catch (const std::exception& e) {
        std::cerr << "Error: " << e.what() << std::endl;
    }
}

int main() {
    setlocale(LC_ALL, "");
    std::srand(std::time(nullptr));
    try {
        std::vector<Vuelo> vuelos;
        const std::string nombreArchivo = "vuelos.txt";
        int opcion = 0;
        do {
            std::cout << "\n--- Menu ---\n";
            std::cout << "1. Agregar un vuelo\n";
            std::cout << "2. Consultar vuelos\n";
            std::cout << "3. Ver emisiones de carbono\n";
            std::cout << "4. Salir\n";
            std::cout << "Elige una opcion: ";
            std::cin >> opcion;
            if (std::cin.fail()) throw std::invalid_argument("Opcion no valida.");

            switch (opcion) {
                case 1: agregarVuelo(vuelos, nombreArchivo); break;
                case 2: consultarVuelos(nombreArchivo); break;
                case 3: mostrarEmisiones(nombreArchivo); break;
                case 4: std::cout << "Hasta luego!\n"; break;
                default: std::cout << "Opcion invalida.\n"; std::cin.clear(); std::cin.ignore(10000, '\n');
            }
        } while (opcion != 4);
    } catch (const std::exception& e) {
        std::cerr << "Error critico: " << e.what() << std::endl;
    }
    return 0;
}

#include "Vuelo.h"
#include <iostream>

//eso son los constructores y metodos de la clase Vuelo
Vuelo::Vuelo() : dia("Desconocido"), hora("00:00"), duracion(0), salida("Desconocido"), llegada("Desconocido"), ocupacion(0) {}
Vuelo::Vuelo(const std::string& dia, const std::string& hora, int duracion, const std::string& salida, const std::string& llegada, int ocupacion)
    : dia(dia), hora(hora), duracion(duracion), salida(salida), llegada(llegada), ocupacion(ocupacion) {}

// eso son los getters de la clase Vuelo
std::string Vuelo::getDia() const { return dia; }
std::string Vuelo::getHora() const { return hora; }
int Vuelo::getDuracion() const { return duracion; }
std::string Vuelo::getSalida() const { return salida; }
std::string Vuelo::getLlegada() const { return llegada; }
int Vuelo::getOcupacion() const { return ocupacion; }

// eso permite mostrar los detalles del vuelo
void Vuelo::mostrar() const {
    std::cout << "Dia: " << dia << ", Hora: " << hora << ", Duracion: " << duracion << " min"
              << ", Salida: " << salida << ", Llegada: " << llegada
              << ", Ocupacion: " << ocupacion << "%" << std::endl;
}

// eso permite guardar los detalles del vuelo en un archivo
void Vuelo::guardarEnArchivo(std::ofstream& archivo) const {
    archivo << dia << " " << hora << " " << duracion << " " << salida << " "
            << llegada << " " << ocupacion << std::endl;
}

// eso permite cargar los detalles del vuelo desde un archivo
void Vuelo::cargarDesdeArchivo(std::istream& archivo) {
    archivo >> dia >> hora >> duracion >> salida >> llegada >> ocupacion;
}

// eso representa el cálculo de las emisiones de carbono del vuelo ficticio
double Vuelo::calcularEmisionCarbono() const {
    return duracion * 0.15 * ocupacion / 100.0; 
}

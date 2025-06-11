#ifndef VUELO_H
#define VUELO_H
#include <string>
#include <fstream>

class Vuelo {
private:
    std::string dia;
    std::string hora;
    int duracion;
    std::string salida;
    std::string llegada;
    int ocupacion;

public:
    Vuelo();
    Vuelo(const std::string& dia, const std::string& hora, int duracion, const std::string& salida, const std::string& llegada, int ocupacion);
    std::string getDia() const;
    std::string getHora() const;
    int getDuracion() const;
    std::string getSalida() const;
    std::string getLlegada() const;
    int getOcupacion() const;
    void mostrar() const;
    void guardarEnArchivo(std::ofstream& archivo) const;
    void cargarDesdeArchivo(std::istream& archivo);
    double calcularEmisionCarbono() const;
};
#endif

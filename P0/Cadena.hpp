#ifndef CADENA_HPP_
#define CADENA_HPP_
#include <iostream>

class Cadena{
public:
    explicit Cadena(size_t n=0,char c =' ');//--constructor
    Cadena();//--constructor de cadena vacia
    Cadena(const char* s);//--constructor de cadena de caracteres de bajo nivel
    Cadena(const Cadena& cad,size_t inicial,size_t longitud=npos);//--constructor de copia a partir de otra sub cadena, con posicion incial y numero de caracteres
    Cadena(const char* s, size_t n);//--constructor de una cadena de caracteres de bajo nivel de lo n primeros caracteres
    Cadena& operator =(const Cadena& cad);//-------------------------------------------------------
    Cadena(const Cadena& cad);//--constructor de copia, nos hace falta porque tenemos un puntero en la parte privada, igual que la sobrecarga de '='
    static const size_t npos=-1;//constante
    operator const char*() const;//--constructor de conversion a const char*
    size_t length() const ;//--observador de la longitud de cadena
    Cadena& operator +=(const Cadena& cad);//concatenacion de cadena
    char& operator [](size_t indice);//para poder acceder a un caracter de la cadena
    const char& operator [](size_t indice)const;//idem pero solo con lectura
    const char& at(size_t indice)const;//para poder acceder a un caracter de la cadena, la funcion comprueba que la posicion no sobrepasa la cadena
    char& at(size_t indice);//idem, pero solo con lectura
    Cadena substr(size_t indice, size_t tam);//nos permite elegir el numero de caracteres de una cadena
    ~Cadena();//destructor

private:
  char* s_;//Es necesario sobrecargar el operador de asignacion '=' cuando en la parte privada hay punteros
  size_t tam_;

};

Cadena& operator +(const Cadena& cad1,const Cadena& cad2);
bool operator <(const Cadena& cad1,const Cadena& cad2);
bool operator >(const Cadena& cad1,const Cadena& cad2);
bool operator <=(const Cadena& cad1,const Cadena& cad2);
bool operator >=(const Cadena& cad1,const Cadena& cad2);
bool operator ==(const Cadena& cad1,const Cadena& cad2);
bool operator !=(const Cadena& cad1,const Cadena& cad2);

#endif // CADENA_HPP_

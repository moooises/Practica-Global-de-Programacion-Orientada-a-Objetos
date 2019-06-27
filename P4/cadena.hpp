#ifndef CADENA_HPP_
#define CADENA_HPP_
#include <iostream>
using namespace std;

class Cadena{
public:
    explicit Cadena(size_t n=0,char c =' ');//--constructor
    Cadena(const char* s);//--constructor de cadena de caracteres de bajo nivel
    Cadena(const Cadena& cad,size_t inicial,size_t longitud=npos);//--constructor de copia a partir de otra sub cadena, con posicion incial y numero de caracteres
    Cadena(const char* s, size_t n);//--constructor de una cadena de caracteres de bajo nivel de lo n primeros caracteres
    Cadena& operator =(const Cadena& cad);//-------------------------------------------------------
    Cadena& operator =(Cadena&& cad);//--
    Cadena(const Cadena& cad);//--constructor de copia, nos hace falta porque tenemos un puntero en la parte privada, igual que la sobrecarga de '='
    Cadena(Cadena&& cad);//-----constructor de movimiento
    static const size_t npos=-1;//constante
    const char* c_str() const;//--constructor de conversion a const char*
    size_t length() const ;//--observador de la longitud de cadena
    Cadena& operator +=(const Cadena& cad);//concatenacion de cadena
    char& operator [](size_t indice);//para poder acceder a un caracter de la cadena
    const char& operator [](size_t indice)const;//idem pero solo con lectura
    const char& at(size_t indice)const;//para poder acceder a un caracter de la cadena, la funcion comprueba que la posicion no sobrepasa la cadena
    char& at(size_t indice);//idem, pero solo con lectura
    Cadena substr(size_t indice, size_t tam);//nos permite elegir el numero de caracteres de una cadena
    ~Cadena();//destructor

    typedef char* iterator;
    typedef const char* const_iterator;
    typedef std::reverse_iterator<iterator> reverse_iterator;
    typedef std::reverse_iterator<const_iterator> const_reverse_iterator;

    iterator begin();
    const_iterator begin() const;

    const_iterator cbegin() const;

    reverse_iterator rbegin();
    const_reverse_iterator rbegin() const;

    const_reverse_iterator crbegin() const;

    iterator end();
    const_iterator end() const;

    const_iterator cend() const;

    reverse_iterator rend();
    const_reverse_iterator rend() const;

    const_reverse_iterator crend() const;


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

ostream& operator <<(ostream& os, const Cadena& cad);
istream& operator >>(istream& is, Cadena& cad);

namespace std {
    template <>
    struct hash<Cadena> {
        size_t operator()(const Cadena& cad) const {
            hash<string> hs;
            const char* p = cad.c_str();
            string s(p);
            size_t res = hs(s);
            return res;
                                                    }
                        };

            }
#endif // CADENA_HPP_


#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"

class Articulo{
public:
    Articulo(const Cadena& reff,const Cadena& tit,const Fecha& f, double prec, unsigned stoc);
    Cadena referencia() const;
    Cadena titulo() const;
    Fecha f_publi() const;
    double precio() const;
    double& precio();
    unsigned stock() const;
    unsigned& stock();

private:
    Cadena referencia_;
    Cadena titulo_;
    Fecha f_publi_;
    double precio_;
    unsigned stock_;

};

ostream& operator <<(ostream& os, const Articulo& art);

#endif

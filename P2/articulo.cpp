#include "articulo.hpp"
#include <iomanip>


Articulo::Articulo(const Cadena& reff,const Cadena& tit,const Fecha& f, double prec, unsigned stoc):
    referencia_(reff),titulo_(tit),f_publi_(f),precio_(prec),stock_(stoc){}

Cadena Articulo::referencia() const{
    return referencia_;
                                    }

Cadena Articulo::titulo() const{
    return titulo_;
                                }

Fecha Articulo::f_publi() const{
    return f_publi_;
                                }

double Articulo::precio() const{
    return precio_;
                                }

double& Articulo::precio(){
    return precio_;
                        }

unsigned Articulo::stock() const{
    return stock_;
                                }

unsigned& Articulo::stock(){
    return stock_;
                            }

ostream& operator <<(ostream& os, const Articulo& art) {
    os << "[" << art.referencia() << "] ";
    os << "\"" << art.titulo() << "\", ";
    os << art.f_publi().anno() << ". ";
    os << fixed << setprecision(2) << art.precio() << " €";
    return os;
                                                        }


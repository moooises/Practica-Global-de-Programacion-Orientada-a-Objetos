#include "articulo.hpp"
#include <iomanip>

Autor::Autor(const Cadena& nom, const Cadena& apell,const Cadena& direcc):nombre_(nom),apellidos_(apell),direccion_(direcc){}

Cadena Autor::nombre() const{
    return nombre_;
                            }

Cadena Autor::apellidos() const{
    return apellidos_;
                                }

Cadena Autor::direccion() const{
    return direccion_;
                                }
//------------------------------------------------------------------

Articulo::Articulo(const Articulo::Autores& a,const Cadena& reff,const Cadena& tit,const Fecha& f, double prec):
    referencia_(reff),titulo_(tit),f_publi_(f),precio_(prec){
        if(a.empty())throw Autores_vacios();
                                                            }

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

const Articulo::Autores& Articulo::autores() const{
    return autores_;
                                        }
//----------------------------------------------------

ArticuloAlmacenable::ArticuloAlmacenable(const Articulo::Autores& a,const Cadena& reff,const Cadena& tit,const Fecha& f, double prec,unsigned stoc):
    Articulo(a,reff,tit,f,prec),stock_(stoc){}

unsigned ArticuloAlmacenable::stock() const{
    return stock_;
                                }

unsigned& ArticuloAlmacenable::stock(){
    return stock_;
                            }

//-----------------------------------------------------------

Libro::Libro(const Articulo::Autores& a,const Cadena& reff, const Cadena& tit, const Fecha& f,double pre,unsigned npag, unsigned stoc):
    ArticuloAlmacenable(a,reff,tit,f,pre,stoc),n_pag_(npag){}

unsigned Libro::n_pag()const{
    return n_pag_;
                            }

void Libro::impresion_especifica(ostream& os) const{
    os<<n_pag_<<" págs., "<<stock()<<" unidades.";
                                                    }

//---------------------------------------------------------------

Cederron::Cederron(const Articulo::Autores& a, const Cadena& reff, const Cadena& tit,const Fecha& f, double pre,unsigned stoc,unsigned mb):
    ArticuloAlmacenable(a,reff,tit,f,pre,stoc),MB(mb){}

unsigned Cederron::tam() const{
    return MB;
                                }

void Cederron::impresion_especifica(ostream& os) const{
    os<<MB<<" MB, "<<stock()<<" unidades.";
                                                        }

//-----------------------------------------------------------------

LibroDigital::LibroDigital(const Articulo::Autores& a, const Cadena& reff, const Cadena& tit,const Fecha& f, double pre, const Fecha& fexpir):
    Articulo(a,reff,tit,f,pre),f_expir_(fexpir){}

Fecha LibroDigital::f_expir() const{
    return f_expir_;
                                    }

void LibroDigital::impresion_especifica(ostream& os) const{
    os<<"A la venta hasta  el "<<f_expir_<<".";
                                                            }

//-----------------------------------------------------------

ostream& operator <<(ostream& os, const Articulo& art) {
    os << "[" << art.referencia() << "] ";
    os << "\"" << art.titulo() << "\", de ";
    for(auto iter = art.autores().begin();iter!=art.autores().end();iter++){
        if(iter==--art.autores().end()) os<<(*iter)->apellidos();
        else os<<(*iter)->apellidos()<<", ";
                                                                                }
    os<<". ";
    os << art.f_publi().anno() << ". ";
    os << fixed << setprecision(2) << art.precio() << " €\t\n";
    art.impresion_especifica(os);
    return os;
                                                        }


#ifndef ARTICULO_HPP_
#define ARTICULO_HPP_

#include "cadena.hpp"
#include "fecha.hpp"

#include <set>

class Autor{
public:
    Autor(const Cadena& nom,const Cadena& apell, const Cadena& direcc);
    Cadena nombre() const;
    Cadena apellidos() const;
    Cadena direccion() const;

private:
    Cadena nombre_;
    Cadena apellidos_;
    Cadena direccion_;

};

class Articulo{
public:
    typedef set<Autor*> Autores;
    class Autores_vacios{};
    Articulo(const Autores& a,const Cadena& reff,const Cadena& tit,const Fecha& f, double prec);
    Cadena referencia() const;
    Cadena titulo() const;
    Fecha f_publi() const;
    double precio() const;
    double& precio();
    //unsigned stock() const;
    //unsigned& stock();
    const Autores& autores() const;

    virtual ~Articulo(){};
    virtual void impresion_especifica(ostream& os) const=0;

private:
    Cadena referencia_;
    Cadena titulo_;
    Fecha f_publi_;
    double precio_;
    //unsigned stock_;
    const Autores autores_;

};

ostream& operator <<(ostream& os, const Articulo& art);

class ArticuloAlmacenable: public Articulo{
public:
    ArticuloAlmacenable(const Articulo::Autores& a,const Cadena& reff,const Cadena& tit,const Fecha& f, double prec,unsigned stoc);
    unsigned stock() const;
    unsigned& stock();
private:
    unsigned stock_;
};

class Libro: public ArticuloAlmacenable{
public:
    Libro(const Articulo::Autores& a,const Cadena& reff, const Cadena& tit, const Fecha& f,double pre,unsigned npag, unsigned stoc);

    unsigned n_pag() const;

    void impresion_especifica(ostream& os) const;
private:
    unsigned n_pag_;

};

class Cederron: public ArticuloAlmacenable{
public:
    Cederron(const Articulo::Autores& a, const Cadena& reff, const Cadena& tit,const Fecha& f, double pre,unsigned stoc,unsigned mb);
    unsigned tam()const;
    void impresion_especifica(ostream& os)const;
private:
    unsigned MB;

};

class LibroDigital:public Articulo{
public:
    LibroDigital(const Articulo::Autores& a, const Cadena& reff, const Cadena& tit,const Fecha& f, double pre, const Fecha& fexpir);
    Fecha f_expir() const;
    void impresion_especifica(ostream& os)const;
private:
    Fecha f_expir_;
};

#endif

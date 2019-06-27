#ifndef USUARIO_HPP_INCLUDED
#define USUARIO_HPP_INCLUDED


#include "cadena.hpp"
#include "articulo.hpp"
#include "tarjeta.hpp"

#include <map>
#include <unordered_map>
#include <unordered_set>

class Tarjeta;
class Numero;

class Clave{
public:
    enum Razon{CORTA,ERROR_CRYPT};
    Clave(const char* s);
    class Incorrecta{

    public:
        Incorrecta(const Clave::Razon r);
        Clave::Razon razon() const;
    private:
        Clave::Razon r_;
    };


    Cadena& clave() const;
    bool verifica(const char* s)const;

private:
    Cadena clave_;

};


class Usuario{

public:
    Usuario(const Cadena& id,const Cadena& nombre, const Cadena& apellido,const Cadena& direcc, const Clave& clave);
    typedef std::map<Numero, Tarjeta*> Tarjetas;//un usuario puede tener varias tarjetas
    typedef std::unordered_map<Articulo*, unsigned int> Articulos;//Porque los articulos no estan repetidos

    class Id_duplicado{
    public:
        Id_duplicado(const Cadena& id);
        Cadena& idd() const;
    private:
        Cadena id_;
    };
    Usuario(const Usuario& us)= delete;
    Usuario& operator =(const Usuario& us)=delete;
    Cadena& id() const;
    Cadena& nombre() const;
    Cadena& apellidos() const;
    Cadena& direccion() const;
    const Tarjetas& tarjetas() const;
    void es_titular_de(Tarjeta& t);
    void no_es_titular_de(Tarjeta& t);
    ~Usuario();
    void compra(Articulo& art, const unsigned cantidad=1);
    const Articulos& compra()const;
    unsigned n_articulos() const;
    friend ostream& operator <<(ostream& os,const Usuario& us);
private:
    Cadena id_;
    Cadena nombre_;
    Cadena apellidos_;
    Cadena direccion_;
    Clave clave_;
    Tarjetas tarjetas_;
    Articulos articulos_;
    static unordered_set<Cadena> registrados;

};
ostream& operator <<(ostream& os,const Usuario& us);
ostream& mostrar_carro(ostream& os, const Usuario& us);

#endif // USUARIO_HPP_

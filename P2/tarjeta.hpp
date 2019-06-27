#ifndef TARJETA_HPP_
#define TARJETA_HPP_

#include "cadena.hpp"
#include "fecha.hpp"
#include "usuario.hpp"

class Usuario;

class Numero{
public:
    enum Razon{LONGITUD,DIGITOS,NO_VALIDO};

    class Incorrecto{
    public:
        Incorrecto(const Razon r);
        Razon razon()const;//-
    private:
        Razon razon_;
                    };

        Numero(const Cadena& num);
        operator const char*() const;

private:
    Cadena numero_;



};
bool operator <(const Numero& n1, const Numero& n2);

class Tarjeta{
public:
    enum Tipo{VISA,Mastercard,Maestro,JCB,AmericanExpress};

    class Caducada{
    public:
        Caducada(const Fecha& f);
        Fecha cuando() const;
    private:
        Fecha f_;
                    };
    Tarjeta(Tipo t,const Numero& num,Usuario& user,const Fecha& f);
    Tarjeta& operator =(const Tarjeta& t)=delete;
    Tarjeta(const Tarjeta& t)=delete;
    Tipo tipo() const;
    Numero numero() const;
    const Usuario* titular() const;
    Fecha caducidad() const;
    Cadena titular_facial() const;
    void anular_titular();
    ~Tarjeta();

private:
    Tipo tipo_;
    Numero numero_;
    const Usuario* titular_;
    Fecha caducidad_;
    Cadena titular_facial_;


};

ostream& operator <<(ostream& os,const Tarjeta& t);
ostream& operator <<(ostream& os, const Tarjeta::Tipo& tipo);

bool operator <(const Tarjeta& t1, const Tarjeta& t2);


#endif // TARJETA_HPP_

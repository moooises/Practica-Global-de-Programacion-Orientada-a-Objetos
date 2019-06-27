#ifndef FECHA_HPP_
#define FECHA_HPP_
#include<iostream>
using namespace std;

class Fecha{
public:
    class Invalida{
    public:
        Invalida(const char* s);
        const char* por_que() const;
    private:
        const char* s_;
    };

    explicit Fecha(int d=0,int m=0,int a=0);
    Fecha(const char* s);
    static const int AnnoMaximo=2037;
    static const int AnnoMinimo=1902;
    int dia() const;
    int mes() const;
    int anno() const;
    const char* cadena()const ;///////////////////
    Fecha& operator++();
    Fecha& operator--();
    Fecha& operator++(int);
    Fecha& operator--(int);
    Fecha& operator+=(int);
    Fecha& operator-=(int);

private:
    int dia_,mes_,anno_;
    void Fecha_Valida() const;
};

Fecha& operator +(const Fecha&,int);
Fecha& operator -(const Fecha&,int);
long operator -(const Fecha&,const Fecha&);
bool operator <(const Fecha&,const Fecha&);
bool operator >(const Fecha&,const Fecha&);
bool operator <=(const Fecha&,const Fecha&);
bool operator >=(const Fecha&,const Fecha&);
bool operator ==(const Fecha&,const Fecha&);
bool operator !=(const Fecha&,const Fecha&);

ostream& operator <<(ostream& os,const Fecha& f);
istream& operator >>(istream& is,const Fecha& f);

#endif // FECHA_HPP_


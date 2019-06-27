#include "Fecha.hpp"
#include <iostream>
#include <ctime>
#include <cstdio>
#include <string>

Fecha::Fecha(int d,int m,int a):dia_(d),mes_(m),anno_(a){
    if(dia_==0||mes_==0||anno_==0){
        time_t local=time(nullptr);
        tm* actual = localtime(&local);
        if(dia_==0)dia_=actual->tm_mday;
        if(mes_==0)mes_=actual->tm_mon+1;
        if(anno_==0)anno_=actual->tm_year+1900;
                                    }
    Fecha_Valida();

                                                            }

Fecha::Fecha(const char* s){
if(sscanf(s,"%d/%d/%d",&dia_,&mes_,&anno_)==3)*this=Fecha(dia_,mes_,anno_);
else throw Fecha::Invalida("Error: Formato introducido incorrecto");
                            }

inline int Fecha::dia() const{return dia_;}
inline int Fecha::mes() const{return mes_;}
inline int Fecha::anno() const{return anno_;}

Fecha::operator const char*()const{
char*s=new char[40];
setlocale(LC_TIME,"");
tm f={};
f.tm_mday=dia_;
f.tm_mon=mes_-1;
f.tm_year=anno_-1900;
mktime(&f);
strftime(s,40,"%A %d de %B de %Y",&f);
return s;
                                        }

Fecha& Fecha::operator +=(int dias){
tm f={};
f.tm_mday=dia_+dias;
f.tm_mon=mes_-1;
f.tm_year=anno_-1900;
mktime(&f);
dia_=f.tm_mday;
mes_=f.tm_mon+1;
anno_=f.tm_year+1900;
Fecha_Valida();
return *this;
                                    }

Fecha& Fecha::operator -=(int dias){return *this+=-dias;}

Fecha& Fecha::operator ++(){return *this+=1;}

Fecha& Fecha::operator ++(int dias){return *this+=dias;}

Fecha& Fecha::operator --(){return *this+=-1;}

Fecha& Fecha::operator --(int dias){return *this+=-dias;}

Fecha& operator +(const Fecha& f, int dias){
Fecha aux(f);
aux+=dias;
return aux;
                                            }

Fecha& operator -(const Fecha& f, int dias){
Fecha aux(f);
aux+=-dias;
return aux;
                                            }

long operator -(const Fecha& fa, const Fecha& fb){
tm a={};
tm b={};
a.tm_mday=fa.dia();
a.tm_mon=fa.mes()-1;
a.tm_year=fa.anno()-1900;
b.tm_mday=fb.dia();
b.tm_mon=fb.mes()-1;
b.tm_year=fb.anno()-1900;
long dias = (long)difftime(mktime(&a),mktime(&b))/(24*60*60);
return dias;
                                                    }

bool operator <(const Fecha& fa,const Fecha& fb){
if(fa.anno()<fb.anno())return true;
else{
    if(fa.anno()==fb.anno() && fa.mes()<fb.mes())return true;
    else{
        if(fa.anno()==fb.anno() && fa.mes()==fb.mes() && fa.dia()<fb.dia())return true;
        else return false;
        }
    }

                                                }

bool operator >(const Fecha& fa, const Fecha& fb){return fb<fa;}

bool operator ==(const Fecha& fa, const Fecha& fb){
if(fa.dia()==fb.dia() && fb.mes()==fb.mes() && fa.anno()==fb.anno())return true;
else return false;
                                                    }

bool operator !=(const Fecha& fa, const Fecha& fb){return !(fa==fb);}

bool operator <=(const Fecha& fa, const Fecha& fb){return fa==fb || fa<fb;}

bool operator >=(const Fecha& fa, const Fecha& fb){return fb<=fa;}

void Fecha::Fecha_Valida() const{//Mirar excepciones
    if(anno_>AnnoMaximo) throw Fecha::Invalida("Error:Anno introducido superior a 2037");
    if(anno_<AnnoMinimo) throw Fecha::Invalida("Error: Anno introducidi inferior a 1902");
    if((mes_==1||mes_==3||mes_==5||mes_==7||mes_==8||mes_==10||mes_==12)&&(dia_>31 || dia_<1))
       throw Fecha::Invalida("Error: Ese mes tiene 31 dias");
    if((mes_==4||mes_==6||mes_==9||mes_==11)&&(dia_>30 || dia_<1))
        throw Fecha::Invalida("Error: Ese mes tiene 30 dias");
    if(mes_==2){
        if(dia_<1 || (dia_>28&&!((anno_%4==0)&&((anno_%100!=0)||(anno_%400==0)))))
            throw Fecha::Invalida("Error: Febrero tiene 28 dias, si su año no es bisiesto");
        if(dia_<1 || (dia_>29&&((anno_%4==0)&&((anno_%100!=0)||(anno_%400==0)))))
            throw Fecha::Invalida("Error: Febrero tiene 29 dias, si es un año bisiesto");
                }
    if(mes_<1 || mes_>12)throw Fecha::Invalida("Error: El mes debe estar comprendido entre 1 y 12");
                                }

Fecha::Invalida::Invalida(const char* s):s_(s){}

const char* Fecha::Invalida::por_que() const{return s_;}



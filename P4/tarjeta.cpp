#include "tarjeta.hpp"
#include <cstring>
#include <iomanip>
#include <algorithm>

bool luhn(const Cadena& numero);

bool EsBlanco::operator()(char c) const{
    return isspace(c);
                                        }

bool EsDigito::operator()(char c) const{
    return isdigit(c);
                                        }

Numero::Numero(const Cadena& num){
  size_t tam=num.length();
  char* tmp = new char[tam+1];
  strcpy(tmp,num.c_str());
  char* ini= tmp;
  char* fin=tmp+tam;
  fin=remove_if(ini,fin,EsBlanco());
  *fin='\0';
  tam=strlen(tmp);
  if(tam<13||tam>19)throw Numero::Incorrecto(Numero::LONGITUD);
  if(find_if(ini,fin,not1(EsDigito()))!=fin) throw Numero::Incorrecto(Numero::DIGITOS);
  if(!luhn(tmp))throw Numero::Incorrecto(Numero::NO_VALIDO);
  numero_=tmp;
  delete[] tmp;


  /**  unsigned digitos =0;
    Cadena::const_iterator iter=num.begin();
    while(iter!=num.end()){
        if(*iter!=' '){
            if(*iter<48 || *iter>57)throw Numero::Incorrecto(Numero::DIGITOS);
            else digitos++;
                        }
        iter++;
                            }
     if(digitos<13 || digitos>19)throw Numero::Incorrecto(Numero::LONGITUD);
     char* numero=new char[digitos];
     unsigned i=0;
     iter=num.begin();
     while(iter!=num.end()){
        if(*iter!=' '){
            numero[i]=*iter;
            ++i;
                        }
        else ++iter;
                            }
    if(!luhn(numero))throw Numero::Incorrecto(Numero::NO_VALIDO);
    numero_=numero;
    delete[]numero;*/
                                    }

Numero::operator const char*() const{
    return numero_.c_str();
                                    }

bool operator <(const Numero& n1,const Numero& n2){
    return strcmp(n1,n2)<0;
                                                    }

Numero::Incorrecto::Incorrecto(const Razon r):razon_(r){}

Numero::Razon Numero::Incorrecto::razon() const{
    return razon_;
                                    }

Tarjeta::Tarjeta(Tipo t,const Numero& num,Usuario& user,const Fecha& f):
        tipo_(t),numero_(num),titular_(&user),caducidad_(f){
    Fecha hoy;
    if(f<hoy)throw Tarjeta::Caducada(f);
    user.es_titular_de(*this);
    titular_facial_=user.nombre();
    titular_facial_+=" ";
    titular_facial_+=user.apellidos();
                                            }

const Tarjeta::Tipo& Tarjeta::tipo() const{
    return tipo_;
                            }

const Numero& Tarjeta::numero() const{
    return numero_;
                                }

Usuario* Tarjeta::titular() const{
    return titular_;
                                        }

const Fecha& Tarjeta::caducidad() const{
    return caducidad_;
                                }

const Cadena& Tarjeta::titular_facial() const{
    return titular_facial_;
                                        }

void Tarjeta::anular_titular(){
    titular_=nullptr;
                                }

Tarjeta::~Tarjeta(){
    Usuario* us = const_cast<Usuario*>(titular_);
    if(us!=nullptr){
        us->no_es_titular_de(*this);
                    }
                }

ostream& operator <<(ostream& os, const Tarjeta& t){
    os<<t.tipo()<<endl;
    os<<t.numero()<<endl;
    os<<t.titular_facial()<<endl;
    os<<"Caduca: "<<setfill('0')<<setw(2)<<t.caducidad().mes()<<"/"<<t.caducidad().anno()%100;
    return os;
                                                    }

ostream& operator <<(ostream& os, const Tarjeta::Tipo& tipo){
    switch(tipo){
        case Tarjeta::VISA: os<<"VISA";break;
        case Tarjeta::Mastercard: os<<"Mastercard";break;
        case Tarjeta::Maestro: os<<"Maestro";break;
        case Tarjeta::JCB: os<<"JCB";break;
        case Tarjeta::AmericanExpress: os<<"AmericanExpress";break;
                }
    return os;
                                                            }

bool operator <(const Tarjeta& t1,const Tarjeta& t2){
    return t1.numero()<t2.numero();
                                                    }

Tarjeta::Caducada::Caducada(const Fecha& f):f_(f){}

Fecha Tarjeta::Caducada::cuando() const{
    return f_;
                                        }

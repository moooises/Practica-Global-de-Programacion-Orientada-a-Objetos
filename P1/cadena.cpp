#include "cadena.hpp"
#include <iostream>
#include <cstring>
#include <stdexcept>

Cadena::Cadena(size_t n,char c):tam_(n){
    s_ = new char[tam_+1];
    for(size_t i=0;i<tam_;++i){
        s_[i]=c;
                            }
    s_[tam_]='\0';

                                        }

Cadena::Cadena(const char* s):tam_(strlen(s)){
    s_=new char[tam_+1];
    strcpy(s_,s);
                                                }

Cadena::Cadena(const char* s,size_t n):tam_(n){
    if(n>strlen(s))tam_=strlen(s);
    s_= new char[tam_+1];
    for(size_t i=0;i<tam_;++i){
        s_[i]=s[i];
                            }
    s_[tam_]='\0';
                                        }

Cadena::Cadena():tam_(0){
    s_= new char[tam_+1];
    s_[tam_]='\0';
                        }

Cadena::Cadena(const Cadena& cad):tam_(cad.tam_){
    s_=new char[tam_+1];
    strcpy(s_,cad.s_);
                                                    }

Cadena::Cadena(const Cadena& cad, size_t inicial, size_t longitud):tam_(longitud){
    if(inicial>cad.tam_-1)throw out_of_range("Error: fuera de rango");
    if(longitud==Cadena::npos || longitud>cad.tam_-inicial)tam_=cad.tam_-inicial;
    s_= new char[tam_+1];
    for(size_t i=0;i<tam_;++i){
        s_[i]=cad.s_[i+inicial];
                            }
    s_[tam_]='\0';
                                                                                    }

const char* Cadena::c_str() const{
    return s_;
                                    }

size_t Cadena::length() const{
    return tam_;
                             }

Cadena& Cadena::operator =(const Cadena& cad){
    if(this!=&cad){
        tam_=cad.tam_;
        delete[] s_;//------------------------------------------------
        s_= new char[tam_+1];
        strcpy(s_,cad.s_);
                    }
    return *this;
                                                }

char& Cadena::operator[](size_t indice){
    return s_[indice];
                                }
const char& Cadena::operator[](size_t indice)const{
    return s_[indice];
                                                    }

char& Cadena::at(size_t indice){
    if(indice>=tam_ || indice<0)throw out_of_range("Error: Fuera de rango");
    else return s_[indice];
                                }

const char& Cadena::at(size_t indice)const{
    if(indice>=tam_ || indice<0)throw out_of_range("Error: Fuera de rango");
    else return s_[indice];
}

Cadena::~Cadena(){
    delete[]s_;
                }

Cadena Cadena::substr(size_t indice,size_t tam){//�Por que no Cadena& ?
    if(indice<0 || indice>=tam_)throw out_of_range("Error: Fuera de rango");
    if(tam_-indice<tam)throw out_of_range("Error:Fuera de rango");
    return Cadena(*this,indice,tam);
                                                }

Cadena& Cadena::operator +=(const Cadena& cad){
    char* aux= new char[tam_+1];
    strcpy(aux,s_);
    delete[] s_;//----------------------------------------------
    tam_+=cad.tam_;
    s_=new char[tam_+1];
    strcpy(s_,aux);
    strcat(s_,cad.s_);
    return *this;

                                                }

Cadena& operator +(const Cadena& cad1,const Cadena& cad2){
    Cadena aux(cad1);
    aux+=cad2;
    return aux;
                                                            }

bool operator <(const Cadena& cad1,const Cadena& cad2){
    return strcmp(cad1.c_str(),cad2.c_str())<0;
                                                        }

bool operator >(const Cadena& cad1,const Cadena& cad2){
    return cad2<cad1;
                                                        }

bool operator ==(const Cadena& cad1,const Cadena& cad2){
    return strcmp(cad1.c_str(),cad2.c_str())==0;
                                                        }

bool operator !=(const Cadena& cad1,const Cadena& cad2){
    return !(cad1==cad2);
                                                        }

bool operator <=(const Cadena& cad1,const Cadena& cad2){
    return(cad1==cad2 || cad1<cad2);
                                                        }

bool operator >=(const Cadena& cad1,const Cadena& cad2){
    return(cad1==cad2 || cad2<cad1);
                                                        }


Cadena::Cadena(Cadena&& cad):s_(cad.s_),tam_(cad.tam_){
cad.tam_=0;
cad.s_=nullptr;
                                                            }

Cadena& Cadena::operator=(Cadena&& cad){
    s_=cad.s_;
    tam_=cad.tam_;
    cad.s_=nullptr;
    cad.tam_=0;
    return *this;

                                        }

ostream& operator <<(ostream& os,const Cadena cad){
    os<<cad.c_str();
    return os;

                                                    }

istream& operator >>(istream& is,Cadena& cad){
    char* aux= new char[32];
    is >> aux;
    Cadena nueva(aux);
    delete[] aux;
    cad=nueva;
    return is;
                                            }

Cadena::iterator Cadena::begin(){
    return s_;
                                }

Cadena::const_iterator Cadena::begin()const{
    return s_;
                                            }

Cadena::const_iterator Cadena::cbegin()const{
    return s_;
                                            }

Cadena::reverse_iterator Cadena::rbegin(){
    return reverse_iterator(end());
                                            }

Cadena::const_reverse_iterator Cadena::crbegin()const{
    return const_reverse_iterator(end());
                                                        }

Cadena::iterator Cadena::end(){
    return s_+tam_;
                                }

Cadena::const_iterator Cadena::end()const{
    return s_+tam_;
                                            }

Cadena::const_iterator Cadena::cend()const{
    return s_+tam_;
                                            }

Cadena::reverse_iterator Cadena::rend(){
    return reverse_iterator(begin());
                                        }

Cadena::const_reverse_iterator Cadena::rend()const{
    return const_reverse_iterator(begin());
                                            }

Cadena::const_reverse_iterator Cadena::crend()const{
    return const_reverse_iterator(begin());
                                                    }

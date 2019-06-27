#include "usuario.hpp"
#include <cstring>
#include <unistd.h>

Clave::Clave(const char* cad)
{
    if (strlen(cad) < 5) throw Incorrecta(Razon::CORTA);

	random_device r;
	uniform_int_distribution<size_t> dist(0, 63);

	char const chars[] ="./0123456789ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz";

	char salteado[2] ={chars[dist(r)],chars[dist(r)]};

	char* cadEncriptada = crypt(cad, salteado);

	if(cadEncriptada == nullptr) throw Incorrecta(Razon::ERROR_CRYPT);

	contra_ = cadEncriptada;
}

Cadena& Clave::clave()const{
    return clave_;
                            }

bool Clave::verifica(const char* s)const{
    return clave_==crypt(s,clave_.c_str());
                                        }

Clave::Incorrecta::Incorrecta(const Clave::Razon r):r_(r){}

Clave::Razon Clave::Incorrecta::razon()const {
    return r_;
                                            }

unordered_set<Cadena> Usuario::registrados;

Usuario::Usuario(const Cadena& id,const Cadena& nombre, const Cadena& apellido,const Cadena& direcc, const Clave& clave):
        id_(id),nombre_(nombre),apellidos_(apellido),direccion_(direcc),clave_(clave){
            if(!registrados.insert(id).second)throw Usuario::Id_duplicado(id);
            else registrados.insert(id);//--------------------------------------------------
                                                                                        }

Cadena& Usuario::id() const{
    return id_;
                            }

Cadena& Usuario::nombre()const{
    return nombre_;
                                }

Cadena& Usuario::apellidos()const{
    return apellidos_;
                                    }

Cadena& Usuario::direccion()const{
    return direccion_;
                                    }

const Usuario::Tarjetas Usuario::tarjetas() const{
    return tarjetas_;
                                                }

void Usuario::es_titular_de(Tarjeta& t){
    if(this==t.titular())tarjetas_.insert(make_pair(t.numero(),&t));
                                        }

void Usuario::no_es_titular_de(Tarjeta& t){
    t.anular_titular();
    tarjetas_.erase(t.numero());
                                            }

Usuario::~Usuario(){
    Usuario::Tarjetas::iterator iter = tarjetas_.begin();
    while(iter!=tarjetas_.end()){
        iter->second->anular_titular();
        iter++;
                                }
    registrados.erase(id_);
                    }

void Usuario::compra(Articulo& art,const unsigned cantidad){
    if(cantidad!=0)articulos_[&art]=cantidad;
    else articulos_.erase(&art);
                                                            }

const Usuario::Articulos& Usuario::compra() const{
    return articulos_;
                                                }
unsigned Usuario::n_articulos() const{
    return articulos_.size();
                                    }

ostream& operator <<(ostream& os, const Usuario& us){
    os<<us.id()<<" ["<<us.clave_.clave().c_str()<<"] "<<us.nombre()<<" "<<us.apellidos()<<endl;
    os<<us.direccion()<<endl;
    os<<"Tarjetas: "<<endl;
    Usuario::Tarjetas::const_iterator iter= us.tarjetas().begin();
    while(iter!=us.tarjetas().end()){
        os<<*iter->second<<endl;
        iter++;
                                    }
    return os;
                                                    }

ostream& mostrar_carro(ostream& os, const Usuario& us){
    os<<"Carrito de compra de "<<us.id()<<" [Articulos: "<<us.n_articulos()<<"]"<<endl;
    os<<"Cant.  Artículo"<<endl;
    os<<"=================================================="<<endl;
    Usuario::Articulos::const_iterator iter=us.compra().begin();
    while(iter!=us.us.compra().end()){
        os<<"   "<<iter->second<<"   "<<*iter->first<<endl;
        iter++;
                                    }
    return os;
                                                    }

Usuario::Id_duplicado::Id_duplicado(const Cadena& id):id_(id){}
Usuario::Id_duplicado::idd() const{return id_;}

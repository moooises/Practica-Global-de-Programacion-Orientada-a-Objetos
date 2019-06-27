#include "pedido.hpp"

#include <iomanip>

unsigned Pedido::n_total_pedidos_=0;

Pedido::Pedido(Usuario_Pedido& UsPe,Pedido_Articulo& PeAr,Usuario& user,const Tarjeta& tar,const Fecha& f):tarjeta_(&tar),fecha_(f){
    if(user.compra().empty())throw Pedido::Vacio(&user);
    if(tar.titular()!= &user)throw Pedido::Impostor(&user);
    if(tar.caducidad()<f)throw Tarjeta::Caducada(tar.caducidad());
    for(Usuario::Articulos::const_iterator iter = user.compra().begin();iter!= user.compra().end();iter++){
        if(iter->second > iter->first->stock()){
            const_cast<Usuario::Articulos&>(user.compra()).clear();//---------
            throw Pedido::SinStock(iter->first);
                                                }
                                                                                                            }
    UsPe.asocia(*this,user);
    total_=0;
    for(Usuario::Articulos::const_iterator iter=user.compra().begin();iter!=user.compra().end();iter++){
        total_+=iter->second*iter->first->precio();
        PeAr.pedir(*iter->first,*this,iter->first->precio(),iter->second);
        iter->first->stock()-=iter->second;
                                                                                                        }
    const_cast<Usuario::Articulos&>(user.compra()).clear();
    numero_= ++n_total_pedidos_;

                                                                                                                                                }

unsigned Pedido::numero() const{
    return numero_;
                                }

const Tarjeta* Pedido::tarjeta() const{
    return tarjeta_;
                                        }

Fecha Pedido::fecha() const{
    return fecha_;
                            }

double Pedido::total() const{
    return total_;
                            }

ostream& operator <<(ostream& os, const Pedido& p){
    os<<"Num. pedido: "<<p.numero()<<endl;
    os<<"Fecha:       "<<p.fecha()<<endl;
    os<<"Pagado con:  "<<*p.tarjeta()<<endl;
    os<<"Importe:     "<<fixed<<setprecision(2)<<p.total()<<" €";
    return os;
                                                    }

Pedido::Vacio::Vacio(Usuario* user):user_(user){}

Usuario& Pedido::Vacio::User() const{
    return *user_;
                                    }

Pedido::Impostor::Impostor(Usuario* user):user_(user){}

Usuario& Pedido::Impostor::User() const{
    return *user_;
                                        }

Pedido::SinStock::SinStock(Articulo*art):art_(art){}

Articulo& Pedido::SinStock::articulo() const{
    return *art_;
                                            }

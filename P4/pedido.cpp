#include "pedido.hpp"

#include <iomanip>

unsigned Pedido::n_total_pedidos_=0;

Pedido::Pedido(Usuario_Pedido& UsPe,Pedido_Articulo& PeAr,Usuario& us,const Tarjeta& tar,const Fecha& f):tarjeta_(&tar),fecha_(f){
   /** if(user.compra().empty())throw Pedido::Vacio(&user);
    if(tar.titular()!= &user)throw Pedido::Impostor(&user);
    if(tar.caducidad()<f)throw Tarjeta::Caducada(tar.caducidad());
    for(Usuario::Articulos::const_iterator iter = user.compra().begin();iter!= user.compra().end();iter++){
        if(ArticuloAlmacenable* AA= dynamic_cast<ArticuloAlmacenable*>(iter->first)){
            if(iter->second > AA->stock()){
                    for(Usuario::Articulos::const_iterator iter = user.compra.begin();iter!=user.compra().end();iter++){
                    user.compra(*iter->first,0);
                                                                                    }
                throw SinStock(iter->first);
               // const_cast<Usuario::Articulos&>(user.compra()).clear();//---------
               //throw Pedido::SinStock(iter->first);
                                                }
                                                                                        }
            else{
                if(LibroDigital* LD = dynamic_cast<LibroDigital*>(iter->first)){
                    if(LD->f_expir()<f) user.compra()(*iter->first,0);
                                                                                }
                }
                                                                                                            }
    if(user.compra().empty())throw Vacio(&user);
    UsPe.asocia(*this,user);
    total_=0;
    for(Usuario::Articulos::const_iterator iter=user.compra().begin();iter!=user.compra().end();iter++){
        total_+=iter->second*iter->first->precio();
        PeAr.pedir(*iter->first,*this,iter->first->precio(),iter->second);
        if(ArticuloAlmacenable* AA= dynamic_cast<ArticuloAlmacenable*>(iter->first))
        AA->stock()-=iter->second;
                                                                                                        }
    const_cast<Usuario::Articulos&>(user.compra()).clear();
    numero_= ++n_total_pedidos_;
*/

if(us.compra().empty())
throw Vacio(&us);
if(tar.titular() != &us)
throw Impostor(&us);
if(tar.caducidad() < f)
throw Tarjeta::Caducada(tar.caducidad());
auto carro = us.compra();
for(auto iter = carro.begin() ; iter != carro.end() ; iter ++) {
if(ArticuloAlmacenable* AA = dynamic_cast<ArticuloAlmacenable*>(iter->first)) {
if(iter->second > AA->stock()) {
for(auto iter = carro.begin() ; iter != carro.end() ; iter ++)
us.compra(*iter->first, 0);
throw SinStock(iter->first);
}
} else if(LibroDigital* LD = dynamic_cast<LibroDigital*>(iter->first)) {
if(LD->f_expir() < f)
us.compra(*iter->first, 0);
}
}
if(us.compra().empty())
throw Vacio(&us);
UsPe.asocia(*this, us);
carro = us.compra();
total_ = 0;
for(auto iter = carro.begin() ; iter != carro.end() ; iter ++) {
total_ += iter->first->precio() * iter->second;
PeAr.pedir(*iter->first, *this, iter->first->precio(), iter->second);
if(ArticuloAlmacenable* AA = dynamic_cast<ArticuloAlmacenable*>(iter->first))
AA->stock() -= iter->second;
}
const_cast<Usuario::Articulos&>(us.compra()).clear();
numero_ = ++ n_total_pedidos_;
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

Usuario& Pedido::Vacio::usuario() const{
    return *user_;
                                    }

Pedido::Impostor::Impostor(Usuario* user):user_(user){}

Usuario& Pedido::Impostor::usuario() const{
    return *user_;
                                        }

Pedido::SinStock::SinStock(Articulo*art):art_(art){}

Articulo& Pedido::SinStock::articulo() const{
    return *art_;
                                            }

#include "usuario_pedido.hpp"

void Usuario_Pedido::asocia(Usuario& user,Pedido& p){
    UP[&user].insert(&p);
    PU[&p]=&user;
                                                    }

void Usuario_Pedido::asocia(Pedido& p, Usuario& user){
    asocia(user,p);
                                                        }

Pedidos Usuario_Pedido::pedidos(Usuario& user){
    return UP.find(&user)->second;
                                                }

Usuario* Usuario_Pedido::cliente(Pedido& p){
    return PU.find(&p)->second;
                                            }

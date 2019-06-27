#ifndef USUARIO_PEDIDO_HPP_
#define USUARIO_PEDIDO_HPP_

#include "usuario.hpp"
#include "pedido.hpp"

#include<set>
#include<map>
class Usuario;
class Pedido;

class Usuario_Pedido{
public:
    typedef set<Pedido*> Pedidos;
    void asocia(Usuario& user, Pedido& p);
    void asocia(Pedido& p,Usuario& user);
    Pedidos pedidos(Usuario& user);
    Usuario* cliente(Pedido& p);
private:
    map<Usuario*,Pedidos> UP;//insert se usa para los set
    map<Pedido*,Usuario*> PU;

};

#endif // USUARIO_PEDIDO_HPP_

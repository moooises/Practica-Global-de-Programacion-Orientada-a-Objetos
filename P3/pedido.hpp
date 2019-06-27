#ifndef PEDIDO_HPP_
#define PEDIDO_HPP_

#include "tarjeta.hpp"
#include "fecha.hpp"
#include "pedido-articulo.hpp"
#include "usuario_pedido.hpp"

class Tarjeta;
class Usuario_Pedido;
class Pedido_Articulo;


class Pedido{
public:

    class Vacio{
    public:
        Vacio(Usuario* user);
        Usuario& User() const;
    private:
        Usuario* user_;
                };

    class Impostor{
    public:
        Impostor(Usuario* user);
        Usuario& User() const;
    private:
        Usuario* user_;
                    };

    class SinStock{
    public:
        SinStock(Articulo* art);
        Articulo& articulo() const;

    private:
        Articulo* art_;

                    };

    Pedido(Usuario_Pedido& UsPe,Pedido_Articulo& PeAr,Usuario& user,const Tarjeta& tar,const Fecha& f = Fecha());
    unsigned numero() const;
    const Tarjeta* tarjeta() const;
    Fecha fecha() const;
    double total() const;
    static unsigned n_total_pedidos(){return n_total_pedidos_;}
private:
    unsigned numero_;
    const Tarjeta* tarjeta_;
    Fecha fecha_;
    double total_;
    static unsigned n_total_pedidos_;

            };

ostream& operator <<(ostream& os, const Pedido& p);

#endif // PEDIDO_HPP_

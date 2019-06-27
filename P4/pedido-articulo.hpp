#ifndef PEDIDO_ARTICULO_HPP
#define PEDIDO_ARTICULO_HPP

#include "articulo.hpp"
#include "pedido.hpp"

class Articulo;
class Pedido;

class LineaPedido{
public:
    explicit LineaPedido(double precio, unsigned cant=1);
    double precio_venta() const;
    unsigned cantidad() const;
private:
    double precio_venta_;
    unsigned cantidad_;

                    };

ostream& operator <<(ostream& os, const LineaPedido& LP);

class OrdenaPedidos: public binary_function<Pedido*,Pedido*,bool>{
public:
    bool operator()(const Pedido* a, const Pedido* b) const;
                                                                };

class OrdenaArticulos: public binary_function<Articulo*,Articulo*,bool>{
public:
    bool operator()(const Articulo* a,const Articulo* b) const;
                                                                    };

class Pedido_Articulo{
public:
    typedef std::map<Articulo*, LineaPedido, OrdenaArticulos> ItemsPedido;
    typedef std::map<Pedido*, LineaPedido, OrdenaPedidos> Pedidos;
    //No hace falta constructores
    void pedir(Pedido& ped,Articulo& art,double precio,unsigned cant=1);
    void pedir(Articulo& art,Pedido& ped,double precio,unsigned cant=1);
    ItemsPedido& detalle (Pedido& ped);
    Pedidos ventas(Articulo& art);
    ostream& mostrarDetallePedidos(ostream& os) const ;
    ostream& mostrarVentasArticulos(ostream& os) const;

private:
    std::map<Pedido*, ItemsPedido, OrdenaPedidos> PaA;
    std::map<Articulo*, Pedidos, OrdenaArticulos> AaP;

                    };

ostream& operator <<(ostream& os, const Pedido_Articulo::ItemsPedido& IP);
ostream& operator <<(ostream& os, const Pedido_Articulo::Pedidos& pedidos);

#endif // PEDIDO-ARTICULO_HPP_


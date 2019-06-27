#include "pedido-articulo.hpp"

#include<iomanip>

LineaPedido::LineaPedido(double precio, unsigned cant):precio_venta_(precio),cantidad_(cant){}

double LineaPedido::precio_venta() const{
    return precio_venta_;
                                        }

unsigned LineaPedido::cantidad() const{
    return cantidad_;
                                        }

ostream& operator <<(ostream& os, const LineaPedido& LP){
    os<<fixed<<setprecision(2)<<LP.precio_venta()<<" €\t"<<LP.cantidad();
    return os;
                                                        }

bool OrdenaPedidos::operator ()(const Pedido* a, const Pedido* b) const{
    return a->numero()<b->numero();
                                                                        }

bool OrdenaArticulos::operator ()(const Articulo* a, const Articulo* b)const{
    return a->referencia()<b->referencia();
                                                                        }

void Pedido_Articulo::pedir(Pedido& ped,Articulo& art,double precio,unsigned cant){
    PaA[&ped].insert(make_pair(&art,LineaPedido(precio,cant)));
    AaP[&art].insert(make_pair(&ped,LineaPedido(precio,cant)));
                                                                                    }

void Pedido_Articulo::pedir(Articulo& art,Pedido& ped,double precio,unsigned cant){
    pedir(art,ped,precio,cant);
                                                                                    }

Pedido_Articulo::ItemsPedido& Pedido_Articulo::detalle(Pedido& ped){
    return PaA.find(&ped)->second;
                                                                    }

Pedido_Articulo::Pedidos Pedido_Articulo::ventas(Articulo& art){
    if(AaP.find(&art)==AaP.end()){
        Pedido_Articulo::Pedidos Vacio;
        return Vacio;
                                    }
    else
    return AaP.find(&art)->second;
                                                                    }

ostream& Pedido_Articulo::mostrarDetallePedidos(ostream& os)const{
    double precio=0;
    map<Pedido*,Pedido_Articulo::ItemsPedido,OrdenaPedidos>::const_iterator iter;
    for(iter=PaA.begin();iter!=PaA.end();++iter){
        os<<"Pedido núm. "<<iter->first->numero();
        os<<"\tCliente: "<<iter->first->tarjeta()->titular()->nombre()<<" "<<"\n";
        os<<"Fecha: "<<iter->first->fecha()<<iter->second;
        precio+=iter->first->total();
                                                }
    os<<fixed;
    os<<"TOTAL VENTAS: "<<setprecision(2)<<precio<<" €"<<endl;
    return os;
                                                                    }

ostream& Pedido_Articulo::mostrarVentasArticulos(ostream& os) const{
    map<Articulo*,Pedido_Articulo::Pedidos,OrdenaArticulos>::const_iterator iter;
    for(iter=AaP.begin();iter!=AaP.end();++iter){
        os<<"Ventas de ["<<iter->first->referencia()<<"] ";
        os<<"\""<<iter->first->titulo()<<"\" \n"<<iter->second<<endl;
    }
    return os;
                                                                    }

ostream& operator <<(ostream& os, const Pedido_Articulo::ItemsPedido& IP){
    double total=0;
    Pedido_Articulo::ItemsPedido::const_iterator iter;
    os<<"  PVP    Cantidad        Artículo \n";
    os<<"=================================================================="<<endl;
    for(iter=IP.begin();iter!=IP.end();++iter){
        os<<" "<<iter->first->precio()<<" €\t";
        os<<iter->second.cantidad()<<"\t";
        os<<"["<<iter->first->referencia()<<"] ";
        os<<"\""<<iter->first->titulo()<<"\" "<<endl;
        total+=(iter->second.precio_venta()*iter->second.cantidad());
                                                }
    os<<"=================================================================="<<endl;
    os<<fixed;
    os<<setprecision(2)<<total<<" €"<<endl;
    return os;
                                                                            }

ostream& operator <<(ostream& os, const Pedido_Articulo::Pedidos& pedidos){
    double precio=0;
    unsigned total=0;
    Pedido_Articulo::Pedidos::const_iterator iter;
    os<<"[Pedidos: "<<iter->first->n_total_pedidos()<<"]"<<endl;
    os<<"=================================================================="<<endl;
    os<<"  PVP    Cantidad        Fecha de venta \n";
    os<<"=================================================================="<<endl;
    for(iter=pedidos.begin();iter!=pedidos.end();++iter){
        os<<" "<<iter->second.precio_venta()<<" €\t";
        os<<iter->second.cantidad()<<"\t";
        os<<iter->first->fecha()<<endl;
        total+=iter->second.cantidad();
        precio+=(iter->second.precio_venta()*iter->second.cantidad());
                                                        }
    os<<"=================================================================="<<endl;
    os<<fixed;
    os<<setprecision(2)<<precio<<" €\t"<<total<<endl;
    return os;
                                                                            }

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//* 41.544.259-CESPEDES,TomasNicolas-(01-2964) *//**/
/**//**   DEBE MODIFICAR LA LÍNEA DE COMENTARIO ANTERIOR CON SUS DATOS   **//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//**   DESARROOLLE LAS "FUNCIONES MIEMBRO" DE LA CLASE    **//**//**//**/

#include "Prisma.h"

Prisma::Prisma() ///Caso por defecto, si no se ingresan parámetros.
{
    alto = 1;
    ancho = 1;
    profundidad = 1;
    color = "Incoloro";
}

Prisma::Prisma(string auxColor, int auxAlto, int auxAncho) ///Si no se ingresa el 3er parámetro de dimensión (profundidad), tomarlo "1" por defecto.
{
    color = auxColor;
    alto = auxAlto;
    profundidad = 1;
    ancho = auxAncho;
}

Prisma::Prisma(string auxColor, int auxAlto, int auxAncho, int auxProfundidad)
{
    color = auxColor;
    alto = auxAlto;
    ancho = auxAncho;
    profundidad = auxProfundidad;
}

Prisma::Prisma(const Prisma &obj)
{
    alto = obj.alto;
    ancho = obj.ancho;
    profundidad = obj.profundidad;
    color = obj.color;
}

ostream & operator <<(ostream &salida, const Prisma &obj)
{
    salida << obj.alto << "x" << obj.ancho << "x" << obj.profundidad << "-" << obj.color;
    return salida;
}

Prisma& Prisma::operator = (const Prisma &obj)
{
    alto = obj.alto;
    ancho = obj.ancho;
    profundidad = obj.profundidad;
    color = obj.color;
    return *this;
}

Prisma Prisma::operator ++ (int)
{
    Prisma aux(*this);
    this->alto++;
    this->ancho++;
    this->profundidad++;
    return aux;
}

Prisma operator * (const int &num, const Prisma &obj)
{
    Prisma aux(obj.color, obj.alto * num, obj.ancho * num, obj.profundidad * num);
    return aux;
}

Prisma& Prisma::operator -- ()
{
    this->alto --;
    this->ancho --;
    this->profundidad --;
    return *this;
}



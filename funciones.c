/**//*41.544.259-CESPEDES,TomasNicolas-(01-2964) *//**/


/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//* CUALQUIER INCLUDE DE BIBLIOTECA QUE NECESITE, HÁGALO ACÁ   *//**//**/
#include <stdlib.h>
#include <stddef.h>

/**//**//* CUALQUIER INCLUDE DE BIBLIOTECA QUE NECESITE, HÁGALO ACÁ   *//**//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
#include "funciones.h"
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//**//* ACÁ DEBE DESARROLLAR LAS FUNCIONES Y PRIMITIVAS PEDIDAS    *//**//**/
/**//**//* ADEMÁS DE CUALQUIER OTRA FUNCIÓN QUE SE REQUIERA           *//**//**/
#define FALSO 0
#define VERDADERO 1

tNodo* buscarMenor(tNodo* desde, int (*comparar)(const void*, const void*));
int string_matching(const char* cad, const char* sub);

///Funciones propias string.h
int strcmp(const char *cadena1, const char *cadena2);
size_t strlen(const char *cadena);
char* strcpy(char *cadena1, const char *cadena2);

tNodo* buscarMenor(tNodo* desde, int (*comparar)(const void*, const void*))
{
    tNodo* pMenor = desde;
    tNodo* p = desde->sig;

    while(p)
    {
        if(comparar(p->info, pMenor->info) < 0)
            pMenor = p;

        p = p->sig; ///LO AVANZO AL SIGUIENTE.
    }

    return pMenor;
}

int strcmp(const char *cadena1, const char *cadena2)
{
     while(*cadena1 && (*cadena1 == *cadena2))
     {
        cadena1++;
        cadena2++;
     }

    return *(char*)cadena1 - *(char*)cadena2;
}

size_t strlen(const char *cadena)
{
    const char *p = cadena;

    while (*cadena)
        ++cadena;

    return cadena - p;
}

int contador_de_ocurrencia(const char *cad, const char *sub) //CUENTA LAS APARICIONES DE LA SUBCADENA
{
    int contMatch = 0, ret;

    while(*cad)
    {
        if((*cad) != (*sub))
            cad++;
        else
        {
            ret = string_matching(cad, sub);
            if(ret)
                cad += strlen(sub);
            else
                cad ++;

            contMatch += ret;
        }
    }

    contMatch += string_matching(cad, sub);

    return contMatch;
}

int string_matching(const char* cad, const char* sub)
{   //SI COINCIDEN LOS ELEMENTOS, AVANZA CADENA Y SUB CADENA
    //SI NO COINCIDEN, AVANZA LA CADENA

    while( ((*cad) == (*sub)) && *cad)
    {
        cad ++;
        sub ++;
    }

    return *sub == '\0';
}

char* strcpy(char *cadena1, const char *cadena2)
{
    char* ret = cadena1;

    while (*cadena2)
        *cadena1 ++ = *cadena2 ++;

    *cadena1 = *cadena2;

    return (char*)ret;
}


/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//* FUNCIONES Y PRIMITIVAS A DESARROLLAR                               *//**/
/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/
/**//* para la información                                                *//**/

void mostrarMovim_MIO(const void *d, FILE *fp)
{
    const tMovi* movim = d;
    fprintf(fp, "%s%10.2f\n", movim->ctaCte, movim->saldo);
}


int compararMovim_MIO(const void *d1, const void *d2)
{
    return strcmp(d1, d2); ///Comparo las dos cadenas para ver si son iguales.
}


int esCtaCte002_MIO(const void *d)
{
    const tMovi* mov = d;
    const char* cad = mov->ctaCte;

    cad += (strlen(cad) - 3); ///Hallo la cantidad de caracteres hasta el campo de Tipo de Cuenta.
    int dev = string_matching(cad, "002"); ///Busco coincidencias de 002 en la cadena.

    return dev; ///dev es devolución.
}



int acumularMoviSaldo_MIO(void **dest, unsigned *tamDest,
                      const void *ori, unsigned tamOri)
{
    tMovi* desMov = *dest;
    const tMovi* oriMov = ori;

    desMov->saldo += oriMov->saldo;

    return 1;
}


void mostrarTotal_MIO(const void *d, FILE *fp)
{
    const tMovi* mov = d;

    fprintf(fp, " Total cliente:%10.2f\n\n", mov->saldo);

}


/**//* para el TDA LISTA                                                  *//**/

int mostrarLista_MIO(const tLista *p,
                     void (*mostrar)(const void *, FILE *), FILE *fp)
{
    fprintf(fp,"Nro Cuenta Banc   Importe\n");
    int cont = 0; ///Contador de elementos de la lista.
    while(*p)
    {
        mostrar((*p)->info, fp);
        p = &(*p)->sig;
        cont ++;
    }

    return cont;
}

void ordenarLista_MIO(tLista *p, int (*comparar)(const void *, const void *))
{
    tLista *listaOrd = p; ///Guardo la primera posicion de la lista.
    if(!*p)
        return;

    while( (*p)->sig )
    {

        tNodo * pMenor = buscarMenor(*p, comparar); ///Devuelve "p" en la primer posicion.

        if(*p != pMenor) ///Si son iguales, significa que no hay mas menores que "pMenor". Si se da esta condición, todo lo detras a "pMenor" está ordenado. Debo avanzar "p".
        {
            tLista *aux = p; ///Creo un puntero auxiliar para desvincular el nodo.
            while( (*aux)->sig != pMenor )///Avanza hasta el nodo anterior al elemento menor.
                aux = &(*aux)->sig;

            (*aux)->sig = pMenor->sig;///Se realiza el puenteo del nodo. Desvinculando el nodo con el elemento menor.

            pMenor->sig = *p;
            if(listaOrd == p)
            {
                *listaOrd = pMenor;
            }
            else
            {
                (*listaOrd)->sig = pMenor;
                listaOrd = &(*listaOrd)->sig;
            }
        }
        else
        {
            listaOrd = &(*listaOrd)->sig;
            p = &(*p)->sig;
        }
    }
}


int eliminarMostrarYMostrarSubTot_MIO(tLista *p, FILE *fpPant,
                                      int comparar(const void *, const void *),
                                      int comparar2(const void *d),
                                      int acumular(void **, unsigned *,
                                                   const void *, unsigned),
                                      void mostrar(const void *, FILE *),
                                      void mostrar2(const void *, FILE *))
{

    int cantElim = 0; ///Contador de nodos de Ctas. Corrientes eliminados.

    while(*p)
    {
        tMovi total;
        tMovi* pTotal = &total;

        if(comparar2( (*p)->info )) ///Para que no repita la linea de los nombres de las columnas, cada vez que quiera mostrar en el While.
        {
            fprintf(fpPant,"Nro Cuenta Banc   Importe\n");
            total.saldo = 0;

            strcpy(total.ctaCte, (*p)->info);

            do ///Utilizo un Do While porque si ingresa al If, se sabe que lo que ingresa es un tipo de cuenta corriente.
                {
                    acumular((void*)&pTotal, (unsigned*)sizeof(tMovi), (*p)->info, sizeof(tMovi)); ///REVISAAAAAR
                    mostrar((*p)->info, fpPant);

                    tNodo* eliminar = *p;
                    *p = eliminar->sig; ///Apunto al siguiente nodo.
                    free(eliminar->info); ///Libero el nodo.
                    free(eliminar);

                    cantElim ++;
                }
            while(*p && comparar2( (*p)->info ) && (comparar( (*p)->info, pTotal->ctaCte)) == 0); ///Valida si la cuenta sea 002 y no haya cambio de cuenta (001, 003, etc). Y si no hay fin de cadena.

            mostrar2(&total, fpPant);
        }
        else
            p = &(*p)->sig;
    }

    return cantElim;
}


int  vaciarListaYMostrar_MIO(tLista *p,
                             void (*mostrar)(const void *, FILE *), FILE *fp)
{
    int cant = 0;
    while(*p)
    {
        tNodo* aux = *p;

        cant ++;
        *p = aux->sig;
        if(mostrar && fp)
            mostrar(aux->info, fp);

        free(aux->info);
    }

    return cant;

}

/**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**//**/


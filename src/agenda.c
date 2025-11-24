#include "agenda.h"
//nuevo:
#include <stdio.h> //se agrego la biblioteca de entrada y salida estandar
#include <string.h>
#include <stdlib.h>
/**
 * Esta función se encarga de iniciar el número de contactos a cero
 */
void iniciar_agenda(Agenda *agenda){
    //nuevo:
    agenda->num_contactos = 0;
}



// Varible que lleva la cuenta de cuantos contactos hay en la agenda
//int num_contactos;   se elimina porque ya esta en agenda.h

/**
 * Esta función sirve para agregar un contacto nuevo en la agenda
 */
void agregar_contacto(Agenda *agenda, Contacto c){
    //nuevo:
     if (agenda->num_contactos < MAX_CONTACTOS) {
        agenda->contactos[agenda->num_contactos] = c;
        agenda->num_contactos++;
    }
}


/**
 * Esta función sirve para buscar un contacto por nombre en la agenda y retorna la posición del contacto si exisite
 * En caso contrario retorna -1
 */
int buscar_contacto(Agenda *agenda, char *nombre){
    //nuevo
    for (int i = 0; i < agenda->num_contactos; i++) {
        if (strcmp(agenda->contactos[i].nombre, nombre) == 0) {
            return i;
        }
    }
    return -1;
}


/**
 * Esta función  sirve para buscar un contacto por su número de telefono en la agenda
 */
int buscar_contacto_x_telefono(Agenda *agenda, char telefono[]){
    for (int i = 0; i < agenda->num_contactos; i++) {
        if (strcmp(agenda->contactos[i].telefono, telefono) == 0) {
            return i;
        }
    }
    return -1;
}


/**
 * Esta función sirve para ordenar los contactos por nombres de forma ascendente
 */
void ordenar_contactos(Agenda *a){
    int i, j;
    Contacto temp;
    for(i = 0; i < a->num_contactos; i++){
        for(j=0; j < a->num_contactos-i-1; j++){
            if(strcmp(a->contactos[j].nombre, a->contactos[j+1].nombre)>0){
                temp = a->contactos[j];
                a->contactos[j] = a->contactos[j+1];
                a->contactos[j+1] = temp;
            }
        }
    }
}

/**
 * Esta función sirve para ordenar los contactos por nombres de forma descendente
 */
void ordenar_contactos_inv(Agenda *a){
    int i, j;
    Contacto temp;
    for(i = 0; i < a->num_contactos; i++){
        for(j=0; j < a->num_contactos-i-1; j++){
            //Completar basandose en la función anterior:
             if(strcmp(a->contactos[j].nombre, a->contactos[j+1].nombre) < 0){
                temp = a->contactos[j];
                a->contactos[j] = a->contactos[j+1];
                a->contactos[j+1] = temp;
            }
        }
    }
}


/**
 * Función auxiliar para imprimir un contacto
 */
void mostrar_contacto(Contacto c){
    //nuevo   
    const char *meses[] = {"ENERO", "FEBRERO", "MARZO", "ABRIL", "MAYO", "JUNIO", 
                          "JULIO", "AGOSTO", "SEPTIEMBRE", "OCTUBRE", "NOVIEMBRE", "DICIEMBRE"};
    const char *tipos[] = {"CASA", "MOVIL", "OFICINA", "OTRO"};
    
    printf("Nombre: %s\n", c.nombre);
    printf("Apellido: %s\n", c.apellido);
    printf("Fecha Nacimiento: %d de %s\n", c.dia_nacimiento, meses[c.mes_nacimiento]);
    printf("Telefono: %s (%s)\n", c.telefono, tipos[c.tipo_telefono]);
    printf("----------------------------\n");
}


/**
 * Función auxiliar para leer un contacto
 */
void leer_contacto(Contacto *c){
    //nuevo 
    printf("Ingrese nombre: ");
    scanf("%s", c->nombre);
    printf("Ingrese apellido: ");
    scanf("%s", c->apellido);
    printf("Ingrese dia de nacimiento: ");
    scanf("%d", &c->dia_nacimiento);
    printf("Ingrese mes de nacimiento (1-12): ");
    scanf("%d", &c->mes_nacimiento);
    c->mes_nacimiento--;  //  pasa de 1-12 a 0-11 internamente
    printf("Ingrese telefono: ");
    scanf("%s", c->telefono);
    printf("Ingrese tipo de telefono (0-CASA, 1-MOVIL, 2-OFICINA, 3-OTRO): ");
    scanf("%d", (int*)&c->tipo_telefono);
}

/**
 * Función que imprime todos los contactos de la agenda en pantalla
 */
void imprimir_agenda(Agenda agenda){
    //nuevo
    printf("\n=== AGENDA DE CONTACTOS ===\n");
    for (int i = 0; i < agenda.num_contactos; i++) {
        printf("Contacto #%d:\n", i + 1);
        mostrar_contacto(agenda.contactos[i]);
    }
}

/**
 * Función que sirve para cargar contactos escritos en un archivo a la agenda
 */
void cargar_contactos(char *filename, Agenda *agenda){
    //nuevo  
    FILE *archivo = fopen(filename, "r");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo %s para lectura\n", filename);
        return;
    }
    Contacto c;
    int mes_temporal;
    while (fscanf(archivo, "%s %s %d %d %s %d", 
                  c.nombre, c.apellido, &c.dia_nacimiento, &c.mes_nacimiento, 
                  c.telefono, (int*)&c.tipo_telefono) == 6) {
        c.mes_nacimiento = mes_temporal - 1;  // ← Convertir 1-12 a 0-11
        if (agenda->num_contactos < MAX_CONTACTOS) {
            agenda->contactos[agenda->num_contactos] = c;
            agenda->num_contactos++;
        }
    }
    
    fclose(archivo);
    printf("Contactos cargados desde %s\n", filename);
}


/**
 * Función que sirve para guardar todos los contactos de la agenda en un archivo
 */
void guardar_contactos(char *filename, Agenda *agenda){
    //nuevo
    FILE *archivo = fopen(filename, "w");
    if (archivo == NULL) {
        printf("Error: No se pudo abrir el archivo %s para escritura\n", filename);
        return;
    }
    
    for (int i = 0; i < agenda->num_contactos; i++) {
        fprintf(archivo, "%s %s %d %d %s %d\n", 
                agenda->contactos[i].nombre,
                agenda->contactos[i].apellido,
                agenda->contactos[i].dia_nacimiento,
                agenda->contactos[i].mes_nacimiento+1,  //+1 para q sea de 1-12
                agenda->contactos[i].telefono,
                agenda->contactos[i].tipo_telefono);
    }
    
    fclose(archivo);
    printf("Contactos guardados en %s\n", filename);
}
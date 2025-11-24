#include <stdio.h>
#include <stdlib.h>
#include "agenda.h"

void mostrar_menu();

int main() {
    Agenda agenda;
    iniciar_agenda(&agenda);
    int opcion;
    char nombre[30];
    char telefono[15];
    char filename[50];
    Contacto nuevo_contacto;
    int posicion;

    do {
        mostrar_menu();
        printf("Seleccione una opcion: ");
        scanf("%d", &opcion);

        switch(opcion) {
            case 1: //lee el nombre del contaco agregado por el usuario y lo agrega a la agenda
                printf("\n=== AGREGAR CONTACTO ===\n");
                leer_contacto(&nuevo_contacto);
                agregar_contacto(&agenda, nuevo_contacto);
                printf("Contacto agregado exitosamente!\n");
                break;

            case 2: //solicita un nombre al usuario, busca el contacto en la agenda y muestra sus datos si existe
                printf("\n=== BUSCAR CONTACTO POR NOMBRE ===\n");
                printf("Ingrese el nombre a buscar: ");
                scanf("%s", nombre);
                posicion = buscar_contacto(&agenda, nombre);
                if (posicion != -1) {
                    printf("Contacto encontrado:\n");
                    mostrar_contacto(agenda.contactos[posicion]);
                } else {
                    printf("Contacto no encontrado.\n");
                }
                break;

            case 3: //busca un contacto por su telefono y si existe, muestra su informacion
                printf("\n=== BUSCAR CONTACTO X TELEFONO ===\n");
                printf("Ingrese el telefono a buscar: ");
                scanf("%s", telefono);
                posicion = buscar_contacto_x_telefono(&agenda, telefono);
                if (posicion != -1) {
                    printf("Contacto encontrado:\n");
                    mostrar_contacto(agenda.contactos[posicion]);
                } else {
                    printf("Contacto no encontrado.\n");
                }
                break;

            case 4: //imprime todos los contactos guardados en la agenda 
                printf("\n=== MOSTRAR TODOS LOS CONTACTOS ===\n");
                imprimir_agenda(agenda);
                break;

            case 5: // se ordenan los contactos en orden alfabetico de la A a la Z
                printf("\n=== ORDENAR CONTACTOS (ASCENDENTE) ===\n");
                ordenar_contactos(&agenda);
                printf("Contactos ordenados alfabeticamente (A-Z)\n");
                break;

            case 6: //ordena los contactos de la Z a la A
                printf("\n=== ORDENAR CONTACTOS (DESCENDENTE) ===\n");
                ordenar_contactos_inv(&agenda);
                printf("Contactos ordenados alfabeticamente (Z-A)\n");
                break;

            case 7: //el usuario escribe el nombre del archivo donde se guardaran los contactos
                printf("\n=== GUARDAR CONTACTOS ===\n");
                printf("Ingrese el nombre del archivo: ");
                scanf("%s", filename);
                guardar_contactos(filename, &agenda);
                break;

            case 8: //carga en la agenda todos los contactos guardados en un archivo 
                printf("\n=== CARGAR CONTACTOS ===\n");
                printf("Ingrese el nombre del archivo: ");
                scanf("%s", filename);
                cargar_contactos(filename, &agenda);
                break;

            case 0:
                printf("Cierre\n");
                break;
                return -1;

            default:
                printf("Opcion no valida. Intentar nuevamente.\n");
        }

        printf("\nPresiona Enter para continuar...");
        getchar(); // Esperar Enter

    } while (opcion != 0);

    return 0;
}

void mostrar_menu() {
    printf("\n=== AGENDA DE CONTACTOS ===\n");
    printf("1. Agregar contacto\n");
    printf("2. Buscar contacto por nombre\n");
    printf("3. Buscar contacto por telefono\n");
    printf("4. Mostrar todos los contactos\n");
    printf("5. Ordenar contactos (A-Z)\n");
    printf("6. Ordenar contactos (Z-A)\n");
    printf("7. Guardar contactos en archivo\n");
    printf("8. Cargar contactos desde archivo\n");
    printf("0. Salir\n");
}
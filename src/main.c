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
            case 1:
                printf("\n=== AGREGAR CONTACTO ===\n");
                leer_contacto(&nuevo_contacto);
                agregar_contacto(&agenda, nuevo_contacto);
                printf("Contacto agregado exitosamente!\n");
                break;

            case 2:
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

            case 3:
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

            case 4:
                printf("\n=== MOSTRAR TODOS LOS CONTACTOS ===\n");
                imprimir_agenda(agenda);
                break;

            case 5:
                printf("\n=== ORDENAR CONTACTOS (ASCENDENTE) ===\n");
                ordenar_contactos(&agenda);
                printf("Contactos ordenados alfabeticamente (A-Z)\n");
                break;

            case 6:
                printf("\n=== ORDENAR CONTACTOS (DESCENDENTE) ===\n");
                ordenar_contactos_inv(&agenda);
                printf("Contactos ordenados alfabeticamente (Z-A)\n");
                break;

            case 7:
                printf("\n=== GUARDAR CONTACTOS ===\n");
                printf("Ingrese el nombre del archivo: ");
                scanf("%s", filename);
                guardar_contactos(filename, &agenda);
                break;

            case 8:
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
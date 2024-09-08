/**
 * @file comunicacion.c
 * @brief Simulación de un sistema de comunicación en un entorno post-apocalíptico.
 * 
 * Este archivo contiene la implementación de un sistema de comunicación simple
 * que permite enviar, recibir, y registrar mensajes en un archivo de texto.
 * El sistema es precario y solo soporta mensajes de texto, ademas que solo registra un mensaje.
 * La idea es poder perfeccionarlo en futuras versiones.
 * 
 * @author [Joaquin Barrios - 41401732]
 * @date [25/08/2024]
 */

#include <stdio.h>
#include <string.h>



// Defino el tipo de mensaje
typedef enum {
    MSG_TYPE_TEXT,
    MSG_TYPE_COMMAND,
    MSG_TYPE_STATUS
} MessageType;

// Defino la estructura de mi mensaje
typedef struct {
    MessageType type;
    char content[256];
} Message;

// Función para inicializar el mensaje
void initMessage(Message *msg, MessageType type, const char *content) {
    msg->type = type;
    strncpy(msg->content, content, sizeof(msg->content) - 1);
    msg->content[sizeof(msg->content) - 1] = '\0';
}

// Función para manejar un mensaje de texto
void handleTextMessage(Message *msg) {
    printf("Mensaje de Texto: %s\n", msg->content);
}

// Función para despachar el mensaje (decidir qué hacer según el tipo)
void dispatchMessage(Message *msg) {
    if (msg->type == MSG_TYPE_TEXT) {
        handleTextMessage(msg);
    } else {
        printf("Tipo de mensaje no soportado.\n");
    }
}

// Función para registrar el mensaje en un archivo
void logMessage(const Message *msg, const char *filename) {
    FILE *file = fopen(filename, "a");
    if (file) {
        fprintf(file, "Tipo: %d, Contenido: %s\n", msg->type, msg->content);
        fclose(file);
    } else {
        printf("Error al abrir el archivo para registrar el mensaje.\n");
    }
}

int main() {
    Message msg;

    // Inicializo el mensaje con un texto
    initMessage(&msg, MSG_TYPE_TEXT, "Hola, sobreviviente dime de forma breve donde estas y que necesitas");

    // Envio el mensaje
    dispatchMessage(&msg);

    // Registro el mensaje en un archivo
    logMessage(&msg, "registro_mensajes.txt");

    // Ahora solicito una respuesta al receptor
    printf("Respuesta: ");
    char response[256];
    fgets(response, sizeof(response), stdin);

    // Quito el salto de línea que fgets añade al final de la entrada
    response[strcspn(response, "\n")] = '\0';

    // Inicializo un nuevo mensaje con la respuesta
    initMessage(&msg, MSG_TYPE_TEXT, response);

    // Registr0 la respuesta en el archivo
    logMessage(&msg, "registro_mensajes.txt");

    // Doy un aviso al receptor de que la ayuda está en camino
    initMessage(&msg, MSG_TYPE_TEXT, "Mensaje enviado, espera la ayuda ;)");

    // Despachamos el mensaje
    dispatchMessage(&msg);
    return 0;
}
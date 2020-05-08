#include <windows.h>
#include <stdio.h>
#include <stdlib.h>

#pragma warning(disable : 4996)

#define SUBMIT 4

const int WINDOWPOS_X = 100;
const int WINDOWPOS_Y = 100;
const int WINDOW_HEIGHT = 500;
const int WINDOW_WIDTH = 500;

HWND TextBox;
HWND Button;
HWND Response;

LPSTR name[100];
LPSTR response[100];

LRESULT CALLBACK WindowProcedure(HWND, UINT, WPARAM, LPARAM);

void AddControls(HWND);

/*
    1. Instance es llamado "handle to an instance" o "handle to a module."
       El sistema operativo utiliza este valor para identificar el ejecutable (EXE) cuando
       éste es cargado a la memoria. 
    2. hPrevInstance no tiene significado. Fue utilizado en el Windows de 16 bits pero ahora
       siempre es cero.
    3. atgs los argumentos de la linea de comandos como un string Unicode.
    4. nCmdShow es una bandera que especifica cada vez que la ventana principal será
       minimizada, maximizada, o mostrada normalmente.
*/
int main(HINSTANCE hInst, HINSTANCE hPrevInst, LPSTR atgs, int ncmdshow)
{
    ShowWindow(GetConsoleWindow(), SW_HIDE); // Para deshacernos de la consola.
    /*
        1. hWnd: Handle to a Window. Pointer a una ventana dueña.
        2. lp Text: El mensaje desplegado en la ventana.
        3. lpCaption: El encabezado de la ventanilla.
        4. uType: Indica los botones que va a contener.

         MB_OK: Boton de OK
         MB_ABORTRETRYIGNORE
         MB_HELP
         MB_YESNO
    */
    // MessageBoxA(NULL, "Hello World!", "First GUI", MB_YESNO); 


    WNDCLASSA wc = { 0 }; // Estructura de la ventana.

    wc.hbrBackground = (HBRUSH)COLOR_WINDOW; // Define el color default de la ventana.
    wc.hCursor = LoadCursor(NULL, IDC_ARROW); // Para que cargue el cursor. Define el tipo de cursor.
    wc.hInstance = hInst; // Para que el sistema operativo identifique la ventana.
    wc.lpszClassName = "myWindowClass"; // Nombre de la clase.
    wc.lpfnWndProc = WindowProcedure; // Un apuntador al procedimiento de la ventana.

    if (!RegisterClassA(&wc)) // Si hay un error regresa -1.
        return -1;

    /*
        Funcion para crear la ventana.

        1. El nombre de la clase de la ventana.
        2. El encabezado de la ventana.
        3. El estilo de la ventana.
        4. Posicion x de la ventana.
        5. Posicion y de la ventana.
        6. Anchura de la ventana.
        7. Altura de la ventana.
        8. Identificador de la ventana padre.
        9. Identificador de un menu.
        10. Un handle a la instancia del modulo que sera asociado con la ventana.
        11. Un apuntador a un valor que sera enviado a la ventana.
    */
    CreateWindowA("myWindowClass", "My Window", WS_OVERLAPPEDWINDOW | WS_VISIBLE,
        WINDOWPOS_X, WINDOWPOS_Y, WINDOW_WIDTH, WINDOW_HEIGHT, NULL, NULL, NULL, NULL);

    // Hacer un loop para que no se cierre la ventana inmediatamente.

    MSG msg = { 0 };

    while (GetMessage(&msg, NULL, NULL, NULL))
    {
        TranslateMessage(&msg);
        DispatchMessage(&msg);
    }

    return 0;
}


/*
    Función callback que procesa mensajes enviados a una ventana.

    1. hWnd: Un handle a la ventana.
    2. msg: El mensaje.
    3. wp: Informacion adicional (Los controles que insertamos).
    4. lp: Informacion adicional del mensaje.
*/
LRESULT CALLBACK WindowProcedure(HWND hWnd, UINT msg, WPARAM wp, LPARAM lp)
{

    switch (msg)
    {
    case WM_COMMAND: // Para comandos para los handlers.
        switch (wp)
        {
        case SUBMIT: // Comandos para el boton de enviar.

            GetWindowTextA(TextBox, name, 100); // Guarda el input y lo mete a la variable "name".

            // Concatena "Hola " al nombre y lo guarda en la variable "response".
            strcpy(response, "Hola ");
            strcat(response, name);

            SetWindowTextA(Response, response); // Despliega el contenido del string "response".
            break;
        }
        break;
    case WM_CREATE: // Definir acciones cuando se crea la ventana.
        AddControls(hWnd);
        break;
    case WM_DESTROY: // Definir acciones cuando cerramos la aplicacion.
        PostQuitMessage(0);
        break;
    default:
        DefWindowProcA(hWnd, msg, wp, lp);  // Se encarga de los mensajes que no estamos procesando arriba.
    }
}

// Añade los controles de nuestra aplicación.
void AddControls(HWND hWnd)
{
    // Crear el texto "Cual es tu nombre?"
    CreateWindowA("static", "Cual es tu nombre?", WS_VISIBLE | WS_CHILD | SS_CENTER,
        150, 100, 200, 50, hWnd, NULL, NULL, NULL);

    // Crear el edit box
    TextBox = CreateWindowA("Edit", "", WS_VISIBLE | WS_CHILD | WS_BORDER | ES_AUTOHSCROLL,
        175, 130, 100, 20, hWnd, NULL, NULL, NULL);

    // Crear el boton
    Button = CreateWindowA("Button", "Enviar", WS_VISIBLE | WS_CHILD,
        275, 130, 50, 20, hWnd, (HMENU)SUBMIT, NULL, NULL);

    // Crear el texto respuesta
    Response = CreateWindowA("static", "", WS_VISIBLE | WS_CHILD | SS_CENTER,
        150, 160, 200, 20, hWnd, NULL, NULL, NULL);
}
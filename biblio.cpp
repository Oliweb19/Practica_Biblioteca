#include "biblioteca.h"

int main(){
    book *libro = nullptr;
    int op = 1;
    ReadBook(&libro, "C:/Users/User/Desktop/Oliver/Program/c++/Est. Datos/Listas_simple_enlazada/Practica/libros.txt");

    while(op != 0){
        system("cls");
        menu();
        cout << "Ingrese una opcion: ";
        cin >> op;

        switch (op){
            case 1:
                RequestBookData(&libro);
                system("Pause");
                break;
            case 2:
                SearchBook(libro);
                system("Pause");
                break;
            case 3:
                PrintBooks(libro);
                system("Pause");
                break;
            case 4:
                ModifyBook(&libro);
                system("Pause");
                break;
            case 5:
                DeleteBook(&libro);
                system("Pause");
                break;
            case 0:
                cout << "Saliendo del programa..." << endl;
                SaveBook(libro, "C:/Users/User/Desktop/Oliver/Program/c++/Est. Datos/Listas_simple_enlazada/Practica/libros.txt");
                break;
            default:
                cout << "Opcion invalida. Intente de nuevo." << endl;
                system("Pause");
                break;
        }
    }

    return 0;
}
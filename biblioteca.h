#include <iostream>
#include <string>
#include <fstream>

using namespace std;

struct book{
    string title;
    string author;
    int ISBN;

    book *next;
};

void menu(){
    cout<<"---> Bienvenido a la Biblioteca <---"<<endl;
    cout<<"1. Agregar Libro"<<endl;
    cout<<"2. Buscar Libro"<<endl;
    cout<<"3. Mostrar Libro"<<endl;
    cout<<"4. Modificar Libro"<<endl;
    cout<<"5. Eliminar Libro"<<endl;
    cout<<"0. Salir"<<endl;
    cout<<"------------------------------------"<<endl;
}

book *NewNodo(string titulo, string autor, int id){
    book *libro = new book;

    libro->title = titulo;
    libro->author = autor;
    libro->ISBN = id;
    libro->next = nullptr;

    return libro;
}

bool Vacio(book *p){
    return p == nullptr;
}

void AddBook(book **libro, string titulo, string autor, int id){
    book *nuevo = NewNodo(titulo, autor, id);

    if(Vacio(*libro)){
        *libro = nuevo;
    }
    else{
        book *aux = *libro;

        while(aux->next != nullptr){
            aux = aux->next;
        }

        aux->next = nuevo;
    }
}

void RequestBookData(book **libro) {
    string titulo, autor;
    int id;
    
    cin.ignore();
    cout << "Ingrese el titulo del libro: ";
    getline(cin, titulo);
    cout << "Ingrese el autor del libro: ";
    getline(cin, autor);
    cout << "Ingrese el ISBN del libro: ";
    cin >> id;

    AddBook(libro, titulo, autor, id);
}

void PrintBooks(book *libro) {
    if (Vacio(libro)) {
        cout << "La lista de libros está vacía." << endl;
        return;
    }

    book *aux = libro;
    while (aux != nullptr) {
        cout << "Titulo: " << aux->title << endl;
        cout << "Autor: " << aux->author << endl;
        cout << "ISBN: " << aux->ISBN << endl;
        cout << "-------------------------" << endl;
        aux = aux->next;
    }
}

void SearchBook(book *libro){
    book *aux;
    int id;

    cout << "Ingrese el ISBN del libro: ";
    cin >> id;

    aux = libro;
    while (aux != nullptr) {
        if (aux->ISBN == id) {
            cout << "Libro encontrado:" << endl;
            cout << "Titulo: " << aux->title << endl;
            cout << "Autor: " << aux->author << endl;
            cout << "ISBN: " << aux->ISBN << endl;
            return;
        }
        aux = aux->next;
    }
    cout << "Libro no encontrado :(" << endl;
}

void ModifyBook(book **libro){
    book *aux;
    int id;

    cout << "Ingrese el ISBN del libro a modificar: ";
    cin >> id;

    aux = *libro;
    while (aux != nullptr) {
        if (aux->ISBN == id) {
            cout << "Ingrese el nuevo titulo: ";
            cin.ignore();
            getline(cin, aux->title);
            cout << "Ingrese el nuevo autor: ";
            getline(cin, aux->author);
            cout << "Ingrese el nuevo ISBN: "<<aux->ISBN<<endl;
            cout << "Libro modificado con exito..." << endl;
            return;
        }
        aux = aux->next;
    }
    cout << "Libro no encontrado :(" << endl;
}

void DeleteBook(book **libro){
    book *temp = *libro, *prev = nullptr;
    int id;

    cout << "Ingrese el ISBN del libro a eliminar: ";
    cin >> id;

    while (temp != nullptr) {
        if (temp->ISBN == id) {
            if (prev == nullptr) {
                *libro = temp->next;
            } else {
                prev->next = temp->next;
            }
            delete temp;
            cout << "Se elimino con exito..." << endl;
            return;
        }
        prev = temp;
        temp = temp->next;
    }
    cout << "Libro no encontrado :(" << endl;
}

void SaveBook(book *libro, const string &filename) {
    ofstream archivo(filename); // Abre el archivo para escritura

    if (archivo.is_open()) {
        book *current = libro;
        while (current != nullptr) {
            archivo <<current->title<<"|";
            archivo <<current->author<<"|";
            archivo <<current->ISBN<<"|"<<endl;
            
            current = current->next;
        }
        archivo.close();
        cout << "La información de los libros se ha guardado en '" << filename << "'." << endl;
    } else {
        cerr << "No se pudo abrir el archivo '" << filename << "' para escritura." << endl;
    }
}

void ReadBook(book **libro, const string &filename) {
    ifstream archivo(filename); // Abre el archivo para lectura

    if (archivo.is_open()) {
        string line;
        while (getline(archivo, line)) {
            size_t pos1 = line.find('|');
            size_t pos2 = line.find('|', pos1 + 1);
            string title = line.substr(0, pos1);
            string author = line.substr(pos1 + 1, pos2 - pos1 - 1);
            int ISBN = stoi(line.substr(pos2 + 1));

            AddBook(libro, title, author, ISBN);
        }
        archivo.close();
    } else {
        cout << "No se pudo abrir el archivo '" << filename << "' para lectura." << endl;
    }
}
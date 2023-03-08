#include <iostream>
#include <stack>
#include <string>

using namespace std;

const int MAX = 100; // Tamaño máximo de la lista

template<class T>
class ListaEstatica {
public:
    ListaEstatica() {
        tam = 0;
    }

    int Inserta(T dato, int pos) {
        if (Llena() || pos < 1 || pos > tam + 1) {
            return 0; // Error
        }
        for (int i = tam; i >= pos; i--) {
            datos[i] = datos[i-1];
        }
        datos[pos-1] = dato;
        tam++;
        return 1; // Éxito
    }

    int Agrega(T dato) {
        if (Llena()) {
            return 0; // Error
        }
        datos[tam] = dato;
        tam++;
        return 1; // Éxito
    }

    int Busca(T dato) {
        for (int i = 0; i < tam; i++) {
            if (datos[i] == dato) {
                return i+1; // Posición del dato (comenzando en 1)
            }
        }
        return 0; // No encontrado
    }

    int Elimina(int pos) {
        if (pos < 1 || pos > tam) {
            return 0; // Error
        }
        for (int i = pos-1; i < tam-1; i++) {
            datos[i] = datos[i+1];
        }
        tam--;
        return 1; // Éxito
    }

    int Vacia() {
        return tam == 0;
    }

    int Llena() {
        return tam == MAX;
    }

    int Muestra() {
        if (Vacia()) {
            return 0; // Error
        }
        for (int i = 0; i < tam; i++) {
            cout << datos[i] << " ";
        }
        cout << endl;
        return 1; // Éxito
    }

private:
    T datos[MAX];
    int tam;
};

bool isOperator(char c) {
    return c == '+' || c == '-' || c == '*' || c == '/';
}

int precedence(char op) {
    if (op == '+' || op == '-')
        return 1;
    if (op == '*' || op == '/')
        return 2;
    return 0;
}

string infixToPostfix(string expression) {
    stack<char> s;
    string postfix = "";
    for (int i = 0; i < expression.length(); i++) {
        char c = expression[i];
        if (isalnum(c)) {
            postfix += c;
        } else if (c == '(') {
            s.push(c);
        } else if (c == ')') {
            while (!s.empty() && s.top() != '(') {
                postfix += s.top();
                s.pop();
            }
            if (!s.empty() && s.top() == '(') {
                s.pop();
            }
        } else if (isOperator(c)) {
            while (!s.empty() && precedence(s.top()) >= precedence(c)) {
                postfix += s.top();
                s.pop();
            }
            s.push(c);
        }
    }
    while (!s.empty()) {
        postfix += s.top();
        s.pop();
    }
    return postfix;
}

int main() {
    ListaEstatica<char> lista;
    int opcion = 0;
char dato;
int pos;

do {
    cout << "MENU" << endl;
    cout << "1. Agrega" << endl;
    cout << "2. Buscar" << endl;
    cout << "3. Elimina" << endl;
    cout << "4. Inserta" << endl;
    cout << "5. Muestra" << endl;
    cout << "6. Salir" << endl;
    cout << "Selecciona una opcion: ";
    cin >> opcion;

    switch (opcion) {
        case 1:
            cout << "Ingrese un dato: ";
            cin >> dato;
            if (lista.Agrega(dato)) {
                cout << "Dato agregado exitosamente." << endl;
            } else {
                cout << "Error al agregar el dato." << endl;
            }
            break;
        case 2:
            cout << "Ingrese un dato a buscar: ";
            cin >> dato;
            pos = lista.Busca(dato);
            if (pos) {
                cout << "El dato " << dato << " se encuentra en la posicion " << pos << endl;
            } else {
                cout << "El dato " << dato << " no se encuentra en la lista." << endl;
            }
            break;
        case 3:
            cout << "Ingrese la posicion del dato a eliminar: ";
            cin >> pos;
            if (lista.Elimina(pos)) {
                cout << "Dato eliminado exitosamente." << endl;
            } else {
                cout << "Error al eliminar el dato." << endl;
            }
            break;
        case 4:
            cout << "Ingrese un dato: ";
            cin >> dato;
            cout << "Ingrese la posicion donde desea insertar el dato: ";
            cin >> pos;
            if (lista.Inserta(dato, pos)) {
                cout << "Dato insertado exitosamente." << endl;
            } else {
                cout << "Error al insertar el dato." << endl;
            }
            break;
        case 5:
            if (lista.Muestra()) {
                cout << "Datos de la lista:" << endl;
            } else {
                cout << "La lista esta vacia." << endl;
            }
            break;
        case 6:
            cout << "Saliendo del programa..." << endl;
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente." << endl;
            break;
    }

} while (opcion != 6);

return 0;
}























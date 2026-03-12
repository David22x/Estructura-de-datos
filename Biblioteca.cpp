#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

// ============================================================
//  CLASE LIBRO
// ============================================================

class Libro {
private:
    string titulo;
    string autor;
    string id;
    bool disponible;

public:
    Libro(string titulo, string autor, string id) {
        this->titulo = titulo;
        this->autor = autor;
        this->id = id;
        this->disponible = true;
    }

    string getId() {
        return id;
    }

    string getTitulo() {
        return titulo;
    }

    string getAutor() {
        return autor;
    }

    bool estaDisponible() {
        return disponible;
    }

    void setDisponible(bool d) {
        this->disponible = d;
    }

    string toString() {
        string estado = disponible ? "Disponible" : "Prestado";
        return "\nLibro   : " + titulo +
               "\nAutor   : " + autor +
               "\nID      : " + id +
               "\nEstado  : " + estado;
    }
};

// ============================================================
//  CLASE USUARIO
// ============================================================

// Forward declaration: Prestamo aun no esta definido pero
// Usuario necesita usar punteros a el
class Prestamo;

class Usuario {
private:
    string nombre;
    string cedula;
    vector<Prestamo*> prestamos;

public:
    Usuario(string nombre, string cedula) {
        this->nombre = nombre;
        this->cedula = cedula;
    }

    string getNombre() {
        return nombre;
    }

    string getCedula() {
        return cedula;
    }

    vector<Prestamo*> getPrestamos() {
        return prestamos;
    }

    void agregarPrestamo(Prestamo* p) {
        prestamos.push_back(p);
    }

    string toString() {
        return "\nUsuario : " + nombre +
               "\nCedula  : " + cedula;
    }
};

// ============================================================
//  CLASE PRESTAMO
// ============================================================

class Prestamo {
private:
    Usuario* usuario;
    Libro* libro;
    string fechaPrestamo;
    string fechaEntrega;

public:
    Prestamo(Usuario* usuario, Libro* libro, string fp, string fe) {
        this->usuario = usuario;
        this->libro = libro;
        this->fechaPrestamo = fp;
        this->fechaEntrega = fe;
    }

    Usuario* getUsuario() {
        return usuario;
    }

    Libro* getLibro() {
        return libro;
    }

    string getFechaPrestamo() {
        return fechaPrestamo;
    }

    string getFechaEntrega() {
        return fechaEntrega;
    }

    string toString() {
        return "\n-------------------------------" +
               usuario->toString() +
               libro->toString() +
               "\nF. Prestamo : " + fechaPrestamo +
               "\nF. Entrega  : " + fechaEntrega +
               "\n-------------------------------";
    }
};

// ============================================================
//  CLASE BIBLIOTECA
// ============================================================

class Biblioteca {
private:
    vector<Libro*> libros;
    vector<Usuario*> usuarios;
    vector<Prestamo*> prestamos;

public:
    void agregarLibro(Libro* l) {
        libros.push_back(l);
        cout << "Libro agregado correctamente." << endl;
    }

    void registrarUsuario(Usuario* u) {
        usuarios.push_back(u);
        cout << "Usuario registrado correctamente." << endl;
    }

    Libro* buscarLibro(string id) {
        for (int i = 0; i < libros.size(); i++) {
            if (libros[i]->getId() == id) {
                return libros[i];
            }
        }
        return NULL;
    }

    Usuario* buscarUsuario(string cedula) {
        for (int i = 0; i < usuarios.size(); i++) {
            if (usuarios[i]->getCedula() == cedula) {
                return usuarios[i];
            }
        }
        return NULL;
    }

    void listarLibros() {
        if (libros.empty()) {
            cout << "\nNo hay libros registrados." << endl;
            return;
        }
        cout << "\n===== LIBROS =====" << endl;
        for (int i = 0; i < libros.size(); i++) {
            cout << libros[i]->toString() << endl;
        }
    }

    void listarUsuarios() {
        if (usuarios.empty()) {
            cout << "\nNo hay usuarios registrados." << endl;
            return;
        }
        cout << "\n===== USUARIOS =====" << endl;
        for (int i = 0; i < usuarios.size(); i++) {
            cout << usuarios[i]->toString() << endl;
        }
    }

    void listarPrestamos() {
        if (prestamos.empty()) {
            cout << "\nNo hay prestamos registrados." << endl;
            return;
        }
        cout << "\n===== PRESTAMOS =====" << endl;
        for (int i = 0; i < prestamos.size(); i++) {
            cout << prestamos[i]->toString() << endl;
        }
    }

    void crearPrestamo(string cedula, string idLibro, string fp, string fe) {
        Usuario* u = buscarUsuario(cedula);
        Libro* l = buscarLibro(idLibro);

        if (u == NULL) {
            cout << "Error: Usuario no encontrado." << endl;
            return;
        }
        if (l == NULL) {
            cout << "Error: Libro no encontrado." << endl;
            return;
        }
        if (!l->estaDisponible()) {
            cout << "Error: El libro no esta disponible." << endl;
            return;
        }

        Prestamo* p = new Prestamo(u, l, fp, fe);
        prestamos.push_back(p);
        u->agregarPrestamo(p);
        l->setDisponible(false);

        cout << "Prestamo creado correctamente." << endl;
    }

    void eliminarPrestamo(string cedula, string idLibro) {
        for (int i = 0; i < prestamos.size(); i++) {
            if (prestamos[i]->getUsuario()->getCedula() == cedula &&
                prestamos[i]->getLibro()->getId() == idLibro) {

                prestamos[i]->getLibro()->setDisponible(true);
                delete prestamos[i];
                prestamos.erase(prestamos.begin() + i);
                cout << "Prestamo eliminado. Libro disponible nuevamente." << endl;
                return;
            }
        }
        cout << "No se encontro el prestamo." << endl;
    }
};

// ============================================================
//  CLASE CONSOLEMANAGER
// ============================================================

class ConsoleManager {
private:
    Biblioteca biblioteca;

public:
    void mostrarMenu() {
        int opcion;
        do {
            cout << "\n===== BIBLIOTECA =====" << endl;
            cout << "1. Agregar libro"         << endl;
            cout << "2. Registrar usuario"     << endl;
            cout << "3. Crear prestamo"        << endl;
            cout << "4. Eliminar prestamo"     << endl;
            cout << "5. Listar libros"         << endl;
            cout << "6. Listar usuarios"       << endl;
            cout << "7. Listar prestamos"      << endl;
            cout << "0. Salir"                 << endl;
            cout << "Opcion: ";
            cin >> opcion;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (opcion) {
                case 1: agregarLibro();               break;
                case 2: registrarUsuario();           break;
                case 3: crearPrestamo();              break;
                case 4: eliminarPrestamo();           break;
                case 5: biblioteca.listarLibros();    break;
                case 6: biblioteca.listarUsuarios();  break;
                case 7: biblioteca.listarPrestamos(); break;
                case 0: cout << "Hasta luego." << endl; break;
                default: cout << "Opcion invalida." << endl;
            }
        } while (opcion != 0);
    }

    void agregarLibro() {
        string titulo, autor, id;
        cout << "Titulo : "; getline(cin, titulo);
        cout << "Autor  : "; getline(cin, autor);
        cout << "ID     : "; getline(cin, id);

        Libro* l = new Libro(titulo, autor, id);
        biblioteca.agregarLibro(l);
    }

    void registrarUsuario() {
        string nombre, cedula;
        cout << "Nombre : "; getline(cin, nombre);
        cout << "Cedula : "; getline(cin, cedula);

        Usuario* u = new Usuario(nombre, cedula);
        biblioteca.registrarUsuario(u);
    }

    void crearPrestamo() {
        string cedula, idLibro, fp, fe;
        cout << "Cedula usuario  : "; getline(cin, cedula);
        cout << "ID libro        : "; getline(cin, idLibro);
        cout << "Fecha prestamo  : "; getline(cin, fp);
        cout << "Fecha entrega   : "; getline(cin, fe);

        biblioteca.crearPrestamo(cedula, idLibro, fp, fe);
    }

    void eliminarPrestamo() {
        string cedula, idLibro;
        cout << "Cedula usuario : "; getline(cin, cedula);
        cout << "ID libro       : "; getline(cin, idLibro);

        biblioteca.eliminarPrestamo(cedula, idLibro);
    }
};

// ============================================================
//  MAIN
// ============================================================

int main() {
    ConsoleManager cm;
    cm.mostrarMenu();
    return 0;
}

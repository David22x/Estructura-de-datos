#include <iostream>
#include <string>
#include <vector>
#include <limits>
using namespace std;

//Se crea la clase Libro 
class Libro {
	//Variables de la clase Libro
private:
    string titulo;
    string autor;
    string id;
    bool disponible;

public:
	//Constructor parametrizado de Libro
    Libro(string titulo, string autor, string id) {
        this->titulo     = titulo;
        this->autor      = autor;
        this->id         = id;
        this->disponible = true;
    }

	//Getters y setters de la clase
    string getId()          { return id; }
    string getTitulo()      { return titulo; }
    string getAutor()       { return autor; }
    bool   estaDisponible() { return disponible; }
    void setDisponible(bool d) { this->disponible = d; }

	//Metodo toString() imprime datos del objeto (Polimorfismo)
    string toString() {
        string estado = disponible ? "Disponible" : "Prestado";
        return "\nLibro   : " + titulo +
               "\nAutor   : " + autor +
               "\nID      : " + id +
               "\nEstado  : " + estado;
    }
};

//Se coloca aqui la clase Prestamo porque se lo necesitara en clase Usuairo
class Prestamo; 

//Clase usuario
class Usuario {
	//Variables de la clase
	//Se utiliza un vector el cual gurdara los prestamso de cada usuario
private:
    string nombre;
    string cedula;
    vector<Prestamo*> prestamos;

public:
	//Construccion parametrizaso de la clase
    Usuario(string nombre, string cedula) {
        this->nombre = nombre;
        this->cedula = cedula;
    }

	//Getters y settes de la clase
    string getNombre() { return nombre; }
    string getCedula() { return cedula; }
    vector<Prestamo*> getPrestamos() { return prestamos; }
    void agregarPrestamo(Prestamo* p) { prestamos.push_back(p); }

	//Metodo toString() imprime datos del objeto (Polimorfismo)
    string toString() {
        return "\nUsuario : " + nombre +
               "\nCedula  : " + cedula;
    }
};

//Clase Prestamo
class Prestamo {
private:
	//Variables de Prestamo
    Usuario* usuario; //Instancia de Usuario
    Libro*   libro; //Instancia de Libro
    string   fechaPrestamo;
    string   fechaEntrega;

public:
	//Constructor parametrizado de Prestamo
    Prestamo(Usuario* usuario, Libro* libro, string fp, string fe) {
        this->usuario       = usuario;
        this->libro         = libro;
        this->fechaPrestamo = fp;
        this->fechaEntrega  = fe;
    }
	
	//Getter y setters
    Usuario* getUsuario()       { return usuario; }
    Libro*   getLibro()         { return libro; }
    string   getFechaPrestamo() { return fechaPrestamo; }
    string   getFechaEntrega()  { return fechaEntrega; }

    void setUsuario(Usuario* u)      { this->usuario = u; }
    void setLibro(Libro* l)          { this->libro = l; }
    void setFechaPrestamo(string fp) { this->fechaPrestamo = fp; }
    void setFechaEntrega(string fe)  { this->fechaEntrega = fe; }

	//Metodo toString() imprime datos del objeto (Polimorfismo)
    string toString() {
        return "\n-------------------------------" +
               usuario->toString() +
               libro->toString() +
               "\nF. Prestamo : " + fechaPrestamo +
               "\nF. Entrega  : " + fechaEntrega +
               "\n-------------------------------";
    }
};

//Clase biblioteca
class Biblioteca {
	//Se utiliza vectores para almacenar 
	//libros, usuarios y prestamos de la biblioteca
private:
    vector<Libro*>    libros;
    vector<Usuario*>  usuarios;
    vector<Prestamo*> prestamos;

public:	
	//Método de agredar libros a la biblioteca
    void agregarLibro(Libro* l) {
        libros.push_back(l);
        cout << "Libro agregado correctamente." << endl;
    }

	//Método de registrar usuarios a la biblioteca
    void registrarUsuario(Usuario* u) {
        usuarios.push_back(u);
        cout << "Usuario registrado correctamente." << endl;
    }
	
	//Método para buscar los libros de la biblioteca segun su id
    Libro* buscarLibro(string id) {
        for (int i = 0; i < libros.size(); i++)
            if (libros[i]->getId() == id) return libros[i];
        return NULL;
    }

	//Método para buscar usuarios de la biblioteca segun su cedula
    Usuario* buscarUsuario(string cedula) {
        for (int i = 0; i < usuarios.size(); i++)
            if (usuarios[i]->getCedula() == cedula) return usuarios[i];
        return NULL;
    }

	//Método para listar todos los libros de la biblioteca
    void listarLibros() {
        if (libros.empty()) { cout << "\nNo hay libros registrados." << endl; return; }
        cout << "\n===== LIBROS =====" << endl;
        for (int i = 0; i < libros.size(); i++) cout << libros[i]->toString() << endl;
    }

	//Método para listar los usuarios de la biblioteca
    void listarUsuarios() {
        if (usuarios.empty()) { cout << "\nNo hay usuarios registrados." << endl; return; }
        cout << "\n===== USUARIOS =====" << endl;
        for (int i = 0; i < usuarios.size(); i++) cout << usuarios[i]->toString() << endl;
    }
    
	//Método para listar los prestamos 
    void listarPrestamos() {
        if (prestamos.empty()) { cout << "\nNo hay prestamos registrados." << endl; return; }
        cout << "\n===== PRESTAMOS =====" << endl;
        for (int i = 0; i < prestamos.size(); i++) cout << prestamos[i]->toString() << endl;
    }

	//Método para crear un prestamo
    void crearPrestamo(string cedula, string idLibro, string fp, string fe) {
        Usuario* u = buscarUsuario(cedula);
        Libro*   l = buscarLibro(idLibro);

		//Verifica que los datos ingresados sean correctos
        if (u == NULL) { cout << "Error: Usuario no encontrado." << endl; return; }
        if (l == NULL) { cout << "Error: Libro no encontrado."   << endl; return; }
        if (!l->estaDisponible()) { cout << "Error: El libro no esta disponible." << endl; return; }

		//Crear el prestamo
        Prestamo* p = new Prestamo(u, l, fp, fe);
        prestamos.push_back(p);
        u->agregarPrestamo(p);
        l->setDisponible(false); 	//Se marca el libro como prestado
        cout << "Prestamo creado correctamente." << endl;
    }

	//Método para eliminar prestamo
    void eliminarPrestamo(string cedula, string idLibro) {
    	//Recorre todos los prestamos
        for (int i = 0; i < prestamos.size(); i++) {
        	//Elimina el prestamo segun la ceédula y el id del libro prestado
            if (prestamos[i]->getUsuario()->getCedula() == cedula &&
                prestamos[i]->getLibro()->getId() == idLibro) {
                prestamos[i]->getLibro()->setDisponible(true);
                delete prestamos[i];
                prestamos.erase(prestamos.begin() + i);
                cout << "Prestamo eliminado. Libro disponible nuevamente." << endl;
                return;
            }
        }
        cout << "Error: No se encontro el prestamo." << endl;
    }

	//Metodo de modificar el prestamo
    void modificarPrestamo(string cedula, string idLibro,
                           string nuevaCedula, string nuevoIdLibro,
                           string nuevaFp, string nuevaFe) {

        // Buscar el prestamo
        Prestamo* p = NULL;
        for (int i = 0; i < prestamos.size(); i++) {
            if (prestamos[i]->getUsuario()->getCedula() == cedula &&
                prestamos[i]->getLibro()->getId() == idLibro) {
                p = prestamos[i];
                break;
            }
        }

        if (p == NULL) { cout << "Error: No se encontro el prestamo." << endl; return; }

        // Cambiar usuario si se indico uno distinto
        if (nuevaCedula != cedula) {
            Usuario* nuevoUsuario = buscarUsuario(nuevaCedula);
            if (nuevoUsuario == NULL) { cout << "Error: El nuevo usuario no existe." << endl; return; }
            p->setUsuario(nuevoUsuario);
        }

        // Cambiar libro si se indico uno distinto
        if (nuevoIdLibro != idLibro) {
            Libro* nuevoLibro = buscarLibro(nuevoIdLibro);
            if (nuevoLibro == NULL) { cout << "Error: El nuevo libro no existe." << endl; return; }
            if (!nuevoLibro->estaDisponible()) { cout << "Error: El nuevo libro no esta disponible." << endl; return; }
            p->getLibro()->setDisponible(true);   // liberar libro anterior
            p->setLibro(nuevoLibro);
            nuevoLibro->setDisponible(false);     // marcar nuevo libro como prestado
        }

        // Cambiar fechas si se ingresaron
        if (nuevaFp != "") p->setFechaPrestamo(nuevaFp);
        if (nuevaFe != "") p->setFechaEntrega(nuevaFe);

        cout << "Prestamo modificado correctamente." << endl;
        cout << p->toString() << endl;
    }
};

//Clase ConsoleManager
//Esta clase es la que manejará todas las interfaces necesarias
//Ademas aqui es donde el codigo se utiliza segun lo que se desee
class ConsoleManager {
private:
	//Se crea una instancia de la clase Biblioteca
    Biblioteca biblioteca;

public:
	//Se ingresan los datos iniciales del programa
    ConsoleManager() {
        //Libros iniciales 
        biblioteca.agregarLibro(new Libro("Cien anios de soledad",    "Gabriel Garcia Marquez",   "L001"));
        biblioteca.agregarLibro(new Libro("Don Quijote de la Mancha", "Miguel de Cervantes",      "L002"));
        biblioteca.agregarLibro(new Libro("El principito",            "Antoine de Saint-Exupery", "L003"));
        biblioteca.agregarLibro(new Libro("1984",                     "George Orwell",            "L004"));
        biblioteca.agregarLibro(new Libro("Harry Potter",             "J.K. Rowling",             "L005"));
        biblioteca.agregarLibro(new Libro("El senor de los anillos",  "J.R.R. Tolkien",           "L006"));
        biblioteca.agregarLibro(new Libro("Crimen y castigo",         "Fiodor Dostoievski",       "L007"));
        biblioteca.agregarLibro(new Libro("La Odisea",                "Homero",                   "L008"));
        biblioteca.agregarLibro(new Libro("Fahrenheit 451",           "Ray Bradbury",             "L009"));
        biblioteca.agregarLibro(new Libro("El codigo Da Vinci",       "Dan Brown",                "L010"));
        //Usuarios iniciales
        biblioteca.registrarUsuario(new Usuario("Carlos Perez",   "1001"));
        biblioteca.registrarUsuario(new Usuario("Maria Lopez",    "1002"));
        biblioteca.registrarUsuario(new Usuario("Juan Gomez",     "1003"));
        biblioteca.registrarUsuario(new Usuario("Ana Martinez",   "1004"));
        biblioteca.registrarUsuario(new Usuario("Luis Torres",    "1005"));
        biblioteca.registrarUsuario(new Usuario("Sofia Ramirez",  "1006"));
        biblioteca.registrarUsuario(new Usuario("Pedro Castillo", "1007"));
        biblioteca.registrarUsuario(new Usuario("Laura Mendoza",  "1008"));
        biblioteca.registrarUsuario(new Usuario("Diego Herrera",  "1009"));
        biblioteca.registrarUsuario(new Usuario("Valentina Cruz", "1010"));
        //Prestamos iniciales
        biblioteca.crearPrestamo("1001", "L001", "2026-03-01", "2026-03-15");
        biblioteca.crearPrestamo("1005", "L004", "2026-03-10", "2026-03-24");
    }

	//Método mostrar menú
    void mostrarMenu() {
        int opcion;
        do {
            cout << "\n===== BIBLIOTECA =====" << endl;
            cout << "1. Agregar libro"         << endl;
            cout << "2. Registrar usuario"     << endl;
            cout << "3. Crear prestamo"        << endl;
            cout << "4. Modificar prestamo"    << endl;
            cout << "5. Eliminar prestamo"     << endl;
            cout << "6. Listar libros"         << endl;
            cout << "7. Listar usuarios"       << endl;
            cout << "8. Listar prestamos"      << endl;
            cout << "0. Salir"                 << endl;
            cout << "Opcion: ";
            cin >> opcion;
            cin.ignore(numeric_limits<streamsize>::max(), '\n');

            switch (opcion) {
                case 1: agregarLibro();               break;
                case 2: registrarUsuario();           break;
                case 3: crearPrestamo();              break;
                case 4: modificarPrestamo();          break;
                case 5: eliminarPrestamo();           break;
                case 6: biblioteca.listarLibros();    break;
                case 7: biblioteca.listarUsuarios();  break;
                case 8: biblioteca.listarPrestamos(); break;
                case 0: cout << "Hasta luego." << endl; break;
                default: cout << "Opcion invalida." << endl;
            }
        } while (opcion != 0);
    }

	//Métodp agregar libro
    void agregarLibro() {
        string titulo, autor, id;
        cout << "Titulo : "; getline(cin, titulo);
        cout << "Autor  : "; getline(cin, autor);
        cout << "ID     : "; getline(cin, id);
        biblioteca.agregarLibro(new Libro(titulo, autor, id));
    }
	
	//Método para registrar un usuario
    void registrarUsuario() {
        string nombre, cedula;
        cout << "Nombre : "; getline(cin, nombre);
        cout << "Cedula : "; getline(cin, cedula);
        biblioteca.registrarUsuario(new Usuario(nombre, cedula));
    }

	//Método para crear un prestamo
    void crearPrestamo() {
        string cedula, idLibro, fp, fe;
        cout << "Cedula usuario : "; getline(cin, cedula);
        cout << "ID libro       : "; getline(cin, idLibro);
        cout << "Fecha prestamo : "; getline(cin, fp);
        cout << "Fecha entrega  : "; getline(cin, fe);
        biblioteca.crearPrestamo(cedula, idLibro, fp, fe);
    }

	//Metodo para modificar un prestamo
    void modificarPrestamo() {
        string cedula, idLibro;
        string nuevaCedula, nuevoIdLibro, nuevaFp, nuevaFe;

		//Se ingresan los datos para modificar el prestamo
        cout << "\n-- Prestamo a modificar --" << endl;
        cout << "Cedula usuario actual : "; getline(cin, cedula);
        cout << "ID libro actual       : "; getline(cin, idLibro);

        cout << "\n-- Nuevos datos (Enter para no cambiar) --" << endl;
        cout << "Nueva cedula usuario  : "; getline(cin, nuevaCedula);
        if (nuevaCedula == "") nuevaCedula = cedula;

        cout << "Nuevo ID libro        : "; getline(cin, nuevoIdLibro);
        if (nuevoIdLibro == "") nuevoIdLibro = idLibro;

        cout << "Nueva fecha prestamo  : "; getline(cin, nuevaFp);
        cout << "Nueva fecha entrega   : "; getline(cin, nuevaFe);

        biblioteca.modificarPrestamo(cedula, idLibro, nuevaCedula, nuevoIdLibro, nuevaFp, nuevaFe);
    }

	//Método para eliminar un prestamo
    void eliminarPrestamo() {
        string cedula, idLibro;
        cout << "Cedula usuario : "; getline(cin, cedula);
        cout << "ID libro       : "; getline(cin, idLibro);
        biblioteca.eliminarPrestamo(cedula, idLibro);
    }
};

//Main
int main() {
    ConsoleManager cm;
    cm.mostrarMenu();
    return 0;
}

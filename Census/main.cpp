#include <cstddef>
#include <fstream>
#include <iostream>
#include <sstream>
#include <string>
#include <time.h>
using namespace std;
#include "persona.h"
#include "lista.h"
#include "hashtable.h"

// Aylín Millán Cázares A01655861
// Karina Ruiz Tron A01656073
// Funciona con pocos datos el numero 2 (debug.csv) por un error que aparecia de malloc(): unaligned tcache chunk detected. El numero 3 con datos completos tarda mucho,son debug se puede ver como si funciona. 

void AgergarLL(Hashtable<string, Persona> &censo,
               LinkedList<Persona> &personas) {
  LinkedList<string> CiudadesKeys = censo.keys();
  while (!CiudadesKeys.is_empty()) {
    string key = CiudadesKeys.remove_front();
    do {
      Persona persona = censo.get_or_default(key, Persona());
      if (persona) {
        personas.addLast(persona);
      }
    } while (censo.remove(key));
  }
}


void Censos(Hashtable<string, Persona> &censo) {
  LinkedList<Persona> personas;
  LinkedList<string> cities = censo.keys();
  AgergarLL(censo, personas);
  while (!cities.is_empty() && !personas.is_empty()) {
    string city = cities.remove_front();
    int n = 0;
    cout << "-\t" << city << ": ";
    while (personas.getFirst().GetCity() == city) {
      personas.remove_front();
      n++;
      if (personas.is_empty())
        break;
    }
    cout << n << "\n";
  }
}


void Ordenamiento(Stack<Persona> &l1) {
  Stack<Persona> l2;

  while (!l1.is_empty()) {
    Persona personaTemp = l1.pop();
    string nombreTemp = personaTemp.GetLastName();
    while (!l2.is_empty() && l2.peek().GetLastName() > nombreTemp) {
      l1.push(l2.pop());
    }
    l2.push(personaTemp);
  }
  while (!l2.is_empty()) {
    l1.push(l2.pop());
  }
}



int main(int argc, char**argv) {
  LinkedList<Persona> lista_p;
  Hashtable<string, Persona> censo(10000);

  ifstream bitacoraa;
  bitacoraa.open("bitacora.csv");
  string c;
  char delimiter = ',';
  getline(bitacoraa, c);
  while (getline(bitacoraa, c)) {
    string id, first_name, last_name, gender, dob, phone, email, ZIP, city,
        state;

    id = c.substr(0, c.find(delimiter));
    c = c.substr(c.find(delimiter) + 1, c.size());
    first_name = c.substr(0, c.find(delimiter));
    c = c.substr(c.find(delimiter) + 1, c.size());
    last_name = c.substr(0, c.find(delimiter));
    c = c.substr(c.find(delimiter) + 1, c.size());
    gender = c.substr(0, c.find(delimiter));
    c = c.substr(c.find(delimiter) + 1, c.size());
    dob = c.substr(0, c.find(delimiter));
    c = c.substr(c.find(delimiter) + 1, c.size());
    phone = c.substr(0, c.find(delimiter));
    c = c.substr(c.find(delimiter) + 1, c.size());
    email = c.substr(0, c.find(delimiter));
    c = c.substr(c.find(delimiter) + 1, c.size());
    ZIP = c.substr(0, c.find(delimiter));
    c = c.substr(c.find(delimiter) + 1, c.size());
    city = c.substr(0, c.find(delimiter));
    c = c.substr(c.find(delimiter) + 1, c.size());
    state = c.substr(0, c.find(delimiter));
    c = c.substr(c.find(delimiter) + 1, c.size());

    stringstream ss;
    int id_;
    int zip_;
    ss << id;
    ss >> id_;
    stringstream ds;
    ds << ZIP;
    ds >> zip_;

    Persona p(id_, first_name, last_name, gender, dob, phone, email, zip_, city, state);

    lista_p.addLast(p);
    censo.put(city, p);
  }
  bitacoraa.close();

  int op;
  cout << "                       Evidencia 3" << endl;
  cout << "==========================================================" << endl;
  cout << "Elija una opción: " << endl;
  cout << "1.Censo poblacional de cada ciudad \n2. Ordenar por last name \n3. Imprimir datos por la prioridad de ZIP (menor a mayor)" << endl;
  cout << endl;
  cout << "Introduzca el número de su elección: ";
  cin >> op;

  if(op == 1){
    Censos(censo);
    cout << "La complejidad es de: O(n^3)" << endl;
    
  }else if(op == 2){
    
    Stack<Persona> stack_p;
    while (!lista_p.is_empty()) {
      stack_p.push(lista_p.remove_last());
    }
    Ordenamiento(stack_p);
    
    while (!stack_p.is_empty()) {
      cout << stack_p.pop() << " ";
    }


    cout << "La complejidad es de: O(log n)" << endl;
    
  }else if(op == 3){
    //Dos queue (copia y final)
    Queue<Persona> rebote; //copia 
    Queue<Persona> listaFinal; //final

    //Copia de lista_p en "rebote"
    for(int i = 0; i < lista_p.size(); i++){
      rebote.enqueue(lista_p.get(i));
    }

    //peekMin en rebote y agregar a listaFinal, luego borrarlo de rebote
    while(rebote.size()!= 0){
      Persona zip = rebote.peekMin();
      listaFinal.enqueue(zip);
      rebote.dequeueMin();
    }
    
    //Output final
    cout << listaFinal << endl;
    
    cout << "La complejidad es de: O(n)" << endl;
    
  }else{
    cout << "Opcion Invalida :(" << endl;
  }
  


}

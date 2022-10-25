#pragma once
#ifndef PERSONA_H
#define PERSONA_H

#include <cstddef>
#include <iostream>
#include <time.h>
#include <string>
using namespace std;

class Persona{
  private:
    string first_name, last_name, gender, dob, phone, email,city, state;
    int zip, id;
  public:
      Persona(int id = 0, string fname = "", string lname = "", string gender = "", string dob = "", string phone = "", string email = "", int zip = 0, string city = "", string state = "")
      {
        this->id = id;
        this->zip = zip;
        this->first_name = fname;
        this->last_name = lname;
        this->city = city;
        this->gender = gender;
        this-> dob = dob;
        this->phone = phone;
        this->email = email;
        this->state = state;
      }

      bool operator>(Persona & p){
        return (this -> zip  > p.zip);
      }

      bool operator<(Persona & p){
        return (this -> zip  < p.zip);
        }

      operator bool() const{
        return id != 0 && first_name != "" &&  last_name != "";
      }

      string GetCity(){
        return city;
      }
      string GetLastName(){
        return last_name;
      }
      string GetFirstName(){
        return first_name;
      }
    
      
      friend ostream & operator <<(ostream &, const Persona &);

      bool operator>=(const Persona & p){
        return (this -> last_name  > p.last_name);
      }
       bool operator>(const Persona & p){
        return this->last_name.compare(p.last_name) > 0;
      }
      bool operator<=(const Persona & p){
        return (this -> last_name  < p.last_name);
      }



/*
Agrega las sobre cargas de operadores necesarias en la clase Persona.
*/
    
};
ostream & operator << (ostream & salida, const Persona & p){
  salida <<"  Name: " << p.first_name << " " << p.last_name<<"Gender:" << p.gender << "Day of Birth: " << p.dob<< "Phone: " <<p.phone << "Email: " << p.email <<"  City: " << p.city << "State: "<< p.state<<"  Zip: " << p.zip << "\n";
  return salida;
}


#endif
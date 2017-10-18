//****************************************************************************
//Student name: Long Le
//Student ID: 923532743
//
//
//
//****************************************************************************
#ifndef LINE_H
#define LINE_H 
#include "node.h"
#include <cstring>
//class type is the class has a list of locations and a list of street car
//it is an abstract base class contains pure virtual functions of adding
//and removing locations and street cars as well 
class type
{
    public:
        type(); //default constructor
        type(const type& t); //copy constructor
        type(bool isLoop);
        ~type(); //destructor
        void print_line() const; //print the line 
        void add_location(location*& l); //add the new location into route
        void input_file(char* dir); //input from file

    protected:
        location* head;
        bool loop;
        void change_loop(bool isLoop);
        void add_node(location*& head, location*& cur, location*& src, bool isLoop); 
        void copy_list(location*& dest, location* src, bool isLoop); 
};

//class line inherits from class type. It represents loop lines which
//contain a list of location and also a list of street cars
class line : public type
{
    public:
        line(); //default constructor
        line(const line& l); //copy constructor
        line(char* id, int n); //constructor
        line(street_car* ls, int n); //constructor with street_car
        ~line(); //destructor
        void display_line() const; //display information of the line 
        void assign(const street_car& sc); //assign a street car to the line 
        void unassign(const street_car& sc); //unassign a street car
        void change_name(char* name); //change the name of the line
        line& operator=(const line& l); //assignment operator
        bool operator==(const line& l); //== operator
        void start(); //start the line
        void stop(); //stop the line

    protected:
        char* id; //id of the line
        street_car* list; //a dynamic array of street cars running on the line
        int nums; //number of street cars in the line  
}; 

//class map contains a list of lines. It can delete a line or force a line
//temporaly stops running
class map
{
    public:
        map(); //default constructor
        map(const map& m); //copy constructor
        ~map(); //destructor
        void display() const; //display all the lines
        void add_line(const line& l); //add a new line to map
        void remove_line(const line& l); //remove a line from map
        void pause(const line& l); //pause a line
        void start(const line& l); //start a line
        bool search(const line& l) const; //search a line

    protected:
        line* list; //a dynamic array of line
        int nums; //number of lines
};
#endif


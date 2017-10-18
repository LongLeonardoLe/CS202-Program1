//****************************************************************************
//Student name: Long Le
//Student ID: 923532743
//
//In this file, there are 4 classes: node, location, street_car, and graph
//which are related closely to each other
//****************************************************************************
#ifndef NODE_H
#define NODE_H 
#include <iostream>
#include <string.h>
#include <fstream>

//node is the basic unit for a location and later a street car in the map
//it's also the unit for the graph
//it contains the specific name of the location
class node
{
    public:
       node(); //default constructor
       node(const node& n); //copy constructor
       node(char* name); //constructor with name 
       ~node(); //destructor
       void display() const; //display function for node
       void change_name(char* name); //function to change the name of the node
       node& operator=(const node& n); //assignment operator

    protected:
        char* name; //name of the location on the map 
};

//the class location inherites from the class node
//a location is a specific stop in a route of street cars
//it has 2 pointers point to the next and the previous stops in the route 
class location : public node
{
    public:
        location(); //default constructor
        location(const location& l); //copy constructor
        location(const node& l); //constructor with node 
        ~location(); //destructor
        location*& go_next(); //go to the next location
        location*& go_prev(); //go to the previous location
        void connect_next(location& l); //connect a location to the next
        void connect_prev(location& l); //connect a location to the previous
        
    protected:
        location* next; //point to the next location on the route 
        location* prev; //point to the previous location on the route  
};

//class street_car inherites from the class node represent a street car and 
//contains necessary functions for a street car
class street_car : public node
{
    public:
        street_car(); //default constructor
        street_car(const street_car& sc); //copy constructor
        street_car(const node& l, char* id, bool stt, int pace); //constructor with location
        street_car(char* name, char* id, bool stt, int pace); //constructor with all values 
        ~street_car(); //destructor
        void change_pace(int p); //change the pace 
        void display() const; //display the current location
        void start(); //to start the street car
        void stop(); //to stop the street car
        street_car& operator=(const street_car& src); //assignment operator
        bool operator==(const street_car& src); //== operator 

    protected:
        char* id; 
        bool status; //current status of the street car, 1 = in service, 0 = out
        int pace; //closest allowed distance to the next street car on the route
};

//class graph represents directed graph of nodes
//it has an adjacency list storing nodes and its connection
class graph
{
    public:
       graph(); //default constructor
       graph(const graph& g); //copy constructor
       ~graph(); //destructor
       void add_node(node& n); //add a new node to graph
       void generate(); //generate a graph from a .txt file 
       void display() const; //display

    protected:
        int size; //total nodes in the graph
        node** node_list; //list of the nodes 
        int* connect_list; //list of connection corresponding to each node
};

#endif


#include "node.h"

//------------------------------ node class --------------------------
//default constructor of node
node::node()
{
    this->name = NULL;
}

//copy constructor of node class 
node::node(const node& n)
{
    this->name = new char[strlen(n.name) + 1];
    strcpy(this->name, n.name);
}

//constructor with name
node::node(char* name)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);
}

//destructor of node class 
node::~node()
{
    delete this->name;
}

//change name of the node
void node::change_name(char* name)
{
    this->name = new char[strlen(name) + 1];
    strcpy(this->name, name);  
}

//display function of node class
void node::display() const 
{
    std::cout << this->name;  
}

//assignment operator: node class
node& node::operator=(const node& n)
{
    if (this != &n)
    {
        delete[] this->name;
        this->name = new char[strlen(n.name) + 1];
        strcpy(this->name, n.name);
    }
    return *this; 
}

//-------------------------- location class ----------------------------
//default constructor of location class
location::location()
{
    this->next = NULL;
    this->prev = NULL;
}

//copy constructor of location class
location::location(const location& l)
    : node(l) 
{
    this->next = NULL;
    this->prev = NULL;
}

//constructor with node
location::location(const node& l)
    : node(l)
{
    this->next = NULL;
    this->prev = NULL;
}

//destructor of location class
location::~location()
{
    delete[] this->next;
    delete[] this->prev;
    this->next = NULL;
    this->prev = NULL;
}

//go to the next location: location class
location*& location::go_next() 
{
    return this->next; 
}

//go to the prev location: location class
location*& location::go_prev()
{
    return this->prev;
}

//connect to the next location: location class
void location::connect_next(location& l)
{
    if (this->next != NULL)
        this->next = NULL;
    this->next = new location;
    this->next = &l;
}

//connect to the prev location: location class
void location::connect_prev(location& l)
{
    if (this->prev != NULL)
        this->prev = NULL;
    this->prev = new location;
    this->prev = &l;
}

//----------------------------- street_car class ---------------------
//default constructor: street_car class
street_car::street_car()
{
    this->id = NULL;
    this->status = false;
    this->pace = 0; 
}

//copy constructor
street_car::street_car(const street_car& sc)
    : node(sc)
{
    this->id = new char[strlen(sc.id) + 1];
    strcpy(this->id, sc.id); 
    this->status = sc.status;
    this->pace = sc.pace; 
}

//constructor with location
street_car::street_car(const node& l, char* id, bool stt, int pace)
    : node(l)
{
    this->id = new char[strlen(id) + 1];
    strcpy(this->id, id); 
    this->status = stt;
    this->pace = pace; 
}

//constructor with all values
street_car::street_car(char* name, char* id, bool stt, int pace)
    : node(name)
{
    this->id = new char[strlen(id) + 1];
    strcpy(this->id, id); 
    this->status = stt;
    this->pace = pace;
}

//destructor: street_car class
street_car::~street_car()
{
    delete this->id;
    this->status = false;
    this->pace = 0;
}

//change the pace of the street car
void street_car::change_pace(int p)
{
    this->pace = p;
}

//display the current location: street_car class
void street_car::display() const
{
    std::cout << "Street car " << this->id << ", current location: ";
    node::display();
    std::cout << std::endl; 
}

//to start the street car
void street_car::start()
{
    if (this->status)
    {
        std::cout << "The street car " << this->id << " is running." << std::endl;
        return;
    }

    this->status = true;
    std::cout << "Pace for " << this->id << ": ";
    std::cin >> this->pace;
}

void street_car::stop()
{
    if (!this->status)
    {
        std::cout << "The street car " << this->id << " is not running." << std::endl;
        return;
    }

    this->status = false;
    this->pace = 0;  
    std::cout << "The street car " << this->id << " has stopped." << std::endl;
}

//assignment operator
street_car& street_car::operator=(const street_car& src)
{
    if (this != &src)
    {
        this->name = new char[strlen(src.name) + 1];
        strcpy(this->name, src.name);
        this->id = new char[strlen(src.id) + 1];
        strcpy(this->id, src.id);
        this->status = src.status;
        this->pace = src.pace; 
    }
    return *this; 
}

//== operator
bool street_car::operator==(const street_car& src)
{
    if (strcmp(this->id, src.id) == 0 && strcmp(this->name, src.name) == 0)
        return true;
    return false; 
}

//--------------------------------- graph class ----------------------------
//default constructor: graph class
graph::graph()
{
    this->size = 0;
    this->node_list = NULL;
    this->connect_list = NULL;
}

//copy constructor: graph class
graph::graph(const graph& g)
{
    this->size = g.size;

    this->connect_list = new int[this->size];
    for (int i = 0; i < this->size; ++i)
        this->connect_list[i] = g.connect_list[i];

    this->node_list = new node*[this->size];
    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->connect_list[i]; ++j)
            this->node_list[i][j] = g.node_list[i][j];
    }
}

//destructor: graph class
graph::~graph()
{
    for (int i = 0; i < this->size; ++i)
    {
        delete[] this->node_list[i];
        this->node_list[i] = NULL;
    }
    delete[] this->node_list;
    delete[] this->connect_list;
    this->connect_list = NULL;
    this->node_list = NULL;
    this->size = 0;
}

//add a new node to graph: graph class
void graph::add_node(node& n)
{
    this->size += 1;

}

//generate graph from text file: graph class
void graph::generate()
{
    std::ifstream fin;
    
    //open the file and input the data of nodes 
    fin.open("listOfNode.txt");
    if (fin.is_open())
    {
        fin >> this->size;
        this->connect_list = new int[this->size];
        this->node_list = new node*[this->size];
        fin.ignore(1000, '\n'); 
        for (int i = 0; i < this->size; ++i)
        {
            char* tmp = new char[256];
            fin.getline(tmp, 256, '\n');
            int connect;
            fin >> connect;
            this->connect_list[i] = connect;
            fin.ignore(1000, '\n');
            this->node_list[i] = new node[connect+1];
            this->node_list[i][0].change_name(tmp);
        }
    }
    fin.close();

    fin.open("connection.txt");
    if (fin.is_open())
    {
        for (int i = 0; i < this->size; ++i)
        {
            for (int j = 1; j < this->connect_list[i]; ++j)
            {
                 int pos;
                 fin >> pos;
                 this->node_list[i][j] = this->node_list[pos][0];
            }
        }
    }
    fin.close(); 
}

//display
void graph::display() const
{
    for (int i = 0; i < this->size; ++i)
    {
        for (int j = 0; j < this->connect_list[i]; ++j)
        {
            this->node_list[i][j].display();
            std::cout << " ";
        }
        std::cout << std::endl;
    }
}


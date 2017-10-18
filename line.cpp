#include "line.h"

//----------------- class type ------------------------------
//default constructor
type::type()
{
    this->head = NULL;
    this->loop = false;
}

//copy constructor
type::type(const type& t)
{
    this->loop = t.loop;  
    this->copy_list(this->head, t.head, this->loop);
}

void type::change_loop(bool isLoop)
{
    this->loop = isLoop;
}

//destructor: type class
type::~type()
{
    this->head = NULL;
    this->loop = false;
}

//add the new node into the location list
void type::add_node(location*& head, location*& cur, location*& src, bool isLoop)
{
    //if this is a loop line 
    if (isLoop)
    {
        if (cur->go_next() == head)
        {
            src->connect_next(*head);
            cur->connect_next(*src);
            return;
        }
        this->add_node(head, cur->go_next(), src, isLoop);
    }
    else
    {
        if (!cur->go_next())
        {
            cur->connect_next(*src);
            src->connect_prev(*cur);
            return;
        }
        this->add_node(head, cur->go_next(), src, isLoop);
    }
}

//add the new location
void type::add_location(location*& l)
{
    if (!this->head)
    {
        this->head = new location(*l);
        return;
    }
    this->add_node(this->head, this->head, l, this->loop);
}

//copy the list
void type::copy_list(location*& dest, location* src, bool isLoop)
{
    if (isLoop)
    {
        if (&dest == &src)
            return;

        dest = new location(*src);

        this->copy_list(dest->go_next(), src->go_next(), isLoop); 
    }
    else
    {
        if (!src)
            return;

        dest = new location(*src);

        this->copy_list(dest->go_next(), src->go_next(), isLoop);  
    }
}

//print the line
void type::print_line() const
{
    location* cur = this->head->go_next();
    if (!this->head)
    {
        std::cout << "No stop in the route.\n";
        return;
    }
    else if (this->loop)
    {
        this->head->display();
        std::cout << " ";
        while (cur->go_next() != this->head)
        {
            cur->display();
            cur = cur->go_next();
        }
        std::cout << "\n";
    }
    else
    {
        this->head->display();
        std::cout << " ";
        while (cur != NULL)
        {
            cur->display();
            cur = cur->go_next();
        }
        std::cout << "\n";
    }
}

//input from file
/*
void type::input_file(char* dir)
{
    std::ifstream fin;

    fin.open(dir);
    if (fin.is_open())
    {
        bool isLoop;
        fin >> isLoop
        this->change_loop(isLoop);

    }
    fin.close();
}
*/
//----------------------------- line class ------------------------------
//default constructor
line::line()
{
    this->id = NULL;
    this->nums = 0;
    this->list = NULL;
}

//copy constructor
line::line(const line& l)
    : type(l)
{
    this->id = new char[strlen(l.id)+1];
    strcpy(this->id, l.id);
    this->nums = l.nums;
    this->list = new street_car[this->nums];
    for (int i = 0; i < this->nums; ++i)
        this->list[i] = l.list[i]; 
}

line::line(char* id, int n)
{
    this->id = new char[strlen(id)+1];
    strcpy(this->id, id);
    this->nums = n;
    this->list = NULL;
}

line::line(street_car* ls, int n)
{
    std::cout << "Name of the line: ";
    this->id = new char[256];
    std::cin.getline(this->id, 256, '\n');
    this->nums = n;
    this->list = new street_car[this->nums];
    for (int i = 0; i < this->nums; ++i)
        this->list[i] = ls[i]; 
}

//destructor
line::~line()
{
    this->list = NULL;
    delete this->list;
    delete this->id;
}

//display
void line::display_line() const
{
    if (this->list == NULL || this->nums == 0)
    {
        std::cout << "The line " << this->id << " has no street cars.\n";
        return;
    }
    std::cout << "Name: " << this->id << std::endl;
    std::cout << "Stops: ";
    this->print_line();
    std::cout << "The list of street cars:\n";
    for (int i = 0; i < this->nums; ++i)
        this->list[i].display();
}

//assign street cars
void line::assign(const street_car& sc)
{
    if (this->list == NULL)
    {
        this->nums = 1;
        this->list = new street_car(sc); 
        return;
    }
    street_car* tmp = new street_car[this->nums];
    for (int i = 0; i < this->nums; ++i)
        tmp[i] = this->list[i];
    this->nums++;
    this->list = NULL;
    street_car tmp1(sc);
    this->list = new street_car[this->nums];
    for (int i = 0; i < (this->nums - 1); ++i)
        this->list[i] = tmp[i];
    this->list[this->nums-1] = tmp1; 
}

//unassign street cars
void line::unassign(const street_car& sc)
{
    if (this->list == NULL)
    {
        std::cout << "There is no street car in the line.\n";
        return;
    }
    int pos = 0;
    street_car* tmp = new street_car[this->nums]; 
    for (int i = 0; i < this->nums; ++i)
    {
        if (this->list[i] == sc)
            pos = i;
        tmp[i] = this->list[i]; 
    }
    this->list = NULL;
    this->list = new street_car[--this->nums];
    for (int i = pos; i < this->nums; ++i)
    {
        tmp[i] = tmp[i+1];  
    }
    for (int i = 0; i < this->nums; ++i)
        this->list[i] = tmp[i];
    if (this->nums == 0)
        this->list = NULL;
}

//change name of the line
void line::change_name(char* name)
{
    this->id = new char[strlen(name)+1];
    strcpy(this->id, name);
}

//= operator
line& line::operator=(const line& l)
{
    if (this != &l)
    {
        this->id = new char[strlen(l.id)+1];
        strcpy(this->id, l.id);
        this->nums = l.nums;
        this->list = NULL;
        this->list = new street_car[this->nums];
        this->copy_list(this->head, l.head, this->loop);
        for (int i = 0; i < this->nums; ++i)
            this->list[i] = l.list[i];
    }
    return *this;
}

//== operator
bool line::operator==(const line& l)
{
    if (strcmp(this->id, l.id) == 0)
        return true;
    return false;
}

//start
void line::start()
{
    for (int i = 0; i < this->nums; ++i)
        this->list[i].start();
}

//stop
void line::stop()
{
    for (int i = 0; i < this->nums; ++i)
        this->list[i].stop();
}

//--------------------------- map class ------------------------------
//default constructor
map::map()
{
    this->list = NULL;
    this->nums = 0;
}

//copy constructor
map::map(const map& m)
{
    this->nums = m.nums;
    this->list = new line[this->nums];
    for (int i = 0; i < this->nums; ++i)
        this->list[i] = m.list[i];
}

//destructor
map::~map()
{
    this->list = NULL;
    delete this->list;
    this->nums = 0;
}

//display
void map::display() const
{
    if (!this->list)
    {
        std::cout << "There is no lines in the map.\n";
        return;
    }
    std::cout << "List of lines:\n";
    for (int i = 0; i < this->nums; ++i)
        this->list[i].display_line();
}

//add a new line
void map::add_line(const line& l)
{
    if (this->list == NULL)
    {
        this->nums = 1;
        this->list = new line(l); 
        return;
    }
    line* tmp = new line[this->nums];
    for (int i = 0; i < this->nums; ++i)
        tmp[i] = this->list[i];
    this->nums++;
    this->list = NULL;
    line tmp1(l);
    this->list = new line[this->nums];
    for (int i = 0; i < (this->nums - 1); ++i)
        this->list[i] = tmp[i];
    this->list[this->nums-1] = tmp1; 
}

//remove a line
void map::remove_line(const line& l)
{
    if (this->list == NULL)
    {
        std::cout << "There is no line in the map\n";
        return;
    }
    int pos = 0;
    line* tmp = new line[this->nums]; 
    for (int i = 0; i < this->nums; ++i)
    {
       if (this->list[i] == l)
            pos = i;
        tmp[i] = this->list[i]; 
    }
    this->list = NULL;
    this->list = new line[--this->nums];
    for (int i = pos; i < this->nums; ++i)
    {
        tmp[i] = tmp[i+1];  
    }
    for (int i = 0; i < this->nums; ++i)
        this->list[i] = tmp[i];
    if(this->nums == 0)
        this->list = NULL;
}

//search
bool map::search(const line& l) const
{
    for (int i = 0; i < this->nums; ++i)
    {
        if (this->list[i] == l)
            return true;
    }
    return false;
}
//pause a line
void map::pause(const line& l)
{
    for (int i = 0; i < this->nums; ++i)
    {
        if (this->list[i] == l)
        {
            this->list[i].stop();
            return;
        }
    }
    std::cout << "No matched line.\n";
}

//start a line
void map::start(const line& l)
{
    for (int i = 0; i < this->nums; ++i)
    {
        if (this->list[i] == l)
        {
            this->list[i].start();
            return;
        }
    }
    std::cout << "No matched line.\n";
}


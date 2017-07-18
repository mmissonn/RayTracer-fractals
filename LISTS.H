#ifndef _lists_h
#define _lists_h

class node
{
   node *_next;

 public:
    node() {_next=0;}

    node *next(){return _next;}

    void next(node* n){_next = n;}
};

class Surfaces;
typedef Surfaces* Surfaces_Pt;

class object_list_node : public node
{
    Surfaces_Pt& reference;

public:
    object_list_node(Surfaces_Pt& s) : reference(s) {}

    Surfaces_Pt& objectlist() {return reference;}
};


class pile
{
    node* first_node;

public:
    pile() {first_node = 0;}

    void push(node* );
    node* pop();
    node* peek_first() { return first_node;};
};

inline void pile::push(node* n)
{
   n->next(first_node);
   first_node = n;
}

inline node* pile::pop()
{ 
   node* result = first_node;
   first_node = first_node ? first_node->next() : 0;
   return(result);
}





#endif







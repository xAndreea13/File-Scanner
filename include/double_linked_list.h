#ifndef double_linked_list
#define double_linked_list

struct list_node
{
    struct list_node *prev;
    struct list_node *next;
};

struct list_head
{
    struct list_node list;   //the structure that contains the pointers
    int counter;  //number of nodes in list
};

/*initialize a new list*/
int double_linked_list_init(struct list_head * lh);

/*get first node*/
struct list_node * get_first_node(struct list_head * lh);

/*get last node*/
struct list_node * get_last_node(struct list_head * lh);

/*get next node*/
struct list_node * get_next_node(struct list_node * node);

/*get prev node*/
struct list_node * get_prev_node(struct list_node * node);

/*add a new node to the back of a list*/
void add_end_node(struct list_head * lh, struct list_node * node);

/*add a new node to the start of a list*/
void add_start_node(struct list_head * lh, struct list_node * node);

/*removes the node - this version does not contains checkers, to be implemented*/
void remove_node(struct list_head * lh, struct list_node * node);

/*get number of nodes*/
int get_nodes_number(struct list_head * lh);

#endif
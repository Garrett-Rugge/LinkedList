#include <iostream>
#include <cassert>

using namespace std;

class List; //classes defined here so class pointers can be defined
class Iterator;

class Link { 
public:
	Link(int n);
private:
	int data;
	Link* next;
	Link* previous;
	friend class List;
	friend class Iterator;
};


class List { 
public:
	List(); 
	~List() {}
	bool empty() const;
	void push_back(int x);
	void push_front(int x);
	void pop_back();
	void pop_front();
	Iterator begin();
	Iterator end();
	Iterator erase(Iterator iter);
	int size();
	void insert(Iterator iter, int x);
private:
	Link* first;
	Link* last;
};


class Iterator {
public:
	Iterator();
	void operator++();
	int & operator*();
private:
	Link* position;
	List* container;
	friend class List;
};

Link::Link(int n){
	data = n;
	previous = NULL;
	next = NULL;
}

List::List(){
	first = NULL;
	last = NULL;	
}

bool List::empty() const {
	if(first == NULL && last == NULL) 
		return true;
	else
		return false;
}

void List::push_back(int x) { //pushes a number into the last part of the list
	Link* new_link = new Link(x);
	if(last == NULL)
	{
		first = new_link;
		last = new_link;
	}
	else
	{
		new_link->previous = last;
		last->next = new_link;
		last = new_link;
	}
}

void List::push_front(int x) { //pushes a number into the first part of the list
	Link* new_link = new Link(x);
	if(last == NULL)
	{
		first = new_link;
		last = new_link;
	}
	else
	{
		new_link->next = first;
		first->previous = new_link;
		first = new_link;
	}
}
void List::pop_back(){ //removes the last part of the list
	last = last->previous;
	last->next = NULL;
}
void List::pop_front(){ //removes the first part of the list
	first = first->next;
	first->previous = NULL;
}
void List::insert(Iterator iter, int x){ //pushes a number into a specific part of the list
	if(iter.position == NULL) //skips un-needed steps if the list is empty
	{
		push_back(x);
		return;
	}
	Link* after = iter.position;
	Link* before = after->previous;
	Link* new_link = new Link(x); 
	new_link->previous = before;
	new_link->next = after;
	after->previous = new_link;
	if(before == NULL)
		first = new_link;
	else
		before->next = new_link;
}

Iterator::Iterator(){
	position = NULL;
	container = NULL;
}

Iterator List::begin(){ //returns first part of the list
	Iterator iter;
	iter.position = first;
	iter.container = this;
	return iter;
}

Iterator List::end(){ //returns last part of the list
	Iterator iter;
	iter.position = NULL;
	iter.container = this;
	return iter;
}
void Iterator::operator++() { //moves iterator to next part of the list
	assert(position != NULL);
	position = position->next;
}
int & Iterator::operator*(){ //outputs what the iterator is pointing to
	assert(position != NULL);
	return position->data;
}

Iterator List::erase(Iterator iter){ //remove a specific part of the list
	Link* remove = iter.position;
	Link* before = remove->previous;
	Link*  after = remove->next;
	if(remove == first)
		first = after;
	else
		before->next = after;
	if(remove == last)
		last = before;
	else
		after->previous = before;
	delete remove;
	Iterator r;
	r.position = after;
	r.container = this;
	return r; //moves the iterator forward to keep it from being NULL
}
int List::size(){ //return the size of the list
	Iterator iter;
	int i = 1;
	iter.position = first;
	while(iter.position!=last){
		++i;
		++iter;
	}
	return i; 
}

int main() { //tests
	List a;
	assert(a.empty() == true);
	a.push_back(17);
	assert(a.empty() == false);
	a.push_front(3);
	a.push_back(10);
	assert(a.size() == 3);
	Iterator it = a.begin();	
	assert(*it == 3);
	++it;
	assert(*it == 17);
	++it;
	assert(*it == 10);
	it = a.begin();
	assert(*it == 3);
	*it += 1;
	assert(*it == 4);
	++it;
	a.insert(it, 29);
	it = a.begin();
	cout << *it << endl;
	++it;
	cout << *it << endl;
	++it;
	cout << *it << endl;
	++it;
	cout << "All tests passed." << endl;
}

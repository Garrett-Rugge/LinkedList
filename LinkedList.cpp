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
};

class Iterator {
public:
	Iterator();
	void operator++();
	int & operator*();
private:
	Link* position;
	friend class List;
};

Link::Link(int n){
	data = n;
	next = NULL;
}
List::List(){
	first = NULL;	
}
bool List::empty() const {
	if(first == NULL) 
		return true;
	else
		return false;
}
void List::push_back(int x) { //pushes a number into the last part of the list
	Link* new_link = new Link(x);
	Link* linkptr = first;
	if(first == NULL)
	{
		first = new_link;
	}
	else
	{
		while(linkptr->next!=NULL){
			linkptr = linkptr->next;
		}
		linkptr->next = new_link;
	}
}
void List::push_front(int x) { //pushes a number into the first part of the list
	Link* new_link = new Link(x);
	if(first == NULL)
	{
		first = new_link;
	}
	else
	{
		new_link->next = first;
		first = new_link;
	}
}
void List::pop_back(){ //removes the last part of the list
	Link * link;
	while(link!=NULL){
		link->next;
	}
	delete link->next;
	link->next = NULL;
}
void List::pop_front(){ //removes the first part of the list
	first = first->next;
}
void List::insert(Iterator iter, int x){ //pushes a number into a specific part of the list
	assert(iter.position !=NULL);
	if(iter.position == first) {
		first = new Link(x);
		return;
	}
	Link * prev = first;
	Link * after = iter.position;
	while(prev->next != iter.position)
		prev = prev->next;
	prev->next = new Link(x);
	Link * new_link = prev->next;
	new_link->next = after;
}
Iterator::Iterator(){
	position = NULL;
}
Iterator List::begin(){ //returns first part of the list
	Iterator iter;
	iter.position = first;
	return iter;
}
Iterator List::end(){ //returns last part of the list
	Iterator iter;
	iter.position = NULL;
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
	Link* after = remove->next;
	if(remove == first)
		first = after;
	delete remove;
}
int List::size(){ //return the size of the list
	Link * link = first;
	int count = 0;
	while (link != NULL) {
		++count;
		link = link->next;
	}
	return count;
}

void test1(){ //tests constructor, push back, push front, and empty
	List a;
	assert(a.empty());
	a.push_back(5);
	assert(a.empty() == false);
	a.push_front(7);
	a.push_back(9);
}
void test2(){ //tests iterator functions
	List b;
	b.push_back(5);
	b.push_back(6);
	b.push_back(7);
	Iterator it;
	it = b.begin();
	assert(*it == 5);
	++it;
	assert(*it == 6);
	++it;
	assert(*it == 7);
	b.insert(it, 10);
	it = b.begin();
	++it;
	++it;
	++it;	
	b.erase(it);
	it = b.
		begin();
	++it;
	++it;
	assert(*it == 10);
}
int main() { //tests
	test1();
	test2();
	
	cout << "All tests passed." << endl;
}

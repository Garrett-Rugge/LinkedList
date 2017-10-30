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
	Link * link = first;
	int count = 0;
	while (link != NULL) {
		++count;
		link = link->next;
	}
	return count;
}

void test1(){ //tests push back and push front
	List a;
	assert(a.empty() == true);
	a.push_back(29);
	assert(a.empty() == false);
	Iterator it;
	it = a.begin();
	assert(a.size() == 1);
	a.push_front(3);
	a.push_back(9);
	assert(*it = 29);
	it = a.begin();
	assert(*it = 3);
	a.erase(it);
	it = a.begin();
	assert(*it = 29);
	a.push_back(7);
	++it;
	a.insert(it, 5);
	it = a.begin();
	assert(*it = 5);
	++it;
	assert(*it = 29);
}
void test2(){ //tests erase and insert
	List b;
	b.push_back(20);
	Iterator it;
	it = b.begin();
	b.push_front(29);
	assert(*it = 20);
	it = b.begin();
	assert(*it = 29);
	b.erase(it);
	it = b.begin();
	assert(*it = 20);
	b.insert(it, 21);
	assert(*it = 21);
	it = b.begin();
	assert(*it = 20);
}
void test3() {//tests erasing the first number of a list
	List c;
	c.push_back(5);
	c.push_back(7);
	c.push_back(9);
	Iterator it;
	it = c.begin();
	c.erase(it);
	it = c.begin();
	assert(*it = 7);
	++it;
	assert(*it = 9);
}
void test4(){//tests erasing the middle number of a list
	List d;
	d.push_back(5);	
	d.push_back(7);
	d.push_back(9);
	Iterator it;
	it = d.begin();
	++it;
	d.erase(it);
	it = d.begin();
	assert(*it = 5);
	++it;
	assert(*it = 9);
}
void test5(){//tests erasing the last number of a list
	List e;
	e.push_back(5);	
	e.push_back(7);
	e.push_back(9);
	Iterator it;
	it = e.begin();
	++it;
	++it;
	e.erase(it);
	it = e.begin();
	assert(*it = 5);
	++it;
	assert(*it = 7);
	++it;
}
void test6(){ //size function test
	List f;
	assert(f.size() == 0);
	f.push_back(5);
	assert(f.size() == 1);
	f.push_back(7);
	assert(f.size() == 2);
	f.push_back(9);
	assert(f.size() == 3);
	
}

int main() { //tests
	test1();
	test2();
	test3();
	test4();
	test5();
	test6();
		
	cout << "All tests passed." << endl;
}

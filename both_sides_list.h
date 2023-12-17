#ifndef __BOTH_SIDES_LIST_H__
#define __BOTH_SIDES_LIST_H__

#include <climits>

#include "exception.h"

#include <ostream>


template <typename F>
class List {

private:
	
	class Node {
		friend class List;
		//Node (): value_(), prev_(nullptr), next_(nullptr) {}
		explicit Node (F& value = F(), Node* prev = nullptr, Node* next = nullptr):
										value_(value), prev_(prev), next_(next) {}
		explicit Node(const F& value): value_(value), prev_(nullptr), next_(nullptr) {}
		F value_;
		Node* prev_;
		Node* next_;
	};
	
	Node *first_;
	Node *last_;
	size_t size_;

public:
	////////////////////////////
	class Iterator {
		friend class List;
	
	private:
		Node *node_;
	
	public:
		Iterator () { node_ = nullptr;}
		// THIS CONST SH TOOK 2 F HOURS
		Iterator(const Iterator& right) {*this = right;}                     ///// AND WHY IT WORKS?????????
		// TF IT WORKS, FIELD BY FIELD??????????
		// why typename after template <T>, what with dependencies?
		explicit Iterator(Node* node): node_(node) {}
		
		Iterator& operator ++ () { node_ = node_-> next_; return *this; }
		Iterator& operator -- () { node_ = node_-> prev_; return *this; }
		Iterator& operator = (const Iterator& right) { this->node_ = right.node_; return *this; }
		bool operator != (const Iterator& right) const { return node_ != right.node_; }
		bool operator == (const Iterator& right) const { return node_ == right.node_; }
		F& operator*() const { return node_->value_; }
	};
	
	/////////////////////////////
	List();
	List(const List& right);
	~List();
	
	List& operator = (const List& right);
	List& operator += (const List& right); // concatenation
	
	void InsertBefore(const Iterator& it, const F& value);
	void AddLast(const F& new_value);
	void AddFirst(const F& new_value);
	F& GetValue(const Iterator& it) const;
	size_t Size() { return size_; }
	bool DeleteNode(Iterator& it);     // true if deleted and false otherwise
	bool operator == (const List& right);
	// next functions should be called with correct existing node - else itpos would generate conflict
	Iterator Begin() const { return Iterator(first_); }
	Iterator End() const { return Iterator(); } // const qualified at top level whatever it means
	Iterator Last() const { return Iterator(last_); }
	Iterator& FindFirstElementByValue(const F& value);
	
	template <typename K>
	friend std::ostream& operator << (std::ostream& os, const List<K>& list);
};


template <typename T>
List<T>::List(): first_(nullptr), last_(nullptr), size_(0) {}


template <typename T>
List<T>::List(const List<T>& right): first_(nullptr), last_(nullptr), size_(0){
	// TF WITHOUT IT HE JUST EAT LAST ELEMENT FROM RIGHT
	// AND WOULD BE NOT EMPTY?????????????????????????????????????????????????????????????
	if (right.size_ != 0) { // size_ = right.size_ automatically by AddFirst needed amount calls
		for (Node *p = right.first_; p != right.last_->next_; p = p->next_) {
			AddLast(p->value_);
		}
	}
}

template <typename T>
List<T>::~List() {
	Node *p = first_;
	while (p != nullptr) {
		Node *tmp = p->next_;
		delete p;
		p = tmp;
	}
	first_ = nullptr;
	last_ = nullptr;
	size_ = 0;
}

template <typename T>
void List<T>::AddFirst(const T& value) {
	try {
		if (first_ == nullptr) { // empty List
			first_ = new Node(value);
			last_ = first_;
		}
		else {
			Node *p = new Node(value);
			first_->prev_ = p;
			p->next_ = first_;
			first_ = p;
		}
		++size_;
	} catch (std::bad_alloc &) {
		throw Exception(EC_MEMORY, "List.AddFirst(value): memory allocation error");
	}
}


template <typename T>
void List<T>::AddLast(const T& value) {
	try {
		if (last_ == nullptr) { // empty List
			last_ = new Node(value);
			first_ = last_;
		}
		else {
			Node *p = new Node(value);
			last_->next_ = p;
			p->prev_ = last_;
			last_ = p;       // last_->next = nullptr; automatically by constructor of p
		}
		++size_;
	} catch (std::bad_alloc &) {
		throw Exception(EC_MEMORY, "List.AddLast(value): memory allocation error");
	}
}

template <typename T>
typename List<T>::Iterator& List<T>::FindFirstElementByValue(const T& value) {
	static Iterator it;
	for (it = Begin(); it != End(); ++it) {
		if (*it == value) return it;
	}
	return (it = End());
}

template <typename T>
bool List<T>::DeleteNode(Iterator& it) {
	// if only 1 element operator delete doesn't allocate pointer to nullptr
	// so it should be done manually
	if (it == End()) {return false;}
	Node *p = it.node_;
	if (size_ == 1) {
		if ((p != first_) || (p != last_)) {
			throw Exception(EC_UNKNOWN, "In DeleteNode call series when 1 element last_ != first_, need to revise");
		}
	}
	else if (p == first_) {  // Begin of list, it.itpos == AtBegin took away an fhour
		(first_->next_)->prev_ = nullptr; // p keeps it node
		first_ = first_->next_;
	}
	else if (p == last_) {
		last_ = last_->prev_;
		last_->next_ = nullptr; // p is still alive
	}
	else {
		(p->prev_)->next_ = p->next_;
		(p->next_)->prev_ = p->prev_;
	}
	delete p;
	--size_;
	if (size_ == 0) {
		first_ = nullptr;
		last_ = nullptr;
	}
	return true;
}

template <typename T>
void List<T>::InsertBefore(const Iterator& it, const T& value) {
	Node *p = it.node_;
	if (it == Begin()) {
		AddFirst(value);
	}
	if (it == Last()) {
		AddLast(value);
	}
	else if (it != End()) { // inside list
			Node *node = new Node(value);
			// connect with previous
			(p->prev_)->next_ = node;
			node->prev_ = (p->prev_);
			// connect with p
			node->next_ = p;
			p->prev_ = node;
		}
	else if (it == End()) {
		throw Exception(EC_RANGE, "InsertBefore called from nullptr iterator");
	}
}

template <typename T>
T& List<T>::GetValue(const Iterator& it) const {
	if (it != End()) {
		return it.node_->value_;
	} else {
		throw Exception(EC_RANGE, "Called value of nullptr iterator");
	}
}
/*
template <typename T>
typename List<T>::Iterator& List<T>::Iterator::operator = (const Iterator& right) {
	node_ = right.node_;
	return *this;
}
*/
template <typename T>
List<T>& List<T>::operator = (const List& right) {
	if (this == &right) return *this;
	// clean old list
	while (first_ != nullptr) {
		Node *p = first_;
		first_ = first_->next_;
		delete p;
	}
	first_ = right.first_;
	last_ = right.last_;
	size_ = right.size_;
	return *this;
}

template <typename T>
bool List<T>::operator == (const List& right) {
	if (size_ != right.size_) return false;
	Iterator it1 = Begin();
	for (Iterator it2 = right.Begin(); it2 != right.End(); ++it2) { // right.End() should be optimized - never-mind
		if (*it1 != *it2) return false;
		++it1;
	}
	return true;
}

/*
template <typename T>
List<T>& List<T>::operator + (const List& right) {
	last_->next_ = right.first_;
	right.first_->prev_ = last_;                          /////////////////// WHY SIGILL illegal instruction thrown here
}
*/

template <typename T>
List<T>& List<T>::operator += (const List& right) {
	if (right.size_ == 0) { return *this; }
	for (Iterator it = right.Begin(); it != right.End(); ++it) {
		AddLast(*it);
	}
	return *this;
}

template <typename T>
std::ostream& operator << (std::ostream& os, const List<T>& list) {
	os << "size: " << list.size_ << "; list: [";
	typename List<T>::Iterator it;
	if (list.size_ > 0) {
		for (it = list.Begin(); it != list.End(); ++it) {
			os << " " << *it;
		}
	}
	return (os << " ]\n");
}

#endif

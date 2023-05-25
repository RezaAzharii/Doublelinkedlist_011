#include <iostream>
#include <string>
using namespace std;

class Node {
public:
	int noMhs;
	string name;
	Node* next;
	Node* prev;
}; 

class Doublelinkedlist {
private:
	Node* START;
public:

	Doublelinkedlist();
	void addNode();
	bool search(int rollNo, Node** previous, Node** current);
	bool deleteNode(int rollNo);
	bool listEmpty();
	void ascending();
	void descending();
	void hapus();
	void searchData();
};

Doublelinkedlist::Doublelinkedlist() {
	START = NULL;
}

void Doublelinkedlist::addNode() {
	int nim;
	string nm;
	cout << "\nEnter the roll number of the student: ";
	cin >> nim;
	cout << "\Enter the name of the student: ";
	cin.ignore();
	getline(cin, nm);
	Node* newNode = new Node();
	newNode->noMhs = nim;
	newNode->name = nm;

	if (START == NULL || nim <= START->noMhs) {
		if (START != NULL && nim == START->noMhs) {
			cout << "\nDuplicate number not allowed" << endl;
			return;
		}
		newNode->next = START;
		if (START != NULL)
			START->prev = newNode;
		newNode->prev = NULL;
		START = newNode;
		return;
	}

	Node* current = START;
	while (current->next != NULL && nim > current->next->noMhs)
		current = current->next;

	if (current->next != NULL && nim == current->next->noMhs) {
		cout << "\nDuplicate roll numbers not allowed" << endl;
		return;
	}

	newNode->next = current->next;
	newNode->prev = current;
	if (current->next != NULL)
		current->next->prev = newNode;
	current->next = newNode;
}

bool Doublelinkedlist::search(int rollNo, Node** previous, Node** current) {
	*previous = *current = START;
	while (*current != NULL && rollNo != (*current)->noMhs) {
		*previous = *current;
		*current = (*current)->next;
	}
	return (*current != NULL);
}

bool Doublelinkedlist::deleteNode(int rollNo) {
	Node* previous, * current;
	previous = current = NULL;
	if (search(rollNo, &previous, &current) == false)
		return false;

	if (current->next != NULL)
		current->next->prev = previous;
	if (previous != NULL)
		previous->next = current->next;
	else
		START = current->next;

	delete current;
	return true;
}

bool Doublelinkedlist::listEmpty() {
	return (START == NULL);
}

void Doublelinkedlist::ascending() {
	if (listEmpty())
		cout << "\nList is empty" << endl;
	else {
		cout << "\nRecords in ascending order of roll number are:" << endl;
		Node* currentNode = START;
		while (currentNode != NULL) {
			cout << currentNode->noMhs << " " << currentNode->name << endl;
			currentNode = currentNode->next;
		}
	}
}

void Doublelinkedlist::descending() {
	if (listEmpty())
		cout << "\nList is empty" << endl;
	else {
		cout << "\nRecords in descending order of roll number are:" << endl;
		Node* currentNode = START;
		while (currentNode->next != NULL)
			currentNode = currentNode->next;

		while (currentNode != NULL) {
			cout << currentNode->noMhs << " " << currentNode->name << endl;
			currentNode = currentNode->prev;
		}
	}
}

void Doublelinkedlist::hapus() {
	if (listEmpty()) {
		cout << "\nList is empty" << endl;

	}
	cout << "\nEnter the roll number of the student whose record is to be deleted: ";
	int rollNo;
	cin >> rollNo;
	cout << endl;
	if (Doublelinkedlist::deleteNode(rollNo) == false)
		cout << "Record not found" << endl;
	else
		cout << "record with roll number" << rollNo << " deleted" << endl;
}

void Doublelinkedlist::searchData() {
	if (listEmpty() == true) {
		cout << "\nList is empty" << endl;

	}
	Node* prev, * curr;
	prev = curr = NULL;
	cout << "\nEnter the roll number of the student whose record you want to search: ";
	int num;
	cin >> num;
	if (Doublelinkedlist::search(num, &prev, &curr) == false)
		cout << "\nRecord not found" << endl;
	else {
		cout << "\nRecord found" << endl;
		cout << "\nRoll number: " << curr->noMhs << endl;
		cout << "\nName: " << curr->name << endl;
	}
}
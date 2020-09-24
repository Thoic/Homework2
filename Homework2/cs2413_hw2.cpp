#include <iostream>;

using namespace std;

class Course {
private:
	int capacity;
	Course* ptr_prev;
	Course* ptr_next;
public:
	Course* getPrev() {
		return ptr_prev;
	}
	Course* getNext() {
		return ptr_next;
	}
	int getCapacity() {
		return capacity;
	}
	void setPrev(Course* ptr_prev) {
		this->ptr_prev = ptr_prev;
	}
	void setNext(Course* ptr_next) {
		this->ptr_next = ptr_next;
	}
	void setCapacity(int capacity) {
		this->capacity = capacity;
	}
	Course(int capacity) {
		this->capacity = capacity;
		ptr_prev = NULL;
		ptr_next = NULL;
	}
};

int binarySearch(Course* head, int key, int front, int end);

int main() {
	int task;
	cin >> task;

	int key;
	cin >> key;

	int nextVal;

	Course* head = NULL;
	Course* tail = NULL;
	int tailIndex = 0;

	//create linked list
	while (cin >> nextVal) {
		Course* node = new Course(nextVal);
		Course* last = head;

		//if head is uninitialized
		if (head == NULL) {
			//set head and tail to node
			head = node;
			tail = node;
			continue;
		}

		//loop through current list until we reach a node where
		//the next pointer is null
		while (last->getNext() != NULL) {
			last = last->getNext();
		}
		//add the new node to the list
		last->setNext(node);
		node->setPrev(last);

		//set the tail pointer to the new node
		tail = node;
		tailIndex++;
	}

	switch (task) {
		case 0: {
			//output binary search result
			cout << binarySearch(head, key, 0, tailIndex);
			break;
		}
		case 1: {
			int index = binarySearch(head, key, 0, tailIndex);
			//if not in list, perform insertion
			if (index == -1) {
				Course* node = head;
				while (node != NULL) {
					//if the node we're at is greater than the key
					if (node->getCapacity() > key) {
						//create new node with key
						Course* new_node = new Course(key);
						
						//initialize pointers on new node
						new_node->setNext(node);
						new_node->setPrev(node->getPrev());

						//configure pointers on nodes before and after
						node->getPrev()->setNext(new_node);
						node->setPrev(new_node);
						
						//insertion complete, end loop
						break;
					}

					node = node->getNext();
				}

				node = head;
				while (node != NULL) {
					cout << node->getCapacity() << ' ';
					node = node->getNext();
				}
			}
			//if in list, perform deletion
			else {
				Course* node = head;
				while (node != NULL) {
					if (node->getCapacity() == key) {
						//if the node to be deleted is head
						if (node == head) {
							head = node->getNext();
						}

						//change next
						if (node->getNext() != NULL) {
							node->getNext()->setPrev(node->getPrev());
						}

						//change prev
						if (node->getPrev() != NULL) {
							node->getPrev()->setNext(node->getNext());
						}

						//deletion completed, end loop
						break;
					}
					node = node->getNext();
				}

				node = head;
				while (node != NULL) {
					cout << node->getCapacity() << ' ';
					node = node->getNext();
				}
				break;
			}
		}
	}

	return 0;
}

int binarySearch(Course* head, int key, int front, int end) {
	if (front > end) { return -1; }

	int midpoint = (front + end) / 2;

	//find the node at the midpoint
	Course* temp = head;
	for (int i = 0; i < midpoint; i++) {
		temp = temp->getNext();
	}

	if (key == temp->getCapacity())
		return midpoint;
	else if (key < temp->getCapacity())
		return binarySearch(head, key, front, midpoint - 1);
	else if (key > temp->getCapacity())
		return binarySearch(head, key, midpoint + 1, end);
}
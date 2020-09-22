#include <iostream>;

using namespace std;

class Course {
public:
	int capacity;
	Course* ptr_prev;
	Course* ptr_next;
	Course(int capacity);
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
		while (last->ptr_next != NULL) {
			last = last->ptr_next;
		}
		//add the new node to the list
		last->ptr_next = node;
		node->ptr_prev = last;

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
					if (node->capacity > key) {
						//create new node with key
						Course* new_node = new Course(key);
						
						//initialize pointers on new node
						new_node->ptr_next = node;
						new_node->ptr_prev = node->ptr_prev;

						//configure pointers on nodes before and after
						node->ptr_prev->ptr_next = new_node;
						node->ptr_prev = new_node;
						
						//insertion complete, end loop
						break;
					}

					node = node->ptr_next;
				}

				node = head;
				while (node != NULL) {
					cout << node->capacity << ' ';
					node = node->ptr_next;
				}
			}
			//if in list, perform deletion
			else {
				Course* node = head;
				while (node != NULL) {
					if (node->capacity == key) {
						//if the node to be deleted is head
						if (node == head) {
							head = node->ptr_next;
						}

						//change next
						if (node->ptr_next != NULL) {
							node->ptr_next->ptr_prev = node->ptr_prev;
						}

						//change prev
						if (node->ptr_prev != NULL) {
							node->ptr_prev->ptr_next = node->ptr_next;
						}

						//deletion completed, end loop
						break;
					}
					node = node->ptr_next;
				}

				node = head;
				while (node != NULL) {
					cout << node->capacity << ' ';
					node = node->ptr_next;
				}
				break;
			}
		}
	}

	return 0;
}

Course::Course(int capacity) {
	this->capacity = capacity;
	ptr_prev = NULL;
	ptr_next = NULL;
}

int binarySearch(Course* head, int key, int front, int end) {
	if (front > end) { return -1; }

	int midpoint = (front + end) / 2;

	//find the node at the midpoint
	Course* temp = head;
	for (int i = 0; i < midpoint; i++) {
		temp = temp->ptr_next;
	}

	if (key == temp->capacity)
		return midpoint;
	else if (key < temp->capacity)
		return binarySearch(head, key, front, midpoint - 1);
	else if (key > temp->capacity)
		return binarySearch(head, key, midpoint + 1, end);
}
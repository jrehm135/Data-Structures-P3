// implement your linked list template class here
template <typename T>
LinkedList<T>::LinkedList() : head(nullptr), size(0)
{}

template <typename T>
LinkedList<T>::~LinkedList()
{
	while (head != nullptr) {
		Node<T> * temp = head;
		head = head->next;
		delete temp;
	}
	head = nullptr;
	size = 0;
}
template <typename T>
LinkedList<T>::LinkedList(const LinkedList<T> & x) : head(nullptr), size(0)
{
	Node<T> * x_curr = x.head;
	Node<T> * this_prev = nullptr;

	while (x_curr != nullptr) {
		Node<T> * this_curr = new Node<T>(x_curr->data);
		this_curr->prev = this_prev;
		if (this_prev != nullptr)
			this_prev->next = this_curr;
		else head = this_curr;
		this_prev = this_curr;
		x_curr = x_curr->next;
		size += 1;
	}
}

template <typename T>
LinkedList<T>& LinkedList<T>::operator=(LinkedList<T> x)
{
	swap(*this, x);
	return *this;
}

template <typename T>
void LinkedList<T>::swap(LinkedList<T>& x, LinkedList<T>& y)
{
	std::swap(x.head, y.head);
	std::swap(x.size, y.size);
}

template <typename T>
bool LinkedList<T>::isEmpty()
{
	if (size == 0)
		return true;
	else
		return false;
	//checks if the stack is empty
}

template <typename T>
size_t LinkedList<T>::getLength()
{
	return size;
}

template <typename T>
void LinkedList<T>::insert(std::size_t position, const T& item)
{
	if (position > size)
		throw std::range_error("Entry reference greater than list length.");
	else {
	Node<T> * current = head;
	//creates a new node for the current position value
	Node<T> * newNode = new Node<T>(item);
	//creates a new node for the new position value
	int spot = 0;
	
	if (position >= 0 && position <= size)
	{
		if (position == 0)
		{
			newNode->prev = nullptr;
			//sets previous node to null
			newNode->next = head;
			//sets next node to the previous head
			head = newNode;
			//newNode becomes the new head
		}
		else if (position == size)
		{
			while (spot != position - 1)
			{
				current = current->next;
				spot++;
			}
			//iterates to the last node
			current->next = newNode;
			newNode->next = nullptr;
			newNode->prev = current;
			//sets nextNode to the next value, and the value after it to null, then adds a pointer back to the past top value
		}
		else
		{
			while (spot != position)
			{
				current = current->next;
				spot++;
			}
			//iterates to the node at position
			Node<T> * previous = current->prev;
			newNode->next = current;
			current->prev = newNode;
			newNode->prev = previous;
			previous->next = newNode;
		}
	}
	size += 1;
	//adds 1 thing, so size increases by 1
}
}

template <typename T>
void LinkedList<T>::remove(std::size_t position)
{
	if (size == 0 || position > size - 1)
		throw std::range_error("Entry reference greater than list length.");
	else {
		int spot = 0;
		Node<T>* current = head;
		if (position >= 0 && position <= size)
		{
			size--;
			if (position == 0)
			{
				head = head->next;
				head->prev = nullptr;
			}
			else if (position == size)
			{
				while (spot != position)
				{
					current = current->next;
					spot++;
				}
				current = nullptr;
			}
			else
			{
				while (spot != position)
				{
					current = current->next;
					spot++;
				}
				Node<T>* nextNode = current->next;
				current->prev->next = current->next;
				nextNode->prev = current->prev;
			}
			delete current;
		}
	}
}

template <typename T>
void LinkedList<T>::clear()
{
	while (head != nullptr) {
		Node<T> * temp = head;
		head = head->next;
		delete temp;
	}
	head = nullptr;
	size = 0;
}

template <typename T>
T LinkedList<T>::getEntry(std::size_t position)
{
	if (size == 0 || position > size - 1)
		throw std::range_error("Entry reference greater than list length.");
	else
	{
		Node<T> * current = head;
		for (int i = 0; i < position; i++) {
			current = current->next;
		}
		return current->data;
	}
}

template <typename T>
void LinkedList<T>::setEntry(std::size_t position, const T& newValue)
{
	if (size == 0 || position > size - 1)
		throw std::range_error("Entry reference greater than list length.");
	else
	{
		Node<T> * current = head;
		for (int i = 0; i < position; i++) {
			current = current->next;
		}
		current->data = newValue;
	}
}
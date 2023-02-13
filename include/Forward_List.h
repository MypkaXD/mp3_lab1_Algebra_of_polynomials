#ifndef FORWARD_LIST_H
#define FORWARD_LIST_H

#define size_t int

template <class T>
class List {
private:
	struct Node {
		T m_elem = T(); // элемент 
		Node* m_next = nullptr; // указатель на следующий элемент
		Node(T elem, Node* next) : m_elem(elem), m_next(next) {}
		Node(T elem) : m_elem(elem) {}
		Node() {}
		Node(const Node& other) {
			m_elem = other.m_elem;
			delete m_next;
			m_next = new Node();
			m_next = other.m_next;
		}
	};
	Node* m_first = nullptr;
public:
	class iterator {
	private:
		friend class List;
		Node* m_ptr = nullptr;
	public:
		iterator(Node* ptr) : m_ptr(ptr) {}
		iterator(const iterator& other) : m_ptr(other.m_ptr) {}
		~iterator() {
			m_ptr = nullptr;
		}
		iterator& operator=(const iterator& other) {
			m_ptr = other.m_ptr;
			return *this;
		}

		iterator& operator++() {
			m_ptr = m_ptr->m_next;
			return *this;
		}
		iterator operator++(int) {
			iterator temp = m_ptr;
			m_ptr += 1;
			return temp;
		}
		iterator operator+(size_t n) { // двигает не на ++ а на больше
			iterator temp(*this);
			for (size_t count = 0; count < n; ++count) {
				temp.m_ptr = temp.m_ptr->m_next;
			}
			return temp;
		}
		T& operator*() {
			return m_ptr->m_elem;
		}
		friend bool operator!=(const iterator& first, const iterator& second) {
			return (first.m_ptr != second.m_ptr);
		}
		friend bool operator==(const iterator& first, const iterator& second) {
			return !(second == first);
		}
	};
	List() {}
	explicit List(const size_t size) {
		if (size == 0)
			return;
		if (size < 0)
			throw ("ERROR: SIZE SHOULD BE GRERATER THAN ZERO");
		m_first = new Node();
		Node* temp = m_first;
		for (size_t count = 1; count < size; ++count) {
			temp->m_next = new Node();
			temp = temp->m_next;
		}
	}
	List(size_t size, T elem) {
		if (size == 0)
			return;
		m_first = new Node(elem);
		Node* temp = m_first;
		for (size_t count = 1; count < size; count++) {
			temp->m_next = new Node(elem);
			temp = temp->m_next;
		}
	}
	List(const List<T>& other) {
		delete m_first;
		m_first = new Node(other.m_first->m_elem);
		Node* temp = m_first;
		Node* hope = other.m_first;
		hope = hope->m_next;
		iterator count = other.begin();
		for (++count; count != other.end(); ++count) {
			temp->m_next = new Node(hope->m_elem);
			temp = temp->m_next;
			hope = hope->m_next;
		}
	}
	List(const std::initializer_list<T>& list) {
		delete m_first;
		m_first = new Node(*list.begin());
		Node* temp = m_first;
		for (auto it = list.begin() + 1; it < list.end(); ++it) {
			temp->m_next = new Node(*it);
			temp = temp->m_next;
		}
	}
	List(List&& other) noexcept {
		m_first = nullptr;
		std::swap(m_first, other.m_first);
	}
	~List() {
		Node* temp = m_first;
		while (temp) {
			Node* temp2 = temp->m_next;
			delete temp;
			temp = temp2;
		}
	}
	const List& operator=(const List& other) {
		if (this == &other)
			return *this;
		this->clear();
		m_first = new Node(other.m_first->m_elem);
		Node* temp1 = m_first;
		Node* temp2 = other.m_first->m_next;
		iterator count = other.begin();
		for (++count; count != other.end(); ++count) {
			temp1->m_next = new Node(temp2->m_elem);
			temp1 = temp1->m_next;
			temp2 = temp2->m_next;
		}
		return *this;
	}
	const List& operator=(List&& other) noexcept {
		if (this == &other)
			return *this;
		std::swap(m_first, other.m_first);
		return *this;
	}

	bool operator==(const List& other) const noexcept {
		if (size() != other.size())
			return false;
		else {
			iterator i = other.begin();
			for (iterator count = begin(); count != end(); ++count) {
				if (*i != *count)
					return false;
				++i;
			}
		}
		return true;
	}

	bool operator!=(const List& other) const noexcept {
		return (!(*this == other));
	}

	size_t size() const {
		Node* temp = m_first;
		size_t lenght = 0;
		for (iterator count = begin(); temp != nullptr; ++count) {
			lenght++;
			temp = temp->m_next;
		}
		return lenght;
	}

	void print() {
		Node* temp = m_first;
		for (iterator count = begin(); count != end(); ++count) {
			std::cout << temp->m_elem << "\t";
			temp = temp->m_next;
		}
	}

	void flip() {
		Node* temp = m_first;
		Node* it = m_first;
		Node* temp1 = nullptr;
		while (it) {
			temp = it->m_next;
			it->m_next = temp1;
			temp1 = it;
			it = temp;
		}
		m_first = temp1;
	}

	void merge(const List& other) {
		if (size() + other.size() == 0) return;
		Node* result = new Node(m_first->m_elem);
		Node* temp = result;
		Node* tempHop = m_first->m_next;
		iterator count = begin();
		for (++count; count != end(); ++count) {
			temp->m_next = new Node(tempHop->m_elem);
			temp = temp->m_next;
			tempHop = tempHop->m_next;
		}
		tempHop = other.m_first;
		for (iterator count = other.begin(); count != other.end(); ++count) {
			temp->m_next = new Node(tempHop->m_elem);
			temp = temp->m_next;
			tempHop = tempHop->m_next;
		}
		m_first = result;
	}

	const bool empty() const noexcept {
		//return !size();
		if (m_first == nullptr)
			return true;
		else return false;
	}

	void pop_front() {
		if (m_first == nullptr)
			throw("ERROR: the list is emptry");
		Node* temp = m_first->m_next;
		delete[] m_first;
		m_first = temp;
	}

	void push_front(const T& elem) {
		Node* temp1 = new Node(elem);
		Node* temp2 = m_first;
		m_first = temp1;
		m_first->m_next = temp2;
	}

	void assign(iterator first, iterator last) {
		Node* temp = m_first;
		while (temp) {
			Node* temp2 = temp->m_next;
			delete[] temp;
			temp = temp2;
		}
		m_first = new Node(*first);
		Node* list = m_first;
		for (++first; first != last; ++first) {
			list->m_next = new Node(*first);
			list = list->m_next;
		}
	}

	void clear() {
		if (empty()) throw ("ERROR: list is empty");

		Node* temp1 = m_first;
		Node* temp2;
		while (temp1->m_next) {
			temp2 = temp1->m_next;
			delete temp1;
			temp1 = temp2;
		}
		m_first = nullptr;
	}

	iterator insert_after(iterator prev, T value) {
		Node* temp = new Node(value);
		temp->m_next = prev.m_ptr->m_next;
		prev.m_ptr->m_next = temp;
		return iterator(temp);
	}
	iterator erase_after(iterator prev) {
		Node* temp1 = prev.m_ptr;
		Node* temp2 = temp1->m_next;
		temp1->m_next = temp2->m_next;
		delete[] temp2;
		return iterator(temp1->m_next);
	}

	const iterator cbegin() const {
		return iterator(m_first);
	}

	iterator begin() const {
		return iterator(m_first);
	}
	const iterator cend() const {
		Node* temp = m_first;
		for (size_t count = 0; count < size(); ++count) {
			temp = temp->m_next;
		}
		return iterator(temp);
	}
	iterator end() const {
		Node* temp = m_first;
		for (size_t count = 0; count < size(); ++count) {
			temp = temp->m_next;
		}
		return iterator(temp);
	}
};

#endif // !FORWARD_LIST_H
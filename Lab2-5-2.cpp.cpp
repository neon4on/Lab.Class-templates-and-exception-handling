#include <ctime>
#include <iostream>
#include <string>
using namespace std;

template<class T>
class List
{
	class Node
	{
	public:
		T data;
		Node* next;

		Node(T t = T(), Node* n = nullptr);
	};
	Node* head;
	int size;

public:
	List();
	~List();
	void pushBack(T value);
	void pushFront(T value);
	int getSize() const;
	T& operator[] (int);
	void popFront();
	void popBack();
	void clear();
	void insert(T value, int index);
	void removeAt(int index);
};

template<class T>
void show(List<T>&);

// главное меню программы
int Menu(void)
{
	int select;

	do
	{
		system("CLS");
		cout << "Информация о заявках на авиабилеты" << endl << endl;
		cout << "0 - Список" << endl;
		cout << "1 - Добавление элемента в начало списка" << endl; 
		cout << "2 - Добавление элемента в конец списка" << endl;
		cout << "3 - Получить количество элементов в списке" << endl;
		cout << "4 - Удаление последнего элемента в списке" << endl;
		cout << "5 - Удаление первого элемента в списке" << endl;
		cout << "6 - Добавление элемента в список по указанному индексу" << endl;
		cout << "7 - Удаление элемента в списке по указанному индексу" << endl;
		cout << "8 - Очистить список" << endl;
		cout << "9 - Выход из программы" << endl;
		cout << "ВЫБОР: ";
		cin >> select;
	} while ((select < 0) || (select > 9));

	return select;
}

int main()
{
	List<string> list;
	setlocale(LC_ALL, "Russian");

	int select, num;
	string a;
	do
	{
		// вызываем главное меню и выполняем выбор пользователя
		select = Menu();
		switch (select)
		{
		case 5:
		{
			list.popFront();
			break;
		}
		case 2:
		{
			cout << "Введите им: ";
			cin >> a;
			list.pushBack(a);
			break;
		}
		case 8:
		{
			list.clear();
			break;
		}
		case 3:
		{
			num = list.getSize();
			cout << "Num: " << num;
			break;
		}
		case 1:
		{
			cout << "Введите им: ";
			cin >> a;
			list.pushFront(a);
			break;
		}
		case 6:
		{
			cout << "Введите им: ";
			cin >> a;
			cout << "Введите ном: ";
			cin >> num;
			list.insert(a, num);
			break;
		}
		case 7:
		{
			cout << "Введите ном: ";
			cin >> num;
			list.removeAt(num);
			break;
		}
		case 4:
		{
			list.popBack();
			break;
		} show(list);
		case 0:
		{
			show(list);
			break;
		}
		}
		if (select != 9)
		{
			cout << endl << endl;
			system("pause");
		}
	} while (select != 9);
	return EXIT_SUCCESS;
}

template <class T>
List<T>::Node::Node(T t, Node* n)
{
	data = t;
	next = n;
}

template<class T>
List<T>::List()
{
	size = 0;
	head = nullptr;
}

template<class T>
List<T>::~List()
{
	clear();
}

template<class T>
void List<T>::pushBack(T value)
{
	if (head == nullptr)
		head = new Node(value);
	else
	{
		for (Node* current = head; ; current = current->next)
			if (current->next == nullptr)
			{
				current->next = new Node(value);
				break;
			}
	}
	size++;
}

template<class T>
void List<T>::pushFront(T value)
{
	head = new Node(value, head);
	size++;
}

template<class T>
int List<T>::getSize() const
{
	return size;
}

template<class T>
T& List<T>::operator[](int index)
{
	if (index > size - 1 || index < 0)
	{
		string message = "Недопустимый индекс ";
		message.append(to_string(index));
		throw out_of_range(message);
	}
	Node* current = head;
	for (int i = 0; i < index; i++)
		current = current->next;
	return current->data;
}

template<class T>
void List<T>::popFront()
{
	if (size <= 0) return;
	Node* temp = head;
	head = head->next;
	delete temp;
	size--;
}

template<class T>
void List<T>::popBack()
{
	removeAt(size - 1);
}

template<class T>
void List<T>::clear()
{
	while (size) popFront();
}

template<class T>
void List<T>::insert(T value, int index)
{
	if (index > size || index < 0)
	{
		string message = "Недопустимый индекс ";
		message.append(to_string(index));
		throw out_of_range(message);
	}
	if (index == 0) pushFront(value);
	else
	{
		Node* previous = head;
		for (int i = 0; i < index - 1; i++)
			previous = previous->next;
		previous->next = new Node(value, previous->next);
		size++;
	}
}

template<class T>
void List<T>::removeAt(int index)
{
	if (index > size - 1 || index < 0)
	{
		string message = "Недопустимый индекс ";
		message.append(to_string(index));
		throw out_of_range(message);
	}
	if (index == 0) popFront();
	else
	{
		Node* previous = head;
		for (int i = 0; i < index - 1; i++)
			previous = previous->next;
		Node* temp = previous->next;
		previous->next = temp->next;
		delete temp;
		size--;
	}
}

template<class T>
void show(List<T>& list)
{
	for (int i = 0; i < list.getSize(); i++) cout << list[i] << "  ";
	cout << endl;
}

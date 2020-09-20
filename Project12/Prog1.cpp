#include <iostream>
#include <iomanip>
#include <vector>
#include <algorithm>  // sort
#include "Prog1.h"

namespace Prog1 {
	const char* pr = ""; // будущее сообщение об ошибке
	// функция ввода
	Row* input(Row* head, int* a, int* b)
	{
		int MAX_X = 0, MAX_Y = 0, a1, b1;
		Row* R = nullptr;
		int m; //кол-вo элементов
		std::cout << "How many elements are there in the matrix?-->";
		if (!getNum(m) || m == 0) return nullptr;
		std::cout << "Enter items for matrix:" << std::endl;
		for (m; m > 0; m--) {
			Item* I;
			try {
				I = new Item;
			}
			catch (std::bad_alloc & ba)
			{
				std::cout << "------ too many rows in matrix: " << ba.what() << std::endl;
				return nullptr;
			}
			I->next = nullptr;
			std::cout << "Enter Y coord--> ";
			if (!getNum(I->Y)) return nullptr;
			std::cout << "Enter X coord--> ";
			if (!getNum(I->X)) return nullptr;
			std::cout << "Enter number--> ";
			if (!getNum(I->num)) return nullptr;
			if (!(R = find_Row(I->Y, head))) {
				try {
					R = new Row;
				}
				catch (std::bad_alloc & ba)
				{
					std::cout << "------ too many rows in matrix: " << ba.what() << std::endl;
					return nullptr;
				}
				R->head = nullptr;
				R->next = nullptr;
				R->i = I->Y;
				if (!head)
					head = R;
				else
					head = input_Row(R, head);
			}
			if (!R->head)
				R->head = I;
			else
				R->head = input_Item(I, R->head);

			if (MAX_Y < I->Y)
				MAX_Y = I->Y;
			if (MAX_X < I->X)
				MAX_X = I->X;
		}
		std::cout << "How many rows are in the matrix?-->";
		pr = "MIN=";
		do {
			std::cout << pr << MAX_X + 1 << std::endl;
			if (!getNum(a1)) return nullptr;
			*a = a1;
			pr = "Impossible! Impossible! Minimum number of rows:";
		} while (MAX_X + 1 > * a);
		std::cout << "How many columns are there in the matrix?-->";
		pr = "MIN=";
		do {
			std::cout << pr << MAX_Y + 1 << std::endl;
			if (!getNum(b1)) return nullptr;
			*b = b1;
			pr = "Impossible! Impossible! Minimum number of columns:";
		} while (MAX_Y + 1 > * b);
		return head;
	}
	//input Items
	void output(const char* msg, Row* head, int* a, int* b)
	{
		int i, j;
		std::cout << msg << ":\n";
		Row* R = head;
		j = R->i;
		for (j; j > 0; j--, print_0(*a - 1));
		while (R) {
			Item* I = R->head;
			i = I->X;
			for (i; i > 0; i--, std::cout << std::setw(3) << std::setprecision(3) << 0 << "  ");
			while (I) {
				std::cout << std::setw(3) << std::setprecision(3) << I->num << "  ";
				if (I->next) {
					i = I->next->X - I->X - 1;
					I = I->next;
					for (i; i > 0; i--, std::cout << std::setw(3) << std::setprecision(3) << 0 << "  ");
				}
				else break;
			}
			if (!I->X == 0)
				i = *a - I->X - 1;
			for (i; i > 0; i--, std::cout << std::setw(3) << std::setprecision(3) << 0 << "  ");
			std::cout << std::endl;

			if (R->next) {
				j = R->next->i - R->i - 1;
				for (j; j > 0; j--, print_0(*a - 1));
				R = R->next;
			}
			else break;
		}
		if (!R->i == 0)
			j = *b - R->i - 1;
		for (j; j > 0; j--, print_0(*a - 1));
	}
	//вывод 0 вместо пустых элементов
	void print_0(int MAX_X) {
		for (MAX_X; MAX_X >= 0; MAX_X--, std::cout << std::setw(3) << std::setprecision(3) << 0 << "  ");
		std::cout << std::endl;
	}
	//clear memory
	void erase(Row* Head_R)
	{
		Item* I, * Head_I;
		Row* R;
		while (Head_R) {
			R = Head_R;
			Head_I = Head_R->head;
			while (Head_I) {
				I = Head_I;
				if (Head_I->next)
					Head_I = Head_I->next;
				else {
					delete I;
					break;
				}
				delete I;
			}
			if (Head_R->next)
				Head_R = Head_R->next;
			else {
				delete R;
				break;
			}
			delete R;
		}
	}
	//вставка ряда
	Row* input_Row(Row* r, Row* head) {
		if ((r->i) > (head->i))
			if (head->next) {
				Row* R = head->next;
				while ((r->i) > (R->i))
					if (R->next)
						R = R->next;
					else {
						R->next = r;
						return head;
					}
				r->next = R;
				R = r;
				return head;
			}
			else {
				head->next = r;
				return head;
			}
		else {
			r->next = head;
			return r;
		}
	};
	//вставка элемента
	Item* input_Item(Item* i, Item* head) {
		if ((i->X) >= (head->X))
			if (head->next) {
				Item* I = head->next;
				while ((i->X) > (I->X))
					if (I->next)
						I = I->next;
					else {
						I->next = i;
						return head;
					}
				if (i->X == I->X) {
					if (I->next)
						i = I->next;
					I = i;
				}
				else {
					i->next = I;
					I = i;
				}
				return head;
			}
			else {
				if (i->X == head->X) {
					head = i;
				}
				else
					head->next = i;
				return head;
			}
		    else {
			i->next = head;
			return i;
		    }
	};
	//поиск ряда
	Row* find_Row(int i, Row* head) {
		Row* R = head;
		if (R) {
			for (R; R->i != i && R->next != nullptr; R = R->next);
			if (R->i == i)
				return R;
		}
		return nullptr;
	};

	template <class T>
	int getNum(T& a)
	{
		std::cin >> a;
		if (!std::cin.good())
			return 0;
		return 1;
	}
	
	Item* InsertionSort(Item* Head, int i)
	{

		Item* ptr = Head->next;
		Item* result = Head;
		result->next = NULL;

		while (ptr)
		{
			Item* temp = ptr;
			ptr = ptr->next;
			if (i == 1)
				result = SortedInsert1(result, temp);
			else
				result = SortedInsert2(result, temp);
		}

		return result;
	}

	Item* SortedInsert1(Item* Head, Item* NewNode)
	{
		if (Head == NULL || Head->num >= NewNode->num)
		{
			NewNode->next = Head;
			Head = NewNode;
			return Head;
		}

		Item* ptr = Head;
		Item* prev = NULL;

		while (ptr != NULL && ptr->num < NewNode->num)
		{
			prev = ptr;
			ptr = ptr->next;
		}

		NewNode->next = ptr;
		prev->next = NewNode;

		return Head;
	}

	Item* SortedInsert2(Item* Head, Item* NewNode)
	{
		if (Head == NULL || Head->num >= NewNode->num)
		{
			NewNode->next = Head;
			Head = NewNode;
			return Head;
		}

		Item* ptr = Head;
		Item* prev = NULL;

		while (ptr != NULL && ptr->num > NewNode->num)
		{
			prev = ptr;
			ptr = ptr->next;
		}

		NewNode->next = ptr;
		prev->next = NewNode;

		return Head;
	}

	void result(Row* R)
	{
		Row* r = R;
		Item* I = r->head;
		while (r != NULL) {
			int i = findfe(r->head);
			r->head = InsertionSort(r->head, i);
			r->head = changenumber(r->head);
			r = r->next;
		}
	}

	Item* changenumber(Item* r) {
		int i = 0;
		Item* head = r;
		while (r != NULL) {
			r->X = i;
			r = r->next;
			i++;
		}
		return head;
	}

	int findfe(Item* ptr) {
		while (ptr != NULL) {
			if (ptr->X == 1) {
				if (ptr->num > 0)
					return 1;
				else return -1;
			}
			ptr = ptr->next;
		}
		return -1;
	}

	double SUM(Item* I) {
		double sum = I->num;
		while (I->next) {
			I = I->next;
			sum = sum + I->num;
		}
		return sum;
	}

	bool comp(double a, double b) {
		return a > b;
	}
}
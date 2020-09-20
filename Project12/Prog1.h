namespace Prog1 {
	//������ ������
	struct Item {
		double num; //number
		int Y; //row nomber
		int X; //column nomber
		struct Item* next; //next Item
	};
	//������ �����
	struct Row {
		int i; //������ ������
		Item* head; //��������� �� ������ ������ ������
		struct Row* next; //��������� ������
	};

	// ������ ������� ����� ������ ��������
	template <class T>
	int getNum(T& a);
	Row* input_Row(Row* r, Row* head);
	Item* input_Item(Item* head, Item* I);
	int findfe(Item*);
	Item* SortedInsert1(Item*, Item*);
	Item* SortedInsert2(Item*, Item*);
	Item* changenumber(Item*);

	void print_0(int);

	// ��������� �������
	Row* input(Row*, int*, int*); // ���� �������
	Row* find_Row(int i, Row* head);
	void output(const char* msg, Row* head, int*, int*); // ����� �������
	void erase(Row*); // ������������ ������� ������
	void result(Row*); // ���������� �������� ����������
	double SUM(Item*); // ���������� ����� ����
	bool comp(double, double);
}

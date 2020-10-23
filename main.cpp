#include <iostream>
#include <time.h>
#include "llist.h"

using std::cout;
using std::endl;
using std::ostream;

struct data {
	int num;
	char c;
};

data* generateData() {
	data* d = new data();
	d->num = rand() % 10001; // 0 - 10000
	d->c = rand() % ('z' - 'a' + 1) + 'a'; // a - z
	return d;
}

ostream& operator<<(ostream& out, const data& n) {
	out << "int: " << n.num << endl << "char: " << n.c << endl;
	return out;
}

ostream& operator<<(ostream& out, data* const& n) {
	out << "int: " << n->num << endl << "char: " << n->c << endl;
	return out;
}

int dataCompare(const data& ob1, const data& ob2)
{
	int d = ob1.num - ob2.num;
	if (d != 0)
		return d;
	return ob1.c - ob2.c;
}

int dataCompare(data* const &ob1, data* const& ob2)
{
	int d = ob1->num - ob2->num;
	if (d != 0)
		return d;
	return ob1->c - ob2->c;
}

int dataCompareDelete(data* const &ob1, data* const& ob2)
{
	int d = ob1->num - ob2->num;
	if (d != 0)
		return d;
	if (ob1->c - ob2->c != 0)
		return ob1->c - ob2->c;

	delete ob2;

	return 0;
}

void test() {
	LinkedList<data> l1;

	// dane testowe
	data d1;
	d1.num = 22;
	d1.c = 'K';

	data d2;
	d2.num = 456;
	d2.c = 'a';

	data d3;
	d3.num = 123789;
	d3.c = 'S';

	data n1;
	n1.num = 999999;
	n1.c = 'X';

	data t1;
	t1.num = 1010;
	t1.c = 'o';

	// wywolania metod na liscie
	l1.addToHead(d1);
	l1.showList();

	l1.addToTail(d2);
	l1.showList();

	l1.addToTail(d3);
	l1.showList();

	l1.addToHead(d1);
	l1.showList();

	l1.addToTail(d2);
	l1.showList();

	l1.addToTail(d3);
	l1.showList();


	l1.deleteTail();
	l1.showList();

	l1.deleteHead();
	l1.showList();

	cout << "GET BY INDEX" << endl;
	data* d = l1.getByIndex(0);
	if (d != nullptr) {
		cout << *d << endl;
	}

	if (l1.getSize() > 3) {
		cout << l1[3] << endl;
	}

	l1.getByIndex(5);

	l1.getByIndex(6);


	l1.setByIndex(3, n1);
	l1.showList();


	cout << "SEARCH" << endl;
	l1.search(t1, dataCompare);

	cout << endl << endl << "SEARCH'N'DELETE" << endl << endl;
	l1.showList();
	l1.searchDelete(d3, dataCompare);
	l1.showList();

	data f1;
	f1.num = 457;
	f1.c = 'r';

	cout << endl << endl << "ADD IN ORDER" << endl << endl;
	l1.addInOrder(f1, dataCompare);

	l1.showList();

	data f2;
	f2.num = 456;
	f2.c = 'a';

	l1.addInOrder(f2, dataCompare);

	l1.showList();

	getchar();
}

int main() {
	srand(time(NULL));
	//test();

	const int testStages[] = {
		5000,
		10000,
		15000,
		20000,
		50000,
		100000
	};
	double elapsedTime = 0;

	LinkedList<data*>* l = new LinkedList<data*>();

	for (int i = 0; i < sizeof(testStages) / sizeof(testStages[0]); i++) {

		// dodawanie
		clock_t start = clock();
		for (int j = 0; j < testStages[i]; j++) {
			data* d = generateData();
			l->addToTail(d);
		}
		clock_t stop = clock();
		elapsedTime = double(stop - start) / (CLOCKS_PER_SEC);

		l->showList(10);
		printf("Dodanie %d elementow do listy zajelo %.6f s (%.3f ms)\n", testStages[i], elapsedTime, elapsedTime * 1000);
		printf("Dodanie pojedynczego elementu zajelo %.8f s (%.5f ms)\n\n", elapsedTime / testStages[i], (elapsedTime / testStages[i]) * 1000);

		// wyszukiwanie i usuwanie
		const int numOfSearches = 10000;
		start = clock();
		for (int j = 0; j < numOfSearches; j++) {
			data* d = generateData();
			l->searchDelete(d, dataCompareDelete);
			delete d;
		}
		stop = clock();
		elapsedTime = double(stop - start) / (CLOCKS_PER_SEC);

		l->showList(10);
		printf("Wyszukanie i usuniecie %d elementow z listy zajelo %.4f s (%.2f ms)\n", numOfSearches, elapsedTime, elapsedTime * 1000);
		printf("Wyszukanie i usuniecie pojedynczego elementu zajelo %.9f s (%.6f ms)\n\n", elapsedTime / numOfSearches, (elapsedTime / numOfSearches) * 1000);

		for (Element<data*>* k = l->getHead(); k != nullptr; k = k->next) {
			delete k->getData();
		}

		l->clearList();
	}

	delete l;

	cout << "Nacisnij dowolny klawisz, aby zakonczyc..." << endl;
	getchar();
	return 0;
}
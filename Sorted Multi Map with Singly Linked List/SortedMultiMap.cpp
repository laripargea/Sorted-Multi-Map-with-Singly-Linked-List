#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>
#include <vector>
#include <exception>
using namespace std;


SortedMultiMap::SortedMultiMap(Relation r) {
	//intial avem relatia si primul nod (capul) care e gol, theta(1) doar initializam
	this->R = r;
	this->head = NULL;
}

void SortedMultiMap::add(TKey k, TValue v) {
	//O(smm)
	//cautam prima data MMNode cu cheia k ca la search
	MultiMapNode* aux = head; //theta(1)
	bool found = false; //testam daca exista cheia si ne oprim cand am gasit-o sa mai iteram, theta(1)
	while (aux != NULL) //best theta(1), worst theta(smm), average theta(smm) -> O(smm)
	{
		if (aux->key == k) //theta(1)
		{
			found = true; //am gasit MMNode care contine cheia
			break;
		}
		else {
			aux = aux->next;
		}
	}
	//de data asta avem nevoie doar de valuesNodes ca sa adaugam valoarea la sfarsit
	if (!found)
	{
		// adaugam o noua cheie k cu v singura ei valoare
		if (head == NULL)
		{
			head = new MultiMapNode();
			head->next = NULL;
			head->key = k;
			//un nou ValuesNode pt lista de valori
			head->head = new ValuesNode();
			head->head->next = NULL;
			head->head->val = v;
		}
		else
		{
			// daca cheia nu exista si avem noduri trebuie adaugata pe pozitia corecta
			// daca e prima:
			if (R(k, head->key))
			{ //adaugam la inceputul MultiMapNode
				//aux = head;
				MultiMapNode* new_node = new MultiMapNode();
				new_node->key = k;
				new_node->head = new ValuesNode();
				new_node->head->val = v;
				new_node->head->next = NULL;
				new_node->next = head;
				head = new_node;
				return;
			}
			// altfel iteram nodurile sa adaugam la lista
			MultiMapNode* prev = head;
			aux = head->next;
			while (aux != NULL && !R(k, aux->key)) //best theta(1), worst theta(smm), average theta(smm) -> O(smm)
			{
				prev = aux;
				aux = aux->next;
			}
			// cand am ajuns la capat sau am gasit pozitia dupa relatie adaugam un MultiMapNode
			// aici il cream
			MultiMapNode* new_node = new MultiMapNode();
			new_node->key = k;
			new_node->head = new ValuesNode();
			new_node->head->val = v;
			new_node->head->next = NULL;
			// aici link
			prev->next = new_node;
			new_node->next = aux;
		}
	}
	else //theta(1)
	{
		//valoarea o adaugam la inceput la lista de valori
		ValuesNode* new_node = new ValuesNode();
		new_node->next = aux->head;
		new_node->val = v;
		aux->head = new_node;
	}

}

vector<TValue> SortedMultiMap::search(TKey k) const {
	//O(n)
	vector<TValue> v = vector<TValue>(); //theta(1)

	MultiMapNode* aux = head; //theta(1)
	bool found = false; // testam daca cheia existam, nu mai iteram cand am gasit-o, theta(1)
	while (aux != NULL) //best theta(1), worst theta(n), average theta(n) -> O(n)
	{
		if (aux->key == k) //theta(1)
		{
			found = true; //am gasit MMNode cu cheia
			break;
		}
		else
		{
			aux = aux->next;
		}
	}
	if (!found)
	{
		return v; //lista goala
	}
	else
	{
		// luam ValuesNode's din head
		ValuesNode* vnode = aux->head;
		while (vnode != NULL) { //best theta(1), worst theta(n), average theta(n) -> O(n)
			v.push_back(vnode->val);
			vnode = vnode->next;
		}
		return v; //theta(1)
	}

}

bool SortedMultiMap::remove(TKey k, TValue v) {
	//O(smm) pt ca nu avem while in while
	//cautam cheia
	MultiMapNode* aux = head; //theta(1)
	bool found = false; //theta(1)
	while (aux != NULL) //best theta(1), worst theta(n), average theta(n)->O(n)
	{ //merge si daca head==NULL
		if (aux->key == k)
		{
			found = true;
			break;
		}
		else
		{
			aux = aux->next;
		}
	}
	// daca nu am gasit cheia return false
	if (!found) //theta(1)
	{
		return false;
	}
	// altfel cautam valoarea in multimapnode aux
	ValuesNode* vnode = aux->head; //theta(1)
	if (vnode->next == NULL)
	{ // avem doar 1 valoare
		if (vnode->val == v)
		{
			// atunci stergem si nodul cu cheia
			//pt asta trebuie sa gasim un prev node
			// daca avem doar un multimapnod
			if (head == aux) //theta(1)
			{
				delete vnode;
				head = head->next; //poate fi si null
					// testam cand adaugam noul TElem
				delete aux; // stergem prev head
				return true;
			}
			//aux trebuie sa aiba prev node sa il folosim cand stergem
			MultiMapNode* prev = head;
			while (prev->next != aux) //best theta(1), worst theta(smm), average theta(smm) -> O(smm)
			{
				prev = prev->next;
			}
			prev->next = aux->next;
			delete vnode;
			delete aux;
			return true;
		}
		else //theta(1)
		{
			return false;
		}
	}
	//altfel avem mai multe valori
	// daca e prima
	if (vnode->val == v) //theta(1)
	{
		aux->head = vnode->next;
		delete vnode;
		return true;
	}
	ValuesNode* prev = vnode; // daca nu e primul ne trebuie iar prev node sa stergem, theta(1)
	vnode = vnode->next; //theta(1)
	while (vnode != NULL) //best theta(1), worst theta(smm), average theta(smm) -> O(smm)
	{
		if (vnode->val == v) //theta(1)
		{
			// il stergem
			prev->next = vnode->next;
			delete vnode;
			return true;
		}
		else
		{
			prev = vnode;
			vnode = vnode->next;
		}
	}
	//daca nu am gasit valoarea
	return false; //theta(1)
}


int SortedMultiMap::size() const
{
	//O(n^2)
	// numaram toate cheile din noduri si la fiecare cheie toate valorile
	MultiMapNode* mnode; //theta(1)
	ValuesNode* vnode; //theta(1)
	int size = 0; //theta(1)
	mnode = head; //theta(1)
	while (mnode != NULL) //best theta(1), worst theta(n^2) -> O(n^2)
	{
		vnode = mnode->head; //theta(1)
		while (vnode != NULL) //best theta(1), worst theta(n), average theta(n) -> O(n)
		{
			size++;
			vnode = vnode->next;
		}
		mnode = mnode->next; //theta(1)
	}
	return size; //theta(1)
}

bool SortedMultiMap::isEmpty() const
{
	//theta(1)
	if (head != NULL)
	{
		//daca head nu are nicio cheie valoare e null adica gol
		return false;
	}
	else
		return true;
}

SMMIterator SortedMultiMap::iterator() const {
	return SMMIterator(*this); //theta(1)
}

SortedMultiMap::~SortedMultiMap()
{
	//theta(smm)
	if (head != NULL)
	{
		MultiMapNode* mnode = head, * mdel; //theta(1)
		ValuesNode* vnode = NULL, * vdel; //theta(1)
		//prima data stergem nodurile de valori
		while (mnode != NULL) //best theta(smm), worst theta(smm), average theta(smm) -> theta(smm)
		{
			vdel = vnode = mnode->head; //theta(1)
			while (vnode != NULL) //best theta(n), worst theta(n), average theta(n) -> theta(n)
			{
				vnode = vnode->next;
				delete vdel;
				vdel = vnode;
			}
			mnode = mnode->next; //theta(1)
		}
		// dupa toate nodurile mmnod
		mdel = mnode = head; //theta(1)
		while (mnode != NULL) //theta(smm)
		{
			mnode = mnode->next;
			delete mdel;
			mdel = mnode;
		}
	}
}

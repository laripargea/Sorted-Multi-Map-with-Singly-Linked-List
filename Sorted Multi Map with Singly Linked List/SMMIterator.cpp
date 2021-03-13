#include "SMMIterator.h"
#include "SortedMultiMap.h"

SMMIterator::SMMIterator(const SortedMultiMap& m) : map(m) {
	// MultiMapNode si ValuesNode, theta(1) doar if/else
	this->curr_k_node = map.head;
	if (this->curr_k_node != NULL)
	{
		this->curr_v_node = curr_k_node->head;
	}
	else
	{
		this->curr_v_node = NULL;
	}
}

void SMMIterator::first() {
	//la fel cu constructor, theta(1)
	this->curr_k_node = map.head;
	if (this->curr_k_node != NULL)
	{
		this->curr_v_node = curr_k_node->head;
	}
	else
	{
		this->curr_v_node = NULL;
	}
}

void SMMIterator::next() {
	// cand nu mai avem elemente curr_k_node si curr_v_node - NULL, theta(1) doar if/else
	if (curr_v_node)
	{
		if (curr_v_node->next)
		{
			curr_v_node = curr_v_node->next;
		}
		else
		{
			//v nu e null -> k nu null
			curr_k_node = curr_k_node->next;
			if (curr_k_node)
			{
				curr_v_node = curr_k_node->head;
			}
			else
			{
				curr_v_node = NULL;
			}
		}
	}
	else
	{
		if (curr_k_node == NULL)
		{
			return;
		}
		else
		{
			curr_k_node = curr_k_node->next;
			if (curr_k_node)
			{
				curr_v_node = curr_k_node->head;
			}
		}
	}
}

bool SMMIterator::valid() const {
	if (curr_k_node != NULL) //valid daca exista adica nu e null, theta(1)
	{
		return true;
	}
	return false;
}

TElem SMMIterator::getCurrent() const {
	//theta(1)
	if (valid())
	{ // daca cheia e valida, e si valoarea
		TKey k = curr_k_node->key;
		TValue v = curr_v_node->val;
		return make_pair(k, v);
	}
	else
	{
		return NULL_TELEM;
	}
}



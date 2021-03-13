#pragma once

#include "SortedMultiMap.h"


class SMMIterator {
	friend class SortedMultiMap;
private:
	//DO NOT CHANGE THIS PART
	const SortedMultiMap& map;
	SMMIterator(const SortedMultiMap& map);

	MultiMapNode* curr_k_node;
	ValuesNode* curr_v_node;

public:
	void first();
	void next();
	bool valid() const;
	TElem getCurrent() const;
};


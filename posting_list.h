/*
 * posting_list.h
 *
 *  Created on: Jun 29, 2017
 *      Author: divya
 */

#ifndef POSTING_LIST_H_
#define POSTING_LIST_H_

#include <unordered_map>
#include <vector>

using namespace std;

class CPostingList
{
public:
	vector<int> doc_list;
	unordered_map<int, double> posting_list;
	size_t doc_list_size;


	void insertScore(int doc_id, double score);
	void remove(int doc_id);
	double getScore(int doc_id);
	size_t getSize();

};

#endif /* POSTING_LIST_H_ */

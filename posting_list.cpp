/*
 * posting_list.cpp
 *
 *  Created on: Jun 29, 2017
 *      Author: divya
 */

#include"posting_list.h"
#include<iostream>

/* insert a doc_id, score pair into the posting list */
void CPostingList::insertScore(int doc_id, double score)
{
	this->posting_list.emplace(doc_id,score);
	this->doc_list.push_back(doc_id);
	this->doc_list_size++;
}


/* Given a doc_id, look up its score in the unordered_map */
double CPostingList::getScore(int doc_id)
{
	 std::unordered_map<int,double>::const_iterator it = this->posting_list.find (doc_id);

	  if ( it == this->posting_list.end())
	  {
	    std::cout<< "doc_id = " << doc_id<< " not found";
	    return -1;
	  }
	  else
	  {
	    return it->second;
	  }
}

size_t CPostingList::getSize()
{
 return this->doc_list_size;
}

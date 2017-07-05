/*
 * TopKAlgos.cpp
 *
 *  Created on: Jun 26, 2017
 *      Author: divya
 */

#include "topK.h"

#include<vector>
#include<unordered_map>
#include<unordered_set>
#include<iostream>
#include <omp.h>


void TopKAlgos::print(vector<pair<int,double>>& print_vector,string message)
{
	cout << message << endl;
	for(size_t i = 0; i < print_vector.size(); i++)
	{
		cout << print_vector[i].first << " = " << print_vector[i].second << endl;
	}

}

void TopKAlgos::TopKInsert(pair<int,double> p, vector<pair<int, double>>& topK_vector)
{
	if(topK_vector[topK_vector.size()-1].second < p.second)
	{
	for(int i = topK_vector.size()-2 ; i >= 0; i--)
			{
				if(p.second > topK_vector[i].second)
				{
					topK_vector[i+1] = topK_vector[i];
				}
				else
				{

					topK_vector[i+1].second = p.second;
					topK_vector[i+1].first = p.first;

					break;
				}
			}
	if(p.second >= topK_vector[0].second)
	{
		topK_vector[0].second = p.second;
		topK_vector[0].first = p.first;
	}
	}

}

vector<pair<int,double>> TopKAlgos::calcTopK(long start, long end, int k)
{
	//cout << "Called calcTopK with start=" << start << " and end= " << end  << endl;
	vector<pair<int,double> > local_topK(k, std::make_pair(-1, 0.0));
	std::unordered_set<int> docs_seen_set;
	for(int i = start; i <= end; i++) //loop through every row of the posting list
	{
		double threshold = 0;
		for(size_t ii = 0; ii < posting_list_vector.size(); ii++) // loop across posting lists
		{
			int current_doc_id = posting_list_vector[ii]->doc_list[i];
			double current_topk_score = 0;
			threshold+= posting_list_vector[ii]->getScore(current_doc_id);

			std::unordered_set<int>::const_iterator got = docs_seen_set.find (current_doc_id);
			if(got == docs_seen_set.end())
			{
			for(size_t j = 0; j < posting_list_vector.size(); j++)
			{
				current_topk_score += posting_list_vector[j]->getScore(current_doc_id);

			}
			docs_seen_set.insert(current_doc_id);
			TopKInsert(std::make_pair(current_doc_id,current_topk_score), local_topK);
			}

		}
		//cout << "Threshold for sorted access " << i << "= " << threshold << endl;
	}
 return local_topK;
}

vector<int> TopKAlgos::TAFaginAlgorithm(vector<CPostingList*>& posting_lists_vector, int k)
{
	//cout << "Entering TAFagin Algo" << endl;
	int nProcs = omp_get_num_procs();
	vector<int> shared_topK;
#pragma omp parallel num_threads(4)
	{
#pragma omp critical
		{
		int tid = omp_get_thread_num();
		cout << "Thread num ::" << tid << endl;
		}
		std::vector<pair<int,double>> local_topK; // local topK recorded for each parallel block
#pragma omp for nowait
	for(int i = 0; i < nProcs; i++) // Threads that finish early can merge with shared_topK as soon as they finish (no wait)
	{
		local_topK = calcTopK(i*BLOCK_SIZE, i*BLOCK_SIZE + BLOCK_SIZE - 1, k);
	}
#pragma omp critical
	{
	print(local_topK, "Local topK are ");
	}
	}
	return shared_topK;
}

/*
vector<int> TopKAlgos::ThresholdAlgorithm(vector<CPostingList*>& posting_lists_vector, int k)
{
	std::vector<int> result_list;
	int threshold;
	#pragma omp parallel for private(threshold)
	for(int i = 0; i < posting_lists_vector.size(); i++)
	{
		for(std::list<int>::iterator it=posting_lists_vector[i]->doc_list.begin(); it != posting_lists_vector[i]->doc_list.end(); ++it)
		{
			docs_seen[*it]++;
			if(docs_seen[*it] == posting_lists_vector.size())
			{
				result_list.push_back(*it);
				if(result_list.size() == k)
				{
					exit;
				}
			}
		}
	}
}
*/



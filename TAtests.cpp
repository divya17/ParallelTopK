/*
 * TAtests.cpp
 *
 *  Created on: Jul 3, 2017
 *      Author: divya
 */


#include "topK.h"
#include "posting_list.h"
#include <iostream>
#include <fstream>
#include <sstream>

CPostingList* GeneratePostingListFromFile(std::string filename)
{
	int doc_id;
		double score;

		std::string line;
		ifstream readFile(filename);

		CPostingList* posting_list_obj = new CPostingList();


			while(!readFile.eof())
			{
			readFile >> doc_id >> score;
		    //std::cout << "reading.." << "doc =" << doc_id << " and score = " << score << endl;
		    posting_list_obj->insertScore(doc_id, score);
		    //cout << posting_list_obj->doc_list_size << endl;
			}
			//cout<< "End of creating input lists.." << endl;
			//posting_list_vector.push_back(posting_list_obj);
			//cout<< "End of creating input lists.." << endl;


		readFile.close();
		std::cout << "posting list size = " << posting_list_obj->doc_list_size << endl;
		return posting_list_obj;
}

int main()
{

	vector<CPostingList*> posting_list_vector;
	string file1 = "postingList1-1000000.txt";
	string file2 = "postingList2-1000000.txt";
	string file3 = "postingList3-1000000.txt";

	posting_list_vector.push_back(GeneratePostingListFromFile(file1));
	posting_list_vector.push_back(GeneratePostingListFromFile(file2));
	posting_list_vector.push_back(GeneratePostingListFromFile(file3));

	TopKAlgos* topK_algos_obj = new TopKAlgos(posting_list_vector);
	topK_algos_obj->TAFaginAlgorithm(topK_algos_obj->posting_list_vector, 10);



	std::cout << "The End" << endl;

}

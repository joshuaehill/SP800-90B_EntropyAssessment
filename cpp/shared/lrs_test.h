#pragma once

#include "utils.h"

/*
* ---------------------------------------------
*		LONGEST REPEATED SUBSTRING HELPERS
* ---------------------------------------------
*/

vector<byte> substr(const byte text[], int pos, int len){

	if(pos+len > SIZE){
		len = SIZE - pos;
	}

	vector<byte> substring;

	for(int i = 0; i < len; i++){
		substring.push_back(text[pos+i]);
	}

	return substring;
}

void find_substrings(const byte text[], int substr_len, map<vector<byte>, vector<int>> &indexes){

	// First iteration
	if(substr_len == 2){

		// Store all 2-tuples that appear in the text
		for(int i = 0; i < SIZE-1; i++){
			indexes[substr(text, i, substr_len)].push_back(i);
		}

	// All other iterations, don't just find all n-tuples naively like 2-tuples
	// Any (n+1)-tuple must build upon an n-tuple, so just take the existing indexes and build on them
	}else{

		vector<int> good_indexes;
		map<vector<byte>, vector<int>>::iterator itr;

		// Store all the indexes of n-tuple substrings that occur more than once
		for(itr = indexes.begin(); itr != indexes.end(); ++itr){
			for(int i = 0; i < itr->second.size(); i++){
				good_indexes.push_back(itr->second[i]);
			}

		}

		indexes.clear();

		// Extend the n-tuples to (n+1)-tuples and store like before
		for(int i = 0; i < good_indexes.size(); i++){
			indexes[substr(text, good_indexes[i], substr_len)].push_back(good_indexes[i]);
		}
	}
}

void erase_substrings(map<vector<byte>, vector<int>> &indexes){

	// Prune the map of any substrings that occur only once
	map<vector<byte>, vector<int>>::iterator itr = indexes.begin();
	while(itr != indexes.end()){
		if(itr->second.size() < 2){
			indexes.erase(itr++);
		}else{
			++itr;
		}
	}
}

int len_LRS(const byte text[], const int remaining = 1){

	// String is the substring we are looking at, vector stores the indexes those substrings begin at
	map<vector<byte>, vector<int>> indexes;
	int substr_len = 2;
	
	// Progressively grow the length of the n-tuples to look for
	while(true){
		find_substrings(text, substr_len, indexes);
		erase_substrings(indexes);

		if(indexes.size() < remaining) break;
		substr_len++;
	}

	if(remaining != 1) return substr_len;

	// We advance one further than we need to
	return substr_len-1;
}

int count_tuples(const byte data[], const int length){

	set<vector<byte>> tuples;
	for(int i = 0; i < SIZE-length; i++){
		tuples.insert(substr(data, i, length));
	}

	return ((SIZE-length) - tuples.size());
}

/*
* ---------------------------------------------
*			 HELPER FUNCTIONS
* ---------------------------------------------
*/

void calc_collision_proportion(const vector<double> &p, double &p_col){
	
	for(unsigned int i = 0; i < p.size(); i++){
		p_col += pow(p[i], 2);
	}
}

/*
* ---------------------------------------------
* 		  			 TEST
* ---------------------------------------------
*/

bool len_LRS_test(const byte data[]){

	vector<double> p(256, 0.0);
	calc_proportions(data, p);

	double p_col = 0.0;
	calc_collision_proportion(p, p_col);

	// Calculate the number of overlapping substrings of the same length as the longest repeated substring
	int lrs = len_LRS(data);
	int n = SIZE - lrs;
	long int overlap = n_choose_2(n);

	double pr_e = 1 - pow(1 - pow(p_col, lrs), overlap);

	#ifdef VERBOSE
	cout << "P_col: " << p_col << " LRS: " << lrs << " Pr(E >= 1): " << pr_e << endl;
	#endif

	return (pr_e >= 0.001);
}

double LRS_test_noniid(const byte data[]){

	int u = len_LRS(data, 20);
	int v = len_LRS(data, 2);

	cout << "u = " << u << endl;
	cout << "v = " << v << endl;

	if(v < u){
		cout << "Error in LRS" << endl;
		return 0.0;
	}

	vector<double> p;
	for(int i = u; i <= v; i++){
		int count = count_tuples(data, i);
		long double numer = n_choose_2(count);
		double denom = n_choose_2(SIZE-i+1);

		p.push_back(pow(numer/denom, 1.0/i));
	}

	double p_max = 0.0;
	for(int i = 0; i < p.size(); i++){
		if(p[i] > p_max){
			p_max = p[i];
		}
	}

	cout << "P_max = " << p_max << endl;

	return -log2(p_max);
}
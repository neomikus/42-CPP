#include "PmergeMe.hpp"

int comparisons = 0;

static int nextJacobsthal(int n_jacobsthal)
{
	return(((pow(2, n_jacobsthal)) - (pow(-1, n_jacobsthal))) / 3);
}

bool listPmergeMe::comp(const int first, const std::list<int> second)
{
	comparisons++;
	return(first < second.back());
}

void	listPmergeMe::init_list(char *argv[], listlist &sequence) {
	std::list<int>	start;

	for (size_t i = 1; argv[i]; i++)
		start.push_back(atoi(argv[i]));
	
	for (std::list<int>::iterator it = start.begin(); it != start.end(); it++)
	{
		std::list<int> temp;

		temp.push_back(*it);
		sequence.push_back(temp);
	}
}

listlist	listPmergeMe::merge(listlist lst) {
	listlist newLst;

	for (listlist::iterator it = lst.begin(); it != lst.end(); it++)
	{
		listlist::iterator first = it++;
		listlist::iterator second = it;
		std::list<int> temp;
		comparisons++;
		if (first->back() < second->back()) {
			temp = *first;
			temp.splice(temp.end(), *second, second->begin(), second->end());
		}
		else {
			temp = *second;
			temp.splice(temp.end(), *first, first->begin(), first->end());
		}
		newLst.push_back(temp);
	}

	return (newLst);
}

listlist	listPmergeMe::halve(listlist lst) {
	listlist newLst;

	for (listlist::iterator it = lst.begin(); it != lst.end(); it++)
	{
		std::list<int> temp;
		std::list<int>::iterator it2 = it->begin();

		std::advance(it2, it->size() / 2);
		temp.splice(temp.end(), *it, it2, it->end());
		newLst.push_back(*it);
		newLst.push_back(temp);
	}
	return (newLst);
}

void	listPmergeMe::constructMainPend(listlist lst, listlist &main, listlist &pend, iteratorlistlist &pairs, std::list<int> rest) {
	size_t i = 0;
	for (listlist::iterator it = lst.begin(); it != lst.end(); it++) {
		if (it != lst.begin() && !(std::distance(lst.begin(), it) % 2)) {
			pend.push_back(*it);
		}
		else {
			main.push_back(*it);
			if (i++ > 1)
				pairs.push_back(--main.end());
		}
	}

	if (!rest.empty()) {
		pend.push_back(rest);
		pairs.push_back(main.end());
	}
}

listlist	listPmergeMe::insert(listlist &main, listlist pend, iteratorlistlist pairs) {
	unsigned int jacobsthalPos = 3 - 1;
	unsigned int jacobsthalPrevPos = 1; 
	size_t jacobsthalN = 3;

	iteratorlistlist::iterator pairIt = pairs.begin();
	for (listlist::iterator pendIt = pend.begin(); !pend.empty();)
	{
		if (jacobsthalPos - jacobsthalPrevPos > pend.size())
		{
			std::advance(pendIt, pend.size());
			std::advance(pairIt, pend.size());
		}
		else
		{
			std::advance(pendIt, jacobsthalPos - jacobsthalPrevPos);
			std::advance(pairIt, jacobsthalPos - jacobsthalPrevPos);
		}
		for (; pendIt != --pend.begin();)
		{
			main.insert(std::upper_bound(main.begin(), *pairIt, pendIt->back(), comp), *pendIt);
			listlist::iterator tempPendIt = pendIt--;
			pend.erase(tempPendIt);
			iteratorlistlist::iterator tempPairIt = pairIt--;
			pairs.erase(tempPairIt);
		}
		jacobsthalPrevPos = jacobsthalPos;
		jacobsthalPos = nextJacobsthal(++jacobsthalN) - 1;
	}

	return (main);
}

listlist	listPmergeMe::mergeInsert(listlist lst) {
	std::list<int> rest;

	if (lst.size() % 2) {
		rest = lst.back();
		lst.pop_back();
	}

	lst = listPmergeMe::merge(lst);

	if (lst.size() > 1)
		lst = mergeInsert(lst);

	lst = listPmergeMe::halve(lst);

	if (lst.size() < 2)
		return (lst);

	listlist			main;
	listlist			pend;
	iteratorlistlist	pairs;
	
	listPmergeMe::constructMainPend(lst, main, pend, pairs, rest);
	listPmergeMe::insert(main, pend, pairs);

	return (main);
}

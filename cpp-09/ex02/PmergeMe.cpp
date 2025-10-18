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

bool dequePmergeMe::comp(const int first, const std::deque<int> second)
{
	comparisons++;
	return(first < second.back());
}


void	dequePmergeMe::init_deck(char *argv[], deckdeck &sequence) {
	std::deque<int>	start;

	for (size_t i = 1; argv[i]; i++)
		start.push_back(atoi(argv[i]));
	
	for (std::deque<int>::iterator it = start.begin(); it != start.end(); it++)
	{
		std::deque<int> temp;

		temp.push_back(*it);
		sequence.push_back(temp);
	}
}

deckdeck	dequePmergeMe::merge(deckdeck deck) {
	deckdeck	newDeck;

	while (!deck.empty()) {
		deckdeck::iterator	second = deck.begin();
		deckdeck::iterator	first = second++;
		std::deque<int>	temp;
		comparisons++;
		if (first->back() < second->back()) {
			temp.insert(temp.end(), first->begin(), first->end());
			temp.insert(temp.end(), second->begin(), second->end());
		}
		else {
			temp.insert(temp.end(), second->begin(), second->end());
			temp.insert(temp.end(), first->begin(), first->end());
		}
		deck.pop_front();
		deck.pop_front();
		newDeck.push_back(temp);
	}
	
	return (newDeck);
}

deckdeck	dequePmergeMe::halve(deckdeck deck) {
	deckdeck	newDeck;

	while (!deck.empty()) {
		std::deque<int>	firstHalf;
		std::deque<int>	secondHalf;

		size_t	halfDeck = 2;
		if (deck.begin()->size() > 1)
		halfDeck = deck.begin()->size() / 2;
		
		for (size_t i = 0; i < halfDeck; i++)
		{
			firstHalf.push_back(deck.begin()->front());
			deck.begin()->pop_front();
		}
		while (!deck.begin()->empty()) {
			secondHalf.push_back(deck.begin()->front());
			deck.begin()->pop_front();
		}
		newDeck.push_back(firstHalf);
		newDeck.push_back(secondHalf);
		deck.pop_front();
	}
	return (newDeck);
}

void	dequePmergeMe::constructMainPend(deckdeck deck, deckdeck &main, deckdeck &pend, std::deque<int> rest) {
	for (deckdeck::iterator it = deck.begin(); it != deck.end(); it++) {
		if (it != deck.begin() && !(std::distance(deck.begin(), it) % 2))
			pend.push_back(*it);
		else
			main.push_back(*it);
	}

	if (!rest.empty())
		pend.push_back(rest);
}

deckdeck::iterator	dequePmergeMe::search_pair(deckdeck &main, deckdeck::iterator pendIt, 
	deckdeck originalPend, deckdeck added) {
	deckdeck::iterator pos = std::find(originalPend.begin(), originalPend.end(), *pendIt);
	int newPos = std::distance(originalPend.begin(), pos);
	return (main.begin() + newPos + added.size() + 2);
}

deckdeck	dequePmergeMe::remove_values(deckdeck pend, size_t position)
{
	deckdeck newPend;
	deckdeck::iterator it = pend.begin();
	
	if (pend.size() == 1)
		return (newPend);

	for (size_t i = 0; i != position; i++) {
		it++;
	}
	it++;
	for (; it != pend.end(); it++) {
		newPend.push_back(*it);
	}

	return (newPend);
}

deckdeck	dequePmergeMe::insert(deckdeck &main, deckdeck pend) {
	unsigned int jacobsthalPos = 3 - 1;
	unsigned int jacobsthalPrevPos = 1; 
	size_t jacobsthalN = 3;
	deckdeck			originalPend = pend;
	deckdeck			added;

	for (deckdeck::iterator pendIt = pend.begin(); !pend.empty(); pendIt = pend.begin()) {
		if (pend.size() > 1 && jacobsthalPos - jacobsthalPrevPos > pend.size()) {
			std::advance(pendIt, pend.size());
		}
		else if (pend.size() > 1) {
			std::advance(pendIt, jacobsthalPos - jacobsthalPrevPos);
		}
		if (pendIt == pend.end()) {
			pendIt--;
		}
		int pos = std::distance(pend.begin(), pendIt);
		for (int currentPos = pos; currentPos >= 0; currentPos--) {
			main.insert(std::upper_bound(main.begin(), search_pair(main, pendIt, originalPend, added), pendIt->back(), comp), *pendIt);
			added.push_back(*pendIt);
			if (pendIt != pend.begin())
				pendIt--;
		}
		pend = remove_values(pend, pos);
		jacobsthalPrevPos = jacobsthalPos;
		jacobsthalPos = nextJacobsthal(++jacobsthalN) - 1;
	}

	return (main);
}

deckdeck	dequePmergeMe::mergeInsert(deckdeck deck) {
	std::deque<int> rest;

	if (deck.size() % 2) {
		rest = deck.back();
		deck.pop_back();
	}

	deck = dequePmergeMe::merge(deck);

	if (deck.size() > 1)
		deck = mergeInsert(deck);

	deck = dequePmergeMe::halve(deck);
	
	if (deck.size() < 2)
		return (deck);	

	deckdeck			main;
	deckdeck			pend;
	
	dequePmergeMe::constructMainPend(deck, main, pend, rest);
	dequePmergeMe::insert(main, pend);

	return (main);

}

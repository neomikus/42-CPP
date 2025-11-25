#ifndef PMERGEME_HPP
#define PMERGEME_HPP

#include <list>
#include <deque>
#include <iostream>
#include <utility>
#include <cstdlib>
#include <cmath>
#include <ctime>
#include <algorithm>

#define RESET   "\033[0m"
#define BLACK   "\033[30m"      /* Black */
#define RED     "\033[31m"      /* Red */
#define GREEN   "\033[32m"      /* Green */
#define YELLOW  "\033[33m"      /* Yellow */
#define BLUE    "\033[34m"      /* Blue */
#define MAGENTA "\033[35m"      /* Magenta */
#define CYAN    "\033[36m"      /* Cyan */
#define WHITE   "\033[37m"      /* White */
#define BOLDBLACK   "\033[1m\033[30m"      /* Bold Black */
#define BOLDRED     "\033[1m\033[31m"      /* Bold Red */
#define BOLDGREEN   "\033[1m\033[32m"      /* Bold Green */
#define BOLDYELLOW  "\033[1m\033[33m"      /* Bold Yellow */
#define BOLDBLUE    "\033[1m\033[34m"      /* Bold Blue */
#define BOLDMAGENTA "\033[1m\033[35m"      /* Bold Magenta */
#define BOLDCYAN    "\033[1m\033[36m"      /* Bold Cyan */
#define BOLDWHITE   "\033[1m\033[37m"      /* Bold White */

typedef std::list<std::list<int> > listlist;
typedef std::list<std::list<std::list <int> >::iterator > iteratorlistlist;

namespace listPmergeMe
{
	void 		init_list(char *argv[], listlist &sequence);
	bool		comp(const int first, const std::list<int> second);
	listlist	merge(listlist lst);
	listlist	halve(listlist lst);
	void		constructMainPend(listlist lst, listlist &main, listlist &pend, 
									iteratorlistlist &pairs, std::list<int> rest);
	listlist	insert(listlist &main, listlist pend, iteratorlistlist pairs);
	listlist	mergeInsert(listlist lst);
}

typedef std::deque<std::deque<int> > deckdeck;
typedef std::deque<std::deque<std::deque <int> >::iterator > iteratordeckdeck;


namespace dequePmergeMe
{
	void 				init_deck(char *argv[], deckdeck &sequence);
	bool				comp(const int first, const std::deque<int> second);
	deckdeck			merge(deckdeck deck);
	deckdeck			halve(deckdeck deck);
	void				constructMainPend(deckdeck deck, deckdeck &main, deckdeck &pend, std::deque<int> rest, std::deque<int> &pairs);
	deckdeck			insert(deckdeck &main, deckdeck pend, std::deque<int> &pairs);
	deckdeck			mergeInsert(deckdeck deck);
	deckdeck			remove_values(deckdeck pend, size_t position);
	std::deque<int>		remove_values(std::deque<int> pairs, size_t position);
	deckdeck::iterator	search_pair(deckdeck &main, const std::deque<int> pairs, const int currentPos);
	void				update_pairs(std::deque<int> &pairs, int insertedPosition);
}

void	print(deckdeck deck);
#endif
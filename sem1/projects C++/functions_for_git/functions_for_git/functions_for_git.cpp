#pragma once

#include <iostream>
#include <list>
#include <set>
#include <stdexcept>
#include <vector>

/*template <class Iterator>
Iterator LocalMax(Iterator first, Iterator last) {
  Iterator it;
  for (it = first; it != last; ++it) {
    if ((first + 1) == last) {
      return first;
    } else if (it == first) {
      if (*it > *(it + 1)) {
        return it;
      }
    } else if (it == last - 1) {
      if (*it > *(it - 1)) {
        return it;
      }
    } else {
      if (*it > *(it - 1) && *it > *(it + 1)) {
        return it;
      }
    }
  }
  return it;
}*/
template <class Iterator, class Predicate>
Iterator Partition(Iterator first, Iterator last, Predicate pred) {
  Iterator it;
  while (pred(*first)) {
    ++first;
  }
  for (Iterator i = first; ++i != last;) {
    if (pred(*i)) {
      auto t = *first;
      *first = *i;
      *i = t;
      ++first;
    }
  }
  return first;
}
int main() {
  std::vector<int> victor = { 5, 6,2, 7,1, 7, 4};
  std::vector<int>::iterator iter =
      Partition(victor.begin(), victor.end(), [](int a) { return a > 2; });
  std::cout << *iter;
  for(std::vector<int>::iterator i = victor.begin(); i!=victor.end(); ++i){
    std::cout << *i << "\n";
  }
}

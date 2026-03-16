#include "spellcheck.h"

#include <algorithm>
#include <iostream>
#include <numeric>
#include <ranges>
#include <set>
#include <vector>
#include<string>

template <typename Iterator, typename UnaryPred>
std::vector<Iterator> find_all(Iterator begin, Iterator end, UnaryPred pred);

Corpus tokenize(std::string& source) {
  Corpus corpus;
  auto is_space= [](unsigned char ch){return std::isspace(ch);};
  auto its=find_all(source.begin(),source.end(),is_space);

  std::transform(its.begin(),its.end()-1,its.begin()+1,
    std::inserter(corpus,corpus.end()),
    [&source](Token t,auto it1,auto it2){
    return t(source,it1,it2);
  });

  std::erase_if(corpus,[](Token t){return t.content.empty();});
  return corpus;
}

std::set<Misspelling> spellcheck(const Corpus& source, const Dictionary& dictionary) {
  using rv=std::ranges::view;
  auto misspell_view= source|
  return std::set<Misspelling>();
};

/* Helper methods */

#include "utils.cpp"
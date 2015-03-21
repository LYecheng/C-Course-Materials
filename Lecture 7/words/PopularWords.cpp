#include <iostream>
#include <iterator>
#include <algorithm>
#include <map>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>    
#include <string>
#include <set>
#include <cctype>
#include <limits>
#include <utility>
#include <iomanip>
using namespace std;
using namespace boost::filesystem;
using namespace boost;
using namespace boost::algorithm;

size_t const topWords = 20;

int main(int argc, char* argv[])
{
  path p(argv[1]);   // p reads clearer than argv[1] in the following code
  map<string, size_t> wordCountMap;
  try
  {
    string delimChars;
    for (unsigned u = 0; u < numeric_limits<unsigned char>::max(); u++) {
      if (isspace(u) || ispunct(u))
        delimChars.append(1, u);
    }
    char_separator<char> delimiters(delimChars.c_str());
    for (auto iter = directory_iterator(p); iter != directory_iterator(); iter++) {
      boost::filesystem::ifstream file(iter->path());
      string line;
      while (getline(file, line)) {
        tokenizer<char_separator<char>> tok(line, delimiters);
        for (auto token : tok) {
          to_lower(token);
          wordCountMap[token]++;
        }
      }
    }
  }
  catch (filesystem_error const& ex)  {
    cout << ex.what() << '\n';
  }
  vector<pair<string, unsigned>> wordCountVector(wordCountMap.begin(), wordCountMap.end());
  if (wordCountVector.empty()) {
    cout << "No words found" << endl;
    return 1;
  }
  size_t adjustedTopWords = min(topWords, wordCountVector.size());
  partial_sort(wordCountVector.begin(),
    wordCountVector.begin() + adjustedTopWords,
    wordCountVector.end(),
    [](pair<string, unsigned> const &l, pair<string, unsigned> const &r) {
    return l.second > r.second;
  });
  for (auto wc = wordCountVector.begin(); wc < wordCountVector.begin() + adjustedTopWords; wc++)
    cout << left << setw(10) << wc->second << wc->first << endl;
  return 0;
}
#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/tokenizer.hpp>
#include <boost/algorithm/string.hpp>    
#include <string>
#include <set>
#include <cctype>
#include <limits>
using namespace std;
using namespace boost::filesystem;
using namespace boost;
using namespace boost::algorithm;

int main(int argc, char* argv[])
{
  path p(argv[1]);   // p reads clearer than argv[1] in the following code
  set<string> words;
  try
  {
    string delimChars;
    for (unsigned char u = 0; ; u++) {
      if (isspace(u) || ispunct(u))
        delimChars.append(1, u);
      if (u == numeric_limits<unsigned char>::max())
        break;
    }
    char_separator<char> delimiters(delimChars.c_str());
    for (auto iter = directory_iterator(p); iter != directory_iterator(); iter++) {
      boost::filesystem::ifstream file(iter->path());
      string line;
      while (getline(file, line)) {
        tokenizer<char_separator<char>> tok(line, delimiters);
        transform(tok.begin(), tok.end(), inserter(words, words.begin()),
          [](string s)->string { to_lower(s); return s;  });
      }
    }
  }
  catch (filesystem_error const& ex)  {
    cout << ex.what() << '\n';
  }
  cout << words.size() << endl;
  return 0;
}
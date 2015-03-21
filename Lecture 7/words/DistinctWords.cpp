#include <iostream>
#include <iterator>
#include <algorithm>
#include <boost/filesystem.hpp>
#include <boost/filesystem/fstream.hpp>
#include <boost/tokenizer.hpp>
#include <string>
#include <set>
using namespace std;
using namespace boost::filesystem;
using namespace boost;

int main(int argc, char* argv[])
{
  path p(argv[1]);   // p reads clearer than argv[1] in the following code
  set<string> words;
  try
  {
    char_separator<char> delimiters(" \t");
    for (auto iter = directory_iterator(p); iter != directory_iterator(); iter++) {
      boost::filesystem::ifstream file(iter->path());
      string line;
      while (getline(file, line)) {
        tokenizer<char_separator<char>> tok(line, delimiters);
        copy(tok.begin(), tok.end(), inserter(words, words.begin()));
      }
    }
  }
  catch (filesystem_error const& ex)  {
    cout << ex.what() << '\n';
  }
  cout << words.size() << endl;
  return 0;
}
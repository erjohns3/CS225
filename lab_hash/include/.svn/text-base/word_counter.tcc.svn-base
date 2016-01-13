/**
 * @file word_counter.cpp
 * Implementation of the WordFreq class.
 *
 * @author Chase Geigle
 * @date Spring 2011
 * @date Spring 2012
 */

using std::vector;
using std::pair;
using std::string;
using std::ifstream;
using std::istringstream;
using std::cout;
using std::endl;

template <template <class K, class V> class HT>
WordFreq<HT>::WordFreq(const string& infile)
    : filename(infile)
{
    /* nothing */
}

template <template <class K, class V> class HT>
vector<pair<string, int>> WordFreq<HT>::getWords(int threshold) const
{
    vector< pair<string, int> > ret;
    /**
	* @todo Implement this function.
	* @see char_counter.cpp if you're having trouble.
	*/
	HT<string, int> table {1};
	TextFile text {filename};
	while(text.good()){
		std::string word = text.getNextWord();
		if(table.contains(word))
			table[word]++;
		else
			table.insert(word, 1);
	}
	for (auto i=table.begin(); i!=table.end(); i++){
		if(i->second >= threshold){
			pair<string, int> pair(i->first, i->second);
			ret.push_back(pair);
		}
	}
    return ret;
}

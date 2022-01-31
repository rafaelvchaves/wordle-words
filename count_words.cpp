#include <algorithm>
#include <fstream>
#include <iostream>
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

void display(std::unordered_map<std::string, int> &map)
{
  using pair_t = std::pair<std::string, int>;
  std::vector<pair_t> freq_vec(map.size());
  uint32_t index = 0;
  for (auto [key, val] : map)
  {
    freq_vec[index++] = {key, val};
  }
  std::sort(freq_vec.begin(), freq_vec.end(),
            [](const pair_t &p1, const pair_t &p2)
            { return p1.second > p2.second || (p1.second == p2.second && p1.first < p2.first); });
  for (auto [key, val] : freq_vec)
  {
    std::cout << key << ": " << val << std::endl;
  }
}

bool has_duplicates(std::string& word) {
  std::unordered_set<char> characters;
  for (unsigned int i = 0; i < word.size(); i++) {
    if (characters.count(word[i]) > 0) {
      return true;
    }
    characters.insert(word[i]);
  }
  return false;
}

int main()
{
  std::vector<std::string> words;
  std::unordered_map<std::string, int> letter_pos_count;
  std::ifstream infile("words.txt");
  std::string word;
  while (infile >> word)
  {
    int word_length = word.length();
    if (word_length == 5 && word[4] != 's')
    {

      // std::cout << word << std::endl;
      for (unsigned int i = 0; i < word_length; i++)
      {
        words.push_back(word);
        std::string key = std::string(1, word[i]) + std::to_string(i + 1);
        letter_pos_count[key]++;
      }
    }
  }
  int num_words = words.size();
  // for (auto [letter_pos, count] : letter_pos_count)
  // {
  //   letter_pos_count[letter_pos] = count / num_words;
  // }
  display(letter_pos_count);
  std::unordered_map<std::string, int> word_scores;
  for (auto word : words)
  {
    if (has_duplicates(word)) continue;
    int word_length = word.length();
    int score = 0;
    for (unsigned int i = 0; i < word_length; i++)
    {
      std::string key = std::string(1, word[i]) + std::to_string(i + 1);
      score += letter_pos_count[key];
    }
    word_scores[word] = score;
  }
  display(word_scores);
  return 0;
}
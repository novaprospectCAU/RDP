#include "utils.hpp"

// C표준과 파서 규칙에 따라 나올 수 없는 단어인지 확인하는 함수
bool word_checker(string word)
{
  if (word.length() == 0)
  {
    return false;
  }
  if (!word.compare(";") ||
      !word.compare("(") ||
      !word.compare(")") ||
      !word.compare(":="))
  {
    return true;
  }
  if (!word.compare("+") ||
      !word.compare("-") ||
      !word.compare("*") ||
      !word.compare("/"))
  {
    return true;
  }
  if (word.length() == 1 && (isalnum(word.at(0))))
  {
    return true;
  }
  if (isalpha(word.at(0)) || word.at(0) == '-')
  {
    for (int i = 1; i < word.length(); i++)
    {
      if (!isalpha(word.at(i)))
      {
        return false;
      }
    }
    return true;
  }
  for (int i = 0; i < word.length(); i++)
  {
    if (!isalnum(word.at(i)) || word.at(i) != '_')
    {
      return false;
    }
  }
  return true;
}
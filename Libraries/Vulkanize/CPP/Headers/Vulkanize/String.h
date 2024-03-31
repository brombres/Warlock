#pragma once

#include <string>
#include <vector>

struct StringPool
{
  std::vector<std::string*> strings;

  ~StringPool()
  {
    for (auto st : strings) delete st;
    strings.clear();
  }

  std::string& on_use()
  {
    if (strings.size())
    {
      auto result = strings.back();
      strings.pop_back();
      return *result;
    }
    else
    {
      return *(new std::string());
    }
  }

  void on_end_use( std::string& st )
  {
    st.clear();
    strings.push_back( &st );
  }
};

struct String
{
  static StringPool pool;

  std::string& value;

  String() : value(pool.on_use()) {}
  ~String() { pool.on_end_use(value); }

  std::string& operator*() { return value; }
  std::string* operator->() { return &value; }
};

StringPool String::pool;

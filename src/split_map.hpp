#ifndef SPLIT_MAP_HPP
#define SPLIT_MAP_HPP

#include <iostream>
#include <optional>
#include <stdint.h>
#include <unordered_map>

template <class K, class V> class split_map
{
private:
  uint32_t capacity;
  uint32_t size;

  static const uint32_t default_capacity = 64;
  static const uint32_t capacity_scale_factor = 2;

  std::unordered_map<K, V> table;

public:
  split_map () : capacity (default_capacity){};

  void
  put (K key, V value)
  {
    table[key] = value;
  };

  std::optional<V>
  get (K key)
  {
    auto iter = table.find (key);
    if (iter == table.end ())
      return std::nullopt;
    else
      return iter->second;
  };

  void
  print ()
  {
    for (auto &elem : table)
      {
        std::cout << elem.first << ": " << elem.second << ", ";
      }
  };
};

#endif
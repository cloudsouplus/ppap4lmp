/*!
  @file src/filters/fil_set.cpp
  @brief This file has an implementation of the FilSet class, which is
  a subclass of the Filter class.
  @author Takayuki Kobayashi
  @date 2018/07/01
  @details For more details, please see the header file,
  src/filters/fil_set.h.
*/

#include "fil_set.h"

/* ------------------------------------------------------------------ */

FilSet::FilSet(
  const Map<Str,Set<Json>> &value_sets_)
{
  value_sets = value_sets_;
}

/* ------------------------------------------------------------------ */

FilSet::FilSet(
  const ElPtr &elem,
  const Map<Str,Set<Json>> &value_sets_) : Filter(elem)
{
  value_sets = value_sets_;
}

/* ------------------------------------------------------------------ */

void FilSet::compute_impl(
  Json &data,
  DataKeys &datakeys)
{
  for (const auto &item : value_sets)
  {
    datakeys.required(item.first);
  }

  Json tmp = Json::array();

  for (const auto &d : data)
  {
    bool pass = true;

    for (const auto &item : value_sets)
    {
      auto set = item.second;

      if (set.find(d[item.first]) == set.end())
      {
        pass = false;
        break;
      }
    }

    if (pass)
    {
      tmp.push_back(d);
    }
  }

  data.swap(tmp);
}

/* ------------------------------------------------------------------ */

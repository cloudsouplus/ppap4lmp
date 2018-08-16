/* ---------------------------------------------------------------------
AddMap: stands for Adder for Mapping from existing properties to new
properties.

create: 2018/06/24 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "add_map.h"
#include "utils.h"

/* ------------------------------------------------------------------ */

AddMap::AddMap(
  const Str &key_ref_, const Str &key_new_,
  const Dict<Json,Json> &mapping_)
{
  key_ref = key_ref_;
  key_new = key_new_;
  mapping = mapping_;
}

/* ------------------------------------------------------------------ */

void AddMap::compute_impl(Json &data, Set<Str> &datakeys)
{
  if (!check_containment<Str>(datakeys, key_ref))
  {
    runtime_error("AddMap needs '" + key_ref + "'");
    return;
  }

  if (data.is_array())
  {
    for (auto &d : data)
    {
      d[key_new] = mapping.at(d[key_ref]);
    }
  }
  else
  {
    data[key_new] = mapping.at(data[key_ref]);
  }

  datakeys.insert(key_new);
}
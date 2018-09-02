/* ---------------------------------------------------------------------
StaMolecules: stands for Starter to generate Molecules from atoms.

create: 2018/07/07 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#include "sta_molecules.h"
#include "../utils.h"

/* ------------------------------------------------------------------ */

StaMolecules::StaMolecules(
  ShPtr<Element> gen_atoms)
{
  ext_generator = gen_atoms;
}

/* ------------------------------------------------------------------ */

void StaMolecules::compute_impl(
  Json &data,
  Set<Str> &datakeys)
{
  auto gen_atoms = ext_generator->get_element();

  check_keys(gen_atoms, {"mol", "id"});

  auto &atoms = gen_atoms->get_data();

  Dict<int,int> id2index;

  int max_index = 0;

  for (const auto &atom : atoms)
  {
    int molid = atom["mol"];

    if (id2index.find(molid) == id2index.end())
    {
      data[max_index]["id"] = molid;
      id2index[molid] = max_index++;
    }

    data[id2index[molid]]["atom-ids"].push_back(atom["id"]);
  }

  datakeys.insert({"id", "atom-ids"});
}
/* ---------------------------------------------------------------------
GenDict: stands for Generator Dictionary containing elements.

create: 2018/07/03 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef GEN_DICT_H
#define GEN_DICT_H

#include <generators/generator.h>

class GenDict : public Generator {
  Dict<Str,ShPtr<Generator>> generator_dict;
 public:
  GenDict(
    const Dict<Str,ShPtr<Generator>> &generator_dict_);
  virtual ~GenDict() = default;
  virtual ShPtr<Element> get_element(
    Json name = nullptr) override;
  virtual ShPtr<Generator> get_generator(
    Json name = nullptr) override;
  const Set<Str> get_keys();
};

#endif
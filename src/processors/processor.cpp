/*!
  @file src/processors/processor.cpp
  @brief This file has an implementation of Processor class,
  where an analysis process is programmed.
  @author Takayuki Kobayashi
  @date 2018/06/22
*/

#include "processor.h"

/* ------------------------------------------------------------------ */

template <class GEN>
void Processor::register_generator(
  const ShPtr<GEN> &gen)
{
  generators.clear();

  generators.push_back(gen);

  n_generators = generators.size();
}

template void Processor::register_generator(
  const ElPtr &gen);
template void Processor::register_generator(
  const ShPtr<GenDict> &gen);
template void Processor::register_generator(
  const ShPtr<GenList> &gen);

/* ------------------------------------------------------------------ */

template <class GEN>
void Processor::register_generators(
  const Vec<ShPtr<GEN>> &gens)
{
  generators.clear();

  for (const auto &gen : gens)
  {
    generators.push_back(gen);
  }

  n_generators = generators.size();
}

template void Processor::register_generators(
  const Vec<ElPtr> &gens);
template void Processor::register_generators(
  const Vec<ShPtr<GenDict>> &gens);
template void Processor::register_generators(
  const Vec<ShPtr<GenList>> &gens);

/* ------------------------------------------------------------------ */

bool Processor::run()
{
  int index;

  #pragma omp critical (processor)
  {
    index = i_generator++;
  }

  if (index < n_generators)
  {
    generators[index]->hello();

    run_impl(index);

    generators[index]->goodbye();

    return false;
  }

  return true;
}

/* ------------------------------------------------------------------ */

void Processor::startup()
{
  #pragma omp critical (processor)
  {
    i_generator = 0;
  }

  for (const auto &g : generators)
  {
    g->appoint();
  }
}

/* ------------------------------------------------------------------ */

/*!
  @file src/starters/sta_dump_atoms.h
  @brief This file has a definition of StaDumpAtoms class,
  which is a subclass of Starter class.
  @author Takayuki Kobayashi
  @date 2018/06/29
*/

#ifndef STA_DUMP_ATOMS_H
#define STA_DUMP_ATOMS_H

#include <starters/sta_dump.h>

/*!
  @brief StaDumpAtoms reads a Lammps' dump file
  and sets properties for atoms.

  An object of this class reads properties of atoms
  from a Lammps' dump file specified by #filepath.
  Note that only properties at a time specified by #timestep are read.

  About usage in Python,
  please see pybind::py_sta_dump_atoms.
*/
class StaDumpAtoms : public StaDump {
  /*!
    Make a list whether each value printed in a line of
    a Lammps' dump file is an integer or not.

    @param line
      The first line in a body of a Lammps' dump file:
      a line below the line beginning with <c>ITEM: ATOMS</c>.

    @return A constant ::Vec object containing booleans
    whether each value in the \c line is an integer or not.
  */
  const Vec<bool> make_is_int_vector(
    const Str &line);
 protected:
  /*!
    @brief This method overrides Updater::compute_impl.

    <dl class="property added">
      <dt class="property added">Property to be added</dt>
      <dd class="property added">
        - Keys to be set are names of dumped Lammps' atom property.
          In a Lammps' dump file, the names are printed in a line
          beginning with <c>ITEM: ATOMS</c>.
      </dd>
    </dl>
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  using StaDump::StaDump;
  virtual ~StaDumpAtoms() = default;
};

#endif
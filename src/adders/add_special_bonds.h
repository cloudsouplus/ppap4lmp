/*!
  @file src/adders/add_special_bonds.h
  @brief This file has a definition of AddSpecialBonds class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/08/19
*/

#ifndef ADD_SPECIAL_BONDS_H
#define ADD_SPECIAL_BONDS_H

#include <adders/adder.h>

/*!
  @brief AddSpecialBonds adds special bonds.
  @details This class inherits Adder class and overrides
  Adder::compute_impl.

  Special bonds is a property for atoms (or beads) belonging to
  the same molecule; if an atom has another atom as one of its special
  bonds, the two atoms are considered to interact with each other
  through bonded potential(s) (bond-length, bond-angle ...).

  An object of this class has a molecular Element object as
  the #ext_generator, and is appended to an atomic (or bead) Element
  object. That object owns schemes for special bonds for each type of
  molecule; a scheme is something like a list of special bonds of
  atoms in one molecule.

  About usage in Python,
  please see src/pybind/adders/py_add_special_bonds.h.

  Key of property to be added:
    - \c <c>special-bonds</c> (array of integer)

  Key of required property:
    - \c atom-ids (array of integer)
*/
class AddSpecialBonds : public Adder {
  /*!
    @brief Schemes of special bonds for each molecular type.
    @details Definition of special bonds is stored as a map (dictionary)
    from molecular types to vector of vector (list of list) of
    zero-based index of atoms <i>in a molecule</i> of the type.
    The first vector corresponds atoms in a molecule,
    and the second vector corresponds special bonds of the each atom.
  */
  Map<int,Vec<Vec<int>>> mol_type_to_sbondses_in_mol;
 protected:
  /*!
    @copydoc AddMap::compute_impl
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddSpecialBonds class for
    one molecular type.
    @param el_mols : Shared pointer to a molecular Element object
    consisting of an atomic (or bead) Element object where the
    constructed object is appended to.
    This argument is assigned to #ext_generator.
    @param scheme : ::Vec of ::Vec of zero-based index of atoms in
    a molecule.
    This argument is stored in #mol_type_to_sbondses_in_mol as a scheme
    for molecular type 1.
  */
  AddSpecialBonds(
    const ElPtr &el_mols,
    const Vec<Vec<int>> &scheme);
  /*!
    @brief Constructor of AddSpecialBonds class for
    multiple molecular types.
    @param el_mols : Shared pointer to a molecular Element object
    consisting of an atomic (or bead) Element object where the
    constructed object is appended to.
    This argument is assigned to #ext_generator.
    @param schemes : ::Map from molecular types to ::Vec of ::Vec of
    zero-based index of atoms in a molecule.
    This argument is assigned to #mol_type_to_sbondses_in_mol.
  */
  AddSpecialBonds(
    const ElPtr &el_mols,
    const Map<int,Vec<Vec<int>>> &schemes);
  virtual ~AddSpecialBonds() = default;
};

#endif
/*!
  @file src/adders/add_child_positions.h
  @brief This file has a definition of AddChildPositions class,
  which is a subclass of Adder class.
  @author Takayuki Kobayashi
  @date 2018/09/03
*/

#ifndef ADD_CHILD_POSITIONS_H
#define ADD_CHILD_POSITIONS_H

#include <adders/adder.h>

/*!
  @brief AddChildPositions adds relative positions of a child Element
  object to a parent Element object.
  @details An object of this class owns a \e child object
  as #ext_generator, and is appended to a \e parent object
  using its Element::append_updater. An example of \e child is
  an Element object containing data for atoms, and an example of
  \e parent is an Element object containing data for molecules.
  Positions of a \e child is computed relative to a position
  of a \e parent and appended to an array belonging to the \e parent.

  The terms \e child and \e parent are used because a \e parent object
  consists of a \e child object. In terms of time series, however,
  the \e child is created earlier than the \e parent.

  About usage in Python,
  please see src/pybind/adders/py_add_child_positions.h.
*/
class AddChildPositions : public Adder {
  /*!
    @brief Name of \e child object stored as #ext_generator.
    @details The key for property added to a \e parent object
    by this class is named as <c>[child_name]-xs</c>,
    <c>[child_name]-ys</c> and <c>[child_name]-zs</c>.
    The \e parent object is also required to have
    <c>[child_name]-ids</c> property.
  */
  Str child_name;
 protected:
  /*!
    @copydoc Updater::compute_impl
    @details
    <table class="py_table2">
      <caption>
        AddChildPositions related properties
      </caption>
      <tr class="py_tr">
        <th class="py_th2">Key for property to be added</th>
        <th class="py_th2">Key for required property</th>
        <th class="py_th2">Key for externally required property</th>
      </tr>
      <tr class="py_tr">
        <td class="py_td">
          - <c>[child_name]-xs</c> : array of floats
          - <c>[child_name]-ys</c> : array of floats
          - <c>[child_name]-zs</c> : array of floats
        </td>
        <td class="py_td">
          - <c>[child_name]-ids</c> : array of integers
          - \c xu : float
          - \c yu : float
          - \c zu : float
        </td>
        <td class="py_td">
          - \c id : integer
          - \c xu : float
          - \c yu : float
          - \c zu : float
        </td>
      </tr>
    </table>
  */
  virtual void compute_impl(
    Json &data,
    DataKeys &datakeys) override;
 public:
  /*!
    @brief Constructor of AddChildPositions class.
    @param elem : Shared pointer to a \e child object.
    This argument is assigned to #ext_generator.
    @param child_name_ : A string for naming the \e child object.
    This argument is assigned to #child_name.
  */
  AddChildPositions(
    const ElPtr &elem,
    const Str &child_name_);
  virtual ~AddChildPositions() = default;
};

#endif
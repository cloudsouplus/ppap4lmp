import unittest
import traceback

from ppap4lmp import \
  create, StaCustom, StaMolecules, AddCoMPosition, AddInertiaMoment

class TestAddInertiaMoment(unittest.TestCase):

  custom_data = [
    {"id": 1, "mol": 1, "mass": 1.0, "xu": 1.0, "yu": 0.0, "zu": 0.0},
    {"id": 2, "mol": 1, "mass": 1.0, "xu": -1.0, "yu": 0.0, "zu": 0.0},
    {"id": 3, "mol": 1, "mass": 1.0, "xu": 0.0, "yu": 1.0, "zu": 0.0},
    {"id": 4, "mol": 1, "mass": 1.0, "xu": 0.0, "yu": -1.0, "zu": 0.0},
    {"id": 5, "mol": 1, "mass": 1.0, "xu": 0.0, "yu": 0.0, "zu": 1.0},
    {"id": 6, "mol": 1, "mass": 1.0, "xu": 0.0, "yu": 0.0, "zu": -1.0},
  ]

  def test_error01(self):

    atoms = create(StaCustom(self.custom_data))
    molecules = create(StaMolecules(atoms))
    molecules.append_updater(AddCoMPosition(atoms))

    molecules.append_updater(
      AddInertiaMoment(create(StaCustom({"foo": 0, "bar": 1}))))

    try:
      molecules.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: Missing key(s) 'id', 'mass', 'xu', 'yu', 'zu'")

  def test_error02(self):

    atoms = create(StaCustom(self.custom_data))
    molecules = create(StaMolecules(atoms))
    molecules.append_updater(AddInertiaMoment(atoms))

    try:
      molecules.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: Missing key(s) 'xu', 'yu', 'zu'")

  def test_isotropic(self):

    atoms = create(StaCustom(self.custom_data))
    molecules = create(StaMolecules(atoms))
    molecules.append_updater(AddCoMPosition(atoms))
    molecules.append_updater(AddInertiaMoment(atoms))

    data = molecules.get_data()[0]

    self.assertEqual(data["I_xx"], data["I_yy"])
    self.assertEqual(data["I_yy"], data["I_zz"])
    self.assertEqual(data["I_xy"], data["I_xz"])
    self.assertEqual(data["I_xy"], data["I_yz"])

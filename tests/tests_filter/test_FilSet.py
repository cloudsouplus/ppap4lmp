import unittest
import traceback

from ppap4lmp import create, StaDumpAtoms, StaCopy, FilSet

class TestFilSet(unittest.TestCase):

  def test_error01(self):

    atoms = create(
      StaDumpAtoms("dumps_bead/bead.2990000.dump", 2990000))
    atoms.append_updater(FilSet({"dummy": {1, 2, 3}}))

    try:
      atoms.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: Missing key(s) 'dummy'")

  def test_equivalent_filter(self):

    self._test_equivalent_filter(
      ("dumps_bead/bead.2990000.dump", 2990000),
      {"mol": {1, 2, 3}}, {"id": set(range(120001, 120082))})

    self._test_equivalent_filter(
      ("dumps_atom/atom.0.dump", 0),
      {"mol": {4, 5}}, {"id": set(range(115, 191))})

  def _test_equivalent_filter(self, arguments, filter1, filter2):

    atoms = create(StaDumpAtoms(*arguments))
    filtered_atoms1 = create(
      StaCopy(atoms)).append_updater(FilSet(filter1))
    filtered_atoms2 = create(
      StaCopy(atoms)).append_updater(FilSet(filter2))

    self.assertEqual(
      filtered_atoms1.get_data(), filtered_atoms2.get_data())
    self.assertEqual(
      filtered_atoms1.get_keys(), filtered_atoms2.get_keys())

  def test_remaining_number(self):

    self._test_remaining_number(
      ("dumps_bead/bead.2990000.dump", 2990000),
      {"mol": {1, 2, 3}}, 81)

    self._test_remaining_number(
      ("dumps_atom/atom.0.dump", 0),
      {"mol": {4, 5}, "type": {1}}, 24)

  def _test_remaining_number(self, arguments, filterset, num):

    atoms = create(StaDumpAtoms(*arguments))
    atoms.append_updater(FilSet(filterset))

    self.assertEqual(len(atoms.get_data()), num)

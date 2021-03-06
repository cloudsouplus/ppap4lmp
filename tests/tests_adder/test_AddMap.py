import unittest
import traceback

from ppap4lmp import create, StaCustom, AddMap

class TestAddMap(unittest.TestCase):

  def test_error01(self):

    elem = create(StaCustom({"foo": 0, "bar": 1}))
    elem.append_updater(AddMap("dummy", "new", {1: 0}))

    try:
      elem.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: Missing key(s) 'dummy'")

  def test_error02(self):

    elem = create(StaCustom({"foo": 0, "bar": 1}))
    elem.append_updater(AddMap("foo", "bar", {0: 1}))

    try:
      elem.get_data()
    except SystemError:
      msg = traceback.format_exc()
      self.assertEqual(
        msg.split("\n")[0],
        "RuntimeError: Key 'bar' already exists")

  def test_nonarray(self):

    data_old = {"A": 1, "B": 2}
    data_new = {"A": 1, "B": 2, "C": 3}

    elem = create(StaCustom(data_old))
    elem.append_updater(AddMap("A", "C", {1: 3, 2: 2, 3: 1}))

    self.assertEqual(data_new, elem.get_data())
    self.assertEqual({"A", "B", "C"}, elem.get_keys())

  def test_array(self):

    data_old = [{"A": i, "B": i*i} for i in range(1000)]
    data_new = [{"A": i, "B": i*i, "C": i%3} for i in range(1000)]

    mapping = {i: i%3 for i in range(1000)}

    elem = create(StaCustom(data_old))
    elem.append_updater(AddMap("A", "C", mapping))

    self.assertEqual(data_new, elem.get_data())
    self.assertEqual({"A", "B", "C"}, elem.get_keys())

  def test_overwrite(self):

    data_old = [{"A": i, "B": i*i} for i in range(1000)]
    data_new = [{"A": i, "B": i%3} for i in range(1000)]

    mapping = {i: i%3 for i in range(1000)}

    elem = create(StaCustom(data_old))
    elem.append_updater(AddMap("A", "B", mapping).overwrite())

    self.assertEqual(data_new, elem.get_data())
    self.assertEqual({"A", "B"}, elem.get_keys())
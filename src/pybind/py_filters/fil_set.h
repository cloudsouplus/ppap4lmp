#ifndef PYBIND_FIL_SET_H
#define PYBIND_FIL_SET_H

#include <filters/fil_set.h>
#include <pybind/py_filters/filter.h>

static void pybind_fil_set(py::module &m)
{
  py::class_<FilSet,PyUpdater<FilSet>,Filter,Updater,ShPtr<FilSet>>(m, "FilSet")
    .def(py::init<const Map<Str,Set<Json>> &>())
    .def(py::init<const ElPtr &,const Map<Str,Set<Json>> &>());
}

#endif
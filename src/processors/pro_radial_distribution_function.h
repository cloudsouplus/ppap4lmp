/* ---------------------------------------------------------------------
ProRadialDistributionFunction: stands for Processor which computes
Radial Distribution Function (RDF) from wrapped positions.

create: 2018/08/19 by Takayuki Kobayashi
--------------------------------------------------------------------- */

#ifndef PRO_RADIAL_DISTRIBUTION_FUNCTION_H
#define PRO_RADIAL_DISTRIBUTION_FUNCTION_H

#include <processors/processor.h>

class ProRadialDistributionFunction : public Processor {
  int n_bins = 1;
  double bin_width = 1.0;
  bool bin_from_r = false;
  bool beyond_half = false;
  ArrayXd rdf;
  List<ArrayXd> rdf_traj;
  List<double> density_traj;
  List<ArrayXd> number_distribution_traj;
 protected:
  virtual void run_impl(
    int index) override;
 public:
  ProRadialDistributionFunction(
    ShPtr<Element> atoms,
    ShPtr<Element> box);
  ProRadialDistributionFunction(
    List<std::pair<ShPtr<Element>,ShPtr<Element>>> pairs);
  virtual ~ProRadialDistributionFunction() = default;
  virtual void prepare() override;
  virtual void finish() override;
  void set_bin(
    double bin_width_,
    int n_bins_);
  void bin_from_r_to_r_plus_dr(
    bool bin_from_r_ = true);
  void beyond_half_box_length(
    bool beyond_half_ = true);
  const ArrayXd get_r_axis();
  const ArrayXd &get_rdf();
  const List<ArrayXd> &get_rdf_traj();
};

#endif
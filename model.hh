// Copyright 2017 Global Phasing Ltd.
//
// Data structures to keep macromolecular structure model.

#ifndef GEMMI_MODEL_HH_
#define GEMMI_MODEL_HH_

#include <vector>
#include <string>
#include "elem.hh"

namespace gemmi {
namespace mol {

struct Structure;
struct Model;
struct Chain;
struct Residue;

enum class EntityType { Unknown, Polymer, NonPolymer, Water };

struct Atom {
  std::string name;
  char altloc;
  signed char charge;  // [-8, +8]
  Element element = El::X;
  double x, y, z;
  float occ;
  float b_iso;
  Residue* parent = nullptr;
};

struct Residue {
  int seq_id = -1000;
  char ins_code = '\0';
  std::string name;
  std::vector<Atom> atoms;
  Chain* parent = nullptr;
  Residue(int id, char ins, std::string rname) noexcept
    : seq_id(id), ins_code(ins), name(rname) {}
};

struct Chain {
  std::string name;
  EntityType entity_type = EntityType::Unknown;
  std::vector<Residue> residues;
  Model* parent = nullptr;
  explicit Chain(std::string cname) noexcept : name(cname) {}
};

struct Model {
  std::string name;  // actually an integer number
  std::vector<Chain> chains;
  Structure* parent = nullptr;
  explicit Model(std::string mname) noexcept : name(mname) {}
};

struct UnitCell {
  double lengths[3];
  double angles[3];
};

struct Structure {
  std::string entry_id;
  UnitCell cell;
  int z;
  std::string sg_hm;
  std::vector<Model> models;
  // std::vector<Ops> ncs;
};

} // namespace mol
} // namespace gemmi
#endif
// vim:sw=2:ts=2:et
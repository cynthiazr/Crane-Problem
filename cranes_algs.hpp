///////////////////////////////////////////////////////////////////////////////
// cranes_algs.hpp
//
// Algorithms that solve the crane unloading problem.
//
// All of the TODO sections for this project reside in this file.
//
// This file builds on crane_types.hpp, so you should familiarize yourself
// with that file before working on this file.
//
///////////////////////////////////////////////////////////////////////////////

#pragma once

#include <cassert>
#include <math.h>

#include "cranes_types.hpp"

namespace cranes {

// Solve the crane unloading problem for the given grid, using an exhaustive
// optimization algorithm.
//
// This algorithm is expected to run in exponential time, so the grid's
// width+height must be small enough to fit in a 64-bit int; this is enforced
// with an assertion.
//
// The grid must be non-empty.
path crane_unloading_exhaustive(const grid& setting) {

  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);

  // Compute maximum path length, and check that it is legal.
  const size_t max_steps = setting.rows() + setting.columns() - 2;
  assert(max_steps < 64);

  path best(setting);

  // Loop through all possible paths of length up to max_steps.
  for (size_t steps = 0; steps <= max_steps; steps++) {

    // Loop through all possible binary strings of length steps.
    for (size_t path_bits = 0; path_bits <= pow(2, steps) - 1; path_bits++) {

      // Generate a path from the binary string of steps bits.
      path candidate(setting);
      bool valid_path = true;

      for (size_t i = 0; i < steps; i++) {
        // Extract the i-th bit from path_bits.
        bool east = (path_bits >> i) & 1;
        step_direction dir;
        if (east) {
          // Move east.
          dir = STEP_DIRECTION_EAST;
        } else {
          // Move south.
          dir = STEP_DIRECTION_SOUTH;
        }

        if (candidate.is_step_valid(dir)) { // if the next step is valid, add the next step to the candidate path
          candidate.add_step(dir);
        } else {
          valid_path = false; // Otherwise, the next step is invalid and we stop checking
          break;
        }
      }

      // If the candidate path is valid and it reaches more cranes than the current best path,
      // update the best path to be the candidate path.
      if (valid_path && candidate.total_cranes() > best.total_cranes()) {
        best = candidate;
      }
      
    }
  }
  return best;
}


// Solve the crane unloading problem for the given grid, using a dynamic
// programming algorithm.
//
// The grid must be non-empty.
//path crane_unloading_dyn_prog(const grid& setting) {
path crane_unloading_dyn_prog(const grid& setting) {

  path best(setting);

  // grid must be non-empty.
  assert(setting.rows() > 0);
  assert(setting.columns() > 0);
  
  using cell_type = std::optional<path>;

  std::vector<std::vector<cell_type> > A(setting.rows(),
                                        std::vector<cell_type>(setting.columns()));

  A[0][0] = path(setting);
  assert(A[0][0].has_value());

  for (coordinate r = 0; r < setting.rows(); ++r) {
    for (coordinate c = 0; c < setting.columns(); ++c) {

      if (setting.get(r, c) == CELL_BUILDING){
        A[r][c].reset();
        continue;
        }

      cell_type from_above = std::nullopt;
      cell_type from_left = std::nullopt;

	    // TODO: implement the dynamic programming algorithm, then delete this
      // comment.

      // assert(best->has_value());
      //  //   std::cout << "total cranes" << (**best).total_cranes() << std::endl;

     // return **best;
	  }
  }
  return best;
}

}
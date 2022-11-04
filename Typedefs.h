#ifndef TYPEDEFS_H
#define TYPEDEFS_H

#include <vector>
#include <array>
#include <memory>

class Move;

typedef std::array<int, 2> coords_t;

typedef std::vector<std::shared_ptr<Move>> moves_t;
typedef std::shared_ptr<Move> move_ptr_t;

#endif

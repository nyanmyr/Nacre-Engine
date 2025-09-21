#ifndef DEPENDENCIES_HPP
#define DEPENDENCIES_HPP

#include <iostream>
#include <vector>
#include <queue>
#include <unordered_map>
#include <memory>
#include <string>

#include <SFML/Graphics.hpp>

using std::queue;
using std::vector;
using std::unordered_map;
using std::runtime_error;
using std::shared_ptr;
using std::make_shared;
using std::static_pointer_cast;
using std::cout;
using std::map;
using std::string;

using namespace sf;
// using is too tedious

using Entity = uint32_t;

using DeltaTime = float;

const Entity MAX_ENTITIES = 10;

#endif
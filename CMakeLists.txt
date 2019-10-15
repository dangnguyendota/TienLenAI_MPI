cmake_minimum_required(VERSION 3.15)
project(MPIProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(MPIProject main.cpp objects/Card.cpp objects/Card.h base/BaseObject.cpp base/BaseObject.h base/BaseCard.cpp base/BaseCard.h base/Game.h base/Player.h base/Reward.h base/GameConfiguration.h base/GameConfig.h base/Node.h objects/Dub.cpp objects/Dub.h objects/Trips.cpp objects/Trips.h objects/Quads.cpp objects/Quads.h objects/DubSequence.cpp objects/DubSequence.h objects/TripSequence.cpp objects/TripSequence.h objects/QuadSequence.cpp objects/QuadSequence.h)
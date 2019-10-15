cmake_minimum_required(VERSION 3.15)
project(MPIProject)

set(CMAKE_CXX_STANDARD 14)

add_executable(MPIProject main.cpp base/Card.cpp base/Card.h base/BaseObject.cpp base/BaseObject.h base/BaseCard.cpp base/BaseCard.h base/Game.h base/Player.h base/Reward.h base/GameConfiguration.h base/GameConfig.h base/Node.h)
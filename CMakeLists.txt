cmake_minimum_required(VERSION 3.13)
project(ParseTree)

set(CMAKE_CXX_STANDARD 17)

include_directories(include)
link_directories(library)

add_library(ParseTree SearchDirectionType.h Symbol.cpp Symbol.h ParseNode.cpp ParseNode.h ParseTree.cpp ParseTree.h NodeCondition/NodeCondition.h NodeCondition/IsLeaf.cpp NodeCondition/IsLeaf.h NodeCondition/IsEnglishLeaf.cpp NodeCondition/IsEnglishLeaf.h NodeCollector.cpp NodeCollector.h TreeBank.cpp TreeBank.h ConstituentSpan.cpp ConstituentSpan.h ParallelTreeBank.cpp ParallelTreeBank.h)
add_executable(Test SearchDirectionType.h Symbol.cpp Symbol.h ParseNode.cpp ParseNode.h ParseTree.cpp ParseTree.h NodeCondition/NodeCondition.h NodeCondition/IsLeaf.cpp NodeCondition/IsLeaf.h NodeCondition/IsEnglishLeaf.cpp NodeCondition/IsEnglishLeaf.h NodeCollector.cpp NodeCollector.h TreeBank.cpp TreeBank.h ConstituentSpan.cpp ConstituentSpan.h Test/SymbolTest.cpp Test/NodeCollectorTest.cpp Test/ParseTreeTest.cpp Test/TreeBankTest.cpp ParallelTreeBank.cpp ParallelTreeBank.h Test/ParallelTreeBankTest.cpp)

target_link_libraries(ParseTree Dictionary)
target_link_libraries(Test Dictionary)
cmake_minimum_required(VERSION 3.13)
project(ParseTree)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")

find_package(dictionary REQUIRED)

add_library(ParseTree src/ModifiedParsevalMetric.cpp src/ModifiedParsevalMetric.h src/ParsevalMetric.cpp src/ParsevalMetric.h src/ModifiedLeafAncestorMetric.cpp src/ModifiedLeafAncestorMetric.h src/LeafAncestorMetric.cpp src/LeafAncestorMetric.h src/Metric.h src/SearchDirectionType.h src/Symbol.cpp src/Symbol.h src/ParseNode.cpp src/ParseNode.h src/ParseTree.cpp src/ParseTree.h src/NodeCondition/NodeCondition.h src/NodeCondition/IsLeaf.cpp src/NodeCondition/IsLeaf.h src/NodeCondition/IsEnglishLeaf.cpp src/NodeCondition/IsEnglishLeaf.h src/NodeCollector.cpp src/NodeCollector.h src/TreeBank.cpp src/TreeBank.h src/ConstituentSpan.cpp src/ConstituentSpan.h src/ParallelTreeBank.cpp src/ParallelTreeBank.h)
target_link_libraries(ParseTree dictionary::dictionary)
add_executable(Test src/ModifiedParsevalMetric.cpp src/ModifiedParsevalMetric.h src/ParsevalMetric.cpp src/ParsevalMetric.h src/ModifiedLeafAncestorMetric.cpp src/ModifiedLeafAncestorMetric.h src/LeafAncestorMetric.cpp src/LeafAncestorMetric.h src/Metric.h src/SearchDirectionType.h src/Symbol.cpp src/Symbol.h src/ParseNode.cpp src/ParseNode.h src/ParseTree.cpp src/ParseTree.h src/NodeCondition/NodeCondition.h src/NodeCondition/IsLeaf.cpp src/NodeCondition/IsLeaf.h src/NodeCondition/IsEnglishLeaf.cpp src/NodeCondition/IsEnglishLeaf.h src/NodeCollector.cpp src/NodeCollector.h src/TreeBank.cpp src/TreeBank.h src/ConstituentSpan.cpp src/ConstituentSpan.h Test/MetricTest.cpp Test/SymbolTest.cpp Test/NodeCollectorTest.cpp Test/ParseTreeTest.cpp Test/TreeBankTest.cpp src/ParallelTreeBank.cpp src/ParallelTreeBank.h Test/ParallelTreeBankTest.cpp)
target_link_libraries(Test dictionary::dictionary)
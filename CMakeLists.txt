cmake_minimum_required(VERSION 3.13)
project(ParseTree)
set(CMAKE_CXX_STANDARD 20)

include(${CMAKE_BINARY_DIR}/conanbuildinfo.cmake)
conan_basic_setup()
set(CONAN_INCLUDE_DIRS_DICTIONARY "/Users/olcay/.conan/data/Dictionary/1.0.0/_/_/package/ace494fb7be9c56def71a38747cca129e2ccda0d/include")

add_library(ParseTree src/ModifiedParsevalMetric.cpp src/ModifiedParsevalMetric.h src/ParsevalMetric.cpp src/ParsevalMetric.h src/ModifiedLeafAncestorMetric.cpp src/ModifiedLeafAncestorMetric.h src/LeafAncestorMetric.cpp src/LeafAncestorMetric.h src/Metric.h src/SearchDirectionType.h src/Symbol.cpp src/Symbol.h src/ParseNode.cpp src/ParseNode.h src/ParseTree.cpp src/ParseTree.h src/NodeCondition/NodeCondition.h src/NodeCondition/IsLeaf.cpp src/NodeCondition/IsLeaf.h src/NodeCondition/IsEnglishLeaf.cpp src/NodeCondition/IsEnglishLeaf.h src/NodeCollector.cpp src/NodeCollector.h src/TreeBank.cpp src/TreeBank.h src/ConstituentSpan.cpp src/ConstituentSpan.h src/ParallelTreeBank.cpp src/ParallelTreeBank.h)
add_executable(Test src/ModifiedParsevalMetric.cpp src/ModifiedParsevalMetric.h src/ParsevalMetric.cpp src/ParsevalMetric.h src/ModifiedLeafAncestorMetric.cpp src/ModifiedLeafAncestorMetric.h src/LeafAncestorMetric.cpp src/LeafAncestorMetric.h src/Metric.h src/SearchDirectionType.h src/Symbol.cpp src/Symbol.h src/ParseNode.cpp src/ParseNode.h src/ParseTree.cpp src/ParseTree.h src/NodeCondition/NodeCondition.h src/NodeCondition/IsLeaf.cpp src/NodeCondition/IsLeaf.h src/NodeCondition/IsEnglishLeaf.cpp src/NodeCondition/IsEnglishLeaf.h src/NodeCollector.cpp src/NodeCollector.h src/TreeBank.cpp src/TreeBank.h src/ConstituentSpan.cpp src/ConstituentSpan.h Test/MetricTest.cpp Test/SymbolTest.cpp Test/NodeCollectorTest.cpp Test/ParseTreeTest.cpp Test/TreeBankTest.cpp src/ParallelTreeBank.cpp src/ParallelTreeBank.h Test/ParallelTreeBankTest.cpp)

target_link_libraries(ParseTree ${CONAN_LIBS})
target_link_libraries(Test ${CONAN_LIBS})
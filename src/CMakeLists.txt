cmake_minimum_required(VERSION 3.13)
project(ParseTree)
set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_FLAGS "-O3")

find_package(dictionary REQUIRED)

add_library(ParseTree EvaluationMetrics/ModifiedParsevalMetric.cpp EvaluationMetrics/ModifiedParsevalMetric.h EvaluationMetrics/ParsevalMetric.cpp EvaluationMetrics/ParsevalMetric.h EvaluationMetrics/ModifiedLeafAncestorMetric.cpp EvaluationMetrics/ModifiedLeafAncestorMetric.h EvaluationMetrics/LeafAncestorMetric.cpp EvaluationMetrics/LeafAncestorMetric.h EvaluationMetrics/Metric.h SearchDirectionType.h Symbol.cpp Symbol.h ParseNode.cpp ParseNode.h ParseTree.cpp ParseTree.h NodeCondition/NodeCondition.h NodeCondition/IsLeaf.cpp NodeCondition/IsLeaf.h NodeCondition/IsEnglishLeaf.cpp NodeCondition/IsEnglishLeaf.h NodeCollector.cpp NodeCollector.h TreeBank.cpp TreeBank.h ConstituentSpan.cpp ConstituentSpan.h ParallelTreeBank.cpp ParallelTreeBank.h)
target_link_libraries(ParseTree dictionary::dictionary)

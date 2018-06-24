#include <iostream>
#include <gtest/gtest.h>
#include <gmock/gmock.h>
#include "Graph.h"
#include "Graph.cpp"
using namespace std;

TEST(graph, graph)
{
    SparseGraph<GraphNode, GraphEdge> graph;

    GraphNode n;
    GraphEdge e1(0, 1);
    // addNode
    EXPECT_EQ(0, graph.addNode(n));
    EXPECT_EQ(1, graph.addNode(n));
    // addEdge
    graph.addEdge(e1);
    // getActiveNodesNum
    EXPECT_EQ(2, graph.getActiveNodesNum());
    // getNextFreeIndex
    EXPECT_EQ(2, graph.getNextFreeIndex());
    // getEdgesNum()
    EXPECT_EQ(1, graph.getEdgesNum());
    // isPresent
    EXPECT_TRUE(graph.isPresent(0));
    EXPECT_TRUE(graph.isPresent(1));
    // isEmpty
    EXPECT_FALSE(graph.isEmpty());
    // removeNode
    graph.removeNode(0);
    EXPECT_EQ(1, graph.getActiveNodesNum());
    EXPECT_EQ(2, graph.getNodesNum());
    EXPECT_EQ(0, graph.getEdgesNum());
    // removeEdge
    EXPECT_EQ(0, graph.addNode(n));
    EXPECT_EQ(2, graph.addNode(n));
    graph.addEdge(e1);
}

TEST(graph, edge_iterator)
{
    SparseGraph<GraphNode, GraphEdge> graph;

    GraphNode n;
    GraphEdge e1(0, 1);
    GraphEdge e2(0, 2);
    EXPECT_EQ(0, graph.addNode(n));
    EXPECT_EQ(1, graph.addNode(n));
    EXPECT_EQ(2, graph.addNode(n));
    graph.addEdge(e1);
    graph.addEdge(e2);

    SparseGraph<GraphNode, GraphEdge>::EdgeIterator iter(graph, 0);
    //
    int i = 0;
    for (GraphEdge *e = iter.begin(); !iter.end(); e = iter.next(), ++i) {
        if (i == 0) {
            EXPECT_EQ(e->getTo(), 2);
        } else if (i == 1) {
            EXPECT_EQ(e->getTo(), 1);
        }
    }
    EXPECT_EQ(i, 2);
}

TEST(graph, dfs)
{
    SparseGraph<GraphNode, GraphEdge> graph;
    GraphNode n;
    GraphEdge e1(0, 1);
    GraphEdge e2(0, 2);
    GraphEdge e3(1, 3);
    GraphEdge e5(3, 4);
    GraphEdge e4(3, 2);

    ASSERT_EQ(0, graph.addNode(n));
    ASSERT_EQ(1, graph.addNode(n));
    ASSERT_EQ(2, graph.addNode(n));
    ASSERT_EQ(3, graph.addNode(n));
    ASSERT_EQ(4, graph.addNode(n));

    graph.addEdge(e1);
    graph.addEdge(e2);
    graph.addEdge(e3);
    graph.addEdge(e5);
    graph.addEdge(e4);

    ASSERT_EQ(graph.getEdgesNum(), 5);
    ASSERT_EQ(5, graph.getActiveNodesNum());

    GraphDFS<SparseGraph<GraphNode, GraphEdge> > dfs(graph, 0, 2);
    EXPECT_TRUE(dfs.isFound());
    EXPECT_STREQ(dfs.debugRoute().data(), "2, 3, 1, 0");
}

int main(int argc, char *argv[])
{
    ::testing::InitGoogleTest(&argc, argv);
    return RUN_ALL_TESTS();
}


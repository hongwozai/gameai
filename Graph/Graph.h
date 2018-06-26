/*************************************************
 ** Copyright(c) 2018, luzeya
 ** All rights reserved
 **
 ** 文件名：Graph.h
 ** 创建人：zeya
 ** 创建日期： 2018-06-23
 **
 ** 描  述：图的实现
 ** 注  意：
 **************************************************/
#ifndef GRAPH_H
#define GRAPH_H

#include <list>
#include <string>
#include <vector>

class GraphNode
{
public:

    typedef int IndexType;

    enum {
        INVALID_INDEX = -1,
    };

public:

    GraphNode() : index(INVALID_INDEX) {}

    ~GraphNode() {}

    void setIndex(IndexType i) { this->index = i; }

    IndexType getIndex() const { return index; }

private:

    IndexType index;
};

class GraphEdge
{
public:

    typedef int   IndexType;
    typedef double CostType;

public:

    GraphEdge(IndexType from,
              IndexType to,
              CostType weight)
        : from(from),
          to(to),
          weight(weight) {}

    GraphEdge(IndexType from, IndexType to)
        : from(from),
          to (to),
          weight(1) {}

    GraphEdge()
        : from(GraphNode::INVALID_INDEX),
          to(GraphNode::INVALID_INDEX),
          weight(0) {}

    void setFrom(IndexType i) { this->from = i; }

    void setTo(IndexType i) { this->to = i; }

    void setWeight(CostType c) { this->weight = c; }

    IndexType getFrom() const { return this->from; }

    IndexType getTo() const { return this->to; }

    CostType getWeight() const { return this->weight; }

private:

    IndexType from;
    IndexType to;
    CostType  weight;
};

template <class GraphNode, class GraphEdge>
class SparseGraph
{
public:

    typedef typename GraphNode::IndexType IndexType;
    typedef GraphNode NodeType;
    typedef GraphEdge EdgeType;

    typedef std::vector<NodeType> NodeVector;
    typedef std::list<EdgeType>   EdgeList;
    typedef std::vector<EdgeList>  AdjList;

public:

    SparseGraph(bool digraph = false)
        : digraph(digraph),
          nextIndex(0)
    {}

    const NodeType& getNode(IndexType i) const {
        return nodes[i];
    }

    const EdgeType& getEdge(IndexType from, IndexType to) const;

    // 返回下一个可用索引
    IndexType getNextFreeIndex();

    // 添加一个节点并返回其索引
    IndexType addNode(NodeType &node);

    // 通过设置节点索引为INVALID_INDEX来删除一个节点
    void removeNode(IndexType index);

    void addEdge(EdgeType &edge);

    void removeEdge(IndexType from, IndexType to);

    // 返回图中活动的和不活动的节点数
    int getNodesNum() const;
    // 返回当前图中活动的节点数
    int getActiveNodesNum() const;
    // 返回当前图中的边数
    int getEdgesNum() const;

    bool isDigraphFunc() const { return digraph; }

    // 没有节点返回true
    bool isEmpty() const;

    // 节点在图中存在返回true
    bool isPresent(IndexType index) const;

public:

    class EdgeIterator;

    friend class EdgeIterator;

private:

    // 节点集合
    NodeVector nodes;

    // 邻接表
    AdjList adjlist;

    // 是否为有向图
    bool digraph;

    // 下一个节点的索引
    IndexType nextIndex;
};

template <class GraphNode, class GraphEdge>
class SparseGraph<GraphNode, GraphEdge>::EdgeIterator
{
public:

    EdgeIterator(SparseGraph &graph, IndexType from)
        : graph(graph),
          from(from)
    {
        iter = graph.adjlist[from].begin();
    }

    EdgeType *begin() {
        return &*graph.adjlist[from].begin();
    }

    bool end() {
        return graph.adjlist[from].end() == iter;
    }

    EdgeType *next() {
        ++iter;
        return &*iter;
    }

private:

    SparseGraph &graph;
    typename std::list<EdgeType>::iterator iter;
    IndexType from;
};

template <class Graph>
class GraphDFS
{
public:

    typedef typename Graph::EdgeType Edge;
    typedef typename Graph::NodeType Node;
    typedef typename Graph::IndexType Index;

public:

    GraphDFS(Graph &graph, int source, int target = -1)
        : graph(graph),
          source(source),
          target(target),
          visited(graph.getNodesNum(), UNVISITED),
          route(graph.getNodesNum(), NO_PARENT_ASSIGNED),
          found(false)
    {
        found = search();
    }

    ~GraphDFS() {}

    bool search();

    bool isFound() const { return found; }

    std::string debugRoute();
    std::list<Index> getRoute();

private:

    enum {
        VISITED,
        UNVISITED,
        NO_PARENT_ASSIGNED = -1,
    };

private:

    Graph &graph;

    // 源与目的的索引
    Index source;
    Index target;

    // 已参观
    std::vector<int> visited;

    // 到达目标所走过的路径
    std::vector<Index> route;

    // 是否找到路径
    bool found;
};

template <class Graph>
class GraphDijkstra
{
public:

    typedef typename Graph::EdgeType Edge;
    typedef typename Graph::NodeType Node;
    typedef typename Graph::IndexType Index;

public:

    GraphDijkstra(Graph &graph, int source, int target = -1)
        : graph(graph),
          source(source),
          target(target),
          visited(graph.getNodesNum(), UNVISITED),
          route(graph.getNodesNum(), NO_PARENT_ASSIGNED),
          found(false)
    {
        found = search();
    }

    ~GraphDijkstra() {}

    bool search();

    bool isFound() const { return found; }

    std::string debugRoute();
    std::list<Index> getRoute();

private:

    enum {
        VISITED,
        UNVISITED,
        NO_PARENT_ASSIGNED = -1,
    };

private:

    Graph &graph;

    // 源与目的的索引
    Index source;
    Index target;

    // 已参观
    std::vector<int> visited;

    // 到达目标所走过的路径
    std::vector<Index> route;

    // 是否找到路径
    bool found;
};

#endif /* GRAPH_H */

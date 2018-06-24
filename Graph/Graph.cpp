#include <stack>
#include <algorithm>
#include <iostream>
#include <sstream>
#include <iterator>
#include <numeric>
#include <string>
#include "Graph.h"

template <class GraphNode, class GraphEdge>
const GraphEdge& SparseGraph<GraphNode, GraphEdge>::getEdge(
    IndexType from,
    IndexType to) const
{
    return find_if(adjlist[from].begin(), adjlist[from].end(),
                   [&to] (GraphEdge &e) {
                       return e.getTo() == to;
                   });
}

template <class GraphNode, class GraphEdge>
typename SparseGraph<GraphNode, GraphEdge>::IndexType
SparseGraph<GraphNode, GraphEdge>::getNextFreeIndex()
{
    auto it = find_if(nodes.begin(), nodes.end(),
                      [] (NodeType &n) {
                          return n.getIndex() == NodeType::INVALID_INDEX;
                      });

    if (it != nodes.end()) {
        return nextIndex++;
    }
    return it - nodes.begin();
}

template <class GraphNode, class GraphEdge>
typename SparseGraph<GraphNode, GraphEdge>::IndexType
SparseGraph<GraphNode, GraphEdge>::addNode(GraphNode &node)
{
    IndexType i = getNextFreeIndex();
    if (nodes.size() < i + 1) {
        nodes.resize(i + 1);
        adjlist.resize(i + 1);
    }
    nodes[i] = node;
    nodes[i].setIndex(i);
    adjlist[i].clear();
    return i;
}

template <class GraphNode, class GraphEdge>
void SparseGraph<GraphNode, GraphEdge>::removeNode(IndexType i)
{
    if (i >= nodes.size()) {
        return;
    }

    nodes[i].setIndex(NodeType::INVALID_INDEX);
    adjlist[i].clear();
}

template <class GraphNode, class GraphEdge>
void SparseGraph<GraphNode, GraphEdge>::addEdge(GraphEdge &edge)
{
    if (edge.getFrom() >= nodes.size() ||
        nodes[edge.getFrom()].getIndex() == NodeType::INVALID_INDEX) {
        return;
    }
    if (edge.getTo() >= nodes.size() ||
        nodes[edge.getTo()].getIndex() == NodeType::INVALID_INDEX) {
        return;
    }
    // find
    auto it = find_if(adjlist[edge.getFrom()].begin(),
                      adjlist[edge.getFrom()].end(),
                      [&edge] (GraphEdge &e) {
                          return e.getTo() == edge.getTo();
                      });
    // insert
    if (it != adjlist[edge.getFrom()].end()) {
        *it = edge;
    } else {
        adjlist[edge.getFrom()].push_front(edge);
    }
}

template <class GraphNode, class GraphEdge>
void SparseGraph<GraphNode, GraphEdge>::removeEdge(IndexType from, IndexType to)
{
    if (from >= nodes.size() ||
        nodes[from].getIndex() == GraphNode::INVALID_INDEX) {
        return;
    }
    remove_if(adjlist[from].begin(), adjlist[to].end(),
              [&to] (GraphEdge &e) {
                  return e.To() = to;
              });
}

template <class GraphNode, class GraphEdge>
int SparseGraph<GraphNode, GraphEdge>::getNodesNum() const
{
    return nodes.size();
}

template <class GraphNode, class GraphEdge>
int SparseGraph<GraphNode, GraphEdge>::getActiveNodesNum() const
{
    return count_if(nodes.begin(), nodes.end(),
                    [] (const NodeType &n) {
                        return n.getIndex() != NodeType::INVALID_INDEX;
                    });
}

template <class GraphNode, class GraphEdge>
int SparseGraph<GraphNode, GraphEdge>::getEdgesNum() const
{
    return accumulate(adjlist.begin(), adjlist.end(), 0,
                      [] (int s, std::list<EdgeType> l) -> int {
                          return s + l.size();
                      });
}

template <class GraphNode, class GraphEdge>
bool SparseGraph<GraphNode, GraphEdge>::isEmpty() const
{
    if (nodes.size() == 0) {
        return true;
    }
    return !count_if(nodes.begin(), nodes.end(),
                     [] (const NodeType &n) {
                         return n.getIndex() != NodeType::INVALID_INDEX;
                     });
}

template <class GraphNode, class GraphEdge>
bool SparseGraph<GraphNode, GraphEdge>::isPresent(IndexType index) const
{
    if (index >= nodes.size()) {
        return false;
    }

    return nodes[index].getIndex() != NodeType::INVALID_INDEX;
}

#include <iostream>

template <class Graph>
bool GraphDFS<Graph>::search()
{
    std::stack<Edge*> stack;
    Edge dummy(source, source);

    stack.push(&dummy);
    while (!stack.empty()) {
        Edge *curr = stack.top();
        stack.pop();

        // visited
        if (visited[curr->getTo()] == VISITED) {
            continue;
        }
        visited[curr->getTo()] = VISITED;

        // 记录父节点的关系，可以反向查找到路径
        route[curr->getTo()] = curr->getFrom();

        // debug
        std::cout << "visiting: " << curr->getFrom() << ":"
                  << curr->getTo() << std::endl;

        // found
        if (curr->getTo() == target) {
            // return found = true;
            found = true;

            // debug
            // copy(route.begin(), route.end(),
            //      std::ostream_iterator<int>(std::cout, " "));
            // std::cout << std::endl;
        }

        typename Graph::EdgeIterator iter(graph, curr->getTo());
        for (Edge *e = iter.begin(); !iter.end(); e = iter.next()) {
            if (visited[e->getTo()] == UNVISITED) {
                stack.push(e);
            }
        }

    }
    return found;
}

template <class Graph>
std::string GraphDFS<Graph>::debugRoute()
{
    std::ostringstream ss;
    Index from = target;

    while (from != source) {
        ss << from << ", ";
        from = route[from];
    }
    ss << source;
    return ss.str();
}

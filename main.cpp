#include <iostream>
#include <set>
#include <map>

class Graph {
public:
    Graph() {
        m_edges = 0;
        m_nodes = 0;
    }
    bool addNode(int x);
    bool deleteNode(int x);
    bool addEdge(int x, int y);
    bool deleteEdge(int x, int y);
    int getNodes();
    int getEdges();
    int getDegreeNode(int node);
    void getNeighbors(int node);
    bool testAdjacency(int x, int y);
    bool contraction(int x, int y);
    void print();

private:
    int m_edges;
    int m_nodes;
    std::map<int, std::set<int>> edges_list;
    bool checkNodes(int x, int y);
};

bool Graph::addNode(int node) {
    if (edges_list.end() != edges_list.find(node)) {
        std::cout << "Node exists!" << std::endl;
        return false;
    } 

    std::set<int> edge_list;
    edges_list[node]  = edge_list;
    m_nodes++;

    return true;
}

bool Graph::deleteNode(int node) {
    if (edges_list.end() == edges_list.find(node)) {
        std::cout << "Node doesn't exists!" << std::endl;
        return false;
    } 

    edges_list.erase(node);
    for (auto &x : edges_list) {
        if (x.second.find(node) != x.second.end()) {
            x.second.erase(node);
        }
    }
    m_nodes--;

    return true;
}

bool Graph::addEdge(int x, int y) {
    if (!checkNodes(x,y)) {
        return false;
    } 

    if (edges_list[x].end() != edges_list[x].find(y)) {
        std::cout << "Edge already here!" << std::endl;
        return false;
    }
    
    edges_list[x].insert(y);
    edges_list[y].insert(x);
    m_edges++;

    return true;
}

bool Graph::deleteEdge(int x, int y) {
    if (!checkNodes(x,y)) {
        return false;
    } 

    if (edges_list[x].end() == edges_list[x].find(y)) {
        std::cout << "Edge " <<x <<" "<<y<<" doesn't exists!" << std::endl;
        return false;
    }
    
    edges_list[x].erase(y);
    edges_list[y].erase(x);
    m_edges--;

    return true;
}

int Graph::getNodes() {
    return m_nodes;
}

int Graph::getEdges() {
    return m_edges;
}

int Graph::getDegreeNode(int node) {
    auto it = edges_list.find(node);
    if (edges_list.end() == it) {
        std::cout <<"Node " <<node << " doesn't exists!" << std::endl;
        return 0;
    }
    return it->second.size();
}

void Graph::getNeighbors(int node) {
    auto it = edges_list.find(node);
    if (edges_list.end() == it) {
        std::cout <<"Node " <<node << " doesn't exists!" << std::endl;
        return;
    }

    for (auto &x : it->second) {
        std::cout << x <<" ";
    }
    std::cout << std::endl;
}

bool Graph::testAdjacency(int x, int y) {
    if (!checkNodes(x,y)) {
        return false;
    } 

    auto it = edges_list.find(x);
    for (auto &node : it->second) {
        if (node == y) {
            std::cout << "Adjacency test passed!" << std::endl;
            return true;
        }
    }

    std::cout <<"Adjacency test failed!" << std::endl;
    return false;

}

bool Graph::contraction(int x, int y) {
    if (!checkNodes(x,y)) {
        return false;
    }

    if (!testAdjacency(x,y)) {
        return false;
    }

    auto it_one = edges_list.find(x);
    auto it_two = edges_list.find(y);
    for (auto &node : it_two->second) {
        if (it_one->second.find(node) == it_one->second.end()
            && it_one->first != node) {
            addEdge(it_one->first, node);
        }
    }
    deleteNode(y);

    return true;
}

void Graph::print() {
    if (0 == edges_list.size()) {
        std::cout << "Graph is empty!" << std::endl;
        return;
    }

    for (auto &x : edges_list) {
        std::cout << x.first <<"-->";
        for (auto &y : x.second) {
            std::cout << y <<", ";
        }
        std::cout << std::endl;
    }
    std::cout << std::endl;
}

bool Graph::checkNodes(int x, int y){
    if (edges_list.end() == edges_list.find(x) && edges_list.end() == edges_list.find(y)) {
        std::cout << "Nodes are not in graph!" << std::endl;
        return false;
    }

    if (edges_list.end() == edges_list.find(x)) {
        std::cout << "Destination node " << x << " is not here!" << std::endl;
        return false;
    }

    if (edges_list.end() == edges_list.find(y)) {
        std::cout << "Source node " << y << " is not here!" << std::endl;
        return false;
    }
    return true;
}

int main() {
    Graph graph;
    graph.addNode(0);
    graph.addNode(1);
    graph.addNode(2);
    graph.addNode(3);
    graph.addNode(4);

    graph.addEdge(0,1);
    graph.addEdge(0,4);
    graph.addEdge(1,2);
    graph.addEdge(1,3);
    graph.addEdge(1,4);
    graph.addEdge(2,3);
    graph.addEdge(3,4);

    graph.print();

    // graph.deleteNode(2);
    graph.print();

    std::cout << graph.getEdges() << std::endl;
    std::cout << graph.getDegreeNode(0) << std::endl;
    graph.getNeighbors(1);
    graph.testAdjacency(3,0);

    graph.contraction(4,1);
    graph.print();
}
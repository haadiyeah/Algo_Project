#include"MinPriorityQueue.h"
#pragma once
void dfs_visit(Graph& g, Node* vertex, int& time, Graph* forest)
{
    forest->nodes.push_back(vertex);
    time = time + 1;    // Starting time for vertex
    vertex->timeS = time;
    vertex->color = "gray"; // Mark as visited once.
    for (auto& v : vertex->edges)
    {
        for (auto& adj : g.nodes)
        {
            if (adj->nodeId == v->toNodeId) // check all edges direct outward from vertex
            {
                if (adj->color == "white")  // Check if adjacent node is unvisited
                {
                    adj->pi = vertex;
                    dfs_visit(g, adj, time, forest);
                }
            }
        }
    }
    vertex->color = "black";   //  Mark as finished
    time = time + 1;
    vertex->timeF = time;// Finishing time for Vertex
}

vector<Graph*> dfs(Graph& g)
{
    vector<Graph*> forests;

    for (auto& vertex : g.nodes)
    {
        vertex->color = "white";
        vertex->pi = nullptr;
    }
    int time = 0;
    for (auto& vertex : g.nodes)
    {
        Graph* forest = new Graph();
        if (vertex->color == "white")
        {
            dfs_visit(g, vertex, time, forest);
        }
        if (forest->nodes.size())
            forests.push_back(forest);
    }
    return forests;
}

Graph computeGTranspose(Graph g)
{
    Graph gTranspose;
    for (const auto& node : g.nodes)
    {
        Node* newNode;
        if (node->getType() == "Student")
        {
            newNode = new Student(*dynamic_cast<Student*>(node));
        }
        else if (node->getType() == "Teacher")
        {
            newNode = new Teacher(*dynamic_cast<Teacher*>(node));
        }
        else if (node->getType() == "Staff")
        {
            newNode = new Staff(*dynamic_cast<Staff*>(node));
        }

        gTranspose.nodes.push_back(newNode);
    }

    for (const auto& edge : g.edges)
    {
        Edge* newEdge;
        if (edge->getType() == "Mentor Of")
        {
            newEdge = new Mentorship(edge->fromNodeId, edge->toNodeId);
        }
        else if (edge->getType() == "Student Of")
        {
            newEdge = new StudentRelation(edge->fromNodeId, edge->toNodeId);
        }

        gTranspose.edges.push_back(newEdge);
        gTranspose.nodes[newEdge->fromNodeId - 1]->edges.push_back(newEdge);
    }

    return gTranspose;
}



bool compareFinishTimes(Node* a, Node* b) {
    return a->timeF > b->timeF;
}



//finding strongly connected components: Malaika -------> proj general idea point 2-> strong communication ties
void strongConnectedComponents(Graph& g)
{
    dfs(g);
    Graph G_Transpose = computeGTranspose(g);
    sort(G_Transpose.nodes.begin(), G_Transpose.nodes.end(), compareFinishTimes);
    vector<Graph*> forests = dfs(G_Transpose);
    for (Graph* g : forests)
    {
        cout << "DISPLAY FOREST: \n";
        g->display();
    }
}

Node* getGraphNode(Graph g, int e)
{
    for (Node* vertex : g.nodes)
    {
        if (e == vertex->nodeId)
        {
            return vertex;
        }
    }
}

//  Use a DFS approach to traverse and display MST
void MST_print(Graph g, Node* node, int& totalCost) {
    if (node == nullptr)    // Check base case
    {
        return;
    }

    node->color = "gray";
    if (node->pi)
        cout << "Node: " << node->pi->nodeId << " " << node->pi->name << " gives the message to Node: " << node->nodeId << " " << node->name << " which has cost: " << node->key << endl;
    for (auto& v : node->edges)
    {
        for (auto& adj : g.nodes)
        {
            if (adj->nodeId == v->toNodeId)
            {
                if (adj->color == "white" && adj->pi->nodeId == node->nodeId)
                {
                    MST_print(g, getGraphNode(g, v->toNodeId), totalCost);
                }
            }
        }
    }
    totalCost += node->key;
    node->color = "black";
}

int getHeapIndex(vector<Node*>heap, Node* u)    // Get node position in heap.
{
    for (int i = 0; i < heap.size(); i++)
    {
        if (heap[i]->nodeId == u->nodeId)
            return i;
    }
    return -1;
}

void MST_PRIM(Graph g, Node* root)
{

    for (Node* v : g.nodes)
    {
        v->key = INT_MAX;   // Init all node keys to int max 
        v->pi = nullptr;    // Predecessor information will be set to null initially
    }
    root->key = 0;
    vector<Node*> heap; // Minimum Priority Queue initialization
    minHeapInsert(heap, g); // Used as a Middleware function to build Minimum Priority Queue of Graph Nodes
    Node* v;
    while (HEAP_SIZE > 0)
    {
        v = extractMin(heap);   // Get Node with Minimum key. 
        Node* u = nullptr;
        for (Edge* e : v->edges)
        {   //Check distance to each Adjacent Node and check if new distance is less than Adjacent Node key
            u = getGraphNode(g, e->toNodeId);
            if (checkID(u->nodeId, heap) && e->weight < u->key)
            {
                u->pi = v;
                u->key = e->weight;
                heap_Decrease_Key(heap, getHeapIndex(heap, u), u);  // Update heap based on new key values
            }
        }
    }
    for (Node* n : g.nodes)
    {
        n->color = "white";
    }
    int totalCost = 0;
    MST_print(g, root, totalCost); //Visualize the MST
    cout << "Total cost of the above MST is: " << totalCost << endl;
}

//~~~~~~~~~~~~~CALL THIS FUNCTION IN MAIN~~~~~~~~~~~~~~~~
//Adding it as a middleware function.
//MST is not intended for directed graphs so graphs that have no edge going towards them might get missed. 
//All nodes that dont have an edge going towards them, will be considered as root atleast once.
void MST_start(Graph g)
{
    for (Node* n : g.nodes)
    {
        bool direct = false;
        for (Edge* e : g.edges)
        {
            if (e->toNodeId == n->nodeId)
            {
                direct = true;
                break;
            }
        }
        if (!direct)
        {
            MST_PRIM(g, n);
        }
    }
}
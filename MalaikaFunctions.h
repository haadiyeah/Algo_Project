#pragma once
void dfs_visit(Graph& g, Node* vertex, int& time, Graph* forest)
{
    forest->nodes.push_back(vertex);
    time = time + 1;
    vertex->timeS = time;
    vertex->color = "gray";
    for (auto& v : vertex->edges)
    {

        for (auto& adj : g.nodes)
        {
            if (adj->nodeId == v->toNodeId)
            {
                if (adj->color == "white")
                {
                    adj->pi = vertex;
                    dfs_visit(g, adj, time, forest);
                }
            }
        }
    }
    vertex->color = "black";
    time = time + 1;
    vertex->timeF = time;
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

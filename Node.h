#pragma once
class Edge;

class Node {
public:
    int nodeId;
    string name;
    string dob;
    string dept;
    vector<Edge*> edges;
    int timeF = 0;
    int timeS = 0;
    double influence;
    int key=0;
    string color = "white"; //added this cuz color is needed for dfs algorithm -malaika
    Node* pi = nullptr; //added this cuz predecessor is needed for dfs algorithm -malaika
    Node(int nodeId, const string& name, const string& dept) : nodeId(nodeId), name(name), dept(dept) {}
    Node(int nodeId) : nodeId(nodeId) {}
    virtual ~Node() {}
    virtual string getType() const = 0;//pure vitrual
};

#pragma once
#include "Node.h"

//Show all events info along with most frequent participators
void showEventParticipants(const Graph& graph, int eventId) {
    // Find the event node with the specified ID
    Event* eventNode = nullptr;
    for (const auto& node : graph.nodes) {
        if (node->getType() == "Event" && node->nodeId == eventId) {
            eventNode = dynamic_cast<Event*>(node);
            break;
        }
    }

    if (eventNode) {
        cout << "Event ID: " << eventNode->nodeId << " Event name " << eventNode->name << ", Event Hosted By: " << eventNode->hostedby << endl;

        // Map to store frequency counts for each participant
        unordered_map<int, int> participantFrequency;

        // Traverse all nodes to find edges related to the given event
        for (const auto& node : graph.nodes) {
            for (const auto& edge : node->edges) {
                if (edge->getType() == "Participates In Event") {
                    ParticipatesInEvent* participationEdge = dynamic_cast<ParticipatesInEvent*>(edge);
                    if (participationEdge->toNodeId == eventId) {
                        // Increment frequency count for the participant
                        participantFrequency[participationEdge->fromNodeId]++;
                    }
                }
            }
        }

        // Find the participant with the maximum frequency
        auto maxParticipant = max_element(participantFrequency.begin(), participantFrequency.end(),
            [](const auto& a, const auto& b) {
                return a.second < b.second;
            });

        if (maxParticipant != participantFrequency.end()) {
            cout << "Max Participant ID: " << maxParticipant->first
                << ", Frequency: " << maxParticipant->second << endl;
        }

        cout << endl;
    }
    else {
        cout << "Event not found with ID: " << eventId << endl;
    }
}

// identify most popular event
void identifyPopularEvents(Graph& g) {
    int maxAttendance = 0;
    Event* popularEvent = nullptr;

    for (auto& node : g.nodes) {
        if (node->getType() == "Event") {

            Event* eventNode = dynamic_cast<Event*>(node);
            if (eventNode->attendance > maxAttendance) {
                maxAttendance = eventNode->attendance;
                popularEvent = eventNode;
            }
        }
    }

    if (popularEvent) {
        cout << "Popular Event: " << popularEvent->name << " (ID: " << popularEvent->nodeId << ")\n";
        cout << "Attendance: " << popularEvent->attendance << "\n";
    }
    else {
        cout << "No events found.\n";
    }
}

//Calculate attendence count for every event to see which event is popular
void updateEventAttendance(Graph& g) {
    for (auto& node : g.nodes) {
        if (node->getType() == "Student" || node->getType() == "Teacher" || node->getType() == "Mentor") {
            // Traverse edges of the current individual node

            for (const auto& edge : node->edges) {
                if (edge->getType() == "Participates In Event") {
                    ParticipatesInEvent* participationEdge = dynamic_cast<ParticipatesInEvent*>(edge);
                    // Find the corresponding event node and update its attendance
                    for (auto& event : g.nodes) {
                        if (event->getType() == "Event" && event->nodeId == participationEdge->toNodeId) {

                            Event* eventNode = dynamic_cast<Event*>(event);
                            eventNode->attendance += 1;
                            cout << eventNode->attendance << endl;

                        }
                    }
                }
            }
        }
    }

    cout << "Event attendance updated.\n";
}


// Function to remove a node from the graph
//Allow for dynamic changes in the social network, such as individuals joining or
// leaving the university, to simulate the evolving nature of social connections.

void removeEdge(Graph& g, int fromNodeId, int toNodeId) {
    // Remove the edge from the edges vector
    g.edges.erase(
        remove_if(g.edges.begin(), g.edges.end(), [fromNodeId, toNodeId](Edge* edge) {
            return edge->fromNodeId == fromNodeId && edge->toNodeId == toNodeId;
            }),
        g.edges.end());

    // Remove the edge from the edges vector in the source node
    auto it = remove_if(g.nodes[fromNodeId - 1]->edges.begin(), g.nodes[fromNodeId - 1]->edges.end(),
        [toNodeId](Edge* edge) {
            return edge->toNodeId == toNodeId;
        });
    g.nodes[fromNodeId - 1]->edges.erase(it, g.nodes[fromNodeId - 1]->edges.end());

    cout << "Edge removed successfully." << endl;
}


void removeNode(Graph& g, int nodeId) {
    // Remove edges associated with the removed node
    for (auto& edge : g.nodes[nodeId - 1]->edges) {
        removeEdge(g, nodeId, edge->toNodeId);
    }

    // Remove the node from the nodes vector
    auto it = remove_if(g.nodes.begin(), g.nodes.end(), [nodeId](Node* node) {
        return node->nodeId == nodeId;
        });
    g.nodes.erase(it, g.nodes.end());

    cout << "Node and its associated edges removed successfully." << endl;
}

//calculates influence by three or four critereas
// academic impact : cgpa
// event participation
//leadership role
double calculateInfluence(Node* individual) {
    double influence = 0.0;

    // Metrics for influence calculation
    // You can adjust the weights as needed
    const double cgpaWeight = 0.3;
    const double participationWeight = 0.2;
    const double leadershipWeight = 0.3;

    if (individual->getType() == "Student") {
        influence += dynamic_cast<Student*>(individual)->cgpa * cgpaWeight;
    }
    // Additional influence based on edges participation and leadership role
    for (const auto& edge : individual->edges) {
        if (edge->getType() == "Participates In Event") {
            influence += participationWeight;
        }
        else if (edge->getType() == "Leadership Role") {
            influence += leadershipWeight;
        }
    }

    return influence;
}


//Breadth first search is applied to traverse graph and find influential people of the university
// Breadth-First Search (BFS) for Influence Analysis in a Graph

//BFS
void bfs_influence_analysis(Graph& g) {

    cout << "Influence Analysis using BFS:\n";

    // Set to keep track of visited nodes
    unordered_set<Node*> visited;

    // Iterate through each node in the graph
    for (auto& startNode : g.nodes) {
        // Check if the node has been visited
        if (visited.find(startNode) == visited.end()) {
            // Initialize a queue for BFS and enqueue the current node
            queue<Node*> bfsQueue;
            bfsQueue.push(startNode);
            // Mark the current node as visited
            visited.insert(startNode);

            // BFS traversal
            while (!bfsQueue.empty()) {
                // Dequeue the front node in the queue
                Node* currentNode = bfsQueue.front();
                bfsQueue.pop();

                // Calculate influence based on node type (Student, Teacher, etc.)
                double influence = calculateInfluence(currentNode);
                // Assign calculated influence to the current node
                currentNode->influence = influence;

                // Print the node type, name, and calculated influence
                cout << currentNode->getType() << " " << currentNode->name
                    << " - Influence: " << influence << endl;

                // Enqueue adjacent nodes that haven't been visited
                for (const auto& edge : currentNode->edges) {
                    Node* adjacentNode = nullptr;
                    // Find the adjacent node in the graph
                    for (auto& node : g.nodes) {
                        if (node->nodeId == edge->toNodeId) {
                            adjacentNode = node;
                            break;
                        }
                    }

                    // Check if the adjacent node exists and hasn't been visited
                    if (adjacentNode && visited.find(adjacentNode) == visited.end()) {
                        // Enqueue the adjacent node and mark it as visited
                        bfsQueue.push(adjacentNode);
                        visited.insert(adjacentNode);
                    }
                }
            }
        }
    }
}

// fatimas code finish//////////////////////////////////////////////////////////////////////////////s




#include<iostream>
#include<fstream>
#include<iomanip>
#include<string>
#include<limits>
#include<sstream>
#include<vector>
#include<chrono>
#include <queue>
#include<algorithm>
#include <unordered_set>
#include"json-develop/single_include/nlohmann/json.hpp"

using namespace std;
using json = nlohmann::json;

#include "Edges.h"
#include "Graph.h"
#include "Node.h"
#include "Student.h"
#include "Teacher.h"
#include "Staff.h"
#include "Event.h"
#include "MalaikaFunctions.h"
#include "FatimaFunctions.h"

#include <boost/graph/adjacency_list.hpp>


//global graph variable
Graph graph;

int main() {

    using json = nlohmann::json;
    ifstream inputFile("graph.json"); // json file
    json jsonData = json::parse(inputFile); // getting entire array of objects from file

    graph.populateFromJson(jsonData);
    graph.display();
    strongConnectedComponents(graph);

    cout << "\n\n\t\t\tWelcome to University Social Network\n\t";
    for (int i = 0; i < 15; i++)
        cout << " * ~";
    cout << endl;

    cout<<"\n\t (D) Display Graph \t\t\t (E) Add Edge \n\t (N) Add Node \t\t\t\t (A) Add Event \n\t (L) Leave University / End Event \t (I) Influence Analysis \n\t (S) Find Most Frequent Participator \t (P) See Popular Events \n\t (X) Exit \t>";
    char choice;
    cin >> choice;
    cin.ignore();
    while (choice != 'X') {
        if (choice == 'S')
        {
            int nodeId;
            cout << "Enter the id of the event you want to check frequent participators of: ";
            cin >> nodeId;
            showEventParticipants(graph, nodeId);
        }
        if (choice == 'P')
        {
            updateEventAttendance(graph);
            identifyPopularEvents(graph);
        }
        if (choice == 'L') {
            int nodeId;
            cout << "Enter the id of the node you want to remove: ";
            cin >> nodeId;
            removeNode(graph, nodeId);
        }
        if (choice == 'E') {
            cout << "Enter the type of edge you want to add (mentor/student/participates/leadership) : ";
            string edgeType;
            cin >> edgeType;
            cout << "Enter the id of the node you want to add the edge to : ";
            int toNodeId;
            cin >> toNodeId;
            cout << "Enter the id of the node you want to add the edge from : ";
            int fromNodeId;
            cin >> fromNodeId;
            Edge* edge = nullptr;

            if (edgeType == "mentor") {
                // to          // from  (directed)
                edge = new Mentorship(toNodeId, fromNodeId);
            }
            else if (edgeType == "student") {
                edge = new StudentRelation(toNodeId, fromNodeId);
            }
            else if (edgeType == "participates") {
                // Check if a "Participates In Event" edge already exists
                bool edgeExists = false;
                for (const auto& existingEdge : graph.nodes[fromNodeId - 1]->edges) {
                    if (existingEdge->getType() == "Participates In Event" && existingEdge->toNodeId == toNodeId) {
                        ParticipatesInEvent* participationEdge = dynamic_cast<ParticipatesInEvent*>(existingEdge);
                        // Increase the frequency_participation variable
                        participationEdge->frequency_participation += 1;
                        cout << participationEdge->frequency_participation;
                        edgeExists = true;
                        break;
                    }
                }

                // If the edge doesn't exist, create a new one
                if (!edgeExists) {
                    edge = new ParticipatesInEvent(toNodeId, fromNodeId);
                }
            }
            else if (edgeType == "leadership") {
                edge = new LeadershipRole(toNodeId, fromNodeId);
            }

            if (edge) {
                graph.edges.push_back(edge);
                graph.nodes[fromNodeId - 1]->edges.push_back(edge);
            }

        }
        if (choice == 'A')
        {

            string eventType;

            int nodeId = graph.nodes.size() + 1;
            cout << "Enter the event type: ";
            getline(cin, eventType);
            cout << "Enter the department which is starting this event: ";
            string dept;
            getline(cin, dept);
            cout << "Enter the NAME of the event : ";
            string name;
            getline(cin, name);

            Event* event = new Event(nodeId, name, dept, eventType);
            graph.nodes.push_back(event);
        }
        if (choice == 'N') {
            cout << "Enter the type of node you want to add (student/teacher/staff) : ";
            string nodeType;
            getline(cin, nodeType);
            int nodeId = graph.nodes.size() + 1; // new node id will be the size of the nodes vector + 1
            cout << "Enter the name of the person or event you want to add : ";
            string name;
            getline(cin, name);
            cout << "Enter the department : ";
            string dept;
            getline(cin, dept);

            Node* node = nullptr;
            if (nodeType == "student") {
                node = new Student(nodeId, name, dept);
                cout << "Enter the degree program : ";
                string degreeProgram;
                getline(cin, degreeProgram);
                cout << "Enter the batch : ";
                string batch;
                getline(cin, batch);
                cout << "Enter the roll number : ";
                string rollNumber;
                getline(cin, rollNumber);
                cout << "Enter the CGPA : ";
                string cgpaStr;
                getline(cin, cgpaStr);
                double cgpa = stod(cgpaStr);

                Student* student = dynamic_cast<Student*>(node);
                student->degreeProgram = degreeProgram;
                student->batch = batch;
                student->rollNumber = rollNumber;
                student->cgpa = cgpa;
            }
            else if (nodeType == "teacher") {
                node = new Teacher(nodeId, name, dept);
                cout << "Enter the salary : ";
                string salaryStr;
                getline(cin, salaryStr);
                cout << "Enter the position : ";
                string position;
                getline(cin, position);
                cout << "Enter the office hours : ";
                string officeHrs;
                getline(cin, officeHrs);
                double salary = stod(salaryStr);
                Teacher* teacher = dynamic_cast<Teacher*>(node);
                teacher->salary = salary;
                teacher->position = position;
                teacher->officeHrs = officeHrs;
            }
            else if (nodeType == "staff") {
                node = new Staff(nodeId, name, dept);
                cout << "Enter the working hours : ";
                string workingHrs;
                getline(cin, workingHrs);
                cout << "Enter the job title : ";
                string jobTitle;
                getline(cin, jobTitle);
                cout << "Enter the salary : ";
                string salaryStr;
                getline(cin, salaryStr);
                double salary = stod(salaryStr);

                Staff* staff = dynamic_cast<Staff*>(node);
                staff->workingHrs = workingHrs;
                staff->jobTitle = jobTitle;
                staff->salary = salary;
            }


            if (node) {
                graph.nodes.push_back(node);
            }
            else {
                cout << "Invalid option\n";
            }
        }
        else if (choice == 'D') {
            graph.display();
        }
        else if (choice == 'I') {
            bfs_influence_analysis(graph);
        }
        else {
            cout << "Invalid choice" << endl;
        }

        cout << "press E to add a new edge, N to add a new node, A for adding a new event ,\nL for Leaving university / Ending an event  ,\nD for displaying the graph , \nI for influence analysis,\nS Find most frequent Participator for and event \nP See popular events\nX to exit" << endl;

        cin >> choice;
    }



    cout << "Save changed graph to the json file? Y/N " << endl;
    char saveChoice;
    cin >> saveChoice;
    if (saveChoice == 'Y') {
        graph.saveGraphToJson(graph, "graph.json");

    }

    // free the allocated memory
    for (auto node : graph.nodes) {
        delete node;
    }

    for (auto edge : graph.edges) {
        delete edge;
    }

    return 0;
}



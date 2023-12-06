#pragma once
#include "Edges.h"
#include "Node.h" 
#include "Staff.h"
#include "Student.h"
#include "Teacher.h"
#include "Event.h"

struct Graph {
    vector<Node*> nodes;
    vector<Edge*> edges;

    void display() {
        cout << "DISPLAY: \n";
        for (const auto& node : nodes) {
            cout << node->getType() << " " << node->name << "(id : " << node->nodeId << " ) " << endl;
            for (const auto& edge : node->edges) {
                cout << "  " << edge->getType() << " " << edge->toNodeId << endl;
            }
        }
    }


    void saveGraphToJson(const Graph& g, const string& filename) {
        json graphJson;

        for (const auto& node : g.nodes) {
            json nodeJson;
            nodeJson["nodeid"] = node->nodeId;
            nodeJson["name"] = node->name;
            nodeJson["type"] = node->getType();
            nodeJson["dob"] = node->dob;
            nodeJson["dept"] = node->dept;

            if (node->getType() == "Student") {
                const auto studentNode = dynamic_cast<Student*>(node);
                nodeJson["type"] = "student";
                nodeJson["degreeProgram"] = studentNode->degreeProgram;
                nodeJson["batch"] = studentNode->batch;
                nodeJson["rollNumber"] = studentNode->rollNumber;
                nodeJson["cgpa"] = studentNode->cgpa;

            }
            else if (node->getType() == "Teacher") {
                const auto teacherNode = dynamic_cast<Teacher*>(node);
                nodeJson["type"] = "teacher";
                nodeJson["salary"] = teacherNode->salary;
                nodeJson["position"] = teacherNode->position;
                nodeJson["officeHrs"] = teacherNode->officeHrs;

            }
            else if (node->getType() == "Staff") {
                const auto staffNode = dynamic_cast<Staff*>(node);
                nodeJson["type"] = "staff";
                nodeJson["workingHrs"] = staffNode->workingHrs;
                nodeJson["jobTitle"] = staffNode->jobTitle;
                nodeJson["salary"] = staffNode->salary;

            }
            else if (node->getType() == "Event") {
                const auto eventNode = dynamic_cast<Event*>(node);
                nodeJson["type"] = "event";
                nodeJson["name"] = eventNode->name;
                nodeJson["dept"] = eventNode->hostedby;
                nodeJson["eventType"] = eventNode->eventType;

            }

            json edgesJson;
            for (const auto& edge : node->edges) {
                json edgeJson;
                edgeJson["nodeid"] = edge->toNodeId;
                edgeJson["edgeType"] = edge->getType();
                edgesJson.push_back(edgeJson);
            }

            nodeJson["edges"] = edgesJson;
            graphJson.push_back(nodeJson);
        }

        ofstream outputFile(filename);
        outputFile << setw(4) << graphJson << endl;
        cout << "Graph saved to " << filename << endl;
    }

    // function to populate graph from already existing nodes in file
    void populateFromJson(const json& jsonData) {
        for (int i = 0; i < jsonData.size(); i++) {
            int nodeId = jsonData.at(i)["nodeid"];
            string name = jsonData.at(i)["name"];
            string dept = jsonData.at(i)["dept"];
            string type = jsonData.at(i)["type"];

            if (type == "student") {
                string degreeProgram = jsonData.at(i)["degreeProgram"];
                string batch = jsonData.at(i)["batch"];
                string rollNumber = jsonData.at(i)["rollNumber"];
                double cgpa = jsonData.at(i)["cgpa"];

                Student* student = new Student(nodeId, name, dept, degreeProgram, batch, rollNumber, cgpa);
                nodes.push_back(student);
                cout << "added " << name;
            }
            else if (type == "teacher") {
                double salary = jsonData.at(i)["salary"];
                string position = jsonData.at(i)["position"];
                string officeHrs = jsonData.at(i)["officeHrs"];

                Teacher* teacher = new Teacher(nodeId, name, dept, salary, position, officeHrs);
                nodes.push_back(teacher);

            }
            else if (type == "staff") {
                string workingHrs = jsonData.at(i)["workingHrs"];
                string jobTitle = jsonData.at(i)["jobTitle"];
                double salary = jsonData.at(i)["salary"];

                Staff* staff = new Staff(nodeId, name, dept, workingHrs, jobTitle, salary);
                nodes.push_back(staff);
            }
            else if (type == "event") {
                string eventType = jsonData.at(i)["eventType"];
                string name = jsonData.at(i)["name"];
                string hostedby = jsonData.at(i)["dept"];
                Event* event = new Event(nodeId, name, hostedby, eventType);
                nodes.push_back(event);

            }
            else {
                cout << "Invalid data encountered in filereading at object " << i << endl;
                continue;
            }

            for (const auto& edgeData : jsonData.at(i)["edges"]) {
                int connectedNodeId = edgeData["nodeid"];
                string edgeType = edgeData["edgeType"];

                Edge* edge = nullptr;

                if (edgeType == "Mentor Of") {
                    // to          // from  (directed)
                    edge = new Mentorship(connectedNodeId, nodeId);
                }
                else if (edgeType == "Student Of") {
                    edge = new StudentRelation(connectedNodeId, nodeId);
                }
                else if (edgeType == "Participates In Event") {
                    edge = new ParticipatesInEvent(connectedNodeId, nodeId);
                }
                else if (edgeType == "Leadership Role") {
                    edge = new LeadershipRole(connectedNodeId, nodeId);
                }

                if (edge) {
                    edges.push_back(edge);
                    nodes[nodeId - 1]->edges.push_back(edge); // adding edge to the newly created node
                }
                else {
                    cout << "Invalid data encountered in filereading at object " << i << " while adding edge "<< endl;
                }
            }
        }
    }


};

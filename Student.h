#pragma once

// Derived classes for specific node types
class Student : public Node {
public:

    string degreeProgram;
    string batch;
    string rollNumber;
    double cgpa;

    //influence added



    void operator=(const Student& t)       // overloaded = operator for every node
    {
        this->nodeId = t.nodeId;
        this->name = t.name;
        this->dob = t.dob;
        this->dept = t.dept;
        this->timeF = t.timeF;
        this->timeS = t.timeS;
        this->degreeProgram = t.degreeProgram;
        this->batch = t.batch;
        this->rollNumber = t.rollNumber;
        this->cgpa = t.cgpa;
        this->color = t.color;
        this->pi = t.pi;
        this->edges = t.edges;
    }
    Student(int nodeId, const string& name, const string& dept, const string& degreeProgram, const string& batch, const string& rollNumber, double cgpa)
        : Node(nodeId, name, dept), degreeProgram(degreeProgram), batch(batch), rollNumber(rollNumber), cgpa(cgpa) {}

    Student(int nodeId, const string& name, const string& dept) : Node(nodeId, name, dept) {}

    string getType() const override { return "Student"; }
};

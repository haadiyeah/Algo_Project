#pragma once

class Teacher : public Node {
public:
    double salary;
    string position;
    string officeHrs;



    Teacher(int nodeId, const string& name, const string& dept) : Node(nodeId, name, dept) {}

    Teacher(int nodeId, const string& name, const string& dept, double salary, const string& position, const string& officeHrs)
        : Node(nodeId, name, dept), salary(salary), position(position), officeHrs(officeHrs) {}

    void operator=(const Teacher& t)       // overloaded = operator for every node
    {
        this->nodeId = t.nodeId;
        this->name = t.name;
        this->dob = t.dob;
        this->dept = t.dept;
        this->timeF = t.timeF;
        this->timeS = t.timeS;
        this->salary = t.salary;
        this->position = t.position;
        this->officeHrs = t.officeHrs;
        this->color = t.color;
        this->pi = t.pi;
        this->edges = t.edges;
    }

    string getType() const override { return "Teacher"; }
};

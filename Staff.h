#pragma once

class Staff : public Node {
public:
    string workingHrs;
    string jobTitle;
    double salary;
    void operator=(const Staff& t)       // overloaded = operator for every node
    {
        this->nodeId = t.nodeId;
        this->name = t.name;
        this->dob = t.dob;
        this->dept = t.dept;
        this->timeF = t.timeF;
        this->timeS = t.timeS;
        this->workingHrs = t.workingHrs;
        this->jobTitle = t.jobTitle;
        this->salary = t.salary;
        this->color = t.color;
        this->pi = t.pi;
        this->edges = t.edges;
    }
    Staff(int nodeId, const string& name, const string& dept) : Node(nodeId, name, dept) {}
    Staff(int nodeId, const string& name, const string& dept, const string& workingHrs, const string& jobTitle, double salary) : Node(nodeId, name, dept), workingHrs(workingHrs), jobTitle(jobTitle), salary(salary) {}


    string getType() const override { return "Staff"; }
};


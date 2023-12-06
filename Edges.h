#pragma once

class Edge {
public:
    int toNodeId;
    int fromNodeId;
    string edgeType;
    void operator=(const Edge& e)
    {
        this->edgeType = e.edgeType;
        this->toNodeId = e.toNodeId;
        this->fromNodeId = e.fromNodeId;
    }

    void reverseEdge()//needed for strong connection as we need G Transpose
    {

        if (this->edgeType == "Mentorship")
        {
            this->edgeType = "StudentRelation";
        }
        else if (this->edgeType == "StudentRelation")
        {
            this->edgeType = "Mentorship";
        }

        int temp = this->toNodeId;
        this->toNodeId = this->fromNodeId;
        this->fromNodeId = temp;


    }
    Edge(int toNodeId, int fromNodeId, string edgeType) : toNodeId(toNodeId), fromNodeId(fromNodeId), edgeType(edgeType) {}
    virtual ~Edge() {}

    virtual string getType() const = 0;

private:
};

class Mentorship : public Edge {
public:
    Mentorship(int toNodeId, int fromNodeId) : Edge(toNodeId, fromNodeId, "Mentorship") {}
    string getType() const override { return "Mentor Of"; }

};

class StudentRelation : public Edge {
public:
    StudentRelation(int toNodeId, int fromNodeId) : Edge(toNodeId, fromNodeId, "StudentRelation") {}
    string getType() const override { return "Student Of"; }
};

// Edge to be added between Individuals and event
class ParticipatesInEvent : public Edge {
public:
    int frequency_participation;
    ParticipatesInEvent(int toNodeId, int fromNodeId) : Edge(toNodeId, fromNodeId, "Participates In Event") {}

    string getType() const override { return "Participates In Event"; }
};

// Adding leadership role for an individual
class LeadershipRole : public Edge {
public:
    LeadershipRole(int toNodeId, int fromNodeId) : Edge(toNodeId, fromNodeId, "LeadershipRole") {}

    string getType() const override { return "Leadership Role"; }
};

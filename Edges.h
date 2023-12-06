#pragma once
#include <cstdlib>
#include <ctime>
class Edge {
public:
    int toNodeId;
    int fromNodeId;
    string edgeType;
    int weight;
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

    Mentorship(int toNodeId, int fromNodeId) : Edge(toNodeId, fromNodeId, "Mentorship") {


        // Generating random weights between 5 and 10
        int min = 5;
        int max = 10;
        weight = min + rand() % (max - min + 1);
    }
    string getType() const override { return "Mentor Of"; }

};

class StudentRelation : public Edge {
public:
    StudentRelation(int toNodeId, int fromNodeId) : Edge(toNodeId, fromNodeId, "StudentRelation") {

        // Generating random weights between 5 and 10
        int min = 5;
        int max = 10;
        weight = min + rand() % (max - min + 1);
    }
    string getType() const override { return "Student Of"; }
};


// Edge to be added between Individuals and event
class ParticipatesInEvent : public Edge {
public:
    int frequency_participation;
    ParticipatesInEvent(int toNodeId, int fromNodeId) : Edge(toNodeId, fromNodeId, "Participates In Event") {
        // Generating random weights between 5 and 10
        int min = 1;
        int max = 50;
        weight = min + rand() % (max - min + 1);
    }

    string getType() const override { return "Participates In Event"; }
};

// Adding leadership role for an individual
class LeadershipRole : public Edge {
public:
    LeadershipRole(int toNodeId, int fromNodeId) : Edge(toNodeId, fromNodeId, "LeadershipRole") {
        // Generating random weights between 5 and 10
        int min = 5;
        int max = 10;
        weight = min + rand() % (max - min + 1);
    }
    string getType() const override { return "Leadership Role"; }
};

//Edge to be added between students that are friends
class Friendship : public Edge {
public:
    Friendship(int toNodeId, int fromNodeId) : Edge(toNodeId, fromNodeId, "FriendshipBetweenStudents") {
        // Generating random weights between 1 and 4
        int min = 1;
        int max = 4;
        weight = min + rand() % (max - min + 1);
    }
    string getType() const override { return "Friend of"; }
};
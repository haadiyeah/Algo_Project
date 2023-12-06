#pragma once

// Node for Event
class Event : public Node {
public:
    string eventType;
    string name;
    string hostedby;
    int attendance = 0;

    Event(int nodeId, const string& name, const string& dept, const string& eventType)
        : Node(nodeId), eventType(eventType), name(name), hostedby(dept) {}

    string getType() const override { return "Event"; }
};

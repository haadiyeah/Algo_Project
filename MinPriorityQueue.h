#pragma once
#include <iostream>
#include <fstream>
#include<vector>
#include <string>
#include <any>
#include"Graph.h"

using namespace std;
int HEAP_SIZE = 0;

//get the parent element of index i
int parent(int i)
{
    return (i - 1) / 2;
}
//get the left child of element at index i
int left(int i)
{
    return (2 * i);
}
//get the right child of element at index i
int right(int i)
{
    return (2 * i) + 1;
}

//Maintaining min Heap property
void heapify(vector<Node*>& minHeap, int i) 
{
    int l = left(i);
    int r = right(i);
    int smallest = i;
    if (l < HEAP_SIZE && minHeap[l]->key < minHeap[smallest]->key)
    {
        smallest = l;
    }

    if (r < HEAP_SIZE && minHeap[r]->key < minHeap[smallest]->key)
    {
        smallest = r;
    }

    if (smallest != i)
    {
        swap(minHeap[i], minHeap[smallest]);
        heapify(minHeap, smallest);
    }
}

void build_Min_Heap(vector<Node*>& s)
{
    HEAP_SIZE = s.size();
    for (int i = s.size() / 2 - 1; i >= 0; i--)
    {
        heapify(s, i);
    }
}


// Increasing the priority of  key(state) in the min-heap
//Updating min heap
void heap_Decrease_Key(vector<Node*>& minHeap, int i, Node* key)
{
    if (key->key > minHeap[i]->key)
    {
        cout << "ERROR! New key is larger than the previous Key!\n";
        exit(1);
    }
    minHeap[i] = key;
    while (i > 0 && minHeap[parent(i)]->key < minHeap[i]->key)//ensures that the parent node has the highest priority
    {
        swap(minHeap[i], minHeap[parent(i)]);
        i = parent(i);
    }
}
//Inserting the state into min heap at its correct place
void min_Heap_Insert(vector<Node*>& minHeap, Node* key)
{
    HEAP_SIZE++;
    minHeap[HEAP_SIZE - 1]->key = INT_MAX;    // Set priority to a maximum value
    heap_Decrease_Key(minHeap, HEAP_SIZE - 1, key);
}
// Get the minimum element from the min-heap
Node* minimum(Node* minHeap[])
{
    return minHeap[0];
}
// Extract and return the minimum element from the min-heap
Node* extractMin(vector<Node*>& minHeap)
{
    Node* min = minHeap[0];
    minHeap[0] = minHeap[HEAP_SIZE - 1];
    HEAP_SIZE--;
    heapify(minHeap, 0);
    return min;
}

// Inserting data into minHeap
void minHeapInsert(vector<Node*>& minHeap, Graph g)
{
    for (Node* vertex : g.nodes)
    {
        minHeap.push_back(vertex);
    }
    build_Min_Heap(minHeap);
}

bool checkID(int id, vector<Node*>heap)
{
    for (Node* e : heap)
    {
        if (e->nodeId == id)
        {
            return true;
        }
    }
    return false;
}
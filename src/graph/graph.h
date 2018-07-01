#ifndef _GRAPH_H_
#define _GRAPH_H_

#include <map>
#include <unordered_map>
#include <set>
#include <vector>
#include <limits>
#include <iostream>
#include <eigen3/Eigen/Dense>

using namespace Eigen;


struct Graph
{

    static const int UnassignedId = -1;
    static const int  InvalidId = -2;

    struct Vertex;
    struct Edge;

    typedef std::set<Edge*> EdgeSet;
    typedef std::set<Vertex*> VertexSet;
    
    typedef std::unordered_map<int, Vertex*> VertexIDMap;
    typedef std::unordered_map<int, Edge*> EdgeIDMap;

    
    struct Vertex {

        Vertex(int id=InvalidId);
        Vertex(int id, Vector2f position);
        ~Vertex();

        int id() const {return _id;}
        void setId(int id) {_id=id;}

        Vector2f position() const {return _position;}

        const EdgeSet& edges() const {return _edges;}
        EdgeSet& edges() {return _edges;}

        EdgeSet enteringEdges();
        EdgeSet exitingEdges();

        protected:
            int _id;
            Vector2f _position;
            EdgeSet _edges;


    };

    struct Edge {

        Edge(Vertex* from, Vertex* to, bool undirected, int id, float cost, int capacity);
        ~Edge();

        const VertexSet vertices() const {return _vertices;}
        VertexSet vertices() {return _vertices;}

        const Vertex* from() const {return _from;}
        Vertex* from() {return _from;}
        const Vertex* to() const {return _to;}
        Vertex* to() {return _to;}

        const int id() const {return _id;}
        void setId(int id);

        const int parentId() const {return _parentId;}
        void setParentId(int id){_parentId = id;}

        const bool undirected() const {return _undirected;}
        void setUndirected(bool undirected) {_undirected = undirected;}

        const float cost() const {return _cost;}
        void setCost(float cost) {_cost = cost;}

        const int capacity() const {return _capacity;}
        void setCapacity(int capacity) {_capacity = capacity;} 

        protected: 
            VertexSet _vertices;
            int _id;
            Vertex* _from;
            Vertex* _to;
            int _parentId;

            bool _undirected;
            float  _cost;
            int _capacity;

    };

    // Constructor and destructor
    Graph();
    ~Graph();

    // Copy constructor and assignement operator
    Graph(const Graph& graph);
	Graph& operator=(const Graph& graph);

    // Returns a vertex <i>id</i> in the graph, or 0 if the vertex id is not present
    Vertex* vertex(int id);
    const Vertex* vertex(int id) const;

    // Returns an edge <i>id</i> in the graph, or 0 if the edge id is not present
    Edge* edge(int id);
    const Edge* edge(int id) const;

    // Removes a vertex from the graph. Returns true on success (vertex was present)
    bool removeVertex(Vertex* v);
    // Removes an edge from the graph. Returns true on success (edge was present)
    bool removeEdge(Edge* e);
    // Clears the graph and empties all structures.
    void clear();

    // @returns the map <i>id -> vertex</i> where the vertices are stored
    const VertexIDMap& vertices() const {return _vertices;}
    VertexIDMap& vertices() {return _vertices;}
    // @returns the map <i>id -> edge</i> where the edges are stored
    const EdgeIDMap& edges() const {return _edges;}
    EdgeIDMap& edges() {return _edges;}

    //Adds a vertex to the graph, returns a null pointer if something fails
    Graph::Vertex* addVertex(const int& id, Vector2f position = Vector2f(0.0, 0.0));

    // Adds an edge to the graph, returns a null pointer if something fails
    Graph::Edge* addEdge(Vertex* from, Vertex* to, bool undirected = false, float cost = -1, int capacity = INT_MAX);
    Graph::Edge* addEdge(int fromId, int toId, bool undirected = false, float cost = -1, int capacity = INT_MAX);

    // Detaches a vertex from all its connected edges
    bool detachVertex(Vertex* v);
        
    // Print information about all the vertices in the graph
    void printVerticesInfo();
    // Print information about all the edges in the graph
    void printEdgesInfo();

    protected:

        // Adds an edge to the graph, returns false if something fails
        bool addEdge(Edge* e);

        // Adds a vertex to the graph, returns false if something fails
        bool addVertex(Vertex* v);


        VertexIDMap _vertices;
        EdgeIDMap _edges;

        int _verticesIdCount;
        int _edgesIdCount;


};



#endif
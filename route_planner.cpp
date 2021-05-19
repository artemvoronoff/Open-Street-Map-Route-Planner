#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    // TODO 2: Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
    // Store the nodes you find in the RoutePlanner's start_node and end_node attributes.
  
  	this->start_node = &model.FindClosestNode(start_x, start_y);
  	this->end_node = &model.FindClosestNode(end_x, end_y);

}


// TODO 3: Implement the CalculateHValue method.
// Tips:
// - You can use the distance to the end_node for the h value.
// - Node objects have a distance method to determine the distance to another node.

float RoutePlanner::CalculateHValue(RouteModel::Node const *node) {
    return node->distance(*end_node);  

}


// Here we are adding all unvisted neighbors to the open list (AddNeighbors method)
// FindNeighbors method of the current_node to populate current_node vector with all the neighbors
// With each node, we set the parent, h_value, g_value
//Italso uses the CalculateHValue to get the h-Value calculation
// Here we will essentially, set visited attribute to true if we've visited it, and add the neigbor to open_list

void RoutePlanner::AddNeighbors(RouteModel::Node *current_node) {
  	current_node->FindNeighbors();
  	float current_g = current_node->g_value;
  	current_node->visted = true;
  
  
  	for (int i = 0; i < current_node->neighbors.size(); ++i) {
      
      	RouteModel::Node *neighbor = current_node->neighbors[i];
    
    	neighbor->parent = current_node;
    	neighbor->g_value = current_g + neighbor->distance(*current_node);
    	neighbor->h_value = CalculateHValue(neighbor);
    
    	open_list.push_back(neighbor);
    	neighbor->visited = true;
    
  }

}


// Sorting and returning the next node.
// Sum h value and g value and returning them sorted
// Then the one with the lowest sum, send pointer
// Then we remove that from the open_lsit
// Lastly, returning pointer

	float Compare(RouteModel::Node* a, RouteModel::Node* b) {
    	float f1 = a->g_value + a->h_value;
    	float f2 = b->g_value + b->h_value;

    	return f1 > f2;
	}	

RouteModel::Node *RoutePlanner::NextNode() {
  
  	sort(this->open_list.begin(), this->open_list.end(), Compare);
  	RouteModel::Node *next = open_list.back();
  	return next;

}


// ConstructFinalPath method to return the final path found from your A* search.
// 
// This method takes the current (final) node as an argument and iteratively follow the 
//   chain of parents of nodes until the starting node is found.
// For each node in the chain, it adds the distance from the node to its parent to the distance variable.
// The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    while(current_node->x != this->start_node->x && current_node->y != this->start_node->y){
        
        path_found.push_back(*current_node);
        distance += current_node->distance(*current_node->parent);
        current_node = current_node->parent;
    }

    path_found.push_back(*current_node);

    std::reverse(path_found.begin(), path_found.end());

    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}


// A* Search algorithm
// - Uses the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, uses the ConstructFinalPath method to return the final path that was found.
// - Final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;
  
  	this->open_list.push_back(this->start_node);

    	while(this->open_list.size() > 0) {

       	 	current_node = this->NextNode();
        	this->open_list.pop_back();

        	if (current_node->x == this->end_node->x && current_node->y == this->end_node->y) {
            	m_Model.path = ConstructFinalPath(current_node);
            	break;
        	}

        	AddNeighbors(current_node);           
    }

}

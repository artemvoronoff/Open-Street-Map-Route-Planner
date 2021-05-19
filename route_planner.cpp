#include "route_planner.h"
#include <algorithm>

RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    // Using the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
    // Storing the nodes you find in the RoutePlanner's start_node and end_node attributes.
    this->start_node = &model.FindClosestNode(start_x, start_y);
    this->end_node = &model.FindClosestNode(end_y, end_y);

}

// CalculateHValue method calculates the h value for given nodes.
// The total distance to the ending node.
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
    
    	neighbors->parent = current_node;
    	neighbors->g_value = current_g + neighbor->distance(*current_node);
    	neighbors->h_value = CalculateHValue(neighbor);
    
    	open_list.push_back(neighbor);
    	neighbor->visited = true;
    
  }

}


// TODO 5: Complete the NextNode method to sort the open list and return the next node.
// Tips:
// - Sort the open_list according to the sum of the h value and g value.
// - Create a pointer to the node in the list with the lowest sum.
// - Remove that node from the open_list.
// - Return the pointer.

RouteModel::Node *RoutePlanner::NextNode() {

}


// TODO 6: Complete the ConstructFinalPath method to return the final path found from your A* search.
// Tips:
// - This method should take the current (final) node as an argument and iteratively follow the 
//   chain of parents of nodes until the starting node is found.
// - For each node in the chain, add the distance from the node to its parent to the distance variable.
// - The returned vector should be in the correct order: the start node should be the first element
//   of the vector, the end node should be the last element.

std::vector<RouteModel::Node> RoutePlanner::ConstructFinalPath(RouteModel::Node *current_node) {
    // Create path_found vector
    distance = 0.0f;
    std::vector<RouteModel::Node> path_found;

    // TODO: Implement your solution here.

    distance *= m_Model.MetricScale(); // Multiply the distance by the scale of the map to get meters.
    return path_found;

}


// TODO 7: Write the A* Search algorithm here.
// Tips:
// - Use the AddNeighbors method to add all of the neighbors of the current node to the open_list.
// - Use the NextNode() method to sort the open_list and return the next node.
// - When the search has reached the end_node, use the ConstructFinalPath method to return the final path that was found.
// - Store the final path in the m_Model.path attribute before the method exits. This path will then be displayed on the map tile.

void RoutePlanner::AStarSearch() {
    RouteModel::Node *current_node = nullptr;

    // TODO: Implement your solution here.

}

# Open Street Map Route Planner
 Extend the IO2D map display code to use A*, in which the program will be able to find a path between two points on any "map".
 
 Motion Planning - (also known as the navigation problem), a computational problem to find a sequence of valid configurations that moves that object from the sources to the destination. Mainly this process is used in geometry, computer animation, robotics and computer games.
 
 We will be implementating an algorithm called A*Search, that's inherently similar to another potential contender: "Breadth-first search (BFS)".
 
 BFS is, "is an algorithm for traversing or searching tree or graph data structures. It starts at the tree root (or some arbitrary node of graph, sometimes referred to as a 'search key'), and explores all of the neighbor nodes at the present depth prior to moving on to the nodes at the next depth level. It uses the opposite strategy of "depth-first search", which instead explores the node branch as far as possible before forced to backtrack and expand to other nodes. 
 
             "Breadth-first search"
 
 ![alt text](https://upload.wikimedia.org/wikipedia/commons/thumb/3/33/Breadth-first-tree.svg/300px-Breadth-first-tree.svg.png)
 
 
   Order in which the ndoes are expanded
   
   
   
   The following psuedocode for the algorithm in a single simple function (Unfortunately, it cannot be done that simply).
   
SEARCH( grid, initial_point, goal_point ) :

1.) Initialize an empty list of open nodes.

2.) Initialize a starting node with the following:

       .) x and y values given by initial_point.
       .) g = 0, where g is the cost for each move.
       .)h given by the heuristic function (a function of the current coordinates and the goal).
       
3.) Add the new node to the list of open nodes.

4.) WHILE the list of open nodes is nonempty:

        .) Sort the open list by f-value
        .) Pop the optimal cell (called the current cell).
        .) Mark the cell's coordinates in the grid as part of the path.
        .) IF the current cell is the goal cell:

              .) return the grid.
        .) else, expand the search to the current node's neighbors. This includes the following steps:

              .) Check each neighbor cell in the grid to ensure that the cell is empty: it hasn't been closed and is not an obstacle.
              .) If the cell is empty, compute the cost (g value) and the heuristic, and add to the list of open nodes.
              .) Mark the cell as closed.
              
5.) If you exit the while loop because the list of open nodes is empty, you have run out of new nodes to explore and haven't found a path.


SUMMARY:

The A* algoirthm finds a path from the start node to the end of the node by checking for open neighbors of the current node, computing a heuristic for each of the neighbors, and adding those neighbors to the list of open nodes to explore next. The next node to explore is the one with the lowest total cost + heuristic (g + h). This process is repeated until the end is found, as long as there are still open nodes to explore.





PDF IMAGE:
Included in the files, is a PDF of the code structure, and simple explanations of the functions. To that image, ...
The code for the A* Search algorithm has been broken down into the following functions:

    1.) CellSort() - sorts the open list according to the sum of h + g
    2.) ExpandNeighbors() - loops through the current node's neighbors and calls appropriate functions to add neighbors to the open list
    3.) CheckValidCell() - ensures that the potential neighbor coordinates are on the grid and that the cell is open
    4.) Heuristic() - computes the distance to the goal
    5.) AddToOpen() - adds the node to the open list and marks the grid cell as closed


# OpenStreetMap Project
Three (3) Main Data Types:

[NODE](https://wiki.openstreetmap.org/wiki/Node)
      A node is one of the most basic elements in the OpenStreetMap data model. Each node indicates a single point with an identifier, latitude and longitude.
[WAY](https://wiki.openstreetmap.org/wiki/Way)
      A way is an ordered list of nodes that represent a feature in the map. This feature could be a road, or a boundary of a park, or some other feature in the map. 
[RELATION](https://wiki.openstreetmap.org/wiki/Relation)
      A relation is a data structure which documents a relationship between other data elements.
      
Mapping a large river with distinct banks on either side of the river. 
    Nodes are used to provide the coordinates of points along the banks of the river. Multiple nodes are then connected using ways; there are ways which form closed section of the river, labeled as "Areas" in the image below. These ways are then grouped together using a relation, which represents the entire river.
    ![alt text](https://video.udacity-data.com/topher/2019/August/5d51adfa_osm-river/osm-river.png)

# io2d implementation
Here you could find the implementation, and download. [here](https://github.com/cpp-io2d/P0267_RefImpl/blob/master/BUILDING.md)

Michael Kazakov's io2d demo

Central Park:
./maps -b -73.9866,40.7635,-73.9613,40.7775
![alt text](https://kazakov.life/wordpress/wp-content/uploads/2018/06/central_park.png)
Acropolis of Athens:
./maps -b 23.7125,37.9647,23.7332,37.9765
![alt text](https://kazakov.life/wordpress/wp-content/uploads/2018/06/athens_acropolis.png)
Vatican:
./maps -b 12.44609,41.897,12.46575,41.907
![alt text](https://kazakov.life/wordpress/wp-content/uploads/2018/06/vatican.png)



# Code Route Planning Project
https://github.com/udacity/CppND-Route-Planning-Project

# OSM Route Planner Code Structure

[OSM Route Planner Code Structure](https://lucid.app/publicSegments/view/ccfc56ec-8c49-4ab1-8bc5-0c0afb594aa1/image.png)

# Route Planning Starter Repo
The starter code can be found [here](https://github.com/udacity/CppND-Route-Planning-Project)
![alt text](https://github.com/udacity/CppND-Route-Planning-Project/blob/master/map.png)



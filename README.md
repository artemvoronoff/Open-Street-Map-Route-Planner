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

io2d demo [kazakov](https://kazakov.life/2018/06/07/io2d-demo-maps/)

Central Park:
./maps -b -73.9866,40.7635,-73.9613,40.7775
![alt text](https://kazakov.life/wordpress/wp-content/uploads/2018/06/central_park.png)
Acropolis of Athens:
./maps -b 23.7125,37.9647,23.7332,37.9765
![alt text](https://kazakov.life/wordpress/wp-content/uploads/2018/06/athens_acropolis.png)
Vatican:
./maps -b 12.44609,41.897,12.46575,41.907
![alt text](https://kazakov.life/wordpress/wp-content/uploads/2018/06/vatican.png)

# main.cpp
Here we input file stream and 2 options 
ios::binary uploading as binary and not any other datatype (string, etc). Plus, ios::ate which means "at the end" which means we will imeediately seek the end of the input stream. Then on like 108--we can tell the program to use is.tellg() to determine the size of the input stream, and tell it to create a vector, called contents. Then we can seekg back to the beginning of the input string (is.seekg(0)) From there read in all of the input stream into the contents. Once we are done, we will return the contents vector using std::move(contents). 
```
static std::optional<std::vector<std::byte>> ReadFile(const std::string &path)
{   
    std::ifstream is{path, std::ios::binary | std::ios::ate};
    if( !is )
        return std::nullopt;
    
    auto size = is.tellg();
    std::vector<std::byte> contents(size);    
    
    is.seekg(0);
    is.read((char*)contents.data(), size);

    if( contents.empty() )
        return std::nullopt;
    return std::move(contents);
}
```
In main, firstly we have code to parse command line arguments, there is a possible command line argument "-f" L126 Specify the osm data file that you would want to use. Otherwise, the data file will be provided in the following else statement starting on L129 which is /map.osm"

From there we a have a vector of bytes L137, which we essentially through lines 139 & 146 ReadFile function to read in the contents of the osm_data_file into the vector osm_data
```
int main(int argc, const char **argv)
{    
    std::string osm_data_file = "";
    if( argc > 1 ) {
        for( int i = 1; i < argc; ++i )
            if( std::string_view{argv[i]} == "-f" && ++i < argc )
                osm_data_file = argv[i];
    }
    else {
        std::cout << "To specify a map file use the following format: " << std::endl;
        std::cout << "Usage: [executable] [-f filename.osm]" << std::endl;
        osm_data_file = "../map.osm";
    }
    
    std::vector<std::byte> osm_data;
 
    if( osm_data.empty() && !osm_data_file.empty() ) {
        std::cout << "Reading OpenStreetMap data from the following file: " <<  osm_data_file << std::endl;
        auto data = ReadFile(osm_data_file);
        if( !data )
            std::cout << "Failed to read." << std::endl;
        else
            osm_data = std::move(*data);
    }
```
   
In the rest of the code, we create a RouteModel object (model) using the osm_data data. Then create an RoutePlanner object using, that model and the coordinates 10, 10, 90, 90; The 10, 10 are the x, y of starting value coordinates, and 90, 90 are x, y of the ending coordinates.
Afterwards, we call the AStarSearch function, and run it the coordinates, and it records the results in the RoutePlanner object. Lastly, there is a Render object created using, the model, and io2d code to display the results. 
```   
// TODO 1: Declare floats `start_x`, `start_y`, `end_x`, and `end_y` and get
    // user input for these values using std::cin. Pass the user input to the
    // RoutePlanner object below in place of 10, 10, 90, 90.

    // Build Model.
    RouteModel model{osm_data};

    // Create RoutePlanner object and perform A* search.
    RoutePlanner route_planner{model, 10, 10, 90, 90};
    route_planner.AStarSearch();

    std::cout << "Distance: " << route_planner.GetDistance() << " meters. \n";

    // Render results of search.
    Render render{model};

    auto display = io2d::output_surface{400, 400, io2d::format::argb32, io2d::scaling::none, io2d::refresh_style::fixed, 30};
    display.size_change_callback([](io2d::output_surface& surface){
        surface.dimensions(surface.display_dimensions());
    });
    display.draw_callback([&](io2d::output_surface& surface){
        render.Display(surface);
    });
    display.begin_show();
}
```


# planner.h file
Here in the RoutePlanner Class definition, starts off with the constructor, and we have a GetDistance function that returns the distance in a private variable called distance. This will help us store the complete distance from the path we choose (starting to ending). Then we have the declaration of the AStarSearch method with finally, the AddNeighbors, CalculateHValue, ConstructFinalPath, NextNode functions that will help in constructing the AStarSearch method. 
```
class RoutePlanner {
  public:
    RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y);
    // Add public variables or methods declarations here.
    float GetDistance() const {return distance;}
    void AStarSearch();

    // The following methods have been made public so we can test them individually.
    void AddNeighbors(RouteModel::Node *current_node);
    float CalculateHValue(RouteModel::Node const *node);
    std::vector<RouteModel::Node> ConstructFinalPath(RouteModel::Node *);
    RouteModel::Node *NextNode();

  private:
    // Add private variables or methods declarations here.
    std::vector<RouteModel::Node*> open_list;
    RouteModel::Node *start_node;
    RouteModel::Node *end_node;

    float distance = 0.0f;
    RouteModel &m_Model;
};
```

# route_planner.cpp file
Here we start off with multiplying them into percentages

```
RoutePlanner::RoutePlanner(RouteModel &model, float start_x, float start_y, float end_x, float end_y): m_Model(model) {
    // Convert inputs to percentage:
    start_x *= 0.01;
    start_y *= 0.01;
    end_x *= 0.01;
    end_y *= 0.01;

    // TODO 2: Use the m_Model.FindClosestNode method to find the closest nodes to the starting and ending coordinates.
    // Store the nodes you find in the RoutePlanner's start_node and end_node attributes.

}
```

# model.h file
Headerfile for the Model class, this class stores all the open-street map data, that is read into the program. Provides all of the structs for all of the objects that we may find in the open-street map data (Node, Way, Road, Railway, Multipolygon, Building, Leisure, Water, etc.).
Below that, there are getter functions that returns the vector of our street objects (Node, Way, Road, etc.) 
Lastly, we have a private variable, MetricScale, is used to convert the scale of the model, to real-life meters. When we want to compute the, the actual meters we traverse in the path (beginning to end point). 

```
class Model
{
public:
    struct Node {
        double x = 0.f;
        double y = 0.f;
    };
    
    struct Way {
        std::vector<int> nodes;
    };
    
    struct Road {
        enum Type { Invalid, Unclassified, Service, Residential,
            Tertiary, Secondary, Primary, Trunk, Motorway, Footway };
        int way;
        Type type;
    };
    
    struct Railway {
        int way;
    };    
    
    struct Multipolygon {
        std::vector<int> outer;
        std::vector<int> inner;
    };
    
    struct Building : Multipolygon {};
    
    struct Leisure : Multipolygon {};
    
    struct Water : Multipolygon {};
    
    struct Landuse : Multipolygon {
        enum Type { Invalid, Commercial, Construction, Grass, Forest, Industrial, Railway, Residential };
        Type type;
    };
    
    Model( const std::vector<std::byte> &xml );
    
    auto MetricScale() const noexcept { return m_MetricScale; }    
    
    auto &Nodes() const noexcept { return m_Nodes; }
    auto &Ways() const noexcept { return m_Ways; }
    auto &Roads() const noexcept { return m_Roads; }
    auto &Buildings() const noexcept { return m_Buildings; }
    auto &Leisures() const noexcept { return m_Leisures; }
    auto &Waters() const noexcept { return m_Waters; }
    auto &Landuses() const noexcept { return m_Landuses; }
    auto &Railways() const noexcept { return m_Railways; }
    
private:
    void AdjustCoordinates();
    void BuildRings( Multipolygon &mp );
    void LoadData(const std::vector<std::byte> &xml);
    
    std::vector<Node> m_Nodes;
    std::vector<Way> m_Ways;
    std::vector<Road> m_Roads;
    std::vector<Railway> m_Railways;
    std::vector<Building> m_Buildings;
    std::vector<Leisure> m_Leisures;
    std::vector<Water> m_Waters;
    std::vector<Landuse> m_Landuses;
    
    double m_MinLat = 0.;
    double m_MaxLat = 0.;
    double m_MinLon = 0.;
    double m_MaxLon = 0.;
    double m_MetricScale = 1.f;
};
```

# route_model.h && route_model.cpp files



# Code Route Planning Project
https://github.com/udacity/CppND-Route-Planning-Project

# OSM Route Planner Code Structure

[OSM Route Planner Code Structure](https://lucid.app/publicSegments/view/ccfc56ec-8c49-4ab1-8bc5-0c0afb594aa1/image.png)

# Route Planning Starter Repo
The starter code can be found [here](https://github.com/udacity/CppND-Route-Planning-Project)
![alt text](https://github.com/udacity/CppND-Route-Planning-Project/blob/master/map.png)



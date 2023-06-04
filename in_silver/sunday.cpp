#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <limits>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
#include <list>
#include <map>
#include <queue>
//friday oops
class Cell {
    public:
        int index;
        int cell_type;
        int resources;
        vector<int> neighbors;
        int my_ants;
        int opp_ants;
		bool beacon;

        Cell(int index, int cell_type, int resources, vector<int> neighbors, int my_ants, int opp_ants, bool beacon)
            : index(index), cell_type(cell_type), resources(resources), neighbors(neighbors),
            my_ants(my_ants), opp_ants(opp_ants), beacon(false) {}
       // ~Cell();
};

typedef struct s_data{
	int nb_cells;
	int beacons_placed;
	int nb_my_ants;
    int nb_opp_ants;
	int eggCount;
	int crystalCount;
}t_data;

vector<int> BFS_beacon(const vector<Cell>& cells, int start) {
    int nb_cells = cells.size();
    vector<bool> visited(nb_cells, false);
    vector<int> distances(nb_cells, numeric_limits<int>::max());
    vector<int> prev_node(nb_cells, -1);
    distances[start] = 0;

    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (cells[current].beacon == true) {
            vector<int> path;
            while (current != -1) {
                path.insert(path.begin(), current);
                current = prev_node[current];
            }
            
            return path;
        }

        visited[current] = true;

        for (int neighbor : cells[current].neighbors) {
            if (!visited[neighbor]) {
                int next_distance = distances[current] + 1;
                if (next_distance < distances[neighbor]) {
                    distances[neighbor] = next_distance;
                    prev_node[neighbor] = current;
                }
                q.push(neighbor);
            }
        }
    }
    return vector<int>();
}

vector<int> BFS_shortest_path(const vector<Cell>& cells, int start, int target) {
    int nb_cells = cells.size();
    vector<bool> visited(nb_cells, false);
    vector<int> distances(nb_cells, numeric_limits<int>::max());
    vector<int> prev_node(nb_cells, -1);
    distances[start] = 0;

    queue<int> q;
    q.push(start);

    while (!q.empty()) {
        int current = q.front();
        q.pop();

        if (current == target) {
            vector<int> path;
            while (current != -1) {
                path.insert(path.begin(), current);
                current = prev_node[current];
            }
            reverse(path.begin(), path.end());
            return path;
        }

        visited[current] = true;

        for (int neighbor : cells[current].neighbors) {
            if (!visited[neighbor]) {
                int next_distance = distances[current] + 1;
                if (next_distance < distances[neighbor]) {
                    distances[neighbor] = next_distance;
                    prev_node[neighbor] = current;
                }
                q.push(neighbor);
            }
        }
    }
    return vector<int>();
}

vector<vector<int>> find_all_targets(const vector<Cell>& cells, const vector<int>& from) {
    int nb_cells = cells.size();
    vector<bool> visited(nb_cells, false);
    vector<int> unvisited(nb_cells);
    for (int i = 0; i < nb_cells; ++i) {
        unvisited[i] = i;
    }
    vector<int> distances(nb_cells, numeric_limits<int>::max());
    vector<int> prev_node(nb_cells, -1);
    
    for (int start : from) {
        distances[start] = 0;
    }
    
    vector<vector<int>> all_targets;

    while (!unvisited.empty()) {
        int minDist = numeric_limits<int>::max();
        int min_i = -1;

        for (int a : unvisited) {
            if (distances[a] < minDist) {
                min_i = a;
                minDist = distances[a];
            }
        }

        int current = min_i;
        visited[current] = true;

        unvisited.erase(find(unvisited.begin(), unvisited.end(), current));

        if ((cells[current].cell_type == 1 || cells[current].cell_type == 2) && cells[current].resources > 0) {
            vector<int> shortest_path;
            int shortest_path_length = numeric_limits<int>::max();
            for (int start : from) {
                vector<int> path = BFS_shortest_path(cells, start, current);
                if (!path.empty() && path.size() < shortest_path_length) {
                    shortest_path = path;
                    shortest_path_length = path.size();
                }
            }
            if (!shortest_path.empty()) {
                all_targets.push_back(shortest_path);
            }
        }

        int next_distance = distances[current] + 1;

        for (int v : cells[current].neighbors) {
            if (!visited[v]) {
                if (distances[v] > next_distance) {
                    distances[v] = next_distance;
                    prev_node[v] = current;
                }
            }
        }
    }
    return all_targets;
}

//replace two functions :find_eggs and find_crist
vector<vector<int>> find_targets(const vector<Cell>& cells, vector<int> from, int target_type) {
    int nb_cells = cells.size();
    vector<bool> visited(nb_cells, false);
    vector<int> unvisited(nb_cells);
    for (int i = 0; i < nb_cells; ++i) {
        unvisited[i] = i;
    }
    vector<int> distances(nb_cells, numeric_limits<int>::max());
    vector<int> prev_node(nb_cells, -1);
       for (int start : from) {
        distances[start] = 0;
    }

    vector<vector<int>> all_targets;

    while (!unvisited.empty()) {
        int minDist = numeric_limits<int>::max();
        int min_i = -1;

        for (int a : unvisited) {
            if (distances[a] < minDist) {
                min_i = a;
                minDist = distances[a];
            }
        }

        int current = min_i;
        visited[current] = true;

        unvisited.erase(find(unvisited.begin(), unvisited.end(), current));

        if (cells[current].cell_type == target_type && cells[current].resources > 0) {
            vector<int> shortest_path;
            int shortest_path_length = numeric_limits<int>::max();
            for (int start : from) {
                vector<int> path = BFS_shortest_path(cells, start, current);
                if (!path.empty() && path.size() < shortest_path_length) {
                    shortest_path = path;
                    shortest_path_length = path.size();
                }
            }
            if (!shortest_path.empty()) {
                all_targets.push_back(shortest_path);
            }
        }

        int next_distance = distances[current] + 1;

        for (int v : cells[current].neighbors) {
            if (!visited[v]) {
                if (distances[v] > next_distance) {
                    distances[v] = next_distance;
                    prev_node[v] = current;
                }
            }
        }
    }

    return all_targets;
}

int countTypeCells(const std::vector<Cell>& cells, int type) {
    int count = 0;
    for (const Cell& cell : cells) {
        if (cell.cell_type == type) {
            count++;
        }
    }
    return count;
}

/* this will put the beacons on all resources nodes in a given cluster */

//void    recursivelyPlaceBeacons(const std::vector<Cell>& cells, int node_index, int beacons_placed, int nb_my_ants) {
void    recursivelyPlaceBeacons(std::vector<Cell>& cells, int node_index, string output, t_data &data) {
    if (cells[node_index].resources > 0) {
        if (!cells[node_index].beacon){
            data.beacons_placed++;
        }
        output += "BEACON " + to_string(cells[node_index].index) + " 1;";
        //cerr << "recursive beacons = " << endl;
        cells[node_index].beacon = true;
    }
    for (int neighbor : cells[node_index].neighbors) {
        if (!cells[neighbor].beacon && cells[neighbor].resources > 0) {
            recursivelyPlaceBeacons(cells, neighbor, output, data);
        }
    }
}

//void    recursivelyPlaceBeacons(std::vector<Cell>& cells, int node_index, string output);

#define DISPLAY_VECTOR 0
#define DISPLAY_COND 1
#define DISPLAY_COND1 0

int main()
{
    vector<Cell> cells;
    int number_of_cells; // amount of hexagonal cells in this map
    cin >> number_of_cells; cin.ignore();

    for (int i = 0; i < number_of_cells; i++) {
        int type; // 0 for empty, 1 for eggs, 2 for crystal
        int initial_resources; // the initial amount of eggs/crystals on this cell
        int neigh_0; // the index of the neighbouring cell for each direction
        int neigh_1;
        int neigh_2;
        int neigh_3;
        int neigh_4;
        int neigh_5;
        cin >> type >> initial_resources >> neigh_0 >> neigh_1 >> neigh_2 >> neigh_3 >> neigh_4 >> neigh_5; cin.ignore();  

        vector<int> neighbors = {neigh_0, neigh_1, neigh_2, neigh_3, neigh_4, neigh_5};
        neighbors.erase(std::remove_if(neighbors.begin(), neighbors.end(), [](int id){ return id < 0; }), neighbors.end());
        
        Cell cell(i, type, initial_resources, neighbors, 0, 0, false);
        cells.push_back(cell);
    }
    t_data data = {number_of_cells, 0, 0, 0, countTypeCells(cells, 1), countTypeCells(cells, 2)};

	// cerr << "data variables : " << endl;
	// cerr << "nb cells       : " << data.nb_cells << endl;
	// cerr << "beacons placed : " << data.beacons_placed << endl;
	// cerr << "begin crystals : " << data.crystalCount << endl;
	// cerr << "begin eggs     : " << data.eggCount << endl;
	// cerr << "my ant         : " << data.nb_my_ants << endl;
	// cerr << "opp ants       : " << data.nb_opp_ants << endl;

    int number_of_bases;
    vector<int> my_bases;
    cin >> number_of_bases; cin.ignore();
    for (int i = 0; i < number_of_bases; i++) {
        int my_base_index;
        cin >> my_base_index; cin.ignore();
        my_bases.push_back(my_base_index);
    }
    int opp_base = 0;
    vector<int> opp_bases;
    for (int i = 0; i < number_of_bases; i++) {
        int opp_base_index;
        cin >> opp_base_index; cin.ignore();
        opp_bases.push_back(opp_base_index);
    }
	
    while (1) {
        vector<vector<int>> all_res_paths = find_all_targets(cells, my_bases);
        vector<vector<int>> egg_paths = find_targets(cells, my_bases, 1);
        vector<vector<int>> crist_paths = find_targets(cells, my_bases, 2);
        t_data data = {number_of_cells, 0, 0, 0, countTypeCells(cells, 1), countTypeCells(cells, 2)};
#if DISPLAY_VECTOR
        cerr << "Egg Paths:" << endl;
        for (const auto& path : egg_paths) {
            for (const auto& cell : path) {
                cerr << cell << " ";
            }
            cerr << endl;
        }

        cerr << "Crist Paths:" << endl;
        for (const auto& path : crist_paths) {
            for (const auto& cell : path) {
                cerr << cell << " ";
            }
            cerr << endl;
        }

        cerr << "ALL resources Paths:" << endl;
        for (const auto& path : all_res_paths) {
            for (const auto& cell : path) {
                cerr << cell << " ";
            }
            cerr << endl;
        }
#endif
        for (int i = 0; i < number_of_cells; i++) {
            int resources; // the current amount of eggs/crystals on this cell
            int my_ants; // the amount of your ants on this cell
            int opp_ants; // the amount of opponent ants on this cell
            cin >> resources >> my_ants >> opp_ants;
            cin.ignore();

            cells[i].resources = resources;
            cells[i].beacon = false;
            data.nb_my_ants += my_ants;
            data.nb_opp_ants += opp_ants;
        }
        cerr << "data variables in while: " << endl;
     
        cerr << "beacons placed : " << data.beacons_placed << endl;
        cerr << "my ant         : " << data.nb_my_ants << endl;
	    cerr << "opp ants       : " << data.nb_opp_ants << endl;

         string output;
#if DISPLAY_COND1
        int stay_alive = 1;
        int it = 0;
        for (unsigned int i = 0; i < my_bases.size(); i++)
            cells[my_bases[i]].beacon = true;
         for (int j = 0; j< all_res_paths.size() && stay_alive; ++j) {
                vector<int> path = BFS_beacon(cells, all_res_paths[j][0]);
                for (int i = 0; i < path.size(); ++i) {
                //cerr << "beacon cond : " << (beacons_placed < nb_my_ants/2) << endl;
                    if (data.beacons_placed > data.nb_my_ants / 2){
                        stay_alive = 0;
                        break;
                        }
                    if(!cells[path[i]].beacon){
                            data.beacons_placed++;          
                    }
                    output += "BEACON " + to_string(all_res_paths[j][i]) + " 1;";
                            //cerr << "here beacons = " << endl; 
                    cells[path[i]].beacon = true;
                }
            }
#endif
//
#if DISPLAY_COND
        int stay_alive = 1;
        int it = 0;
        for (unsigned int i = 0; i < my_bases.size(); i++){
            cells[my_bases[i]].beacon = true;
            data.beacons_placed++;
        }

        if(data.nb_my_ants < 25 && it < 3){
            for (int j = 0; j< egg_paths.size() && stay_alive; ++j) {
                vector<int> path = BFS_beacon(cells, egg_paths[j][0]);
                for (int i = 0; i < path.size(); ++i) {
                //cerr << "beacon cond : " << (beacons_placed < nb_my_ants/2) << endl;
                    if (data.beacons_placed > data.nb_my_ants / 2){
                        stay_alive = 0;
                        break;
                        }
                    if(!cells[path[i]].beacon){
                            data.beacons_placed++;          
                    }
                    output += "BEACON " + to_string(egg_paths[j][i]) + " 1;";
                            //cerr << "here beacons = " << endl; 
                    cells[path[i]].beacon = true;
                }
            }
            ++it;
        }
        else{
            for (int j = 0; j< all_res_paths.size() && stay_alive; ++j) {
                vector<int> path = BFS_beacon(cells, all_res_paths[j][0]);
                for (int i = 0; i < path.size(); ++i) {
                //cerr << "beacon cond : " << (beacons_placed < nb_my_ants/2) << endl;
                    if (data.beacons_placed > data.nb_my_ants / 2){
                        stay_alive = 0;
                        break;
                        }
                    if(!cells[path[i]].beacon){
                            data.beacons_placed++;          
                    }
                    output += "BEACON " + to_string(all_res_paths[j][i]) + " 1;";
                            //cerr << "here beacons = " << endl; 
                    cells[path[i]].beacon = true;
                }
            }
        }
#endif

        cerr << "beacon places after : " << data.beacons_placed << endl;

   //   Output the beacons or other instructions
        if (!output.empty()) {
        	output.pop_back(); // Remove the trailing semicolon
        } else {
        	output = "WAIT";
        }

        cout << output << endl;
        }
}


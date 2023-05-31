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

vector<vector<int>> find_targets(const vector<Cell>& cells, const vector<int>& from, int target_type) {
    int nb_cells = cells.size();
    vector<bool> visited(nb_cells, false);
    vector<int> unvisited(nb_cells);
    for (int i = 0; i < nb_cells; ++i) {
        unvisited[i] = i;
    }
    vector<int> distances(nb_cells, numeric_limits<int>::max());
    vector<int> prev_node(nb_cells, -1);
    
    vector<vector<int>> all_targets;

    for (int start : from) {
        distances[start] = 0;
    }

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
            vector<int> path = BFS_shortest_path(cells, from[0], current);
            if (!path.empty()) {
                all_targets.push_back(path);
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

vector<vector<int>> find_targets(const vector<Cell>& cells, const vector<int>& from) {
    int nb_cells = cells.size();
    vector<bool> visited(nb_cells, false);
    vector<int> unvisited(nb_cells);
    for (int i = 0; i < nb_cells; ++i) {
        unvisited[i] = i;
    }
    vector<int> distances(nb_cells, numeric_limits<int>::max());
    vector<int> prev_node(nb_cells, -1);
    
    vector<vector<int>> all_targets;

    for (int start : from) {
        distances[start] = 0;
    }

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
            vector<int> path;
            for (int start : from) {
                vector<int> temp_path = BFS_shortest_path(cells, start, current);
                if (!temp_path.empty()) {
                    path = temp_path;
                    break;
                }
            }
            if (!path.empty()) {
                all_targets.push_back(path);
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
    vector<vector<int>> all_res_paths = find_targets(cells, my_bases);
    vector<vector<int>> egg_paths = find_targets(cells, my_bases, 1);
    vector<vector<int>> crist_paths = find_targets(cells, my_bases, 2);

    // cerr << "Egg Paths:" << endl;
    // for (const auto& path : egg_paths) {
    //     for (const auto& cell : path) {
    //         cerr << cell << " ";
    //     }
    //     cerr << endl;
    // }

    // cerr << "Crist Paths:" << endl;
    // for (const auto& path : crist_paths) {
    //     for (const auto& cell : path) {
    //         cerr << cell << " ";
    //     }
    //     cerr << endl;
    // }

    // cerr << "ALL resources Paths:" << endl;
    // for (const auto& path : all_res_paths) {
    //     for (const auto& cell : path) {
    //         cerr << cell << " ";
    //     }
    //     cerr << endl;
    // }

    int nb_my_ants = 0;
    int nb_opp_ants = 0;

    for (int i = 0; i < number_of_cells; i++) {
        int resources; // the current amount of eggs/crystals on this cell
        int my_ants; // the amount of your ants on this cell
        int opp_ants; // the amount of opponent ants on this cell
        cin >> resources >> my_ants >> opp_ants;
        cin.ignore();

        cells[i].resources = resources;
        nb_my_ants += my_ants;
        nb_opp_ants += opp_ants;
        cells[i].beacon = false;
    }
    //cerr << "my ants : " << nb_my_ants<< endl;
    Cell& base_cell = cells[my_bases[0]];
    vector<int> neighbor_indices;
    for (int neighbor_index : base_cell.neighbors) {
        neighbor_indices.push_back(neighbor_index);
    }

    int str_egg = 0;
    int str_crist = 0;
    int str = 1;

    string output;

    // Collecting eggs
    int beacons_placed = 0;
    //cerr << "beacon places before : " << beacons_placed << endl;
    int count = 1;
    // for (const auto& path : all_res_paths) {
    for (const auto& path : egg_paths) {
        //cerr << "beacon cond : " << (beacons_placed < nb_my_ants/2) << endl;
        if (beacons_placed < nb_my_ants / 2){
            for (int i = 0; i < path.size(); ++i) {
                if(!cells[i].beacon){
                    beacons_placed++;        
                }
                output += "BEACON " + to_string(path[i]) + " 1;";
                cells[i].beacon = true;
            }
        }
        count++;
        if (count > 2)
            break ;
    }
    //for (const auto& path : all_res_paths) {
    for (const auto& path : crist_paths) {
       // cerr << "beacon cond : " << (beacons_placed < nb_my_ants/2) << endl;
        if (beacons_placed < nb_my_ants / 2){
            for (int i = 0; i < path.size(); ++i) {
                if(!cells[i].beacon){
                    beacons_placed++;        
                }
                output += "BEACON " + to_string(path[i]) + " 1;";
                cells[i].beacon = true;
            }
        }
    }
    //Collecting eggs and crystals
    // for (int iteration = 0; iteration < 3; ++iteration) {
    //     vector<vector<int>> targets;
    //     if (iteration == 0) {
    //         targets = egg_paths; // Collect eggs
    //     } else {
    //         targets = all_res_paths; // Collect both eggs and crystals
    //     }

    //     for (const auto& path : targets) {
    //         if (beacons_placed < nb_my_ants / 2){
    //             for (int i = 1; i < path.size(); ++i) {
    //                                 if(!cells[i].beacon){
    //                 beacons_placed++;        
    //             }
    //                 if (cells[path[i]].cell_type == 2) {
    //                     output += "BEACON " + to_string(path[i - 1]) + " 1;";
    //                     cells[i].beacon = true;
    //                 } else if (cells[path[i]].cell_type == 1) {
    //                     output += "BEACON " + to_string(path[i - 1]) + " 1;";
    //                     cells[i].beacon = true;
    //                 }
    //             }
    //         }
    //     }
    // }
    //cerr << "beacon places after : " << beacons_placed << endl;

        // Output the beacons or other instructions
        if (!output.empty()) {
            output.pop_back(); // Remove the trailing semicolon
        } else {
            output = "WAIT";
        }

        cout << output << endl;
    }
}

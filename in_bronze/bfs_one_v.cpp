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

//return all the sources in one vector
vector<vector<int>> find_targets(const vector<Cell>& cells, int from) {
    int nb_cells = cells.size();
    vector<bool> visited(nb_cells, false);
    vector<int> unvisited(nb_cells);
    for (int i = 0; i < nb_cells; ++i) {
        unvisited[i] = i;
    }
    vector<int> distances(nb_cells, numeric_limits<int>::max());
    vector<int> prev_node(nb_cells, -1);
    distances[from] = 0;

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

        if (cells[current].cell_type == 1 || cells[current].cell_type == 2) {
            vector<int> path = BFS_shortest_path(cells, from, current);
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

//replace two functions :find_eggs and find_crist
vector<vector<int>> find_targets(const vector<Cell>& cells, int from, int target_type) {
    int nb_cells = cells.size();
    vector<bool> visited(nb_cells, false);
    vector<int> unvisited(nb_cells);
    for (int i = 0; i < nb_cells; ++i) {
        unvisited[i] = i;
    }
    vector<int> distances(nb_cells, numeric_limits<int>::max());
    vector<int> prev_node(nb_cells, -1);
    distances[from] = 0;

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

        if (cells[current].cell_type == target_type) {
            vector<int> path = BFS_shortest_path(cells, from, current);
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
	int total_b;
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
    int my_base = 0;
    cin >> number_of_bases; cin.ignore();
    for (int i = 0; i < number_of_bases; i++) {
        int my_base_index;
        cin >> my_base_index; cin.ignore();
        my_base = my_base_index;
    }
    int opp_base = 0;
    for (int i = 0; i < number_of_bases; i++) {
        int opp_base_index;
        cin >> opp_base_index; cin.ignore();
        opp_base = opp_base_index;
    }

    while (1) {
        
		vector<vector<int>> all_res_paths = find_targets(cells, my_base);
		// cerr << "ALL resources Paths:" << endl;
		// for (const auto& path : all_res_paths) {
		// 	for (const auto& cell : path) {
		// 		cerr << cell << " ";
		// 	}
		// 	cerr << endl;
		// }

		vector<vector<int>> egg_paths = find_targets(cells, my_base, 1);
		// cerr << "Egg Paths:" << endl;
		// for (const auto& path : egg_paths) {
		// 	for (const auto& cell : path) {
		// 		cerr << cell << " ";
		// 	}
		// 	cerr << endl;
		// }

		vector<vector<int>> crist_paths = find_targets(cells, my_base, 2);
		// cerr << "Crist Paths:" << endl;
		// for (const auto& path : crist_paths) {
		// 	for (const auto& cell : path) {
		// 		cerr << cell << " ";
		// 	}
		// 	cerr << endl;
		// }

        int nb_my_ants = 0;
        int nb_opp_ants = 0;

        for (int i = 0; i < number_of_cells; i++) {
            int resources; // the current amount of eggs/crystals on this cell
            int my_ants; // the amount of your ants on this cell
            int opp_ants; // the amount of opponent ants on this cell
            cin >> resources >> my_ants >> opp_ants; cin.ignore();

			//cerr << "resources : " << resources << endl;

            cells[i].resources = resources;
            nb_my_ants += my_ants;
            nb_opp_ants += opp_ants;
        }	

		Cell& base_cell = cells[my_base];
		vector<int> neighbor_indices;
		for (int neighbor_index : base_cell.neighbors) {
			neighbor_indices.push_back(neighbor_index);
		}

		//cerr << "Indices of neighbors of my_base: ";
		//for (int neighbor_index : neighbor_indices) {
		//	cerr << neighbor_index << " ";
		//}
		//cerr << endl;

		int str_egg = 0; 
		int str_crist = 0;

		if (nb_my_ants < 25) {
			int type2 = 0;
			for (int neighbor_index : cells[my_base].neighbors) {
				if (cells[neighbor_index].cell_type == 2) {
					type2++;
				}
			}
			if (type2 > 0) {
				str_egg = 3;
				str_crist = 1;
			} else {
				str_egg = 3;
				str_crist = 0;
			}
		} else {
			str_egg = 3;
			str_crist = 4;
		}
		
 		string output;
		
		// for (const auto& path : all_res_paths) {
		// 	// int t_size = 0;
		// 	// t_size += path.size();
		// 	// if(t_size > nb_my_ants/2)
		// 	// 	break ;
		// 	for (int i = 1; i < path.size(); ++i) {
		// 		output += "LINE " + to_string(path[i - 1]) + " " + to_string(path[i]) + " " + to_string(1) + ";";
		// 	}
		// }

		if (str_crist > 0) {
			for (const auto& path : crist_paths) {
				for (int i = 1; i < path.size(); ++i) {
					output += "LINE " + to_string(path[i - 1]) + " " + to_string(path[i]) + " " + to_string(str_crist) + ";";
				}
			}
		}

		// if (str_egg > 0) {
		// 	for (const auto& path : egg_paths) {
		// 		for (int i = 0; i < path.size(); ++i) {
		// 			output += "BEACON " + to_string(path[i]) + " " + to_string(str_egg) + ";";
		// 		}
		// 	}
		// }

		if (str_egg > 0) {
			for (const auto& path : egg_paths) {
				for (int i = 1; i < path.size(); ++i) {
					output += "LINE " + to_string(path[i - 1]) + " " + to_string(path[i]) + " " + to_string(str_crist) + ";";
				}
			}
		}

		cout << output;
		//cout << "WAIT";
        cout << endl;

        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        // WAIT | LINE <sourceIdx> <targetIdx> <strength> | BEACON <cellIdx> <strength> | MESSAGE <text>
    }
}
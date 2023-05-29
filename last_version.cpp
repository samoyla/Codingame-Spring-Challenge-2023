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

class Cell {
    public:
        int index;
        int cell_type;
        int resources;
        vector<int> neighbors;
        int my_ants;
        int opp_ants;


        Cell(int index, int cell_type, int resources, vector<int> neighbors, int my_ants, int opp_ants)
            : index(index), cell_type(cell_type), resources(resources), neighbors(neighbors),
            my_ants(my_ants), opp_ants(opp_ants) {}
       // ~Cell();
};

vector<int> BFS_dist(vector<Cell> &cells,int from, int to){
	int nb_cells = cells.size();
	vector <bool> visited;
	visited.resize(nb_cells, false);

	vector<int> unvisited(nb_cells);
	for(int i = 0; i < nb_cells; ++i){
		unvisited[i] = i;
	}

	vector<int> distances(nb_cells, numeric_limits<int>::max());
	vector<int> prev_node(nb_cells, -1);
	distances[from] = 0;

	while(!unvisited.empty()){
		//shortest unvisited distance
		int minDist = numeric_limits<int>::max();
		int min_i = -1;
	
		for(vector<int>::iterator it = unvisited.begin(); it != unvisited.end(); ++it){
			int c = *it;
			if(distances[c] < minDist){
				min_i = c;
				minDist = distances[c];
			}
		}

		int current = min_i;
		visited[current] = true;

		if(current == to)
			break;//we are in the right place

		unvisited.erase(find(unvisited.begin(), unvisited.end(), current));

		int next_distance = distances[current] + 1;

		for(vector<int>::iterator it = cells[current].neighbors.begin(); it != cells[current].neighbors.end(); ++it){
			int v = *it;
			if(!visited[v]){
				if (distances[v] > next_distance){
					distances[v] = next_distance;
					prev_node[v] = current;
				}
			}
		}
	}
	vector<int> paths;
	paths.push_back(to);
	int curr= prev_node[to];
	while(curr != -1){
		paths.push_back(curr);
		curr = prev_node[curr];
	}

	reverse(paths.begin(), paths.end());

	return paths;
}

vector<int> find_eggs(vector<Cell> &cells, int from){
	int nb_cells = cells.size();
	vector <bool> visited;
	visited.resize(nb_cells, false);

	vector<int> unvisited(nb_cells);
	for(int i = 0; i < nb_cells; ++i){
		unvisited[i] = i;
	}

	vector<int> distances(nb_cells, numeric_limits<int>::max());
	vector<int> prev_node(nb_cells, -1);
	distances[from] = 0;

	vector<int> eggs;

	while(!unvisited.empty()){
		//shortest unvisited distance
		int minDist = numeric_limits<int>::max();
		int min_i = -1;
	
		for(vector<int>::iterator it = unvisited.begin(); it != unvisited.end(); ++it){
			int a = *it;
			if(distances[a] < minDist){
				min_i = a;
				minDist = distances[a];
			}
		}
		if (min_i < 0){
			cerr<< "ERR" << min_i << endl;
			break;
		}

		int current = min_i;
		visited[current] = true;

		if(cells[current].cell_type == 1)
			eggs.push_back(current);
		
		unvisited.erase(find(unvisited.begin(), unvisited.end(), current));

		int next_distance = distances[current] + 1;

		for(vector<int>::iterator it = cells[current].neighbors.begin(); it != cells[current].neighbors.end(); ++it){
			int b = *it;
			if(!visited[b]){
				if (distances[b] > next_distance){
					distances[b] = next_distance;
				}
			}
		}
	}
	return eggs;
}
	
vector<int> find_crist(vector<Cell> &cells, int from){
	int nb_cells = cells.size();
	vector <bool> visited;
	visited.resize(nb_cells, false);

	vector<int> unvisited(nb_cells);
	for(int i = 0; i < nb_cells; ++i){
		unvisited[i] = i;
	}

	vector<int> distances(nb_cells, numeric_limits<int>::max());
	vector<int> prev_node(nb_cells, -1);
	distances[from] = 0;

	vector<int> crist;

	while(!unvisited.empty()){
		//shortest unvisited distance
		int minDist = numeric_limits<int>::max();
		int min_i = -1;
	
		for(vector<int>::iterator it = unvisited.begin(); it != unvisited.end(); ++it){
			int a = *it;
			if(distances[a] < minDist){
				min_i = a;
				minDist = distances[a];
			}
		}
		if (min_i < 0){
			cerr<< "ERR" << min_i << endl;
			break;
		}

		int current = min_i;
		visited[current] = true;

		if(cells[current].cell_type == 2)
			crist.push_back(current);
		
		unvisited.erase(find(unvisited.begin(), unvisited.end(), current));

		int next_distance = distances[current] + 1;

		for(vector<int>::iterator it = cells[current].neighbors.begin(); it != cells[current].neighbors.end(); ++it){
			int b = *it;
			if(!visited[b]){
				if (distances[b] > next_distance){
					distances[b] = next_distance;
				}
			}
		}
	}
	return crist;
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
        
        Cell cell(i, type, initial_resources, neighbors, 0, 0);
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
        
        vector<int> eggs = find_eggs(cells, my_base);
		// for (std::vector<int>::iterator it = eggs.begin(); it != eggs.end(); ++it)
        // 	std::cerr << *it << " ";
    	// std::cerr << std::endl;
    
        vector<int> crist = find_crist(cells, my_base);
		// for (std::vector<int>::iterator it = crist.begin(); it != crist.end(); ++it)
        // 	std::cerr << *it << " ";
    	// std::cerr << std::endl;

		// vector<int> paths = BFS_dist(cells, my_base, opp_base);
		
		// for (std::vector<int>::iterator it = paths.begin(); it != paths.end(); ++it)
		// 	std::cerr << *it << " ";
		// std::cerr << std::endl;

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

            // if(cells[i].cell_type == 1 && resources > 0)
            //     eggs.push_back(cells[i].index);

            // if(cells[i].cell_type == 2 && resources > 0)
            //     crist.push_back(cells[i].index);
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

        if (nb_my_ants < 25) 
		{
			//bool Type2 = false;
			//for (int neighbor_index : cells[my_base].neighbors) {
				//if (cells[neighbor_index].cell_type == 2) {
					//Type2 = true;
					//break;
				//}
			//}
			//if (Type2) {
				//str_egg = 3;
				//str_crist = 1;
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
		}
        else if(nb_opp_ants - nb_my_ants > 5)
        {
            str_egg = 3;
            str_crist = 2;
        }
        else
        {
            str_egg = 1;
            str_crist = 4;
        }
        string output;
		
        if(str_egg > 0)
        {
            for(int i = 0; i != eggs.size(); ++i)
                output += "LINE " + to_string(my_base) + " " + to_string(eggs[i]) + " " + to_string(str_egg) + ";"; 
        }
        if(str_crist > 0)
        {
            for(int i = 0; i != crist.size(); ++i)
                output += "LINE " + to_string(my_base) + " " + to_string(crist[i]) + " " + to_string(str_crist) + ";"; 
        }

        cout << output;
		//cout << "WAIT";
        cout << endl;
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        // WAIT | LINE <sourceIdx> <targetIdx> <strength> | BEACON <cellIdx> <strength> | MESSAGE <text>
    }
}

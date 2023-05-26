#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

/**
 * Auto-generated code below aims at helping you parse
 * the standard input according to the problem statement.
 **/
#include <vector>
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

int main()
{
    vector<Cell> cells;
    int number_of_cells; // amount of hexagonal cells in this map
    cin >> number_of_cells; cin.ignore();
    int cr = -1;
    int rc = -1;
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
        if (type == 2 && initial_resources > cr)
            rc = i;
        vector<int> neighbors = {neigh_0, neigh_1, neigh_2, neigh_3, neigh_4, neigh_5};
        neighbors.erase(std::remove_if(neighbors.begin(), neighbors.end(), [](int id){ return id < 0; }), neighbors.end());
        
        Cell cell(i, type, initial_resources, neighbors, 0, 0);
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
    vector<int> opp_bases;
    for (int i = 0; i < number_of_bases; i++) {
        int opp_base_index;
        cin >> opp_base_index; cin.ignore();
        opp_bases.push_back(opp_base_index);
    }

    // game loop
    while (1) {
        for (int i = 0; i < number_of_cells; i++) {
            int resources; // the current amount of eggs/crystals on this cell
            int my_ants; // the amount of your ants on this cell
            int opp_ants; // the amount of opponent ants on this cell
            cin >> resources >> my_ants >> opp_ants; cin.ignore();

            cells[i].resources = resources;
            cells[i].my_ants = my_ants;
            cells[i].opp_ants = opp_ants;
        }
        
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;
        
        for(int i = 0; i != cells.size(); ++i){
            if (cells[i].cell_type == 2)
                cout << "LINE " <<  my_bases[0] << " " << cells[i].index  << " " << 1 << ";" ;
        }
        cout << endl;

        //std::cout << "LINE " <<  my_bases[0] << " " <<  rc << " " << 1;
        //cout << endl;

        // WAIT | LINE <sourceIdx> <targetIdx> <strength> | BEACON <cellIdx> <strength> | MESSAGE <text>
        //cout << "WAIT" << endl;
    }

}

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
    int my_bases = 0;
    cin >> number_of_bases; cin.ignore();
    for (int i = 0; i < number_of_bases; i++) {
        int my_base_index;
        cin >> my_base_index; cin.ignore();
        my_bases = my_base_index;
    }
    int opp_bases = 0;
    for (int i = 0; i < number_of_bases; i++) {
        int opp_base_index;
        cin >> opp_base_index; cin.ignore();
        opp_bases = opp_base_index;
    }
    
    // game loop
    while (1) {
        
        vector<int> eggs;
        // for(int i =0; i != number_of_cells; ++i ){
        //     if(cells[i].cell_type == 1)
        //         eggs.push_back(cells[i].index);
        // }
    
        vector<int> crist;
        // for(int i = 0; i != number_of_cells; ++i){
        //     if(cells[i].cell_type == 2)
        //         crist.push_back(cells[i].index);
        // }

        int nb_my_ants = 0;
        int nb_opp_ants = 0;
        for (int i = 0; i < number_of_cells; i++) {
            int resources; // the current amount of eggs/crystals on this cell
            int my_ants; // the amount of your ants on this cell
            int opp_ants; // the amount of opponent ants on this cell
            cin >> resources >> my_ants >> opp_ants; cin.ignore();

            cells[i].resources = resources;
            nb_my_ants += my_ants;
            nb_opp_ants += opp_ants;

            if(cells[i].cell_type == 1 && resources > 0)
                eggs.push_back(cells[i].index);

            if(cells[i].cell_type == 2 && resources > 0)
                crist.push_back(cells[i].index);
        }
        
        int str_egg = 0; 
        int str_crist = 0;
        if(nb_my_ants < 25)
        {
            str_egg = 3;
            str_crist = 0;
        }
        else if(nb_opp_ants - nb_my_ants > 5)
        {
            str_egg = 2;
            str_crist = 1;
        }
        else
        {
            str_egg = 3;
            str_crist = 1;
        }
        string output;
        if(str_egg > 0)
        {
            for(int i = 0; i != eggs.size(); ++i)
                output = "LINE " + to_string(my_bases) + " " + to_string(eggs[i]) + " " + to_string(str_egg); 
        }
        if(str_crist > 0)
        {
            for(int i = 0; i != crist.size(); ++i)
                output = "LINE " + to_string(my_bases) + " " + to_string(crist[i]) + " " + to_string(str_crist); 
        }
        cout << output;
        cout << endl;
        // Write an action using cout. DON'T FORGET THE "<< endl"
        // To debug: cerr << "Debug messages..." << endl;

        // WAIT | LINE <sourceIdx> <targetIdx> <strength> | BEACON <cellIdx> <strength> | MESSAGE <text>
    }
}
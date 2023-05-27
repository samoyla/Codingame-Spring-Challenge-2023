#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

struct Cell {
    int index;
    std::vector<int> neighbors;
    int type;
    int res;

    Cell(int _index, const std::vector<int>& _neighbors, int _type, int _res)
        : index(_index), neighbors(_neighbors), type(_type), res(_res) {}
};

std::vector<int> shortest_path(const std::vector<Cell>& cells, int start, int goal) {
    int n_cells = cells.size();
    std::vector<bool> visited(n_cells, false);
    std::vector<int> unvisited(n_cells);
    for (int i = 0; i < n_cells; ++i)
        unvisited[i] = i;
    std::vector<int> dist(n_cells, std::numeric_limits<int>::max());
    std::vector<int> prev(n_cells, -1);
    dist[start] = 0;

    while (!unvisited.empty()) {
        // Find shortest unvisited distance
        int min_dist = std::numeric_limits<int>::max();
        int min_i = -1;
        for (std::vector<int>::iterator it = unvisited.begin(); it != unvisited.end(); ++it) {
            int c = *it;
            if (dist[c] < min_dist) {
                min_i = c;
                min_dist = dist[c];
            }
        }

        int current = min_i;
        visited[current] = true;

        if (current == goal)
            break; // Done

        unvisited.erase(std::find(unvisited.begin(), unvisited.end(), current));
        int next_dist = dist[current] + 1;

        for (std::vector<int>::const_iterator it = cells[current].neighbors.begin(); it != cells[current].neighbors.end(); ++it) {
            int n = *it;
            if (!visited[n]) {
                if (dist[n] > next_dist) {
                    dist[n] = next_dist;
                    prev[n] = current;
                }
            }
        }
    }

    std::vector<int> path;
    path.push_back(goal);
    int cur = prev[goal];
    while (cur != -1) {
        path.push_back(cur);
        cur = prev[cur];
    }

    std::reverse(path.begin(), path.end());
    return path;
}

int closest_link(const std::vector<Cell>& cells, int start, const std::vector<int>& goals) {
    int cur_min_dist = std::numeric_limits<int>::max();
    int cur_min_i = goals[0];
    for (std::vector<int>::const_iterator it = goals.begin(); it != goals.end(); ++it) {
        int g = *it;
        std::vector<int> path = shortest_path(cells, start, g);
        if (path.size() < cur_min_dist) {
            cur_min_dist = path.size();
            cur_min_i = g;
        }
    }
    return cur_min_i;
}

std::pair<std::vector<int>, std::vector<int> > find_res(const std::vector<Cell>& cells, int start) {
    int n_cells = cells.size();
    std::vector<bool> visited(n_cells, false);
    std::vector<int> unvisited(n_cells);
    for (int i = 0; i < n_cells; ++i)
        unvisited[i] = i;
    std::vector<int> dist(n_cells, std::numeric_limits<int>::max());
    std::vector<int> prev(n_cells, -1);
    dist[start] = 0;

    std::vector<int> crist;
    std::vector<int> eggs;

    while (!unvisited.empty()) {
        // Find shortest unvisited distance
        int min_dist = std::numeric_limits<int>::max();
        int min_i = -1;
        for (std::vector<int>::iterator it = unvisited.begin(); it != unvisited.end(); ++it) {
            int c = *it;
            if (dist[c] < min_dist) {
                min_i = c;
                min_dist = dist[c];
            }
        }

        if (min_i < 0) {
            std::cerr << "ERR " << min_i << std::endl;
            break;
        }

        int current = min_i;
        visited[current] = true;

        if (cells[current].type == 1)
            eggs.push_back(current);
        if (cells[current].type == 2)
            crist.push_back(current);

        unvisited.erase(std::find(unvisited.begin(), unvisited.end(), current));
        int next_dist = dist[current] + 1;

        for (std::vector<int>::const_iterator it = cells[current].neighbors.begin(); it != cells[current].neighbors.end(); ++it) {
            int n = *it;
            if (!visited[n]) {
                if (dist[n] > next_dist) {
                    dist[n] = next_dist;
                    //prev[n] = current;
                }
            }
        }
    }

    return std::make_pair(crist, eggs);
}

int main() {
    int number_of_cells;
    std::cin >> number_of_cells;

    std::vector<Cell> cells;
    for (int i = 0; i < number_of_cells; ++i) {
        int _type, initial_resources, neigh_0, neigh_1, neigh_2, neigh_3, neigh_4, neigh_5;
        std::cin >> _type >> initial_resources >> neigh_0 >> neigh_1 >> neigh_2 >> neigh_3 >> neigh_4 >> neigh_5;
        std::vector<int> neighbors;
        neighbors.push_back(neigh_0);
        neighbors.push_back(neigh_1);
        neighbors.push_back(neigh_2);
        neighbors.push_back(neigh_3);
        neighbors.push_back(neigh_4);
        neighbors.push_back(neigh_5);
        Cell cell(i, neighbors, _type, initial_resources);
        cells.push_back(cell);
    }

    int number_of_bases;
    std::cin >> number_of_bases;

    int my_base_index, opp_base_index;
    for (int i = 0; i < number_of_bases; ++i) {
        std::cin >> my_base_index;
    }
    for (int i = 0; i < number_of_bases; ++i) {
        std::cin >> opp_base_index;
    }

    // TEST
    // std::vector<int> path = shortest_path(cells, my_base_index, opp_base_index);
    // for (std::vector<int>::iterator it = path.begin(); it != path.end(); ++it)
    //     std::cerr << *it << " ";
    // std::cerr << std::endl;

    // BFS pour la liste des ressources (croissantes par distance)
    std::pair<std::vector<int>, std::vector<int> > res = find_res(cells, my_base_index);
    const std::vector<int>& crist = res.first;
    const std::vector<int>& eggs = res.second;
    for (std::vector<int>::const_iterator it = crist.begin(); it != crist.end(); ++it)
        std::cerr << *it << " ";
    std::cerr << std::endl;
    for (std::vector<int>::const_iterator it = eggs.begin(); it != eggs.end(); ++it)
        std::cerr << *it << " ";
    std::cerr << std::endl;

    while (true) {
        std::string output = "";

        int ants_own = 0;
        int ants_opp = 0;
        for (int i = 0; i < number_of_cells; ++i) {
            int resources, my_ants, opp_ants;
            std::cin >> resources >> my_ants >> opp_ants;
            if (std::find(eggs.begin(), eggs.end(), i) != eggs.end() && resources < 1)
                eggs.erase(std::find(eggs.begin(), eggs.end(), i));
            if (std::find(crist.begin(), crist.end(), i) != crist.end() && resources < 1)
                crist.erase(std::find(crist.begin(), crist.end(), i));

            ants_own += my_ants;
            ants_opp += opp_ants;
        }

        std::vector<int> to_visit;
        std::vector<int> connected;
        connected.push_back(my_base_index);
        std::vector<std::pair<int, int> > links;

        if (ants_own < 15)
            to_visit = eggs;
        else {
            to_visit = crist;
            to_visit.insert(to_visit.end(), eggs.begin(), eggs.end());
        }

        while (!to_visit.empty()) {
            int v = to_visit[0];
            to_visit.erase(to_visit.begin());
            int cl = closest_link(cells, v, connected);
            links.push_back(std::make_pair(v, cl));
            connected.push_back(v);
        }

        for (std::vector<std::pair<int, int> >::iterator it = links.begin(); it != links.end(); ++it) {
            int start = it->first;
            int goal = it->second;
            int strength = cells[start].type;
            output += "LINE " + std::to_string(start) + " " + std::to_string(goal) + " " + std::to_string(strength) + ";";
        }

        // output += "LINE " + std::to_string(my_base_index) + " " + std::to_string(crist[0]) + " 1;";

        // Write an action using cout
        // To debug: std::cerr << "Debug messages..." << std::endl;

        std::cout << output << std::endl;
    }

    return 0;
}

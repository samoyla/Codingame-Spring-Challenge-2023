#include <iostream>
#include <vector>
#include <limits>
#include <algorithm>

struct Cell {
    int index;
    std::vector<int> neighbors;
    int type;
    int res;

    Cell(int i, const std::vector<int>& n, int t, int r)
        : index(i), neighbors(n), type(t), res(r) {}
};

std::vector<int> shortest_path(const std::vector<Cell>& cells, int start, int goal) {
    int n_cells = cells.size();
    std::vector<bool> visited(n_cells, false);
    std::vector<int> unvisited(n_cells);
    for (int i = 0; i < n_cells; ++i)
        unvisited[i] = i;
    std::vector<int> dist(n_cells, std::numeric_limits<int>::max());
    std::vector<int> prev(n_cells);
    dist[start] = 0;

    while (!unvisited.empty()) {
        // Find shortest unvisited distance
        int min_dist = std::numeric_limits<int>::max();
        int min_i = -1;
        for (int c : unvisited) {
            if (dist[c] < min_dist) {
                min_i = c;
                min_dist = dist[c];
            }
        }

        int current = min_i;
        visited[current] = true;

        if (current == goal)
            break; // Done

        unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), current), unvisited.end());
        int next_dist = dist[current] + 1;

        for (int n : cells[current].neighbors) {
            if (!visited[n]) {
                if (dist[n] > next_dist) {
                    dist[n] = next_dist;
                    prev[n] = current;
                }
            }
        }
    }

    std::vector<int> path;
    int cur = goal;
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
    for (int g : goals) {
        std::vector<int> path = shortest_path(cells, start, g);
        if (path.size() < cur_min_dist) {
            cur_min_dist = path.size();
            cur_min_i = g;
        }
    }
    return cur_min_i;
}

std::pair<std::vector<int>, std::vector<int>> find_res(const std::vector<Cell>& cells, int start) {
    int n_cells = cells.size();
    std::vector<bool> visited(n_cells, false);
    std::vector<int> unvisited(n_cells);
    for (int i = 0; i < n_cells; ++i)
        unvisited[i] = i;
    std::vector<int> dist(n_cells, std::numeric_limits<int>::max());
    std::vector<int> prev(n_cells);
    dist[start] = 0;

    std::vector<int> crist;
    std::vector<int> eggs;

    while (!unvisited.empty()) {
        // Find shortest unvisited distance
        int min_dist = std::numeric_limits<int>::max();
        int min_i = -1;
        for (int c : unvisited) {
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

        unvisited.erase(std::remove(unvisited.begin(), unvisited.end(), current), unvisited.end());
        int next_dist = dist[current] + 1;

        for (int n : cells[current].neighbors) {
            if (!visited[n]) {
                if (dist[n] > next_dist) {
                    dist[n] = next_dist;
                    // prev[n] = current;
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
        std::vector<int> neighbors = {neigh_1, neigh_2, neigh_3, neigh_4, neigh_5};
        Cell cell(i, neighbors, _type, initial_resources);
        cells.push_back(cell);
    }

    int number_of_bases;
    std::cin >> number_of_bases;
    int my_base_index, opp_base_index;
    std::cin >> my_base_index >> opp_base_index;

    // TEST
    // std::vector<int> path = shortest_path(cells, my_base_index, opp_base_index);
    // for (int p : path)
    //     std::cerr << p << " ";
    // std::cerr << std::endl;

    std::vector<int> crist, eggs;
    std::tie(crist, eggs) = find_res(cells, my_base_index);
    for (int c : crist)
        std::cerr << c << " ";
    std::cerr << std::endl;
    for (int e : eggs)
        std::cerr << e << " ";
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
        std::vector<std::pair<int, int>> links;

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

        for (const std::pair<int, int>& link : links)
            output += "LINE " + std::to_string(link.first) + " " + std::to_string(link.second) + " 1;";

        // output += "LINE " + std::to_string(my_base_index) + " " + std::to_string(crist[0]) + " 1;";

        // Write an action using std::cout
        // To debug: std::cerr << "Debug messages..." << std::endl;

        std::cout << output << std::endl;
    }

    return 0;
}

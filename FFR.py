import sys
import math


class Cell:
    def __init__(self, index, neighbors, type, res):
        self.index = index
        self.neighbors = neighbors
        self.type = type
        self.res = res

def shortest_path(cells, start, goal):
    n_cells = len(cells)
    visited = [False]*n_cells
    unvisited = [i for i in range(n_cells)]
    dist = [sys.maxsize]*n_cells
    prev = [None]*n_cells
    dist[start] = 0

while (len(unvisited) > 0):
    # Find shortest unvisited distance
    min_dist = sys.maxsize
    min_i    = -1
    for c in unvisited:
        if (dist[c] < min_dist):
            min_i    = c
            min_dist = dist[c]

    current = min_i
    visited[current] = True

if (current == goal):
    break # Done

unvisited.remove(current)
next_dist = dist[current] + 1

for n in cells[current].neighbors:
    if (not visited[n]):
        if (dist[n] > next_dist):
            dist[n] = next_dist
            prev[n] = current

    path = [goal]
    cur = prev[goal]
    #print(cur)
    while (cur != None):
        path.append(cur)
        cur = prev[cur]
   
    path.reverse()
    #print(dist, visited, file=sys.stderr)
    return path

def closest_link(cells, start, goals):
    cur_min_dist = sys.maxsize
    cur_min_i    = goals[0]
    for g in goals:
        path = shortest_path(cells, start, g)
        if (len(path) < cur_min_dist):
            cur_min_dist = len(path)
            cur_min_i    = g
    return cur_min_i




def find_res(cells, start):
    n_cells = len(cells)
    visited = [False]*n_cells
    unvisited = [i for i in range(n_cells)]
    dist = [sys.maxsize]*n_cells
    prev = [None]*n_cells
    dist[start] = 0

    crist = []
    eggs  = []

    while (len(unvisited) > 0):
        # Find shortest unvisited distance
        min_dist = sys.maxsize
        min_i    = -1
        for c in unvisited:
            #print(dist[c], min_dist, file=sys.stderr)
            if (dist[c] < min_dist):
                min_i    = c
                min_dist = dist[c]

        if (min_i < 0):
            print("ERR", min_i, file=sys.stderr)
            break

        current = min_i
        visited[current] = True

        if cells[current].type == 1:
            eggs.append(current)
        if cells[current].type == 2:
            crist.append(current)

        unvisited.remove(current)
        next_dist = dist[current] + 1

        for n in cells[current].neighbors:
            if (not visited[n]):
                if (dist[n] > next_dist):
                    dist[n] = next_dist
                    #prev[n] = current

    return crist, eggs

        
    


# Auto-generated code below aims at helping you parse
# the standard input according to the problem statement.

number_of_cells = int(input())  # amount of hexagonal cells in this map
cells = []
for i in range(number_of_cells):
    # _type: 0 for empty, 1 for eggs, 2 for crystal
    # initial_resources: the initial amount of eggs/crystals on this cell
    # neigh_0: the index of the neighbouring cell for each direction
    _type, initial_resources, neigh_0, neigh_1, neigh_2, neigh_3, neigh_4, neigh_5 = [int(j) for j in input().split()]
    cell = Cell(i, [neigh_1, neigh_2, neigh_3, neigh_4, neigh_5], _type, initial_resources)
    cells.append(cell)

number_of_bases = int(input())
for i in input().split():
    my_base_index = int(i)
for i in input().split():
    opp_base_index = int(i)

# TEST
#print(shortest_path(cells, my_base_index, opp_base_index))

# BFS pour la liste des ressources (croissantes par distance)
crist, eggs = find_res(cells, my_base_index)
print(crist, eggs, file=sys.stderr)

while True:
    output = ""

    ants_own = 0
    ants_opp = 0
    for i in range(number_of_cells):
        # resources: the current amount of eggs/crystals on this cell
        # my_ants: the amount of your ants on this cell
        # opp_ants: the amount of opponent ants on this cell
        resources, my_ants, opp_ants = [int(j) for j in input().split()]
        if ((i in eggs) and (resources < 1)):
            eggs.remove(i)
        if ((i in crist) and (resources < 1)):
            crist.remove(i)

        ants_own += my_ants
        ants_opp += opp_ants

    st = [1, 2, 3]
    to_visit = []
    if (ants_own < 15):
        to_visit += eggs
    else:
        to_visit += crist
        to_visit += eggs

    connected = [my_base_index]
    links = []
    while (len(to_visit) > 0):
        v = to_visit.pop(0)
        cl = closest_link(cells, v, connected)
        links.append((v, cl, st[cells[v].type]))
        connected.append(v)

    for (start, goal, strength) in links:
        output += f"LINE {start} {goal} {strength};"
  
    #output += f"LINE {my_base_index} {crist[0]} 1;"

    # Write an action using print
    # To debug: print("Debug messages...", file=sys.stderr, flush=True)


    # WAIT | LINE <sourceIdx> <targetIdx> <strength> | BEACON <cellIdx> <strength> | MESSAGE <text>
    print(output)
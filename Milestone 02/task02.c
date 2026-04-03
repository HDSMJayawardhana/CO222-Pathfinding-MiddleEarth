//E/19/169
//JAYAWARDHANA HDSM

#include <stdio.h>
#include <stdbool.h>

#define MAX_SIZE 26
#define MAX_H 10
#define MAX_W 10

// Structure to represent a cell in the map
typedef struct {
    int row, col;
} Cell;

// Global arrays
char map[MAX_H][MAX_W];
bool visited[MAX_H][MAX_W];
int distance[MAX_H][MAX_W];

// Queue for BFS
typedef struct {
    Cell items[MAX_SIZE * MAX_SIZE];
    int front, rear;
} Queue;

// Create a 2D array for a given string
void createmaparray(int H, int W, char mapstring[]) {
    int index = 0;
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            map[i][j] = mapstring[index++];
        }
    }
}

// Function to check if the cell is within bounds
bool validcell(int row, int col, int H, int W) {
    return row >= 0 && row < H && col >= 0 && col < W;
}

// Function to check if a move is valid based on conditions
bool validmove(char from, char to) {
    int diff = to - from;
    return (diff <= 2 && diff >= 0) || (diff >= -3 && diff <= 0);
}

// Function to perform Breadth-First Search
int bfs(int H, int W, Cell start, Cell end) {
    // Directional vectors for up, down, left, right
    int dr[] = {-1, 1, 0, 0};
    int dc[] = {0, 0, -1, 1};

    // Reset global arrays
    for (int i = 0; i < H; ++i) {
        for (int j = 0; j < W; ++j) {
            visited[i][j] = false;
            distance[i][j] = 0;
        }
    }

    // Initialize the queue for BFS
    Queue queue;
    queue.front = queue.rear = -1;

    // Enqueue the starting cell
    queue.items[++queue.rear] = start;
    visited[start.row][start.col] = true;

    // BFS
    while (queue.front < queue.rear) {
        Cell current = queue.items[++queue.front];

        // Check if the current cell is the destination
        if (current.row == end.row && current.col == end.col) {
            return distance[current.row][current.col];
        }

        // Explore neighboring cells
        for (int i = 0; i < 4; ++i) {
            int newrow = current.row + dr[i];
            int newcol = current.col + dc[i];

            // Check the new position is within bounds
            if (validcell(newrow, newcol, H, W)) {
                // Check the move is valid
                if (!visited[newrow][newcol] && validmove(map[current.row][current.col], map[newrow][newcol])) {
                    // Enqueue the new cell
                    queue.items[++queue.rear] = (Cell){newrow, newcol};
                    visited[newrow][newcol] = true;
                    distance[newrow][newcol] = distance[current.row][current.col] + 1;
                }
            }
        }
    }

    // No path found
    return -1;
}

// Function to find the minimum distances
void find_minimum_distances(int H, int W, Cell start, Cell end, Cell teleport1, Cell teleport2, int min_distances[]) {
    // Calculate the minimum distances
    min_distances[0] = bfs(H, W, start, end);  // From start to end
    min_distances[1] = bfs(H, W, start, teleport1);  // From start to teleport1
    min_distances[2] = bfs(H, W, start, teleport2);  // From start to teleport2
    min_distances[3] = bfs(H, W, teleport1, end);  // From teleport1 to end
    min_distances[4] = bfs(H, W, teleport2, end);  // From teleport2 to end
}

int main() {
    // Input variables
    int H, W; // Height and Width of the map
    int S1, S2; // Start
    int E1, E2; // End
    int TR1, TC1; // Teleport 1
    int TR2, TC2; // Teleport 2

    // Reading input
    scanf("%d %d", &H, &W);
    scanf("%d %d", &S1, &S2);
    scanf("%d %d", &E1, &E2);

    char mapstring[H * W + 1];
    scanf("%s", mapstring);

    scanf("%d %d", &TR1, &TC1);
    scanf("%d %d", &TR2, &TC2);

    // Create a 2D array for the map
    createmaparray(H, W, mapstring);

    Cell start = {S1, S2};  // Starting position
    Cell end = {E1, E2};    // Ending position
    Cell teleport1 = {TR1, TC1}; // Teleportation door 1 position
    Cell teleport2 = {TR2, TC2}; // Teleportation door 2 position

    // Array to store minimum distances
    int min_distances[5];

    // Find the minimum distances
    find_minimum_distances(H, W, start, end, teleport1, teleport2, min_distances);

    // Output
    for (int i = 0; i < 5; ++i) {
        printf("%d ", min_distances[i]);
    }
    printf("\n");

    return 0;
}


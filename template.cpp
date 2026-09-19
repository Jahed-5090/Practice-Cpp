

// Linear Graph[cite: 2]
map<int, vector<pair<int, int>>> createLinear(int n)
{
    map<int, vector<pair<int, int>>> adj;
    for (int i = 0; i < n - 1; i++)
    {
        int weight = (rand() % 9) + 1;
        adj[i].push_back({i + 1, weight});
    }
    return adj;
}

// Circular Graph[cite: 2]
map<int, vector<pair<int, int>>> createCircular(int n)
{
    map<int, vector<pair<int, int>>> adj;
    for (int i = 0; i < n; i++)
    {
        int next = (i + 1) % n;
        int weight = (rand() % 9) + 1;
        adj[i].push_back({next, weight});
    }
    return adj;
}

// Complete Graph[cite: 2]
map<int, vector<pair<int, int>>> createComplete(int n)
{
    map<int, vector<pair<int, int>>> adj;
    for (int u = 0; u < n; u++)
    {
        for (int v = 0; v < n; v++)
        {
            if (u != v)
            {
                int weight = (rand() % 9) + 1;
                adj[u].push_back({v, weight});
            }
        }
    }
    return adj;
}

// Random Graph[cite: 2]
map<int, vector<pair<int, int>>> createRandom(int n, int edges)
{
    map<int, vector<pair<int, int>>> adj;
    set<pair<int, int>> used;
    while ((int)used.size() < edges)
    {
        int u = rand() % n;
        int v = rand() % n;
        if (u == v || used.count({u, v}))
            continue;

        used.insert({u, v});
        int weight = (rand() % 15);
        adj[u].push_back({v, weight});
    }
    return adj;
}

// --- File Input/Output ---

// Save Matrix to File[cite: 2]
void saveToFile(string filename, const vector<vector<int>> &dist)
{
    ofstream file(filename);
    for (int i = 0; i < (int)dist.size(); i++)
    {
        for (int j = 0; j < (int)dist[i].size(); j++)
        {
            if (dist[i][j] == INF)
                file << "INF ";
            else
                file << dist[i][j] << " ";
        }
        file << endl;
    }
    file.close();
}

// Read Matrix from File[cite: 2]
vector<vector<int>> readFromFile(string filename, int vtx)
{
    vector<vector<int>> dist(vtx, vector<int>(vtx, INF));
    ifstream file(filename);
    string x;
    for (int i = 0; i < vtx; i++)
    {
        for (int j = 0; j < vtx; j++)
        {
            file >> x;
            if (x == "INF")
                dist[i][j] = INF;
            else
                dist[i][j] = stoi(x);
        }
    }
    file.close();
    return dist;
}

auto startD = chrono::high_resolution_clock::now();

auto endD = chrono::high_resolution_clock::now();
chrono::duration<double, milli> timeD = endD - startD;
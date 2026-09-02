// Dij-Matrix
void solve(vector<vector<ll>> &adjM, ll src, ll node, ofstream &fout)
{ // changed
    vector<ll> dist(node + 1, INF), par(node + 1, -1);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    dist[src] = 0;
    pq.push({0, src});
    while (!pq.empty())
    {
        ll d = pq.top().first, u = pq.top().second;
        pq.pop();
        if (d > dist[u])
            continue;
        for (int v = 1; v <= node; v++)
        { // changed
            if (u == v || adjM[u][v] >= INF)
                continue;      // changed
            ll w = adjM[u][v]; // changed
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                par[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    if (dist[node] >= INF)
    {
        cout << -1 << endl;
        fout << -1 << endl;
    }
    else
    {
        vector<ll> path;
        for (ll i = node; i != -1; i = par[i])
            path.push_back(i);
        reverse(path.begin(), path.end());
        for (ll x : path)
        {
            cout << x << " ";
            fout << x << " ";
        }
        cout << endl;
        fout << endl;
    }
    for (int i = 1; i <= node; i++)
    {
        ll v = (dist[i] >= INF ? -1 : dist[i]);
        cout << v << " ";
        fout << v << " ";
    }
    cout << endl;
    fout << endl;
}

// edgeL
void solve(vector<array<ll, 3>> &edgeList, ll src, ll node, ofstream &fout)
{ // changed
    vector<ll> dist(node + 1, INF), par(node + 1, -1);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    dist[src] = 0;
    pq.push({0, src});
    while (!pq.empty())
    {
        ll d = pq.top().first, u = pq.top().second;
        pq.pop();
        if (d > dist[u])
            continue;
        for (auto &e : edgeList)
        { // changed
            if (e[0] != u)
                continue;          // changed
            ll v = e[1], w = e[2]; // changed
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                par[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    if (dist[node] >= INF)
    {
        cout << -1 << endl;
        fout << -1 << endl;
    }
    else
    {
        vector<ll> path;
        for (ll i = node; i != -1; i = par[i])
            path.push_back(i);
        reverse(path.begin(), path.end());
        for (ll x : path)
        {
            cout << x << " ";
            fout << x << " ";
        }
        cout << endl;
        fout << endl;
    }
    for (int i = 1; i <= node; i++)
    {
        ll v = (dist[i] >= INF ? -1 : dist[i]);
        cout << v << " ";
        fout << v << " ";
    }
    cout << endl;
    fout << endl;
}

// ADJL
void solve(vector<vector<pair<ll, ll>>> &adj, ll src, ll node, ofstream &fout)
{ // changed
    vector<ll> dist(node + 1, INF), par(node + 1, -1);
    priority_queue<pair<ll, ll>, vector<pair<ll, ll>>, greater<pair<ll, ll>>> pq;
    dist[src] = 0;
    pq.push({0, src});
    while (!pq.empty())
    {
        ll d = pq.top().first, u = pq.top().second;
        pq.pop();
        if (d > dist[u])
            continue;
        for (auto &pr : adj[u])
        {                                   // changed
            ll v = pr.first, w = pr.second; // changed
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                par[v] = u;
                pq.push({dist[v], v});
            }
        }
    }
    if (dist[node] >= INF)
    {
        cout << -1 << endl;
        fout << -1 << endl;
    }
    else
    {
        vector<ll> path;
        for (ll i = node; i != -1; i = par[i])
            path.push_back(i);
        reverse(path.begin(), path.end());
        for (ll x : path)
        {
            cout << x << " ";
            fout << x << " ";
        }
        cout << endl;
        fout << endl;
    }
    for (int i = 1; i <= node; i++)
    {
        ll v = (dist[i] >= INF ? -1 : dist[i]);
        cout << v << " ";
        fout << v << " ";
    }
    cout << endl;
    fout << endl;
}

BELLMOND
MAtrix

    void
    solve(vector<vector<ll>> &adjM, ll src, ll node, ofstream &fout)
{ // changed
    vector<ll> dist(node + 1, INF), par(node + 1, -1);
    dist[src] = 0;
    for (int i = 1; i < node; i++)
    {
        for (int u = 1; u <= node; u++)
        {
            if (dist[u] >= INF)
                continue;
            for (int v = 1; v <= node; v++)
            { // changed
                if (u == v || adjM[u][v] >= INF)
                    continue;      // changed
                ll w = adjM[u][v]; // changed
                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    par[v] = u;
                }
            }
        }
    }
    if (dist[node] >= INF)
    {
        cout << -1 << endl;
        fout << -1 << endl;
    }
    else
    {
        vector<ll> path;
        for (ll i = node; i != -1; i = par[i])
            path.push_back(i);
        reverse(path.begin(), path.end());
        for (ll x : path)
        {
            cout << x << " ";
            fout << x << " ";
        }
        cout << endl;
        fout << endl;
    }
    for (int i = 1; i <= node; i++)
    {
        ll v = (dist[i] >= INF ? -1 : dist[i]);
        cout << v << " ";
        fout << v << " ";
    }
    cout << endl;
    fout << endl;
}

// EL
void solve(vector<array<ll, 3>> &edgeList, ll src, ll node, ofstream &fout)
{ // changed
    vector<ll> dist(node + 1, INF), par(node + 1, -1);
    dist[src] = 0;
    for (int i = 1; i < node; i++)
    {
        for (auto &e : edgeList)
        {                                    // changed
            ll u = e[0], v = e[1], w = e[2]; // changed
            if (u == v || dist[u] >= INF)
                continue; // changed
            if (dist[u] + w < dist[v])
            {
                dist[v] = dist[u] + w;
                par[v] = u;
            }
        }
    }
    if (dist[node] >= INF)
    {
        cout << -1 << endl;
        fout << -1 << endl;
    }
    else
    {
        vector<ll> path;
        for (ll i = node; i != -1; i = par[i])
            path.push_back(i);
        reverse(path.begin(), path.end());
        for (ll x : path)
        {
            cout << x << " ";
            fout << x << " ";
        }
        cout << endl;
        fout << endl;
    }
    for (int i = 1; i <= node; i++)
    {
        ll v = (dist[i] >= INF ? -1 : dist[i]);
        cout << v << " ";
        fout << v << " ";
    }
    cout << endl;
    fout << endl;
}

// AL
void solve(vector<vector<pair<ll, ll>>> &adj, ll src, ll node, ofstream &fout)
{ // changed
    vector<ll> dist(node + 1, INF), par(node + 1, -1);
    dist[src] = 0;
    for (int i = 1; i < node; i++)
    {
        for (int u = 1; u <= node; u++)
        {
            if (dist[u] >= INF)
                continue;
            for (auto &pr : adj[u])
            {                                   // changed
                ll v = pr.first, w = pr.second; // changed
                if (u == v)
                    continue; // changed
                if (dist[u] + w < dist[v])
                {
                    dist[v] = dist[u] + w;
                    par[v] = u;
                }
            }
        }
    }
    if (dist[node] >= INF)
    {
        cout << -1 << endl;
        fout << -1 << endl;
    }
    else
    {
        vector<ll> path;
        for (ll i = node; i != -1; i = par[i])
            path.push_back(i);
        reverse(path.begin(), path.end());
        for (ll x : path)
        {
            cout << x << " ";
            fout << x << " ";
        }
        cout << endl;
        fout << endl;
    }
    for (int i = 1; i <= node; i++)
    {
        ll v = (dist[i] >= INF ? -1 : dist[i]);
        cout << v << " ";
        fout << v << " ";
    }
    cout << endl;
    fout << endl;
}

FLOYD
matrix void solve(vector<vector<ll>> &adjM, ll src, ll node, ofstream &fout)
{                                   // changed
    vector<vector<ll>> dist = adjM; // changed
    vector<vector<ll>> par(node + 1, vector<ll>(node + 1, -1));
    for (int i = 1; i <= node; i++)
        for (int j = 1; j <= node; j++)
            if (i != j && dist[i][j] < INF)
                par[i][j] = i;
    for (int k = 1; k <= node; k++)
    {
        for (int i = 1; i <= node; i++)
        {
            for (int j = 1; j <= node; j++)
            {
                if (dist[i][k] != INF && dist[k][j] != INF)
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        par[i][j] = par[k][j];
                    }
            }
        }
    }
    if (dist[src][node] >= INF)
    {
        cout << -1 << endl;
        fout << -1 << endl;
    }
    else
    {
        vector<ll> path;
        ll cur = node;
        while (cur != -1)
        {
            path.push_back(cur);
            if (cur == src)
                break;
            cur = par[src][cur];
        }
        reverse(path.begin(), path.end());
        for (ll x : path)
        {
            cout << x << " ";
            fout << x << " ";
        }
        cout << endl;
        fout << endl;
    }
    for (int i = 1; i <= node; i++)
    {
        ll v = (dist[src][i] >= INF ? -1 : dist[src][i]);
        cout << v << " ";
        fout << v << " ";
    }
    cout << endl;
    fout << endl;
}

// EL
void solve(vector<array<ll, 3>> &edgeList, ll src, ll node, ofstream &fout)
{                                                                 // changed
    vector<vector<ll>> dist(node + 1, vector<ll>(node + 1, INF)); // changed
    for (int i = 0; i < (int)edgeList.size(); i++)
    {                                                                  // changed
        ll u = edgeList[i][0], v = edgeList[i][1], w = edgeList[i][2]; // changed
        dist[u][v] = min(dist[u][v], w);                               // changed
    }
    for (int i = 1; i <= node; i++)
        dist[i][i] = 0;
    vector<vector<ll>> par(node + 1, vector<ll>(node + 1, -1));
    for (int i = 1; i <= node; i++)
        for (int j = 1; j <= node; j++)
            if (i != j && dist[i][j] < INF)
                par[i][j] = i;
    for (int k = 1; k <= node; k++)
    {
        for (int i = 1; i <= node; i++)
        {
            for (int j = 1; j <= node; j++)
            {
                if (dist[i][k] != INF && dist[k][j] != INF)
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        par[i][j] = par[k][j];
                    }
            }
        }
    }
    if (dist[src][node] >= INF)
    {
        cout << -1 << endl;
        fout << -1 << endl;
    }
    else
    {
        vector<ll> path;
        ll cur = node;
        while (cur != -1)
        {
            path.push_back(cur);
            if (cur == src)
                break;
            cur = par[src][cur];
        }
        reverse(path.begin(), path.end());
        for (ll x : path)
        {
            cout << x << " ";
            fout << x << " ";
        }
        cout << endl;
        fout << endl;
    }
    for (int i = 1; i <= node; i++)
    {
        ll v = (dist[src][i] >= INF ? -1 : dist[src][i]);
        cout << v << " ";
        fout << v << " ";
    }
    cout << endl;
    fout << endl;
}

// AL
void solve(vector<vector<pair<ll, ll>>> &adj, ll src, ll node, ofstream &fout)
{                                                                 // changed
    vector<vector<ll>> dist(node + 1, vector<ll>(node + 1, INF)); // changed
    for (int u = 1; u <= node; u++)
    { // changed
        for (int i = 0; i < (int)adj[u].size(); i++)
        {                                                 // changed
            ll v = adj[u][i].first, w = adj[u][i].second; // changed
            dist[u][v] = min(dist[u][v], w);              // changed
        }
    }
    for (int i = 1; i <= node; i++)
        dist[i][i] = 0;
    vector<vector<ll>> par(node + 1, vector<ll>(node + 1, -1));
    for (int i = 1; i <= node; i++)
        for (int j = 1; j <= node; j++)
            if (i != j && dist[i][j] < INF)
                par[i][j] = i;
    for (int k = 1; k <= node; k++)
    {
        for (int i = 1; i <= node; i++)
        {
            for (int j = 1; j <= node; j++)
            {
                if (dist[i][k] != INF && dist[k][j] != INF)
                    if (dist[i][k] + dist[k][j] < dist[i][j])
                    {
                        dist[i][j] = dist[i][k] + dist[k][j];
                        par[i][j] = par[k][j];
                    }
            }
        }
    }
    if (dist[src][node] >= INF)
    {
        cout << -1 << endl;
        fout << -1 << endl;
    }
    else
    {
        vector<ll> path;
        ll cur = node;
        while (cur != -1)
        {
            path.push_back(cur);
            if (cur == src)
                break;
            cur = par[src][cur];
        }
        reverse(path.begin(), path.end());
        for (ll x : path)
        {
            cout << x << " ";
            fout << x << " ";
        }
        cout << endl;
        fout << endl;
    }
    for (int i = 1; i <= node; i++)
    {
        ll v = (dist[src][i] >= INF ? -1 : dist[src][i]);
        cout << v << " ";
        fout << v << " ";
    }
    cout << endl;
    fout << endl;
}
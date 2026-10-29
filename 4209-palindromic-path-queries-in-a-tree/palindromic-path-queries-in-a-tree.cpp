class Solution {
    vector<vector<int>> adj;
    vector<int> parent, depth, sz, heavy, head, pos;
    int timer = 0;
    vector<int> seg;

    void buildSeg(int node, int l, int r, vector<int>& a) {
        if (l == r) {
            seg[node] = a[l];
            return;
        }
        int mid = (l + r) / 2;
        buildSeg(node * 2, l, mid, a);
        buildSeg(node * 2 + 1, mid + 1, r, a);
        seg[node] = seg[node * 2] ^ seg[node * 2 + 1];
    }

    void update(int node, int l, int r, int p, int val) {
        if (l == r) {
            seg[node] = val;
            return;
        }
        int mid = (l + r) / 2;
        if (p <= mid)
            update(node * 2, l, mid, p, val);
        else
            update(node * 2 + 1, mid + 1, r, p, val);

        seg[node] = seg[node * 2] ^ seg[node * 2 + 1];
    }

    int query(int node, int l, int r, int ql, int qr) {
        if (ql <= l && r <= qr) return seg[node];
        int mid = (l + r) / 2, ans = 0;

        if (ql <= mid)
            ans ^= query(node * 2, l, mid, ql, qr);
        if (qr > mid)
            ans ^= query(node * 2 + 1, mid + 1, r, ql, qr);

        return ans;
    }

    int pathQuery(int u, int v, int n) {
        int mask = 0;

        while (head[u] != head[v]) {
            if (depth[head[u]] < depth[head[v]])
                swap(u, v);

            mask ^= query(1, 0, n - 1, pos[head[u]], pos[u]);
            u = parent[head[u]];
        }

        if (depth[u] > depth[v]) swap(u, v);

        mask ^= query(1, 0, n - 1, pos[u], pos[v]);
        return mask;
    }

public:
    vector<bool> palindromePath(int n, vector<vector<int>>& edges,
                                string s, vector<string>& queries) {
        adj.assign(n, {});
        for (auto& e : edges) {
            adj[e[0]].push_back(e[1]);
            adj[e[1]].push_back(e[0]);
        }

        parent.assign(n, -1);
        depth.assign(n, 0);
        sz.assign(n, 1);
        heavy.assign(n, -1);
        head.resize(n);
        pos.resize(n);

        vector<int> order = {0};

        for (int i = 0; i < (int)order.size(); i++) {
            int u = order[i];
            for (int v : adj[u]) {
                if (v == parent[u]) continue;
                parent[v] = u;
                depth[v] = depth[u] + 1;
                order.push_back(v);
            }
        }

        for (int i = n - 1; i > 0; i--) {
            int u = order[i], p = parent[u];
            sz[p] += sz[u];

            if (heavy[p] == -1 || sz[u] > sz[heavy[p]])
                heavy[p] = u;
        }

        vector<pair<int, int>> st = {{0, 0}};

        while (!st.empty()) {
            auto [u, h] = st.back();
            st.pop_back();

            for (int v = u; v != -1; v = heavy[v]) {
                head[v] = h;
                pos[v] = timer++;

                for (int w : adj[v]) {
                    if (w != parent[v] && w != heavy[v])
                        st.push_back({w, w});
                }
            }
        }

        vector<int> a(n);
        for (int i = 0; i < n; i++)
            a[pos[i]] = 1 << (s[i] - 'a');

        seg.assign(4 * n, 0);
        buildSeg(1, 0, n - 1, a);

        vector<bool> ans;

        for (string& q : queries) {
            string type;
            int u;
            char c;

            stringstream ss(q);
            ss >> type >> u;

            if (type == "update") {
                ss >> c;
                s[u] = c;
                update(1, 0, n - 1, pos[u], 1 << (c - 'a'));
            } else {
                int v;
                ss >> v;
                int mask = pathQuery(u, v, n);
                ans.push_back((mask & (mask - 1)) == 0);
            }
        }

        return ans;
    }
};
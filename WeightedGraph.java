import java.util.*;

public class WeightedGraph {
    private int V;
    private List<List<int[]>> adj; // each int[] = {neighbor, weight}

    public WeightedGraph(int V) {
        this.V = V;
        adj = new ArrayList<>();
        for (int i = 0; i < V; i++) {
            adj.add(new ArrayList<>());
        }
    }

    public void addEdge(int u, int v, int w) {
        addEdge(u, v, w, false);
    }

    public void addEdge(int u, int v, int w, boolean directed) {
        adj.get(u).add(new int[]{v, w});
        if (!directed) {
            adj.get(v).add(new int[]{u, w});
        }
    }

    public void print() {
        for (int i = 0; i < V; i++) {
            System.out.print(i + ": ");
            for (int[] edge : adj.get(i)) {
                int neighbor = edge[0];
                int weight = edge[1];
                System.out.print("(" + neighbor + ", w=" + weight + ") ");
            }
            System.out.println();
        }
    }

    public static void main(String[] args) {
        WeightedGraph g = new WeightedGraph(5);
        g.addEdge(0, 1, 4);
        g.addEdge(0, 4, 1);
        g.addEdge(1, 2, 3);
        g.addEdge(1, 3, 2);
        g.addEdge(1, 4, 5);
        g.addEdge(2, 3, 7);
        g.addEdge(3, 4, 6);

        g.print();
    }
}
using System;

class GFG
{
    static int V = 5;
    int minDistance(int[] dist,
                    bool[] sptSet)
    {
        int min = int.MaxValue, min_index = -1;

        for (int v = 0; v < V; v++)
            if (sptSet[v] == false && dist[v] <= min)
            {
                min = dist[v];
                min_index = v;
            }

        return min_index;
    }

    void printPath(int[] prev, int v)
    {
        if (prev[v] != -1)
        {
            printPath(prev, prev[v]);
            Console.Write(" ===> ");
        }
        Console.Write(v);
    }

    void printSolution(int[] dist, int[] prev, int n)
    {
        /*Console.Write("Vertex	 Distance "
                    + "from Source\n");
        for (int i = 0; i < V; i++)
            Console.Write(i + " \t\t " + dist[i] + "\n");*/
        Console.WriteLine("Vertex\tDistance\tPath");
        for (int i = 0; i < V; i++)
        {
            Console.Write(i + "\t" + dist[i] + "\t\t");
            if (dist[i] == int.MaxValue)
            {
                Console.WriteLine("No path");
            }
            else
            {
                printPath(prev, i);
                Console.WriteLine();
            }
        }
    }
    void dijkstra(int[,] graph, int src)
    {
        int[] dist = new int[V];
        int[] prev = new int[V];
        bool[] sptSet = new bool[V];
        for (int i = 0; i < V; i++)
        {
            dist[i] = int.MaxValue;
            prev[i] = -1;
            sptSet[i] = false;
        }
        dist[src] = 0;
        for (int count = 0; count < V - 1; count++)
        {
            int u = minDistance(dist, sptSet);
            sptSet[u] = true;
            for (int v = 0; v < V; v++)
                if (!sptSet[v] && graph[u, v] != 0 &&
                    dist[u] != int.MaxValue && dist[u] + graph[u, v] < dist[v])
                {
                    dist[v] = dist[u] + graph[u, v];
                    prev[v] = u;
                }


        }
        printSolution(dist, prev, V);
    }

    public static void Main()
    {
        int[,] graph = new int[,] { { 0, 4, 0, 0, 0 },
                                    { 4, 0, 8, 0, 20 },
                                    { 0, 8, 0, 4, 0},
                                    { 0, 0, 4, 0, 9},
                                    { 0, 20, 0, 9, 0} };
        GFG t = new GFG();
        t.dijkstra(graph, 0);
    }
}
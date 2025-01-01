class Graph:
    def __init__(self):
        self.adj_list = {}

    def add_edge(self, node1, node2):
        """Add an edge between node1 and node2."""
        if node1 not in self.adj_list:
            self.adj_list[node1] = []
        if node2 not in self.adj_list:
            self.adj_list[node2] = []
        self.adj_list[node1].append(node2)
        self.adj_list[node2].append(node1)

    def bfs_traversal(self, start):
        """Perform BFS traversal starting from the given node."""
        visited = set()
        queue = [start]
        order = []

        while queue:
            current = queue.pop(0)
            if current not in visited:
                visited.add(current)
                order.append(current)
                queue.extend(neighbor for neighbor in self.adj_list[current] if neighbor not in visited)
        return order

    def dfs_traversal(self, start):
        """Perform DFS traversal starting from the given node."""
        visited = set()
        order = []

        def dfs_recursive(node):
            visited.add(node)
            order.append(node)
            for neighbor in self.adj_list[node]:
                if neighbor not in visited:
                    dfs_recursive(neighbor)

        dfs_recursive(start)
        return order

# Run the program
if __name__ == "__main__":
    g = Graph()

    # Input the graph
    num_edges = int(input("Number of edges: "))
    print("Enter each edge (node1 node2):")
    for _ in range(num_edges):
        node1, node2 = input().split()
        g.add_edge(node1, node2)

    start_node = input("Starting node: ")

    # Print traversal results
    print("BFS:", g.bfs_traversal(start_node))
    print("DFS:", g.dfs_traversal(start_node))


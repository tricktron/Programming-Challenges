from itertools import *
from heapq import *

class PriorityQueue:

    def __init__(self, t=None):
        self._pq = [] if t is None else t  # list of entries arranged in a heap
        self._entry_finder = {}  # mapping of tasks to entries
        self._REMOVED = '<removed-task>'  # placeholder for a removed task
        self._counter = count()  # unique sequence count

    def add_task(self, task, priority=0):
        """Add a new task or update the priority of an existing task. Adding a new task is O(logn) and updating a task is 0(1)."""
        if task in self._entry_finder:
            self.remove_task(task)
        count = next(self._counter)
        entry = [-priority, count, task]
        self._entry_finder[task] = entry
        heappush(self._pq, entry)

    def remove_task(self, task):
        """Mark an existing task as REMOVED.  Raise KeyError if not found."""
        entry = self._entry_finder.pop(task)
        entry[-1] = self._REMOVED

    def pop_task(self):
        """Remove and return the lowest priority task. Raise KeyError if empty. In O(logn)."""
        while self._pq:
            priority, count, task = heappop(self._pq)
            if task is not self._REMOVED:
                del self._entry_finder[task]
                return task
        raise KeyError('pop from an empty priority queue')

    def is_empty(self):
        """Return True if the queue is empty, False otherwise."""
        return self._pq == []

    def task_exists(self, task):
        return task in self._entry_finder



def get_neighbours(x, y):
    """ Returns the indexes of neighbors at pos(x, y) in the 2d array if they exist. A valid neighbour is one step
    north, one step east, one step south or one step west.
    :param x: int
    :param y: int
    :return: list of (x,y) tuples
    """
    t = []
    if x > 0:
        t.append((x-1, y))
    if y > 0:
        t.append((x, y-1))
    if x < row-1:
        t.append((x+1, y))
    if y < col-1:
        t.append((x, y+1))
    return t


def relax(i, j, weights, q, neighbour_index):
    """Performs the modified relaxation. It computes the min of current position and the neighbour because we look for
    the min bottleneck.
    :param i: int
    :param j: int
    :param weights: list of list
    :param q: Max priority queue
    :param neighbour_index: int
    """
    c = weights[neighbour_index[0]][neighbour_index[1]]
    if q.task_exists(neighbour_index):
        if c < weights[i][j]:
            q.add_task(neighbour_index, c)
    q.add_task(neighbour_index, min(c, weights[i][j]))
    weights[neighbour_index[0]][neighbour_index[1]] = min(c, weights[i][j])


def find_max_bottleneck(weights, s_x, s_y, d_x, d_y):
    """Uses a modified version of Dijkstra to find the maximal bottleneck in the graph using a modified max priority
    queue. It operates directly on the 2d weights array and terminates if the destination pos is reached or if the queue
    is empty which means every position has been considered.
    :param weights: list of list
    :param s_x: int start_x pos
    :param s_y: int start_y pos
    :param d_x: int destination x pos
    :param d_y: int destination y pos
    :return: int
    """
    q = PriorityQueue()
    q.add_task((s_x, s_y), weights[s_x][s_y])
    visited = {}
    i, j = s_x, s_y
    while not q.is_empty() and (i, j) != (d_x, d_y):  # do until all vertices are explored
        (i, j) = q.pop_task()
        visited[(i, j)] = True
        t = get_neighbours(i, j)
        for neighbour_index in t:
            if not visited.get(neighbour_index, False):
                relax(i, j, weights, q, neighbour_index)
    return weights[d_x][d_y]


if __name__ == '__main__':
    row, col, start_x, start_y, dest_x, dest_y = (int(i) for i in range(3) for i in input().split())
    weights = [[int(i) for i in input().split()] for _ in range(row)]
    val = find_max_bottleneck(weights, start_y, start_x, dest_y, dest_x)
    print(val)




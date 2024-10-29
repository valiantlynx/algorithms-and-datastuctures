#include <iostream>
#include <vector>
#include <string>
#include <unordered_map>

struct PrintJob {
    std::string name;
    int priority;

    PrintJob(const std::string& name, int priority) : name(name), priority(priority) {}
};

// Max-Heap Priority Queue
class PriorityQueue {
private:
    std::vector<PrintJob> heap;
    std::unordered_map<std::string, int> jobMap; // Map for quick job access

    void heapifyUp(int index) {
        while (index > 0 && heap[parent(index)].priority < heap[index].priority) {
            swap(index, parent(index));
            index = parent(index);
        }
    }

    void heapifyDown(int index) {
        int maxIndex = index;
        int leftChild = left(index);
        int rightChild = right(index);

        if (leftChild < heap.size() && heap[leftChild].priority > heap[maxIndex].priority) {
            maxIndex = leftChild;
        }
        if (rightChild < heap.size() && heap[rightChild].priority > heap[maxIndex].priority) {
            maxIndex = rightChild;
        }
        if (index != maxIndex) {
            swap(index, maxIndex);
            heapifyDown(maxIndex);
        }
    }

    int parent(int index) { return (index - 1) / 2; }
    int left(int index) { return 2 * index + 1; }
    int right(int index) { return 2 * index + 2; }

    void swap(int i, int j) {
        std::swap(heap[i], heap[j]);
        jobMap[heap[i].name] = i;
        jobMap[heap[j].name] = j;
    }

public:
    void insertJob(const std::string& name, int priority) {
        if (jobMap.count(name)) {
            std::cout << "Error: Job with the name '" << name << "' already exists.\n";
            return;
        }

        heap.emplace_back(name, priority);
        int index = heap.size() - 1;
        jobMap[name] = index;
        heapifyUp(index);
        displayHighestPriorityJob();
    }

    void processJob() {
        if (heap.empty()) {
            std::cout << "No jobs to process.\n";
            return;
        }
        
        PrintJob highestPriorityJob = heap[0];
        std::cout << "Processing: " << highestPriorityJob.name << " (Priority: " << highestPriorityJob.priority << ")\n";

        jobMap.erase(highestPriorityJob.name);
        heap[0] = heap.back();
        heap.pop_back();

        if (!heap.empty()) {
            jobMap[heap[0].name] = 0;
            heapifyDown(0);
        }
    }

    void updatePriority(const std::string& name, int newPriority) {
        if (!jobMap.count(name)) {
            std::cout << "Error: Job with the name '" << name << "' does not exist.\n";
            return;
        }

        int index = jobMap[name];
        int oldPriority = heap[index].priority;
        heap[index].priority = newPriority;

        if (newPriority > oldPriority) {
            heapifyUp(index);
        } else {
            heapifyDown(index);
        }

        std::cout << "Updated " << name << " to priority " << newPriority << ".\n";
        displayQueue();
    }

    void displayHighestPriorityJob() {
        if (!heap.empty()) {
            std::cout << "Next job: " << heap[0].name << " (Priority: " << heap[0].priority << ")\n";
        } else {
            std::cout << "No jobs in the queue.\n";
        }
    }

    void displayQueue() {
        std::cout << "Queue contains: ";
        for (const auto& job : heap) {
            std::cout << "[" << job.name << " (Priority: " << job.priority << ")] ";
        }
        std::cout << "\n";
    }
};

int main() {
    PriorityQueue queue;

    queue.insertJob("Thesis", 4);
    queue.insertJob("Project", 5);
    queue.insertJob("Report", 3);
    queue.insertJob("Assignment", 2);

    queue.displayHighestPriorityJob();
    queue.processJob();

    queue.insertJob("Invoice", 6);
    queue.updatePriority("Thesis", 7);

    return 0;
}

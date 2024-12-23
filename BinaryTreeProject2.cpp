
// Name        : BinarySearchTree.cpp
// Author      : Nai Muhinyi
// Version     : 1.0
// Copyright   : Copyright � 2024 SNHU COCE
// Description : Project 2 Binary Search
//============================================================================

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <string>

using namespace std;

// Course structure to store course data
struct Course {
    string courseId;  
    string courseTitle;   
    vector<string> prerequisites;  // List of prerequisites course numbers

    // Default constructor
    Course() {}

    // Parameterized constructor
    Course(string number, string title, vector<string> prereqs)
        : courseId(number), courseTitle(title), prerequisites(prereqs) {
    }
};

// Structure for the binary search tree
struct Node {
    Course course;  // Course object of data stored in the node
    Node* left;     // Pointer to the left child node
    Node* right;    // Pointer to the right child node

    // Constructor to initialize a node with a course
    Node(Course c) : course(c), left(nullptr), right(nullptr) {}
};

// Binary Search Tree class to manage Course objects
class BinarySearchTree {
private:
    Node* root;  // Root node of the binary search tree

    // Recursive methods
    void inOrderTraversal(Node* node);  
    Node* insertNode(Node* node, Course course); 
    Node* searchNode(Node* node, string courseId);  

public:
    BinarySearchTree();  // Constructor
    ~BinarySearchTree();  // Destructor

    // Public methods
    void Insert(Course course);  
    void PrintAllCourses();  
    void PrintCourseDetails(string courseId); 
};

// Constructor to initialize the root 
BinarySearchTree::BinarySearchTree() : root(nullptr) {}

// Destructor to clean up memory used 
BinarySearchTree::~BinarySearchTree() {
    
    while (root != nullptr) {
        root = nullptr;
    }
}

// Insert a course into the tree
void BinarySearchTree::Insert(Course course) {
    root = insertNode(root, course);
}

// Recursively insert a course into the correct position in the tree
Node* BinarySearchTree::insertNode(Node* node, Course course) {
    if (node == nullptr) {
        return new Node(course);  
    }
    if (course.courseId < node->course.courseId) {
        node->left = insertNode(node->left, course);  // Traverse left for smaller values
    }
    else {
        node->right = insertNode(node->right, course);  // Traverse right for larger values
    }
    return node;
}

// Print all courses in alphanumeric order
void BinarySearchTree::PrintAllCourses() {
    inOrderTraversal(root);
}

// In-order traversal and print courses
void BinarySearchTree::inOrderTraversal(Node* node) {
    if (node != nullptr) {
        inOrderTraversal(node->left);  // Visit left subtree
        cout << node->course.courseId << ": " << node->course.courseTitle << endl;
        inOrderTraversal(node->right);  // Visit right subtree
    }
}

// Print details of a specific course
void BinarySearchTree::PrintCourseDetails(string courseId) {
    Node* result = searchNode(root, courseId);
    if (result == nullptr) {
        cout << "Course not found: " << courseId << endl;
    }
    else {
        cout << "Course Number: " << result->course.courseId << endl;
        cout << "Course Title: " << result->course.courseTitle << endl;
        cout << "Prerequisites: ";
        for (const string& prereq : result->course.prerequisites) {
            cout << prereq << " ";
        }
        cout << endl;
    }
}

// Recursively search for a course by course number
Node* BinarySearchTree::searchNode(Node* node, string courseId) {
    if (node == nullptr || node->course.courseId == courseId) {
        return node;  // Return the node if found or null if not found
    }
    if (courseId < node->course.courseId) {
        return searchNode(node->left, courseId);  // Search left subtree
    }
    return searchNode(node->right, courseId);  // Search right subtree
}

// Display menu
void displayMenu() {
    cout << "Menu:\n";
    cout << "1. Load Course Data\n";
    cout << "2. Print All Courses\n";
    cout << "3. Print Course Details\n";
    cout << "9. Exit\n";
    cout << "Enter your choice: ";
}

// Load course data from a file into the binary search tree
void loadCourseData(BinarySearchTree& bst, const string& filename) {
    ifstream file(filename);
    cout << "Attempting to open file: " << filename << endl; //testingby purposes to see if filename was received by funciton
    if (!file.is_open()) {
        cout << "Error: Could not open file." << endl;
        return;
    }

    string line;
    while (getline(file, line)) {
        stringstream ss(line);
        string courseId, courseTitle, prereq;
        vector<string> prerequisites;

        // Parsing 
        getline(ss, courseId, ',');  // Parse course number
        getline(ss, courseTitle, ',');  // Parse course title
        while (getline(ss, prereq, ',')) {
            prerequisites.push_back(prereq);  // Parse prerequisites
        }

        Course course(courseId, courseTitle, prerequisites);  
        bst.Insert(course);  
    }
    file.close();
    cout << "Courses loaded successfully." << endl;
}


int main() {
    BinarySearchTree bst;  // Binary search tree object
    int choice;
    string filename = "CS 300 ABCU_Advising_Program_Input.csv"; // manual input of file name

    //cout << "Enter the course data file name: ";
    //cin >> filename;

    do {
        displayMenu();  
        cin >> choice;  

        switch (choice) {
        case 1:
            loadCourseData(bst, filename);  
            break;
        case 2:
            cout << "\nAll Courses (Sorted):\n";
            bst.PrintAllCourses();  
            break;
        case 3: {
            string courseId;
            cout << "Enter course number: ";
            cin >> courseId; 
            bst.PrintCourseDetails(courseId);  
            break;
        }
        case 9:
            cout << "Exiting program." << endl;
            break;
        default:
            cout << "Invalid choice. Please try again." << endl;
            break;
        }
    } while (choice != 9);  // Exit the loop if the user selects option 9

    return 0;
}









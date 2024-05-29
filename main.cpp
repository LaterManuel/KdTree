#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <algorithm>
#include <iomanip>
using namespace std;

struct point{
    float x;
    float y;
    point(){};
    point(float x, float y):x(x), y(y) {}
}; 


//Read data from file
void readData(vector<point>& data,string filename){
    ifstream file(filename);
    string line;
    //Skip first line
    getline(file, line);
    while(getline(file, line)){
        stringstream ss(line);
        string x, y;
        getline(ss, x, ',');
        getline(ss, y, ',');
        data.push_back(point(stof(x), stof(y)));
    }
}


struct Node{
    point coord;
    Node* left;
    Node* right;
    Node(point coord){
        this->coord = coord;
        this->left = NULL;
        this->right = NULL;
    }
};

// Estructura para KD Tree
struct KDTree {
    Node* root;
    KDTree() {
        this->root = NULL;
    }

    // Función para construir el KDTree
    Node* buildTree(vector<point>& points, int depth = 0) {
        if (points.empty()) return NULL;

        // Alternar entre ejes x e y
        int axis = depth % 2;

        // Ordenar puntos por el eje correspondiente
        if (axis == 0) {
            sort(points.begin(), points.end(), [](point a, point b) { return a.x < b.x; });
        } else {
            sort(points.begin(), points.end(), [](point a, point b) { return a.y < b.y; });
        }

        // Encontrar la mediana
        int medianIndex = points.size() / 2;
        point medianPoint = points[medianIndex];

        // Crear nodo
        Node* node = new Node(medianPoint);

        // Dividir los puntos en dos subconjuntos
        vector<point> leftPoints(points.begin(), points.begin() + medianIndex);
        vector<point> rightPoints(points.begin() + medianIndex + 1, points.end());

        // Construir subárboles
        node->left = buildTree(leftPoints, depth + 1);
        node->right = buildTree(rightPoints, depth + 1);

        return node;
    }

    // Función para iniciar la construcción del KDTree
    void build(vector<point>& points) {
        root = buildTree(points);
    }

    // Función para imprimir el KDTree (recorrido en orden)
    void printTree(Node* node) {
        if (node == NULL) return;
        printTree(node->left);
        cout << node->coord.x << " " << node->coord.y << endl;
        printTree(node->right);
    }

    // Función para iniciar la impresión del KDTree
    void print() {
        printTree(root);
    }
};

int main(){
    vector<point> data;
    readData(data, "data2k.csv");
    // //Print data
    // for(int i = 0; i < data.size(); i++){
    //     cout << data[i].x << " " << data[i].y << endl;
    // }
    // Construir el KDTree
    cout<<"KDTree"<<endl;
    KDTree tree;
    tree.build(data);

    // Imprimir el KDTree--
    tree.print();

    return 0;

}
#include <iostream>
#include <vector>
#include <cmath>
#include <ctime>
#include <string>
#include <cstdlib>
#include <fstream>

using namespace std;

vector< vector<float> > read_graph(string filename, int &num_cities);
float tsmindist(vector< vector<float> > &graph);
long nCr(int n, int r);
int subset_no(const string &subset, int r);
string subset(int index, int n, int r);

int main() {
    clock_t start, finish;
    
    // Test input file read function
    int num_cities;
    vector< vector<float> > dists;
    dists = read_graph("tsp.txt", num_cities);
    cout << "Number of cities: " << num_cities << endl;
    cout << "Distance b/w 1 and 25:  " << dists[0][24] << endl;
    cout << "Distance b/w 1 and 2:   " << dists[0][1] << endl;
    cout << "Distance b/w 3 and 3:   " << dists[3][3] << endl;
    cout << "Distance b/w 24 and 24: " << dists[23][24] << endl << endl;
    
    // Answer: 359.333 s
    cout << "Solving Traveling Salesman problem..." << endl;
    start = clock();
    float distance = tsmindist(dists);
    finish = clock();
    cout << "Final answer: " << distance << endl;
    cout << "Running Time: " << 1.0 * (finish - start) / CLOCKS_PER_SEC
         << " s" << endl << endl;

    return 0;
}

vector< vector<float> > read_graph(string filename, int &num_cities) {
    class City {
        public:
            float x, y;
            City(float x, float y) : x(x), y(y) {}
            City() {}
            float distance(City &other) {
                return sqrt(pow(this->x - other.x, 2) + pow(this->y - other.y, 2));
            }
    };
    
    // read file and store distance matrix
    ifstream input_file;
    input_file.open(filename.c_str());
    input_file >> num_cities;
    float x, y;
    City city_list[num_cities];
    for(int i = 0; i < num_cities; ++i) {
        input_file >> x >> y;
        city_list[i] = City(x, y);
    }
    input_file.close();
    
    // calculate distances and return distance matrix: 26246.4
    vector< vector<float> > dists(num_cities, vector<float>(num_cities));
    float distance;
    for(int i = 0; i < num_cities - 1; ++i) {
        for(int j = i; j < num_cities; ++j) {
            if(j == i) {
                dists[i][i] = 0.0;
                continue;
            }
            distance = city_list[i].distance(city_list[j]);
            dists[i][j] = distance;
            dists[j][i] = distance;
        }
    }
    return dists;
}

template<typename T>
class Matrix {
    class matrix_row {
        public:
            matrix_row(int cols) : cols(cols) { this->row = new T[cols]; }
            
            ~matrix_row() { delete[] this->row; }
            
            T& operator[](int col) {
                if(col < 0 || col >= this->cols) exit(1);
                return this->row[col];
            }
            
            const T& operator[](int col) const {
                if(col < 0 || col >= this->cols) exit(1);
                return this->row[col];
            }
            
        private:
            const int cols;
            T *row;
    };
    
    public:        
        Matrix(int rows, int cols) : rows(rows), cols(cols) {
            this->matrix = new matrix_row*[rows];
            for(int i = 0; i < rows; ++i) {
                this->matrix[i] = new matrix_row(cols);
            }
        }
        
        ~Matrix() {
            for(int i = 0; i < this->rows; ++i) {
                delete this->matrix[i];
            }
            delete[] this->matrix;
        }
        
        matrix_row& operator[](int row) { return *(this->matrix[row]); }
        
        const matrix_row& operator[](int row) const { return *(this->matrix[row]); }
               
        int nrows() const { return this->rows; }
        
        int ncols() const { return this->cols; }
               
    private:
        const int rows;
        const int cols;
        matrix_row **matrix;
        
        // make copying and assignment illegal
        Matrix(const Matrix &other) { return *this; }
        Matrix& operator=(const Matrix &rhs) { return *this; }
};

long nCr(int n, int r) {
    long value = 1;
    if(r == 0) return value;
    for(int i = 1; i <= r; ++i) value = value * (n - r + i) / i;
    return value;
}

int subset_no(const string &subset, int r) {
    int n = subset.size();
    if(r == 0 || r == n) {
        return 0;
    } else {
        int zeros = subset.find('1'), number = 0;
        if(zeros == string::npos) exit(1);
        for(int j = 0; j < zeros; ++j) {
            number += nCr(n - j - 1, r - 1);
        }
        return number + subset_no(subset.substr(zeros + 1, string::npos), r - 1);
    }
}

string subset(int index, int n, int r) {
    if(index == 0) {
        string ss_str(n, '0');
        for(int i = 0; i < r; ++i) {
            ss_str[i] = '1';
        }
        return ss_str;
    } else {
        int block, remaining = index, zeros;
        for(int i = 0; i < r; ++i) {
            zeros = 0;            
            while(true) {
                block = nCr(n - zeros - 1, r - i - 1);
                if(block > remaining) {
                    string ss_str(zeros + 1, '0');
                    ss_str[zeros] = '1';
                    return ss_str + subset(remaining, n - zeros - 1, r - 1);
                    break;
                }
                remaining -= block;
                ++zeros;
            }
        }
        return string(n, '0'); // this statement should never be reached
    }
}

float tsmindist(vector< vector<float> > &graph) {   
    // determine upper distance limit
    float ulimit = 0.0;
    for(int i = 0; i < graph.size() - 1; ++i) {
        for(int j = i + 1; j < graph.size(); ++j) {
            if(graph[i][j] > ulimit) ulimit = graph[i][j];
        }
    }
    ulimit = ulimit * graph.size() + 1.0;
    
    // declare matrices and initialize subset size 1 matrix
    Matrix<float> *previous, *current;
    previous = new Matrix<float>(nCr(graph.size() - 1, 12), graph.size() - 1);
    current = new Matrix<float>(nCr(graph.size() - 1, 12), graph.size() - 1);
    cout << "Subset size: 1" << endl;
    cout << "No. Subsets: " << previous->nrows() << endl << endl;
    for(int i = 0; i < previous->nrows(); ++i) {
        for(int j = 0; j < previous->ncols(); ++j) {
            if(i == j) {
                (*previous)[i][i] = graph[0][i+1];
            } else {
                (*previous)[i][j] = ulimit;
            }
        }
    }
    
    // dynamic programming algorithm
    int cp = 2;
    float distance, temp;
    while(cp < graph.size()) { // graph.size()) {
        current = new Matrix<float>(nCr(graph.size() - 1, cp), graph.size() - 1);
        cout << "Subset size: " << cp << endl;
        cout << "No. Subsets: " << current->nrows() << endl << endl;
        for(int i = 0; i < current->nrows(); ++i) {
            string ss_str = subset(i, graph.size() - 1, cp);
            for(int j = 0; j < current->ncols(); ++j) {
                distance = ulimit;
                if(ss_str[j] == '1') {
                    string p_str = ss_str;
                    p_str[j] = '0';
                    int p_ind = subset_no(p_str, cp - 1);
                    for(int k = 0; k < previous->ncols(); ++k) {
                        temp = (*previous)[p_ind][k] + graph[k+1][j+1];
                        if(temp < distance) distance = temp;
                    }
                }
                (*current)[i][j] = distance;                
            }
        }
        ++cp;
        delete previous;
        previous = current; 
    }
    cout << endl;

    // calculate final jump and return distance
    distance = ulimit;
    for(int i = 0; i < current->ncols(); ++i) {
        temp = (*current)[0][i] + graph[i+1][0];
        if(temp < distance) distance = temp;
    }
    delete current;

    return distance;
}

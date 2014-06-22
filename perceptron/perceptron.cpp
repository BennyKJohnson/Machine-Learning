#include <iostream>
#include <fstream>
#include <vector>

using namespace std;

struct data
{
    vector<int> values;
    int desired;
};

data createData(int values[], int expected)
{
    data newData;
    for(int i=0;i<3;i++)
    {
        newData.values[i] = values[i];
    }
    newData.desired = expected;
    return newData;
}

float dot_product(vector<int> values, vector<float> weights)
{
    float sum = 0;
    for(int i=0;i<3;i++)
    {
        sum += values[i] * weights[i];
    }
    return sum;
}
vector<data> readDataFromFile(string filename)
{
    vector<data> training_set;
    ifstream file;
    file.open(filename);
    if (file.good()) {
        int columns =0;
        int sets = 0;
        file >> columns;
        file >> sets;
        for (int s =0; s<sets; s++) {
            data set;
            vector<int> values;
            for (int c=0; c<columns; c++) {
                int value;
                file >> value;
                set.values.push_back(value);
            }
            int expected;
            file >> expected;
            set.desired = expected;
            training_set.push_back(set);
        }
    }
    return training_set;
}
int main()
{
    float threshold = 0;
    float learning_rate = 0;
    vector<float> weights;
    vector<data> training_set;
    cout << "Enter filename of training data: ";
    string filename;
    cin >> filename;
    training_set = readDataFromFile(filename);
    cout << "Enter Threshold: ";
    cin >> threshold;
    cout << "Enter Learning Rate: ";
    cin >> learning_rate;
    for (int i =0; i < training_set[0].values.size(); i++) {
        cout << "Enter Weight " << i << ": ";
        float weight = 0;
        cin >> weight;
        weights.push_back(weight);
    }
    /*
     int value1[3] = {1,0,0};
     int value2[3] = {1,0,1};
     int value3[3] = {1,1,0};
     int value4[3] = {1,1,1};
     
     training_set[0] = createData(value1,1);
     training_set[1] = createData(value2,1);
     training_set[2] = createData(value3,1);
     training_set[3] = createData(value4,0);
     */
    
    while(true)
    {
        cout << "---------------------" << endl;
        int error_count = 0;
        for(int i = 0;i<training_set.size();i++)
        {
            data current = training_set[i];
            for(int e=0;e< weights.size(); e++)
                cout << weights[e] << ", ";
            cout << endl;
            float result = dot_product(current.values, weights) > threshold;
            float error = current.desired - result;
            if(error != 0)
            {
                error_count += 1;
                for(int i=0;i<current.values.size();i++)
                {
                    weights[i] += learning_rate * error * current.values[i];
                }
                
            }
        }
        if(error_count == 0)
            break;
    }
    
}


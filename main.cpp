#include <iostream>
#include "graph.h"
#include <fstream>
#include <iterator>
#include <string>
#include <sstream>
#include <iomanip>

using namespace std;
template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}

int main(int argc, char* argv[]) {

    Graph myComputation;
    myComputation.readGraph(argv[1]);
    //cout<<"outta here"<<endl;
    ifstream infile(argv[2]);
    string line;
    getline(infile,line);
    vector<string>words;
    split1(line,words);
    vector<int>ids;
    for(int i=0;i<words.size();i++) {
        int ID = myComputation.getVariable(words[i]);
        ids.push_back(ID);
    }


    queue<Node *>q;
    vector<int>incSize(myComputation.idCount+1,0);
    myComputation.initTopologicalOrder(q,incSize);

    ofstream myfile,myfile2;
    myfile.open(argv[3]);
    myfile2.open(argv[4]);

    if(myComputation.isCyclic) {
        myfile << "ERROR: COMPUTATION GRAPH HAS CYCLE!" << endl;
        myfile2 << "ERROR: COMPUTATION GRAPH HAS CYCLE!" << endl;

    }
    else {
        for (int i = 0; i < myComputation.inputNodes.size(); i++) {
            int id = myComputation.inputNodes[i];
            myfile2 << "d" << myComputation.name[myComputation.outputNode];
            myfile2 << "/d" << myComputation.name[id] << " ";
        }
        myfile2 << endl;
        myfile << myComputation.name[myComputation.outputNode] << endl;
        getline(infile, line);

        while (line != "") {
            vector<string> words;
            split1(line, words);
            vector<double> inputs(ids.size() + 1);
            for (int i = 0; i < ids.size(); i++) {
                inputs[ids[i]] = stod(words[i]);
            }
            double out = myComputation.forwardPass(inputs);
            myfile << setprecision(30)<< out << endl;
            vector<double> ans = myComputation.backwardPass(out);
            for (int i = 0; i < myComputation.inputNodes.size(); i++) {
                myfile2 << setprecision(30)<<ans[i] << " ";
            }
            myfile2 << endl;
            getline(infile, line);
        }}
        myfile.close();
        myfile2.close();



    return 0;
}
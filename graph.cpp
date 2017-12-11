#include <iostream>
#include <fstream>
#include <vector>
#include <string>
#include <unordered_map>
#include "graph.h"
#include "variable.h"
#include "function.h"
#include <queue>
#include <cmath>
#include <iterator>
#include <sstream>

using namespace std;

template <class Container>
void split1(const string& str, Container& cont)
{
    istringstream iss(str);
    copy(istream_iterator<string>(iss),
         istream_iterator<string>(),
         back_inserter(cont));
}


// helper function that checks whether the given string is number or not.
bool isNumber(const string& s)
{
    char* end = 0;
    double val = strtod(s.c_str(), &end);
    return end != s.c_str() && val != HUGE_VAL;
}

int Graph::getVariable(string inp){
    int res;
    if( isNumber(inp) ){
        double val = stod(inp.c_str());
        idCount++;
        name[idCount] = inp;
        vars[idCount] = new Variable(idCount, inp, val);
        res = idCount;
        type[idCount] = VARIABLE;
    }
    else{
        if(id.find(inp)==id.end()){
            idCount++;
            id[inp] = idCount;
            name[idCount] = inp;
            vars[idCount] = new Variable(idCount, inp);
            res = idCount;
            type[idCount] = VARIABLE;
        }
        else{
            res = id[inp];
        }
    }
     printf("%s -> %d\n",inp.c_str(), res);
    return res;
}

int Graph::getFunction(string fnc){
    idCount++;
    name[idCount] = fnc;
    type[idCount] = FUNCTION;
    Function *f;
     cout << "new Function: " << fnc << endl;
    if(fnc.compare("mult")==0)
        f = new Multiplication(idCount, fnc);
    else if(fnc.compare("add")==0)
        f = new Addition(idCount, fnc);
    else if(fnc.compare("subs")==0)
        f = new Subtraction(idCount, fnc);
    else if(fnc.compare("divide")==0)
        f = new Division(idCount, fnc);

    else if(fnc.compare("sin")==0)
        f = new Sine(idCount, fnc);
    else if(fnc.compare("cos")==0)
        f = new Cosine(idCount, fnc);
    else if(fnc.compare("identity")==0)
        f = new Identity(idCount, fnc);
    else if(fnc.compare("tan")==0)
        f = new Tangent(idCount, fnc);
    else if(fnc.compare("acos")==0)
        f = new ArcCosine(idCount, fnc);
    else if(fnc.compare("asin")==0)
        f = new ArcSine(idCount, fnc);
    else if(fnc.compare("atan")==0)
        f = new ArcTangent(idCount, fnc);
    else if(fnc.compare("exp")==0)
        f = new Exponential(idCount, fnc);
    else if(fnc.compare("log")==0)
        f = new Log(idCount, fnc);
    else if(fnc.compare("log10")==0)
        f = new Log10(idCount, fnc);
    else if(fnc.compare("pow")==0)
        f = new Power(idCount, fnc);
    else if(fnc.compare("sqrt")==0)
        f = new Sqrt(idCount, fnc);
    fncs[idCount] = f;
    return idCount;
}

void Graph::addUnaryFunction(string fnc, string inp, string out){

    int fId = getFunction(fnc);
    int inpId = getVariable(inp);
    int outId = getVariable(out);
    fncs[fId]->addInput(vars[inpId]);
    fncs[fId]->setOutput(vars[outId]);

    vars[inpId]->addTo(fncs[fId]);
    vars[outId]->setFrom(fncs[fId]);
}

void Graph::addBinaryFunction(string fnc, string inp1, string inp2, string out){
    int fID = getFunction(fnc);
    int inpID1 = getVariable(inp1);
    int inpID2 = getVariable(inp2);
    int outID = getVariable(out);
    fncs[fID]->addInput(vars[inpID1]);
    fncs[fID]->addInput(vars[inpID2]);
    fncs[fID]->setOutput(vars[outID]);

    vars[inpID1]->addTo(fncs[fID]);
    vars[inpID2]->addTo(fncs[fID]);
    vars[outID]->setFrom(fncs[fID]);

}

void Graph::addAssignment(string lvalue, string rvalue) {
    int lvalID = getVariable(lvalue);
    int rvalID = getVariable(rvalue);
    int fID = getFunction("identity");

    fncs[fID]->addInput(vars[rvalID]);
    fncs[fID]->setOutput(vars[lvalID]);

    vars[lvalID]->setFrom(fncs[fID]);
    vars[rvalID]->addTo(fncs[fID]);

}

void Graph::readGraph(string fileName){
    ifstream infile(fileName);
    string line;
    getline(infile,line);

    while(line!=""){
        vector<string> words;
        split1(line,words);
        //taking input nodes
        if(words[0].compare("input")==0){
            int myId = getVariable(words[1]);
            inputNodes.push_back(myId);
        }
        //taking output node
        else if(words[0].compare("output")==0){
            int myId = getVariable(words[1]);
            outputNode = myId;
        }
        else{
            //binary function
            if(words.size()==5){
                addBinaryFunction(words[2],words[3],words[4],words[0]);
            }
            //unary function
            else if(words.size()==4){
                addUnaryFunction(words[2],words[3],words[0]);
            }
            //assignment
            else if(words.size()==3){
                addAssignment(words[0],words[2]);
            }
        }

       getline(infile,line);
    }

}

void Graph::initTopologicalOrder(queue<Node *> &q, vector<int> &incSizes){
    for(int i=1;i<idCount+1;i++){
        if(type[i]==VARIABLE){
            if(vars[i]->from!=nullptr)
            incSizes[i] = 1;
            else{
                q.push(vars[i]);
            }
        }
        else{
            incSizes[i] = fncs[i]->inputs.size();
        }
    }
    while(!q.empty()){
        int nowID = q.front()->id;
        //cout<< "NowID: "<<nowID<<endl;
        forwardPassOrder.push_back(nowID);
        q.pop();
        if(type[nowID]==VARIABLE){
            Variable *vNow = vars[nowID];
            for(int i=0;i<vNow->to.size();i++){
                int checkID = vNow->to[i]->id;
                if(--incSizes[checkID]==0)
                    q.push(fncs[checkID]);

            }
        }
        else{
            Function *fNow = fncs[nowID];
            int checkID = fNow->output->id;
            if(--incSizes[checkID]==0) {
                q.push(vars[checkID]);
            }
        }



    }
}

bool Graph::isCyclic(){
}

double Graph::forwardPass(vector<double> inputValues){
    for(int i=1;i<inputValues.size()+1;i++)
        vars[i]->value = inputValues[i];
    for(int i=0;i<forwardPassOrder.size();i++){
        if(type[forwardPassOrder[i]]==FUNCTION)
        fncs[forwardPassOrder[i]]->doForward();
    }
    return vars[outputNode]->value;

}

vector<double> Graph::backwardPass(double output){
    vars[outputNode]->derivative=1;
    for(int i=1;i<idCount+1;i++){
        if(type[i]==VARIABLE && i!=outputNode){
            vars[i]->derivative=0;
    }}
    for(int i=forwardPassOrder.size()-1;i>=0;i--){
        if(type[forwardPassOrder[i]]==FUNCTION)
        fncs[forwardPassOrder[i]]->doBackward();

    }
    vector<double>res(inputNodes.size(),0);
    for(int i=0;i<inputNodes.size();i++) {
        //cout<<"Name is : "<<name[inputNodes[i]]<<" ";
        res[i] = vars[inputNodes[i]]->derivative;
        cout<<res[i]<<" ";
    }
    cout<<endl;
    return res;
};
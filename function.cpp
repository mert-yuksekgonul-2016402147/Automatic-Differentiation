#include "function.h"
#include "math.h"
#include <iostream>


using namespace std;
#define PI 3.14159265

Function::Function(int _id, string _name) {
    id = _id;
    name = _name;
}
Function::Function() {
    id = 0;
    name = "";
}
Multiplication::Multiplication(int _id, string _name) {
    id=_id;
    name=_name;
}
Addition::Addition(int _id, string _name) {
    id=_id;
    name=_name;
}
Division::Division(int _id, string _name) {
    id=_id;
    name=_name;
}
Power::Power(int _id, string _name) {
    id=_id;
    name=_name;
}
Exponential::Exponential(int _id, string _name) {
    id=_id;
    name=_name;
}
Sine::Sine(int _id, string _name) {
    id=_id;
    name=_name;
}
ArcSine::ArcSine(int _id, string _name) {
    id=_id;
    name=_name;
}
ArcCosine::ArcCosine(int _id, string _name) {
    id=_id;
    name=_name;
}
ArcTangent::ArcTangent(int _id, string _name) {
    id=_id;
    name=_name;
}
Log10::Log10(int _id, string _name) {
    id=_id;
    name=_name;
}
Sqrt::Sqrt(int _id, string _name) {
    id=_id;
    name=_name;
}
Log::Log(int _id, string _name) {
    id=_id;
    name=_name;
}
Identity::Identity(int _id, string _name) {
    id=_id;
    name=_name;
}
Cosine::Cosine(int _id, string _name) {
    id=_id;
    name=_name;
}
Tangent::Tangent(int _id, string _name) {
    id=_id;
    name=_name;
}

Subtraction::Subtraction(int _id, string _name) {
    id=_id;
    name=_name;
}


void Multiplication::doForward() {
    this->output->value = this->inputs[0]->value * this->inputs[1]->value;
    /*cout<<"Done forward with "<<this->inputs[0]->name<<" "<<this->inputs[0]->value;
    cout<<" and "<<this->inputs[1]->name<<" "<<this->inputs[1]->value;
    cout<<" passed to "<<output->name<<" is "<< output->value<<endl;
*/

}
void Multiplication::doBackward() {
    //cout<<this->name<<endl;
    //cout<<"Input1 : "<<inputs[0]->name<<" "<< inputs[0]->value<<endl;
      //  cout<<" Input2: "<<inputs[1]->name<<" "<<inputs[1]->value<<endl;

    //cout<<"Output :"<<output->name<<" "<<output->derivative<<endl;
    this->inputs[0]->derivative += this->output->derivative*(this->inputs[1]->value);
    this->inputs[1]->derivative += this->output->derivative*(this->inputs[0]->value);
}

void Subtraction::doForward() {
    this->output->value = this->inputs[0]->value - this->inputs[1]->value;
}
void Subtraction::doBackward() {//cout<<this->name<<endl;
    //cout<<"Input1 : "<<inputs[0]->name<<" "<< inputs[0]->value<<endl;
    //cout<<" Input2: "<<inputs[1]->name<<" "<<inputs[1]->value<<endl;

    //cout<<"Output :"<<output->name<<" "<<output->derivative<<endl;
    this->inputs[0]->derivative += this->output->derivative;
    this->inputs[1]->derivative += -this->output->derivative;
}


void Division::doForward() {
    this->output->value = this->inputs[0]->value / this->inputs[1]->value;
}

void Division::doBackward() {//cout<<this->name<<endl;
    //cout<<"Input1 : "<<inputs[0]->name<<" "<< inputs[0]->value<<endl;
    //cout<<" Input2: "<<inputs[1]->name<<" "<<inputs[1]->value<<endl;
    //cout<<"Output :"<<output->name<<" "<<output->derivative<<endl;

    this->inputs[0]->derivative += this->output->derivative*(1/(this->inputs[1]->value));
    this->inputs[1]->derivative += this->output->derivative*(-this->inputs[0]->value/pow(this->inputs[1]->value,2));
}


void Addition::doForward() {
    this->output->value = this->inputs[0]->value + this->inputs[1]->value;
}
void Addition::doBackward() {//cout<<this->name<<endl;
    //cout<<"Input1 : "<<inputs[0]->name<<" "<< inputs[0]->value<<endl;
    //cout<<" Input2: "<<inputs[1]->name<<" "<<inputs[1]->value<<endl;

    //cout<<"Output :"<<output->name<<" "<<output->derivative<<endl;
    this->inputs[0]->derivative += this->output->derivative;
    this->inputs[1]->derivative += this->output->derivative;
}

void Sine::doForward() {
    this->output->value = sin(this->inputs[0]->value);
}
void Sine::doBackward() {
    this->inputs[0]->derivative += this->output->derivative*(cos(this->inputs[0]->value));
}

void Cosine::doForward() {
    this->output->value = cos(this->inputs[0]->value);
}

void Cosine::doBackward() {
    //cout<<this->name<<endl;
    //cout<<"Input1 : "<<inputs[0]->name<<" "<< inputs[0]->value<<endl;

    //cout<<"Output :"<<output->name<<" "<<output->derivative<<endl;
    this->inputs[0]->derivative += this->output->derivative*(-sin(this->inputs[0]->value));
}

void Tangent::doForward() {
    this->output->value = tan(this->inputs[0]->value);
}

void Tangent::doBackward(){
    this->inputs[0]->derivative +=this->output->derivative*( 1 + pow(tan(this->inputs[0]->value),2));
};

void Identity::doForward() {
    this->output->value = this->inputs[0]->value;
}
void Identity::doBackward() {
    this->inputs[0]->derivative += this->output->derivative;
}

void Power::doForward() {
    this->output->value = pow(this->inputs[0]->value,this->inputs[1]->value);
}
void Power::doBackward() {
    double a = this->inputs[0]->value;
    double b = this->inputs[1]->value;
    this->inputs[0]->derivative += this->output->derivative*(b*pow(a,b-1));
    this->inputs[1]->derivative += this->output->derivative*(pow(a,b)*log(a));
}
void Log10::doForward() {
    this->output->value = log10(this->inputs[0]->value);
}
void Log10::doBackward() {
    this->inputs[0]->derivative += this->output->derivative*(1/(this->inputs[0]->value * log(10)));
}
void Log::doForward() {
    this->output->value = log(this->inputs[0]->value);
}
void Log::doBackward() {
    this->inputs[0]->derivative += this->output->derivative*(1/(this->inputs[0]->value));
}
void Sqrt::doForward() {
    this->output->value = sqrt(this->inputs[0]->value);
}
void Sqrt::doBackward() {

   // cout<<this->name<<endl;
//    cout<<"Input1 : "<<inputs[0]->name<<" "<< inputs[0]->value<<endl;

  //  cout<<"Output :"<<output->name<<" "<<output->derivative<<endl;
    double x = this->inputs[0]->value;
    //cout<<this->inputs[0]->derivative<<endl;
    this->inputs[0]->derivative += (this->output->derivative)/(2*sqrt(x));
    //cout<<this->inputs[0]->derivative<<endl;
}
void ArcSine::doForward() {
    this->output->value = asin(this->inputs[0]->value);
}

void ArcSine::doBackward() {
    //cout<<"calculating backwards of "<<this->name<<" from node "<<this->output->name<<" ";
    //cout<<"derivative is "<<output->derivative<<endl;
    double x = this->inputs[0]->value;
    this->inputs[0]->derivative += this->output->derivative*(1/(sqrt(1-pow(x,2))));
}

void ArcCosine::doForward() {
    this->output->value = acos(this->inputs[0]->value);
}
void ArcCosine::doBackward() {
    double x = this->inputs[0]->value;
    this->inputs[0]->derivative += this->output->derivative*(-1/(sqrt(1-pow(x,2))));
}

void ArcTangent::doForward() {
    this->output->value = atan(this->inputs[0]->value);
}
void ArcTangent::doBackward() {
    double x = this->inputs[0]->value;
    this->inputs[0]->derivative += this->output->derivative*(1/(1+pow(x,2)));
}

void Exponential::doForward() {
    this->output->value = exp(this->inputs[0]->value);
}
void Exponential::doBackward() {
    this->inputs[0]->derivative += this->output->derivative*(exp(this->inputs[0]->value));
}



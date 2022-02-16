#include <iostream>
#include "fstream"
#include <vector>

using namespace std;

string readingFile(){
    ifstream file("/Users/dmitrij/CLionProjects/compiling-the-for-loop-to-while-prod/text.txt");
    string str;
    string content; //хранится прочтенный фаил
    while (getline(file, str)) {
        content += str;
        content.push_back('\n');
    };
    return content;
}

void creatureReadyFile( const string& text) {
    ofstream out;
    out.open("/Users/dmitrij/CLionProjects/compiling-the-for-loop-to-while-prod/for-while.txt", ios::app);
    out << text << endl;
};

struct Condition {
     string initialize;
     string condition;
     string increment;
};


Condition parserCondition (string conditionBlocFor){
    Condition elementConditionBlock;
    int j = 3;
    while ( j != 0) {
        string strCondition = conditionBlocFor;
        switch (j) {
            case 3: elementConditionBlock.initialize = strCondition.substr(0 ,strCondition.find(';'));
                break;
            case 2: elementConditionBlock.condition = strCondition.substr(0 ,strCondition.find(';'));
                break;
            case 1: elementConditionBlock.increment = strCondition;
                break;
        }
        conditionBlocFor.erase(0, strCondition.find(';') + 1);
        j--;
    };
    return elementConditionBlock;
};

string parserBody(const string& body) {
    return body.substr(body.find('{') + 1, body.find('}') - body.find('{') - 1 );
};

string creatureWhileFromFor(const Condition& condition, const string& body ) {
    return "int " + condition.initialize + "\n" + "while(" + condition.condition + " ){" + body + condition.increment + "\n}\n";
};

string parser( const string& i ) {
    string finalText, initialize, condition, increment, bodyBlocFor;
    string strCondition = i;
    string conditionBlocFor = strCondition.substr(i.find('(') + 1, i.find(')')-i.find('(') - 1 );
    return creatureWhileFromFor(parserCondition(conditionBlocFor), parserBody(i));
};

//void checkCode(const string& code) {
//    string str = code;
//    string index;
//    int startElement = str.find("for(");
//    int end = str.find(')');
//    int endElement = str.find('}');
//
//    for (int i = 23; i <= str.length(); i++) {
//        if((i > end)  && (str[i] == ';')){
//            index = str[i];
//            break;
//        };
//    }
//    if ((startElement  == -1) || (endElement == -1)){
//        creatureReadyFile(str.substr(0, str.length()));
//    }
//};

void processingText( string content) {
    string str;
    while (content.length() != 0) {
        str = content;

//        checkCode(str);

        int startElement = str.find("for(");
        int end = str.find(')');
        int endElement = str.find('}');

        if ((startElement  == -1) || (endElement == -1)){
            creatureReadyFile(str.substr(0, str.length()));
            break;
        }

        creatureReadyFile(str.substr(0, startElement));

        string forelement = parser(str.substr(startElement, endElement  - startElement + 1));

        creatureReadyFile(forelement);

        content.erase(0, endElement + 1);
    }
}


int main() {
    string content = readingFile();

    processingText(content);

    return 0;
}

#include <iostream>
#include "fstream"

using namespace std;

string readingFile(){
    ifstream file("/Users/dmitrij/CLionProjects/compiling-the-for-loop-to-while-prod/text.txt");
    string str;
    string content;
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
            case 3: {
                elementConditionBlock.initialize = strCondition.substr(0 ,strCondition.find(';'));
//                if (elementConditionBlock.initialize.find(',') != -1) {
//                    elementConditionBlock.initialize = elementConditionBlock.initialize.replace(strCondition.find(','), 2 , ";\n   ");
//                }
                break;
            }
            case 2: {
                elementConditionBlock.condition = strCondition.substr(0 ,strCondition.find(';'));
                break;
            }
            case 1: {
                if (strCondition.find(',') == -1){
                    elementConditionBlock.increment = strCondition;
                } else {
                    elementConditionBlock.increment = strCondition.erase(strCondition.insert(
                            strCondition.find(','), ";\n\t\t").find(','), 2);
                }
                break;
            }
        }
        conditionBlocFor.erase(0, strCondition.find(';') + 2);
        j--;
    };
    return elementConditionBlock;
};

string parserBody(const string& body) {
    return body.substr(body.find('{') + 1, body.find('}') - body.find('{') - 1 );
};

string creatureWhileFromFor(const Condition& condition, string body, const string& typeLoop ) {
    string readyLoop;
    if (typeLoop == "body in one line") {
        body.erase( body.find('\n'), 1);
        readyLoop = "\t" + condition.initialize + ";\n" +
                "\twhile( " + condition.condition +
                " ){\n   " + body + "\t\t" +
                condition.increment + ";\n\t}";
    } else {
        readyLoop = "\t" + condition.initialize +
                ";\n" + "\twhile( " + condition.condition +
                " ){\t\t" + body + "\t\t" +
                condition.increment + ";\n\t}";
    }
    return readyLoop;
};

string parser( const string& i ) {
    return creatureWhileFromFor(parserCondition(i.substr(
            i.find('(') + 1,
            i.find(')')-i.find('(') - 1 )),
            parserBody(i),
            "\t\t");
};

string checkCode(string str) {
    if (str.find("for(")  == -1){
        creatureReadyFile(str.substr(0, str.length()));
        str.clear();
    } else {
        creatureReadyFile(str.substr(0, str.find("for(")));
        str.erase(0, str.find("for("));
    }
    if (str.find("for(") < str.find(')') ) {
        for (int i = str.find(')') + 1; i <= str.find('\n'); i++) {
            switch (str[i]) {
                case ';': {
                    //TODO Массив без тела
                    creatureReadyFile(creatureWhileFromFor(parserCondition(
                            str.substr(str.find('(') + 1,
                            str.find(')') - str.find('(') - 1 )),
                            "\n",
                            ""
                    ));
                    i = str.find('\n') + 1;
                    str.erase(0, str.find('\n') + 1);
                    break;
                }
                case '{': {
                    //TODO Массив с телом
                    creatureReadyFile(parser(str.substr(
                            str.find("for("),
                            str.find('}')  - str.find("for(") + 1
                    )));
                    str.erase(0, str.find('}') + 1);
                    break;
                }
                case '\n': {
                    //TODO Массив с телом в одну строчку
                    Condition conditional = parserCondition(
                            str.substr(str.find('(') + 1,
                            str.find(')') - str.find('(') - 1
                    ));
                    str.erase(0, str.find('\n') + 2);
                    creatureReadyFile(creatureWhileFromFor(
                            conditional,
                            str.substr(0, str.find('\n') + 2 ),
                            "body in one line"
                    ));
                    str.erase(0, str.find('\n') + 2 );
                    break;
                }
            }
        }
    }
    return str;
};

void processingText(  string content) {
    while (content.length() != 0) {
        content = checkCode(content);
    }
}

int main() {
    string content = readingFile();
    processingText(content);
    cout << "Success" << endl;
    return 0;
}
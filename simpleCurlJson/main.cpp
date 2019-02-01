#include <json.h>
#include <iostream>
#include <fstream>
using namespace std;

void Indent(ostream &ofs, int indent)
{
    for (int i = 0; i < indent; i++)
        ofs << ' ';
}

void MyPrint(ostream &ofs, const Json::Value &val, int indent = 0)
{
    switch (val.type())
    {
    case Json::nullValue:
        ofs << "null";
        break;
    case Json::booleanValue:
        ofs << (val.asBool() ? "true" : "false");
        break;
    case Json::intValue:
        ofs << val.asLargestInt();
        break;
    case Json::uintValue:
        ofs << val.asLargestUInt();
        break;
    case Json::realValue:
        ofs << val.asDouble();
        break;
    case Json::stringValue:
        ofs << '"' << val.asString() << '"';
        break;
    case Json::arrayValue:
    {
        Json::ArrayIndex size = val.size();
        if (size == 0)
            ofs << "[]";
        else
        {
            ofs << "[\n";
            int newIndent = indent + 4;
            for (Json::ArrayIndex i = 0; i < size; i++)
            {
                Indent(ofs, newIndent);
                MyPrint(ofs, val[i], newIndent);
                ofs << (i + 1 == size ? "\n" : ",\n");
            }
            Indent(ofs, indent);
            ofs << ']';
        }
        break;
    }
    case Json::objectValue:
    {
        if (val.empty())
            ofs << "{}";
        else
        {
            ofs << "{\n";
            int newIndent = indent + 4;
            vector<string> keys = val.getMemberNames();
            for (size_t i = 0; i < keys.size(); i++)
            {
                Indent(ofs, newIndent);
                const string &key = keys[i];
                ofs << '"' << key << '"' << " : ";
                MyPrint(ofs, val[key], newIndent);
                ofs << (i + 1 == keys.size() ? "\n" : ",\n");
            }
            Indent(ofs, indent);
            ofs << '}';
        }
        break;
    }
    default:
        cerr << "Wrong type!" << endl;
        exit(0);
    }
}
void MyPrintFind(ostream &ofs, const Json::Value &val,const std::string& keyName ,int indent=0)
{
    switch (val.type())
    {
    case Json::nullValue:
        ofs << "null";
        break;
    case Json::booleanValue:
        ofs << (val.asBool() ? "true" : "false");
        break;
    case Json::intValue:
        ofs << val.asLargestInt();
        break;
    case Json::uintValue:
        ofs << val.asLargestUInt();
        break;
    case Json::realValue:
        ofs << val.asDouble();
        break;
    case Json::stringValue:
        ofs << '"' << val.asString() << '"';
        break;
    case Json::arrayValue:
    {
        Json::ArrayIndex size = val.size();
        if (size == 0)
            ofs << "[]";
        else
        {
            ofs << "[\n";
            int newIndent = indent + 4;
            for (Json::ArrayIndex i = 0; i < size; i++)
            {
                Indent(ofs, newIndent);
                MyPrintFind(ofs, val[i],keyName, newIndent);
                ofs << (i + 1 == size ? "\n" : ",\n");
            }
            Indent(ofs, indent);
            ofs << ']';
        }
        break;
    }
    case Json::objectValue:
    {
        if (val.empty())
            ofs << "{}";
        else
        {
            ofs << "{\n";
            int newIndent = indent + 4;
            vector<string> keys = val.getMemberNames();
            for (size_t i = 0; i < keys.size(); i++)
            {
                const string &key = keys[i];
                if(key.compare(keyName) != 0 ) {
                    continue;
                }
                Indent(ofs, newIndent);
               
                ofs << '"' << key << '"' << " : ";
                MyPrintFind(ofs, val[key],keyName, newIndent);
                ofs << (i + 1 == keys.size() ? "\n" : ",\n");
            }
            Indent(ofs, indent);
            ofs << '}';
        }
        break;
    }
    default:
        cerr << "Wrong type!" << endl;
        exit(0);
    }
}

void example()
{
    ifstream ifs("alice.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj); // reader can also read strings
    cout << "Book: " << obj["book"].asString() << endl;
    cout << "Year: " << obj["year"].asUInt() << endl;
    const Json::Value &characters = obj["characters"]; // array of characters
    for (int i = 0; i < characters.size(); i++)
    {
        cout << "    name: " << characters[i]["name"].asString();
        cout << " chapter: " << characters[i]["chapter"].asUInt();
        cout << endl;
    }
}
void example2()
{
    ifstream ifs("luke.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj); // reader can also read strings
    const Json::Value &data = obj["results"];
    MyPrint(cout, data);
}
void findExample(const string& root, const string &str)
{
    ifstream ifs("luke.json");
    Json::Reader reader;
    Json::Value obj;
    reader.parse(ifs, obj); // reader can also read strings
    const Json::Value &data = obj[root];
    cout << "calling MyPrintFind()" << endl;
    MyPrintFind(cout, data,str);

  
}

int main(int argc, char *argv[])
{
    example();
    example2();
    cout << "Search test" << endl;
    findExample("results","films");

}
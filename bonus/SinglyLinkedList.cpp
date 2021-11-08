#include <iostream>
#include <list>
#include <string>

using namespace std;

void printList(list<int> &list)
{
    for (auto it = list.begin(); it != list.end(); it++)
    {
        cout << *it << "-->";
    }
    cout << "null";
}

int main()
{
    string command;
    list<int> list;
    while (command.compare("exit") != 0)
    {
        cin >> command;
        if (command.compare("addBack") == 0)
        {
            int value;
            cin >> value;
            list.push_back(value);
        }
        else if (command.compare("addFront") == 0)
        {
            int value;
            cin >> value;
            list.push_front(value);
        }
        else if (command.compare("addIndex") == 0)
        {
           int index, value;
            cin >> index >> value;
            auto it = list.begin();
            for (int i = 0; i < index; i++)
                it++;
            list.insert(it, value);
        }
        else if (command.compare("deleteIndex") == 0)
        {
            int index;
            cin >> index;
            auto it = list.begin();
            for (int i = 0; i < index; i++)
                it++;
            list.erase(it);
        }
    }
    
    printList(list);

    return 0;
}
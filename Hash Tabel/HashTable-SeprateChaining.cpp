#include <bits/stdc++.h>
using namespace std;

template <class Key, class Value>
class Node
{
public:
    Key key;
    Value value;
    Node *next;
    Node(Key _key, Value _value, Node *_next = NULL)
    {
        key = _key;
        value = _value;
        next = _next;
    }
};

template <class Key, class Value>
class HashTable
{
private:
    vector<Node<Key, Value> *> table;
    size_t capacity, size;
    size_t (*Hash)(Key);

    int hashCode(Key key)
    {
        return (((int)Hash(key)) % capacity);
    }

    void reSize(size_t newCapacity)
    {
        capacity = newCapacity;
        vector<Node<Key, Value> *> temp(newCapacity, NULL);
        for (size_t i = 0; i < table.size(); ++i)
        {
            for (Node<Key, Value> *node = table[i]; node != NULL;)
            {
                size_t index = hashCode(node->key);
                temp[index] = new Node<Key, Value>(node->key, node->value, temp[index]);

                Node<Key, Value> *tempNode = node;
                node = node->next;
                delete tempNode;
            }
        }
        table = temp;
    }

public:
    HashTable()
    {
        capacity = 4;
        table = vector<Node<Key, Value> *>(capacity, NULL);
        size = 0;

        Hash = [](Key key) -> size_t
        {
            hash<Key> hashValue;
            return hashValue(key);
        };
    }

    HashTable(int _capacity)
    {
        if (_capacity < 4)
            capacity = 4;
        else
            capacity = _capacity;

        table = vector<Node<Key, Value> *>(capacity, NULL);
        size = 0;

        Hash = [](Key key) -> size_t
        {
            hash<Key> hashValue;
            return hashValue(key);
        };
    }

    HashTable(size_t (*func)(Key))
    {
        capacity = 4;
        table = vector<Node<Key, Value> *>(capacity, NULL);
        size = 0;
        Hash = func;
    }

    HashTable(int _capacity, size_t (*func)(Key))
    {
        if (_capacity < 4)
            capacity = 4;
        else
            capacity = _capacity;
        table = vector<Node<Key, Value> *>(capacity, NULL);
        size = 0;
        Hash = func;
    }

    size_t Size()
    {
        return size;
    }

    void clear()
    {
        for (size_t i = 0; i < capacity; ++i)
        {
            for (Node<Key, Value> *node = table[i]; node != NULL;)
            {
                Node<Key, Value> *temp = node;
                node = node->next;
                delete temp;
            }
        }
        capacity = 4;
        size = 0;
        table = vector<Node<Key, Value> *>(capacity, NULL);
    }

    bool isEmpty()
    {
        return size == 0;
    }

    void put(Key key, Value value)
    {
        if (size >= 5 * capacity)
            reSize(2 * capacity);

        size_t index = hashCode(key);

        for (Node<Key, Value> *node = table[index]; node != NULL; node = node->next)
        {
            if (node->key == key)
            {
                node->value = value;
                return;
            }
        }
        table[index] = new Node<Key, Value>(key, value, table[index]);
        size++;
    }

    Value get(Key key)
    {
        size_t index = hashCode(key);
        for (Node<Key, Value> *node = table[index]; node != NULL; node = node->next)
        {
            if (node->key == key)
                return node->value;
        }
        return Value();
    }

    void remove(Key key)
    {
        size_t index = hashCode(key);

        Node<Key, Value> *prev = NULL;
        for (Node<Key, Value> *node = table[index]; node != NULL; node = node->next)
        {
            if (node->key == key)
            {
                size--;
                if (prev == NULL)
                {
                    delete node;
                    table[index] = NULL;
                }
                else
                {
                    Node<Key, Value> *temp = node;
                    prev->next = node->next;
                    delete temp;
                }
                break;
            }
            prev = node;
        }
        if (capacity > 4 && size <= 2 * capacity) // size / capacity <= 2
            reSize(capacity / 2);
    }

    bool contains(Key key)
    {
        size_t index = hashCode(key);

        for (Node<Key, Value> *node = table[index]; node != NULL; node = node->next)
        {
            if (node->key == key)
                return true;
        }
        return false;
    }

    vector<pair<Key, Value>> Keys()
    {
        vector<pair<Key, Value>> keys;
        for (size_t i = 0; i < table.size(); ++i)
        {
            for (Node<Key, Value> *node = table[i]; node != NULL;)
            {
                keys.push_back({node->key, node->value});
                node = node->next;
            }
        }
        return keys;
    }

    ~HashTable()
    {
        for (size_t i = 0; i < table.size(); ++i)
        {
            for (Node<Key, Value> *node = table[i]; node != NULL;)
            {
                Node<Key, Value> *tempNode = node;
                node = node->next;
                delete tempNode;
            }
        }
    }
};

int main()
{

    return 0;
}
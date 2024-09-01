struct Node
{
    Node *links[2];
    ll cntEndWith = 0;
    ll cntPrefix = 0;

    bool containsKey(ll bit)
    {
        return (links[bit] != NULL);
    }
 
    Node *get(ll bit)
    {
        return links[bit];
    }
 
    void put(ll bit, Node *node)
    {
        links[bit] = node;
    }
 
    void increaseEnd()
    {
        cntEndWith++;
    }
 
    void increasePrefix()
    {
        cntPrefix++;
    }
 
    void deleteEnd()
    {
        cntEndWith--;
    }
 
    void reducePrefix()
    {
        cntPrefix--;
    }
};
 
// Define a class for the
// trie data structure
class Trie
{
private:
    Node *root;
 
public:
    Trie()
    {
        root = new Node();
    }
 
    void insert(ll num)
    {
        Node *node = root;
        for (ll i = 31; i >= 0; i--)
        {
            ll bit = (num >> i) & 1;
            if (!node->containsKey(bit))
            {
                node->put(bit, new Node());
            }
            node = node->get(bit);
            node->increasePrefix();
        }
        node->increaseEnd();
    }
 
    ll getMax(ll num)
    {
        Node *node = root;
 
        ll maxNum = 0;
 
        for (ll i = 31; i >= 0; i--)
        {
            ll bit = (num >> i) & 1;
 
            if (node->containsKey(1 - bit) && node->get(1 - bit)->cntPrefix > 0)
            {
 
                maxNum |= (1 << i);
 
                node = node->get(1 - bit);
            }
            else
            {
                node = node->get(bit);
            }
        }
 
        // Return the maximum XOR value
        return maxNum;
    }
 
    void erase(ll num)
    {
        Node *node = root;
        for (ll i = 31; i >= 0; i--)
        {
            ll bit = (num >> i) & 1;
            if (node->containsKey(bit))
            {
                node = node->get(bit);
                node->reducePrefix();
            }
        }
        node->deleteEnd();
    }
};

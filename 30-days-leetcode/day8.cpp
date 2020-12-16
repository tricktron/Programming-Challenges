#include <iostream>
#include <vector>

using namespace std;
 struct ListNode {
     int val;
     ListNode *next;
     ListNode(int x) : val(x), next(NULL) {}
};

class Solution {
public:
    ListNode* middleNode(ListNode* head) {
        vector<ListNode*> nodes;
        while(head->next != NULL) {
            nodes.push_back(head);
            head = head->next;
        }
        return nodes[nodes.size()/2];
    }
};

int main() {

}
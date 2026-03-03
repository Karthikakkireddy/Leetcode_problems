/*
    Problem Link - https://leetcode.com/problems/odd-even-linked-list/
    Difficulty - Medium
    Odd Even Linked List

    Goal:
    Rearrange the list so that:
    - All nodes at odd positions come first
    - Then all nodes at even positions
    - Preserve original relative order

    Example:
    1 → 2 → 3 → 4 → 5
    becomes
    1 → 3 → 5 → 2 → 4


    Idea:
    Maintain two separate chains:
    - odd list
    - even list

    Walk through the list:
    - Link odd nodes together
    - Link even nodes together

    Finally connect:
    last odd → head of even list


    Time Complexity: O(N)
    - Each node is visited once.
    - Each pointer reassignment happens once per node.

    Space Complexity: O(1)
    - No extra data structures.
    - Only pointer manipulation.


    Edge Cases:
    ✔ empty list
    ✔ single node
    ✔ two nodes
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode() : val(0), next(nullptr) {}
 *     ListNode(int x) : val(x), next(nullptr) {}
 *     ListNode(int x, ListNode *next) : val(x), next(next) {}
 * };
 */
class Solution {
public:
    ListNode* oddEvenList(ListNode* head) 
    {
        if(head == NULL || head -> next == NULL)
        {
            return head;
        }  

        ListNode* odd = head;
        ListNode* evenHead = head -> next;
        ListNode* even = evenHead;


        while(even!= NULL && even -> next != NULL)
        {
            odd -> next = even -> next; // odd -> next = odd -> next -> next;
            odd = odd -> next; 
            even -> next = odd -> next; // even -> next = even -> next -> next;
            even = even -> next;
        }
        odd -> next = evenHead;

        return head;
    }
};
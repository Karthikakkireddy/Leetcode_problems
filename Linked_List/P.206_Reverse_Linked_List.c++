/*
    Problem Link - https://leetcode.com/problems/reverse-linked-list/
    TC- O(n)
    SC- O(1) -> Three variables/pointers used thus it's a constant space.
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
    ListNode* reverseList(ListNode* head) {
        if(head == NULL || head -> next == NULL)
        {
            return head;
        }

        ListNode* front = NULL;
        ListNode* prev = NULL;

        while(head != NULL)
        {
            front = head -> next;
            head -> next = prev; 
            prev = head;
            head = front;
        }

        return prev;
    }
};
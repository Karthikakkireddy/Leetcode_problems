/*
    Problem Link - https://leetcode.com/problems/delete-the-middle-node-of-a-linked-list/
*/

/*
   
    Approach: Tortoise and Hare (Slow & Fast Pointer)

    Idea:
    - Use two pointers:
        slow -> moves 1 step at a time
        fast -> moves 2 steps at a time
    - When fast reaches the end,
      slow will be at the middle node.

    But since we need to DELETE the middle,
    we must also track the node BEFORE slow.
    So we maintain:
        slowPrev -> previous of slow

    ------------------------------------------------------------

    Edge Case:
    - If the list has only one node,
      deleting the middle means returning NULL.

    ------------------------------------------------------------

    Why This Works:
    - Fast pointer moves twice as fast as slow.
    - When fast reaches the end:
        slow has covered exactly half the distance.
    - Therefore slow points to the middle node.
    - slowPrev helps us reconnect the list by skipping slow.

    ------------------------------------------------------------

    Time Complexity:
    - O(N) → We traverse the list once.

    Space Complexity:
    - O(1) → No extra data structures used.

    ------------------------------------------------------------

    Important Detail:
    - Middle is defined as floor(n / 2) index (0-based).
    - For even length lists,
      this naturally deletes the second middle node,
      which matches the problem requirement.

    ------------------------------------------------------------

    Cleanliness Observation:
    - You directly accessed head->next without checking if head is NULL.
      In LeetCode it's guaranteed non-empty, but in real systems,
      you should guard against nullptr to avoid segmentation fault.
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
    ListNode* deleteMiddle(ListNode* head) {
        
        if(head-> next == NULL)
            return NULL;

        ListNode* slowPrev = NULL;
        ListNode* slow = head; 
        ListNode* fast = head;

        while(fast != NULL && fast -> next != NULL)
        {
            slowPrev = slow;
            slow = slow -> next; 
            fast = fast -> next -> next; 
        }


        slowPrev -> next = slow -> next; 
        delete slow;

        return head;
    }
};



/*
    Problem:
    Delete the middle node of a singly linked list and return the head.

    ------------------------------------------------------------

    Approach: Optimized Slow & Fast Pointer (No slowPrev)

    Key Idea:
    - Instead of tracking the previous node explicitly,
      we shift the pointer initialization so that:
          slow stops ONE NODE BEFORE the middle.
    - That way, we can delete slow->next directly.

    ------------------------------------------------------------

    Initialization Trick:
        slow = head
        fast = head->next->next

    Why?

    - In the traditional approach:
          fast starts at head
          slow ends exactly at middle
          so we need slowPrev.

    - In THIS version:
          fast starts two steps ahead.
          So when fast reaches the end,
          slow naturally stops at node BEFORE middle.

    That eliminates the need for slowPrev.

    ------------------------------------------------------------

    Edge Case:
    - If list has 0 or 1 node → return NULL
      because deleting the middle leaves an empty list.

    ------------------------------------------------------------

    Loop Logic:
        while(fast != NULL && fast->next != NULL)

    - fast moves 2 steps.
    - slow moves 1 step.
    - When loop ends:
          slow is positioned right before middle node.

    ------------------------------------------------------------

    Deletion Logic:
        ListNode* delNode = slow->next;
        slow->next = slow->next->next;
        delete delNode;

    - Store middle node temporarily.
    - Bypass it.
    - Free memory.

    ------------------------------------------------------------

    Time Complexity:
        O(N) → Single traversal.

    Space Complexity:
        O(1) → No extra storage.

    ------------------------------------------------------------

    Even Length Behavior:
    - This deletes the second middle node,
      matching problem requirement.
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
    ListNode* deleteMiddle(ListNode* head) {
        
        if(head== NULL || head-> next == NULL)
            return NULL;

       
        ListNode* slow = head; 
        ListNode* fast = head-> next ->next;

        while(fast != NULL && fast -> next != NULL)
        {

            slow = slow -> next; 
            fast = fast -> next -> next; 
        }


        ListNode* delNode = slow -> next;
        slow -> next = slow -> next->next; 
        delete delNode;

        return head;
    }
};
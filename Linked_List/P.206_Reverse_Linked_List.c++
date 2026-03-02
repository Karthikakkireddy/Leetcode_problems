/*
    3 Approaches. 
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


/*
    Reverse Linked List (Recursive)

    How this works (simple idea):

    We go all the way to the end of the list first.
    Then while coming back (recursion unwinds),
    we flip the direction of each link.

    Example:
    1 → 2 → 3 → NULL

    recursion goes till 3
    while returning:
    3 → 2 → 1


    Why a separate helper function?

    Recursion needs extra information at every step:

    • head  → current node we are processing
    • prev  → node that should come before current after reversing
    • newHead → to send the new head (tail of original list) back to caller

    Since recursion can return only one value,
    we pass newHead by reference to update it.

    Time Complexity: O(N)
    → every node is visited once

    Space Complexity: O(N)
    → recursion stack holds N calls
    → NOT constant space

    Note:
    Iterative solution is preferred in interviews because it uses O(1) space.
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
    void reverseLL(ListNode* head, ListNode* prev, ListNode* &newHead)
    {
        // reached end → prev becomes new head
        if(head == NULL)
        {
            newHead = prev;
            return;
        }

        // go deeper first
        reverseLL(head->next, head, newHead);

        // reverse link while coming back
        head->next = prev;
    }

    ListNode* reverseList(ListNode* head) {
        ListNode* newHead = NULL;

        reverseLL(head, NULL, newHead);
        return newHead;
    }
};



/*
    Reverse Linked list (Recursive – clean version)

    Core idea:
    Reverse everything AFTER the current node,
    then fix the current node at the end.

    Think like this:
    head → rest of list

    1 → 2 → 3 → NULL

    reverseList(2) gives:
    3 → 2

    then attach 1 at the end:
    3 → 2 → 1


    What each step does:

    1️⃣ Base case
        If list is empty OR only one node,
        it is already reversed.

    2️⃣ Reverse the rest of the list
        reverseList(head->next)

    3️⃣ Fix current node
        head->next->next = head   → flip link
        head->next = NULL         → prevent cycle

    4️⃣ Return new head (tail of original list)


    Time Complexity: O(N)
    → each node processed once

    Space Complexity: O(N)
    → recursion stack depth = N

    ⚠️ Important:
    head->next = NULL is required.
    Without it, you create a cycle.

    ⚠️ Interview reality:
    Iterative version is preferred for O(1) space.
*/
class Solution {
public:
    
    ListNode* reverseList(ListNode* head) {

        // base case: empty list or single node
        if(head == NULL || head->next == NULL)
            return head;

        // reverse the rest of the list
        ListNode* newHead = reverseList(head->next);

        // fix current node
        ListNode* front = head->next; 
        front->next = head;   // flip direction
        head->next = NULL;    // avoid cycle

        return newHead;       // return new head
    }
};
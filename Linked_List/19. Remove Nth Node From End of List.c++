/*
    Problem Link = https://leetcode.com/problems/remove-nth-node-from-end-of-list/
*/

/*
    Remove Nth Node From End — Brute Force Approach

    Idea:
    1️⃣ First count total number of nodes (length = L).
    2️⃣ The node to remove is at position (L - n) from the start.
    3️⃣ Traverse again to reach the node just before it.
    4️⃣ Adjust pointers and delete the node.


    Time Complexity: O(N)
        - First traversal to count nodes → O(N)
        - Second traversal to reach deletion point → O(N)
        - Total ≈ 2N → O(N)

    Space Complexity: O(1)
        - Only a few pointer variables used.
        - No extra data structures.

    Edge Cases:
        ✔ Removing head node
        ✔ Removing last node
        ✔ Single node list
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head == NULL || head -> next == NULL)
        {
            delete head;
            return NULL;
        }
        
        ListNode* temp = head; 
        int numberNodes=0;
        while(temp != NULL)
        {
            temp = temp -> next; 
            numberNodes++;
        }
        temp = head;
        for(int i=1; i <numberNodes - n ; i++)
        {
            temp = temp -> next ;
        }
        ListNode* delTemp ;

        if(numberNodes - n == 0)
        {
            delTemp = head;
            head = head -> next;
        }
        else
        {
            delTemp= temp -> next;
            temp -> next = temp -> next -> next;
        }
        
        delete delTemp;

        return head;
    }
};


/*
    Two Pointer Approach (Single Pass)

    Idea:
    1️⃣ Move the fast pointer 'n' steps ahead.
       → This creates a fixed gap of 'n' nodes between slow and fast.

    2️⃣ Move both slow and fast together until fast reaches the end.

    3️⃣ When fast reaches the last node:
       → slow will be just before the node that needs to be deleted.

    4️⃣ Adjust pointers to remove the target node.


    Why this works:

    After moving fast 'n' steps ahead,
    the distance between slow and fast is exactly 'n'.

    When fast reaches the end of the list,
    slow must be exactly (n + 1)th node from the end,
    meaning slow->next is the nth node from the end.

    So we delete slow->next.


    Special Case:
    If fast becomes NULL immediately after shifting 'n' steps,
    that means n == length of list.
    So we must delete the head.


    Time Complexity: O(N)
    - Each node is visited at most once.

    Space Complexity: O(1)
    - Only two pointers are used.
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        if(head == NULL || head -> next == NULL)
        {
            delete head;
            return NULL;
        }
        
        ListNode* slow = head;
        ListNode* fast = head;
        while(n--)
        {
            fast = fast -> next;
        }

        while(fast!= NULL && fast-> next != NULL)
        {
            slow = slow -> next;
            fast = fast -> next;
        }
        if(fast == NULL)
        {
            head = slow -> next;
            delete slow;

        }
        else
        {
            ListNode* delTemp = slow -> next;
            slow-> next = slow -> next -> next; 
            delete(delTemp);
        }
       

        return head;
    }
};


/*
    Two Pointer Approach - DUMMY NODE VERSION
    TC - O(N)
    SC - O(1)
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
    ListNode* removeNthFromEnd(ListNode* head, int n) {
        // Create a dummy node before head to handle edge cases
        ListNode* dummy = new ListNode(0, head);

        // Initialize slow and fast pointers at dummy
        ListNode* slow = dummy;
        ListNode* fast = dummy;

        // Move fast pointer N+1 steps ahead to create a gap
        for (int i = 0; i <= n; i++) {
            fast = fast->next;
        }

        // Move both pointers until fast reaches the end
        while (fast != NULL) {
            slow = slow->next;
            fast = fast->next;
        }

        // Slow is now at node before target → delete target node
        slow->next = slow->next->next;

        // Return updated head
        return dummy->next;
    }
};
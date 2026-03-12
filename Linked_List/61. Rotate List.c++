/*
    Problem link - https://leetcode.com/problems/rotate-list/description/
*/

/*
    Approach:
    - First compute the length of the linked list.
    - Since rotating N times gives the same list,
      compute the effective rotation using:
            shift = k % length

    - Use two pointers (slow and fast).
    - Move the fast pointer `shift` steps ahead.
    - Move both pointers together until fast reaches the last node.

    Why This Works:
    - The slow pointer will stop at the node just before
      the new head after rotation.
    - We then reconnect the list by:
        1. Making the last node point to the original head.
        2. Setting the new head.
        3. Breaking the link at the slow pointer.

    Time Complexity: O(N)
    - One traversal to compute the length.
    - One traversal to locate the rotation point.

    Space Complexity: O(1)
    - Only a few pointer variables are used.
*/
class Solution {
public:
    ListNode* rotateRight(ListNode* head, int k) {
        if(head == NULL || head -> next == NULL)
            return head;
        ListNode* temp = head;
        int n=0;
        while(temp != NULL)
        {
            temp = temp -> next ;
            n++;
        }
        int shift = k%n;

        ListNode* slow = head;
        ListNode* fast = head;

        for(int i = 1; i<= shift ; i++)
        {
            fast = fast -> next;
        }

        while(fast -> next != NULL)
        {
            slow = slow -> next;
            fast = fast -> next;
        }

        fast -> next = head ;
        head = slow -> next;
        slow-> next = NULL;

        return head;
    }
};


/*
    Approach: Circular Linked List Trick

    Idea:
    - First find the length of the linked list.
    - Connect the last node back to the head, forming a circular list.
    - Rotating right by k is equivalent to moving
          n - (k % n)
      steps from the head to find the new tail.

    Steps:
    1. Traverse the list to get its length and last node.
    2. Connect last node to head to form a circular list.
    3. Move (n - k % n - 1) steps to find the new tail.
    4. The next node becomes the new head.
    5. Break the circle to restore the list.

    Why This Works:
    - Rotating a list is essentially cutting it at the correct point.
    - Making it circular allows us to move directly to the new tail
      without complex pointer manipulation.

    Time Complexity: O(N)
    - One traversal to compute length.
    - At most one traversal to reach the new tail.

    Space Complexity: O(1)
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
    ListNode* rotateRight(ListNode* head, int k) {
        if(head == NULL || head -> next == NULL)
            return head;
        ListNode* temp = head;
        int n=1;
        while(temp->next != NULL)
        {
            temp = temp -> next ;
            n++;
        }
        temp-> next = head;
        int shift = n - (k%n);

        ListNode* temp2 = head;
        ListNode* newTail;

        for(int i = 1; i<=shift-1 ; i++)
        {
            temp2 = temp2 -> next;
        }
        head = temp2-> next;
        temp2->next = NULL;

       

        return head;
    }
};
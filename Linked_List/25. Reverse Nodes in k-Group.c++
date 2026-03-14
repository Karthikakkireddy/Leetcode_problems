/*
    Problem Link - https://leetcode.com/problems/reverse-nodes-in-k-group/description/
*/

/*
    Idea (Recursive K-group reversal)

    The goal is:
        Reverse the list in groups of size k.

    Instead of trying to reverse everything at once,
    we break the problem into smaller pieces using recursion.

    Think of it like:
        reverse first k nodes
        + solve the rest of the list recursively.

    ------------------------------------------------------

    Step 1: Check if at least k nodes exist

        ListNode* temp = dummy;

        We move temp k steps forward.
        If we cannot move k steps, it means the remaining
        nodes are less than k, so we simply return head
        (because they should not be reversed).

    ------------------------------------------------------

    Step 2: Solve the rest of the list first

        ListNode* nextGroupHead = reverseKGroup(temp->next, k);

    temp->next currently points to the node where the next
    group begins.

    We recursively process the rest of the list first.
    That way, when we reverse the current group,
    we already know where it should connect.

    ------------------------------------------------------

    Step 3: Temporarily isolate the first k nodes

        temp->next = NULL;

    Now the first k nodes become an independent list.

    Example:
        before cut:
        1 → 2 → 3 → 4 → 5 → 6

        after cut (k = 3):
        1 → 2 → 3 → NULL
        4 → 5 → 6

    This allows us to safely reverse only the first group.

    ------------------------------------------------------

    Step 4: Reverse the current group

        temp = reverseLL(head);

    The helper function reverses the first k nodes.

    Example:
        1 → 2 → 3
    becomes
        3 → 2 → 1

    temp now points to the new head of this reversed group.

    ------------------------------------------------------

    Step 5: Connect the reversed group to the rest

        head->next = nextGroupHead;

    Important detail:
        "head" is now the last node after reversal.

    So we connect it to the already processed remainder.

    ------------------------------------------------------

    Final return

        return temp;

    temp is the new head of this reversed section,
    which becomes the head for this recursive level.

    ------------------------------------------------------

    Why this works

    - Recursion ensures the rest of the list is already
      processed when we reverse the current group.
    - Each group is isolated, reversed, and reattached.

    ------------------------------------------------------

    Time Complexity: O(N)

    - Each node is visited once during recursion.
    - Each node is also part of exactly one reversal.
    - Overall still linear.

    ------------------------------------------------------

    Space Complexity: O(N)

    - Due to recursion stack (one call per group).
*/
class Solution {
public:
    ListNode* reverseLL(ListNode* head)
    {
        if(head == NULL || head -> next == NULL)
            return head;
        
        ListNode* prev = NULL;
        ListNode* curr = head ; 
        ListNode* front = head -> next;

        while(curr != NULL)
        {
            curr -> next = prev; 
            prev= curr ;
            curr = front ;
            if(front != NULL)
                front = front -> next ;
        }
        return prev;
    }
    ListNode* reverseKGroup(ListNode* head, int k) {
        if(head == NULL || head -> next == NULL)
        {
            return head;
        }

        ListNode* dummy = new ListNode(-1);
        dummy -> next = head;
        ListNode* temp = dummy;
        for(int i=1 ; i<= k ; i++)
        {
            temp = temp -> next;
            if(temp == NULL )
            {
                return head;
            }
        }
        ListNode* nextGroupHead = reverseKGroup(temp -> next , k);
        temp -> next = NULL; 
        temp = reverseLL(head);
        head -> next = nextGroupHead;
        return temp;
    }
};
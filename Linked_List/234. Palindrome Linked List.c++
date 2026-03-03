/*
    Problem link :  https://leetcode.com/problems/palindrome-linked-list/
*/


/*
    Naive Approach:
    1️⃣ Use slow & fast pointer to find the middle of the list.
    2️⃣ Store the second half of the list into a vector.
    3️⃣ Compare the first half with the reversed second half (via vector).

    Why this works:
    In a palindrome, first half == reversed second half.

    Time Complexity: O(N)
    - Finding middle → O(N/2)
    - Storing second half → O(N/2)
    - Comparing values → O(N/2)
    - Total = O(3N/2) → O(N)

    Space Complexity: O(N)
    - Vector stores about N/2 elements
    - Linear extra space

    Note:
    We store node pointers, but we only compare values.
    We could store just integers instead.
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
    bool isPalindrome(ListNode* head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while(fast != NULL && fast -> next != NULL)
        {
            slow = slow -> next ;
            fast = fast -> next -> next;
        }
        vector<ListNode*> v;
        while(slow != NULL)
        {
            v.emplace_back(slow);
            slow = slow -> next;
        }

        ListNode* temp = head;

        for(int i = v.size()-1 ; i>= 0 ; i--)
        {
            if(v[i]-> val != temp -> val)
            {
                return false;
            }
            temp = temp -> next;
        }
        return true;
    }
};



/*
    Optimal Approach (O(1) space)

    Steps:

    1️⃣ Find the middle of the linked list using slow & fast pointers.
        - slow moves 1 step
        - fast moves 2 steps
        - slow stops at end of first half

    2️⃣ Reverse the second half of the list.

    3️⃣ Compare first half and reversed second half node by node.

    4️⃣ Restore the second half back to original
       (important if the list should not be modified).


    Why this works:
    A palindrome reads the same forward and backward.
    Reversing the second half lets us compare both halves directly.


    Time Complexity: O(N)
        - Find middle → N/2
        - Reverse second half → N/2
        - Compare halves → N/2
        - Restore list → N/2
        Total ≈ 2N → O(N)

    Space Complexity: O(1)
        - No extra data structures used.
        - Reversal is done in-place.


    Edge cases handled:
        ✔ empty list
        ✔ single node
        ✔ even length
        ✔ odd length
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
    ListNode* reverseLL(ListNode* head)
    {
        ListNode* front = head -> next;
        ListNode* curr = head;
        ListNode* prev = NULL ;

        while(curr != NULL)
        {
            curr -> next = prev;
            prev = curr;
            curr = front;
            if(front != NULL)
                front = front -> next;
        }
        return prev; 
    }
    bool isPalindrome(ListNode* head) {
        if(head == NULL || head -> next == NULL)
        {
            return true;
        }
        ListNode* slow = head;
        ListNode* fast = head;

        while(fast->next != NULL && fast -> next->next != NULL)
        {
            slow = slow -> next ;
            fast = fast -> next -> next;
        }
        ListNode* secondHalfHead = reverseLL(slow-> next);
        ListNode* restore = secondHalfHead;
        ListNode* firstHalfHead = head;

        while(secondHalfHead != NULL)
        {
            if(firstHalfHead -> val != secondHalfHead -> val)
            {
                ListNode* temp = reverseLL(restore);
                return false;
            }
            firstHalfHead = firstHalfHead -> next;
            secondHalfHead = secondHalfHead -> next;
        }
        ListNode* temp2 = reverseLL(restore);
        return true;

    }
};
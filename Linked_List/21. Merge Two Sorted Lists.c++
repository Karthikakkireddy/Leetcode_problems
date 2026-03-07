
/*
    Problem Link - https://leetcode.com/problems/merge-two-sorted-lists/submissions/1941147332/?envType=problem-list-v2&envId=linked-list

*/


/*
    Approach:
    - Use two pointers to traverse both sorted linked lists.
    - Compare the current nodes of both lists.
    - Insert the smaller value into a new linked list.
    - Move the pointer of the list from which the value was taken.
    - Once one list finishes, append the remaining nodes
      from the other list to the result list.

    Why This Works:
    - Both lists are already sorted.
    - By always picking the smaller element, the merged
      list remains sorted.

    Time Complexity: O(N + M)
    - Each node from both lists is processed exactly once.

    Space Complexity: O(N + M)
    - A new linked list is created containing all nodes
      from both input lists.
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
    ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
        ListNode* dummy = new ListNode(-1);
        ListNode* curr = dummy;

        while(a != NULL && b!= NULL)
        {
            ListNode* newNode;
            if(a -> val <= b-> val)
            {
                newNode = new ListNode(a-> val);
                a = a-> next;
            }
            else
            {
                newNode = new ListNode(b-> val);
                b = b-> next;
            }
            curr-> next = newNode;
            curr = newNode;
        }
        while(a != NULL)
        {
            ListNode* newNode = new ListNode(a-> val);
            a= a-> next;
            curr-> next = newNode;
            curr = newNode;
        }
        while(b != NULL)
        {
            ListNode* newNode = new ListNode(b-> val);
            b= b-> next;
            curr-> next = newNode;
            curr = newNode;
        }
        

        return dummy -> next;
    }
};

/*
    Limitation of this approach:
    - A new linked list is created by allocating new nodes
      and copying values from both input lists.

    - This is unnecessary because the two lists are already
      composed of nodes that can be reused.

    - Instead of creating new nodes, we could simply adjust
      the existing node pointers to merge the lists, which
      would reduce the extra space usage.
*/






/*
    Why This Solves the O(N + M) Space Issue:

    - The previous approach created a completely new linked list
      by allocating new nodes for every element.
    - That required O(N + M) extra space because N + M new nodes
      were created.

    - In this approach, no new nodes are created (except the dummy node).
    - Instead, we reuse the existing nodes from both linked lists
      and simply change their `next` pointers to form the merged list.

    - Since we are only rearranging pointers and not allocating
      new nodes proportional to the input size, the extra space
      used does not grow with N or M.

    Time Complexity: O(N + M)
    - Each node from both lists is visited exactly once.

    Space Complexity: O(1)
    - Only a few pointer variables are used and the existing
      nodes are reused.
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
    ListNode* mergeTwoLists(ListNode* a, ListNode* b) {
        ListNode* dummy = new ListNode(-1);
        ListNode* curr = dummy;

        while(a != NULL && b!= NULL)
        {
            if(a -> val <= b-> val)
            {
                curr -> next = a ;
                curr =a ;
                a = a-> next;
            }
            else
            {
                curr -> next = b;
                curr =b ;
                b = b-> next;
            }
        }
        
        if(a==NULL)
        {
            curr -> next = b;
        }
        if(b== NULL)
        {
            curr -> next = a;
        }

        return dummy -> next;
    }
};
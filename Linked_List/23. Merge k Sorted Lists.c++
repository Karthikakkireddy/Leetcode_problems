/*
    Problem Link - https://leetcode.com/problems/merge-k-sorted-lists/description/
*/

/*
    Approach: Sequential Merging

    Idea:
    - Start with an empty list (newHead).
    - Merge each list from the input vector with the current result.
    - After every merge, the result becomes larger.
    - Repeat until all lists are merged.

    Example:
        lists = [L1, L2, L3]

        Step 1:
            merge(L1 , NULL) → result = L1

        Step 2:
            merge(L2 , result)

        Step 3:
            merge(L3 , result)

    -------------------------------------------------------

    Why This Works

    - The helper function mergeLL() merges two sorted linked lists.
    - By repeatedly merging lists into the result, we eventually
      combine all lists into one sorted list.

    -------------------------------------------------------

    Time Complexity

        Let:
            k = number of lists
            n = total number of nodes across all lists

        First merge:
            O(size(L1))

        Second merge:
            O(size(L1) + size(L2))

        Third merge:
            O(size(L1) + size(L2) + size(L3))

        ...

        In worst case this becomes:

            O(n * k)

        because the result list keeps growing and is merged again.

    -------------------------------------------------------

    Space Complexity: O(1)

    - No extra data structures are used.
    - Only pointer manipulations are done.
*/
class Solution {
public:
    ListNode* mergeLL(ListNode* l1, ListNode* l2)
    {
        ListNode* dummy = new ListNode(-1);
        ListNode* temp = dummy;
        while(l1!= NULL && l2 != NULL)
        {
            if(l1 -> val <= l2 -> val)
            {
                temp -> next = l1;
                temp = l1; 
                l1 = l1 -> next;
            }
            else
            {
                temp -> next = l2;
                temp = l2 ; 
                l2 = l2 -> next;
            }
        }
        if(l1 != NULL)
        {
            temp -> next = l1;
        }
        if(l2 != NULL)
        {
            temp -> next =  l2;
        }
        return dummy -> next;
    }
    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size() == 0 )
            return NULL;
        ListNode* newHead = NULL;
        for(auto x : lists)
        {
            newHead = mergeLL(x, newHead);

        }
        return newHead;
    }
};
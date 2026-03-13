/*
    Problem link - https://leetcode.com/problems/remove-duplicates-from-sorted-list/description/?envType=problem-list-v2&envId=linked-list
*/

/*
    Approach

    - The linked list is sorted, so duplicate values appear
      next to each other.
    - For each node (curr), move another pointer (front)
      forward while the values are the same.
    - Delete those duplicate nodes.
    - Finally connect curr directly to the next unique node.

    Essentially:
    - Keep the first occurrence of each value
    - Remove all immediate duplicates after it.

    ------------------------------------------------------

    Dry Run Example

    List:
        1 → 1 → 1 → 2 → 3 → 3

    Step 1:
        curr = first 1
        front moves over duplicate 1s

        deleted nodes: 1, 1
        front stops at 2

        curr->next = 2

        List becomes:
        1 → 2 → 3 → 3

    Step 2:
        curr = 2
        no duplicates

    Step 3:
        curr = 3
        front skips duplicate 3
        delete duplicate

        curr->next = NULL

    Final list:
        1 → 2 → 3

    ------------------------------------------------------

    Why This Works

    - Since the list is sorted, duplicates are always consecutive.
    - By skipping and deleting nodes with the same value,
      we ensure only one copy remains.

    ------------------------------------------------------

    Time Complexity: O(N)
    - Each node is visited once while skipping duplicates.

    Space Complexity: O(1)
    - No extra data structures are used.
*/
class Solution {
public:
    ListNode* deleteDuplicates(ListNode* head) {
        ListNode* curr = head ;
        while(curr != NULL)
        {
            ListNode* front = curr -> next ;
            while(front != NULL && front -> val == curr -> val)
            {
                ListNode* dummy = front ;
                front = front -> next;
                delete(dummy);
            }
            curr -> next = front ;

            curr = curr -> next;
        }
        return head;
    }
};
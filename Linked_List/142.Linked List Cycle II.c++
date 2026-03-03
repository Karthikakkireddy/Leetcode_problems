/*
    Problem link - https://leetcode.com/problems/linked-list-cycle-ii/

*/



/*
    Detect Cycle II (Brute Force using Hash Set)

    Idea:
    As we walk through the list, we store each node's address.
    If we ever see the SAME node again, we found the start of the cycle.

    Why this works:
    In a cycle, traversal eventually loops back to a previously visited node.
    The first repeated node is the cycle entry point.

    Example:
    1 → 2 → 3 → 4 → 5
              ↑     ↓
              ← ← ← ←

    When we revisit node 3 → cycle starts there.


    Time Complexity: O(N)
    → each node visited once
    → hash lookup & insert are O(1) average

    Worst case: O(N²) (rare hash collisions)

    Space Complexity: O(N)
    → set stores visited node addresses

    Notes:
    • We store node addresses, not values.
      Same values ≠ same node.

    • If no cycle exists, traversal reaches NULL.
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {

        unordered_set<ListNode* > s;

        ListNode* temp = head;
        while(temp != NULL)
        {
            if(s.count(temp))
            {
                return temp;
            }
            s.insert(temp);
            temp = temp -> next;
        }
        return temp;

    }
};



/*
    Detect Cycle II — Floyd’s Algorithm (Optimal)

    Goal:
    Return the node where the cycle begins.
    If no cycle → return NULL.


    STEP 1: Detect if a cycle exists
    --------------------------------
    • slow moves 1 step
    • fast moves 2 steps

    If they meet → a cycle exists.
    If fast reaches NULL → no cycle.


    STEP 2: Find the start of the cycle
    -----------------------------------
    When slow & fast meet:

    1️⃣ Move slow back to head.
    2️⃣ Keep fast at meeting point.
    3️⃣ Move both one step at a time.
    4️⃣ Where they meet again = cycle start.


    WHY DOES THIS WORK?

    Let:
    L = distance from head → cycle start
    C = cycle length
    x = distance from cycle start → meeting point

    When they meet:
        slow traveled = L + x
        fast traveled = L + x + kC   (k ≥ 1)

        fast moves twice as fast:
        2(L + x) = L + x + kC
        ⇒ L + x = kC
        ⇒ L = kC − x

    This means:
    if one pointer starts from head
    and the other from meeting point,
    both will meet at the cycle start.


    Time Complexity: O(N)
    → detection + locating start is linear

    Space Complexity: O(1)
    → no extra memory used

    Edge cases handled:
    ✔ empty list
    ✔ single node
    ✔ cycle at head
    ✔ long tail before cycle
*/

/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */
class Solution {
public:
    ListNode *detectCycle(ListNode *head) {

        ListNode* slow = head;
        ListNode* fast = head;

        // STEP 1: detect cycle
        while(fast != NULL && fast->next != NULL)
        {
            slow = slow->next;
            fast = fast->next->next;

            // pointers meet → cycle exists
            if(fast == slow)
            {
                // STEP 2: find cycle start
                slow = head;

                while(fast != slow)
                {
                    slow = slow->next;
                    fast = fast->next;
                }

                return slow;  // cycle entry
            }
        }

        return NULL; // no cycle
    }
};
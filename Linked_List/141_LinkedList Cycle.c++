/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     ListNode *next;
 *     ListNode(int x) : val(x), next(NULL) {}
 * };
 */

// BRUTE FORCE Approach: Store visited node addresses in a unordered set.
// If we encounter the same node address again, a cycle exists.

// Time Complexity: O(N) average
// - We traverse each node at most once.
// - unordered_set insert & lookup are O(1) on average.
// - Therefore total time is linear.
//
// Worst case (rare): O(N^2) if hash collisions degrade performance.

// Space Complexity: O(N)
// - In the worst case (no cycle), we store all N node addresses.
class Solution {
public:
    bool hasCycle(ListNode *head) {
        unordered_set<ListNode *> st;

        ListNode* temp = head;
        while(temp != NULL)
        {
            if(!st.count(temp))
            {
                st.insert(temp);
            }
            else
            {
                return true;
            }
            temp = temp -> next;
        }

        return false;
    }
};


// Floyd’s Cycle Detection (Tortoise & Hare)
//
// Idea:
// - Use two pointers moving at different speeds.
// - slow moves 1 step at a time.
// - fast moves 2 steps at a time.
// - If a cycle exists, fast will eventually "lap" slow
//   and they will meet inside the cycle.
// - If there is no cycle, fast will reach NULL.

    // WHY THIS WORKS:

    // Think of runners on a circular track.

    // Once both pointers enter the cycle:
    // - slow moves 1 step per iteration
    // - fast moves 2 steps per iteration
    // → fast gains 1 step on slow every iteration

    // This reduces the gap between them.

    // Since the loop has finite length,
    // the gap must eventually become zero,
    // so they meet.

    // If there is NO cycle:
    // fast keeps moving forward and reaches NULL,
    // proving no loop exists.

// Time Complexity: O(N)
// - Each pointer traverses the list at most once.
// - Even in a cycle, they meet within N steps.
//
// Space Complexity: O(1)
// - No extra memory is used; only two pointers.

class Solution {
public:
    bool hasCycle(ListNode *head) {
        ListNode* slow = head;
        ListNode* fast = head;

        while(fast != NULL && fast->next != NULL)
        {
            slow = slow->next;          // move 1 step
            fast = fast->next->next;    // move 2 steps

            // If pointers meet, cycle exists
            if(slow == fast)
                return true;
        }

        // fast reached end → no cycle
        return false;
    }
};
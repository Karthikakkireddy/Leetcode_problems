/*
    Problem link - https://leetcode.com/problems/swap-nodes-in-pairs/description/?envType=problem-list-v2&envId=linked-list
*/


/*
    Approach: Recursion (swap first pair, solve the rest)

    Idea:
    - Take the first two nodes and swap them.
    - Recursively solve the remaining list.
    - Attach the result of the recursive call to the swapped pair.

    Example:
        1 → 2 → 3 → 4

    Step 1:
        swap(1,2) → 2 → 1
        recursively process:
            3 → 4

    Step 2:
        swap(3,4) → 4 → 3

    Step 3:
        connect results:
        2 → 1 → 4 → 3

    Key Steps in Code:
    - nextPairHead = swapPairs(head->next->next)
        Recursively swap the rest of the list.

    - nextToHeadNode = head->next
        This becomes the new head after swapping.

    - nextToHeadNode->next = head
        Reverse the first pair.

    - head->next = nextPairHead
        Connect the swapped pair with the rest of the list.

    Time Complexity: O(N)
    - Each node is visited exactly once.

    Space Complexity: O(N)
    - Due to recursion stack (one call per pair).
*/
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        
        if(head == NULL || head -> next == NULL)
        {
            return head;
        }

        ListNode* nextPairHead = swapPairs(head -> next -> next);
        ListNode* nextToHeadNode = head -> next ;

        nextToHeadNode -> next = head ;

        head -> next = nextPairHead;

        return nextToHeadNode;
    }
};


/*
    Approach: Iterative pair swapping

    Idea:
    - We swap nodes in pairs by adjusting pointers.
    - A dummy node is used to simplify swapping the first pair.
    - At each step we swap two nodes and move forward to the next pair.

    Example:
        1 → 2 → 3 → 4

    First swap:
        prevNode → 1 → 2 → 3 → 4
        becomes
        prevNode → 2 → 1 → 3 → 4

    Second swap:
        prevNode moves to 1
        3 → 4 becomes
        4 → 3

    Final:
        2 → 1 → 4 → 3

    Pointer roles:
        prevNode → node before the pair
        currNode → first node of the pair

    Swap steps:
        1. prevNode -> next = second node
        2. first node -> next = node after pair
        3. second node -> next = first node

    Why dummy node helps:
        - Without dummy, swapping the first pair would require
          special handling because head changes.

    Time Complexity: O(N)
        - Each node is processed once.

    Space Complexity: O(1)
        - No recursion or extra data structures used.
*/
class Solution {
public:
    ListNode* swapPairs(ListNode* head) {
        
        if(head == NULL || head -> next == NULL)
        {
            return head;
        }
        ListNode* dummy = new ListNode(-1);
        ListNode* prevNode = dummy; 
        ListNode* currNode = head;

        while(currNode !=NULL && currNode -> next !=NULL)
        {
            prevNode -> next = currNode -> next ;
            currNode -> next = prevNode -> next -> next ;
            prevNode -> next -> next = currNode;

            prevNode = currNode;
            currNode = currNode -> next ;
        }
        return dummy -> next;

        
    }
};
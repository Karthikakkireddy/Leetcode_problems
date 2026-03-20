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


/*
    Approach: Min Heap (Priority Queue)

    Idea:
    - At any moment, we want the smallest node among all lists.
    - So we push the first node of every list into a min heap.
    - Repeatedly:
        → take the smallest node
        → attach it to result
        → push its next node into the heap

    Example:
        lists = [1→4→5, 1→3→4, 2→6]

        Heap initially: [1,1,2]

        Step:
            pick 1 → push its next (4)
            pick 1 → push its next (3)
            pick 2 → push its next (6)
            ...

------------------------------------------------------

    Why This Works

    - Heap always gives the smallest available node.
    - We only keep at most K nodes in heap (one from each list).
    - So we efficiently merge all lists in sorted order.

------------------------------------------------------

    Time Complexity: O(N log K)

    - N = total number of nodes
    - K = number of lists
    - Each node is pushed and popped once → log K cost

------------------------------------------------------

    Space Complexity: O(K)

    - Heap stores at most one node from each list
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

    ListNode* mergeKLists(vector<ListNode*>& lists) {
        if(lists.size() == 0 )
            return NULL;

       priority_queue<
                        pair<int, ListNode*>,
                        vector<pair<int, ListNode*>>,
                        greater<pair<int, ListNode*>>
                    > q;
       
        
        for(auto x : lists)
        {
            if(x!= NULL)
                q.push({x-> val , x});
        }
        ListNode* dummy = new ListNode(-1);
        ListNode* curr = dummy;
        if(!q.empty())
             cout << q.top().first << "\n";
        while(!q.empty())
        {
            pair<int, ListNode* > pq = q.top();
            curr -> next = pq.second;
            q.pop();
            if(pq.second -> next != NULL)
            {
                q.push({pq.second -> next -> val , pq.second -> next});
            }
            curr = pq.second;
        }
        return dummy -> next ; 
    }
};
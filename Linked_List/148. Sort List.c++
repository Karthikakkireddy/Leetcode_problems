/*
    Problem Link - https://leetcode.com/problems/sort-list/
*/


/*
    Brute Force Approach

    Idea:
    - Traverse the linked list and store all node values in a vector.
    - Sort the vector.
    - Traverse the linked list again and overwrite the node values
      using the sorted values from the vector.

    Why This Works:
    - Instead of rearranging the nodes, we simply reorder the values.
    - Sorting the values ensures the linked list becomes sorted.

    Time Complexity: O(N log N)
    - O(N)   → copying values from linked list to vector
    - O(NlogN) → sorting the vector
    - O(N)   → writing sorted values back into the linked list

    Overall TC = O(N log N)

    Space Complexity: O(N)
    - Extra vector used to store all node values.
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
    ListNode* sortList(ListNode* head) {
        vector<int> v;

        ListNode* temp = head ;
        while(temp != NULL)
        {
            v.emplace_back(temp-> val);
            temp = temp -> next;
        }
        sort(v.begin(), v.end());

        temp = head; 
        int i=0;
        while(temp != NULL)
        {
            temp -> val = v[i];
            i++;
            temp = temp -> next;
        }
        return head;
    }
};


/*
    Approach: Merge Sort on Linked List

    Idea:
    - Use slow and fast pointers to find the middle of the linked list.
    - Split the list into two halves.
    - Recursively sort both halves.
    - Merge the two sorted halves using the merge function.

    Why This Works:
    - Each split divides the list roughly in half.
    - The merge step combines two sorted lists efficiently.

    Time Complexity: O(N log N)
    - The list is divided log N times.
    - At each level, all N nodes are processed during merging.

    Space Complexity: O(log N)
    - Due to recursion stack during the divide process.
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


    // Middle node
    ListNode* middleNode(ListNode* head)
    {
        if(head == NULL || head -> next == NULL)
        {
            return head;
        }
        ListNode* slow = head;
        ListNode* fast = head;

        while(fast-> next != NULL && fast-> next -> next != NULL)
        {
            slow = slow -> next; 
            fast = fast -> next -> next;
        }
        return slow;
    }

    // Merging two LL
    ListNode* merge(ListNode* left, ListNode* right)
    {
        ListNode* dummy = new ListNode(-1);
        ListNode* curr = dummy;

        while(left != NULL && right != NULL)
        {
            if(left -> val <= right -> val)
            {
                curr -> next = left;
                curr = left;
                left= left-> next;
            }
            else
            {
                curr -> next = right;
                curr = right;
                right = right -> next;
            }
        }
        if(left == NULL)
        {
            curr -> next = right;
        }
        if(right == NULL)
        {
            curr -> next = left;
        }

        return dummy -> next;
    }


    // Merge sort
    ListNode* sortList(ListNode* head) {
        if(head == NULL || head -> next == NULL)
        {
            return head;
        }
        ListNode* mid = middleNode(head);
       
        ListNode* firstHalf = head;
        ListNode* secondHalf = mid -> next;

        mid -> next = NULL;

        firstHalf = sortList(firstHalf);

        secondHalf = sortList(secondHalf);

        ListNode* newHead =  merge(firstHalf, secondHalf);

        return newHead;

    }

};
/*
    3 variants
    Problem Link:
    https://leetcode.com/problems/intersection-of-two-linked-lists/
*/

/*
    Better than Brute Force Approach (Hashing)

    Idea:
    - Store all nodes of Linked List B in a hash set.
    - Traverse Linked List A and check if the current node
      exists in the set.
    - The first node found in the set is the intersection node.

    Why This Works:
    - Intersection means both lists share the exact same node
      in memory (same address), not just the same value.
    - By storing node addresses of list B, we can quickly check
      whether a node from list A already appeared in list B.

    If no intersection exists:
    - Traversal of list A finishes and NULL is returned.

    Time Complexity: O(N + M)
    - Traverse list B once to fill the set.
    - Traverse list A once to check intersection.

    Space Complexity: O(N) or O(M)
    - Depends on which list we store in the hash set.
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* b = headB;
        unordered_set<ListNode* > st;

        while(b != NULL)
        {
            st.insert(b);
            b = b-> next;
        }

        ListNode* a = headA;

        while(a!= NULL)
        {
            if(st.count(a))
                break;
            a = a-> next;
        }
        return a;
    }
};

/*
    Approach: Length Alignment

    Idea:
    - First compute the length of both linked lists.
    - If the lengths are different, move the pointer of the longer
      list forward until both lists have the same remaining length.
    - Once aligned, move both pointers together.
    - The first node where both pointers become equal is the intersection node.

    Why This Works:
    - After removing the extra nodes from the longer list,
      both pointers have the same number of nodes left to traverse.
    - Therefore they will reach the intersection node at the same time.

    If no intersection exists:
    - Both pointers will eventually become NULL.

   Time Complexity: O(N + M)

    - O(max(N,M)) to compute lengths
    - O(|N-M|) to align pointers
    - O(min(N,M)) to find intersection

    Overall simplified complexity = O(N + M)
    - N = length of list A
    - M - length of list B
    - One traversal to compute lengths.
    - One traversal to align pointers.
    - One traversal to compare nodes.

    Space Complexity: O(1)
    - Only a few pointer variables are used.
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
    ListNode *getIntersectionNode(ListNode *headA, ListNode *headB) {
        ListNode* a = headA;
        ListNode* b = headB;
        int lenA=0;
        int lenB=0;

        while(a!= NULL || b!= NULL)
        {
            if(a!=NULL)
            {
                lenA++;
                a = a-> next;
            }
            if(b!=NULL)
            {
                lenB++;
                b = b->next;
            }
        }
        a= headA;
        b= headB;

        while(lenA!=lenB)
        {
            if(lenA > lenB)
            {
                a= a-> next;
                lenA--;
            }
            else
            {
                b = b-> next;
                lenB--;
            }
        }

        while(a!=b)
        {
            a = a-> next;
            b = b-> next;
        }
        return a;
    }
};






/*
    Problem:
    Find the intersection node of two singly linked lists.

    Approach: Two-Pointer Switching Trick

    Idea:
    - Start two pointers:
            d1 → head1
            d2 → head2

    - Traverse both lists simultaneously.
    - When a pointer reaches the end of its list,
      redirect it to the head of the other list.

    Why This Works:
    - Let length of list1 = N
      length of list2 = M

    Pointer d1 travels:
        N nodes in list1 + M nodes in list2

    Pointer d2 travels:
        M nodes in list2 + N nodes in list1

    So both pointers travel exactly:
        N + M nodes

    If an intersection exists:
        both pointers arrive at the intersection
        node at the same time.

    If no intersection exists:
        both pointers reach NULL at the same time.

    Key Insight:
    - Switching heads automatically compensates for
      the length difference between the two lists.
    - No need to compute lengths or align pointers.

    Time Complexity: O(N + M)
    Space Complexity: O(1)
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
    ListNode *getIntersectionNode(ListNode *head1, ListNode *head2) {
    ListNode* d1 = head1;
    ListNode* d2 = head2;
    
    // Traverse both lists, when one reaches the end, redirect it to the head of the other list
    while (d1 != d2) {
        if(d1 == NULL)
        {
            d1 = head2;
        }
        else
        {
            d1 = d1-> next;
        }
        if(d2 == NULL)
        {
            d2 = head1;
        }
        else
        {
            d2 = d2-> next;
        }
       
    }
    
    return d1;  // If they meet, return the intersection node, otherwise NULL
    }
};
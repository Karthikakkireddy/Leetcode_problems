/*
    Problem Link - https://leetcode.com/problems/double-a-number-represented-as-a-linked-list/?envType=problem-list-v2&envId=linked-list
*/


/*
    Problem: Double a Number Represented as a Linked List

    Idea:
    - The number is stored in forward order.
      Example: 1 -> 8 -> 9 represents 189.

    - Since multiplication normally starts from the least
      significant digit, we first reverse the linked list.

    Steps:
    1. Reverse the original linked list so we can process
       digits from least significant to most significant.
    2. Traverse the reversed list and double each digit.
       Handle carry just like normal arithmetic.
    3. Build a new linked list containing the result digits.
    4. Restore the original linked list by reversing it again.
    5. Reverse the result list to restore the correct order.

    Why This Works:
    - Reversing lets us process digits in the correct order
      for arithmetic operations (right to left).
    - Carry is propagated exactly like manual multiplication.

    Time Complexity: O(N)
    - Reverse original list → O(N)
    - Traverse and compute doubled digits → O(N)
    - Restore original list → O(N)
    - Reverse result list → O(N)

    Total ≈ 4N → O(N)

    Space Complexity: O(1)*
    - Only pointer variables and carry are used.
    - The result list is required output, but we do not need that new LL (We can modify the existing LL, 
    which we did not do this approach).
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
        if(head == NULL || head -> next == NULL )
        {
            return head;
        }

        ListNode* prev = nullptr;
        ListNode* front = head -> next;

        while(head != NULL)
        {
            head -> next = prev;
            prev = head; 
            head = front;
            if(front != NULL)
                front =front -> next;
        }
        return prev; 

    }
    ListNode* doubleIt(ListNode* head) 
    {
        ListNode* reversedLL = reverseLL(head);
        ListNode* dummy = new ListNode(-1, nullptr);
        ListNode* curr = dummy; 

        ListNode* temp = reversedLL;
        int carry = 0;
        while(temp != NULL)
        {
            int sum = (temp-> val * 2) + carry;
            ListNode* newNode = new ListNode(sum%10);
            carry = sum / 10;

            curr -> next = newNode;
            curr = newNode;

            temp = temp-> next;
            if(temp == NULL && carry == 1)
            {
                ListNode* lastNode = new ListNode(carry);
                curr -> next = lastNode; 
                curr = lastNode;
            }

        }
        // Reversing the original LL
        reverseLL(reversedLL);

        ListNode* newDHead = reverseLL(dummy -> next);
        return newDHead;
    }
};

/*
    How This Is Different / Better Than the Old Approach:
        - The previous solution created a new linked list to store
        the result digits.
        - This version modifies the existing linked list in-place.
        - This avoids allocating extra nodes for every digit and
        makes the solution more space efficient.

    Time Complexity: O(N)
        - Reverse list → O(N)
        - Traverse and double digits → O(N)
        - Reverse list again → O(N)

    Total ≈ 3N → O(N)

    Space Complexity: O(1)
    - The existing linked list nodes are reused and only a
      constant amount of extra memory is used.
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
        if(head == NULL || head -> next == NULL )
        {
            return head;
        }

        ListNode* prev = nullptr;
        ListNode* front = head -> next;

        while(head != NULL)
        {
            head -> next = prev;
            prev = head; 
            head = front;
            if(front != NULL)
                front =front -> next;
        }
        return prev; 

    }
    ListNode* doubleIt(ListNode* head) 
    {
       head = reverseLL(head);

       int carry = 0;

       ListNode* curr = head;

       while(curr != NULL)
       {
            int sum = (curr -> val * 2) + carry;
            cout << sum << " ";
            curr -> val = sum % 10;

            carry = sum /10;

            if(curr -> next == NULL && carry)
            {
                ListNode* newNode = new ListNode(carry);
                curr -> next = newNode;
                carry = 0;
                curr = curr ->next;
            }
            curr = curr ->next;
       }
       head = reverseLL(head);

       return head;
    }
};


/*
    Approach: Recursion

    Idea:
    - Use recursion to reach the last node of the linked list.
    - While returning from recursion, double each digit and
      propagate the carry to the previous nodes.

    Why This Works:
    - Recursion processes nodes from right to left
      (least significant digit first), which is exactly
      how multiplication should be performed.
    - This removes the need to reverse the linked list.

    Why This Is Better Than Previous Approaches:
    - No linked list reversal is required.
    - No extra result list is created.
    - The existing nodes are modified directly.

    Time Complexity: O(N)
    - Each node is visited exactly once.

    Space Complexity: O(N)
    - Due to recursion stack.
*/
class Solution {
public:

    int addNode(ListNode* head )
    {
        if(head == NULL)
            return 0;
        
        int carry = addNode(head -> next);
        int sum = (head -> val *2) + carry;
        head -> val = sum %10;
        carry = sum /10;

        return carry;
    }
    ListNode* doubleIt(ListNode* head) 
    {
        int carry = addNode(head);
        if(carry)
        {

            ListNode* newNode = new ListNode(carry);
            newNode -> next= head;
            head = newNode;
        }
       
       return head;
    }
};
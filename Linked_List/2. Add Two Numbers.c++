/*
`   3 Variants of code
    Problem Link:
    https://leetcode.com/problems/add-two-numbers/

    Problem Statement:
    - Two numbers are represented as linked lists.
    - Each node stores a single digit.
    - Digits are stored in reverse order.
      Example: 342 is stored as 2 -> 4 -> 3
    - We must return the sum as a new linked list in the same format.

    Intuition:
    - This problem mimics how we do addition manually.
    - Traverse both linked lists simultaneously.
    - At each step add:
            digitA + digitB + carry
    - Store the ones-place digit in the new node.
    - Carry the tens-place digit to the next addition.

    Handling Unequal Length Lists:
    - If one list finishes earlier,
      continue processing the remaining list
      while still considering the carry.

    Carry Handling:
    - Maximum possible sum = 9 + 9 + 1 = 19
    - Therefore carry can only be 0 or 1.

    Final Step:
    - If a carry remains after the loop,
      create one extra node with value 1.

    Time Complexity:
    O(N)
    - N is the length of the longer linked list.

    Space Complexity:
    O(1) auxiliary space
    - Only pointers and carry variable are used.
    - The result list itself is required output.
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
    bool checkNumber(int x)
    {
        if(x >= 10)
        {
            return true;
        }
        return false;
    }
    int getTensPlaceDigit(int number)
    {
        
        number= number/10;
        return number;
    }
    ListNode* addTwoNumbers(ListNode* a, ListNode* b) {
        ListNode* prev = nullptr;
        ListNode* newHead = nullptr;
        int carry = 0;

        
        while(a != NULL ||  b != NULL)
        {
            ListNode* newNode ;
            if(a == NULL)
            {
                newNode = new ListNode((b-> val + carry)%10);
                if(checkNumber(b->val +carry))
                {
                    carry = 1;  
                }
                else
                {  
                    carry = 0;
                }
                
              
            }
            if(b == NULL)
            {
                newNode = new ListNode((a-> val + carry)%10);
                if(checkNumber(a->val +carry))
                {
                    carry = 1;
                }
                else
                {
                    carry = 0;
                }
               
            }
            if(a != NULL && b != NULL)
            {
                newNode = new ListNode((a-> val + b-> val+carry) % 10 );
                if(checkNumber(a-> val + b->val +carry))
                {
                    carry = 1;
                   
                }
                else
                {
                    carry = 0;
                }
              
            }
            if(prev != NULL)
            {
                prev -> next = newNode;
            }
            if(newHead == nullptr)
            {
                newHead = newNode;
            }
            prev = newNode;
            if(a != NULL)
                a = a-> next;
            if(b != NULL)
                b= b -> next;
        }

        if(carry)
        {
            ListNode* lastNode = new ListNode(1);
            prev -> next = lastNode;
        }

        return newHead;

    }
};

/*
    Problem:
    Add two numbers represented as linked lists.
    - Each node stores one digit (0–9).
    - Digits are stored in reverse order.
    - Return the sum as a new linked list.

    ----------------------------------------------------

    Intuition:
    This mimics manual addition.

    At every step:
        sum = digitA + digitB + carry
        node value = sum % 10
        carry = sum / 10

    Continue this until both lists are fully traversed.

    ----------------------------------------------------

    Handling Different Length Lists:
    - If one list ends earlier, treat its digit as 0.
    - Continue processing the remaining list with carry.

    ----------------------------------------------------

    Why Dummy Node is Used:
    - Dummy node simplifies list construction.
    - Avoids special handling for the first node.
    - We always attach new nodes to curr->next.
    - Final answer is dummy->next.

    ----------------------------------------------------

    Final Carry Case:
    - After the loop, if carry remains (example: 9 + 1),
      we append one final node with the carry value.

    ----------------------------------------------------

    Why This Version is Cleaner Than Previous Code:

    1. Carry Handling is Mathematical
       Instead of using helper functions like:
           checkNumber()
       we directly compute:
           carry = sum / 10

       This is simpler and clearer.

    2. Dummy Node Simplifies Linking
       The first version required checking:
           if(prev != NULL)
           if(newHead == NULL)

       Dummy node removes that complexity.

    3. Pointer Management is Simpler
       We only maintain:
           curr -> pointer to last node in result

       Instead of:
           prev
           newHead
           multiple checks

    4. Logic Is Easier to Follow
       Each iteration:
           compute sum
           create node
           move pointers

       The structure becomes predictable and easier to reason about.

    ----------------------------------------------------

    Time Complexity:
    O(N)
    - N is the length of the longer linked list.

    Space Complexity:
    O(1) auxiliary space
    - Only pointers and carry variable are used.
    - Result list itself is required output.
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
    
    ListNode* addTwoNumbers(ListNode* a, ListNode* b) {
       
       ListNode* dummy = new ListNode(-1, nullptr);
       ListNode* curr = dummy;
       int carry=0;

       while(a!= NULL || b!= NULL)
       {
            ListNode* newNode;
            int sum;
            if(a == NULL)
            {
                sum = b->val + carry;
                newNode = new ListNode(sum % 10 );
                carry = sum / 10;
            }
            else if(b == NULL)
            {
                sum = a->val + carry;
                newNode = new ListNode(sum % 10);
                carry = sum /10;
            }
            else
            {
                sum = a->val + b->val + carry;
                newNode = new ListNode(sum % 10);
                carry = sum /10;
            }

            curr -> next = newNode;
            curr = newNode; 

            if(a!= NULL)
            {
                a= a-> next; 
            }
            if(b!= NULL)
            {
                b =b-> next;
            }

            if(a==NULL && b == NULL && carry)
            {
                newNode = new ListNode(carry);
                curr -> next = newNode;
                curr = newNode;
            }
        }
        return dummy -> next;
    }
};


/*
    Improved Version

    Idea:
    - Traverse both linked lists simultaneously.
    - At each step compute:
            sum = carry + value from list A (if exists) + value from list B (if exists)
    - Create a node with:
            digit = sum % 10
            carry = sum / 10
    - Move both pointers forward and continue until both lists end.

    Why This Works:
    - The addition process mimics manual addition digit by digit.
    - Using `sum = carry` first allows us to conditionally add values
      from either list, eliminating multiple case checks.
    - A dummy node simplifies result list construction and avoids
      special handling for the first node.

    Time Complexity: O(N)
    - N is the length of the longer linked list.

    Space Complexity: O(1) auxiliary space
    - Only pointers and carry variable are used.
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
    
    ListNode* addTwoNumbers(ListNode* a, ListNode* b) {
       
       ListNode* dummy = new ListNode(-1, nullptr);
       ListNode* curr = dummy;
       int carry=0;

       while(a!= NULL || b!= NULL)
       {
            ListNode* newNode;
            int sum=carry;

            if(a!=NULL)
            {
                sum = sum+ a->val;
            }
            if(b!=NULL)
            {
                sum = sum+b->val;
            }
            newNode = new ListNode(sum % 10);
            carry = sum /10;

            curr -> next = newNode;
            curr = newNode; 

            if(a!= NULL)
            {
                a= a-> next; 
            }
            if(b!= NULL)
            {
                b =b-> next;
            }

            if(a==NULL && b == NULL && carry)
            {
                newNode = new ListNode(carry);
                curr -> next = newNode;
                curr = newNode;
            }
        }
        return dummy -> next;
    }
};
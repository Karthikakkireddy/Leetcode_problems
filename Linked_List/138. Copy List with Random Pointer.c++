/*
    Problem link - https://leetcode.com/problems/copy-list-with-random-pointer/description/
*/

/*
    Approach: Deep Copy using Hash Maps

    Idea:
    - First create a copy of the linked list (only next pointers).
    - While creating nodes, store:
        1) original node → index
        2) index → new node

    - In the second pass, use these mappings to correctly
      assign the random pointers.

    Steps:
    1. Traverse the original list and create a new list with same values.
    2. Store mappings:
            original node → index
            index → copied node
    3. Traverse both lists again.
       Use the mappings to set the correct random pointers.

    Why This Works:
    - Random pointers may point anywhere in the list.
    - By storing node positions, we can find the corresponding
      copied node for any random pointer.

    Time Complexity: O(N)
    - Two traversals of the linked list.

    Space Complexity: O(N)
    - Hash maps used to store node mappings.
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node* temp = head ;
        unordered_map<Node*, int> m1;
        int mc1 = 0;
        unordered_map<int, Node*>m2;
        int mc2 =0 ;

        Node* dummy = new Node(-1);
        Node* curr = dummy;
        while(temp != NULL)
        {
            Node* newNode = new Node(temp->val);
            curr-> next = newNode;
            curr = newNode; 


            m1[temp] = mc1++;

            m2[mc2++] = curr;
            temp = temp -> next;
        }

        Node* head1 = head;
        Node* head2 = dummy-> next;

        while(head2 != NULL)
        {
            if(head1-> random == NULL)
            {
                head2-> random = NULL;
            }
            else
            {
                head2 -> random =  m2[m1[head1-> random]]; 
            }
          

            head2 = head2 -> next; 
            head1 = head1 -> next;
        }
        return dummy -> next;
    }
};


/*
    Difference from the previous solution:
    - Earlier code used two maps:
            original node → index
            index → copied node
    - This version directly stores:
            original node → copied node
      which simplifies the logic and removes unnecessary mapping.

    How NULL random pointers are handled:
    - If original_node->random is NULL,
      then mp[NULL] returns NULL.
    - So the copied node's random pointer automatically
      becomes NULL without needing an extra condition.

    Time Complexity: O(N)
    - One pass to create nodes and one pass to set random pointers.

    Space Complexity: O(N)
    - Hash map stores mapping for all nodes.
*/
class Solution {
public:
    Node* copyRandomList(Node* head) {
        Node* temp = head ;
        unordered_map<Node *, Node *> mp;

        Node* dummy = new Node(-1);
        Node* curr = dummy;
        while(temp != NULL)
        {
            Node* newNode = new Node(temp->val);
            curr-> next = newNode;
            curr = newNode; 


            mp[temp] = curr;
            temp = temp -> next;
        }

        Node* head1 = head;
        // Node* head2 = dummy-> next;

        while(head1 != NULL)
        {
            mp[head1] -> random =  mp[head1-> random];
            head1 = head1 -> next;
            
        }
        return mp[head];
    }
};


/*
    Approach: Interweaving Nodes (O(1) Space Trick)

    Idea:
    - Instead of using a hashmap, insert the copied node
      directly after its original node in the list.

    Steps:

    1. Insert copied nodes
       - For every node in the original list, create its copy
         and insert it right after the original node.

         Example:
         Original:  A -> B -> C
         After step: A -> A' -> B -> B' -> C -> C'

    2. Assign random pointers
       - If original node's random is X,
         then copied node's random should be X'.
       - Since X' is placed right after X:
             copy->random = original->random->next

    3. Separate the two lists
       - Restore the original list.
       - Extract the copied nodes to form the new list.

    Why This Works:
    - By placing copied nodes next to originals,
      we can easily access the corresponding copy of any node
      without using extra memory.

    Difference from previous hashmap solutions:
    - No extra hash map is used.
    - Instead of storing mappings in memory,
      the mapping is implicitly created by interweaving nodes.

    Time Complexity: O(N)
    - Three linear passes through the list.

    Space Complexity: O(1)
    - No extra data structures are used.
*/
/*
// Definition for a Node.
class Node {
public:
    int val;
    Node* next;
    Node* random;
    
    Node(int _val) {
        val = _val;
        next = NULL;
        random = NULL;
    }
};
*/

class Solution {
public:
    Node* copyRandomList(Node* head) {
        if(head == NULL)
            return head;
        Node* temp = head ;
       while(temp!=NULL)
       {
            Node* newNode = new Node(temp -> val);
            newNode -> next = temp -> next;
            temp -> next = newNode;

            temp = temp -> next -> next;
       }

       Node* temp2 = head;
       Node* newLLHead = head -> next;
        while(temp2 != NULL)
        {
            if(temp2 -> random)
                temp2 -> next -> random = temp2 -> random -> next;
            else
                temp2 -> next -> random = NULL;
            temp2 = temp2 -> next -> next;
        }

        Node* slow = head ;
        Node* fast = head -> next ;
        while(fast != NULL)
        {
            slow-> next = fast -> next;
            slow = fast ;
            fast = fast -> next;
        }
        return newLLHead;
    }
};
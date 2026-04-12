// https://leetcode.com/problems/implement-stack-using-queues/description/

/*
🔴 Stack using 1 Queue (Optimized Trick)

🧠 Idea:
- Queue = FIFO
- Stack = LIFO
👉 So we "rotate" the queue after every push

--------------------------------------------

push(x):

1. Push normally:
       q.push(x)

2. Rotate previous elements behind it:

       for(size-1 times):
            move front → back

👉 Now:
    New element comes to FRONT

--------------------------------------------

🧠 Example:

push(1) → [1]

push(2):
    push → [1,2]
    rotate → [2,1]

push(3):
    push → [2,1,3]
    rotate → [3,2,1]

👉 Always:
    front = top of stack

--------------------------------------------

pop():

- Just remove front
👉 O(1)

--------------------------------------------

top():

- Just return front
👉 O(1)

--------------------------------------------

empty():

- q.empty()

--------------------------------------------

⚡ Complexity:

push → O(N)
pop  → O(1)
top  → O(1)

--------------------------------------------

🎯 One line:

"After push, rotate so newest element comes to front"
*/
class MyStack {
public:
    queue<int> q ; 

    MyStack() {
        
    }
    
    void push(int x) {
        q.push(x);
        int currentSize = q.size(); 

        for(int i=1; i< currentSize ; i++)
        {
            int top = q.front() ; 
            q.push(top);
            q.pop();
        }
    }
    
    int pop() {
        if(q.empty())
        {
            return -1 ; 
        }
        int popped_element = q.front() ; 
        q.pop() ; 
        return popped_element;
        
    }
    
    int top() {
        if(q.empty())
        {
            return -1 ; 
        }
        int top_element = q.front() ; 

        return top_element;
    }
    
    bool empty() {
        if(q.size() == 0 )
            return true ; 

        return false;
    }
};

/**
 * Your MyStack object will be instantiated and called as such:
 * MyStack* obj = new MyStack();
 * obj->push(x);
 * int param_2 = obj->pop();
 * int param_3 = obj->top();
 * bool param_4 = obj->empty();
 */
// https://leetcode.com/problems/implement-queue-using-stacks/description/


/*
🔴 Queue using 1 Stack (Brute Force)

🧠 Idea:
- Stack = LIFO
- Queue = FIFO
👉 So we reverse twice to simulate queue

--------------------------------------------

push(x):
- Just push into st1
👉 O(1)

--------------------------------------------

pop():

1. Move all elements to st2
   → reverses order

2. Top of st2 = front of queue
   → remove it

3. Move elements back to st1

👉 O(N)

--------------------------------------------

peek():

Same as pop but:
- DO NOT remove element
👉 just read st2.top()

👉 O(N)

--------------------------------------------

empty():
- Just check st1.empty()

--------------------------------------------

🧠 Mental Model:

st1: [back ... front]

After reversing:
st2: [front ... back]

--------------------------------------------

⚠️ Drawback:

- pop → O(N)
- peek → O(N)

👉 Not optimal (but correct brute force)

--------------------------------------------

🎯 One line:

"Reverse stack → access front → restore"
*/
class MyQueue {
public:
    int currentSize ;
    stack<int> st1 ; 
    MyQueue() {
        currentSize = 0;
    }
    
    void push(int x) 
    {
        st1.push(x);
    }
    
    int pop() 
    {
        if(st1.empty())
        {
            return -1 ; 
        }
        stack<int> st2; 
        while(!st1.empty())
        {
            st2.push(st1.top());
            st1.pop(); 
        }
        int removed_element = st2.top(); 
        st2.pop(); 
        while(!st2.empty())
        {
            st1.push(st2.top());
            st2.pop(); 
        }

        return removed_element; 

    }
    
    int peek() 
    {
        if(st1.empty())
        {
            return -1 ; 
        }
        stack<int> st2; 
        while(!st1.empty())
        {
            st2.push(st1.top());
            st1.pop(); 
        }
        int front_element = st2.top(); 

        while(!st2.empty())
        {
            st1.push(st2.top());
            st2.pop(); 
        }

        return front_element; 
    }
    
    bool empty() {
        if(st1.empty())
        {
            return true; 
        }
        return false;
    }
};


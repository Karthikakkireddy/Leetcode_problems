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

/*
🔴 Queue using 2 Stacks (Push-Costly Version)

🧠 Idea:
- Maintain st1 such that:
      top of st1 = front of queue

👉 So pop/peek become O(1)

--------------------------------------------

push(x):

1. Move all elements from st1 → st2
   (reverse order)

2. Push new element into st1

3. Move everything back from st2 → st1

👉 Now newest element goes to bottom,
   oldest stays on top (queue order)

--------------------------------------------

🧠 Example:

push(1): [1]

push(2):
    st1 → st2: []
    st1 = [2]
    restore → [2,1] (top = 1)

push(3):
    → [3,2,1] (top = 1)

👉 st1 top = front of queue

--------------------------------------------

pop():
- Just pop from st1
👉 O(1)

--------------------------------------------

peek():
- Return st1.top()
👉 O(1)

--------------------------------------------

empty():
- st1.empty()

--------------------------------------------

⚡ Complexity:

push → O(N)
pop  → O(1)
peek → O(1)

--------------------------------------------

🎯 One line:

"Rearrange on push so front stays at top"
*/
class MyQueue {
public:
    stack<int> st1; 
    stack<int> st2; 
    MyQueue() {

    }
    
    void push(int x) 
    {
        while(! st1.empty())
        {
            int top = st1.top(); 
            st2.push(top); 
            st1.pop(); 
        }
        st1.push(x); 
        while(! st2.empty())
        {
            int top = st2.top(); 
            st1.push(top); 
            st2.pop(); 
        }

    }
    
    int pop() 
    {
        if(st1.empty())
            return -1 ;
        int popped_element = st1.top() ; 
        st1.pop() ; 
        return popped_element;
    }
    
    int peek() 
    {
        if(st1.empty())
            return -1 ;
        int top_element = st1.top() ; 

        return top_element;
    }
    
    bool empty() {
        if(st1.empty() )
            return true;
        return false;
    }
};

/*
🔴 Queue using 2 Stacks (Optimal / Amortized O(1))

🧠 Idea:
- st1 → for incoming elements (push)
- st2 → for outgoing elements (pop/peek)

👉 Lazy transfer:
   Move elements ONLY when needed

--------------------------------------------

push(x):

- Always push into st1
👉 O(1)

--------------------------------------------

pop():

1. If st2 NOT empty:
       pop from st2

2. Else:
       Move ALL from st1 → st2
       (this reverses order)

3. Pop from st2

👉 Front element is always on top of st2

--------------------------------------------

peek():

Same as pop, but DO NOT remove

👉 Just return st2.top()

--------------------------------------------

🧠 Example:

push(1), push(2), push(3)

st1 = [1,2,3] (top = 3)
st2 = []

pop():

→ move to st2:
    st2 = [3,2,1] (top = 1)

→ pop → 1 ✅

--------------------------------------------

⚡ Key Insight:

Each element moves:
    st1 → st2 only ONCE

👉 So overall cost is spread out

--------------------------------------------

⚡ Complexity:

push → O(1)
pop  → Amortized O(1)
peek → Amortized O(1)

--------------------------------------------

🎯 One line:

"Push to st1, pop from st2, transfer only when needed"
*/
class MyQueue {
public:
    stack<int> st1; 
    stack<int> st2; 
    MyQueue() {

    }
    
    void push(int x) 
    {
        st1.push(x);
    }
    
    int pop() 
    {
        int popped_element;
        if(!st2.empty())
        {
            popped_element = st2.top();


        }
        else
        {
            while(!st1.empty())
            {
                int top_st1 = st1.top() ;
                st2.push(top_st1);
                st1.pop(); 
            }

        }
        popped_element = st2.top();
        st2.pop();
        return popped_element ;    
    }
    
    int peek() 
    {
        int top_element; 
        if(!st2.empty())
        {
            top_element = st2.top();
        }
        else
        {
            while(!st1.empty())
            {
                int top_st1 = st1.top() ;
                st2.push(top_st1);
                st1.pop(); 
            }

        }
        top_element = st2.top();

        return top_element ;    
    }
    
    bool empty() {
        if(st1.empty() && st2.empty())
            return true;
        return false;
    }
};

// https://leetcode.com/problems/min-stack/description/

/*
🔴 MinStack (Your Approach)

🧠 Idea:
- stk3 → normal stack (for top)
- stk1 → always sorted (min at top)
- stk2 → helper for rearranging

--------------------------------------------

push(val):

- Insert into stk1 in sorted order
  (smallest element always on top)

- Push val into stk3 (normal stack)

👉 Costly because we rearrange stk1

--------------------------------------------

pop():

- Remove top from stk3 → actual element

- Remove same element from stk1:
    → move elements to stk2
    → delete it
    → restore back

👉 Again costly

--------------------------------------------

top():
- Return stk3.top()

--------------------------------------------

getMin():
- Return stk1.top() (smallest element)

--------------------------------------------

⚠️ Complexity:

push → O(N)
pop  → O(N)
top  → O(1)
min  → O(1)

👉 NOT optimal

--------------------------------------------

🧠 Problem:

- Maintaining sorted stack = expensive
- Too much shifting using stk2

--------------------------------------------

🎯 One line:

"Sorted stack for min → but operations become O(N)"
*/
class MinStack {
public:

    stack<int> stk1; 
    stack<int> stk2; 
    stack<int> stk3; 
    MinStack() {
        
    }
    
    void push(int val) {
        
       
            while(!stk1.empty() && val >= stk1.top())
            {
                int temp = stk1.top(); 
                stk2.push(temp) ; 
                stk1.pop();
            }
            stk1.push(val); 
            stk3.push(val);
            while(!stk2.empty())
            {
                int temp = stk2.top(); 
                stk1.push(temp) ; 
                stk2.pop();
            }
        
    }
    
    void pop() {
        int delElement;
        if(!stk3.empty() )
        {
            delElement = stk3.top() ;
            stk3.pop(); 
        }

        if(!stk1.empty() )
        {
            while(!stk1.empty() && stk1.top() != delElement) 
            {
                int temp = stk1.top() ; 
                stk2.push(temp);
                stk1.pop() ;
            }
            stk1.pop(); 
            while(!stk2.empty())
            {
                int temp = stk2.top() ; 
                stk1.push(temp);
                stk2.pop();
            }
        }
    }
    
    int top() {
        return stk3.empty() ? -1 : stk3.top() ; 
    }
    
    int getMin() {
        return stk1.empty() ? -1 : stk1.top() ; 
    }
};

/*
🔴 MinStack (Optimal Approach)

🧠 Idea:
- Store pair: {value, min_so_far}
- Each element remembers minimum till that point

--------------------------------------------

push(val):

- If stack empty:
      min = val
- Else:
      min = min(val, previous min)

- Push: {val, min}

👉 Each element carries its own min

--------------------------------------------

pop():
- Just pop
👉 No extra work

--------------------------------------------

top():
- Return first (value)

--------------------------------------------

getMin():
- Return second (min till now)

--------------------------------------------

⚡ Complexity:

push → O(1)
pop  → O(1)
top  → O(1)
min  → O(1)

👉 Fully optimal

--------------------------------------------

🧠 Mental Model:

"Each element knows the minimum before it"

--------------------------------------------

🎯 One line:

"Store value + min so far → no extra work later"
*/
class MinStack {
public:

    stack<pair<int, int>> stk1; 
    int min_ele;

    MinStack() {

    }
    
    void push(int val) {
        

        if(!stk1.empty())
        {
            int check_min = stk1.top().second; 
            min_ele = min(check_min , val); 
        }
        else
        {
            min_ele = val ; 
        }
        
        
        pair<int, int> temp ;
        temp.first = val ;
        temp.second = min_ele;

        stk1.push(temp);
        
    }
    
    void pop() {
        if(!stk1.empty() )
        {
            stk1.pop() ; 
        }
    }
    
    int top() {
        return stk1.empty() ? -1 : stk1.top().first ; 
    }
    
    int getMin() {
        return stk1.empty() ? -1 : stk1.top().second ; 
    }
};



/*
🔴 MinStack (Clean Final Version)

🧠 Idea:
- Store {value, min_so_far} in stack

--------------------------------------------

push(val):

- If empty:
      push {val, val}

- Else:
      push {val, min(val, previous min)}

👉 No extra variable needed

--------------------------------------------

pop():
- Just pop

--------------------------------------------

top():
- Return first (value)

--------------------------------------------

getMin():
- Return second (min)

--------------------------------------------

⚡ Complexity:

All operations → O(1)

--------------------------------------------

🧠 Why this is better than previous version:

✔ No separate min variable
✔ More concise
✔ Less chance of bugs

--------------------------------------------

🎯 One line:

"Each element stores its own minimum"
*/
class MinStack {
public:

    stack<pair<int, int>> stk1; 


    MinStack() {

    }
    
    void push(int val) {
        

        if(!stk1.empty())
        {
            stk1.push({val, min(val, stk1.top().second)});
        }
        else
        {
            stk1.push({val, val});
        }

    }
    
    void pop() {
        if(!stk1.empty() )
        {
            stk1.pop() ; 
        }
    }
    
    int top() {
        return stk1.empty() ? -1 : stk1.top().first ; 
    }
    
    int getMin() {
        return stk1.empty() ? -1 : stk1.top().second ; 
    }
};

// TC - O(1) and SC - O(2*N)


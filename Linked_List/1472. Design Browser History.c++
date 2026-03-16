/*
    Problem link - https://leetcode.com/problems/design-browser-history/description/
*/

/*
    Idea: Simulating Browser History using a Doubly Linked List

    Each node represents a webpage.

    Node structure:
        val   → URL of the page
        back  → previous page in history
        front → next page in history

    currentPage always points to the page currently open.

---------------------------------------------------------

    visit(url)

    - Create a new node for the new page.
    - Link it after the current page.
    - Move currentPage pointer to the new page.

    Important Browser Behavior:
        If we had gone back earlier, all forward history
        should be discarded.

    In this implementation:
        When we assign
            currentPage->front = newPage
        the previous forward chain becomes unreachable
        and effectively disappears.

---------------------------------------------------------

    back(steps)

    - Move currentPage backward up to 'steps' times.
    - Stop early if there is no previous page.

    Example:
        A → B → C → D
                ↑ current

        back(2) → B

---------------------------------------------------------

    forward(steps)

    - Move currentPage forward up to 'steps' times.
    - Stop if there is no forward page.

    Example:
        A → B → C → D
        ↑ current

        forward(2) → C

---------------------------------------------------------

    Why Doubly Linked List Works Well

    - back pointer allows moving backward
    - front pointer allows moving forward
    - no need to shift elements like in arrays
*/
class Node{
    public:
        string val;
        Node* back ;
        Node* front;

        Node(string data)
        {
            this-> val = data;
            back = NULL;
            front = NULL;
        }
};

class BrowserHistory {
    Node* currentPage;
public:
  
    BrowserHistory(string homepage) {
        currentPage = new Node(homepage);

    }
    
    void visit(string url) {
        Node* newPage = new Node(url);
        currentPage -> front = newPage;
        newPage ->back = currentPage;
        currentPage = newPage;
    }
    
    string back(int steps) {



        while(steps && currentPage -> back !=NULL)
        {
            currentPage = currentPage -> back; 
            steps--;
        }
        return currentPage->val;
    }
    
    string forward(int steps) {
        while(steps && currentPage -> front !=NULL)
        {
            currentPage = currentPage -> front; 
            steps--;
        }
        return currentPage->val;
    }
};

/**
 * Your BrowserHistory object will be instantiated and called as such:
 * BrowserHistory* obj = new BrowserHistory(homepage);
 * obj->visit(url);
 * string param_2 = obj->back(steps);
 * string param_3 = obj->forward(steps);
 */